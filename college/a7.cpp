#include <iostream>
#include <string>
#include <limits>
using namespace std;

class Publication {
protected:
    string title;
    float price;
public:
    Publication() : title(""), price(0.0) {}
    virtual void getData() {
        cout << "Enter title: ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, title);
        cout << "Enter price: ";
        cin >> price;
        if (cin.fail() || price < 0)
            throw invalid_argument("Invalid price input!");
    }
    virtual void displayData() const {
        cout << "Title: " << title << endl;
        cout << "Price: " << price << endl;
    }
    virtual ~Publication() {}
};

class Book : public Publication {
    int pageCount;
public:
    Book() : pageCount(0) {}
    void getData() override {
        try {
            Publication::getData();
            cout << "Enter page count: ";
            cin >> pageCount;
            if (cin.fail() || pageCount < 0)
                throw invalid_argument("Invalid page count input!");
        } catch (exception &e) {
            cerr << "Exception: " << e.what() << endl;
            title = "";
            price = 0.0;
            pageCount = 0;
        }
    }
    void displayData() const override {
        cout << "\n--- Book Details ---" << endl;
        Publication::displayData();
        cout << "Page Count: " << pageCount << endl;
    }
};

class Tape : public Publication {
    float playTime;
public:
    Tape() : playTime(0.0) {}
    void getData() override {
        try {
            Publication::getData();
            cout << "Enter play time (in minutes): ";
            cin >> playTime;
            if (cin.fail() || playTime < 0)
                throw invalid_argument("Invalid play time input!");
        } catch (exception &e) {
            cerr << "Exception: " << e.what() << endl;
            title = "";
            price = 0.0;
            playTime = 0.0;
        }
    }
    void displayData() const override {
        cout << "\n--- Tape Details ---" << endl;
        Publication::displayData();
        cout << "Play Time: " << playTime << " minutes" << endl;
    }
};

int main() {
    Book b;
    Tape t;

    cout << "Enter Book Details:\n";
    b.getData();

    cout << "\nEnter Tape Details:\n";
    t.getData();

    cout << "\n=============================\n";
    cout << "Publication Details\n";
    cout << "=============================\n";

    b.displayData();
    t.displayData();

    return 0;
}
