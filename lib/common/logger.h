#ifndef _LOGGER_H_
#define _LOGGER_H_

#include <chrono>
#include <ctime>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>

class Logger {
  public:
    enum class LogLevel {
        NONE,
        DEBUG,
        INFO,
        TRACE,
        WARN,
        ERROR,
        FATAL
    };

    Logger(const std::string&, const LogLevel);
    ~Logger();

    void changeLogLevel(const LogLevel) noexcept;
    
    void DEBUG(const std::string&);
    void INFO(const std::string&);
    void TRACE(const std::string&);
    void WARN(const std::string&);
    void ERROR(const std::string&);
    void FATAL(const std::string&);

  private:
    std::string getCurrentTime() const noexcept;

  private:
    LogLevel level_;
    std::ofstream file_; 
};

extern "C" inline std::unique_ptr<Logger> createLogger(const std::string& journalFile, const Logger::LogLevel logLevel) {
        return std::make_unique<Logger>(journalFile, logLevel);
}

#endif // _LOGGER_H_

