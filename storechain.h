#ifndef STORECHAIN_H
#define STORECHAIN_H

#include <map>
#include <string>
using namespace std;

typedef map<string,double>Products;
class StoreChain
{
    string store_name, store_location;
    Products store_products;

public:
    StoreChain();
    StoreChain( string, string, Products);
    void setStoreName(string);
    void setStoreLocation(string);
    void addProductToContainer(string,double);
    void setProductsContainer(Products);
    string getStoreName();
    string getStoreLocation();
    Products getProductContainer();
    string getAllProducts();
};

#endif // STORECHAIN_H
