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


