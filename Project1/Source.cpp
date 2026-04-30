#include "Header.h"

int main() {
    try {
        // 🔹 CSV → JSON
        vector<Order> orders = readCSV("orders.csv");
        json j = convertToJSON(orders);
        saveJSON(j, "output.json");

        // 🔹 JSON → CSV (reverse conversion)
        vector<Order> fromJson = readJSON("output.json");
        saveCSV(fromJson, "restored.csv");

        cout << "Conversion completed successfully!\n";
    }
    catch (const exception& e) {
        cout << "Error: " << e.what() << endl;
    }

    return 0;
}