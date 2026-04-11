#pragma once
#include <string>

struct Node
{
  std::string key;
  std::string value;
  Node *prev;
  Node *next; 
};

class DoublyLinkedList
{
  private:
    Node *head;
    Node *tail;

  public:
    DoublyLinkedList();
    ~DoublyLinkedList();

    void insert(const std::string &key, const std::string &value);
    void remove(const std::string &key);
    std::string *search(const std::string &key);

    void display(const std::string &msg = "");
    void displayReverse(const std::string& msg = ""); 
};
