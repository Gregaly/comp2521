#!/usr/bin/python3
import csv
import os
import sys
import subprocess
import random


sizes = list(range(5, 100, 5)) + list(range(200, 900, 100)) + list(range(1000, 10000, 1000)) + list(range(10000, 100000, 10000)) + list(range(100000, 1000000, 100000))
sizesA = list(range(5, 100, 5)) + list(range(200, 900, 100)) + list(range(1000, 5000, 1000))
print(sizes)
iterations = 5

from subprocess import PIPE, run

def out(command):
	result = run(command, stdout=PIPE, stderr=PIPE, universal_newlines=True, shell=True)
	return result.stderr

def reversed(list, fileName, sortName):
	try:
		with open(fileName, "w") as file:
			# create initial file
			writer = csv.writer(file, delimiter=",")

			for size in list:

				print("testing size", size)

				# unsorted
				sum = 0
				for iter in range(iterations):
					myTime = out([f"./gen {size} D | /usr/bin/time --format=\"%U\" ./{sortName} > /dev/null ;"])

					sum += float(myTime)

				useIntAvg = '%s' % float('%.2g' % (sum / iterations))

				print("useIntList: {}".format(useIntAvg))

				writer.writerow([size, useIntAvg])
				file.flush()
	except BaseException as e:
		print("an exception happened!", e)

def sorted(list, fileName, sortName):
	try:
		with open(fileName, "w") as file:
			# create initial file
			writer = csv.writer(file, delimiter=",")

			for size in list:

				print("testing size", size)

				# unsorted
				sum = 0
				for iter in range(iterations):
					myTime = out([f"./gen {size} A | /usr/bin/time --format=\"%U\" ./{sortName} > /dev/null ;"])

					sum += float(myTime)

				useIntAvg = '%s' % float('%.2g' % (sum / iterations))

				print("useIntList: {}".format(useIntAvg))

				writer.writerow([size, useIntAvg])
				file.flush()
	except BaseException as e :
		print("an exception happened!", e)

def random(list, fileName, sortName):
	try:
		with open(fileName, "w") as file:
			# create initial file
			writer = csv.writer(file, delimiter=",")

			for size in list:

				print("testing size", size)

				# unsorted
				sum = 0
				for iter in range(iterations):
					myTime = out([f"./gen {size} R | /usr/bin/time --format=\"%U\" ./{sortName} > /dev/null ;"])

					sum += float(myTime)

				useIntAvg = '%s' % float('%.2g' % (sum / iterations))

				print("useIntList: {}".format(useIntAvg))

				writer.writerow([size, useIntAvg])
				file.flush()
	except BaseException as e:
		print("an exception happened!", e)

sorted(sizesA, "sortedA.csv", "sortA")
sorted(sizes, "sortedB.csv", "sortB")

#random(sizesA, "randomA.csv", "sortA")
#random(sizes, "randomB.csv", "sortB")

#reversed(sizesA, "reversedA.csv", "sortA")
#reversed(sizes, "reversedB.csv", "sortB")
