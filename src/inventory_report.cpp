#include "inventory_report.hpp"
#include <fstream>
#include <iomanip>
#include <iostream>

using namespace std;

bool isValidQuantity(int quantity) {
    // TODO: Return true when quantity is 0 or greater.
    return quantity >= 0;
}

bool isValidPrice(double price) {
    // TODO: Return true when price is 0 or greater.
    return price >= 0.0;
}

double calculateItemValue(const InventoryItem& item) {
    // TODO: Return quantity multiplied by price.
    // If quantity or price is invalid, return 0.0.
    if (!isValidQuantity(item.quantity) || !isValidPrice(item.price)) {
return 0.0;
}

return item.quantity * item.price;
}

int readInventoryFile(string filename, InventoryItem items[], int maxItems) {
    // TODO:
    // Open the input file.
    // Read records in this format: sku name quantity price
    // Store valid records in the items array.
    // Stop when the file ends or maxItems is reached.
    // Return the number of records stored.
    ifstream inputFile(filename);

if (!inputFile.is_open()) {
return 0;
}

int count = 0;
InventoryItem item;

while (count < maxItems &&
inputFile >> item.sku >> item.name >> item.quantity >> item.price) {

if (isValidQuantity(item.quantity) && isValidPrice(item.price)) {
items[count] = item;
count++;
}
}
inputFile.close();

return count;
}
bool writeInventoryReport(string filename, const InventoryItem items[], int count) {
    // TODO:
    // Open the output file.
    // Write each item and its total value.
    // Write the total inventory value.
    // Return true if the report was written successfully.
    ofstream outputFile(filename);

if (!outputFile.is_open()) {
return false;
}
outputFile << fixed << setprecision(2);

for (int i = 0; i < count; i++) {
outputFile << items[i].sku << " "
<< items[i].name << " "
<< items[i].quantity << " "
<< items[i].price << " "
<< calculateItemValue(items[i]) << endl;
}

outputFile << "Total inventory value: "
<< calculateTotalInventoryValue(items, count) << endl;

outputFile.close();

return true;
}

double calculateTotalInventoryValue(const InventoryItem items[], int count) {
    // TODO:
    // Return the sum of all item values.
    // Return 0.0 for null arrays or invalid counts.
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
    // TODO:
    // Search for a matching SKU.
    // Return the index if found.
    // Return -1 if not found.
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
    // TODO:
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
