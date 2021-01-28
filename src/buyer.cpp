#include "buyer.h"
#include "shoppingcart.h"
#include "eshoperror.h"

Buyer::Buyer(string name, string email) : User(name, email)
{
    _bonus = 0;
    _category = Bronze;
    _cart = new ShoppingCart(this);
}

void
Buyer::awardBonus(double orderValue)
{
    setBonus(orderValue);
    setCategory();
}

void
Buyer::placeOrder(Item* item, int quantity)
{
    try {
        _cart->addItemOrder(item, quantity);
    } catch (const EShopError& e){
        cout << e.error() << endl;
        cout << "Available quantity is " + to_string(item->getStock()) << endl;
        string ans;
        do {
            cout << "Do you want to add the available quantity to the cart? [y/n]: ";
            cin >> ans;
        }
        while( !cin.fail() && ans!="y" && ans!="n" );

        if (ans == "y")
            _cart->addItemOrder(item, item->getStock());
    }
}

void
Buyer::removeFromOrder(Item* item)
{
    _cart->removeItemOrder(item);
}

void
Buyer::checkout()
{
    _cart->checkout();
}

set<int>
Buyer::showCart()
{
    try {
        return _cart->showCart();
    } catch (const EShopError& e) {
        throw e;
    }
}

pair<Item*, int>
Buyer::getItemOrder(Item* item)
{
    try {
        return _cart->getItemOrder(item);
    } catch (const EShopError& e) {
        throw e;
    }
}

void
Buyer::clearCart()
{
    _cart->clearCart();
}


bool
Buyer::operator==(Buyer& other)
{
    return (this->getName() == other.getName()) && (this->getEmail() == other.getEmail());
}

void
Buyer::setBonus(double value) {
    _bonus = static_cast<int>(value*0.1);
}

int
Buyer::getBonus() { return _bonus; }

void
Buyer::setCategory() {
    for(auto c: _categories)
        if (_bonus > _categoryScore[c]) _category = c;
}

Buyer::Category
Buyer::getCategory() { return _category; }

string
Buyer::getCategoryName() { return _categoryString[_category]; }

bool
Buyer::isAdmin() { return false; }
