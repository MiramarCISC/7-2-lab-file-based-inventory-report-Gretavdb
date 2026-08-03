#include "inventory_report.hpp"
#include <fstream>
#include <iomanip>
#include <iostream>

using namespace std;

bool isValidQuantity(int quantity) {
    //Return true when quantity is 0 or greater.
    return quantity >= 0;
}

bool isValidPrice(double price) {
    //Return true when price is 0 or greater.
    return price >= 0.0;
}

double calculateItemValue(const InventoryItem& item) {
    //Return quantity multiplied by price. // If quantity or price is invalid, return 0.0.
    if (!isValidQuantity(item.quantity) || !isValidPrice(item.price)) {
        return 0.0;
    }

    return item.quantity * item.price;
}

int readInventoryFile(string filename, InventoryItem items[], int maxItems) {
    // Open the input file.
    ifstream inputFile(filename);

    if (!inputFile.is_open()) {
        return 0;
    }

    if (items == nullptr || maxItems <= 0) {
        inputFile.close();
        return 0;
    }

    int count = 0;

    // Read records in this format: sku name quantity price
    // Stop when the file ends or maxItems is reached.
    while (count < maxItems &&
            inputFile >> items[count].sku
                    >> items[count].name
                    >> items[count].quantity
                    >> items[count].price) {

        // Store valid records in the items array.              
        if (isValidQuantity(items[count].quantity) &&
            isValidPrice(items[count].price)) {
            count ++;
        }
    }

        // Return the number of records stored.
        inputFile.close();
        return count;
}

bool writeInventoryReport(string filename, const InventoryItem items[], int count) {
    // Open the output file.
    ofstream outputFile(filename);

    if (!outputFile.is_open()) {
        return false;
    }

    if (items == nullptr || count <= 0) {
        outputFile.close();
        return false;
    }

    outputFile << fixed << setprecision(2);

    // Write each item and its total value.
    for (int i = 0; i < count; i++) {
        outputFile << items[i].sku << " "
                   << items[i].name << " " 
                   << items[i].quantity << " "
                   << items[i].price << " "
                   << calculateItemValue(items[i]) << endl;
    }

    // Write the total inventory value.
    outputFile << "Total inventory value: "
            << calculateTotalInventoryValue(items, count)
            << endl;

    // Return true if the report was written successfully.
    outputFile.close();
    return true;  
}

double calculateTotalInventoryValue(const InventoryItem items[], int count) {
    // Return the sum of all item values. // Return 0.0 for null arrays or invalid counts.
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
    // Search for a matching SKU. // Return the index if found. // Return -1 if not found.
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
    // Return the index of the item with the highest item value.
    // Return -1 for null arrays or invalid counts.
    if (items == nullptr || count <= 0) {
        return -1;
    }

    int highestIndex = 0;

    for (int i = 1; i < count; i++) {
        if (calculateItemValue(items[i]) >
            calculateItemValue(items[highestIndex])) {
                highestIndex = i;
            }
    }
    return highestIndex;
}
