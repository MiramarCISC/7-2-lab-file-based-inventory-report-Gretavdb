[![Open in Codespaces](https://classroom.github.com/assets/launch-codespace-2972f46106e565e64193e422d61a12cf1da4916b45550586e14ef0a7c637dd04.svg)](https://classroom.github.com/open-in-codespaces?assignment_repo_id=24283910)
# CISC 192 Lab 7.2: File-Based Inventory Report

## Overview

In this lab, you will build an inventory report program that reads item records from a text file, stores them in an array of structures, calculates inventory totals, and writes a report to an output file.

This lab focuses on file input, file output, structures, arrays, loops, validation, and report formatting.

## Required Features

Your program must:

- Define an `InventoryItem` structure
- Read inventory records from a file
- Store inventory records in an array of structures
- Calculate the value of one item
- Calculate the total inventory value
- Find the item with the highest total value
- Search for an item by SKU
- Write a formatted inventory report to a file
- Pass the automated tests

## Input File Format

Each inventory record should use this format:

```text
SKU Name Quantity Price
```

Example:

```text
A100 Apples 10 1.50
B200 Bread 5 3.25
C300 Cereal 8 4.75
```

Use single-word item names for this lab.

## Build and Run

```bash
make
./main
```

## Run Tests

```bash
make test
```

## Required Functions

```cpp
bool isValidQuantity(int quantity);
bool isValidPrice(double price);
double calculateItemValue(const InventoryItem& item);

int readInventoryFile(std::string filename, InventoryItem items[], int maxItems);
bool writeInventoryReport(std::string filename, const InventoryItem items[], int count);

double calculateTotalInventoryValue(const InventoryItem items[], int count);
int findItemBySku(const InventoryItem items[], int count, std::string sku);
int findHighestValueItemIndex(const InventoryItem items[], int count);
```

## Grading Notes

This lab is about file input and output. Do not hard-code all inventory records in the program.

Your tests may create temporary files to verify that file reading and writing work correctly.
