#include "../include/video_encoder.h"

#include <iostream>
#include <cstdlib>
#include <cstdint>

static void add_stream(output_stream *ostream, AVFormatContext *format_ctx,
                       AVCodec **codec, enum AVCodecID codec_id) {
    AVCodecContext *codec_ctx;

    *codec = avcodec_find_encoder(codec_id);

    if (!(*codec)) {
        std::cout << "Could not find encoder for "
            << avcodec_get_name(codec_id) << std::endl;
        std::exit(1);
    }

    ostream->stream = avformat_new_stream(format_ctx, NULL);
    if (!ostream->stream) {
        std::cout << "Could not allocate stream" << std::endl;
        std::exit(1);
    }

    ostream->stream->id = format_ctx->nb_streams-1;
    codec_ctx = avcodec_alloc_context3(*codec);
    if (!codec_ctx) {
        std::cout << "Could not alloc an encoding context" << std::endl;
        std::exit(1);
    }
    ostream->codec_ctx = codec_ctx;

    if (format_ctx->oformat->flags & AVFMT_GLOBALHEADER) {
        codec_ctx->flags |= AV_CODEC_FLAG_GLOBAL_HEADER;
    }
}

static AVFrame *alloc_picture(enum AVPixelFormat pix_fmt, int width,
                              int height) {
    AVFrame *picture;

    picture = av_frame_alloc();
    if (!picture) {
        return NULL;
    }

    picture->format = pix_fmt;
    picture->width  = width;
    picture->height = height;

    if (av_frame_get_buffer(picture, 0) < 0) {
        std::cout << "Could not allocate frame data." << std::endl;
        std::exit(1);
    }

    return picture;
}

static void open_video(AVFormatContext *format_ctx, AVCodec *codec,
                       output_stream *ostream, AVDictionary *opt_arg) {
    AVCodecContext *codec_ctx = ostream->codec_ctx;
    AVDictionary *opt = NULL;

    av_dict_copy(&opt, opt_arg, 0);

    int ret = avcodec_open2(codec_ctx, codec, &opt);
    av_dict_free(&opt);
    if (ret < 0) {
        std::cout << "Could not open video codec." << std::endl;
        std::exit(1);
    }

    ostream->frame = alloc_picture(codec_ctx->pix_fmt, codec_ctx->width,
                                   codec_ctx->height);
    if (!ostream->frame) {
        std::cout << "Could not allocate video frame" << std::endl;
        std::exit(1);
    }

    ret = avcodec_parameters_from_context(ostream->stream->codecpar,
                                          codec_ctx);
    if (ret < 0) {
        std::cout << "Could not copy the stream parameters" << std::endl;
        std::exit(1);
    }
}

static void write_frame(AVFormatContext *format_ctx, output_stream *ostream,
                        AVFrame *frame) {
    AVCodecContext *c = ostream->codec_ctx;
    AVPacket *pkt = nullptr;

    pkt = av_packet_alloc();
    if (!pkt) {
        std::cout << "Could not allocate a packet" << std::endl;
        std::exit(1);
    }

    int ret = avcodec_send_frame(c, frame);
    if (ret < 0) {
        std::cout << "Error encoding video frame." << std::endl;
        std::exit(1);
    }

    while (ret >= 0) {
        ret = avcodec_receive_packet(c, pkt);
        if (ret == AVERROR(EAGAIN) || ret == AVERROR_EOF)
            break;
        else if (ret < 0) {
            std::cout << "Error during encoding." << std::endl;
            std::exit(1);
        }

        av_packet_rescale_ts(pkt, c->time_base, ostream->stream->time_base);
        pkt->stream_index = ostream->stream->index;

        ret = av_interleaved_write_frame(format_ctx, pkt);
        av_packet_unref(pkt);
        if (ret < 0) {
            std::cout << "Error while writing video frame." << std::endl;
            std::exit(1);
        }
    }
}

