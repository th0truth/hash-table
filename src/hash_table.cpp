#include "hash_table.h"
#include <string>
#include <cstring>
#include <cstdint>
#include <cmath>
using namespace std;

ht_item HashTable::DELETED_ITEM = {nullptr, nullptr}; 

ht_item *HashTable::new_item(string &key, string &value)
{
  // Allocate an item
  ht_item *item = new ht_item;
  item->key = key;
  item->value = value;
  return item;  
}

void HashTable::del_item(ht_item *item)
{
  if (item != nullptr && item != &DELETED_ITEM) {
    delete item;
  }
}

HashTable::HashTable(void)
{
  this->size = 53;
  this->count = 0;

  // Allocate an array of size containing pointers to ht_item.
  this->items = new ht_item*[this->size]();
}

HashTable::~HashTable(void)
{
  for (int i = 0; i < this->size; i++) {
    ht_item *item = this->items[i];
    if (item != nullptr && item != &DELETED_ITEM) {
      del_item(item);
    }
  }

  // Delete the array of pointers
  delete[] this->items;
}

static int32_t ht_hash(string s, const int a, const int m)
{
  int64_t hash = 0;
  const int len_s = s.size();
  for (int i = 0; i < len_s; i++) {
    hash += (int64_t)pow(a, len_s - (i+1)) * s[i];
    hash = hash % m;
  }
  return (int32_t)hash;
}