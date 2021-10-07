#include <iostream>
#include "HW4-Todo-QueueArray.hpp"

TodoQueueArray::TodoQueueArray(){
  queueFront = -1;
  queueEnd = -1;
}

bool TodoQueueArray::isEmpty(){
  return (queueFront == -1 && queueEnd == -1) ? true : false;
}

bool TodoQueueArray::isFull(){
  return (queueEnd + 1) % MAX_QUEUE_SIZE == queueFront ? true : false;
}

void TodoQueueArray::enqueue(std::string todoItem){
  TodoItem* tmp = new TodoItem;
  tmp->todo = todoItem;
  if(isFull()){
    std::cout << "Queue full, cannot add new todo item." << std::endl;
    return;
  }
  else if(isEmpty()){
    queueFront = 0;
    queueEnd = 0;
  }else{
    queueEnd = (queueEnd + 1) % MAX_QUEUE_SIZE;
  }
  queue[queueEnd] = *tmp;
}

void TodoQueueArray::dequeue(){
  if(isEmpty()){
    std::cout << "Queue empty, cannot dequeue an item." << std::endl;
    return;
  }
  else if(queueFront == queueEnd){
    queueFront = -1;
    queueEnd = -1;
  }else{
    queueFront = (queueFront + 1) % MAX_QUEUE_SIZE;
  }
}

TodoItem TodoQueueArray::peek(){
  if(isEmpty()){
    std::cout << "Queue empty, cannot peek." << std::endl;
  }
  return queue[queueFront];
}
