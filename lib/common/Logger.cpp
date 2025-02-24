#include "./Logger.h"

Logger::Logger(const std::string& journalFile, const LogLevel logLevel) : level_(logLevel) {
    file_.open(journalFile, std::ios::app);

    if (!file_) {
        throw std::runtime_error("ERROR: Can't open journal file " + journalFile);
    }
}

Logger::~Logger() {
    file_.close();
}

void Logger::changeLogLevel(const LogLevel logLevel) noexcept {
    level_ = logLevel;
}

void Logger::DEBUG(const std::string& message) {
    if (level_ <= LogLevel::DEBUG) {
        file_ << message << ' ' << "[ DEBUG ]" << ' ' \
              << "[ " << getCurrentTime() << " ]" << std::endl;
    }
}

void Logger::INFO(const std::string& message) {
    if (level_ <= LogLevel::INFO) {
        file_ << message << ' ' << "[ INFO ]" << ' ' \
              << "[ " << getCurrentTime() << " ]" << std::endl;
    }
}

void Logger::TRACE(const std::string& message) {
    if (level_ <= LogLevel::TRACE) {
        file_ << message << ' ' << "[ TRACE ]" << ' ' \
              << "[ " << getCurrentTime() << " ]" << std::endl;
    }
}

void Logger::WARN(const std::string& message) {
    if (level_ <= LogLevel::WARN) {
        file_ << message << ' ' << "[ WARN ]" << ' ' \
              << "[ " << getCurrentTime() << " ]" << std::endl;
    }
}

void Logger::ERROR(const std::string& message) {
    if (level_ <= LogLevel::ERROR) {
        file_ << message << ' ' << "[ ERROR ]" << ' ' \
              << "[ " << getCurrentTime() << " ]" << std::endl;
    }
}

void Logger::FATAL(const std::string& message) {
    if (level_ <= LogLevel::FATAL) {
        file_ << message << ' ' << "[ FATAL ]" << ' ' \
              << "[ " << getCurrentTime() << " ]" << std::endl;
    }
}

std::string Logger::getCurrentTime() const noexcept {
    auto time = std::chrono::system_clock::now();
    std::time_t current_time_t = std::chrono::system_clock::to_time_t(time);

    std::string current_time = std::ctime(&current_time_t);
    current_time.pop_back();

    return current_time;
}

extern "C" std::unique_ptr<LoggerInterface> createLogger(
    const std::string& journalFile, 
    const Logger::LogLevel logLevel
    ) 
{
    return std::make_unique<Logger>(journalFile, logLevel);
}