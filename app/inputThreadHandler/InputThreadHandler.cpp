#include "./InputThreadHandler.h"

InputThreadHandler::InputThreadHandler(Buffer& buffer): buffer_(buffer) {}

void InputThreadHandler::operator()() {
    std::string input;

    while (std::getline(std::cin, input)) {
        std::vector<std::string> splittedInput = split(input);

        if (splittedInput.empty()) {
            continue;
        }

        Buffer::LoggingMessage loggingMessage = createLog(splittedInput);

        if (loggingMessage.log.empty()) {
            continue;
        }

        buffer_.put(loggingMessage);
    }
}

std::vector<std::string> InputThreadHandler::split(const std::string& str, const char delimeter) const {
    std::vector<std::string> strings;
    std::string tmpString = "";

    for (const auto c: str) {
        if (c == delimeter) {
            if (!tmpString.empty()) {
                strings.push_back(tmpString);
                tmpString.clear();
            }
        } else {
            tmpString += c;
        }
    }

    if (!tmpString.empty()) {
        strings.push_back(tmpString);
    }

    return strings;
}

Buffer::LoggingMessage InputThreadHandler::createLog(const std::vector<std::string>& strings) const {
    Buffer::LoggingMessage loggingMessage;

    std::string strLogLevel = strings.back();
    loggingMessage.level = stringToLogLevel(strLogLevel);

    std::string log = "";
    if (loggingMessage.level == LoggerInterface::LogLevel::NONE) {
        for (const auto& str: strings) {
            log += str;
            log += ' ';
        }
    } else {
        for (size_t i = 0; i != strings.size() - 1; ++i) {
            log += strings[i];
            log += ' ';
        }
    }
    log.pop_back();
    loggingMessage.log = log;

    return loggingMessage;
}