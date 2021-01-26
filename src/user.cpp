#include "user.h"

User::User(string name, string email)
{
    setName(name);
    setEmail(email);
}

void
User::setName(string name) { _name = name; }

string
User::getName() { return _name; }

void
User::setEmail(string email) { _email = email; }

string
User::getEmail() { return _email; }
