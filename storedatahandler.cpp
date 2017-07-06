#include "storedatahandler.hpp"
#include "iostream"
#include <iomanip>

using namespace std;


StoreDataHandler::StoreDataHandler(){

}
list<StoreChain>::iterator findStore(list<StoreChain>::iterator first,list<StoreChain>::iterator last,StoreChain this_store){


    for(list<StoreChain>::iterator it = first; it != last; ++it){
        if(it->getStoreName() == this_store.getStoreName()
                && it->getStoreLocation() == this_store.getStoreLocation()){
            //Found store
            return it;
        }
    }

    return last;
}
void StoreDataHandler::read_data(string dataString,string *product, double *product_price, StoreChain* aStorePtr){
    //read a data string
    string storeName,storeLocation;
    
    Splitter splittedString(dataString);
    splittedString.split(';');
    storeName = splittedString.fetch_field(0);
    storeLocation = splittedString.fetch_field(1);
    *product = splittedString.fetch_field(2);
    *product_price = stod(splittedString.fetch_field(3));
    aStorePtr->setStoreName(storeName);
    aStorePtr->setStoreLocation(storeLocation);

}
void StoreDataHandler::read_and_save_Data(list<string>data){
    //read Data
    double product_price;
    string storeName,storeLocation,product;
    StoreChain aStore;

    for(list<string>::iterator it = data.begin(); it!= data.end();++it){
        string dataString = *it;
        read_data(dataString, &product, &product_price, &aStore);
        feedStoreData(aStore, product, product_price);
    }

}

void StoreDataHandler::feedStoreData(StoreChain aStore,string product,double productPrice){
    //update data to storelist
    StoreChain existingStore;
    list<StoreChain>::iterator existingStore_it = findStore(storeList.begin(),storeList.end(),aStore);
    //if store exist, update list
    if(existingStore_it != storeList.end()){        
        existingStore_it->addProductToContainer(product,productPrice);
    }
    //else add new store to list
    else{
        aStore.addProductToContainer(product, productPrice);
        storeList.push_back(aStore);
    }

}
list<StoreChain> StoreDataHandler::get_storeList(){

    return storeList;
}
void StoreDataHandler::printChain_Names(string chainName){
    list<string>chainsLocations;
    StoreChain aStore;
    for(list<StoreChain>::iterator it = storeList.begin(); it != storeList.end(); ++it){
        aStore = *it;
            if(aStore.getStoreName() == chainName)
                chainsLocations.push_back(aStore.getStoreLocation());
    }
    chainsLocations.sort();
    for(list<string>::iterator it = chainsLocations.begin(); it != chainsLocations.end(); ++it){
        cout<<*it<<endl;
    }
}
void StoreDataHandler::printChains(){
    list<string>allChains;
    StoreChain oneStore;
    for(list<StoreChain>::iterator it= storeList.begin(); it != storeList.end();++it){
            oneStore = *it;
            allChains.push_back(oneStore.getStoreName());
     }
    allChains.sort();
    allChains.unique();
    for(list<string>::iterator it = allChains.begin(); it != allChains.end(); ++it){
        cout<<*it<<endl;

    }
}
void StoreDataHandler::printChain_locations(string chainName){
    list<string>locations;
    StoreChain aStore;
    for(list<StoreChain>::iterator it= storeList.begin(); it != storeList.end();++it){
        aStore = *it;
        if(aStore.getStoreName() == chainName)
            locations.push_back(aStore.getStoreLocation());
     }
    if(locations.size() == 0){
        cout<<"Error:_Store name is not correct."<<endl;
        return;
    }
    locations.sort();
    locations.unique();
    for(list<string>::iterator it = locations.begin(); it != locations.end(); ++it){
        cout<<*it<<endl;
    }
}
void StoreDataHandler::printCheapestproduct(string product_name){
    list<string>storesNames;
    StoreChain aStore;
    string aStoreName;
    Products aStore_Products;
    double minPrice = -1.0;
    double productPrice = -1.0;
    bool productIsInStores = false;

    Splitter wordsList(product_name);
    wordsList.split(' ');
    int inputWordsListcount = wordsList.number_of_fields();
    if(inputWordsListcount > 1){
        cout<<"Error: command not allowed for more than one product"<<endl;
        return;
    }
    for(list<StoreChain>::iterator it= storeList.begin(); it != storeList.end();++it){
        aStore = *it;
        aStore_Products = aStore.getProductContainer();
        Products::iterator productIterator = aStore_Products.find(product_name);
        if(productIterator != aStore_Products.end() ){
            //found Product
            productIsInStores = true;
            productPrice = productIterator->second;
            aStoreName = aStore.getStoreName() + " " + aStore.getStoreLocation();

            if(minPrice == -1){
                //first round
                minPrice = productPrice;
                storesNames.push_back(aStoreName);
            }
            else if(minPrice > productPrice ){
                minPrice = productPrice;
                storesNames.clear();
                storesNames.push_back(aStoreName);
            }
            else if(minPrice == productPrice){
                storesNames.push_back(aStoreName);
            }


        }
    }
    if(productIsInStores){
        cout<<fixed<<setprecision(2)<<minPrice<<endl;
        storesNames.sort();
        storesNames.unique();
        for(list<string>::iterator it = storesNames.begin(); it != storesNames.end(); ++it)
            cout<<*it<<endl;
    }
    else
        cout<<"This product is not available anywhere."<<endl;
}

void StoreDataHandler::printStoreProducts(string store_info){
    StoreChain aStore;
    string products;
    string store_location;
    string store_chainName;
    bool storeFound = false;
    Splitter wordsList(store_info);
    wordsList.split(' ');
    int inputWordsListcount = wordsList.number_of_fields();
    if(inputWordsListcount < 2){
         cout<<"Error:_Store name or location is not correct."<<endl;
         return;
    }
    store_chainName = wordsList.fetch_field(0);

    for(int i = 1; i < inputWordsListcount; i++)
        store_location.append(wordsList.fetch_field(i));
    for(list<StoreChain>::iterator it= storeList.begin(); it != storeList.end();++it){
        aStore = *it;
        if(store_chainName == aStore.getStoreName()
            && store_location == aStore.getStoreLocation()){
            products = aStore.getAllProducts();
            storeFound = true;
            break;
        }


    }
    if(storeFound)
        cout<<products;
    else
        cout<<"Error:Store name or location is not correct"<<endl;

}





