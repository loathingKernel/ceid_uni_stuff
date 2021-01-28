#ifndef ESHOP_H
#define ESHOP_H

#include <iostream>
#include <vector>
#include "item.h"
#include "owner.h"
#include "buyer.h"

using namespace std;

/**
 * \class EShop
 * \brief Class implementing the e-shop.
 *
 * This class implements the e-shop related functionality.
 * There are two ways this class can be instantiated, either by passing the name
 * of the e-shop, in which case we have to specify an owner later on or by passing
 * the name and the email of the owner to the constructor. It also holds the
 * manipulates the Items and the Buyers of the EShop.
 */
class EShop
{
public:
    /**
     * \brief Constructor of EShop
     *
     * @param name <string> The name of the e-shop
     */
    explicit EShop(string name);
    /**
     * \brief Constructor of EShop
     *
     * @param name <string> The name of the e-shop
     * @param owner <string> The name of the owner
     * @param email <string> The email of the owner
     */
    EShop(string name, string owner, string email);
    /**
     * \brief The destructor of e-shop
     *
     * We require this to destroy any Item or Buyer objects
     * created during execution
     */
    ~EShop();

    /**
     * \brief Get the name of the e-shop
     */
    string getName();
    /**
     * \brief Get the owner
     */
    Owner* getOwner();

    /**
     * \brief Add an Item to the e-shop
     *
     * Checks if the Item already exists, if it does, throws and exception
     */
    void addItem(Item*);
    /**
     * \brief Remove an Item from the eshop if it exists
     */
    void removeItem(Item*);
    /**
     * \brief Return an Item reference if the Item's ID is found in the e-shop
     */
    Item* getItemById(size_t id);

    /**
     * \brief Add a Buyer to the e-shop
     *
     * Checks if the Buyer already exists, if it does, throws and exception
     */
    void addBuyer(Buyer*);
    /**
     * \brief Remove a Buyer from the eshop if it exists and clears their cart
     */
    void removeBuyer(Buyer*);
    /**
     * \brief Return a Buyer reference if the Buyer's email is found in the e-shop
     */
    Buyer* getBuyerByEmail(string email);

    /**
     * \brief Update an Item's stock.
     */
    void updateItemStock(Item*, int);
    /**
     * \brief Get the categories of Items that exist in the e-shop
     *
     * Returns a vector of pairs consisting of the categories names and the
     * number of products in each category.
     *
     * @return <vector<pair<string, int>>>
     */
    vector<pair<string, int>> getCategories();
    /**
     * \brief Get the Items in a specific category
     *
     * Returns a vector of pairs consisting of the Item IDs and the name of
     * each product
     *
     * @return <vector<pair<int, string>>>
     */
    vector<pair<int, string>> getProductsInCategory(string);
    /**
     * \brief Shows the details of the specified product
     */
    void showProduct(Item*);
    /**
     * \brief Prints the status of the Buyers
     *
     * Also returns a vector of vectors of strings with the information for each
     * buyer
     *
     * @return <vector<vector<string>>>
     */
    vector<vector<string>> checkStatus();

private:
    /// \brief Sets the name of the owner.
    void setOwner(string name, string email);

    string _name;
    Owner* _owner = nullptr;
    vector<Buyer*> _buyers;
    vector<Item*>  _items;
};

#endif // ESHOP_H
