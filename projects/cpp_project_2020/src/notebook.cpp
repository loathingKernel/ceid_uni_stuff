#include <typeinfo>
#include "notebook.h"

Notebook::Notebook(int subjects, int stock, double price, string name, string desc) : Item(stock, price, name, desc)
{
    setSubjects(subjects);
    setCategory(typeid(*this).name());
    setId();
}

string
Notebook::getDetails()
{
    string ret;
    ret += to_string(_subjects);
    ret += "\n";
    return ret;
}

void
Notebook::setId()
{
    size_t h_obj = hash<string>{}(typeid(*this).name());
    size_t h_sub = hash<int>{}(_subjects);
    Item::setId(h_obj ^ (h_sub << 1));
}

void
Notebook::setSubjects(int subjects) { _subjects = subjects; }
int
Notebook::getSubjects() { return _subjects; }
