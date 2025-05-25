#pragma once
#include <vector>
#include <memory>
#include "Menu_Items.hpp"

extern std::vector<Dish> dishes;
extern std::vector<Dish> combos;
extern std::vector<Wings> wings;
extern std::vector<std::unique_ptr<Beverage>> beverages;
extern std::vector<Extra> extras;
extern int TotalProducts;

void LoadMenu();