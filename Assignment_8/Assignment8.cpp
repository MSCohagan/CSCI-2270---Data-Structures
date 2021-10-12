#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include "PriorityQueue.hpp"
#include "limits.h"
using namespace std;

// Michael Cohagan
// Assignment 8
// Priority Queue
// Shayon Gupta

PriorityQueue::PriorityQueue(int queueSize)
{
    //initalize queue to queue size
    priorityQueue = new PatientNode[queueSize];
    currentQueueSize = 0;
    maxQueueSize = queueSize; 
}

PriorityQueue::~PriorityQueue()
{
    delete[] priorityQueue;
}

void PriorityQueue::enqueue(string _name, int _injurySeverity, int _treatmentTime)
{
    //add to end, repairupward till good
    currentQueueSize++;
    priorityQueue[currentQueueSize].name = _name;
    priorityQueue[currentQueueSize].injurySeverity = _injurySeverity;
    priorityQueue[currentQueueSize].treatmentTime = _treatmentTime;
    for(int i = currentQueueSize; i > 0; i/=2)
    {
        repairUpward(i);
    }
}

void PriorityQueue::dequeue()
{
    //dequeue front , repair downward till good
    priorityQueue[1] = priorityQueue[currentQueueSize];
    currentQueueSize--;
    for(int i = 1; i < currentQueueSize; i*=2)
    {
        if(i != currentQueueSize && priorityQueue[i+1].injurySeverity > priorityQueue[i].injurySeverity )
        {
            i++;
        }
        repairDownward(i);
    }
}

string PriorityQueue::peekName()
{
    return priorityQueue[1].name; 
}

int PriorityQueue::peekInjurySeverity()
{
     return priorityQueue[1].injurySeverity; 
}

int PriorityQueue::peekTreatmentTime()
{
    return priorityQueue[1].treatmentTime; 
}

