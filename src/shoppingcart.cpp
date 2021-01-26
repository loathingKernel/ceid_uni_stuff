#include <vector>
#include "shoppingcart.h"
#include "eshoperror.h"

ShoppingCart::ShoppingCart(Buyer* buyer)
{
    _buyer = buyer;
}

void
ShoppingCart::addItemOrder(Item* item, int quantity)
{
    //TODO: exception
    if (item->getStock() >= quantity) {
        if (_order.find(item) != _order.end())
            changeItemOrderQuantity(item, quantity);
        else
            _order.emplace(item, quantity);
        item->setStock(item->getStock() - quantity);
    } else {
        throw EShopError("Item " + item->getName() + " does not have enough stock.");
    }
}

void
ShoppingCart::removeItemOrder(Item* item)
{
    if (_order.find(item) != _order.end()) {
        item->setStock(item->getStock() + _order[item]);
        _order.erase(item);
    }
}

void
ShoppingCart::changeItemOrderQuantity(Item* item, int quantity)
{
    _order[item] += quantity;
    if (_order[item] <= 0) removeItemOrder(item);
}

pair<Item*, int>
ShoppingCart::getItemOrder(Item* item)
{
    return make_pair(item, _order[item]);
}

double
ShoppingCart::calculateNet()
{
    double value = 0;
    for(auto o: _order) value += o.first->getPrice()*o.second;
    return value;
}

double
ShoppingCart::calculateCourier()
{
    if (_buyer->getCategory() == Buyer::Gold) return 0;
    else {
        double value = calculateNet();
        if (_buyer->getCategory() == Buyer::Silver) return value*0.01;
        else return (value*0.02 >= 3 ? value*0.02 : 3);
    }
}

set<int>
ShoppingCart::showCart()
{
    set<int> ids;
    if (_order.empty()) throw EShopError("Shopping cart is empty.");
    for (auto o: _order) {
        ids.insert(o.first->getId());
        cout << o.first->getId() << ", " << o.first->getName() << ", " << o.second << ", "<< o.first->getPrice()*o.second << endl;
    }
    cout << "Order value: " << calculateNet() << endl;
    cout << "Courier value: " << calculateCourier() << endl;
    return ids;
}

void
ShoppingCart::clearCart()
{
    for (auto o: _order)
        o.first->setStock(o.first->getStock() + o.second);
    _order.clear();
}

void
ShoppingCart::checkout()
{
    showCart();

    string ans;
    do {
        cout << "Do you want to continue the checkout? [y/n]: ";
        cin >> ans;
    }
    while( (!cin.fail() && ans!="y" && ans!="n") );

    if (ans == "y") {
        _buyer->awardBonus(calculateNet());
        _order.clear();
    }
}

