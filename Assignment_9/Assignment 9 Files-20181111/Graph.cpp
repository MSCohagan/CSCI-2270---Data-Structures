#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <queue>

#include "Graph.hpp"

using namespace std;

Graph::Graph(){

}

Graph::~Graph(){

}

void Graph::addEdge(std::string v1, std::string v2, int distance){
  vertex * tempV = findVertex(v1);
  Edge tempE;
  tempE.v = findVertex(v2);
  tempE.distance = distance;
  tempV->Edges.push_back(tempE);
}

void Graph::addVertex(std::string name){
  vertex newCity;
  newCity.visited = false;
  newCity.name = name;
  newCity.district = 0;
  vertices.push_back(newCity);
}

void Graph::displayEdges(){
  vertex* temp;
  for(int i = 0; i < vertices.size(); i++){
    temp = &(vertices[i]);
    cout<<temp->district<<":"<< temp->name<<"-->";
    for(auto edge = temp->Edges.begin(); edge != temp->Edges.end(); edge++){
      if(edge != temp->Edges.end()-1){
        cout<<(edge->v)->name<<" ("<<edge->distance<<" miles)"<<"***";
      }else{
        cout<<(edge->v)->name<<" ("<<edge->distance<<" miles)";
      }
    }
    cout<<endl;
  }
}

void Graph::assignDistricts(){
  int district = 1;
  for(int i = 0; i < vertices.size(); i++){
    if(vertices[i].visited == false){
      vertices[i].visited = true;
      BFTraversalLabel(vertices[i].name, district);
      district++;
    }
  }
}

void Graph::printDFS(){
    setAllVerticesUnvisited();
    for(int i = 0; i < vertices.size(); i++){
        if(!vertices[i].visited){
            DFTraversal(&vertices[i]);
        }
    }
}

void Graph::setAllVerticesUnvisited(){
  for(int i = 0; i < vertices.size(); i++){
    vertices[i].visited = false;
  }
}

vertex *Graph::findVertex(std::string name){
  vertex* tempVertex = NULL;
  for(int i = 0; i < vertices.size(); i++){
    if(vertices[i].name ==name){
      tempVertex = &vertices[i];
      return tempVertex;
    }
  }
  return tempVertex;
}

void Graph::BFTraversalLabel(string startingCity, int distID){
  queue<vertex*> queue;
  vertex* temp = findVertex(startingCity);
  temp->visited = true;
  temp->district = distID;
  queue.push(temp);
  while(!queue.empty()){
    temp = queue.front();
    queue.pop();
    for(auto edge = temp->Edges.begin(); edge != temp->Edges.end(); edge++){
      if(!edge->v->visited){
        edge->v->district = distID;
        edge->v->visited = true;
        queue.push(edge->v);
      }
    }
  }
}

void Graph::DFTraversal(vertex* v){
    v->visited = true;
    cout<<v->name<<endl;
    for(int i = 0; i < v->Edges.size(); i++){
        if(!v->Edges[i].v->visited){
             DFTraversal(v->Edges[i].v);
        }
    }

}


int main(int argc, char* argv[]){
  Graph g;
  std::vector<std::string> zombieVector;
  if(argc != 2){
    cout<<"Not enough arguments"<<endl;
  }else{
 //     cout<<"test1"<<endl;
    string userFile = argv[1];
    ifstream file;
    file.open(userFile);
    if(file.is_open()){
    //    cout<<"test2"<<endl;
      string line;
      string city;
      string connectedCity;
      string distance;
      int tempConnection = 0;
      getline(file, line);
      stringstream ss(line);
      getline(ss, city, ',');
      while(getline(ss, city, ',')){
  //        cout<<"test3"<<endl;
        zombieVector.push_back(city);
        g.addVertex(city);
      }
      while(getline(file, line)){
 //         cout<<"test4"<<endl;
        stringstream ss2(line);
        int position = 0;
        getline(ss2, city, ',');
        while(getline(ss2, distance, ',')){
  //          cout<<"test5"<<endl;
          tempConnection = stoi(distance);
          if(tempConnection > 0){
 //             cout<<"test6"<<endl;
            connectedCity = zombieVector[position];
            g.addEdge(city, connectedCity, tempConnection);
            cout<<" ... Reading in "<<city<<" -- "<<connectedCity<<" -- "<<distance<<endl;

          }
          position++;
        }
      }
      g.assignDistricts();
      g.displayEdges();
    }else{
  //      cout<<"test7"<<endl;
      cout<<"Couldn't open the file"<<endl;
    }
  }
  return 0;
}