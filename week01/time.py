import csv
import os
import sys
import subprocess
import random


sizes = list(range(1000, 10000, 1000)) + list(range(10000, 100001, 5000)) 
print(sizes)
iterations = 5

def gen_files():

	os.system("./randList {} > /tmp/nums".format(size))
	os.system("sort -n /tmp/nums > /tmp/numsSorted")
	os.system("sort -nr /tmp/nums > /tmp/numsReversed")




from subprocess import PIPE, run

def out(command):
    result = run(command, stdout=PIPE, stderr=PIPE, universal_newlines=True, shell=True)
    return result.stderr

with open("out.csv", "w") as out
	# create initial file
	out = csv.writer(out, delimiter=",")
	
	for size in sizes:
		
		print("testing size", size)

		for fileName,csv, type in zip(["/tmp/nums", "/tmp/numsSorted", "/tmp/numsReversed"], [normal, sorted, reversed], ["unsorted", "sorted", "reversed"]):
			# unsorted
			totalMy = 0
			totalSort = 0
			for iter in range(iterations):
				gen_files()
				myTime = out(["/usr/bin/time -f %e ./useIntList < {} >/dev/null".format(fileName)])
				sortTime = out(["/usr/bin/time -f %e sort -n < {} > /dev/null".format(fileName)])

				totalMy += float(myTime)
				totalSort += float(sortTime)

			useIntAvg = '%s' % float('%.2g' % (totalMy / iterations))
			useSortAvg = '%s' % float('%.2g' % (totalSort / iterations))

			print("useIntList:{:10s}: {}".format(type, useIntAvg))
			print("sort      :{:10s}: {}".format(type, useSortAvg))

			csv.writerow([size, iterations, useIntAvg, useSortAvg])


