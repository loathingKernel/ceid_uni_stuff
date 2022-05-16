#ifndef MENU_H
#define MENU_H

#include "eshop.h"
#include "item.h"
#include "pen.h"
#include "pencil.h"
#include "notebook.h"
#include "paper.h"
#include "eshoperror.h"


/**
 * \class Menu
 * \brief Creates a menu for the e-shop's interface
 *
 * This class provides the majority of user input and output.
 * It takes an instantiated EShop and provides a navigation Menu.
 */
class Menu
{
public:
    Menu(EShop*);
    ~Menu();

    void showWelcome();
    void showLoginMenu();

    void showOwnerMenu();
    void showBuyerMenu();

    void showBrowseMenu();
    void showCategoryMenu(string);
    void showProductMenu(string, int);
    void showCartMenu();
    void showStatusMenu();
    void showCheckoutMenu();

private:
    /// \brief User authentication
    void login(string);
    /// \brief Helper function to encapsulate yes/no questions
    bool askYesNo(string);

    User* _user = nullptr;
    Owner* _owner = nullptr;
    Buyer* _buyer = nullptr;
    EShop* _eshop;
};

#endif // MENU_H
