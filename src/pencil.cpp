#include <typeinfo>
#include "pencil.h"

Pencil::Pencil(double tipSize, Pencil::Type type, int stock, double price, string name, string desc) : Item(stock, price, name, desc)
{
    setTipSize(tipSize);
    setType(type);
    setCategory(typeid(*this).name());
    setId();
}

void
Pencil::setId()
{
    size_t h_obj = hash<string>{}(typeid(*this).name());
    size_t h_typ = hash<string>{}(_typeMap[_type]);
    size_t h_tip = hash<double>{}(_tipSize);
    Item::setId(h_obj ^ ((h_typ ^ (h_tip << 1)) << 1));
}

string
Pencil::getDetails()
{
    string ret;
    ret += to_string(_tipSize);
    ret += ", ";
    ret += _typeMap[_type];
    ret += "\n";
    return ret;
}

void
Pencil::setTipSize(double size) { _tipSize = size; }
double
Pencil::getTipSize() { return _tipSize; }

void
Pencil::setType(Type type) { _type = type; }
Pencil::Type
Pencil::getType() { return _type; }
