#include <iomanip>
#include <set>
#include <iterator>
#include "menu.h"

Menu::Menu(EShop* eshop)
{
    _eshop = eshop;
    showWelcome();
}

void
Menu::showWelcome()
{
    cout << "Welcome to " << quoted(_eshop ->getName()) << endl;
    showLoginMenu();
    if(_user->isAdmin()) {
        showOwnerMenu();
    } else {
        showBuyerMenu();
    }
}

void
Menu::showLoginMenu()
{
    string email;
    cout << "Enter the email address of a user to log in: ";
    cin >> email;
    try {
        login(email);
    } catch (const EShopError& e) {
        cout << e.error() << endl;
        exit(-1);
    }
}

void
Menu::showOwnerMenu()
{
    cout << "Hello " << quoted(_owner->getName()) << " " << quoted(_owner->getEmail()) << endl;
    cout << "You are the owner of " << quoted(_eshop->getName()) << endl;
    cout << endl;
    cout << "Please choose an action." << endl;
    cout << "1. Browse Store" << endl;
    cout << "2. Check Status" << endl;
    cout << "3. Back" << endl;
    cout << "4. Logout" << endl;
    cout << "5. Exit" << endl;

    string ans; int chc;
    do {
        cout << "Action: ";
        cin >> ans;
        chc = stoi(ans);
    } while( !cin.fail() && chc < 1 && chc > 5);

    switch (stoi(ans)) {
        case 1:
            showBrowseMenu();
            break;
        case 2:
            showStatusMenu();
            break;
        case 3:
            showBuyerMenu();
            break;
        case 4:
            showLoginMenu();
            break;
        default:
            exit(0);
    }
}

void
Menu::showStatusMenu()
{
    cout << "Please choose a buyer." << endl;
    vector<vector<string>> buyers = _eshop->checkStatus();
    int idx = 0;
    for(auto b: buyers) {
        cout << to_string(++idx) << ". " << b[0] << " " << b[1] << " " << b[2] << " " << b[3] << " " << endl;
    }
    cout << to_string(idx+1) << ". Back" << endl;

    string ans; int chc;
    do {
        cout << "Buyer: ";
        cin >> ans;
        chc = stoi(ans);
    } while( !cin.fail() && chc < 1 && chc > idx+1);

    if (chc <= idx) {
        Buyer* buyer = _eshop->getBuyerByEmail(buyers[chc][0]);
        buyer->showCart();

        if (askYesNo("Do you want to delete this buyer?")) {
            _eshop->removeBuyer(buyer);
        }
        showStatusMenu();
    } else {
        showOwnerMenu();
    }
}


void
Menu::showBuyerMenu()
{
    cout << "Hello " << quoted(_buyer->getName()) << " " << quoted(_buyer->getEmail()) << endl;
    cout << "You are a " << quoted(_buyer->getCategoryName()) << " customer with " << _buyer->getBonus() << " points" << endl;
    cout << endl;
    cout << "Please choose an action." << endl;
    cout << "1. Browse Store" << endl;
    cout << "2. View Cart" << endl;
    cout << "3. Checkout" << endl;
    cout << "4. Back" << endl;
    cout << "5. Logout" << endl;
    cout << "6. Exit" << endl;

    string ans;
    do {
        cout << "Action: ";
        cin >> ans;
    } while( !cin.fail() && stoi(ans) < 1 && stoi(ans) > 6);

    switch (stoi(ans)) {
        case 1:
            showBrowseMenu();
            break;
        case 2:
            showCartMenu();
            break;
        case 3:
            showCheckoutMenu();
            break;
        case 4:
            showBuyerMenu();
            break;
        case 5:
            showLoginMenu();
            break;
        default:
            exit(0);
    }
}

void
Menu::showBrowseMenu()
{
    cout << "Please choose a category." << endl;
    vector<pair<string, int>> categories = _eshop->getCategories();
    int idx = 0;
    for(auto c: categories) {
        cout << to_string(++idx) << ". " << c.first << " " << "(" << c.second << ")" << endl;
    }
    cout << to_string(idx+1) << ". Back" << endl;

    string ans; int chc;
    do {
        cout << "Category: ";
        cin >> ans;
        chc = stoi(ans);
    } while( !cin.fail() && chc < 1 && chc > idx+1);

    if (chc <= idx) {
        showCategoryMenu(categories[chc-1].first);
    } else {
        if (_user->isAdmin())
            showOwnerMenu();
        else
            showBuyerMenu();
    }
}

