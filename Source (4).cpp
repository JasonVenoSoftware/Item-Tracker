#include <Python.h>
#include <iostream>
#include <Windows.h>
#include <cmath>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

/*
Description:
	To call this function, simply pass the function name in Python that you wish to call.
Example:
	callProcedure("printsomething");
Output:
	Python will print on the screen: Hello from python!
Return:
	None
*/
void CallProcedure(string pName)
{
	char* procname = new char[pName.length() + 1];
	std::strcpy(procname, pName.c_str());

	Py_Initialize();
	PyObject* my_module = PyImport_ImportModule("pythonfile");
	PyErr_Print();
	PyObject* my_function = PyObject_GetAttrString(my_module, procname);
	PyObject* my_result = PyObject_CallObject(my_function, NULL);
	Py_Finalize();

	delete[] procname;
}

/*
Description:
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("PrintMe","Test");
Output:
	Python will print on the screen:
		You sent me: Test
Return:
	100 is returned to the C++
*/
int callIntFunc(string proc, string param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	char* paramval = new char[param.length() + 1];
	std::strcpy(paramval, param.c_str());


	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"pythonfile");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(z)", paramval);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;
	delete[] paramval;


	return _PyLong_AsInt(presult);
}

/*
Description:
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("doublevalue",5);
Return:
	25 is returned to the C++
*/
int callIntFunc(string proc, int param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"pythonfile");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(i)", param);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;

	return _PyLong_AsInt(presult);
}

void histogram(string line) { // Splits each line in file, turns second part to int, prints number of '*' instead
	string word = "";
	for (auto x : line) { // Prints 'Spinach \n 5' instead of 'Spinach 5'. 
		if (x == ' ') {
			cout << word;
			word = "";
		}
		else {
			word = word + x;
		}
	}
	cout << " ";
	int frequency = stoi(word);
	for (int i = 0; i < frequency; i++) { // Prints '*' instead of frequency.  Ex. '***' instead of '3'.
		cout << "*";
	}
	cout << endl;
}


void read_file() { // Opens and reads frequency.dat, passes each line to histogram().  
	string str;
	vector<string> input_list;
	ifstream inFS;
	inFS.open("frequency.dat");
	if (!inFS.is_open()) {
		cout << "Couldn't open file " << endl;
	}
	while (getline(inFS, str)) {
		if (str.size() > 0) {
			input_list.push_back(str);
		}
	}
	inFS.close();

	for (int i = 0; i < input_list.size(); i++) {
		histogram(input_list.at(i));
	}
}


void display_menu() {
	string user_value;
	while (true) {
		cout << "1: List of items purchased with quantities. " << endl;
		cout << "2: Quantity of certain item. " << endl;
		cout << "3: Histogram of all items. " << endl;
		cout << "4: Exit program. " << endl;
		cout << "Choose an option: " << endl;
		cin >> user_value;
		if (user_value == "1") { // List of all item's frequencies
			CallProcedure("OptionOne");
		}
		else if (user_value == "2") { // Frequency of one specific item
			string option_two_item;
			cout << "What item are you looking for?  " << endl;
			cin >> option_two_item;
			cout << "'" << option_two_item << "' appears in the list ";
			cout << callIntFunc("OptionTwo", option_two_item);
			cout << " times.  " << endl;
		}
		else if (user_value == "3") { // Histogram of all item's frequencies
			CallProcedure("OptionThree");
			read_file();
		}
		else if (user_value == "4") {
			cout << "Exiting program." << endl;
			break;
		}
		else {
			cout << "Invalid option.  Please choose 1, 2, 3, or 4." << endl;
			continue;
		}
	}
}

void main()
{
	display_menu();
}
