#ifndef HW4_TODO_QUEUELINKEDLIST
#define HW4_TODO_QUEUELINKEDLIST
#include <string>

struct TodoItem
{
  std::string todo;
  TodoItem *next;
};

class TodoQueueLinkedList
{
public:
  TodoQueueLinkedList();
  ~TodoQueueLinkedList();
  bool isEmpty();
  void enqueue(std::string todoItem);
  void dequeue();
  TodoItem* peek();
  TodoItem* getQueueFront() { return queueFront; }
  TodoItem* getQueueEnd() { return queueEnd; }
private:
  TodoItem* queueFront; // the item in the list that will be dequeued next
  TodoItem* queueEnd; // the item in the list that was most recently enqueued
};
#endif
