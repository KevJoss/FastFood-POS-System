#include <fstream>
#include <nlohmann/json.hpp>
#include "../Menu_Items/Menu.hpp"

using json = nlohmann::json;

void SaveOrdersToJSON(const std::string& filename) {
    json pedidos_json;

    for (const auto& [key, ptr_mapa] : GeneralMap) {
        int order_id = key.first;
        bool carryout = key.second;
        json pedido;
        pedido["carryout"] = carryout;
        for (const auto& [id, pair] : *ptr_mapa) {
            auto ptr_producto = pair.first;
            int quantity = pair.second;
            pedido["productos"].push_back({
                {"id", id},
                {"nombre", ptr_producto->getName()},
                {"cantidad", quantity},
                {"precio", ptr_producto->getPrice(carryout) * quantity}
            });
        }
        pedidos_json[std::to_string(order_id)] = pedido;
    }

    std::ofstream file(filename);
    file << pedidos_json.dump(4); 
    file.close();
}