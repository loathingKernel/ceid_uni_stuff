#include <typeinfo>
#include "pen.h"

Pen::Pen(double tipSize, string color, int stock, double price, string name, string desc) : Item(stock, price, name, desc)
{
    setTipSize(tipSize);
    setColor(color);
    setCategory(typeid(*this).name());
    setId();
}

void
Pen::setId()
{
    size_t h_obj = hash<string>{}(typeid(*this).name());
    size_t h_clr = hash<string>{}(_color);
    size_t h_tip = hash<double>{}(_tipSize);
    Item::setId(h_obj ^ ((h_clr ^ (h_tip << 1)) << 1));
}

string
Pen::getDetails()
{
    string ret;
    ret += to_string(_tipSize);
    ret += ", ";
    ret += _color;
    ret += "\n";
    return ret;
}

void
Pen::setTipSize(double size) { _tipSize = size; }
double
Pen::getTipSize() { return _tipSize; }

void
Pen::setColor(string color) { _color = color; }
string
Pen::getColor() { return _color; }
