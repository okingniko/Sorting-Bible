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

