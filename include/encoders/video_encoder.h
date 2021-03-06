#ifndef GATHVL_VIDEO_ENCODER_H
#define GATHVL_VIDEO_ENCODER_H

#include <memory>
#include <string>
#include <fstream>

#include <cairo.h>

extern "C" {
    #include <libavformat/avformat.h>
    #include <libavutil/opt.h>
    #include <libswscale/swscale.h>
    #include <libavutil/imgutils.h>
}

#include "encoder.h"
#include "../types/vec.h"

struct output_stream {
    AVStream *stream;
    AVCodecContext *codec_ctx;

    std::int64_t next_pts;

    AVFrame *frame;

    struct SwsContext *sws_ctx;
};

struct video_encoder : encoder {
    void encode(cairo_surface_t *image) override;

    video_encoder() : video_encoder("/tmp/video.mp4") {}
    video_encoder(std::string file_url) :
        video_encoder(file_url, {600, 400}) {}
    video_encoder(std::string file_url, vec vid_size) :
        video_encoder(file_url, size, 25) {}
    video_encoder(std::string file_url, vec vid_size, int frame_rate);

    ~video_encoder();

private:
    AVFormatContext *format_ctx;
    output_stream ostream;
    vec size;
    int frames_per_sec;
};

#endif //GATHVL_VIDEO_ENCODER_H
