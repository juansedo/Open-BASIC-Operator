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

  	ifstream myfile ("example.txt");
  	if (myfile.is_open()) {
    	getline(myfile, line);
		Variables v;
		stringstream first(line);
		string word;

		/*It must have Begin keyword*/
		first >> word;
		if (!word.compare("Begin")) {
			cout << "Error: missing \"Begin\" keyword in line 01";
			return 0;
		}
		
		/*It must have the dots at the end*/
		first >> word;
		if (!(word.at(word.size()) == ':')) {
			cout << "Error: expected \":\" in line 1";
			return 0;
		}
		if(!isFuncName(word)) {
			cout << "Error: expected \":\" in line 1";
			return 0;
		}

		if (first) {
			cout << "Error: too many arguments";
			return 0;
		}

		while ( getline (myfile, line)) {
      		/*Line is put into a stream*/
			stringstream ss(line);
			string word;
			string newVariable;
			for (int i = 0; ss; i++) {
				/*Each word of line is evaluated*/
				
				ss >> word;

				/*We search does what mean the word*/
				switch(word.at(0)) {
					case '@':
						//declaration case
						if (!newVariable.empty) {
							cout << "Error: wrong declaration in line " << i + 1;
							return 0;
						}
						newVariable = word.substr(1);
						break;
					case '~':
						//Function case
						break;
					default:
						//Expression case
						string word2;
						v.put(word, );
						break;
				}
			}
    	}
    	myfile.close();
  	}
  	else cout << "Error: unable to open file"; 
	
	system("pause");
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
				case '@': case '*': case '=': case '+': case '^': case '_':
				case '`': case '-': case '~':
					break;
				default:
					return false;
			}
	}
	return true;
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

class Word {
private:
	string str;
	bool isDeclaration;
public:
	
};

class Expression {

};