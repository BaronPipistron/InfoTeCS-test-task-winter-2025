#include <iostream>

#include "../lib/common/logger.h"

int main() {
    std::unique_ptr<Logger> logger = createLogger("test.txt", Logger::LogLevel::DEBUG);

    logger->FATAL("test message");

    return 0;
}