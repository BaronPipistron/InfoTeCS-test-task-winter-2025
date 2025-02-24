#include "./Buffer.h"

void Buffer::put(const LoggingMessage& message) {
    buffer_.push(message);
    cv_.notify_one();
}

Buffer::LoggingMessage Buffer::pop() {
    std::unique_lock<std::mutex> lock(mutex_);
    cv_.wait(lock, [&]{ return !buffer_.empty(); });

    LoggingMessage msg = buffer_.front();
    buffer_.pop();

    return msg;
}

bool Buffer::isStop() const noexcept {
    return stopFlag_;
}

void Buffer::setStop() noexcept {
    stopFlag_ = true;
    cv_.notify_one();
}