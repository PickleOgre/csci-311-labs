// Lab 3 - BST.cpp
// Author: *** Josiah Lawrence ***

#include "BST.h"

#include <limits.h>

#include <iostream>
#include <vector>

// ***do not change the headers***

// you solutions go here
// remember that you do not need to implement all of them
// follow the document to see which ones you need to implement

using std::shared_ptr;

BST::BST() {}

BST::~BST() {}

shared_ptr<Node>
BST::search(int target)
{
  return search(root, target);
}

shared_ptr<Node>
BST::search(shared_ptr<Node> n, int target)
{
  if (n == nullptr)
    return nullptr;
  if (n->value == target)
    return n;
  if (n->value > target)
    return search(n->left, target);
  if (n->value < target)
    return search(n->right, target);
  return nullptr;
}

shared_ptr<Node>
BST::minimum()
{
  return minimum(root);
}

shared_ptr<Node>
BST::minimum(shared_ptr<Node> n)
{
  if (n->left == nullptr)
    return n;
  else
    return minimum(n->left);
}

shared_ptr<Node>
BST::maximum()
{
  return maximum(root);
}

shared_ptr<Node>
BST::maximum(shared_ptr<Node> n)
{
  if (n->right == nullptr)
    return n;
  else
    return maximum(n->right);
}

void
BST::insertValue(int val)
// If root does not exist, insert val as root. Else call helper function.
{
  if (root == nullptr) {
    root = shared_ptr<Node>(new Node(val));
  } else {
    root = insertValue(root, val);
  }
}

shared_ptr<Node>
BST::insertValue(shared_ptr<Node> n, int val)
{
  if (val < n->value) {
    if (n->left != nullptr) {
      n->left = insertValue(n->left, val);
    } else {
      n->left = shared_ptr<Node>(new Node(val));
    }
  } else if (val > n->value) {
    if (n->right != nullptr) {
      n->right = insertValue(n->right, val);
    } else {
      n->right = shared_ptr<Node>(new Node(val));
    }
  } // If n->value == val, nothing to be done.
  return n;
}

void
BST::deleteValue(int val)
{
  if (search(val) == nullptr) 
    return;
  root = deleteValue(root, val);
}

shared_ptr<Node>
BST::deleteValue(shared_ptr<Node> n, int val)
{
  if (val < n->value) {
    // value to be deleted is somewhere in the left subtree
    n->left = deleteValue(n->left, val);
  } else if (val > n->value) {
    // value to be deleted is somewhere in the right subtree
    n->right = deleteValue(n->right, val);
  } else if (n->right == nullptr && n->left == nullptr) {
    // No children -> delete n itself
    return nullptr;
  } else if (n->left == nullptr) {
    // only right child exists -> let n = right child
    return n->right;
  } else if (n->right == nullptr) {
    // only left child exists -> let n = left child
    return n->left;
  } else {
    // both children exist -> let n = right min; delete right max
    shared_ptr<Node> minRight = minimum(n->right);
    n->value = minRight->value;
    n->right = deleteValue(n->right, minRight->value);
  }
  return n;
}

bool
BST::isBST(shared_ptr<Node> n)
{
  return isBST(n, INT_MIN, INT_MAX);
}

bool
BST::isBST(shared_ptr<Node> n, int low, int high)
{
  if (n == nullptr)
    return true;
  if (n->value < low or n->value > high) {
    return false;
  }
  return isBST(n->left, low, n->value) && isBST(n->right, n->value, high);
}

void
BST::preOrder(shared_ptr<Node> n, std::vector<shared_ptr<Node>>& order)
{
  if (n != nullptr) {
    order.push_back(n);
    if (n->left != nullptr)
      preOrder(n->left, order);
    if (n->right != nullptr)
      preOrder(n->right, order);
  }
}

void
BST::inOrder(shared_ptr<Node> n, std::vector<shared_ptr<Node>>& order)
{
  if (n != nullptr) {
    if (n->left != nullptr)
      inOrder(n->left, order);
    order.push_back(n);
    if (n->right != nullptr)
      inOrder(n->right, order);
  }
}

void
BST::postOrder(shared_ptr<Node> n, std::vector<shared_ptr<Node>>& order)
{
  if (n != nullptr) {
    if (n->left != nullptr)
      postOrder(n->left, order);
    if (n->right != nullptr)
      postOrder(n->right, order);
    order.push_back(n);
  }
}
