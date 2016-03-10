##0. 前言
1. Simple Sorts包括两种排序算法： 选择排序(Selection sort) 和 插入排序（Insertion sort)。
2. 代码基于C++11编写，编译器使用g++4.9.2 版本。
3. 测试数据集使用[导论](http://blog.csdn.net/okingniko/article/details/50830524)中提供的程序生成。
4. 测试使用[导论](http://blog.csdn.net/okingniko/article/details/50830524)中提供的测试框架，加入相关的头文件，并进行相关算法调用(具体可参见[插入排序](http://blog.csdn.net/okingniko/article/details/50830629#t3)中的测试源代码)。

##1. 插入排序(Insertion sort)
###1.1 基本思想
插入排序的基本思想是：每步将一个待排序的纪录，按其关键码值的大小插入前面已经排序的文件中适当位置上，直到全部插入完为止。
###1.2 源代码
```c++
// InsertionSort.h
#include <vector>

template<typename ItemType>
void InsertionSort(std::vector<ItemType> &items)
{
  for (int i = 1; i < items.size(); ++i) {
    auto tmp = std::move(items[i]);
    
    int j;
    for (j = i; j > 0 && items[j - 1] > tmp; --j) 
      items[j] = std::move(items[j - 1]);
    items[j] = std::move(tmp);
  }
}
```

```c++
// InsertionSort_test.cc
// Compile: g++ -std=c++11 -o insertion_sort SelectionSort_test.cc 
#include "InsertionSort.h"
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
   
  
  cout << "Deal with " << nums.size() << " nums" << endl;
  WriteNumsToFile(nums, argv[2]);

  return 0;
}
```
## 2. 选择排序(Selection sort)
###2.1 基本思想
选择排序（Selection sort）是一种简单直观的排序算法。它的工作原理是每一次从待排序的数据元素中选出最小（或最大）的一个元素，存放在序列的起始位置，直到全部待排序的数据元素排完。 选择排序是不稳定的排序方法（比如序列[5， 5， 3]第一次就将第一个[5]与[3]交换，导致第一个5挪动到第二个5后面）。
###2.2 源代码
```c++
// SelectionSort.h
#include <vector>

template<class ItemType>
void SelectionSort(std::vector<int> &items) 
{
  for (int i = 0; i < items.size(); ++i) {
    int min_idx = i;
    for (int j = i; j < items.size() ; ++j) {
      if (items[j] < items[min_idx])
        min_idx = j;
    }
    if (i != min_idx) {
    // swap two element using std::move
     auto tmp = std::move(items[i]);
     items[i] = std::move(items[min_idx]);
     items[min_idx] = std::move(tmp);
    }
  }
}
```
## 4. 排序测试
测试使用Cmake Test 进行自动化测试。
当然你也可以使用linux下的 `time` 命令进行时间的测试。
###4.1 10000个随机数

###4.2 88888个随机数

