#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <limits>

class Item {
public:
    int itemCode;
    std::string itemName;
    double cost;
    int quantity;

    Item(int code = 0, std::string name = "", double c = 0.0, int q = 0)
        : itemCode(code), itemName(name), cost(c), quantity(q) {}

    void display() const {
        std::cout << "  Code: " << itemCode
                  << ", Name: " << itemName
                  << ", Cost: " << cost
                  << ", Quantity: " << quantity
                  << std::endl;
    }
};

bool compareByCode(const Item& a, const Item& b) {
    return a.itemCode < b.itemCode;
}

bool compareByCost(const Item& a, const Item& b) {
    return a.cost < b.cost;
}

bool compareByQuantity(const Item& a, const Item& b) {
    return a.quantity < b.quantity;
}

void addItem(std::vector<Item>& items) {
    int code, qty;
    std::string name;
    double cost;

    std::cout << "Enter Item Code: ";
    std::cin >> code;
    std::cout << "Enter Item Name: ";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin, name);
    std::cout << "Enter Cost: ";
    std::cin >> cost;
    std::cout << "Enter Quantity: ";
    std::cin >> qty;

    items.push_back(Item(code, name, cost, qty));
    std::cout << "Item added." << std::endl;
}

void displayItems(const std::vector<Item>& items) {
    if (items.empty()) {
        std::cout << "No items to display." << std::endl;
        return;
    }
    std::cout << "--- Item Records ---" << std::endl;
    for (const auto& item : items) {
        item.display();
    }
    std::cout << "--------------------" << std::endl;
}

void searchByCode(const std::vector<Item>& items) {
    int code;
    std::cout << "Enter Item Code to search: ";
    std::cin >> code;

    bool found = false;
    for (const auto& item : items) {
        if (item.itemCode == code) {
            std::cout << "Search Result:" << std::endl;
            item.display();
            found = true;
            break;
        }
    }

    if (!found) {
        std::cout << "Item with code " << code << " not found." << std::endl;
    }
}

void searchByName(const std::vector<Item>& items) {
    std::string name;
    std::cout << "Enter Item Name to search: ";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin, name);

    bool found = false;
    for (const auto& item : items) {
        if (item.itemName == name) {
            std::cout << "Search Result:" << std::endl;
            item.display();
            found = true;
            break;
        }
    }

    if (!found) {
        std::cout << "Item with name '" << name << "' not found." << std::endl;
    }
}

int main() {
    std::vector<Item> inventory;
    int choice;

    do {
        std::cout << "\nItem Record System (STL Vector)" << std::endl;
        std::cout << "1. Add Item" << std::endl;
        std::cout << "2. Display All Items" << std::endl;
        std::cout << "3. Sort by Item Code" << std::endl;
        std::cout << "4. Sort by Cost" << std::endl;
        std::cout << "5. Sort by Quantity" << std::endl;
        std::cout << "6. Search by Item Code" << std::endl;
        std::cout << "7. Search by Item Name" << std::endl;
        std::cout << "8. Exit" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        if (choice == 1) {
            addItem(inventory);
        } else if (choice == 2) {
            displayItems(inventory);
        } else if (choice == 3) {
            std::sort(inventory.begin(), inventory.end(), compareByCode);
            std::cout << "Items sorted by code." << std::endl;
            displayItems(inventory);
        } else if (choice == 4) {
            std::sort(inventory.begin(), inventory.end(), compareByCost);
            std::cout << "Items sorted by cost." << std::endl;
            displayItems(inventory);
        } else if (choice == 5) {
            std::sort(inventory.begin(), inventory.end(), compareByQuantity);
            std::cout << "Items sorted by quantity." << std::endl;
            displayItems(inventory);
        } else if (choice == 6) {
            searchByCode(inventory);
        } else if (choice == 7) {
            searchByName(inventory);
        } else if (choice == 8) {
            std::cout << "Exiting." << std::endl;
        } else {
            std::cout << "Invalid choice. Please try again." << std::endl;
            if (std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
        }
    } while (choice != 8);

    return 0;
}