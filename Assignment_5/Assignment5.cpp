#include <iostream>
#include "HW5-MovieTree.hpp"
#include <string>
#include <sstream>
#include <fstream>
using namespace std;
// Assignemnt 5
// Michael Scott Cohagan
// October 2018

MovieTree::MovieTree(){
    root = nullptr;
};

//In order traversal helper function
void destructorHelper(MovieNode* currentNode){
    if(currentNode!=nullptr){
        destructorHelper(currentNode->leftChild);
        destructorHelper(currentNode->rightChild);
        delete currentNode;
    }

}

MovieTree::~MovieTree(){
    destructorHelper(root);
};



MovieNode* MovieTree::search(string title){
    MovieNode* currentNode = root;
    while(currentNode!=nullptr && currentNode->title != title){
        if(currentNode->title < title){
            currentNode = currentNode->leftChild; 
        }
        else{
           currentNode = currentNode->rightChild;
        }

    }
    /*Return state for RentMovie/FindMovie indicating if movie is in 
    system or not*/
    if(currentNode!= nullptr){
        return currentNode;
    }
    else{
        return nullptr;
    }
}

//Search tree till nullptr
//This is a helper function intended to work alongside addMovieNode
//Will search the tree to find where newNode is intended to go
void addMovieSearch(MovieNode* currentNode, MovieNode* newNode){
    if(newNode->title < currentNode->title){
        //cout << newNode->title << " " << currentNode->title << endl;
        //currentNode = currentNode->leftChild;
        if(currentNode->leftChild == nullptr){
            //newNode->parent = currentNode;
            //currentNode = newNode;
            //cout << "inner if" << endl;
            currentNode->leftChild = newNode;
            newNode->leftChild = newNode->rightChild = nullptr;
        }
        else{
            //cout << "inner else" << endl;
            currentNode = currentNode->leftChild; 
            addMovieSearch(currentNode, newNode);
        }
    }
    else{
        //currentNode = currentNode->rightChild;
        if(currentNode->rightChild == nullptr){
            // newNode->parent = currentNode;
            // currentNode = newNode;
            currentNode->rightChild = newNode;
            newNode->leftChild = newNode->rightChild = nullptr;
        }
        else{ 
            currentNode = currentNode->rightChild;
            addMovieSearch(currentNode, newNode);
        }
    }
}

//Add a Node to the BST 
void MovieTree::addMovieNode(int ranking, string title, int year, int quantity){
    // Initialize new node
    MovieNode* newNode = new MovieNode;
    newNode->ranking = ranking;
    newNode->title = title;
    newNode->year = year;
    newNode->quantity = quantity;
    if(root == nullptr){
        root = newNode;
        newNode->leftChild = newNode->rightChild = nullptr;
    }
    else{
        //cout << "in the else staement" << endl;
        MovieNode* currentNode = root;
        addMovieSearch(currentNode, newNode);
    }
}

//In order traversal helper function
void printHelper(MovieNode* currentNode){
    if(currentNode!=nullptr){
        printHelper(currentNode->leftChild);
        cout << "Movie: " << currentNode->title << " " << currentNode->quantity << endl;
        printHelper(currentNode->rightChild);
    }

}

//Print Movie Inventory (Option 3)
void MovieTree::printMovieInventory(){
    MovieNode* currentNode = root; 
    printHelper(currentNode);

}

//Rent a movie (Option 2)
void MovieTree::rentMovie(string title){
    MovieNode* currentNode = search(title);
    if(currentNode != nullptr){
        if(currentNode->quantity == 0){
            cout << "Movie out of stock." << endl;
        }
        if(currentNode->quantity != 0){
            cout << "Movie has been rented." << endl;
            currentNode->quantity = currentNode->quantity-1;
            cout << "Movie Info:" << endl;
            cout << "===========" << endl;
            cout << "Ranking:" << currentNode->ranking << endl;
            cout << "Title:" << currentNode->title << endl;
            cout << "Year:" << currentNode->year << endl;
            cout << "Quantity:" << currentNode->quantity << endl;
        }
        
    }
    else{
        cout << "Movie not found." << endl;
    }
}

//Find a movie (Option 1)
void MovieTree::findMovie(string title){
    MovieNode* currentNode = search(title);
    if(currentNode != nullptr){
        cout << "Movie Info:" << endl;
        cout << "===========" << endl;
        cout << "Ranking:" << currentNode->ranking << endl;
        cout << "Title:" << currentNode->title << endl;
        cout << "Year:" << currentNode->year << endl;
        cout << "Quantity:" << currentNode->quantity << endl;
    }
    else{
        cout << "Movie not found." << endl;
    }
}


// menu function 
void menu(MovieTree tree){
    // String for user input
    string response;
    bool endState = false;
    while(endState == false){
        cout << "======Main Menu======" << endl;
        cout << "1. Find a movie" << endl;
        cout << "2. Rent a movie" << endl;
        cout << "3. Print the inventory" << endl;
        cout << "4. Quit" << endl;
        getline(cin, response);
        if(response == "1"){
            string answer;
            cout << "Enter title:" << endl;
            getline(cin,answer);
            tree.findMovie(answer);
            endState = false;
        }
        else if(response == "2"){
            string answer;
            cout << "Enter title:" << endl;
            getline(cin,answer);
            tree.rentMovie(answer);
            endState = false;
        }
        else if (response == "3"){
            tree.printMovieInventory();
            endState = false;
        }
        else if(response == "4"){
            cout << "Goodbye!" << endl;
            endState = true;
        }
        else{
            // reprint options 
            endState = false;
        }
    }    
}

int main(int argc, char* argv[]){
    // Open file for building tree
    MovieTree tree;
    ifstream inFile;
    inFile.open(argv[1]);
    if(inFile.is_open()){
        string currentLine;
        string rank, year, qty, title;
        while(getline(inFile, currentLine)){
            stringstream ss(currentLine);
            getline(ss, rank, ',');
            getline(ss, title, ',');
            getline(ss, year, ',');
            getline(ss, qty, ',');
            tree.addMovieNode(stoi(rank),title,stoi(year),stoi(qty));
        }
        menu(tree);
    }
    else{
        cout << "Input file failed to open" << endl;
    }
    // Close input file
    inFile.close();
}