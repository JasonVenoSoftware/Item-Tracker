import re
import string

def printsomething():
	print("Hello from python!")

def PrintMe(v):
	print("You sent me: " + v)
	return 100;

def SquareValue(v):
	return v * v

def OptionOne():
	f = open("inputfile.txt")
	contents = f.read()
	f.close()

	frequency = []
	items = []
	contents = contents.split()

	for i in contents: # Iterates through inputfile, outputs item and frequency, each once
		frequency = contents.count(i)
		if i not in items:
			print(i, frequency)
		items.append(i)

def OptionTwo(item):
	f = open("inputfile.txt")
	contents = f.read()
	f.close()

	frequency = 0
	contents = contents.split()

	for i in contents: # Iterates through inputfile, adds 1 to frequency each time selected item is found
		if i == item:
			frequency += 1

	return frequency; # Returns frequency to C++ to be printed with selected item

def OptionThree():
	f = open("inputfile.txt")
	contents = f.read()
	f.close()

	frequencies = []
	items = []
	contents = contents.split()

	with open("frequency.dat", "w") as myfile:
		for i in contents: # Iterates through inputfile, writes item and frequency to frequency.dat, each once
			frequencies = contents.count(i)
			if i not in items:
				myfile.write("{} {}\n".format(i, frequencies))
			items.append(i)
	
