#include "hq_data.h"

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
            {
                HqBuffer* free_buf = GetFreeBuffer();

                // Lock and read data into free_buf

                SwitchBuffer();
            }

            std::this_thread::sleep_for(interval_ms_);
        }
    });
}

std::string HqData::ReadFastHq(const char* zqdm) {
    

    HqBuffer* current_buf = GetCurrentBuffer();

    // Lock find in map and reutrn read

    return "";
}

HqData::HqBuffer* HqData::GetFreeBuffer() {
    std::lock_guard<std::mutex> lg(mutex_);
    if (current_buffer_ == &buffer_a_)
        return &buffer_b_;
    else
        return &buffer_a_;
}

HqData::HqBuffer* HqData::GetCurrentBuffer() {
    std::lock_guard<std::mutex> lg(mutex_);
    if (current_buffer_ == &buffer_a_)
        return &buffer_a_;
    else
        return &buffer_b_;
}

void HqData::SwitchBuffer() {
    std::lock_guard<std::mutex> lg(mutex_);
    if (current_buffer_ == &buffer_a_)
        current_buffer_ = &buffer_b_;
    else
        current_buffer_ = &buffer_a_;
}

