#include "trie_tree.h"
#include <iostream>

using namespace std;

TrieTree::TrieTree() : root(new TrieNode{{}, false, ""}) {}

TrieTree::~TrieTree()
{
  clear(root);
}

void TrieTree::clear(TrieNode* node)
{
  if (node == nullptr) return;

  for (auto& kv : node->children) {
    clear(kv.second);
  }
  delete node;
}

int TrieTree::nodeCount(TrieNode* node)
{
  if (node == nullptr) return 0;
  int count = 1;
  for (auto& kv : node->children) {
    count += nodeCount(kv.second);
  }
  return count;
}

int TrieTree::keyCount(TrieNode* node)
{
  if (node == nullptr) return 0;
  int count = node->has_value ? 1 : 0;
  for (auto& kv : node->children) {
    count += keyCount(kv.second);
  }
  return count;
}

bool TrieTree::isEmpty()
{
  return root->children.empty() && !root->has_value;
}

void TrieTree::insert(const string& key, const string& value)
{
  TrieNode* cur = root;
  for (char c : key) {
    auto it = cur->children.find(c);
    if (it == cur->children.end()) {
      TrieNode* next = new TrieNode{{}, false, ""};
      cur->children.emplace(c, next);
      cur = next;
    } else {
      cur = it->second;
    }
  }

  cur->has_value = true;
  cur->value = value;
}

string* TrieTree::search(const string& key)
{
  TrieNode* cur = root;
  for (char c : key) {
    auto it = cur->children.find(c);
    if (it == cur->children.end()) return nullptr;
    cur = it->second;
  }

  return cur->has_value ? &cur->value : nullptr;
}

bool TrieTree::removeNode(TrieNode* node, const string& key, size_t depth)
{
  if (node == nullptr) return false;

  if (depth == key.size()) {
    if (!node->has_value) return false;
    node->has_value = false;
    node->value.clear();
    return node->children.empty();
  }

  char c = key[depth];
  auto it = node->children.find(c);
  if (it == node->children.end()) return false;

  TrieNode* child = it->second;
  bool should_delete_child = removeNode(child, key, depth + 1);
  if (should_delete_child) {
    delete child;
    node->children.erase(it);
  }

  return node != root && node->children.empty() && !node->has_value;
}

void TrieTree::remove(const string& key)
{
  removeNode(root, key, 0);
}

void TrieTree::displayTree(TrieNode* node, const string& prefix, bool is_last, char edge)
{
  if (node == nullptr) return;

  cout << prefix << (is_last ? "\\-- " : "|-- ");

  if (edge == '\0') {
    cout << "<root>";
  } else {
    cout << "'" << edge << "'";
  }

  if (node->has_value) {
    cout << " = \"" << node->value << "\"";
  }

  cout << endl;

  string next_prefix = prefix + (is_last ? "    " : "|   ");
  size_t i = 0;
  size_t n = node->children.size();
  for (auto& kv : node->children) {
    bool child_last = (i + 1 == n);
    displayTree(kv.second, next_prefix, child_last, kv.first);
    i++;
  }
}

void TrieTree::display(const string& msg)
{
  if (!msg.empty()) {
    cout << msg << endl;
  }

  if (isEmpty()) {
    cout << "EMPTY" << endl;
    return;
  }

  displayTree(root, "", true, '\0');
}
