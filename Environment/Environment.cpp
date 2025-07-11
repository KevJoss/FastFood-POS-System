#include "../Menu_Items/Menu.hpp"
#include "../System_funcs/NewSale.hpp"
#include "../Final_Database/SaverOrders.hpp"
#include <iostream>
#include <chrono>
#include <thread>
#include <iomanip>
#include <vector>
// #define WIDTH 80
#define DISPLAY 4

extern const int WIDTH = 80;
extern const int TIME = 600;

// General Function to center text in the console
void CenterText(const std::string& text, int width) {
    int padding = (width > static_cast<int>(text.size())) ? (width - text.size()) / 2 : 0;
    std::cout << std::string(padding, ' ') << text << std::endl;
}
// General Function to create a division line in the console
void DivisionText(int width) {
    std::cout << std::setfill('-') << std::setw(width) << "-" << std::endl;
    std::cout << std::setfill(' ');
}
// General Function to jump lines
void JumpLine(int lines) {
    for (int i = 0; i < lines; ++i) {
        std::cout << std::endl;
    }
}

/// SECTION TO MENUS AND BOTTOM NAVIGATION ///

void SalesMenu(); 

// Display the menu and return the selected option
void DisplayMenu();

// Display the new sale menu
void NewSale();

void OrderList();

void ProductsMenu();

// Display general menu options
void DisplayMenu(){
    system("clear" " || cls"); // Clear the console
    DivisionText(WIDTH);
    CenterText("Gustav's Punto de Venta", WIDTH);
    DivisionText(WIDTH);

    std::string nombre = "Kevin";
    CenterText("Bienvenido " + nombre, WIDTH);
    DivisionText(WIDTH);
    std::cout << "1) Listado de Pedidos";
    JumpLine(2);
    std::cout << "2) Estadisticas";
    JumpLine(2);
    std::cout << "3) Productos";
    JumpLine(2);
    std::cout << "4) Realizar Venta";
    JumpLine(2);
    std::cout << "5) Finalizar dia";
    int Selection;
    std::cout << std::setw(WIDTH / 2) << "";
    std::cin >> Selection;
    switch (Selection) {
        case 1:
            DivisionText(WIDTH);
            CenterText("ABRIENDO LISTADO DE PEDIDOS...", WIDTH);
            std::this_thread::sleep_for(std::chrono::milliseconds(TIME));
            ShowOrderAndWait();
            return;
        case 2:
            DivisionText(WIDTH);
            CenterText("ABRIENDO ESTADISTICAS...", WIDTH);
            std::this_thread::sleep_for(std::chrono::milliseconds(TIME));
            DivisionText(WIDTH);
            CenterText("Estadisticas", WIDTH);
            DivisionText(WIDTH);
            std::cout << "\nPresione ENTER para volver al menu...";
            std::cin.ignore();
            std::cin.get();
            DisplayMenu();  
            return;
        case 3:
            DivisionText(WIDTH);
            CenterText("ABRIENDO PRODUCTOS...", WIDTH);
            std::this_thread::sleep_for(std::chrono::milliseconds(TIME));
            DivisionText(WIDTH);
            CenterText("Productos", WIDTH);
            DivisionText(WIDTH);
            ProductsMenu();
            std::cout << "\nPresione ENTER para volver al menu...";
            std::cin.ignore();
            std::cin.get();
            DisplayMenu();  
            return;
        case 4:
            DivisionText(WIDTH);
            CenterText("ABRIENDO VENTAS...", WIDTH);
            std::this_thread::sleep_for(std::chrono::milliseconds(TIME));
            DivisionText(WIDTH);
            CenterText("Realizar Venta", WIDTH);
            DivisionText(WIDTH);
            OrderList();
            return;
        case 5:
            DivisionText(WIDTH);
            CenterText("FINALIZANDO DIA...", WIDTH);
            CenterText("Guardando pedidos...", WIDTH);
            SaveOrdersToJSON("../DataBase/JSON_database/Orders.json");
            std::this_thread::sleep_for(std::chrono::milliseconds(TIME));
            CenterText("Archivo creado con exito", WIDTH);
            DivisionText(WIDTH);
            CenterText("Gracias por usar el sistema", WIDTH);
            return;
        default:
            DivisionText(WIDTH);
            CenterText("Opcion no valida", WIDTH);
            return;
    }
}


// Sales Environment Selection
void SalesMenu(){
    std::cout << std::setw(20) << "Volver al Menu";
    std::cout << std::setw(40) << "Nueva venta" << std::endl;
    std::cout << std::setw(40) << "Pedidos";
    std::cout << std::setw(WIDTH - 20) << "";
    int SalesSelection;
    std::cin >> SalesSelection;
    switch (SalesSelection) {
        case 1:
            DivisionText(WIDTH);
            CenterText("VOLVIENDO AL MENU...", WIDTH);
            std::this_thread::sleep_for(std::chrono::milliseconds(TIME));
            DivisionText(WIDTH);
            DisplayMenu();
            break;
        case 2:
            DivisionText(WIDTH);
            CenterText("ABRIENDO NUEVA VENTA...", WIDTH);
            std::this_thread::sleep_for(std::chrono::milliseconds(TIME));
            DivisionText(WIDTH);
            NewSale();
            break;
        case 3:
            DivisionText(WIDTH);
            CenterText("ABRIENDO PEDIDOS...", WIDTH);
            std::this_thread::sleep_for(std::chrono::milliseconds(TIME));
            DivisionText(WIDTH);  
            std::cout << "Seccion 3" << std::endl;
            break;
        default:
            DivisionText(WIDTH);
            std::cout << "Opcion no valida" << std::endl;
            break;
    }
}

