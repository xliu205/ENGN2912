

#ifndef _STR_EXCEPTION_HPP_
#define _STR_EXCEPTION_HPP_

#include <string>
#include <exception>

using namespace std;



class StrException : public exception {

protected:

  const string _msg;

public:

  StrException(const string& msg):_msg(msg) { }
  virtual ~StrException() throw() {}

  virtual const char* what() const throw() { return _msg.c_str(); }

};

#endif // _STR_EXCEPTION_HPP_
