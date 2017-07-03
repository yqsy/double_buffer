#include "hq_data.h"

#include <fstream>

#include "string_extra.h"

HqData& HqData::instance() {
    static HqData hq_data;
    return hq_data;
}

void HqData::SetFastHqFile(const char* hq_file) {
    hq_file_ = hq_file;
}

void HqData::SetInterval(int ms) {
    interval_ms_ = std::chrono::milliseconds(ms);
}

void HqData::StartReading() {

    loading_thread_ = std::make_shared<std::thread>([this] {
        for (;;) {
            HqBuffer* free_buffer = GetFreeBuffer();

            std::ifstream infile(hq_file_);

            std::string line;

            int current_line = 0;
            while (std::getline(infile, line)) {
                current_line++;
                if (current_line == 1) {
                    continue;
                }

                std::string zq_code;
                if (GetSplitStringPosition(line, "|", 2, &zq_code)) {
                    (*free_buffer)[zq_code] = line;
                }
            }

            {
                std::lock_guard<std::mutex> lg(mutex_);
                SwitchBuffer();
            }

            std::this_thread::sleep_for(interval_ms_);
        }
    });
}

std::string HqData::ReadFastHq(const char* zqdm) {
    std::lock_guard<std::mutex> lg(mutex_);
    auto iter = current_buffer_->find(zqdm);
    if (iter != current_buffer_->end()) {
        return iter->second;
    } else {
        return "";
    }
}

HqData::HqData() {
    hq_file_ = "./mktdt00.txt";
    interval_ms_ = std::chrono::milliseconds(3000);
    current_buffer_ = &buffer_a_;
}

HqData::~HqData() {
    loading_thread_->detach();
}

HqData::HqBuffer* HqData::GetFreeBuffer() {
    if (current_buffer_ == &buffer_a_) {
        return &buffer_b_;
    } else {
        return &buffer_a_;
    }
}

void HqData::SwitchBuffer() {
    if (current_buffer_ == &buffer_a_) {
        current_buffer_ = &buffer_b_;
    } else {
        current_buffer_ = &buffer_a_;
    }
}

