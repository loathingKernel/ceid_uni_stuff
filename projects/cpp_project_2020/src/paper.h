#ifndef PAPER_H
#define PAPER_H

#include "item.h"

using namespace std;

/**
 * \class Paper
 * \brief Class representing a Paper
 */
class Paper final : public Item
{
public:
    /**
     * \brief Constructor for Paper
     *
     * @param int <pages>
     * @param int <weight>
     * @param int <stock>
     * @param double <price>
     * @param string <name>
     * @param string <desc>
     */
    Paper(int pages, int weight, int stock, double price, string name, string desc);

    /**
     * \brief Set the pages of Paper
     *
     * @param pages <int>
     */
    void setPages(int pages);
    /**
     * \brief Get the pages of Paper
     *
     * @return <int>
     */
    int  getPages();

    /**
     * \brief Set the weight of Paper
     *
     * @param subjects <int>
     */
    void setWeight(int);
    /**
     * \brief Get the weight of Paper
     *
     * @return <int>
     */
    int  getWeight();

    /**
     * \brief Override of Item::setID()
     *
     * Computes the Paper's item ID by generating the hashes of the class
     * name, the number of pages and the weight and then XOR'ing the hashes.
     */
    void   setId();
    /**
     * \brief Implements Item::getDetails() for Paper
     *
     * The result is a commaspace-separated string in the order of
     * "pages, weight"
     */
    string getDetails();

private:
    int _pages;
    int _weight;
};

#endif // PAPER_H
