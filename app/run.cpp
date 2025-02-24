#include <iostream>

#include "../lib/LoggerInterface.h"

int main() {
    void* lib = dlopen("./lib/loggerlib.so", RTLD_LAZY);

    if (!lib) {
        std::cerr << "ERROR: can't open dynamic library " << dlerror() << std::endl;
        return 1;
    }

    std::unique_ptr<LoggerInterface> logger = getLoggerInterface(lib, "./test.txt", LoggerInterface::LogLevel::INFO);
    logger->DEBUG("test message");

    logger.reset();
    dlclose(lib);

    return 0;
}