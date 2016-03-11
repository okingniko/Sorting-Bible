# CMake generated Testfile for 
# Source directory: /root/Desktop/SortBible/tests
# Build directory: /root/Desktop/SortBible/tests
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(insertion_sort_test "/root/Desktop/SortBible/tests/insertion_sort_test" "sort_file.txt" "insert_out1.txt")
add_test(selection_sort_test "/root/Desktop/SortBible/tests/selection_sort_test" "sort_file.txt" "select_out1.txt")
add_test(merge_sort_test "/root/Desktop/SortBible/tests/merge_sort_test" "sort_file.txt" "merge_out1.txt")
add_test(heap_sort_test "/root/Desktop/SortBible/tests/heap_sort_test" "sort_file.txt" "heap_out1.txt")
add_test(quick_sort_test "/root/Desktop/SortBible/tests/quick_sort_test" "sort_file.txt" "quick_out1.txt")
