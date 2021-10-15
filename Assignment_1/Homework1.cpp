/*
Michael Cohagan
Assignment 1
Zietz
*/

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
using namespace std;

//Initialize struct for item typing
//Later used to make an array of structs
struct Item{
    string type;
    string status;
    int price;
};

void OutPut(Item itemArray[], int numElements){
    for(int i=0;i<numElements;i++){
        if(itemArray[i].status == " for sale"){
            cout<<itemArray[i].type << ", "<< "for sale"<< ", " <<itemArray[i].price << endl;
        }
        else{
            cout<<itemArray[i].type << ", " << "wanted" << ", " <<itemArray[i].price << endl;
        }
    }
}

int main(int argc, char** argv){
    //Initialize itemArray to store matches
    Item itemArray[100];
    //File in, argument 1 from the command line
    ifstream inFile;
    inFile.open(argv[1]);
    string info;
    //numElements is saved to be passed in to OutPut function for printing
    //incremented whenever i is incremented
    int numElements = 0;
    if(inFile.is_open()){
        int i = 0; 
        while(getline(inFile, info)){
            //Stringstream to parse strings from file
            stringstream ss(info);
            //Initalize values for string objects from struct
            string type, status, price = "";
            getline(ss, type, ',');
            getline(ss, status, ',');
            getline(ss, price, ',');
            itemArray[i].type = type;
            itemArray[i].status = status;
            itemArray[i].price = stoi(price);
            //Second loop to check current input against all previous inputs
            for(int j=0; j<=i; j++){
                //This if statement serves to evaluate a case where an exact match occurs 
                if(itemArray[j].type == itemArray[i].type && itemArray[j].status != itemArray[i].status){
                    //Check case where item in j-th position is the for sale item
                    if(itemArray[j].status == " for sale" && itemArray[j].price <= itemArray[i].price){
                        cout << itemArray[j].type << " " << itemArray[j].price << endl;
                        //Delete Algorithm moves all indicies currently located to the right of j to the left
                        for(int x = j; x<i; x++){
                            itemArray[x] = itemArray[x+1];
                        }
                        i-=2;
                        numElements-=2;
                        //Break to exit for loop
                        break;
                    }
                    //Check case where item in the i-th position is the for sale item
                    else if(itemArray[i].status == " for sale" && itemArray[i].price <= itemArray[j].price){
                        cout << itemArray[i].type << " " << itemArray[i].price << endl;
                        //Delete Algorithm moves all indicies currently located to the right of j to the left
                        for(int x = j; x<i; x++){
                            itemArray[x] = itemArray[x+1];
                        }
                        i-=2;
                        numElements-=2;
                        break;
                    }
                }
            }
            i++;
            numElements++;
        }
    }
    else{
        cout << "File failed to open. " << endl; 
    }
    cout << "#" << endl;
    OutPut(itemArray,numElements);
    cout << "#" << endl;
    inFile.close();
}