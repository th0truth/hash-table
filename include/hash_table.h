#pragma once
#include <string>

#define HT_INITIAL_BASE_SIZE 50

typedef struct {
  std::string key;
  std::string value;
} ht_item;

class HashTable {
  private:
    int32_t base_size;

    HashTable(int32_t size);
    
    void resize(const int32_t base_size);
    void resize_up();
    void resize_down();

    int32_t size;
    int32_t count;
    ht_item **items;
 
    static ht_item DELETED_ITEM;

    ht_item *new_item(const std::string &key, const std::string &value);
    void del_item(ht_item *item);
    
    public:
    // Constructor
    HashTable();
    
    // Desctructor
    ~HashTable();

    std::string *search(const std::string &key);
    void insert(const std::string &key, const std::string &value);
    void remove(const std::string &key);

};
