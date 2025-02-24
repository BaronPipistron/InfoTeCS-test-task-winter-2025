#ifndef _LOGGER_THREAD_HANDLER_H_
#define _LOGGER_THREAD_HANDLER_H_

#include "../buffer/Buffer.h"

class LoggerThreadHandler {
  public:
    LoggerThreadHandler(std::unique_ptr<LoggerInterface>&, Buffer&);

    void operator()();

  private:
    std::unique_ptr<LoggerInterface>& logger_;
    Buffer& buffer_;
};

#endif // _LOGGER_THREAD_HANDLER_H_