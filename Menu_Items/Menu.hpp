#pragma once
#include <vector>
#include <memory>
#include "Menu_Items.hpp"
#include <map>

extern std::vector<Dish> dishes;
extern std::vector<Dish> combos;
extern std::vector<Wings> wings;
extern std::vector<std::unique_ptr<Beverage>> beverages;
extern std::vector<Extra> extras;
extern int TotalProducts;

using Products = std::map<int, std::pair<std::shared_ptr<Product>, int>>;

extern std::map<int, std::pair<std::shared_ptr<Product>, int>> IndividualOrder;

extern std::map<std::pair<int, bool>, std::shared_ptr<Products>> GeneralMap;

void LoadMenu();