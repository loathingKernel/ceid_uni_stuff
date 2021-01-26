#ifndef SHOPPINGCART_H
#define SHOPPINGCART_H

#include <set>
#include <map>
#include "item.h"
#include "buyer.h"

using namespace std;

class ShoppingCart
{
public:
    explicit ShoppingCart(Buyer*);

    void addItemOrder(Item*, int);
    void removeItemOrder(Item*);
    void changeItemOrderQuantity(Item*, int);
    pair<Item*, int> getItemOrder(Item*);

    set<int> showCart();
    void clearCart();

    void checkout();

    double calculateNet();
    double calculateCourier();

private:
    map<Item*, int> _order;
    Buyer* _buyer;
};

#endif // SHOPPINGCART_H
