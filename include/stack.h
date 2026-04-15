#pragma once
#include <cstdint>
#include <stdexcept>

template <class T>
class Stack {
  private:
    T *data;              // Pointer to a dynamically allocated array that will hold the stack's items
    int32_t current_size; // Keeps track of the current number of items in the stack  
    int32_t top_index;    // The index of the "top" elem in the array
    int32_t capacity;     // The max number of items the stack can hold

  public:
    Stack() = delete;      // Setup the constructor
    Stack(int32_t new_capacity);
    Stack(const Stack& other);
    Stack(Stack&& other);
    Stack& operator=(const Stack& other);
    ~Stack();
    
    bool isFull();
    bool isEmpty();
    bool push(T value);
    bool pop();
    T top();

    int32_t size();
    int32_t getCapacity();
    void display(const std::string& prefix = "");
};

// Constructor
template <class T>
Stack<T>::Stack(int32_t new_capacity): current_size(0), top_index(-1), capacity(new_capacity)
{
  data = new T[capacity];
}

// Copy constructor
template<class T>
Stack<T>::Stack(const Stack& other): current_size(other.current_size), top_index(other.top_index), capacity(other.capacity)
{
  data = new T[capacity];
  for (int32_t i = 0; i < current_size; i++) {
    data[i] = other.data[i];
  }
}

// Move constructor
template <class T>
Stack<T>::Stack(Stack&& other): current_size(other.current_size), top_index(other.top_index), capacity(other.capacity), data(other.data)
{
  other.data = nullptr;
  other.current_size = 0;
  other.top_index = -1;
  other.capacity = 0;
}

// Destructor
template <class T>
Stack<T>::~Stack()
{
  delete[] data;
}

// Assignment Operator
template <class T>
Stack<T>& Stack<T>::operator=(const Stack& other)
{
  if (this != &other) {
    delete[] data;
    current_size = other.current_size;
    top_index = other.top_index;
    capacity = other.capacity;
  
    data = new T[capacity];
    for (int32_t i = 0; i < current_size; i++) {
      data[i] = other.data[i];
    }
  }

  return *this;
}

// Check if Full
template <class T>
bool Stack<T>::isFull()
{
  return current_size == capacity;
}

// Check if Empty
template <class T>
bool Stack<T>::isEmpty()
{
  return current_size == 0;
}

// Add an Item
template <class T>
bool Stack<T>::push(T value)
{
  if (isFull())
    return false;
  
  top_index++;
  data[top_index] = value;
  current_size++;
  return true; 
}

// Remove an Item
template <class T>
bool Stack<T>::pop()
{
  if (isEmpty())
    return false;

  top_index--;
  current_size--;
  return true;
}

// Get the Top Item
template <class T>
T Stack<T>::top()
{
  if (isEmpty())
    throw std::runtime_error("Stack is empty.");
  return data[top_index];     
}

// Get Current Size
template <class T>
int32_t Stack<T>::size()
{
  return current_size;
}

// Get Max Capacity
template <class T>
int32_t Stack<T>::getCapacity()
{
  return capacity;
}

// Display the Stack
template <class T>
void Stack<T>::display(const std::string& prefix)
{
  if (!prefix.empty()) {
    std::cout << prefix << std::endl;
  }
  
  if (isEmpty()) {
    std::cout << "[Empty Stack]" << std::endl;
    return;
  }

  std::cout << "Stack (Top to Bottom):" << std::endl;
  for (int32_t i = top_index; i >= 0; i--) {
    std::cout << "  [" << i << "]: " << data[i] << (i == top_index ? " <- TOP" : "") << std::endl;
  }
}
