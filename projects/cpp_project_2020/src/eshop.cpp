#include <typeinfo>
#include <algorithm>
#include <set>
#include "eshop.h"
#include "eshoperror.h"

EShop::EShop(string name)
{
    _name = name;
    _owner = nullptr;
}

EShop::EShop(string name, string owner, string email) : EShop(name)
{
    setOwner(owner, email);
}

EShop::~EShop()
{
    for(auto i: _items) delete i;
    for(auto b: _buyers) delete b;
    delete _owner;
}

Owner*
EShop::getOwner()
{
    return _owner;
}


void
EShop::setOwner(string name, string email)
{
    if (_owner != nullptr)
        throw EShopError("Shop already has an owner");
    _owner = new Owner(name, email);
}

void
EShop::addItem(Item* item)
{
    //TODO: exception
    if (!_items.empty()) {
        for(auto i: _items) {
            if (*i == *item) {
                throw EShopError("Item " + item->getName() + " already exists.");
            }
        }
    }
    _items.push_back(item);
}

void
EShop::removeItem(Item* item)
{
    for(auto i = _items.begin(); i <= _items.end(); ++i) {
        if (**i == *item) {
            delete *i;
            _items.erase(i);
            break;
        }
    }
}

Item*
EShop::getItemById(size_t id)
{
    for(auto i: _items) if (i->getId() == id) return i;
    throw EShopError("Item with ID " + to_string(id) + " does not exist.");
    return nullptr;
}

void
EShop::addBuyer(Buyer* buyer)
{
    //TODO: exception
    for(auto b: _buyers) {
        if (*b == *buyer) {
            throw EShopError("Buyer " + buyer->getName() + " already exists.");
        }
    }
    _buyers.push_back(buyer);
}

void
EShop::removeBuyer(Buyer* buyer)
{
    for(auto b = _buyers.begin(); b <= _buyers.end(); ++b ){
        if (**b == *buyer) {
            (*b)->clearCart();
            delete *b;
            _buyers.erase(b);
            break;
        }
    }
}

Buyer*
EShop::getBuyerByEmail(string email)
{
    for(auto b: _buyers) if (b->getEmail() == email) return b;
    throw EShopError("Buyer with email \'" + email + "\' does not exist.");
    return nullptr;
}

void
EShop::updateItemStock(Item* item, int delta)
{
    item->setStock(item->getStock() + delta);
}

void
EShop::showProduct(Item* item)
{
    cout << *item;
}

vector<pair<string, int>>
EShop::getCategories()
{
    map<string, int> categories;
    for (auto i: _items) {
        string category = i->getCategory();
        if (categories.find(category) != categories.end())
            categories[category]++;
        else categories.emplace(category, 1);
    }
    vector<pair<string, int>> vectored;
    for (auto c: categories)
        vectored.push_back(make_pair(c.first, c.second));
    return vectored;
}

vector<pair<int, string>>
EShop::getProductsInCategory(string category)
{
    vector<pair<int, string>> products;
    for(auto i: _items)
        if (i->getCategory() == category)
            products.push_back(make_pair(i->getId(), i->getName()));
    return products;
}

vector<vector<string>>
EShop::checkStatus()
{
    vector<vector<string>> buyers;
    for (auto b: _buyers) {
        vector<string> info;
        info.push_back(b->getEmail());
        info.push_back(b->getName());
        info.push_back(b->getCategoryName());
        info.push_back(to_string(b->getBonus()));
        buyers.push_back(info);
    }
    return buyers;
}

string
EShop::getName()
{
    return _name;
}
