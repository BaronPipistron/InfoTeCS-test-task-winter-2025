#ifndef _BUFFER_H_
#define _BUFFER_H_

#include <condition_variable>
#include <mutex>
#include <string>
#include <queue>

#include "../../lib/LoggerInterface.h"

class Buffer {
  public:
    struct LoggingMessage {
        std::string log;
        LoggerInterface::LogLevel level;
    };

  public:
    Buffer() = default;
    ~Buffer() = default;

    void put(const LoggingMessage& message);
    LoggingMessage pop();

    [[nodiscard]] bool isStop() const noexcept;
    void setStop() noexcept;

  private:
    std::queue<LoggingMessage> buffer_;
    std::condition_variable cv_;
    std::mutex mutex_;
    bool stopFlag_ = false;
};

#endif // _BUFFER_H_