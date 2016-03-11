##1. 概念
- 在计算机科学与数学中，一个排序算法（Sorting algorithm）是一种能将一串数据依照特定排序方式进行排列的一种算法。最常用到的排序方式是**数值顺序**以及**字典顺序**。有效的排序算法在一些算法（例如搜索算法与合并算法）中是重要的，如此这些算法才能得到正确解答。排序算法也用在处理文字数据以及产生人类可读的输出结果。基本上，排序算法的输出必须遵守下列两个原则：
	1. 输出结果为递增序列（递增是针对所需的排序顺序而言）
  2. 输出结果是原输入的一种排列或重组

## 2. 分类
在计算机科学所使用的排序算法通常被分类为：

-  计算的时间复杂度（最差、平均、和最好性能）：依据列表（list）的大小(n)。一般而言，好的性能是O(n log n)，且坏的性能是O(n2)。对于一个排序理想的性能是O(n)。仅使用一个抽象关键比较运算的排序算法总平均上总是至少需要O(n log n)。
- 存储器使用量（以及其他电脑资源的使用）：严格来说，原地排序(in-place)算法要求的空间复杂度为O(1); 而有时候O(log n) 的额外空间也可被视为原地排序。
- 递归：有些排序算法可设计为递归和非递归形式，E.g. 归并排序
- 稳定性：稳定排序算法会让原本有相等键值的纪录维持相对次序。也就是如果一个排序算法是稳定的，当有两个相等键值的纪录R和S，且在原本的列表中R出现在S之前，在排序过的列表中R也将会是在S之前。
- 依据排序的方法：插入、交换、选择、合并等等。
- Etc.

## 3. 常用算法简要比较
![简要比较](http://img.blog.csdn.net/20160308210208494)

其中：

- 排序后的数按非递减顺序排列
- K 代表数值中的 **数位** 个数
- n 代表数据规模
- m代表数据的最大值减去最小值

## 4. 测试数据
笔者用python写了一个生成随机数的脚本，使用`python GenRandNums.py -h`可查看使用方法
### 4.1 随机数生成源代码
```python
#!/usr/bin/env python
# -*- coding: utf-8 -*-
import os
import random
import getopt
import sys

def gen_rand_nums(count, filename):
	rand_seed = os.urandom(32)
	random.seed(rand_seed)

	with open(filename, "wb") as f:
		for i in range(0, count):
			tmp = str(random.randint(0, 13 * count)) + " "
			f.write(tmp)

	f.close()

def usage():
    print '''Usage:
        -n, --nums      Set the amount of the random nums.
        -h, --help      Show this help.
        -o, --output    Change the output filename.
	'''

if __name__ == '__main__':
	try:
		opts, args = getopt.getopt(sys.argv[1:], 'hn:o:', ["help", "nums= ", "output="])
	except getopt.GetoptError as err:
		print str(err)
		usage()
		sys.exit(2)
	output = "sort_file.txt"
	num_count = 1000
	for o, a in opts:
		if o in ("-h", "--help"):
			usage()
			sys.exit()
		elif o in ("-n", "--nums"):
			num_count = int(a)
		elif o in ("-o", "--output"):
			output = a
		else:
			assert False, "unhandled option"

	gen_rand_nums(num_count, output)

```
注：

- 生成的随机数文件中，每个数以空格为分隔符。

###4.2 测试框架源代码
只需要包含特定的排序算法头文件，并在main函数中调用相关函数，即可进行响应算法的测试。
```c++
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

注：

- 测试数据使用**int**型的数据进行测试，理论上所有具有"<"和">"比较符的数据类型都可以参与测试。

- 在`ReadNumsFromFile`方法中，也可以使用诸如以下代码段的方法来获得文件中的总字节数，并以此来给vector对象预先分配空间。
```c++
buffer.seekp(0, ios::end);
int size = buffer.tellg();
buffer.seekp(0, ios::beg);
```
- 命令行参数解析时，可考虑使用unorderd_map和function对象的结合。
