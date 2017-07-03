#ifndef hq_data_h__
#define hq_data_h__

#include <unordered_map>
#include <vector>
#include <thread>
#include <memory>
#include <chrono>
#include <mutex>
#include <string>


class HqData {

public:
    typedef std::unordered_map<std::string, std::string> HqBuffer;

    static HqData& instance();

    void SetFastHqFile(const char* hq_file);

    void SetInterval(int ms);

    void StartReading();

    std::string ReadFastHq(const char* zqdm);

private:
    HqData();

    ~HqData();

    HqBuffer* GetFreeBuffer();

    void SwitchBuffer();
private:
    std::string hq_file_;

    std::chrono::milliseconds interval_ms_;

private:
    HqBuffer buffer_a_;

    HqBuffer buffer_b_;

    HqBuffer* current_buffer_;

    std::mutex mutex_;

    std::shared_ptr<std::thread> loading_thread_;
};


#endif // hq_data_h__
