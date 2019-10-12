#include "HashTable.h"
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

int main () {
	string line;
	bool isDeclaration;
	bool isSentence;
	bool thisEnded;

  	ifstream myfile ("./BNF and examples/example.obo");
  	if (myfile.is_open()) {
    	getline(myfile, line);
		Variables v;
		stringstream ss(line);
		string word;

		/******************************START LINE*****************************/
		//Begin <Name>:

		/*It must have Begin keyword*/
		ss >> word;
		if (!compareStr(word, "Begin")) {
			/*If it's empty, it throws no error*/
			if (!word.empty) cout << "Error: missing \"Begin\" keyword in line 01" << endl;
			myfile.close();
			return 0;
		}
		
		/*Function name must have the dots at the end*/
		ss >> word;
		if (!(word.at(word.size()-1) == ':')) {
			cout << "Error: expected \":\" in line 1" << endl;
			myfile.close();
			return 0;
		}

		/*Function name must have correct characters*/
		if(!isFuncName(word)) {
			cout << "Error: bad name of function in line 1" << endl;
			myfile.close();
			return 0;
		}


		/*It must have no more words*/
		ss >> word;
		if (ss) {
			cout << "Error: too many arguments" << endl;
			myfile.close();
			return 0;
		}

		for (int i = 2; getline (myfile, line); i++) {
      		/*Line is put into a stream*/
			ss << line;
			word = "";
			string newVariable;

			if (line.at(0) == '@') {
				/************************DECLARATION**************************/
				//@var <= Num
				/*Name of variable*/
				ss >> word;
				newVariable = word.substr(1);
				if (compareStr(newVariable, "Num")) {
					cout << "Error: Num is an OBO keyword, use another name in line " << i << endl;
					myfile.close();
					return 0;
				}

				if (!isVarName(newVariable)) {
					cout << "Error: incorrect name in line " << i << endl;
					myfile.close();
					return 0;
				}


				/*Assignation operator*/
				ss >> word;
				if (!compareStr(word, "<=")) {
					cout << "Error: expected \"<=\" in line " << i << endl;
					myfile.close();
					return 0;
				}

				/*Data type*/
				ss >> word;
				if (!compareStr(word, "Num")) {
					cout << "Error: unknown data type in line " << i << endl;
					myfile.close();
					return 0;
				}





			}
			/*
			if () {

			}*/
    	}
    	myfile.close();
  	}
  	else cout << "Error: unable to open file"; 
	
	//system("pause");
	return 0;
}

bool isFuncName(string str) {
	for (char c: str) {
		if (c == str.at(0)) {
			switch(c) {
				case '0': case '1': case '2': case '3': case '4': case '5':
				case '6': case '7': case '8': case '9':
				case '|': case '!': case '#': case '$': case '%': case '&':
            	case '(': case ')': case '[': case ']': case '{': case '}': 
				case '.': case '<': case '>': case ':': case ';': case '/':
				case '\\': case '?':case '@': case '*': case '=': case '+':
				case '^': case '`': case ',': case '-': case '~':
				return false;
			}
		}
		switch(c) {
				case 'A': case 'B': case 'C': case 'D': case 'E': case 'F': case 'G':
                case 'H': case 'I': case 'J': case 'K': case 'L': case 'M': case 'N':
                case 'O': case 'P': case 'Q': case 'R': case 'S': case 'T': case 'U':
                case 'V': case 'W': case 'X': case 'Y': case 'Z':
                case 'a': case 'b': case 'c': case 'd': case 'e': case 'f': case 'g':
                case 'h': case 'i': case 'j': case 'k': case 'l': case 'm': case 'n':
                case 'o': case 'p': case 'q': case 'r': case 's': case 't': case 'u':
                case 'v': case 'w': case 'x': case 'y': case 'z':
                case 'Á': case 'É': case 'Í': case 'Ó': case 'Ú': case 'Ñ':
                case 'á': case 'é': case 'í': case 'ó': case 'ú': case 'ñ':
				case '0': case '1': case '2': case '3': case '4': case '5':
				case '6': case '7': case '8': case '9':
				case '!': case '#': case '$': case '%': case '&':
            	case '[': case ']': case '{': case '}': 
				case '<': case '>': case ':': case '/': case '\\': case '?':
				case '@': case '*': case '+': case '^': case '_':
				case '`': case '-': case '~':
					break;
				default:
					return false;
			}
	}
	return true;
}

bool isVarName(string str) {
	for (char c: str) {
		if (c == str.at(0)) {
			switch(c) {
				case '0': case '1': case '2': case '3': case '4': case '5':
				case '6': case '7': case '8': case '9':
				case '|': case '!': case '#': case '$': case '%': case '&':
            	case '(': case ')': case '[': case ']': case '{': case '}': 
				case '.': case '<': case '>': case ':': case ';': case '/':
				case '\\': case '?':case '@': case '*': case '=': case '+':
				case '^': case '`': case ',': case '-': case '~':
				return false;
			}
		}
		switch(c) {
				case 'A': case 'B': case 'C': case 'D': case 'E': case 'F': case 'G':
                case 'H': case 'I': case 'J': case 'K': case 'L': case 'M': case 'N':
                case 'O': case 'P': case 'Q': case 'R': case 'S': case 'T': case 'U':
                case 'V': case 'W': case 'X': case 'Y': case 'Z':
                case 'a': case 'b': case 'c': case 'd': case 'e': case 'f': case 'g':
                case 'h': case 'i': case 'j': case 'k': case 'l': case 'm': case 'n':
                case 'o': case 'p': case 'q': case 'r': case 's': case 't': case 'u':
                case 'v': case 'w': case 'x': case 'y': case 'z':
                case 'Á': case 'É': case 'Í': case 'Ó': case 'Ú': case 'Ñ':
                case 'á': case 'é': case 'í': case 'ó': case 'ú': case 'ñ':
				case '0': case '1': case '2': case '3': case '4': case '5':
				case '6': case '7': case '8': case '9':
				case '!': case '#': case '$': case '<': case '>': case ':':
				case '/': case '\\': case '?': case '_': case '`': case '~':
					break;
				default:
					return false;
			}
	}
	return true;
}

bool compareStr(string str1, string str2) {
	return str1.compare(str2) == 0;
}

int declaration(char* sentencia) 
{
	return 0;
}

int assign(char* sentencia)
{
	return 0;
}

int func(char* sentencia)
{
	return 0;
}