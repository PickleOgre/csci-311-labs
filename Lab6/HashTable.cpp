// CSCI 311 - Spring 2023
// Lab 6 - Hash Table cpp
// Author: Josiah Lawrence

// People I worked with on this assignment:
// Ryan, Tabatha

#include "HashTable.h"
#include <algorithm>
#include <iostream>
#include <math.h>

HashTable::HashTable()
{
  size = 11;
  p = 31;
  numElements = 0;
  table.resize(11);
}

HashTable::HashTable(int s, int mult)
{
  size = s;
  p = mult;
  numElements;
  table.resize(s);
}

int
HashTable::getSize()
{
  return size;
}
int
HashTable::getNumElements()
{
  return numElements;
}
int
HashTable::getP()
{
  return p;
}

void
HashTable::printTable()
{
  std::cout << "HASH TABLE CONTENTS" << std::endl;
  for (int i = 0; i < table.size(); i++) {
    if (table[i].size() > 0) {
      std::cout << i << ": ";
      for (int j = 0; j < table[i].size() - 1; j++) {
        std::cout << table[i][j] << ", ";
      }
      std::cout << table[i][table[i].size() - 1] << std::endl;
    }
  }
}

int
HashTable::search(std::string s)
{
  int hash_val = hash(s);
  std::vector<std::string> table_col = table[hash_val];
  for (unsigned int i = 0; i < table_col.size(); i++) {
    if (table_col[i] == s)
      return hash_val;
  }
  return -1;
}

void
HashTable::insert(std::string s)
{
  table[hash(s)].push_back(s);
  numElements++;
}

void
HashTable::remove(std::string s)
{
  int col_num = search(s);
  if (col_num == -1)
    return;
  auto it = std::find(table[col_num].begin(), table[col_num].end(), s);
  table[col_num].erase(it);
  numElements--;
}

void
HashTable::resize(int s)
{
  //std::cout << "Creating New Table " << std::endl;
  std::vector<std::vector<std::string>> new_table;
  new_table.resize(s); // resize vector
  size = s; 

  for (unsigned int i = 0; i < table.size(); i++) {
    for (std::string str : table[i]) {
      //std::cout << "Moving " << str << std::endl;
      new_table[hash(str)].push_back(str);
    }
  }

  table = new_table;
}

int
HashTable::hash(std::string s)
{
  unsigned int sum = 0;
  for (unsigned int i = 0; i < s.length(); i++) {
    sum += int(s[i]) * pow(p, i);
  }

  return sum % size;
}