#ifndef SHOPPINGCART_H
#define SHOPPINGCART_H

#include <set>
#include <map>
#include "item.h"
#include "buyer.h"

using namespace std;

/**
 * \class ShoppingCart
 * \brief Class implementing the shopping cart.
 *
 * This class implements the shopping cart related functionality.
 * This class is instantiated for each buyer, and requires to access functionality
 * related to that specific buyer. To satisfy that need we pass a pointer to the
 * constructing buyer during instantiation for later use. The cart is represented
 * as a map between the Item and an integer representing the quantity of Item in
 * the cart.
 */
class ShoppingCart
{
public:
    /**
     * \brief Constructor for ShoppingCart
     *
     * @param buyer <Buyer*> Pointer to the buyer owning this cart
     */
    explicit ShoppingCart(Buyer* buyer);

    /**
     * \brief Add quantity of an Item to the cart
     *
     * This function also check if the Item is already in the cart,
     * if it is it updates the quantity by adding the requested quantity.
     * It also checks if there is enough stock, if it doesn't, it throws and
     * EShopError exception to be caught by the caller.
     *
     * @param item <Item*> Reference to an item in the eshop
     * @param quantity <int> The quantity of the item
     */
    void addItemOrder(Item* item, int quantity);
    /**
     * \brief Remove an item from the cart completely
     *
     * Also updates the cart.
     *
     * @param item <Item*> Reference to the Item to be removed.
     */
    void removeItemOrder(Item* item);
    /**
     * \brief Changes the quantity of an item in the cart.
     *
     * Also checks of the resulting quantity is below zero and if it is
     * it removes the Item from the cart.
     *
     * @param item <Item*> Reference to the Item to be removed.
     * @param quantity <int> Quantity to remove.
     */
    void changeItemOrderQuantity(Item* item, int quantity);
    /**
     * \brief Get the order information of an item in the cart
     *
     * Returns a pair of Item reference and quantity of the item specified
     * if the item is in the cart.
     *
     * @param item <Item*> Reference to the Item to be returned.
     * @return <pair<Item*,int>> A pair from the cart.
     */
    pair<Item*, int> getItemOrder(Item*);

    /**
     * \brief Show the contents of the cart
     *
     * This function prints the contents of the cart and returns
     * a set of Item IDs of the items in the cart for erroneous input
     * in the menu. It also prints the value of the order and the cost of
     * the courier.
     *
     * @return <set<int>> A set of Item IDs in the cart.
     */
    set<int> showCart();
    /**
     * \brief Clears the cart.
     *
     * It doesn't call removeItemOrder because of the use of an iterator.
     */
    void clearCart();

    /**
     * \brief Performs the checkout
     *
     * Performs the checkout, asks the user for confirmation. If it is positive
     * it clears the cart and awards the bonus to the user.
     */
    void checkout();

    /**
     * \brief Calculates the cost of the order
     */
    double calculateNet();
    /**
     * \brief Calculates the cost of the courier
     *
     * It also takes into account the category of the buyer.
     */
    double calculateCourier();

private:
    /// The cart represented as a map.
    map<Item*, int> _order;
    /// The Buyer this cart belongs to.
    Buyer* _buyer;
};

#endif // SHOPPINGCART_H
