#ifndef ESHOPERROR_H
#define ESHOPERROR_H

#include <iostream>

using namespace std;

/**
 * \class EShopError
 * \brief Exception class for passing error messages on failures
 */
class EShopError
{
public:

    /**
     * \brief Constructor for empty exception messages
     */
    EShopError() { }
    /**
     * \brief Constructor for empty exception messages
     *
     * @param error The error message to pass
     */
    EShopError(string&& error) : _error(move(error)) { }

    /**
     * \brief Return the error message
     */
    const string& error() const {
        return _error;
    }

private:
    string _error;
};

#endif // ESHOPERROR_H

