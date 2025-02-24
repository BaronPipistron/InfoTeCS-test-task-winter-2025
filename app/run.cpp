#include <iostream>
#include <string>
#include <thread>

#include "./buffer/Buffer.h"
#include "./inputThreadHandler/InputThreadHandler.h"
#include "./loggerThreadHandler/LoggerThreadHandler.h"

#include "../lib/LoggerInterface.h"

const std::string LOGGER_DLIB_PATH = "../lib/loggerlib.so";

int main(int argc, char** argv) {
    if (argc != 3) {
        std::cerr << "ERROR: programm arguments is logger journal file " \
                  << "and default log level" << std::endl;
        
        return 1;
    }

    std::string journalFile = argv[1];
    std::string stringDefaultLogLevel = argv[2];
    LoggerInterface::LogLevel defaultLogLevel = stringToLogLevel(stringDefaultLogLevel); 

    void* lib = dlopen(LOGGER_DLIB_PATH.c_str(), RTLD_LAZY);
    if (!lib) {
        std::cerr << "ERROR: can't open dynamic library - " << dlerror() << std::endl;
        return 1;
    } else {
        std::cout << "INFO: dynamic library successfully loaded" << std::endl;
    }

    std::unique_ptr<LoggerInterface> logger = getLoggerInterface(lib, journalFile, defaultLogLevel);
    if (!logger) {
        std::cerr << "ERROR: can't initialize Logger" << std::endl;
    } else {
        std::cout << "INFO: Logger successfully initialized" << std::endl;
    }
    Buffer buffer;

    LoggerThreadHandler loggerHandler(logger, buffer);
    InputThreadHandler inputHandler(buffer);

    std::thread loggerThread(loggerHandler);
    inputHandler();

    loggerThread.join();

    logger.reset();
    dlclose(lib);

    return 0;
}