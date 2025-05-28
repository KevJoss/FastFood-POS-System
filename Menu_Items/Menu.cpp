#include "Menu.hpp"       
#include "Menu_Items.hpp"
#include <iostream>
#include <fstream>
#include <map>
#include <nlohmann/json.hpp>
using json = nlohmann::json;

// Global vectors to hold menu items
std::vector<Dish> dishes;
std::vector<Dish> combos;
std::vector<Wings> wings;
std::vector<Extra> extras;
std::vector<std::unique_ptr<Beverage>> beverages;


// Maps to store product IDs and their corresponding objects
std::map<int, std::pair<std::shared_ptr<Product>, int>> IndividualOrder;

using Products = std::map<int, std::pair<std::shared_ptr<Product>, int>>;

std::map<std::pair<int, bool>, std::shared_ptr<Products>> GeneralMap;

int TotalProducts = 0;

// Loading fucntion for sales
void LoadProduct(const nlohmann::json& j, const std::string& key, std::vector<Dish>& vec) {
    for (const auto& item : j[key]) {
        std::string name = item["name"];
        float price = item["price"];
        float price_carryout = item.contains("price_carryout") ? static_cast<float>(item["price_carryout"]) : price;
        vec.emplace_back(name, price, price_carryout);
    }
}

void LoadMenu() {
    // Clear previous data
    dishes.clear();
    combos.clear();
    wings.clear();
    extras.clear();
    beverages.clear();
    TotalProducts = 0;

    // Dishes
    std::ifstream file_dishes("../DataBase/JSON_database/Dishes.json");
    if (!file_dishes) { std::cerr << "No se pudo abrir Dishes.json\n"; return; }
    json j_dishes; file_dishes >> j_dishes;
    LoadProduct(j_dishes, "Dishes", dishes);

    // Combos
    std::ifstream file_combos("../DataBase/JSON_database/Combos.json");
    if (!file_combos) { std::cerr << "No se pudo abrir Combos.json\n"; return; }
    json j_combos; file_combos >> j_combos;
    LoadProduct(j_combos, "Combos", combos);

    // Wings
    std::ifstream file_wings("../DataBase/JSON_database/Wings.json");
    if (!file_wings) { std::cerr << "No se pudo abrir Wings.json\n"; return; }
    json j_wings; file_wings >> j_wings;
    for (const auto& item : j_wings["Wings"]) {
        std::string name = item["name"];
        float price = item["price"];
        float price_carryout = item["price_carryout"];
        std::string taste = item["taste"];
        wings.emplace_back(name, price, price_carryout, taste);
    }

    // Extras
    std::ifstream file_extras("../DataBase/JSON_database/Extras.json");
    if (!file_extras) { std::cerr << "No se pudo abrir Extras.json\n"; return; }
    json j_extras; file_extras >> j_extras;
    for (const auto& item : j_extras["Extras"]) {
        std::string name = item["name"];
        float price = item["price"];
        extras.emplace_back(name, price);
    }

    // Beverages
    std::ifstream file_beverages("../DataBase/JSON_database/Beverages.json");
    if (!file_beverages) { std::cerr << "No se pudo abrir Beverages.json\n"; return; }
    json j_beverages; file_beverages >> j_beverages;
    for (const auto& item : j_beverages["Beverages"]) {
        std::string name = item["name"];
        float price = item["price"];
        if (item.contains("flavor")) {
            std::string flavor = item["flavor"];
            beverages.push_back(std::make_unique<JuiceandMilkshake>(name, price, flavor));
        } else if (item.contains("volume")) {
            float volume = item["volume"];
            beverages.push_back(std::make_unique<Soda>(name, price, volume));
        } else {
            beverages.push_back(std::make_unique<Beverage>(name, price));
        }
    }

    TotalProducts = dishes.size() + combos.size() + wings.size() + extras.size() + beverages.size();
}