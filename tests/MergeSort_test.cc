#include "MergeSort.h"
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

static void ReadNumsFromFile(const string &filename, vector<int> &nums) {
  ifstream in(filename, ios::in | ios::binary);

  if (!in) {
    cerr << "cannot open input file " << filename << endl;
    exit(EXIT_FAILURE);
  }
 
  int num;
  while (in >> num) {
    nums.push_back(num);
  }
}

static void WriteNumsToFile(vector<int> &nums, const string &filename) {
  ofstream out(filename, ios::out | ios::binary);

  if (!out) {
    cerr << "cannot open output file " << filename << endl;
    exit(EXIT_FAILURE);
  }

  for (const auto &num : nums) {
    out << num << " ";
  }
}

int main(const int argc, const char *argv[])
{
  if (argc != 3) {
    cerr << argv[0] << " <inputfilename> <outfilename>" << endl;
    exit(EXIT_FAILURE);
  }

  vector<int> nums;
  ReadNumsFromFile(argv[1], nums);
  
  // nums contains the input data.
  // call the sort algorithm here.
  MergeSort<int>(nums);   
  
  cout << "Deal with " << nums.size() << " nums" << endl;
  WriteNumsToFile(nums, argv[2]);

  return 0;
}

