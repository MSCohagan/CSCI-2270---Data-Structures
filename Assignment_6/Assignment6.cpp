#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "MovieTree.hpp"

using namespace std;

//Michael Cohagan
//Assignment 6 
//October 2018


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

int countMoviesHelper(MovieNode* currentNode, int count){
    if(currentNode!=nullptr){
        //cout << "if statement" << endl;
        count+=1;
        //cout << "count = " << count << endl;
        count = countMoviesHelper(currentNode->leftChild, count);
        count = countMoviesHelper(currentNode->rightChild, count);
    }
    return count;
}

void MovieTree::countMovies(){
    MovieNode* currentNode = root;
    int count = countMoviesHelper(currentNode, count);
    cout << "Count = " << count << endl;
}

MovieNode* MovieTree::search(string title){
    MovieNode* currentNode = root;
    while(currentNode!=nullptr && currentNode->title != title){
        if(currentNode->title > title){
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
            newNode->parent = currentNode;
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
            newNode->parent = currentNode;
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

MovieNode* deleteMovieHelper(MovieNode* currentNode){
    if (currentNode == nullptr){
        return nullptr;
    }
    while(currentNode->leftChild != nullptr){
        currentNode = currentNode->leftChild;
    }
    return currentNode;
}

void MovieTree::deleteMovie(string title){
    MovieNode* currentNode = search(title);
    if(currentNode==nullptr){
        cout << "Movie not found." << endl;
    }
    //Right child null
    else if(currentNode->leftChild != nullptr && currentNode->rightChild == nullptr){
        MovieNode* temp = currentNode;
        if (currentNode->parent != nullptr && currentNode == currentNode->parent->leftChild){
            currentNode->parent->leftChild = currentNode->leftChild;
        }
        else if(currentNode->parent != nullptr && currentNode == currentNode->parent->rightChild){
            currentNode->parent->rightChild = currentNode->leftChild;
        }
        else{
            root = currentNode->leftChild;
        }
        currentNode->leftChild->parent = currentNode->parent;
        currentNode = currentNode->leftChild; 
        delete temp;
    }
    //Left child null
    else if(currentNode->leftChild == nullptr && currentNode->rightChild != nullptr){
        MovieNode* temp = currentNode;
        if (currentNode->parent != nullptr && currentNode == currentNode->parent->leftChild){
            currentNode->parent->rightChild = currentNode->rightChild;
        }
        else if(currentNode->parent != nullptr && currentNode == currentNode->parent->rightChild){
            currentNode->parent->rightChild = currentNode->rightChild;
        }
        else{
            root = currentNode->rightChild;
        }
        currentNode->rightChild->parent = currentNode->parent;
        currentNode = currentNode->rightChild; 
        delete temp;
    }
    //Both children are null
      else if(currentNode->leftChild == nullptr && currentNode->rightChild == nullptr){
        if(currentNode->parent != nullptr && currentNode == currentNode->parent->leftChild){
            currentNode->parent->leftChild = nullptr;
        }
        else if(currentNode->parent != nullptr && currentNode == currentNode->parent->rightChild){
            currentNode->parent->rightChild = nullptr;
        }
        else{
            root = nullptr;
        }
        delete currentNode;
    }
    //Both children aren't null
    else{
        // if(currentNode == currentNode->parent->leftChild && currentNode->parent != nullptr){
        //     MovieNode* temp = deleteMovieHelper(root);
        //     temp->rightChild = currentNode->rightChild;
        //     temp->leftChild = currentNode->leftChild;
        //     if (currentNode->parent != nullptr){
        //         temp->parent = currentNode->parent;
        //         currentNode->parent->leftChild = temp;
        //         currentNode->rightChild->parent = temp;
        //         currentNode->leftChild->parent = temp;
        //     }
        //     else{
        //         temp->parent = nullptr;
        //         currentNode->rightChild->parent = temp;
        //         currentNode->leftChild->parent = temp;
        //     }
        // }
        // else if(currentNode == currentNode->parent->rightChild && currentNode->parent != nullptr){
        //     MovieNode* temp = deleteMovieHelper(root);
        //     temp->rightChild = currentNode->rightChild;
        //     temp->leftChild = currentNode->leftChild;
        //     if (currentNode->parent != nullptr){
        //         temp->parent = currentNode->parent;
        //         currentNode->parent->rightChild = temp;
        //         currentNode->rightChild->parent = temp;
        //         currentNode->leftChild->parent = temp;
        //     }
        //     else{
        //         temp->parent = nullptr;
        //         currentNode->rightChild->parent = temp;
        //         currentNode->leftChild->parent = temp;
        //     }
        // }
        //else{
            MovieNode* temp = deleteMovieHelper(currentNode->rightChild);
            currentNode->ranking = temp->ranking;
            currentNode->title = temp->title;
            currentNode->year = temp->year;
            currentNode->quantity = temp->quantity;
            if(temp == temp->parent->rightChild){
                temp->parent->rightChild = temp->rightChild;
            }
            else if(temp == temp->parent->leftChild){
                temp->parent->leftChild = temp->rightChild;
            }
            if (temp->rightChild != nullptr){
				temp->rightChild->parent = temp->parent;
			}
            delete temp;
        //}
        
        // delete currentNode;
    }
}

//Rent a movie (Option 2)
void MovieTree::rentMovie(string title){
    MovieNode* currentNode = search(title);
    if(currentNode != nullptr){
        if(currentNode->quantity == 0){
            cout << "Movie out of stock." << endl;
        }
        else{
            cout << "Movie has been rented." << endl;
            currentNode->quantity = currentNode->quantity-1;
            cout << "Movie Info:" << endl;
            cout << "===========" << endl;
            cout << "Ranking:" << currentNode->ranking << endl;
            cout << "Title:" << currentNode->title << endl;
            cout << "Year:" << currentNode->year << endl;
            cout << "Quantity:" << currentNode->quantity << endl;
            if(currentNode->quantity == 0){
                deleteMovie(title);
            }
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
    if(inFile.is_open())
    {
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