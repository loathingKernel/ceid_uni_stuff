#ifndef PAPER_H
#define PAPER_H

#include "item.h"

class Paper final : public Item
{
public:
    /**
     * @param int pages
     * @param int weight
     * @param int stock
     * @param double price
     * @param string name
     * @param string desc
     */
    Paper(int, int, int, double, string, string);

    void setPages(int);
    int  getPages();

    void setWeight(int);
    int  getWeight();

    void   setId();
    string getDetails();

private:
    int _pages;
    int _weight;
};

#endif // PAPER_H
