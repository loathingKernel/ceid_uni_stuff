#ifndef MENU_H
#define MENU_H

#include "eshop.h"
#include "item.h"
#include "pen.h"
#include "pencil.h"
#include "notebook.h"
#include "paper.h"
#include "eshoperror.h"

class Menu
{
public:
    Menu(EShop*);

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


    ~Menu();

private:
    void login(string);
    bool askYesNo(string);

    User* _user = nullptr;
    Owner* _owner = nullptr;
    Buyer* _buyer = nullptr;
    EShop* _eshop;
};

#endif // MENU_H
