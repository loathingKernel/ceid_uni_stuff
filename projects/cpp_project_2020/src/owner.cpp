#include "owner.h"

Owner::Owner(string name, string email) : User(name, email)
{
    _isAdmin = true;
}

bool
Owner::isAdmin() { return _isAdmin; }
