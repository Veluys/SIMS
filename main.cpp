#include <iostream>
#include <limits>
using namespace std;

const int MAX_STOCK = 50;
const int MAX_INV = 50;

class Product
{
private:
    string prodName = "";
    int stock = 0;
    double price = 0;

    void display() const
    {
        cout << "Product Name: " << prodName << endl;
        cout << "Stock: " << stock << endl;
        cout << "Price: " << price << endl;
        cout << "-------------------------------" << endl;
    }

    friend class Inventory;
};

class Inventory
{
    Product prodList[MAX_INV];
    int numProd = 0;

    bool isEmpty()
    {
        return numProd == 0;
    }
    bool isFull()
    {
        return numProd == MAX_INV;
    }

public:
    void addProd()
    {
        if (isFull())
        {
            cout << "The inventory is full, can't add more products.";
            return;
        }

        Product *newProd = &prodList[numProd];

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Enter product name: ";
        getline(cin, newProd->prodName);

        cout << "Enter initial stock: ";
        cin >> newProd->stock;

        cout << "Enter initial price: ";
        cin >> newProd->price;

        numProd++;
    }
    void showInv()
    {
        if (isEmpty())
        {
            cout << "The inventory is currently empty.";
            return;
        }

        for (size_t i = 0; i < numProd; i++)
        {
            prodList[i].display();
        }
    }
    void searchProd()
    {
        if (isEmpty())
        {
            cout << "The inventory is currently empty.";
            return;
        }

        string prod;
        cout << "Enter the product name to be search: ";
        cin >> prod;

        for (size_t i = 0; i < numProd; i++)
        {
            if (prod == prodList[i].prodName)
            {
                cout << "Product found!";
                return;
            }
        }
        cout << "Product not found!";
    }
};

int main()
{
    Inventory inv;
    int option;

    cout << "Welcome to the Simple Inventory Management System!" << endl;

    do
    {
        cout << "\n"
             << "Menu:" << endl;
        cout << "1. Add Product" << endl;
        cout << "2. Display All Products" << endl;
        cout << "3. Search for a Product" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> option;

        cout << "\n";

        switch (option)
        {
        case 1:
            inv.addProd();
            break;
        case 2:
            inv.showInv();
            break;
        case 3:
            inv.searchProd();
            break;
        case 4:
            cout << "Exiting the program. Goodbye!" << endl;
            break;
        default:
            cout << "Invalid option. Please select again." << endl;
            break;
        }
    } while (option != 4);
    return 0;
}