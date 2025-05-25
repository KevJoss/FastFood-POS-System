#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <iomanip>
#include "Environment/Environment.hpp"
#include "Menu_Items/Menu.hpp"
#include <filesystem>
#define WIDTH 80

int main() {
    LoadMenu();
    // std::cout << "Dishes cargados: " << dishes.size() << std::endl;
    // std::cout << "Combos cargados: " << combos.size() << std::endl;
    // std::cout << "Bebidas cargadas: " << beverages.size() << std::endl;
    // std::cout << "Extras cargados: " << extras.size() << std::endl;
    // Display the welcome message and menu
    DivisionText(WIDTH);
    CenterText("Gustav's Punto de Venta", WIDTH);
    DivisionText(WIDTH);

    std::string nombre = "Kevin";
    CenterText("Bienvenido " + nombre, WIDTH);
    DivisionText(WIDTH);

    int Selection = DisplayMenu();

    // Check if the user selected "Ventas" and perform the corresponding action
    return 0;
}



