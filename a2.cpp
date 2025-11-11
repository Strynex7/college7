#include <iostream>
#include <string>
using namespace std;

class Product {
    int productID;
    string productName;
    float price;
    int quantity;
    static int totalProducts;

public:
    Product() { productID = 0; productName = ""; price = 0; quantity = 0; totalProducts++; }
    Product(int id, string name, float p, int q) {
        productID = id; productName = name; price = p; quantity = q; totalProducts++;
    }
    Product(const Product &p) {
        productID = p.productID; productName = p.productName;
        price = p.price; quantity = p.quantity; totalProducts++;
    }
    ~Product() {}

    void getData() {
        cout << "\nEnter Product ID (numbers only): ";
        cin >> productID;
        cin.ignore();
        cout << "Enter Product Name: ";
        getline(cin, productName);
        cout << "Enter Price: ";
        cin >> price;
        cout << "Enter Quantity: ";
        cin >> quantity;
        cin.ignore();
    }

    void showData() {
        cout << "\nProduct ID: " << productID;
        cout << "\nProduct Name: " << productName;
        cout << "\nPrice: " << price;
        cout << "\nQuantity: " << quantity;
        cout << "\nTotal Stock Value: " << stockValue() << "\n";
    }

    inline float stockValue() { return price * quantity; }

    int getID() { return productID; }

    static void showTotalProducts() {
        cout << "\nTotal number of products created: " << totalProducts << "\n";
    }

    friend void comparePrice(Product &p1, Product &p2);
};

int Product::totalProducts = 0;

void comparePrice(Product &p1, Product &p2) {
    cout << "\nComparing Prices:\n";
    if (p1.price > p2.price)
        cout << p1.productName << " is costlier than " << p2.productName << ".\n";
    else if (p2.price > p1.price)
        cout << p2.productName << " is costlier than " << p1.productName << ".\n";
    else
        cout << "Both products have the same price.\n";
}

int main() {
    Product products[50];
    int n = 0;
    string choice;

    while (true) {
        cout << "\n----- Inventory Menu -----";
        cout << "\n1. Add New Product";
        cout << "\n2. Display All Products";
        cout << "\n3. Compare Two Products (by ID)";
        cout << "\n4. Show Total Products";
        cout << "\n5. Exit";
        cout << "\nEnter your choice: ";
        getline(cin, choice);

        if (choice == "1") {
            products[n++].getData();
        }
        else if (choice == "2") {
            if (n == 0) cout << "No products available!\n";
            for (int i = 0; i < n; i++) products[i].showData();
        }
        else if (choice == "3") {
            if (n < 2) {
                cout << "At least two products are needed to compare.\n";
                continue;
            }
            int id1, id2;
            cout << "Enter first Product ID: ";
            cin >> id1;
            cout << "Enter second Product ID: ";
            cin >> id2;
            cin.ignore();

            Product *p1 = nullptr, *p2 = nullptr;
            for (int i = 0; i < n; i++) {
                if (products[i].getID() == id1) p1 = &products[i];
                if (products[i].getID() == id2) p2 = &products[i];
            }

            if (p1 && p2) comparePrice(*p1, *p2);
            else cout << "One or both product IDs not found!\n";
        }
        else if (choice == "4") {
            Product::showTotalProducts();
        }
        else if (choice == "5") {
            cout << "\nExiting program...\n";
            break;
        }
        else {
            cout << "Invalid choice! Try again.\n";
        }
    }
    return 0;
}
