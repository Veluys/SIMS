#include <iostream>
#include <limits>
#include <cctype>
#include <functional>
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
template <typename T>
T getValidNumeric(const string &prompt, function<bool(T)> isValid, const string &failMsg)
{
    T numVal;
    while (true)
    {
        cout << prompt;
        cin >> numVal;

        if (cin.fail())
        {
            cout << "Invalid input. Please enter a new value\n\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        if (!isValid(numVal))
        {
            cout << failMsg << endl
                 << endl;
            continue;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
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

    bool isEmpty(bool printMSG = false)
    {
        printMSG &&numProd == 0 ? cout << "The inventory is currently empty." << endl : cout << "";
        return numProd == 0;
    }
    bool isFull(bool printMSG = false)
    {
        printMSG &&numProd == MAX_INV ? cout << "The inventory is full, can't add more products." << endl : cout << "";
        return numProd == MAX_INV;
    }
    int productExistsAt(const string pName, bool printFoundMSG = false, bool printNFoundMSG = false) const
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
                    printFoundMSG ? cout << "Product name already exists!" << endl : cout << "";
                    return i;
                }
            }
        }
        printNFoundMSG ? cout << "Product not found!" << endl : cout << "";
        return -1;
    }

public:
    void addProd()
    {
        if (isFull(true))
        {
            return;
        }

        Product *newProd = &prodList[numProd];
        string pName = getValidString("Enter product name: ");

        if (productExistsAt(pName, true, false) != -1)
        {
            return;
        }

        newProd->prodName = pName;
        newProd->stock += getValidNumeric<int>("Enter initial stock: ", [](int pStock)
                                               { return pStock > 0 && pStock <= MAX_STOCK; }, "Stock should be a positive value less than or equal to 50");
        newProd->price = getValidNumeric<double>("Enter initial price: ", [](double pPrice)
                                                 { return pPrice > 0; }, "Price should only be a positive value.");

        numProd++;
    }
    void showInv()
    {
        if (isEmpty(true))
        {
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
        if (isEmpty(true))
        {
            return;
        }

        string prod = getValidString("Enter the product name to be search: ");

        if (productExistsAt(prod, false, true) != -1)
        {
            prodList[productExistsAt(prod)].display();
            return;
        }
    }
    void updProd()
    {
        if (isEmpty(true))
        {
            return;
        }

        string prodName = getValidString("Enter the product name to be updated: ");

        if (productExistsAt(prodName, false, true) == -1)
        {
            return;
        }

        Product *product = &prodList[productExistsAt(prodName)];
        bool isNewNameValid = false;
        auto updProdName = [this, &product, &isNewNameValid]()
        {
            cout << "Current Product Name: " << product->prodName << endl;
            string tempName = getValidString("Enter new product name: ");

            if (this->productExistsAt(tempName, true, false) != -1)
            {
                return;
            }

            isNewNameValid = true;
            product->prodName = tempName;
            cout << "\n";
        };

        auto updStock = [&product]()
        {
            cout << "Current Stock: " << product->stock << endl;
            product->stock += getValidNumeric<int>("Enter quantity to add (negative to remove): ", [&product](int pStock)
                                                   { return pStock + product->stock > 0 && pStock + product->stock <= MAX_STOCK; }, "Stock should be a positive value less than or equal to 50");
            cout << "\n";
        };

        auto updPrice = [&product]()
        {
            cout << "Current Price: " << product->price << endl;
            product->price += getValidNumeric<double>("Enter price to add (negative to remove): ", [&product](double pPrice)
                                                      { return pPrice > 0; }, "Price should only be a positive value.");
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

        int option = getValidNumeric<int>("Enter option: ", [](int opt)
                                          { return opt > 0 && opt <= 7; }, "Choice input should only range from 1 - 7.");
        cout << "\n";
        switch (option)
        {
        case 1:
            updProdName();
            if (isNewNameValid == false)
            {
                return;
            }
            break;
        case 2:
            updStock();
            break;
        case 3:
            updPrice();
            break;
        case 4:
            updProdName();
            if (isNewNameValid == false)
            {
                return;
            }
            updStock();
            break;
        case 5:
            updProdName();
            if (isNewNameValid == false)
            {
                return;
            }
            updPrice();
            break;
        case 6:
            updStock();
            updPrice();
            break;
        case 7:
            updProdName();
            if (isNewNameValid == false)
            {
                return;
            }
            updStock();
            updPrice();
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

        option = getValidNumeric<int>("Enter option: ", [](int opt)
                                      { return opt > 0 && opt <= 5; }, "Choice input should only range from 1 - 5.");

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