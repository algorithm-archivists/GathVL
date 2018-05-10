#ifndef VIDEO_MODULE_H
#define VIDEO_MODULE_H

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

#include "vec.h"

struct output_stream {
    AVStream *stream;
    AVCodecContext *codec_ctx;

    std::int64_t next_pts;

    AVFrame *frame;

    struct SwsContext *sws_ctx;
};

struct video_module {
    void encode_frame(cairo_surface_t *surface);

    video_module() : video_module("/tmp/video.mp4") {}
    video_module(std::string file_url) : video_module(file_url, {600, 400}) {}
    video_module(std::string file_url, vec vid_size)
        : video_module(file_url, size, 25) {}
    video_module(std::string file_url, vec vid_size, int frame_rate);

    ~video_module();

private:
    AVFormatContext *format_ctx;
    output_stream ostream;
    std::string url;
    vec size;
    int frames_per_sec;
};

#endif