void
Menu::showCategoryMenu(string category)
{
    cout << "Please select a product." << endl;
    vector<pair<int, string>> products = _eshop->getProductsInCategory(category);
    int idx = 0;
    for(auto p: products) {
        cout << to_string(++idx) << ". " << p.first << " " << "(" << p.second << ")" << endl;
    }
    cout << to_string(idx+1) << ". Back" << endl;

    string ans; int chc;
    do {
        cout << "Product: ";
        cin >> ans;
        chc = stoi(ans);
    } while( !cin.fail() && chc < 1 && chc > idx+1);

    if (chc <= idx) {
        showProductMenu(category, products[chc-1].first);
    } else {
        showBrowseMenu();
    }
}

void
Menu::showProductMenu(string back, int id){
    Item* item = _eshop->getItemById(id);
    _eshop->showProduct(item);
    if (_user->isAdmin()) {
        if (askYesNo("Do you want update the stock of this product?")) {
            int quantity;
            cout << "Quantity: ";
            cin >> quantity;
            _eshop->updateItemStock(item, quantity);
        }
    } else {
        if (askYesNo("Do you want to buy this product?")) {
            int quantity;
            cout << "Quantity: ";
            cin >> quantity;
            _buyer->placeOrder(item, quantity);
        }
    }
    showCategoryMenu(back);
}

void
Menu::showCartMenu()
{
    try {
        set<int> ids = _buyer->showCart();
        int chc;
        string ans;
        Item* item;

        cout << "Actions" << endl;
        cout << "1. Clear Cart" << endl;
        cout << "2. Checkout" << endl;
        cout << "3. Back" << endl;

        do {
            cout << "Please select an action or a product ID to edit your order: ";
            cin >> ans;
            chc = stoi(ans);
            if (ids.contains(chc)) {
                item = _eshop->getItemById(chc);
                break;
            }
        } while (!cin.fail() && chc < 1 && chc > 3);

        switch (chc) {
            case 1:
                _buyer->clearCart();
                break;
            case 2:
                _buyer->checkout();
                break;
            case 3:
                break;
            default:
                pair<Item*, int> item_order;
                try {
                    item_order = _buyer->getItemOrder(item);
                } catch (const EShopError& e) {
                    cout << e.error() << endl;
                    showCartMenu();
                }
                cout << "Editing Item Order: ";
                cout << item_order.first->getName() << " (" << item_order.second << ")" << endl;
                cout << "1. Delete Item Order" << endl;
                cout << "2. Change Item Order" << endl;

                do {
                    cout << "Action: ";
                    cin >> ans;
                    chc = stoi(ans);
                }
                while( (!cin.fail() && chc < 1 && chc > 2) );

                switch (chc) {
                    case 1:
                        _buyer->removeFromOrder(item);
                        break;
                    case 2:
                        do {
                            cout << "Do you want to (1)add or (2)delete: ";
                            cin >> ans;
                            chc = stoi(ans);
                        } while( (!cin.fail() && chc < 1 && chc > 2) );

                        int qnt;
                        do {
                            cout << "Please enter the quantity: ";
                            cin >> ans;
                            qnt = stoi(ans);
                        }
                        while( (!cin.fail() && qnt < 0 && qnt > item_order.second) );

                        if (chc == 1)
                            _buyer->placeOrder(item, qnt);
                        else
                            _buyer->placeOrder(item, -qnt);
                        break;
                }
                showCartMenu();
        }
    } catch (const EShopError& e) {
        cout << e.error() << endl;
    }
    showBuyerMenu();
}

void
Menu::showCheckoutMenu()
{
    _buyer->checkout();
    showBuyerMenu();
}

Menu::~Menu()
{
}

void
Menu::login(string email)
{
    try {
        _buyer = nullptr;
        _owner = nullptr;
        if (email == _eshop->getOwner()->getEmail()) {
            _owner = _eshop->getOwner();
            _user = _owner;
        } else {
            _buyer = _eshop->getBuyerByEmail(email);
            _user = _buyer;
        }
    } catch (const EShopError& e) {
        throw e;
    }
    cout << "Authenticated as: " << _user->getName() << " " << _user->getEmail() << endl;
}

bool
Menu::askYesNo(string message) {
    string ans;
    do {
        cout << message << " [y/n]: ";
        cin >> ans;
    }
    while( !cin.fail() && ans!="y" && ans!="n" );

    if (ans == "y") return true;
    else return false;
}
