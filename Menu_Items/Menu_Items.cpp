#include "Menu_Items.hpp"
#include <iostream>

// Class for IDs
int ID::next_id = 1;
ID::ID() : id(next_id++) {}
ID::ID(int id) : id(id) {}
int ID::getID() const {
    return id;
}

// Class for Products
Product::Product(const std::string& name, float price) : name(name), price(price), ID() {}
std::string Product::getName() const {
    return name;
}
float Product::getPrice() const {
    return price;
}

// Class for CarryOut Products
CarryoutProduct::CarryoutProduct(const std::string& name, float price, float price_carryout, bool carryout)
    : Product(name, price), price_carryout(price_carryout), carryout(carryout) {}
float CarryoutProduct::getPrice(bool carryout) const {
    return carryout ? price_carryout : Product::getPrice();
}
bool CarryoutProduct::isCarryout() const {
    return carryout;
}

// Class for dishes
Dish::Dish(const std::string& name, float price, float price_carryout, bool carryout)
    : CarryoutProduct(name, price, price_carryout, carryout) {}

// Exceptional class for wings
Wings::Wings(const std::string& name, float price_serve, float price_carryout, const std::string& taste, bool carryout)
    : Dish(name, price_serve, price_carryout, carryout), taste(taste) {}
std::string Wings::getTaste() const {
    return taste;
}

// Class for Extras
Extra::Extra(const std::string& name, float price)
    : Product(name, price) {}

// Class for Beverages
Beverage::Beverage(const std::string& name, float price)
    : Product(name, price) {}

// Herency for juices and milkshakes
JuiceandMilkshake::JuiceandMilkshake(const std::string& name, float price, const std::string& flavor)
    : Beverage(name, price), flavor(flavor) {}
std::string JuiceandMilkshake::getFlavor() const {
    return flavor;
}

// Herency for sodas
Soda::Soda(const std::string& name, float price, float volume)
    : Beverage(name, price), volume(volume) {}
float Soda::getVolume() const {
    return volume;
}

// Class for orders (pendiente de implementación)
// class Order {
// }