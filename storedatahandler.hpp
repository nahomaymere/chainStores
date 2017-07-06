#ifndef STOREDATAHANDLER_H
#define STOREDATAHANDLER_H
#include <string>
#include <fstream>
#include <list>
#include <map>
#include "storechain.hpp"
#include "splitter.hpp"

class StoreDataHandler
{
public:
    StoreDataHandler();
    void read_and_save_Data(list<string>data);
    void read_data(string dataString,string *product, double *product_price, StoreChain* aStore);
    void feedStoreData(StoreChain aStore,string product,double productPrice);
    void printChain_Names(string chainName);
    void printChains();
    void printChain_locations(string chainName);
    void printCheapestproduct(string product_name);
    void printStoreProducts(string store_info);
    list<StoreChain> get_storeList();
private:
    list<StoreChain> storeList;

};

#endif // STOREDATAHANDLER_H
