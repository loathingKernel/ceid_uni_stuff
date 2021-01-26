#ifndef OWNER_H
#define OWNER_H

#include "user.h"

using namespace std;

/**
 * \class Owner
 * \brief Specialization of User. Describes an Owner
 *
 * Derivative class to specialize a User.
 * Implements Owner related functionality.
 * Basically nothing because I didn't look forward enough
 * Things like managing Buyers could be in here
 */
class Owner final: public User {
public:
    /**
     * \brief Constructor of Owner
     *
     * @param name Owner's name
     * @param email Owner's login email
     */
    Owner(string name, string email);

    /**
     * \brief Impementation of isAdmin() of User
     *
     * @param none
     * @return bool Always true
     */
    bool isAdmin();

private:
    /// This was requested by the project, it is pointless
    bool _isAdmin;
};

#endif // OWNER_H
