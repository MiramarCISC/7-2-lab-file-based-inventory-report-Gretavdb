#include "inventory_report.hpp"
#include <fstream>
#include <iomanip>
#include <iostream>

using namespace std;

bool isValidQuantity(int quantity) {
    return quantity >= 0;
}

bool isValidPrice(double price) {
    return price >= 0.0;
}

double calculateItemValue(const InventoryItem& item) {
    if (!isValidQuantity(item.quantity) || !isValidPrice(item.price)) {
        return 0.0;
    }
    return item.quantity * item.price;
}

int readInventoryFile(string filename, InventoryItem items[], int maxItems) {
    if (items == nullptr || maxItems <= 0) {
        return 0;
    }

    ifstream inputFile(filename);

    if (!inputFile.is_open()) {
        return 0;
    }

    int count = 0;
    InventoryItem tempItem;

    while (count < maxItems &&
           inputFile >> tempItem.sku
                     >> tempItem.name
                     >> tempItem.quantity
                     >> tempItem.price) {

        if (isValidQuantity(tempItem.quantity) &&
            isValidPrice(tempItem.price)) {

            items[count] = tempItem;
            count++;
        }
    }
    inputFile.close();
    return count;
}

bool writeInventoryReport(string filename, const InventoryItem items[], int count) {
    if (items == nullptr || count < 0) {
        return false;
    }
    ofstream outputFile(filename);
    if (!outputFile.is_open()) {
        return false;
    }
    outputFile << fixed << setprecision(2);
    outputFile << left
               << setw(12) << "SKU"
               << setw(20) << "Name"
               << right
               << setw(10) << "Quantity"
               << setw(12) << "Price"
               << setw(15) << "Value"
               << endl;

    for (int i = 0; i < count; i++) {
        outputFile << left
                   << setw(12) << items[i].sku
                   << setw(20) << items[i].name
                   << right
                   << setw(10) << items[i].quantity
                   << setw(12) << items[i].price
                   << setw(15) << calculateItemValue(items[i])
                   << endl;
    }
    outputFile << endl;
    outputFile << "Total inventory value: $"
               << calculateTotalInventoryValue(items, count)
               << endl;

    outputFile.close();
    return true;
}

double calculateTotalInventoryValue(const InventoryItem items[], int count) {
    if (items == nullptr || count <= 0) {
        return 0.0;
    }

    double total = 0.0;

    for (int i = 0; i < count; i++) {
        total += calculateItemValue(items[i]);
    }

    return total;
}

int findItemBySku(const InventoryItem items[], int count, string sku) {
    if (items == nullptr || count <= 0) {
        return -1;
    }

    for (int i = 0; i < count; i++) {
        if (items[i].sku == sku) {
            return i;
        }
    }

    return -1;
}

int findHighestValueItemIndex(const InventoryItem items[], int count) {
    if (items == nullptr || count <= 0) {
        return -1;
    }

    int highestIndex = 0;
    double highestValue = calculateItemValue(items[0]);

    for (int i = 1; i < count; i++) {
        double currentValue = calculateItemValue(items[i]);

        if (currentValue > highestValue) {
            highestValue = currentValue;
            highestIndex = i;
        }
    }

    return highestIndex;
}
