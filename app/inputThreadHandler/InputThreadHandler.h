#ifndef _INPUT_THREAD_HANDLER_H_
#define _INPUT_THREAD_HANDLER_H_

#include <iostream>
#include <vector>
#include <string>

#include "../buffer/Buffer.h"

class InputThreadHandler {
  public:
    InputThreadHandler(Buffer&);
    ~InputThreadHandler() = default;

    void operator()();

  private:
    std::vector<std::string> split(const std::string&, const char = ' ') const;
    Buffer::LoggingMessage createLog(const std::vector<std::string>&) const;

  private:
    Buffer& buffer_;
};

#endif // _INPUT_THREAD_HANDLER_H_