template <typename T>
void ShowProducts(const std::vector<T>& productos, int width = WIDTH) {
    int currentWidth = 0;
    for (size_t i = 0; i < productos.size(); ++i) {
        std::string nombre = productos[i].getName();
        int ID = productos[i].getID();
        int celdaWidth = std::max(24, static_cast<int>(nombre.length()) + 6);
        std::ostringstream oss;
        oss << std::setw(2) << ID << ") " << nombre;
        std::string celda = oss.str();
        if (currentWidth + celdaWidth > width) {
            std::cout << std::endl;
            currentWidth = 0;
        }
        std::cout << std::setw(celdaWidth) << std::left << celda;
        currentWidth += celdaWidth;
    }
    std::cout << std::endl;
}

// Specialization for beverages (smart pointers)
void ShowProducts(const std::vector<std::unique_ptr<Beverage>>& productos, int width = WIDTH) {
    int currentWidth = 0;
    for (size_t i = 0; i < productos.size(); ++i) {
        std::string nombre = productos[i]->getName();
        int ID = productos[i]->getID();
        int celdaWidth = std::max(24, static_cast<int>(nombre.length()) + 6);
        std::ostringstream oss;
        oss << std::setw(2) << ID << ") " << nombre;
        std::string celda = oss.str();
        if (currentWidth + celdaWidth > width) {
            std::cout << std::endl;
            currentWidth = 0;
        }
        std::cout << std::setw(celdaWidth) << std::left << celda;
        currentWidth += celdaWidth;
    }
    std::cout << std::endl;
}

void ProductsMenu() {
        CenterText("Platos Individuales", WIDTH);
    DivisionText(WIDTH);
    std::cout << std::left << '\n';
    ShowProducts(dishes);
    std::cout << '\n';

    std::cout.unsetf(std::ios::adjustfield);
    DivisionText(WIDTH);
    CenterText("Combos", WIDTH);
    DivisionText(WIDTH);
    std::cout << std::left << '\n';
    ShowProducts(combos);
    ShowProducts(wings);
    std::cout << '\n';

    std::cout.unsetf(std::ios::adjustfield);
    DivisionText(WIDTH);
    CenterText("Extras", WIDTH);
    DivisionText(WIDTH);
    std::cout << std::left << '\n';
    ShowProducts(extras);
    std::cout << '\n';


    std::cout.unsetf(std::ios::adjustfield);
    DivisionText(WIDTH);
    CenterText("Bebidas", WIDTH);
    DivisionText(WIDTH);
    std::cout << std::left << '\n';
    ShowProducts(beverages);
    std::cout << '\n';
    DivisionText(WIDTH);
}


// New Sale Environment Selection
void NewSale() {
    CenterText("Platos Individuales", WIDTH);
    DivisionText(WIDTH);
    std::cout << std::left << '\n';
    ShowProducts(dishes);
    std::cout << '\n';

    std::cout.unsetf(std::ios::adjustfield);
    DivisionText(WIDTH);
    CenterText("Combos", WIDTH);
    DivisionText(WIDTH);
    std::cout << std::left << '\n';
    ShowProducts(combos);
    ShowProducts(wings);
    std::cout << '\n';

    std::cout.unsetf(std::ios::adjustfield);
    DivisionText(WIDTH);
    CenterText("Extras", WIDTH);
    DivisionText(WIDTH);
    std::cout << std::left << '\n';
    ShowProducts(extras);
    std::cout << '\n';


    std::cout.unsetf(std::ios::adjustfield);
    DivisionText(WIDTH);
    CenterText("Bebidas", WIDTH);
    DivisionText(WIDTH);
    std::cout << std::left << '\n';
    ShowProducts(beverages);
    std::cout << '\n';
    DivisionText(WIDTH);
    CenterText("Nuevo pedido", WIDTH);
    DivisionText(WIDTH);
    OrderLoop();
}


// Order List Environment 
void OrderList(){
    std::cout << "1) Nuevo pedido";
    JumpLine(2);
    std::cout << "2) Volver al menu";
    int Selection;
    std::cout << std::setw(WIDTH / 2) << "";
    std::cin >> Selection;
    switch (Selection)
    {
    case 1:
        DivisionText(WIDTH);
        CenterText("ABRIENDO NUEVO PEDIDO...", WIDTH);
        std::this_thread::sleep_for(std::chrono::milliseconds(TIME));
        DivisionText(WIDTH);
        NewSale();
        break;
    case 2:
        DivisionText(WIDTH);
        CenterText("VOLVIENDO AL MENU...", WIDTH);
        std::this_thread::sleep_for(std::chrono::milliseconds(TIME));
        DivisionText(WIDTH);
        DisplayMenu();
        break;
    default:
        break;
    }
}

