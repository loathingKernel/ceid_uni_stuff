#ifndef PENCIL_H
#define PENCIL_H

#include <map>
#include "item.h"

/**
 * \class Pencil
 * \brief Class representing a Pencil
 */
class Pencil final : public Item
{
public:

    /**
     * \brief Enumaration of Pencil types
     */
    enum Type {
        H,
        B,
        HB,
    };

    /**
     * \brief Constructor for Pencil
     *
     * @param tipSize <double>
     * @param type <Pencil::Type>
     * @param stock <int>
     * @param price <double>
     * @param name <string>
     * @param desc <string>
     */
    Pencil(double tipSize, Type type, int stock, double price, string name, string desc);

    /**
     * \brief Set the tip size of the Pencil
     *
     * @param tipSize <double>
     */
    void   setTipSize(double tipSize);
    /**
     * \brief Get the tip size of the Pencil
     *
     * @return <double>
     */
    double getTipSize();

    /**
     * \brief Set the type of the Pencil
     *
     * @param color <Pencil::Type>
     */
    void setType(Type type);
    /**
     * \brief Get the color of the Pen
     *
     * @return <Pencil::Type>
     */
    Type getType();

    /**
     * \brief Override of Item::setID()
     *
     * Computes the Pencil's item ID by generating the hashes of the class
     * name, the tip size and the type and then XOR'ing the hashes.
     */
    void   setId() override;
    /**
     * \brief Implements Item::getDetails() for Pen
     *
     * The result is a commaspace-separated string in the order of
     * "tip size, type"
     */
    string getDetails() override;

private:
    double _tipSize;
    Type _type;
    /// Map of Pencil::Type to string representations
    map<Type, string> _typeMap { {H, "H"}, { B, "B" }, {HB, "HB" } };
};

#endif // PENCIL_H
