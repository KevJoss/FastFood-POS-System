#pragma once
#include <string>
/// SECTION TO MENUS AND BOTTOM NAVIGATION ///
extern const int WIDTH;
extern const int TIME;

void CenterText(const std::string& text, int width);

void DivisionText(int width);

void JumpLine(int lines);

int DisplayMenu();

int SalesMenu();

void NewSale();

void OrderList();