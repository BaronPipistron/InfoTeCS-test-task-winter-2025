#include "./LoggerThreadHandler.h"

LoggerThreadHandler::LoggerThreadHandler(std::unique_ptr<LoggerInterface>& logger, Buffer& buffer): 
    logger_(logger), buffer_(buffer) {}

void LoggerThreadHandler::operator()() {
    while (!buffer_.isStop()) {
        Buffer::LoggingMessage message = buffer_.pop();

        if (message.level == LoggerInterface::LogLevel::NONE) {
            message.level = logger_->getDefaultLogLevel();
        }

        switch (message.level) {
            case LoggerInterface::LogLevel::DEBUG:
                logger_->DEBUG(message.log);
                break;
            case LoggerInterface::LogLevel::INFO:
                logger_->INFO(message.log);
                break;
            case LoggerInterface::LogLevel::TRACE:
                logger_->TRACE(message.log);
                break;
            case LoggerInterface::LogLevel::WARN:
                logger_->WARN(message.log);
                break;
            case LoggerInterface::LogLevel::ERROR:
                logger_->ERROR(message.log);
                break;
            case LoggerInterface::LogLevel::FATAL:
                logger_->FATAL(message.log);
                break;
            default:
                break;
        }
    }
}