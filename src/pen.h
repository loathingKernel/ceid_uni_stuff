#ifndef PEN_H
#define PEN_H

#include "item.h"

using namespace std;

class Pen final : public Item
{
public:
    /**
     * @param tipSize double
     * @param color string
     * @param stock int
     * @param price double
     * @param name string
     * @param desc string
     */
    Pen(double, string, int, double, string, string);

    void   setTipSize(double);
    double getTipSize();

    void   setColor(string);
    string getColor();

    void   setId() override;
    string getDetails() override;

private:
    double _tipSize;
    string _color;
};

#endif // PEN_H
