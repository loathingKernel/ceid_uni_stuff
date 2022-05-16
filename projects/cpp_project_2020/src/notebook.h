#ifndef NOTEBOOK_H
#define NOTEBOOK_H

#include "item.h"

using namespace std;

/**
 * \class Notebook
 * \brief Class representing a Notebook
 */
class Notebook final : public Item
{
public:
    /**
     * \brief Constructor for Notebook
     *
     * @param subjects <int>
     * @param stock <int>
     * @param price <double>
     * @param name <string>
     * @param desc <string>
     */
    Notebook(int subjects, int stock, double price, string name, string desc);

    /**
     * \brief Set the number of subjects of the notebook
     *
     * @param subjects <int>
     */
    void setSubjects(int subjects);
    /**
     * \brief Get the Notebook's number of subjects
     *
     * @return <int>
     */
    int  getSubjects();

    /**
     * \brief Override of Item::setID()
     *
     * Computes the Notebook's item id by generating the hashes of the class
     * name and the number of subjects and then XOR'ing the hashes.
     */
    void   setId() override;
    /**
     * \brief Implements Item::getDetails() for Notebook
     *
     * The result is a string of the number of subjects
     */
    string getDetails() override;

private:
    int _subjects;
};

#endif // NOTEBOOK_H
