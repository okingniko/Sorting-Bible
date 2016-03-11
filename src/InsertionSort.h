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

