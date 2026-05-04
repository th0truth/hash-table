#include "binary_search_tree.h"
#include <iostream>

using namespace std;

BinarySearchTree::BinarySearchTree() : root(nullptr) {}

BinarySearchTree::~BinarySearchTree()
{
  clear(root);
}

void BinarySearchTree::clear(BSTNode* node)
{
  if (node == nullptr) return;
  clear(node->left);
  clear(node->right);
  delete node;
}

bool BinarySearchTree::isEmpty()
{
  return root == nullptr;
}

BSTNode* BinarySearchTree::insertNode(BSTNode* node, const string& key, const string& value)
{
  if (node == nullptr) {
    return new BSTNode{key, value, nullptr, nullptr};
  }

  if (key < node->key) {
    node->left = insertNode(node->left, key, value);
  } else if (key > node->key) {
    node->right = insertNode(node->right, key, value);
  } else {
    node->value = value;
  }

  return node;
}

void BinarySearchTree::insert(const string& key, const string& value)
{
  root = insertNode(root, key, value);
}

BSTNode* BinarySearchTree::searchNode(BSTNode* node, const string& key)
{
  if (node == nullptr || node->key == key) return node;
  if (key < node->key) return searchNode(node->left, key);
  return searchNode(node->right, key);
}

string* BinarySearchTree::search(const string& key)
{
  BSTNode* node = searchNode(root, key);
  return node ? &node->value : nullptr;
}

BSTNode* BinarySearchTree::findMin(BSTNode* node)
{
  while (node != nullptr && node->left != nullptr) {
    node = node->left;
  }
  return node;
}

void BinarySearchTree::displayTree(BSTNode* node, const string& prefix, bool is_last)
{
  if (node == nullptr) return;

  cout << prefix << (is_last ? "\\-- " : "|-- ")
       << "[" << node->key << ": " << node->value << "]" << endl;

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

BSTNode* BinarySearchTree::removeNode(BSTNode* node, const string& key)
{
  if (node == nullptr) return nullptr;

  if (key < node->key) {
    node->left = removeNode(node->left, key);
  } else if (key > node->key) {
    node->right = removeNode(node->right, key);
  } else {
    if (node->left == nullptr) {
      BSTNode* right = node->right;
      delete node;
      return right;
    }
    if (node->right == nullptr) {
      BSTNode* left = node->left;
      delete node;
      return left;
    }

    BSTNode* successor = findMin(node->right);
    node->key = successor->key;
    node->value = successor->value;
    node->right = removeNode(node->right, successor->key);
  }

  return node;
}

void BinarySearchTree::remove(const string& key)
{
  root = removeNode(root, key);
}

void BinarySearchTree::display(const string& msg)
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
