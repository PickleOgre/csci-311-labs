// Lab 2 Skeleton
// Author: *** YOUR NAME HERE ***

#include <iostream>
#include <vector>
#include <limits.h>
using namespace std;

/*************************************************************
 * Your solutions go below here and do not change the headers*
 * ***********************************************************/

int triangleNum(int n)
{ // Returns the number of dots required to construct a triangle with n dots on each side.
  if (n == 0)
    return 0;
  return n + triangleNum(n - 1);
}

int rFib(int n)
{ // Returns the value at position n in the Fibonacci Sequence.
  if (n == 0)
    return 0;
  else if (n == 1)
    return 1;
  return rFib(n - 1) + rFib(n - 2);
}

int rSumHelper(const vector<int> &v, int i)
{ // Recursively adds the value at position i - 1 to the total of the rest of the array.
  if (i == v.size())
    return 0;
  return v[i] + rSumHelper(v, i + 1);
}

int rSum(const vector<int> &v)
{ // Calculates the sum of the elements in a vector recursively
  return rSumHelper(v, 0);
}

int rMaxHelper(const vector<int> &v, int start)
{ // Recursively compares the value at index "start" with the maximum of the rest of the array.
  if (start == 0)
  {
    return v[0];
  }
  else
  {
    int m = rMaxHelper(v, start - 1);
    if (v[start] > m)
      return v[start];
    else
      return m;
  }
}

int rMax(const vector<int> &v)
{ // Finds the maximum value in a vector recursively.
  if (v.size() == 0)
  {
    return INT_MIN;
  }
  return rMaxHelper(v, v.size() - 1);
}

bool isSorted(const vector<int> &v, int start, int end)
{ // Uses recursion to check whether the elements of v are sorted in ascending order between the start and end index
  // Worked with Chris Johnson
  if (v.empty() || v.size() == 1)
    return true;
  if (start == end)
    return true;
  return (v[end - 1] <= v[end] && isSorted(v, start, end - 1));
}

bool isPalindromeHelper(string s, int start, int end)
{
  if (s.length() == 0 || s.length() == 1)
    return true;
  if (start == end)
    return true;
  else if (start == end - 1)
    return (s[start] == s[end]);
  return (s[start] == s[end] && isPalindromeHelper(s, start + 1, end - 1));
}

bool isPalindrome(string s)
{ // Returns true if the string is a palindrome and false otherwise.
  return isPalindromeHelper(s, 0, s.length() - 1);
}

int rBinarySearch(const vector<int> &v, int low, int high, int target)
{ // Uses binary search to find the index of the target in the sorted vector v
  if (low <= high)
  {
    int middle = low + (high - low) / 2;

    if (target == v[middle])
      return middle;
    else if (target < v[middle])
      return rBinarySearch(v, low, middle - 1, target);
    else if (target > v[middle])
      return rBinarySearch(v, middle + 1, high, target);
  }
  return -1; // If low is not <= high, the value must not exist in the array.
}

bool rSubsetSum(const vector<int> &v, int start, int target)
{ // Returns whether there exist some subset of the numbers in v (starting at index start) that adds up to target
  if (target == 0)
    return true;
  if (start >= v.size() || v.empty())
    return false;
  return rSubsetSum(v, start + 1, target - v[start]) // Include current number in sum
         || rSubsetSum(v, start + 1, target);        // Exclude current number from sum
} // Worked together with Chris Johnson on this problem. They gave me the advice to modify the target for each recursive branch.

/***********************************************
 * Main and helper functions for quick testing *
 * *********************************************/
void readIntVector(vector<int> &v, int n);

int main()
{
  int question = -1;
  cout << "Question: ";
  cin >> question;

  int n = 0, start = 0, end = 0;
  vector<int> v;
  string s = "";
  switch (question)
  {
  case 1: // triangleNum
    cout << "Triangle Number n: ";
    cin >> n;
    cout << triangleNum(n) << endl;
    break;
  case 2: // rFib
    cout << "Nth Fibonacci Number: ";
    cin >> n;
    cout << rFib(n) << endl;
    break;
  case 3: // rSum
    cout << "Recursive Sum Vector Size: ";
    cin >> n;
    cout << "Values: ";
    readIntVector(v, n);
    cout << rSum(v) << endl;
    break;
  case 4: // rMax
    cout << "Recursive Max Vector Size: ";
    cin >> n;
    cout << "Values: ";
    readIntVector(v, n);
    cout << rMax(v) << endl;
    break;
  case 5: // isSorted
    cout << "isSorted Vector Size: ";
    cin >> n;
    cout << "Start and End: ";
    cin >> start >> end;
    cout << "Values: ";
    readIntVector(v, n);
    cout << isSorted(v, start, end) << endl;
    break;
  case 6: // isPalindrome
    cout << "String: ";
    cin >> s;
    cout << isPalindrome(s) << endl;
    break;
  case 7: // rBinarySearch
    cout << "Binary Search Vector Size: ";
    cin >> n;
    cout << "Target: ";
    cin >> end;
    cout << "Values: ";
    readIntVector(v, n);
    cout << rBinarySearch(v, 0, v.size() - 1, end) << endl;
    break;
  case 8: // rSubsetSum
    cout << "Subset Sum Vector Size: ";
    cin >> n;
    cout << "Target: ";
    cin >> end;
    cout << "Values: ";
    readIntVector(v, n);
    cout << rSubsetSum(v, 0, end) << endl;
    break;
  }

  return 0;
}

/**************************************************
 * Read a vector of integers in from cin          *
 * v - vector<int> & - the integer vector to fill *
 * n - int - the number of integers to read       *
 * ************************************************/
void readIntVector(vector<int> &v, int n)
{
  int m = 0;
  for (int i = 0; i < n; i++)
  {
    cin >> m;
    v.push_back(m);
  }
}
