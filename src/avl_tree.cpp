#include "avl_tree.h"
#include <iostream>

using namespace std;

AVLTree::AVLTree() : root(nullptr) {}

AVLTree::~AVLTree()
{
  clear(root);
}

void AVLTree::clear(AVLNode* node)
{
  if (node == nullptr) return;
  clear(node->left);
  clear(node->right);
  delete node;
}

bool AVLTree::isEmpty()
{
  return root == nullptr;
}

int AVLTree::height(AVLNode* node)
{
  return node ? node->height : 0;
}

int AVLTree::max(int a, int b)
{
  return (a > b) ? a : b;
}

int AVLTree::balanceFactor(AVLNode* node)
{
  return node ? height(node->left) - height(node->right) : 0;
}

AVLNode* AVLTree::rotateRight(AVLNode* y)
{
  AVLNode* x = y->left;
  AVLNode* t2 = x->right;

  x->right = y;
  y->left = t2;

  y->height = 1 + max(height(y->left), height(y->right));
  x->height = 1 + max(height(x->left), height(x->right));

  return x;
}

AVLNode* AVLTree::rotateLeft(AVLNode* x)
{
  AVLNode* y = x->right;
  AVLNode* t2 = y->left;

  y->left = x;
  x->right = t2;

  x->height = 1 + max(height(x->left), height(x->right));
  y->height = 1 + max(height(y->left), height(y->right));

  return y;
}

AVLNode* AVLTree::insertNode(AVLNode* node, const string& key, const string& value)
{
  if (node == nullptr) {
    return new AVLNode{key, value, 1, nullptr, nullptr};
  }

  if (key < node->key) {
    node->left = insertNode(node->left, key, value);
  } else if (key > node->key) {
    node->right = insertNode(node->right, key, value);
  } else {
    node->value = value;
    return node;
  }

  node->height = 1 + max(height(node->left), height(node->right));
  int balance = balanceFactor(node);

  if (balance > 1 && key < node->left->key) return rotateRight(node);
  if (balance < -1 && key > node->right->key) return rotateLeft(node);

  if (balance > 1 && key > node->left->key) {
    node->left = rotateLeft(node->left);
    return rotateRight(node);
  }

  if (balance < -1 && key < node->right->key) {
    node->right = rotateRight(node->right);
    return rotateLeft(node);
  }

  return node;
}

void AVLTree::insert(const string& key, const string& value)
{
  root = insertNode(root, key, value);
}

AVLNode* AVLTree::searchNode(AVLNode* node, const string& key)
{
  if (node == nullptr || node->key == key) return node;
  if (key < node->key) return searchNode(node->left, key);
  return searchNode(node->right, key);
}

string* AVLTree::search(const string& key)
{
  AVLNode* node = searchNode(root, key);
  return node ? &node->value : nullptr;
}

AVLNode* AVLTree::minValueNode(AVLNode* node)
{
  AVLNode* current = node;
  while (current->left != nullptr) {
    current = current->left;
  }
  return current;
}

void AVLTree::displayTree(AVLNode* node, const string& prefix, bool is_last)
{
  if (node == nullptr) return;

  cout << prefix << (is_last ? "\\-- " : "|-- ")
       << "[" << node->key << ": " << node->value << ", h=" << node->height << "]" << endl;

  string next_prefix = prefix + (is_last ? "    " : "|   ");
  bool has_left = node->left != nullptr;
  bool has_right = node->right != nullptr;

  if (has_left && has_right) {
    displayTree(node->left, next_prefix, false);
    displayTree(node->right, next_prefix, true);
  } else if (has_left) {
    displayTree(node->left, next_prefix, true);
  } else if (has_right) {
    displayTree(node->right, next_prefix, true);
  }
}

AVLNode* AVLTree::removeNode(AVLNode* node, const string& key)
{
  if (node == nullptr) return nullptr;

  if (key < node->key) {
    node->left = removeNode(node->left, key);
  } else if (key > node->key) {
    node->right = removeNode(node->right, key);
  } else {
    if (node->left == nullptr || node->right == nullptr) {
      AVLNode* child = node->left ? node->left : node->right;
      delete node;
      return child;
    }

    AVLNode* successor = minValueNode(node->right);
    node->key = successor->key;
    node->value = successor->value;
    node->right = removeNode(node->right, successor->key);
  }

  node->height = 1 + max(height(node->left), height(node->right));
  int balance = balanceFactor(node);

  if (balance > 1 && balanceFactor(node->left) >= 0) return rotateRight(node);
  if (balance > 1 && balanceFactor(node->left) < 0) {
    node->left = rotateLeft(node->left);
    return rotateRight(node);
  }

  if (balance < -1 && balanceFactor(node->right) <= 0) return rotateLeft(node);
  if (balance < -1 && balanceFactor(node->right) > 0) {
    node->right = rotateRight(node->right);
    return rotateLeft(node);
  }

  return node;
}

void AVLTree::remove(const string& key)
{
  root = removeNode(root, key);
}

void AVLTree::display(const string& msg)
{
  if (!msg.empty()) {
    cout << msg << endl;
  }

  if (root == nullptr) {
    cout << "EMPTY" << endl;
    return;
  }

  displayTree(root, "", true);
}


  
