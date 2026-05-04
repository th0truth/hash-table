#pragma once
#include <string>

struct BSTNode
{
  std::string key;
  std::string value;
  BSTNode *left;
  BSTNode *right;
};

class BinarySearchTree
{
  private:
    BSTNode *root;
  
    BSTNode* insertNode(BSTNode *node, const std::string& key, const std::string& value);
    BSTNode* removeNode(BSTNode *node, const std::string& key);
    BSTNode* findMin(BSTNode *node);
    BSTNode* searchNode(BSTNode *node, const std::string& key);
    void displayTree(BSTNode *node, const std::string& prefix, bool is_last);
    void clear(BSTNode *node);

  public:
    BinarySearchTree();
    ~BinarySearchTree();

    void insert(const std::string& key, const std::string& value);
    void remove(const std::string& key);
    std::string* search(const std::string& key);
    void display(const std::string& msg = "");
    bool isEmpty();
};
