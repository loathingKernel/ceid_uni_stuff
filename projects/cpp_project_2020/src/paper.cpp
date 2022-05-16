#include <typeinfo>
#include "paper.h"


Paper::Paper(int pages, int weight, int stock, double price, string name, string desc) : Item(stock, price, name, desc)
{
    setPages(pages);
    setWeight(weight);
    setCategory(typeid(*this).name());
    setId();
}

string Paper::getDetails()
{
    string ret;
    ret += to_string(_pages);
    ret += ", ";
    ret += to_string(_weight);
    ret += "\n";
    return ret;
}

void Paper::setId()
{
    size_t h_obj = hash<string>{}(typeid(*this).name());
    size_t h_pgs = hash<int>{}(_pages);
    size_t h_wgt = hash<int>{}(_weight);
    Item::setId(h_obj ^ ((h_pgs ^ (h_wgt << 1)) << 1));
}

void
Paper::setPages(int pages) { _pages = pages; }
int
Paper::getPages() { return _pages; }

void
Paper::setWeight(int weight) { _weight = weight; }
int
Paper::getWeight() { return _weight; }
