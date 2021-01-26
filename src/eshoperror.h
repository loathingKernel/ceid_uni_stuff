#ifndef ESHOPERROR_H
#define ESHOPERROR_H

#include <iostream>

using namespace std;

class EShopError
{
public:

    EShopError() { }
    EShopError(string&& error) : _error(move(error)) { }

    const string& error() const {
        return _error;
    }

private:
    string _error;
};

#if 0

#include <iostream>
#include <exception>
using namespace std;

struct MyException : public exception {
const char * what () const throw () {
return "C++ Exception";
}
};

int test() {
try {
throw MyException();
} catch(MyException& e) {
std::cout << "MyException caught" << std::endl;
std::cout << e.what() << std::endl;
} catch(std::exception& e) {
//Other errors
}
}
#endif

#endif // ESHOPERROR_H

