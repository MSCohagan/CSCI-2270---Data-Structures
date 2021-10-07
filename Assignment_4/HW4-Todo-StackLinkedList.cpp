#include <iostream>
#include "HW4-Todo-StackLinkedList.hpp"

TodoStackLinkedList::TodoStackLinkedList(){
  stackHead = NULL;
}

TodoStackLinkedList::~TodoStackLinkedList(){
  while(stackHead != NULL){
    TodoItem * tmp = stackHead;
    stackHead = stackHead->next;
    delete tmp;
  }
  stackHead = NULL;
}

bool TodoStackLinkedList::isEmpty(){
  return (stackHead == NULL) ? true : false;
}

void TodoStackLinkedList::push(std::string todoItem){
  TodoItem * newitem = new TodoItem;
  newitem->todo = todoItem;
  newitem->next = NULL;
  if(stackHead != NULL){
    newitem->next = stackHead;
    stackHead = newitem;
  }else{
    stackHead = newitem;
  }
}

void TodoStackLinkedList::pop(){
  if(stackHead != NULL){
    TodoItem * tmp = stackHead;
    stackHead = stackHead->next;
    delete tmp;
    tmp = NULL;
  }else{
    std::cout << "Stack empty, cannot pop an item." << std::endl;
  }
}

TodoItem * TodoStackLinkedList::peek(){
  if(stackHead != NULL){
    return stackHead;
  }else{
    std::cout << "Stack empty, cannot peek." << std::endl;
    return NULL;
  }
}
