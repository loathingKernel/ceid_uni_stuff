/**
 * \mainpage Ceid Cpp Project 2020
 *
 * \author Tsampas Stilianos (1039884) (4104)
 * \author Siamoglou Charalambos (1041601) (5890)
 *
 * The source code can also be found <a href="https://github.com/loathingkernel/cpp_project_eshop">here</a>.
 *
 * \section intro_sec Introduction
 *
 * This is an implementation of the project for the Objective Programming course.
 * The goal is to create an EShop in the C++ programming language
 *
 * \section design_sec Design
 *
 * The design was based around the
 *
 */

#include <iostream>
#include "menu.h"

int main(int argc, char **argv) {
    EShop eshop = EShop("EShop", "Owner", "owner@eshop.com");

    try {
        eshop.addItem(new Pencil(0.2, Pencil::B, 10, 3.1, "Yellow Pencil Name", "Yellow Pencil Desc"));
        eshop.addItem(new Pencil(0.3, Pencil::H, 15, 2.1, "Orange Pencil Name", "Orange Pencil Desc"));
        eshop.addItem(new Pencil(0.4, Pencil::HB, 20, 2.6, "Purple Pencil Name", "Purple Pencil Desc"));
        eshop.addItem(new Pencil(0.4, Pencil::HB, 10, 3.1, "Purple Pencil Name", "Purple Pencil Desc"));
    } catch(const EShopError& e) {
        cout << e.error() << endl;
    }

    try {
        eshop.addItem(new Pen(0.2, "yellow", 10, 3.1, "Yellow Pen Name", "Yellow Pen Desc"));
        eshop.addItem(new Pen(0.3, "orange", 15, 2.1, "Orange Pen Name", "Orange Pen Desc"));
        eshop.addItem(new Pen(0.4, "purple", 20, 2.6, "Purple Pen Name", "Purple Pen Desc"));
        eshop.addItem(new Pen(0.4, "purple", 10, 3.1, "Purple Pen Name", "Purple Pen Desc"));
    } catch(const EShopError& e) {
        cout << e.error() << endl;
    }

    try {
        eshop.addItem(new Notebook(2, 15, 10.5, "2 Subject Notebook", "Fancy 2 Subject Notebook"));
        eshop.addItem(new Notebook(3, 15, 11.5, "3 Subject Notebook", "Fancy 3 Subject Notebook"));
        eshop.addItem(new Notebook(4, 15, 12.5, "4 Subject Notebook", "Fancy 4 Subject Notebook"));
        eshop.addItem(new Notebook(4, 15, 12.5, "4 Subject Notebook", "Fancy 4 Subject Notebook"));
    } catch(const EShopError& e) {
        cout << e.error() << endl;
    }

    try {
        eshop.addItem(new Paper(100, 2, 15, 10.5, "100 Pages", "Fancy 100"));
        eshop.addItem(new Paper(200, 3, 15, 11.5, "200 Pages", "Fancy 200"));
        eshop.addItem(new Paper(300, 4, 15, 12.5, "300 Pages", "Fancy 300"));
        eshop.addItem(new Paper(300, 4, 15, 12.5, "300 Pages", "Fancy 300"));
    } catch(const EShopError& e) {
        cout << e.error() << endl;
    }

    try {
        eshop.showProduct(eshop.getItemById(6091));
        eshop.showProduct(eshop.getItemById(6092));
        eshop.removeItem(eshop.getItemById(6091));
        eshop.removeItem(eshop.getItemById(6092));
    } catch (const EShopError& e) {
        cout << e.error() << endl;
    }

    try {
        eshop.removeItem(eshop.getItemById(6091));
        eshop.removeItem(eshop.getItemById(6092));
    } catch (const EShopError& e) {
        cout << e.error() << endl;
    }

    try {
        eshop.addBuyer(new Buyer("buyer_a", "buyer_a@isp.org"));
        eshop.addBuyer(new Buyer("buyer_b", "buyer_b@isp.org"));
        eshop.addBuyer(new Buyer("buyer_c", "buyer_c@isp.org"));
        eshop.addBuyer(new Buyer("buyer_b", "buyer_b@isp.org"));
    } catch(const EShopError& e) {
        cout << e.error() << endl;
    }

    try {
        eshop.removeBuyer(eshop.getBuyerByEmail("buyer_c@isp.org"));
    } catch(const EShopError& e) {
        cout << e.error() << endl;
    }

    Buyer* buyer = eshop.getBuyerByEmail("buyer_a@isp.org");
    try {
        buyer->placeOrder(eshop.getItemById(7093), 3);
        buyer->placeOrder(eshop.getItemById(7093), 3);
        buyer->placeOrder(eshop.getItemById(7093), 3);
        buyer->placeOrder(eshop.getItemById(7093), 13);
    } catch(const EShopError& e) {
        cout << e.error() << endl;
    }

    Menu menu = Menu(&eshop);
    return 0;
}
