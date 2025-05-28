#pragma once
#include <iostream>
// General Class for IDs
class ID {
    private:
        static int next_id;
        int id;
    public:
        ID();
        ID(int id);
        int getID() const;
};


// Class for Products

class Product : public ID {
private:
    std::string name;
    float price;
public:
    Product(const std::string& name, float price);
    std::string getName() const;
    virtual float getPrice(bool carryout = false) const;
    virtual ~Product() = default; 

};

class CarryoutProduct : public Product {
private:
    float price_carryout;
    bool carryout;
public:
    CarryoutProduct(const std::string& name, float price, float price_carryout, bool carryout=false);
    float getPrice(bool carryout = false) const override;
    bool isCarryout() const;
};

// Class for dishes

class Dish : public CarryoutProduct {
    public:
        Dish(const std::string& name, float price, float price_carryout, bool carryout=false);
};


// Exceptional class for wings
class Wings : public Dish {
    private: 
        std::string taste;
    public:
        Wings(const std::string& name, float price_serve, float price_carryout, const std::string& taste, bool carryout = false); 
        std::string getTaste() const;
};

// Class for Extras 
class Extra : public Product {
    public:
        Extra(const std::string& name, float price); 
};


// Class for Beverages
class Beverage : public Product {
    public:
        Beverage(const std::string& name, float price);
};


// Herency for juices and milkshakes
class JuiceandMilkshake : public Beverage {
    private:
        std::string flavor;
    public:
        JuiceandMilkshake(const std::string& name, float price, const std::string& flavor); 
        std::string getFlavor() const;
};


// Herency for sodas
class Soda : public Beverage {
    private:
        float volume;
    public:
        Soda(const std::string& name, float price, float volume); 
        float getVolume() const;
};
