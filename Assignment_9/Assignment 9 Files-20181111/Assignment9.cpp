#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <queue>
#include "Graph.hpp"
using namespace std;

// Michael Cohagan
// Assignment 9
// Fall 2018 - Gupta

Graph::Graph(){};

Graph::~Graph(){};

void Graph::addEdge(string v1, string v2, int distance)
{
    // Add edge from v1 to v2
    //cout << v1 << endl;
    //cout << v2 << endl;
    Edge newEdge;
    newEdge.v = Graph::findVertex(v2);
    newEdge.distance = distance;
    vertex* temp = Graph::findVertex(v1);
    temp->Edges.push_back(newEdge);
}

void Graph::addVertex(string name)
{
    vertex newVertex;
    newVertex.name = name;
    newVertex.district = 0;
    newVertex.visited = false;
    vertices.push_back(newVertex);
}

void Graph::displayEdges()
{
    vertex* temp;
    for(int i = 0; i < vertices.size(); i++)
    {
        temp = &(vertices[i]);
        cout << temp->district << ":" << temp->name << "-->";
        for(auto edge = temp->Edges.begin(); edge != temp->Edges.end(); edge++)
        {
            if(edge != temp->Edges.end()-1)
            {
                cout << (edge->v)->name << " (" << edge->distance << " miles)" << "***";
            }
            else
            {
                cout << (edge->v)->name << " (" << edge->distance << " miles)";
            }
        }
        cout << endl;
    }
}

void Graph::assignDistricts()
{
    int district = 1;
    for(int i = 0; i < vertices.size(); i++)
    {
        if(vertices[i].visited == false)
        {
            vertices[i].visited = true;
            BFTraversalLabel(vertices[i].name, district);
            district++;
        }
    }
}

void Graph::printDFS()
{
    setAllVerticesUnvisited();
    for(int i = 0; i < vertices.size(); i++)
    {
        if(!vertices[i].visited)
        {
            DFTraversal(&vertices[i]);
        }
    }
}


void Graph::setAllVerticesUnvisited()
{
    for(int i = 0; i < vertices.size(); i++)
    {
        vertices[i].visited = false;
    }
}

vertex *Graph::findVertex(std::string name)
{
    vertex* temp = NULL;
    for(int i = 0; i < vertices.size(); i++)
    {
        if(vertices[i].name == name)
        {
            temp = &vertices[i];
            return temp;
        }
    }
    return temp;
}


void Graph::BFTraversalLabel(string startingCity, int distID){
  queue<vertex*> queue;
  vertex* root = findVertex(startingCity);
  root->visited = true;
  root->district = distID;
  queue.push(root);
  while(!queue.empty()){
    root = queue.front();
    queue.pop();
    for(auto edge = root->Edges.begin(); edge != root->Edges.end(); edge++){
      if(!edge->v->visited){
        edge->v->district = distID;
        edge->v->visited = true;
        queue.push(edge->v);
      }
    }
  }
}

void Graph::DFTraversal(vertex* v)
{
    v->visited = true;
    cout << v->name << endl;
    for(int i = 0; i < v->Edges.size(); i++)
    {
        if(!v->Edges[i].v->visited)
        {
            DFTraversal(v->Edges[i].v);
        }
    }
}

int main(int argc, char* argv[])
{
    Graph map;
    vector<string> mapVector;
    if(argc != 2)
    {
        cout << "Not enough arguments" << endl;
    }
    else
    {
        string file = agrv[1];
        ifstream inFile;
        inFile.open(file);
        if(inFile.is_open())
        {
            string line, city, connected, distance;
            int tempConnected = 0;
            getline(inFile, line);
            stringstream ss(line);
            getline(ss, city, ',');
            while(getline(ss, city, ','))
            {
                mapVector.push_back(city);
                map.addVertex(city);
            }
            while(getline(inFile, line))
            {
                stringstream sq(line);
                int pos = 0;
                getline (sq, city, ',');
                while(getline(sq, distance, ','))
                {
                    tempConnected = stoi(distance);
                    if(tempConnected > 0)
                    {
                        connected = mapVector[pos];
                        map.addEdge(city, connected, tempConnected);
                        cout << " ... Reading in " << city << " -- " << connected << " -- " << distance << endl;
                    }
                    pos++;
                }
            }
            map.assignDistricts();
            map.displayEdges();
        }
        else
        {
            cout << "Couldn't open the file" << endl;
        }
    }
}