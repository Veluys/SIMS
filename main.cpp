#include <iostream>
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
        cout << "\n"
             << "Product Name: " << prodName << endl;
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
    return 0;
}