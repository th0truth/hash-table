#include <iostream>
#include "hash_table.h"
using namespace std;

int main(void)
{
  HashTable ht;

  ht.insert("apple", "green");
  string *result = ht.search("apple"); 
  if (result != nullptr) {
    cout << "Apple is " << *result << endl;
  } else {
    cout << "Apple not found" << endl;
  }
  return 0;
}