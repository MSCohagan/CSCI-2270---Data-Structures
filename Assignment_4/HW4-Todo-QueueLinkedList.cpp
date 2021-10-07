#include "HW4-Todo-QueueLinkedList.hpp"
#include <iostream>

TodoQueueLinkedList::TodoQueueLinkedList(){
  queueFront = NULL;
  queueEnd = NULL;
}

TodoQueueLinkedList::~TodoQueueLinkedList(){
  while(queueFront != NULL){
    TodoItem *tmp = queueFront;
    queueFront = queueFront->next;
    delete tmp;
  }
  queueEnd = NULL;
}

bool TodoQueueLinkedList::isEmpty(){
  return getQueueFront() == NULL ? true : false;
}

void TodoQueueLinkedList::enqueue(std::string todoItem){
  TodoItem * tmp = new TodoItem;
  tmp ->todo = todoItem;
  temp->next = NULL;
  if(queueFront == NULL){
    queueFront = tmp;
    queueEnd = tmp;
  }else{
    queueEnd->next = tmp;
    queueEnd = temp;
  }
}

void TodoQueueLinkedList::dequeue(){
  if(queueFront == NULL){
    std::cout << "Queue empty, cannot dequeue an item." << std::endl;
    return;
  }
  else if(queueFront == queueEnd){
    queueFront = NULL;
    queueEnd = NULL;
  }else{
    queueFront = queueFront->next
  }
}

TodoItem* TodoQueueLinkedList::peek(){
  if(queueFront == NULL){
    std::cout << "Queue empty, cannot peak." << std::endl;
  }
  return queueFront;
}
