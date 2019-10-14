#include <fstream>
#include <sstream>
#include <string>
using namespace std;

bool isFuncName(string str);

bool isVarName(string str);

bool compareStr(string str1, string str2);

int main () {
	string line;
	bool isDeclaration;
	bool isSentence;
	bool thisEnded;

  	ifstream myfile ("test.obo");
  	if (myfile.is_open()) {
    	getline(myfile, line);
		Variables vars;
		stringstream ss(line);
		string word;

		/******************************START LINE*****************************/
		//Begin <Name>:

		/*It must have Begin keyword*/
		ss >> word;
		if (!compareStr(word, "Begin")) {
			/*If it's empty, it throws no error*/
			if (!(word.empty())) cout << "Error: missing \"Begin\" keyword in line 01" << endl;
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

		ss.str("");
		ss.clear();

		for (int i = 2; getline (myfile, line); i++) {
      		/*Line is put into a stream*/
			ss << line;
			ss >> word;
			if (compareStr(word, "//") || compareStr(word.substr(0,2), "//")) {
				ss.str("");
				ss.clear();
				continue;
			}
			string newVariable;

			if (word.at(0) == '@') {
				/************************DECLARATION**************************/
				//@var <= Num
				/*Name of variable*/
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
				/*Variable created*/
				vars.put(newVariable, 0);
			}
			else if (word.at(0) == '~') {
				/************************PRINT OR READ FUNCTION***************/
				//~Print var
				//~Print 2
				//~Read
				/*Print function comprobation*/
				if (compareStr(word.substr(1), "Print")) {
					ss >> word;
					try {
						float f = stof(word);
						cout << stof(word) << endl;
					}
					catch (invalid_argument& e) {
						try {
							float f = vars.get(word);
							cout << f << endl;
						}
						catch (const char* e) {
							cout << "Error: " << word << " was not declared, line " << i << endl;
							myfile.close();
							return 0;
						}
					}
				}
				
				else if (compareStr(word.substr(1), "Read")) {
					string aux;
					cin >> aux;
				}

				else {
					cout << "Warning: unknown function in line " << i << endl;
					continue;
				}
			}
			else {
				if (!ss) {
					ss.str("");
					ss.clear();
					continue;
				}
				/************************ASSIGNATION**************************/
				//var = 5 + 2
				//num = var + 3
				/*Name of variable to assign*/
				string var_to_assign;
				try {
					vars.get(word);
					var_to_assign = word;
				}
				catch (const char* e) {
					cout << e << " in line " << i << endl;
					myfile.close();
					return 0;
				}
				
				/*Assignation operator*/
				ss >> word;
				if (!compareStr(word, "=")) {
					cout << "Error: expected \"=\" in line " << i << endl;
					myfile.close();
					return 0;
				}

				ss >> word;
				vector <float> sol;
				int count = 0;
				while(ss)
				{	
					if(count > 2)
					{
						cout << "Error: wrong operation format in line " << i << endl;
					}
					
					if(isVarName(word))
					{ 
						sol.push_back(vars.get(word));
						count++;
					}
					else if (isdigit(word[0]))
					{
						sol.push_back(stof(word));
						count++;
					}
					else if(word[0] == '~')
					{
						if(compareStr(word.substr(1), "Read"))
						{
							float a;
							cin >> a;
							sol.push_back(a);
							count++;
						}
						else
						{
							cout << "Error: invalid function in line " << i << endl;
						}
					}
					else if(word == "+")
					{
					if(count < 2){cout << "Error: missing arguments in line " << i << endl;
          return 0;}
					float a = sol.back();
					sol.pop_back();
					float b = sol.back();
					sol.pop_back();
					sol.push_back(a + b);
					count = 1;
					}
					else if(word == "*")
					{
						if(count < 2){cout << "Error: missing arguments in line " << i << endl;
            return 0;}
						float a = sol.back();
						sol.pop_back();
						float b = sol.back();
						sol.pop_back();
						sol.push_back(a * b);
						count = 1;
					}
					else if(word == "-")
					{
						if(count < 2){cout << "Error: missing arguments in line " << i << endl;
            return 0;}
						float a = sol.back();
						sol.pop_back();
						float b = sol.back();
						sol.pop_back();
						sol.push_back(a - b);
						count = 1;
					}
					else if(word == "/")
					{
						if(count < 2){cout << "Error: missing arguments in line " << i << endl;
            return 0;}
						float a = sol.back();
						sol.pop_back();
						float b = sol.back();
						sol.pop_back();
						sol.push_back(a / b);
						count = 1;
					}
					ss >> word;
				}
				vars.put(var_to_assign, sol.back());
			   	}
						ss.str("");
						ss.clear();
					}
					myfile.close();
				}
				else cout << "Error: unable to open file"; 
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
				case '?': case '@': case '*': case '=': case '+':
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
				case '0': case '1': case '2': case '3': case '4': case '5':
				case '6': case '7': case '8': case '9':
				case '!': case '#': case '$': case '<': case '>': case ':':
				case '/': case '?': case '_': case '`': case '~':
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