bool PriorityQueue::isFull()
{
    if(currentQueueSize == maxQueueSize)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool PriorityQueue::isEmpty()
{
    if(currentQueueSize == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void PriorityQueue::repairUpward(int nodeIndex)
{
    cout << "repair up" << endl;
    int i = nodeIndex;
    PatientNode tempNode = priorityQueue[i];
    int parent = i/2;
    if(nodeIndex == 1)
    {

    }
    else if(priorityQueue[i].injurySeverity < priorityQueue[parent].injurySeverity)
    {

    }
    else if(priorityQueue[i].injurySeverity > priorityQueue[parent].injurySeverity)
    {
        priorityQueue[i] = priorityQueue[parent];
        priorityQueue[parent] = tempNode;
    }
    else if(priorityQueue[i].injurySeverity == priorityQueue[parent].injurySeverity)
    {
        if(priorityQueue[i].treatmentTime < priorityQueue[parent].treatmentTime)
        {
            priorityQueue[i] = priorityQueue[parent];
            priorityQueue[parent] = tempNode;
        }
    }
    cout << priorityQueue[i].name << endl;
}


void PriorityQueue::repairDownward(int nodeIndex)
{
    cout << "repair down" << endl;
    int i = nodeIndex;
    PatientNode tempNode = priorityQueue[i];
    int l = nodeIndex * 2;
    int r = (nodeIndex * 2) + 1;
    if(l > currentQueueSize)
    {

    }
    // left severity higher
    else if(priorityQueue[l].injurySeverity > priorityQueue[r].injurySeverity && priorityQueue[l].injurySeverity > priorityQueue[i].injurySeverity)
    {
        priorityQueue[i] = priorityQueue[l];
        priorityQueue[l] = tempNode;
    }
    // right severity higher
    else if(priorityQueue[r].injurySeverity > priorityQueue[l].injurySeverity && priorityQueue[r].injurySeverity > priorityQueue[i].injurySeverity)
    {
        priorityQueue[i] = priorityQueue[r];
        priorityQueue[r] = tempNode;
    }
    // severity is the same, test treatment time
    else if(priorityQueue[r].injurySeverity == priorityQueue[l].injurySeverity && priorityQueue[r].injurySeverity > priorityQueue[i].injurySeverity)
    {
        // right treatment time is higher
        if(priorityQueue[r].treatmentTime < priorityQueue[l].treatmentTime)
        {
            priorityQueue[i] = priorityQueue[r];
            priorityQueue[r] = tempNode;
        }
        // left treatment time is higher
        else if(priorityQueue[l].treatmentTime < priorityQueue[r].treatmentTime)
        {
            priorityQueue[i] = priorityQueue[l];
            priorityQueue[l] = tempNode;
        }
    }
    // injury severity is the same right but higher left
    else if(priorityQueue[r].injurySeverity == priorityQueue[i].injurySeverity && priorityQueue[l].injurySeverity > priorityQueue[i].injurySeverity)
    {   
        priorityQueue[i] = priorityQueue[l];
        priorityQueue[l] = tempNode;
    }
    else if(priorityQueue[l].injurySeverity == priorityQueue[i].injurySeverity && priorityQueue[r].injurySeverity > priorityQueue[i].injurySeverity)
    {
        priorityQueue[i] = priorityQueue[r];
        priorityQueue[r] = tempNode;
    }
    else if(priorityQueue[l].injurySeverity < priorityQueue[i].injurySeverity && priorityQueue[l].injurySeverity == priorityQueue[r].injurySeverity)
    {
        //cout << "we in that crazy else if man" << endl;
        if(priorityQueue[l].treatmentTime < priorityQueue[i].treatmentTime && priorityQueue[r].treatmentTime > priorityQueue[l].treatmentTime)
        {
            priorityQueue[i] = priorityQueue[l];
            priorityQueue[l] = tempNode;
        }
        else if(priorityQueue[l].treatmentTime < priorityQueue[i].treatmentTime && priorityQueue[r].treatmentTime < priorityQueue[l].treatmentTime)
        {
            priorityQueue[i] = priorityQueue[r];
            priorityQueue[r] = tempNode;
        }
        else
        {
            
        }
    }
     cout << priorityQueue[i].name << endl;
}


//Your main function should create an instance of the priority queue 
//class with the size that is passed in as a command line argument
//It should then repeatedly display a menu to the user just like in
//previous labs.
int main(int argc, char* argv[]){

    PriorityQueue patientList(stoi(argv[1]));
    bool isRunning = true;
    int totalTreatmentTime = 0; 
    while(isRunning)
    {
        cout << "======Main Menu======" << endl;
        cout << "1. Get Patient Information from File" << endl;
        cout << "2. Add Patient to Priority Queue" << endl;
        cout << "3. Show Next Patient" << endl;
        cout << "4. Treat Next Patient" << endl;
        cout << "5. Treat Entire Queue" << endl;
        cout << "6. Quit" << endl;
        string answer;
        getline(cin , answer);
        int menuAnswer = stoi(answer);
        if(menuAnswer == 1)
        {
            cout << "Enter filename: " << endl;
            string response;
            getline(cin, response);
            ifstream inFile;
            inFile.open(response);
            if(inFile.is_open())
            {
                string currentLine;
                string name, injurySeverity, treatmentTime;
                while(getline(inFile,currentLine))
                {
                    if(patientList.isFull())
                    {
                        cout << "Priority Queue full. Send remaining patients to another hosptial." << endl;
                    }
                    else
                    {
                        stringstream ss(currentLine);
                        getline(ss, name, ' ');
                        getline(ss, injurySeverity, ' ');
                        getline(ss, treatmentTime, ' ');
                        patientList.enqueue(name, stoi(injurySeverity), stoi(treatmentTime));
                    }
                }
            }
            else
            {
                cout << "File failed to open" << endl;
            }
            isRunning = true;
        }
        else if(menuAnswer == 2)
        {
            if(patientList.isFull())
            {
                cout << "Priority Queue full. Send Patient to another hospital." << endl;
                isRunning = true;
            }
            else
            {
                string name;
                string severity;
                string treatmentTime;
                cout << "Enter Patient Name: " << endl;
                getline(cin, name);
                cout << "Enter Injury Severity: " << endl;
                getline(cin , severity);
                cout << "Enter Treatment Time: " << endl;
                getline(cin , treatmentTime);
                int SV = stoi(severity);
                int TT = stoi(treatmentTime);
                patientList.enqueue(name, SV, TT);
                isRunning = true;
            }
        }
        else if(menuAnswer == 3)
        { 
            if(patientList.isEmpty())
            {
                cout << "Queue empty" << endl;
                isRunning = true;
            }
            else
            {
                string patientName = patientList.peekName();
                int patientInjurySeverity = patientList.peekInjurySeverity();
                int patientTreatmentTime = patientList.peekTreatmentTime();
                cout << "Patient Name: " << patientName << endl;
                cout << "Injury Severity: " << patientInjurySeverity << endl;
                cout << "Treatment Time: " << patientTreatmentTime << endl;
                isRunning = true;
            }
        }
        //dequeue once
        else if(menuAnswer == 4)
        {
            if(patientList.isEmpty())
            {
                cout << "Queue empty." << endl;
                isRunning = true;
            }
            else
            {
                string patientName = patientList.peekName();
                totalTreatmentTime = totalTreatmentTime + patientList.peekTreatmentTime();
                patientList.dequeue();
                cout << "Patient Name: " << patientName << " - Total Time Treating Patients: " << totalTreatmentTime << endl;
                isRunning = true;
            }
        }
        //dequeue whole list
        else if(menuAnswer == 5)
        {
            if(patientList.isEmpty())
            {
                cout << "Queue empty." << endl;
                isRunning = true;
            }
            else
            {
                bool condition;
                while(condition == false)
                {
                    string patientName = patientList.peekName();
                    totalTreatmentTime = totalTreatmentTime + patientList.peekTreatmentTime();
                    patientList.dequeue();
                    cout << "Patient Name: " << patientName << " - Total Time Treating Patients: " << totalTreatmentTime << endl;
                    condition = patientList.isEmpty();
                }   
            }
            isRunning = true;
        }
        else if(menuAnswer == 6)
        {
            cout << "Goodbye!" << endl;
            isRunning = false;
        }
        else
        {
            isRunning = true;
        }
    }
}