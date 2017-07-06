

#include "storechain.hpp"
#include <iomanip>
#include <string>
#include <sstream>
using namespace std;

StoreChain::StoreChain(){

}
StoreChain::StoreChain(string name, string location, Products productsContainer){
   store_name = name;
   store_location = location;
   store_products = productsContainer;
}

void StoreChain::setStoreName(string name){
    store_name = name;
}
void StoreChain::setStoreLocation(string location){
    store_location = location;
}
void StoreChain::setProductsContainer(Products allProducts){
    store_products = allProducts;
}
void StoreChain::addProductToContainer(string productName, double price){
        store_products[productName] = price;
}
string StoreChain::getStoreName(){
    return store_name;
}
string StoreChain::getStoreLocation(){
    return store_location;
}
Products StoreChain::getProductContainer(){
    return store_products;
}
string StoreChain::getAllProducts(){
    stringstream stream;
    string productDisplay;

    for(Products::iterator it = store_products.begin(); it != store_products.end(); ++it ){
            productDisplay += it->first +" ";
            stream<<fixed<<setprecision(2)<<it->second<<"\n";
            productDisplay += stream.str();
            stream.str(string());// clearing my stream

    }
    return productDisplay;
}

