// Homework 3 2018 - Fall Semester
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include "CommunicationNetwork.h"

using namespace std;

void printMenu(){
    // Main Menu
    cout << "======Main Menu======" << endl;
    cout << "1. Build Network" << endl;
    cout << "2. Print Network Path" << endl;
    cout << "3. Transmit Message Coast-To-Coast" << endl;
    cout << "4. Add City" << endl;
    cout << "5. Quit" << endl;
}
void deleteList(city *head){
    // start at the head
    city* currentNode = head;
    city* tmpNode;
    while(currentNode != nullptr){
        tmpNode = currentNode->next;
        //cout << "deleting node " << currentNode->cityName << endl;
        delete currentNode;
        currentNode = tmpNode;
    }
}

void printPath(city* head){
    // Print list beginning at the head and going
    // until the current pointer is nullptr
    city *current = head;
    cout << "===CURRENT PATH===" << endl;
    while(current != nullptr){
        //cout << current->cityName << endl;
        cout << current->cityName << " -> ";
        current = current->next;
        // if(current == nullptr){
        //     break;
        // }
    }
    cout << " NULL" << endl;
    cout << "==================" << endl;

}

// Transmits message from city to city
// word by word
void transmitMessage(city* head){
    ifstream inFile;
    inFile.open("messageIn.txt");
    if(inFile.is_open()){
        string currentWord;
        city* currentNode;
        while(inFile >> currentWord){
            currentNode = head;
            while(currentNode != nullptr){
                //cout << currentNode->cityName << endl;
                currentNode->message = currentWord;
                cout << currentNode->cityName << " " << "received " << currentNode->message << endl;
                currentNode->next->message=currentWord;
                currentNode->message = " ";
                currentNode = currentNode->next;
                // For some reason, code hits a seg fault without breaking here
                // this seems to work
                if(currentNode->next == nullptr){
                    cout << currentNode->cityName << " " << "received " << currentNode->message << endl;
                    break;
                }
            } 
        }
        inFile.close();
    }
    else{
        cout << "Failed to open file. " << endl;
    }

}

city *createNode(string initName, city *initNext, string initMessage){
    // Each city is a struct and contains three pieces and each must be
    // initialized seperately
    city* newNode = new city;
    newNode->name = initName;
    newNode->next = initNext;
    newNode->message = initMessage;
    return newNode; 
}

city *addCity(city *head, city *previous, string name){
    city *newCity = createNode(name,nullptr,"");
    if(previous != nullptr){
        if(head == previous){
            cout << "prev: " << head->name << " ";
            newCity->next = head->next;
            head->next = newCity;
            cout << "new: " << newCity->name << endl; 
        }
        else{
            cout << "prev: " << previous->name << " ";
            newCity->next=previous->next;
            previous->next = newCity;
            cout << "new: " << newCity->name << endl;
        }
    }
    else if(head == nullptr){
        head = newCity;
    }
    else{
        newCity->next = head;
        head = newCity;
    }
    return head;
}

// For use in building the list
bool insertNodeAtEnd(city* head, string cityName){
    city* newNode = createNode(cityName,nullptr,"");
    if (head == nullptr){
        head = newNode;
    }
    else {
        city* currentNode = head;
        while(currentNode->next != nullptr) {
            currentNode = currentNode->next;
        }
        currentNode->next = newNode; 
    }
    // Should not be a case where this returns false
    return true;
}

city *buildNetwork(){
    // Building network with given list of cities
    // Los Angeles is the first city and therefore
    // the head
    city * head = createNode("Los Angeles", nullptr, "");
    string cities[9];
    cities[0] = "Phoenix";
    cities[1] = "Denver";
    cities[2] = "Dallas";
    cities[3] = "St. Louis";
    cities[4] = "Chicago";
    cities[5] = "Atlanta";
    cities[6] = "Washington, D.C.";
    cities[7] = "New York";
    cities[8] = "Boston";
    // Add cities in the array to linked list
    for(int i = 0; i < 9; i++){
        insertNodeAtEnd(head,cities[i]);
        //cout << "Current City: " << cities[i] << endl;
    }
    return head;
}


int main(int argc, char* argv[]){
    // Initialize head to access list
    city * head;
    // Condition for running the menu
    bool response = true;
    // Menu continues to run so long as the user has not quit
    while(response == true){
        printMenu();
        //cout << "Enter a command" << endl;
        string answer;
        cin >> answer;
        // Build list 
        if(answer == "1"){
            //cout << "Building Network" << endl;
            head = buildNetwork();
        }
        // Print list
        else if(answer == "2"){
            printPath(head);
        }
        // Transmit message
        else if(answer == "3"){
            transmitMessage(head);
        }
        // Add city
        else if(answer == "4"){
            cin.ignore();
            city *currentNode = new city;
            *currentNode = *head;
            string cityOne;
            string cityTwo;
            cout << "Enter a City name: " << endl;
            getline(cin, cityOne);
            cout << "Enter a previous City name:  " << endl;
            getline(cin, cityTwo);
            if(cityTwo == head->cityName){
                addCity(head,head,cityOne);
            }
            else{
                while(currentNode->cityName != cityTwo){
                    currentNode = currentNode->next;
                }
                if(currentNode != nullptr){
                    addCity(head, currentNode, cityOne);
                }
                
            }
            //delete currentNode;  
        }
        // Quit
        else if(answer == "5"){
            deleteList(head);
            cout << "Goodbye!" << endl;
            response = false;
        }
        else{
            cout << "Response not recognized, please try again" << endl;
            response = true;
        }
    }

}