#include <iostream>
#include <limits>
#include <cctype>
using namespace std;

const int MAX_STOCK = 50;
const int MAX_INV = 50;

string getValidString(const string &prompt)
{
    string text;

    while (true)
    {
        cout << prompt;
        getline(cin, text);
        if (text.empty())
        {
            cout << "Input can't be empty. Please enter a new value." << endl
                 << endl;
            continue;
        }
        return text;
    }
}

double getValidNumeric(const string &prompt, const string &action, const double &currVal = 0)
{
    double numVal;
    while (true)
    {
        cout << prompt;
        cin >> numVal;

        if (cin.fail())
        {
            cout << "Invalid input, enter a new value." << endl
                 << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (action == "option" && !((int)numVal > 0 && (int)numVal <= 5))
        {
            cout << "Choice input should only range from 1 - 5." << endl
                 << endl;
            continue;
        }
        else if (action == "updOption" && !((int)numVal > 0 && (int)numVal <= 7))
        {
            cout << "Choice input should only range from 1 - 7." << endl
                 << endl;
            continue;
        }
        else if (action == "iniStock" && !((int)numVal > 0 && (int)numVal <= MAX_STOCK))
        {
            cout << "Stock should be a positive value less than or equal to " << MAX_STOCK << "." << endl
                 << endl;
            continue;
        }
        else if (action == "iniPrice" && numVal <= 0)
        {
            cout << "Price should only be a positive value." << endl
                 << endl;
            continue;
        }
        else if (action == "updStock" && !((int)numVal + currVal <= MAX_STOCK && (int)numVal + currVal > 0))
        {
            cout << "Stock should be a positive value less than or equal to " << MAX_STOCK << "." << endl
                 << endl;
            continue;
        }
        //                  T          && T
        else if (action == "updPrice" && numVal + currVal <= 0)
        {
            cout << "Price should only be a positive value." << endl
                 << endl;
            continue;
        }
        return numVal;
    }
}

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
    int productExistsAt(const string pName) const
    {
        for (int i = 0; i < numProd; i++)
        {
            const string existingProduct = prodList[i].prodName;

            if (existingProduct.length() != pName.length())
            {
                continue;
            }

            for (int j = 0; j < pName.length(); j++)
            {
                if (tolower(existingProduct[j]) != tolower(pName[j]))
                {
                    break;
                }
                if (j == pName.size() - 1)
                {
                    return i;
                }
            }
        }
        return -1;
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
        string pName = getValidString("Enter product name: ");

        if (productExistsAt(pName) != -1)
        {
            cout << "Product name already exists!" << endl;
            return;
        }

        newProd->prodName = pName;
        newProd->stock = getValidNumeric("Enter initial stock: ", "iniStock");
        newProd->price = getValidNumeric("Enter initial price: ", "iniPrice");

        numProd++;
    }
    void showInv()
    {
        if (isEmpty())
        {
            cout << "The inventory is currently empty." << endl;
            return;
        }

        cout << "Products in Inventory: " << endl;
        for (size_t i = 0; i < numProd; i++)
        {
            prodList[i].display();
        }
    }
    void searchProd()
    {
        if (isEmpty())
        {
            cout << "The inventory is currently empty." << endl;
            return;
        }

        string prod = getValidString("Enter the product name to be search: ");

        if (productExistsAt(prod) != -1)
        {
            prodList[productExistsAt(prod)].display();
            return;
        }
        else
        {
            cout << "Product not found!" << endl;
        }
    }
    void updProd()
    {
        if (isEmpty())
        {
            cout << "The inventory is currently empty." << endl;
            return;
        }

        string prodName = getValidString("Enter the product name to be updated: ");

        if (productExistsAt(prodName) == -1)
        {
            cout << "Product not found!" << endl;
            return;
        }

        Product *product = &prodList[productExistsAt(prodName)];
        auto updProdName = [](Product *product)
        {
            cout << "Current Product Name: " << product->prodName << endl;
            product->prodName = getValidString("Enter new product name: ");
            cout << "\n";
        };

        auto updStock = [](Product *product)
        {
            cout << "Current Stock: " << product->stock << endl;
            product->stock += (int)getValidNumeric("Enter quantity to add (negative to remove): ", "updStock", product->stock);
            cout << "\n";
        };

        auto updPrice = [](Product *product)
        {
            cout << "Current Price: " << product->price << endl;
            product->price += getValidNumeric("Enter price to add (negative to remove): ", "updPrice", product->price);
            cout << "\n";
        };

        cout << "\n"
             << "Select the information you want to update: " << endl;
        cout << "1. Product Name" << endl;
        cout << "2. Product Stock" << endl;
        cout << "3. Product Price" << endl;
        cout << "4. Product Name and Stock" << endl;
        cout << "5. Product Name and Price" << endl;
        cout << "6. Product Stock and Price" << endl;
        cout << "7. Product Name, Stock, and Price" << endl;

        int option = getValidNumeric("Enter option: ", "updOption");
        cout << "\n";
        switch (option)
        {
        case 1:
            updProdName(product);
            break;
        case 2:
            updStock(product);
            break;
        case 3:
            updPrice(product);
            break;
        case 4:
            updProdName(product);
            updStock(product);
            break;
        case 5:
            updProdName(product);
            updPrice(product);
            break;
        case 6:
            updStock(product);
            updPrice(product);
            break;
        case 7:
            updProdName(product);
            updStock(product);
            updPrice(product);
            break;
        default:
            cout << "Invalid option. Please select again." << endl;
            break;
        }

        product->display();
        return;
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
        cout << "4. Update a Product" << endl;
        cout << "5. Exit" << endl;

        option = getValidNumeric("Enter your choice: ", "option");

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
            inv.updProd();
            break;
        case 5:
            cout << "Exiting the program. Goodbye!" << endl;
            break;
        default:
            cout << "Invalid option. Please select again." << endl;
            break;
        }
    } while (option != 5);
    return 0;
}