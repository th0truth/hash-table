#pragma once
#include <string>

struct AVLNode
{
  std::string key;
  std::string value;
  int height;
  AVLNode *left;
  AVLNode *right;
};

class AVLTree
{
  private:
    AVLNode *root;

    int height(AVLNode *node);
    int balanceFactor(AVLNode *node);
    int max(int a, int b);

    AVLNode* rotateLeft(AVLNode *x);
    AVLNode* rotateRight(AVLNode *y);

    AVLNode* insertNode(AVLNode *node, const std::string& key, const std::string& value);
    AVLNode* removeNode(AVLNode *node, const std::string& key);
    AVLNode* minValueNode(AVLNode *node);
    AVLNode* searchNode(AVLNode *node, const std::string& key);
    void displayTree(AVLNode *node, const std::string& prefix, bool is_last);
    void clear(AVLNode *node);

  public:
    AVLTree();
    ~AVLTree();

    void insert(const std::string& key, const std::string& value);
    void remove(const std::string& key);
    std::string* search(const std::string& key);
    void display(const std::string& msg = "");
    bool isEmpty();
};
