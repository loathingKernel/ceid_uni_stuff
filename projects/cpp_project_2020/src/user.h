#ifndef USER_H
#define USER_H

#include <iostream>

using namespace std;

/**
 * \class User
 * \brief Base class for all users.
 *
 * Base abstract class to subclassed by the Owner and Buyer specialized classes.
 * Implements the common functions of setting the Name and the Email of the user.
 */
class User {
public:
    /**
     * \brief Constructor for User, called by Owner and Buyer
     *
     * @param name string. The name of the user
     * @param email string. The email of the user
     */
    User(string name, string email);

    /**
     * \fn string getName()
     * \brief Get the Name of the user.
     *
     * @param none
     * @return string The user's name
     */
    string getName();
    /**
     * \fn string getEmail()
     * \brief Get the Email of the user.
     *
     * @param none
     * @return string The user's email
     */
    string getEmail();

    /**
     * \brief Check if the user is an admin.
     *
     * Virtual function implemented in the derivative classes
     *
     * @param none
     * @return bool True if the user is an owner, false otherwise.
     */
    virtual bool isAdmin() = 0;

private:
    void setName(string name);
    void setEmail(string email);

    string _name;
    string _email;
};

#endif // USER_H
