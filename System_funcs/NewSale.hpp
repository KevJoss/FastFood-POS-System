#include <map>

void NewSale_UI(int flag = 0);
void SearchProduct(int id, int qty);
bool CarryOutSale_UI();
void OrderLoop();
void ShowOrderAndWait();



void GeneralOrders (const std::map<int, std::pair<std::shared_ptr<Product>, int>>& order, bool carryout);
void ShowOrder(const std::map<std::pair<int, bool>, std::shared_ptr<Products>>& orders = GeneralMap);