#pragma once

#include <cstddef>
#include <map>
#include <string>

struct TrieNode
{
  std::map<char, TrieNode*> children;
  bool has_value;
  std::string value;
};

class TrieTree
{
  private:
    TrieNode* root;

    void clear(TrieNode* node);
    bool removeNode(TrieNode* node, const std::string& key, size_t depth);
    void displayTree(TrieNode* node, const std::string& prefix, bool is_last, char edge);
    int nodeCount(TrieNode* node);
    int keyCount(TrieNode* node);

  public:
    TrieTree();
    ~TrieTree();

    void insert(const std::string& key, const std::string& value);
    void remove(const std::string& key);
    std::string* search(const std::string& key);
    void display(const std::string& msg = "");
    bool isEmpty();
};
