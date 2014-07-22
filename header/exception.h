#ifndef _EXCEPTION_H_
#define _EXCEPTION_H_

#include <string>
#include <boost/exception/all.hpp>

typedef boost::error_info<struct tag_error, std::string> ExceptionDescription;

//following exceptions are available
//BasicException
//FileOpenException
//AccessViolationException
//OutOfRangeException

//base class for all exceptions, with boost debug information
class BasicException :
    public boost::exception,
    public std::exception {
public:
    BasicException(const std::string& error) throw()
        : error_(error) {
    };

    virtual ~BasicException() throw() {
    }
	
//implement std::exception.what()
    virtual char const* what() const throw() {
        return error_.c_str();
    }

private:
    std::string error_; //error description
};


class FileOpenException :
    public BasicException {
public:
    FileOpenException() throw() :
        BasicException("Error while reading file!") {
    }

    FileOpenException(std::string path) throw() :
        BasicException("Error while reading " + path) {
    }

};


class OutOfRangeException : public BasicException {
public:
    OutOfRangeException() throw()
        : BasicException("Tried to access element out of range!") {
    }
    OutOfRangeException(std::string what) throw()
        : BasicException(what) {
    }
};

class AccessViolationException : public BasicException {
public:
    AccessViolationException() throw()
        : BasicException(std::string("Tried to access uninitialized element")) {
    }
    AccessViolationException(std::string what) throw()
        : BasicException(what) {
    }
};



#endif
