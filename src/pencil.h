#ifndef PENCIL_H
#define PENCIL_H

#include <map>
#include "item.h"

class Pencil final : public Item
{
public:

    enum Type {
        H,
        B,
        HB,
    };

    Pencil(double, Type);
    Pencil(double, Type, int, double, string, string);

    void   setTipSize(double);
    double getTipSize();

    void setType(Type);
    Type getType();

    void   setId() override;
    string getDetails() override;

private:
    double _tipSize;
    Type _type;
    map<Type, string> _typeMap { {H, "H"}, { B, "B" }, {HB, "HB" } };
};

#endif // PENCIL_H
