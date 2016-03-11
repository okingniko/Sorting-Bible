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
