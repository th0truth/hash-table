#include <iostream>
#include "hash_table.h"
using namespace std;

int main(void)
{
  HashTable ht;

  // Create
  ht.insert("user", "Oliver James Hartley");

  // Update
  ht.insert("user", "Charlotte Mae Pennington");

  string *user_str = ht.search("user"); 
  if (user_str) {
    cout << "User: " << *user_str << endl;
  }

  for (int i = 0; i < 50; i++) {
    ht.insert(string("key_") + to_string(i), string("value") + to_string(i));
  }
  cout << "HashTable grew to " << (53 * 2) << " buckets automatically." << endl;
}
