#ifndef BUYER_H
#define BUYER_H

#include <set>
#include <map>
#include "item.h"
#include "user.h"

// Forward declaration of ShoppingCart
class ShoppingCart;

using namespace std;

/**
 * \class Buyer
 * \brief Specialization of User. Describes a Buyer
 *
 * Derivative class to specialize a User.
 * Implements Buyer related functionality.
 */
class Buyer final : public  User
{
public:
    /**
     * \brief Constructor of Buyer
     *
     * @param name User's name
     * @param email User's login email
     */
    Buyer(string name, string email);

    /**
     * \brief Disable the copy constructor for buyer
     */
    Buyer(const Buyer&) = delete;

    /**
     * \enum Category
     * \brief Buyer _categories
     *
     * Enumeration of the different Buyer status categories.
     * Used to determine the perks of a Buyer.
     */
    enum Category {
        Bronze,
        Silver,
        Gold,
    };

    /**
     * \brief Impementation of isAdmin() of User
     *
     * @param none
     * @return bool Always false
     */
    bool isAdmin();
    /**
     * \brief Set the buyer's bonus based on the cost of the order
     *
     * @param orderValue double The value of the order
     */
    void awardBonus(double orderValue);
    /**
     * \brief Add an item to the cart with the specified quantity
     *
     * This function checks if the the cart already contains the item.
     * If it does, it updates the quantity in the cart. Also used to remove
     * a quantity using negative values.
     *
     * @param item Item* The item to add to the cart
     * @param quantity int The selected quantity
     */
    void placeOrder(Item* item, int quantity);
    /**
     * \brief Removes an item from the cart completely
     *
     * @param item Item* The item to remove
     */
    void removeFromOrder(Item* item);
    /**
     * \brief Wrapper to ShoppingCart::checkout()
     */
    void checkout();
    /**
     * \brief Wrapper to ShoppingCart::showCart()
     *
     * @return Returns a set of the IDs of the items in the cart
     */
    set<int> showCart();
    /**
     * \brief Wrapper to ShoppingCart::getItemOrder()
     *
     * @return Returns a pair containing an item pointer
     *         and the quantity int in the cart
     */
    pair<Item*, int> getItemOrder(Item*);
    /**
     * \brief Wrapper to ShoppingCart::clearCart()
     */
    void clearCart();

    /**
     * \brief Comparission operator between two Buyers
     *
     * @return bool True if they have the same name and email
     *              otherwise false
     */
    bool operator==(Buyer&);
    /**
     * \brief Disable the copy operator for buyer
     */
    Buyer& operator=(const Buyer&) = delete;

    /**
     * \brief Get the Buyer's bonus
     */
    int      getBonus();
    /**
     * \brief Get the Buyer's category
     */
    Category getCategory();
    /**
     * \brief Get the Buyer's category as string
     */
    string   getCategoryName();

private:
    /**
     * \brief Sets a buyer's bonus based on the cost
     */
    void setBonus(double);
    /**
     * \brief Sets a buyer's category based on _bonus
     */
    void setCategory();

    int _bonus;
    Category _category;
    /// \brief Map of the categories and their respective lower end scores
    map<Category, int> _categoryScore { {Bronze, 0}, {Silver, 100}, {Gold, 200} };
    /// \brief Map of the categories and their string representations
    map<Category, string> _categoryString { {Bronze, "Bronze"}, {Silver, "Silver"}, {Gold, "Gold"} };
    /// \brief I just needed an iterator over the categories, so yeah...
    static constexpr initializer_list<Category> _categories = {Bronze, Silver, Gold};
    /// \brief Pointer to the user's cart (forward declarations and such)
    ShoppingCart* _cart;
};

#endif // BUYER_H
