#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <string>
#include <vector>
#include <fstream>
#include <list>
#include <map>
#include "storechain.h"
#include "splitter.h"
using namespace std;


list<string> readFile(string filename){
    list<string> paragrah;
    ifstream myFile;
    myFile.open(filename);
    string line;
    if(myFile.is_open()){
        while (getline(myFile,line)) {
            paragrah.push_back(line);
        }
        myFile.close();
    }
    else
        cout<<"Error:_the input file can not be read."<<endl;
    return paragrah;

}
list<StoreChain>::iterator findStore(list<StoreChain>::iterator first,
                                     list<StoreChain>::iterator last,StoreChain this_store){


    for(list<StoreChain>::iterator it = first; it != last; ++it){
        cout<<this_store.getStoreName()<<this_store.getStoreLocation()<<" : ";
        cout<<it->getStoreName()<<" "<<it->getStoreLocation()<<endl;
        if(it->getStoreName() == this_store.getStoreName()
                && it->getStoreLocation() == this_store.getStoreLocation()){
            //Found store
            return it;
        }
    }
    cout<<"did not found store "<<this_store.getStoreName()<<" "<<this_store.getStoreLocation()<<endl;

    return last;
}
list<StoreChain> processData(list<string> data){


    list<StoreChain>stores;
    double price;
    string storeName,storeLocation,the_product;
    StoreChain aStore, previous_store;
    
    for(list<string>::iterator it = data.begin(); it!= data.end();++it){

        Splitter splittedString(*it);
        
        splittedString.split(';');
        storeName = splittedString.fetch_field(0);
        storeLocation = splittedString.fetch_field(1);
        Products new_productContainer;

        aStore.setStoreLocation(storeLocation);
        aStore.setStoreName(storeName);
        price = stod(splittedString.fetch_field(3));
        the_product = splittedString.fetch_field(2);
        list<StoreChain>::iterator previous_store_it = findStore(stores.begin(),stores.end(),aStore);



        if(previous_store_it != stores.end()){
            //store already in list"
            cout<<"found store "<<previous_store_it->getStoreName()<<" "<<previous_store_it->getStoreLocation()<<" it is a dupicate"<<endl;


            //previous_store_it->addProductToContainer(the_product,price);
           // cout<<"trying to add"<<the_product<<price<<endl;
            aStore.setProductsContainer(new_productContainer);
            aStore.addProductToContainer(the_product,price);
            cout<<the_product<<" "<<price<<endl;
            stores.push_back(aStore);


        }
        else{

            //store is not in list
            cout<<"found store "<<previous_store_it->getStoreName()<<" "<<previous_store_it->getStoreLocation()<<" it is a dupicate"<<endl;

             aStore.setProductsContainer(new_productContainer);
             aStore.addProductToContainer(the_product,price);
             cout<<the_product<<" "<<price<<endl;
             stores.push_back(aStore);
        }

        
    }
    for(list<StoreChain>::iterator it = stores.begin();it != stores.end();++it){
        StoreChain currentStore = *it;
        cout<<currentStore.getStoreName()<<" "<<currentStore.getStoreLocation()<<endl;
    }
    return stores;
}

void printChain_Names(list<StoreChain> allStores, string chainName){
    list<string>chainsLocations;
    StoreChain aStore;
    for(list<StoreChain>::iterator it = allStores.begin(); it != allStores.end(); ++it){
        aStore = *it;
            if(aStore.getStoreName() == chainName)
                chainsLocations.push_back(aStore.getStoreLocation());
    }
    chainsLocations.sort();
    for(list<string>::iterator it = chainsLocations.begin(); it != chainsLocations.end(); ++it){
        cout<<*it<<endl;
    }
}

