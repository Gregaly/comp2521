#!python3
import csv
import os
import sys
import subprocess
import random


sizes = list(range(5, 100, 5)) + list(range(200, 900, 100)) + list(range(1000, 10000, 1000)) + list(range(10000, 100000, 10000)) + list(range(100000, 1000000, 100000))
print(sizes)
iterations = 5

from subprocess import PIPE, run

def out(command):
	result = run(command, stdout=PIPE, stderr=PIPE, universal_newlines=True, shell=True)
	return result.stderr

def sorted(list):
	with open("sortedB.csv", "w") as file:
		# create initial file
		writer = csv.writer(file, delimiter=",")
		
		for size in list:
			
			print("testing size", size)

			# unsorted
			sum = 0
			for iter in range(iterations):
				myTime = out([f"./gen {size} A | /usr/bin/time --format=\"%U\" ./sortB > /dev/null ;"])

				sum += float(myTime)

			useIntAvg = '%s' % float('%.2g' % (sum / iterations))

			print("useIntList: {}".format(useIntAvg))

			writer.writerow([size, useIntAvg])
			file.flush()

def random():
	with open("out.csv", "w") as file:
		# create initial file
		writer = csv.writer(file, delimiter=",")
		
		for size in sizes:
			
			print("testing size", size)

			# unsorted
			sum = 0
			for iter in range(iterations):
				myTime = out([f"./gen {size} R | /usr/bin/time --format=\"%U\" ./sortA > /dev/null ;"])

				sum += float(myTime)

			useIntAvg = '%s' % float('%.2g' % (sum / iterations))

			print("useIntList: {}".format(useIntAvg))

			writer.writerow([size, useIntAvg])
			file.flush()

sorted(sizes)
