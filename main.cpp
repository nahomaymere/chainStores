#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <string>
#include <vector>
#include <fstream>
#include <list>
#include <map>
#include "storechain.hpp"
#include "splitter.hpp"
#include "storedatahandler.hpp"
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





void userInterface(StoreDataHandler dataHandler){
    string user_input, firstInputWord = "", secondInputPart;
    
  
    while(1){
        cout<<"product search> ";
        getline(cin,user_input);
        Splitter wordsOfInput(user_input);
        wordsOfInput.split(' ');
        int inputWordscount = wordsOfInput.number_of_fields();
        if(user_input == "quit")
            break;
        if(inputWordscount == 1){
            if(user_input == "chains"){
                 dataHandler.printChains();
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
                 dataHandler.printChain_locations(secondInputPart);
            }
            else if(firstInputWord == "cheapest" ){

                 //Prints out the cheapest price of the product in all the known stores.
                 dataHandler.printCheapestproduct(secondInputPart);
            }
            else if( firstInputWord == "selection" && inputWordscount > 1){
                 //The products available at the specified store will be printed in alphabetical order with the prices.
                dataHandler.printStoreProducts(secondInputPart);
            }
            else
                cout<<"Error:_Inpt format is not correct."<<endl;
        }
        
    }
}


int main()
{
    StoreDataHandler dataHandler;
    string fileName = "products.txt";
    list<string> inputs = readFile(fileName);
    dataHandler.read_and_save_Data(inputs);
    userInterface(dataHandler);
    return 0;
}

