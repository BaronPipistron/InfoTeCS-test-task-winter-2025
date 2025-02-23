#include "./logger.h"

Logger::Logger(const std::string& journalFile, const LogLevel logLevel) : level_(logLevel) {
    file_.open(journalFile, std::ios::app);

    if (!file_) {
        throw std::runtime_error("ERROR: Can't open journal file " + journalFile);
    }
}

Logger::~Logger() {
    file_.close();
}

/*
    Think about refactoring
    Repeating code
*/

void Logger::changeLogLevel(const LogLevel logLevel) noexcept {
    level_ = logLevel;
}

void Logger::DEBUG(const std::string& message) {
    file_ << message << ' ' << "[ DEBUG ]" << ' ' \
          << "[ " << getCurrentTime() << " ]" << std::endl;
}

void Logger::INFO(const std::string& message) {
    file_ << message << ' ' << "[ INFO ]" << ' ' \
          << "[ " << getCurrentTime() << " ]" << std::endl;
}

void Logger::TRACE(const std::string& message) {
    file_ << message << ' ' << "[ TRACE ]" << ' ' \
          << "[ " << getCurrentTime() << " ]" << std::endl;
}

void Logger::WARN(const std::string& message) {
    file_ << message << ' ' << "[ WARN ]" << ' ' \
          << "[ " << getCurrentTime() << " ]" << std::endl;
}

void Logger::ERROR(const std::string& message) {
    file_ << message << ' ' << "[ ERROR ]" << ' ' \
          << "[ " << getCurrentTime() << " ]" << std::endl;
}

void Logger::FATAL(const std::string& message) {
    file_ << message << ' ' << "[ FATAL ]" << ' ' \
          << "[ " << getCurrentTime() << " ]" << std::endl;
}

std::string Logger::getCurrentTime() const noexcept {
    auto time = std::chrono::system_clock::now();
    std::time_t current_time_t = std::chrono::system_clock::to_time_t(time);

    std::string current_time = std::ctime(&current_time_t);
    current_time.pop_back();

    return current_time;
}