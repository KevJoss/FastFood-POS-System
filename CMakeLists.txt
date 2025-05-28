cmake_minimum_required(VERSION 3.10)
project(POS_System)

set(CMAKE_CXX_STANDARD 17)

# Incluye tus carpetas de headers
include_directories(
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/Menu_Items
    ${PROJECT_SOURCE_DIR}/Environment
    ${PROJECT_SOURCE_DIR}/System_funcs
    ${PROJECT_SOURCE_DIR}/Final_Database
)

# Archivos fuente principales
add_executable(POS_System
    POS_System.cpp
    Menu_Items/Menu.cpp
    Menu_Items/Menu_Items.cpp
    Environment/Environment.cpp
    System_funcs/NewSale.cpp
    Final_Database/SaveOrders.cpp
)
