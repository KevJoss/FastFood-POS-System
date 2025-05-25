#include <iostream>
#include "../Menu_Items/Menu.hpp"


void NewSale_UI() {
    float sale;
    std::string quantity;

    std::cout << "ID ";
    std::cin >> sale;
    while (sale > TotalProducts || sale < 1) {
        std::cout << "ID no valido. Intente de nuevo: ";
        std::cin >> sale;
    }

    std::cout << "Cantidad: ";
    std::cin >> quantity;
    
}