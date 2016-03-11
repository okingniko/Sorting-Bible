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


