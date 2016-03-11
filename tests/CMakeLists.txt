set(INPUT_FILE1 sort_file.txt)

add_executable(insertion_sort_test InsertionSort_test.cc)
add_test(NAME insertion_sort_test
  COMMAND insertion_sort_test ${INPUT_FILE1} "insert_out1.txt")

add_executable(selection_sort_test SelectionSort_test.cc)
add_test(NAME selection_sort_test
  COMMAND selection_sort_test ${INPUT_FILE1} "select_out1.txt")

add_executable(merge_sort_test MergeSort_test.cc)
add_test(NAME merge_sort_test
  COMMAND merge_sort_test ${INPUT_FILE1} "merge_out1.txt")

add_executable(heap_sort_test HeapSort_test.cc)
add_test(NAME heap_sort_test
  COMMAND heap_sort_test ${INPUT_FILE1} "heap_out1.txt")

add_executable(quick_sort_test QuickSort_test.cc)
add_test(NAME quick_sort_test
  COMMAND quick_sort_test ${INPUT_FILE1} "quick_out1.txt")
