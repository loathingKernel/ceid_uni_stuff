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

#endif // ESHOPERROR_H