void printChains(list<StoreChain> allStores ){
    list<string>allChains;
    StoreChain oneStore;
    for(list<StoreChain>::iterator it= allStores.begin(); it != allStores.end();++it){
            oneStore = *it;
            allChains.push_back(oneStore.getStoreName());
     }
    allChains.sort();
    allChains.unique();
    for(list<string>::iterator it = allChains.begin(); it != allChains.end(); ++it){
        cout<<*it<<endl;

    }
}
void printChain_locations(list<StoreChain> allStores, string chainName){
    list<string>locations;
    StoreChain aStore;
    for(list<StoreChain>::iterator it= allStores.begin(); it != allStores.end();++it){
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
void printCheapestproduct(list<StoreChain>allStores,string product_name){
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
    for(list<StoreChain>::iterator it= allStores.begin(); it != allStores.end();++it){
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
void printStoreProducts(list<StoreChain>allStores,string store_info){
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
    for(list<StoreChain>::iterator it= allStores.begin(); it != allStores.end();++it){
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
void userInterface(list<StoreChain> allStores){
    string user_input, firstInputWord = "", secondInputPart;
    
  
    while(1){
        cout<<"product_search> ";
        getline(cin,user_input);
        Splitter wordsOfInput(user_input);
        wordsOfInput.split(' ');
        int inputWordscount = wordsOfInput.number_of_fields();
        if(user_input == "quit")
            break;
        if(inputWordscount == 1){
            if(user_input == "chains"){
                 printChains(allStores);
            }
            else
                cout<<"Error:_Input format is not correct."<<endl;
        }

        else if(inputWordscount > 1){
            firstInputWord = wordsOfInput.fetch_field(0);
            secondInputPart = "";//reseting value before appending
            for(int i = 1; i < inputWordscount; i++){
                secondInputPart += wordsOfInput.fetch_field(i);
                if(i < inputWordscount - 1)
                    secondInputPart += " ";// putting space after each word except for the last word
            }

            if(firstInputWord == "stores" && inputWordscount > 1){
                 //print all stores location under the name of chain
                 printChain_locations(allStores,secondInputPart);
            }
            else if(firstInputWord == "cheapest" ){

                 //Prints out the cheapest price of the product in all the known stores.
                 printCheapestproduct(allStores,secondInputPart);
            }
            else if( firstInputWord == "selection" && inputWordscount > 1){
                 //The products available at the specified store will be printed in alphabetical order with the prices.
                printStoreProducts(allStores,secondInputPart);
            }
            else
                cout<<"Error:_Inpt format is not correct."<<endl;
        }
        
    }
}

int test(){
    //write to file
    ofstream myfile;
    string testFileName = "testfile.txt";
    myfile.open(testFileName);
    myfile<<"S-Market;Hervantakeskus;milk;0.80\n";
    myfile<<"Prisma;Koivistonkyla;peanut_butter;2.90\n";
    myfile<<"S-Market;Hervantakeskus;milk;0.80\n";
    myfile<<"S-Market;Pirkkala;shoes;2.00\n";
    myfile<<"K-Citymarket;Linnainmaa;peanut_butter;2.80\n";
    myfile<<"S-Market;Kaukajarvi;peanut_butter;3.25\n";
    myfile<<"K-Citymarket;Pirkkala;shoes;0.95\n";
    myfile<<"K-Citymarket;Pirkkala;cheapest_in_one_place;0.95\n";
    myfile<<"Prisma;Kaleva;cheapest_in_one_place;2.95\n";
    myfile<<"K-Citymarket;Pirkkala;peanut_butter;2.90\n";
    myfile<<"Prisma;Lielahti;milk;1.90\n";
    myfile<<"K-Citymarket;Turtola;peanut_butter;4.20\n";
    myfile<<"S-Market;Kaukajarvi;cheapest_in_one_place;1.05\n";
    myfile<<"K-Citymarket;Lielahti;milk;0.95\n";
    myfile<<"K-Citymarket;Linnainmaa;milk;0.95\n";
    myfile<<"Prisma;Kaleva;milk;0.75\n";
    myfile<<"Prisma;Lielahti;peanut_butter;2.90\n";
    myfile<<"S-Market;Pirkkala;peanut_butter;2.00\n";
    myfile<<"S-Market;Pirkkala;peanut_butter;2.00\n";
    myfile<<"S-Market;Hervantakeskus;milk;1.90\n";
    myfile<<"Prisma;Koivistonkyla;milk;1.90\n";
    myfile<<"K-Citymarket;Lielahti;peanut_butter;3.00\n";
    myfile<<"K-Citymarket;Turtola;milk;0.95\n";
    myfile.close();
    //loading data
    list<string>testInputs = readFile(testFileName);
    list<StoreChain>allTestStores = processData(testInputs);
    userInterface(allTestStores);
    return 0;
}
int main()
{
   test();

    /*string fileName = "products.txt";
    list<string> inputs = readFile(fileName);
    list<StoreChain> allStores = processData(inputs);
    userInterface(allStores);*/
    return 0;
}

