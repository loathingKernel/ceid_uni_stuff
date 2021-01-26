#include "item.h"

Item::Item(int stock, double price, string name, string desc)
{
    setStock(stock);
    setPrice(price);
    setName(name);
    setDescription(desc);
}

Item::~Item()
{
}

string Item::getBasicInfo()
{
    string ret;
    ret += to_string(_id);
    ret += ", ";
    ret += _name;
    ret += ", ";
    ret += to_string(_price);
    ret += ", ";
    ret += to_string(_stock);
    ret += ", ";
    ret += _desc;
    ret += ", ";
    return ret;
}

Item::operator std::string ()
{
    return getBasicInfo() + getDetails();
}

ostream&
operator<<(ostream& os, Item& item)
{
    os << static_cast<std::string>(item);
    return os;
}

bool
Item::operator==(const Item& other)
{
    return this->_id == other._id;
}

void
Item::setCategory(string category) { _category = category.substr(1); }
string
Item::getCategory() { return _category; }

void
Item::setId(size_t id) { _id = id % 10000; }
size_t
Item::getId() { return _id; }

void
Item::setStock(int stock) { _stock = stock; }
int
Item::getStock() { return _stock; }

void
Item::setPrice(double price) { _price = price; }
double
Item::getPrice() { return _price; }

void
Item::setName(string name) { _name = name; }
string
Item::getName() { return _name; }

void
Item::setDescription(std::string desc) { _desc = desc; }
string
Item::getDescription() { return _desc; }

