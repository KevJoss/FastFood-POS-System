#include <iostream>
#include <iomanip>
#include <map>
#include "../Menu_Items/Menu.hpp"
#include "../Environment/Environment.hpp"
#include <chrono>
#include <thread>


using Products = std::map<int, std::pair<std::shared_ptr<Product>, int>>;


class OrderID {
    static int next_id;
    int id;
public:
    OrderID() : id(next_id++) {}
    OrderID(int id) : id(id) {}
    int getID() const { return id; }
};

int OrderID::next_id = 1;


void SearchProduct(int id, int qty);


bool CarryOutSale_UI() {
    std::cout << std::endl;
    bool carryout = true;
    std::cout << "Selecciona el tipo de pedido:\n";
    std::cout << "1) Pedido para llevar\n";
    std::cout << "2) Pedido para servirse";
    int option;
    std::cout << std::setw(WIDTH / 2) << "";
    std::cin >> option;
    switch (option) {
        case 1:
            carryout = true;
            return carryout;
        case 2:
            carryout = false;
            return carryout;
        default:
            std::cout << "Opcion no valida. Intente de nuevo.\n";
            CarryOutSale_UI();
            return NULL;
    }
};

void NewSale_UI(int flag = 0) {
    std::map <int, int> order;
    if (flag == 0)  {
        std::cout << "Ingrese el ID del producto y la cantidad que desea agregar al pedido.\n";
    }
    std::cout << std::endl;
    int id;
    int qty;

    DivisionText(WIDTH);
    std::cout << "ID -> ";
    std::cin >> id;
    while (id > TotalProducts || id < 1) {
        std::cout << "ID no valido. Intente de nuevo: ";
        std::cin >> id;
    }

    bool exist = false;
    for (const auto& [ID, pair] : IndividualOrder) {
        if (ID == id) {
            exist = true;
            break;
        }
    }
    if (exist) {
        std::cout << "El producto ya esta en el pedido.\nElija otro por favor.\n";
        NewSale_UI(1);
        return;
    }


    std::cout << "Cantidad -> ";
    std::cin >> qty;
     DivisionText(WIDTH);
    std::cout << std::endl;

    SearchProduct(id, qty);
    

    std::cout << "1) Agregar\t" << "2) Finalizar pedido"; 

    int option;
    std::cout << std::setw(WIDTH / 2) << "";

    std::cin >> option;
    switch (option) {
        case 1:
            NewSale_UI(flag = 1);
            break;
        case 2:
            std::cout << "Pedido finalizado.\n";
            break;
        default:
            std::cout << "Opcion no valida. Intente de nuevo.\n";
            NewSale_UI();
            break;
    }
}

void SearchProduct(int id, int qty) {
    for (const auto& dish : dishes) {
        if (dish.getID() == id) {
            IndividualOrder[id] = std::make_pair(std::make_shared<Dish>(dish), qty);
            return;
        }
    }
    for (const auto& combo : combos) {
        if (combo.getID() == id) {
            IndividualOrder[id] = std::make_pair(std::make_shared<Dish>(combo), qty);
            return;
        }
    }
    for (const auto& wing : wings) {
        if (wing.getID() == id) {
            IndividualOrder[id] = std::make_pair(std::make_shared<Wings>(wing), qty);
            return;
        }
    }
    for (const auto& extra : extras) {
        if (extra.getID() == id) {
            IndividualOrder[id] = std::make_pair(std::make_shared<Extra>(extra), qty);
            return;
        }
    }
    for (const auto& beverage : beverages) {
        if (beverage->getID() == id) {
            IndividualOrder[id] = std::make_pair(std::make_shared<Beverage>(*beverage), qty);
            return;
        }
    }
    std::cout << "Producto no encontrado.\n";
}

void GeneralOrders (const std::map<int, std::pair<std::shared_ptr<Product>, int>>& order, bool carryout) {
    auto ProductPointer = std::make_shared<Products>(order);

    OrderID order_id;

    std::pair<int, bool> key = {order_id.getID(), carryout};

    GeneralMap[key] = ProductPointer;

}


void ShowOrder(const std::map<std::pair<int, bool>, std::shared_ptr<Products>>& orders = GeneralMap) {
    DivisionText(WIDTH);
    CenterText("Listado de pedidos", WIDTH);
    DivisionText(WIDTH);
    std::cout << std::left << '\n';
    float total = 0.0f;
    for (const auto& [key, ptr_mapa] : orders) {
        std::cout << "Pedido ID: " << key.first
                  << " | Para llevar: " << (key.second ? "Si" : "No")
                  << '\n';
        for (const auto& [id, pair] : *ptr_mapa) {
            auto ptr_producto = pair.first;
            int quantity = pair.second;
            total += ptr_producto->getPrice(key.second) * quantity;
            std::cout << "  Cantidad: " << quantity
                    << " | Nombre: " << ptr_producto->getName()
                    << " | Precio: " << ptr_producto->getPrice(key.second) * quantity << " $"
                    << '\n';
        }
        std::cout << "Total del pedido: " << total << " $\n";
        std::cout << '\n';
    DivisionText(WIDTH);
    }
    std::cout << '\n';

}

void ShowOrderAndWait() {
    ShowOrder(); 
    std::cout << "\nPresione ENTER para volver al menu...";
    std::cin.ignore();
    std::cin.get();
    DisplayMenu();  
}

void OrderLoop() {
    while (true) {
        IndividualOrder.clear(); 
        bool carryout = CarryOutSale_UI();
        NewSale_UI();
        GeneralOrders(IndividualOrder, carryout);

        std::cout << "\nDesea realizar otro pedido?\n";
        std::cout << "1) Nuevo pedido\n";
        std::cout << "2) Mostrar resumen y finalizar";
        int option;
        std::cout << std::setw(WIDTH / 2) << "";

        std::cin >> option;
        if (option == 2) {
            ShowOrderAndWait();
            break;
        }
    }
}



