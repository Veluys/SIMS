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

    friend class Inventory;
};
class Inventory
{
    Product prodList[MAX_INV];
    int numProd = 0;
};

int main()
{
}