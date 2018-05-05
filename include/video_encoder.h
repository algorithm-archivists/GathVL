#ifndef VIDEO_ENCODER_H
#define VIDEO_ENCODER_H

#include <memory>
#include <string>
#include <fstream>

#include <libavformat/avformat.h>
#include <libavutil/opt.h>

struct video_encoder {
    AVCodec *codec;
    AVOutputFormat *format;
    AVDictionary *opt;
    std::unique_ptr<AVFormatContext> context;
    std::ofstream file;

    void encode_frame();
    void close();

    video_encoder(std::string file_url);
};

#endif