void video_encoder::encode(cairo_surface_t *image) {
    AVCodecContext *c = ostream.codec_ctx;
    AVFrame *frame = nullptr;

    cairo_surface_flush(image);
    uint8_t *data[1] = {(uint8_t*)cairo_image_surface_get_data(image)};
    int stride[1] = {cairo_image_surface_get_stride(image)};
    cairo_surface_mark_dirty(image);

    if (av_frame_make_writable(ostream.frame) < 0) {
        std::exit(1);
    }

    frame = ostream.frame;
    if (c->pix_fmt != AV_PIX_FMT_BGRA) {
        sws_scale(ostream.sws_ctx, data, stride, 0, c->height, frame->data,
                  frame->linesize);
    } else {
        av_image_fill_arrays(frame->data, frame->linesize, data[0], c->pix_fmt,
                             c->width, c->height, stride[0]);
    }

    ostream.frame->pts = ostream.next_pts++;

    write_frame(format_ctx, &ostream, ostream.frame);
}

video_encoder::video_encoder(std::string url, vec vid_size, int frame_rate)
    : encoder(url), size(vid_size), frames_per_sec(frame_rate) {
    AVOutputFormat *format;
    ostream = {0};
    AVCodec *codec;
    AVDictionary *opt = nullptr;

    av_register_all();

    avformat_alloc_output_context2(&format_ctx, NULL, NULL, url.c_str());
    if (!format_ctx) {
        std::cout << "Could not deduce format from file extension: using MPEG."
            << std::endl;
        avformat_alloc_output_context2(&format_ctx, NULL, "mpeg", url.c_str());
    }

    if (!format_ctx) {
        std::cout << "Can not make format context." << std::endl;
        std::exit(1);
    }

    format = format_ctx->oformat;

    if (format->video_codec == AV_CODEC_ID_NONE) {
        std::cout << "No video codec ID." << std::endl;
    }

    add_stream(&ostream, format_ctx, &codec, format->video_codec);

    if (codec->type == AVMEDIA_TYPE_VIDEO) {
        ostream.codec_ctx->codec_id = format->video_codec;
        ostream.codec_ctx->bit_rate = 400000;
        ostream.codec_ctx->width = static_cast<int>(size.x);
        ostream.codec_ctx->height = static_cast<int>(size.y);
        ostream.codec_ctx->time_base = {1, frames_per_sec};
        ostream.stream->time_base = ostream.codec_ctx->time_base;
        ostream.codec_ctx->gop_size = 12;
        ostream.codec_ctx->pix_fmt = AV_PIX_FMT_YUV420P;

        if (ostream.codec_ctx->codec_id == AV_CODEC_ID_MPEG2VIDEO) {
            ostream.codec_ctx->max_b_frames = 2;
        }

        if (ostream.codec_ctx->codec_id == AV_CODEC_ID_MPEG1VIDEO) {
            ostream.codec_ctx->mb_decision = 2;
        }
    }

    open_video(format_ctx, codec, &ostream, opt);

    av_dump_format(format_ctx, 0, url.c_str(), 1);

    int ret = 0;
    if (!(format->flags & AVFMT_NOFILE)) {
        ret = avio_open(&format_ctx->pb, url.c_str(), AVIO_FLAG_WRITE);
        if (ret < 0) {
            std::cout << "Could not open '" << url.c_str() << "'." << std::endl;
            std::exit(1);
        }
    }

    ret = avformat_write_header(format_ctx, &opt);
    if (ret < 0) {
        std::cout << "Error occurred when opening output file." << std::endl;
        std::exit(1);
    }

    if (ostream.codec_ctx->pix_fmt != AV_PIX_FMT_BGRA) {
        ostream.sws_ctx = sws_getContext(ostream.codec_ctx->width,
                                         ostream.codec_ctx->height,
                                         AV_PIX_FMT_BGRA,
                                         ostream.codec_ctx->width,
                                         ostream.codec_ctx->height,
                                         ostream.codec_ctx->pix_fmt,
                                         SWS_BICUBIC, NULL, NULL, NULL);
        if (!ostream.sws_ctx) {
            std::cout << "Could not initialize the conversion context"
                << std::endl;
            std::exit(1);
        }
    }
}

video_encoder::~video_encoder() {
    write_frame(format_ctx, &ostream, NULL);

    av_write_trailer(format_ctx);

    avcodec_free_context(&ostream.codec_ctx);
    av_frame_free(&ostream.frame);
    sws_freeContext(ostream.sws_ctx);

    if (!(format_ctx->oformat->flags & AVFMT_NOFILE)) {
        avio_closep(&format_ctx->pb);
    }

    avformat_free_context(format_ctx);
}
