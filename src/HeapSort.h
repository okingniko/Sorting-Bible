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
