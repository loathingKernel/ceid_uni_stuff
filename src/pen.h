#ifndef PEN_H
#define PEN_H

#include "item.h"

using namespace std;

/**
 * \class Pen
 * \brief Class representing a Pen
 */
class Pen final : public Item
{
public:
    /**
     * \brief Constructor for Pen
     *
     * @param tipSize <double>
     * @param color <string>
     * @param stock <int>
     * @param price <double>
     * @param name <string>
     * @param desc <string>
     */
    Pen(double tipSize, string color, int stock, double price, string name, string desc);

    /**
     * \brief Set the tip size of the Pen
     *
     * @param tipSize <double>
     */
    void   setTipSize(double tipSize);
    /**
     * \brief Get the tip size of the Pen
     *
     * @return <double>
     */
    double getTipSize();

    /**
     * \brief Set the color of the Pen
     *
     * @param color <string>
     */
    void   setColor(string color);
    /**
     * \brief Get the color of the Pen
     *
     * @return <string>
     */
    string getColor();

    /**
     * \brief Override of Item::setID()
     *
     * Computes the Pen's item ID by generating the hashes of the class
     * name, the tipSize and the color and then XOR'ing the hashes.
     */
    void   setId() override;
    /**
     * \brief Implements Item::getDetails() for Pen
     *
     * The result is a commaspace-separated string in the order of
     * "tip size, color"
     */
    string getDetails() override;

private:
    double _tipSize;
    string _color;
};

#endif // PEN_H
