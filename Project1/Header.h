#pragma once

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <nlohmann/json.hpp>

using namespace std;
using json = nlohmann::json;

struct Order {
    int orderNumber;
    string orderDate;
    string product;
    double price;
};

// 🔹 CSV → vector
vector<Order> readCSV(const string& filename) {
    vector<Order> orders;
    ifstream file(filename);

    if (!file.is_open()) {
        throw runtime_error("Cannot open CSV file");
    }

    string line;

    while (getline(file, line)) {
        stringstream ss(line);
        string temp;
        Order o;

        getline(ss, temp, ',');
        o.orderNumber = stoi(temp);

        getline(ss, o.orderDate, ',');
        getline(ss, o.product, ',');

        getline(ss, temp, ',');
        o.price = stod(temp);

        orders.push_back(o);
    }

    return orders;
}

// 🔹 vector → JSON (рядками як CSV)
json convertToJSON(const vector<Order>& orders) {
    json j;

    for (const auto& o : orders) {
        string line =
            to_string(o.orderNumber) + "," +
            o.orderDate + "," +
            o.product + "," +
            to_string(o.price);

        j["orders"].push_back(line);
    }

    return j;
}

// 🔹 Save JSON
void saveJSON(const json& j, const string& filename) {
    ofstream file(filename);

    if (!file.is_open()) {
        throw runtime_error("Cannot open JSON file");
    }

    file << j.dump(4);
}

// 🔹 JSON → vector
vector<Order> readJSON(const string& filename) {
    vector<Order> orders;
    ifstream file(filename);

    if (!file.is_open()) {
        throw runtime_error("Cannot open JSON file");
    }

    json j;
    file >> j;

    for (const auto& line : j["orders"]) {
        stringstream ss(line.get<string>());
        string temp;
        Order o;

        getline(ss, temp, ',');
        o.orderNumber = stoi(temp);

        getline(ss, o.orderDate, ',');
        getline(ss, o.product, ',');

        getline(ss, temp, ',');
        o.price = stod(temp);

        orders.push_back(o);
    }

    return orders;
}

// 🔹 vector → CSV
void saveCSV(const vector<Order>& orders, const string& filename) {
    ofstream file(filename);

    if (!file.is_open()) {
        throw runtime_error("Cannot open CSV file");
    }

    for (const auto& o : orders) {
        file << o.orderNumber << ","
            << o.orderDate << ","
            << o.product << ","
            << o.price << "\n";
    }
}