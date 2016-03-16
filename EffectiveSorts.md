##0. 前言
1. Efficient sorts包括两种排序算法： 归并排序(Merge sort) 、 堆排序（Heap sort) 、快速排序(Quick sort)。
2. 代码基于C++11编写，编译器使用g++4.9.2 版本。
3. 测试数据集使用[导论](http://blog.csdn.net/okingniko/article/details/50830524)中提供的程序生成。
4. 测试使用[导论](http://blog.csdn.net/okingniko/article/details/50830524)中提供的测试框架，加入相关的头文件，并进行相关算法调用(具体可参见[插入排序](http://blog.csdn.net/okingniko/article/details/50830629#t3)中的测试源代码)。
##1. 归并排序(Merge sort)
###1.1 基本思想
- 归并排序是建立在归并操作上的一种有效的排序算法,该算法是采用分治法（Divide and Conquer）的一个非常典型的应用。将已有序的子序列合并，得到完全有序的序列；即先使每个子序列有序，再使子序列段间有序。若将两个有序表合并成一个有序表，称为二路归并。
- 归并过程为：比较a[i]和a[j]的大小，若a[i]≤a[j]，则将第一个有序表中的元素a[i]复制到r[k]中，并令i和k分别加上1；否则将第二个有序表中的元素a[j]复制到r[k]中，并令j和k分别加上1，如此循环下去，直到其中一个有序表取完，然后再将另一个有序表中剩余的元素复制到r中从下标k到下标t的单元。**归并排序的算法我们通常用递归实现**，先把待排序区间[s,t]以中点二分，接着把左边子区间排序，再把右边子区间排序，最后把左区间和右区间用一次归并操作合并成有序的区间[s,t]。
###1.2 源代码
```c++
// MergeSort.h
#include <vector>

// Internal method that merges two sorted halves of a subarray.
// :param items && tmp_items: same as the above.
// :param left_pos : left_index of the subarray.
// :param right_pos : index of the start of the second half.
// :param right_end : the right-most index of the subarray.
template<typename ItemType>
void Merge(std::vector<ItemType> &items, std::vector<ItemType> &tmp_items,
           int left_pos, int right_pos, int right_end)
{
  int left_end = right_pos - 1;
  
  int i = left_pos, j = right_pos, k = left_pos;
  while(i <= left_end && j <= right_end) {
    if (items[i] <= items[j]) 
      tmp_items[k++] = std::move(items[i++]);
    else 
      tmp_items[k++] = std::move(items[j++]);
  }

  while (i <= left_end)  tmp_items[k++] = std::move(items[i++]);
  while (j <= right_end) tmp_items[k++] = std::move(items[j++]);

  for (int i = left_pos; i <= right_end; ++i)
    items[i] = std::move(tmp_items[i]);
}

// Internal method that makes recursive call
// :param items: array of the input items
// :param tmp_items: array to place the merged result.
// :param left: left-most index of the subarray
// :param right: right-most index of the subarray.
template<typename ItemType>
void MergeSort(std::vector<ItemType> &items, std::vector<ItemType> &tmp_items,
               int left, int right)
{
  if (left < right) {
    int mid = (left + right) / 2;
    MergeSort(items, tmp_items, left, mid);
    MergeSort(items, tmp_items, mid + 1, right);
    Merge(items, tmp_items, left, mid + 1, right);
  }
}

template<typename ItemType>
void MergeSort(std::vector<ItemType> &items)
{
  std::vector<ItemType> tmp_items(items.size());
  
  MergeSort(items, tmp_items, 0, items.size() - 1);
}
```
##2. 堆排序(Heap sort)
###2.1 基本思想
- 堆排序(Heapsort)是指利用堆积树（堆）这种数据结构所设计的一种排序算法，它是选择排序的一种。可以利用数组的特点快速定位指定索引的元素。堆分为大根堆和小根堆，是完全二叉树。大根堆的要求是每个节点的值都不大于其父节点的值，即A[PARENT[i]] >= A[i]。在数组的非降序排序中，需要使用的就是大根堆，因为根据大根堆的要求可知，最大的值一定在堆顶。
- 算法步骤：
	1. 以线性时间建立一个堆。
	2. 通过将堆中的最后一个元素与第一个元素(堆顶)交换，缩减堆的大小并进行下滤。
	3. 执行N- 1 次步骤2， 算法终止。

###2.2 源代码
```c++
#include <vector>

// Internal method, return the leftnode index of the parent node.
// Attention: index starts at 0.
inline int GetLeftChild(int parent) {
  return (parent << 1) + 1;
}

// Internal method, 
// :param items : the array of the input data.
// :param index : the position from which to percolate down.
// :param heap_size : the current logical size of the binary heap.
template<typename ItemType>
void PercDown(std::vector<ItemType> &items, int index, int heap_size) 
{
  auto tmp = std::move(items[index]);
  int child_idx = 0;

  for ( ; GetLeftChild(index) < heap_size; index = child_idx) {
    child_idx = GetLeftChild(index);
    
    if (child_idx < (heap_size - 1) && items[child_idx + 1] > items[child_idx])
      ++child_idx;
    
    if (tmp < items[child_idx])
      items[index] = std::move(items[child_idx]);
    else 
      break;
  }

  items[index] = std::move(tmp);
}

template<typename ItemType>
void HeapSort(std::vector<ItemType> &items)
{
  //make heap, modify the array from the last non-leaf node to root node.
  for (int i = items.size() / 2; i >= 0; --i)
    PercDown(items, i, items.size());
  
  // Detele Max Node N-1 times, to get the sorted array.
  for (int i = items.size() - 1; i >= 0; --i) {
    // swap the max node with the end of the current heap(unsorted).
    auto tmp = std::move(items[i]);
    items[i] = std::move(items[0]);
    items[0] = std::move(tmp);

    PercDown(items, 0, i);
  }
}
```

## 3. 快速排序(Quick Sort)
###3.1 基本思想
- 快速排序（Quicksort）是对冒泡排序的一种改进。
- 快速排序由C. A. R. Hoare在1962年提出。它的基本思想是：通过一趟排序将要排序的数据分割成独立的两部分，其中一部分的所有数据都比另外一部分的所有数据都要小，然后再按此方法对这两部分数据分别进行快速排序，整个排序过程可以递归进行，以此达到整个数据变成有序序列。
- 快速排序的性能和分割点(Pivot)的选取策略密切相关, 笔者实现时采用三数中值分割法(Median-of-Three Partitioning)。
###3.2 源代码
```c++
// QuickSort.h
#include <vector>

template<typename ItemType>
inline void Swap(ItemType &lhs, ItemType &rhs)
{
  auto tmp = std::move(lhs);
  lhs = std::move(rhs);
  rhs = std::move(tmp);
}

// Return the median value of left, center and right
// Order these and hide the pivot on the right.
template<typename ItemType>
const ItemType &Median3(std::vector<ItemType> &items, int left, int right)
{
  int center = (left + right) / 2;
  
  if (items[left] > items[center])
    Swap(items[left], items[center]);
  if (items[left] > items[right])
    Swap(items[left], items[right]);
  if (items[center] > items[right])
    Swap(items[center], items[right]);

  // After the Swap, we'll have A[left] <= A[center] <= A[Right]
  Swap(items[center], items[right]);
  return items[right];
}

template<typename ItemType>
int Partition(std::vector<ItemType> &items, int left, int right)
{
  int i = left - 1;
  auto pivot = Median3(items, left, right);
  //auto pivot = items[right];
  
  for (int j = left; j < right; ++j) {
    if (items[j] <= pivot) {
      ++i;
      Swap(items[i], items[j]);
    }
  }

  // Restore Pivot
  Swap(items[i + 1], items[right]);

  return i + 1;
}
 

template<typename ItemType>
void QuickSort(std::vector<ItemType> &items, int left, int right)
{ 
  if (left < right) { 
    int idx = Partition(items, left, right);
    QuickSort(items, left, idx - 1);
    QuickSort(items, idx + 1, right);
  }
}

template<typename ItemType>
void QuickSort(std::vector<ItemType> &items)
{
  QuickSort(items, 0, items.size() - 1);
}
```

##4. 相关测试
`make test`
