#ifndef _LOGGER_INTERFACE_H_
#define _LOGGER_INTERFACE_H_

#include <dlfcn.h>
#include <iostream>
#include <memory>
#include <string>

class LoggerInterface {
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

    virtual ~LoggerInterface() = default;

    virtual void changeLogLevel(const LogLevel) noexcept = 0;
    virtual LogLevel getDefaultLogLevel() const noexcept = 0;
    
    virtual void DEBUG(const std::string&) = 0;
    virtual void INFO(const std::string&) = 0;
    virtual void TRACE(const std::string&) = 0;
    virtual void WARN(const std::string&) = 0;
    virtual void ERROR(const std::string&) = 0;
    virtual void FATAL(const std::string&) = 0;
};

inline LoggerInterface::LogLevel stringToLogLevel(const std::string& str) {
    if (str == "DEBUG") {
        return LoggerInterface::LogLevel::DEBUG;
    } else if (str == "INFO") {
        return LoggerInterface::LogLevel::INFO;
    } else if (str == "TRACE") {
        return LoggerInterface::LogLevel::TRACE;
    } else if (str == "WARN") {
        return LoggerInterface::LogLevel::WARN;
    } else if (str == "ERROR") {
        return LoggerInterface::LogLevel::ERROR;
    } else if (str == "FATAL") {
        return LoggerInterface::LogLevel::FATAL;
    }

    return LoggerInterface::LogLevel::NONE;
}

extern "C" inline std::unique_ptr<LoggerInterface> getLoggerInterface(
    void* lib,
    const std::string& journalFile, 
    const LoggerInterface::LogLevel logLevel
    )
{
    using CreateLoggerFuncPtr = std::unique_ptr<LoggerInterface>(*)(const std::string&, const LoggerInterface::LogLevel);

    CreateLoggerFuncPtr createLoggerFunc = reinterpret_cast<CreateLoggerFuncPtr>(dlsym(lib, "createLogger"));

    if (!createLoggerFunc) {
        std::cerr << "ERROR: can't load createLogger function" << std::endl;
        return nullptr;
    }

    std::unique_ptr<LoggerInterface> loggerInterface = createLoggerFunc(journalFile, logLevel);

    if (!loggerInterface) {
        std::cerr << "ERROR: can't create loggerInterface" << std::endl;
        return nullptr;
    }

    return loggerInterface;
}

#endif // _LOGGER_INTERFACE_H_