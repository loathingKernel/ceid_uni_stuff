#ifndef ESHOP_H
#define ESHOP_H

#include <iostream>
#include <vector>
#include "item.h"
#include "owner.h"
#include "buyer.h"

class EShop
{
public:
    explicit EShop(string name);
    EShop(string name, string owner, string email);
    ~EShop();

    string getName();
    Owner* getOwner();

    void addItem(Item*);
    void removeItem(Item*);
    Item* getItemById(size_t id);

    void addBuyer(Buyer*);
    void removeBuyer(Buyer*);
    Buyer* getBuyerByEmail(string email);

    void updateItemStock(Item*, int);
    vector<pair<string, int>> getCategories();
    vector<pair<int, string>> getProductsInCategory(string);
    void showProduct(Item*);
    vector<vector<string>> checkStatus();

private:
    void setOwner(string name, string email);

    string _name;
    Owner* _owner = nullptr;
    vector<Buyer*> _buyers;
    vector<Item*>  _items;
};

#endif // ESHOP_H
