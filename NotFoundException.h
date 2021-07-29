#ifndef CSCI2421_NOTFOUNDEXCEPTION_H
#define CSCI2421_NOTFOUNDEXCEPTION_H


#include <stdexcept>
#include <string>

class NotFoundException : public std::logic_error
{
public:
    explicit NotFoundException(const std::string& message = "")
    : std::logic_error("Precondition Violated Exception: " + message){}
};

#endif //CSCI2421_NOTFOUNDEXCEPTION_H
