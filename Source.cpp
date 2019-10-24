#include "HashTable.h"
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

bool isFuncName(string str);

bool isVarName(string str);

bool compareStr(string str1, string str2);

float operar(string word, float a, float b)
{
	if (word == "+")
	{
		return a + b;
	}
	else if (word == "*")
	{
		return a * b;
	}
	else if (word == "-")
	{
		return a - b;
	}
	else if (word == "/")
	{
		return a / b;
	}
	else
	{
		return 0;
	}
}

int main()
{
	string line;

	cout << "Ingrese el nombre del archivo a abrir:" << endl;
	getline(cin, line);
	ifstream myfile("./" + line);

	if (myfile.is_open())
	{
		getline(myfile, line);
		Variables vars;
		stringstream ss(line);
		string word;

		/******************************START LINE*****************************/
		//Begin <Name>:

		/*It must have Begin keyword*/
		ss >> word;
		if (!compareStr(word, "Begin"))
		{
			/*If it's empty, it throws no error*/
			if (!(word.empty()))
				cout << "Error: missing \"Begin\" keyword in line 01" << endl;
			myfile.close();
			return 0;
		}

		/*Function name must have the dots at the end*/
		ss >> word;
		if (!(word.at(word.size() - 1) == ':'))
		{
			cout << "Error: expected \":\" in line 1" << endl;
			myfile.close();
			return 0;
		}

		/*Function name must have correct characters*/
		if (!isFuncName(word))
		{
			cout << "Error: bad name of function in line 1" << endl;
			myfile.close();
			return 0;
		}

		/*It must have no more words*/
		ss >> word;
		if (ss)
		{
			cout << "Error: too many arguments" << endl;
			myfile.close();
			return 0;
		}

		ss.str("");
		ss.clear();

		for (int i = 2; getline(myfile, line); i++)
		{
			/*Line is put into a stream*/
			ss << line;
			ss >> word;
			if (compareStr(word, "//") || compareStr(word.substr(0, 2), "//"))
			{
				ss.str("");
				ss.clear();
				continue;
			}
			string newVariable;
			if (word.at(0) == '@')
			{
				/************************DECLARATION**************************/
				//@var <= Num
				/*Name of variable*/
				newVariable = word.substr(1);
				if (compareStr(newVariable, "Num"))
				{
					cout << "Error: Num is an OBO keyword, use another name in line " << i << endl;
					myfile.close();
					return 0;
				}

				if (!isVarName(newVariable))
				{
					cout << "Error: incorrect name in line " << i << endl;
					myfile.close();
					return 0;
				}

				/*Assignation operar*/
				ss >> word;
				if (!compareStr(word, "<="))
				{
					cout << "Error: expected \"<=\" in line " << i << endl;
					myfile.close();
					return 0;
				}

				/*Data type*/
				ss >> word;
				if (!compareStr(word, "Num"))
				{
					cout << "Error: unknown data type in line " << i << endl;
					myfile.close();
					return 0;
				}
				/*Variable created*/
				vars.put(newVariable, 0);
			}
			else if (word.at(0) == '~')
			{
				/************************PRINT OR READ FUNCTION***************/
				//~Print var
				//~Print 2
				//~Read
				/*Print function comprobation*/
				if (compareStr(word.substr(1), "Print"))
				{
					ss >> word;
					try
					{
						float f = stof(word);
						cout << stof(word) << endl;
					}
					catch (invalid_argument &e)
					{
						try
						{
							float f = vars.get(word);
							cout << f << endl;
						}
						catch (const char *e)
						{
							cout << "Error: " << word << " was not declared, line " << i << endl;
							myfile.close();
							return 0;
						}
					}
				}

				else if (compareStr(word.substr(1), "Read"))
				{
					string aux;
					cin >> aux;
				}

				else
				{
					cout << "Warning: unknown function in line " << i << endl;
					continue;
				}
			}
			else
			{
				if (!ss)
				{
					ss.str("");
					ss.clear();
					continue;
				}

				if(compareStr(word, "End")) {
					cout << "End line reached!" << endl;
					break;
				}
				/************************ASSIGNATION**************************/
				//var = 5 + 2
				//num = var + 3
				/*Name of variable to assign*/
				string var_to_assign;
				try
				{
					vars.get(word);
					var_to_assign = word;
				}
				catch (const char *e)
				{
					cout << e << " in line " << i << endl;
					myfile.close();
					return 0;
				}

				/*Assignation operar*/
				ss >> word;
				if (!compareStr(word, "="))
				{
					cout << "Error: expected \"=\" in line " << i << endl;
					myfile.close();
					return 0;
				}

				ss >> word;
				vector<float> numeros;
				vector<string> operadores;
				while (ss)
				{
					if (isVarName(word))
					{
						if (numeros.size() > 0)
						{
							float temp = numeros.back();
							numeros.pop_back();
							numeros.push_back(operar(operadores.back(), temp, vars.get(word)));
							operadores.pop_back();
						}
						else
						{
							numeros.push_back(vars.get(word));
						}
					}
					else if (isdigit(word[0]))
					{
						try
						{
							if (numeros.size() > 0)
							{

								float temp = numeros.back();
								numeros.pop_back();
								numeros.push_back(operar(operadores.back(), temp, stof(word)));
								operadores.pop_back();
							}
							else
							{
								numeros.push_back(stof(word));
							}
						}
						catch (exception e)
						{
							cout << "Error, not a number in line " << i << endl;
							return 0;
						}
					}
					else if (word[0] == '~')
					{
						if (compareStr(word.substr(1), "Read"))
						{
							float a;
							cin >> a;
							if (numeros.size() > 0)
							{
								float temp = numeros.back();
								numeros.pop_back();
								numeros.push_back(operar(operadores.back(), temp, a));
								operadores.pop_back();
							}
							else
							{
								numeros.push_back(a);
							}
						}
						else
						{
							cout << "Error: invalid function in line " << i << endl;
						}
					}
					else if (word == "(")
					{
						numeros.push_back(1);
						operadores.push_back("*");
					}
					else if (word == ")")
					{
						float temp = numeros.back();
						numeros.pop_back();
						float temp2 = numeros.back();
						numeros.pop_back();
						numeros.push_back(operar(operadores.back(), temp2, temp));
						operadores.pop_back();
					}
					else if (word == "+" || word == "-" || word == "*" || word == "/")
					{
						operadores.push_back(word);
					}
					ss >> word;
				}
				vars.put(var_to_assign, numeros.back());
			}
			ss.str("");
			ss.clear();
		}
		myfile.close();
	}
	else
		cout << "Error: unable to open file";
	system("pause");
	return 0;
}

bool isFuncName(string str)
{
	for (char c : str)
	{
		if (c == str.at(0))
		{
			switch (c)
			{
			case '0':
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
			case '|':
			case '!':
			case '#':
			case '$':
			case '%':
			case '&':
			case '(':
			case ')':
			case '[':
			case ']':
			case '{':
			case '}':
			case '.':
			case '<':
			case '>':
			case ':':
			case ';':
			case '/':
			case '\\':
			case '?':
			case '@':
			case '*':
			case '=':
			case '+':
			case '^':
			case '`':
			case ',':
			case '-':
			case '~':
				return false;
			}
		}
		switch (c)
		{
		case 'A':
		case 'B':
		case 'C':
		case 'D':
		case 'E':
		case 'F':
		case 'G':
		case 'H':
		case 'I':
		case 'J':
		case 'K':
		case 'L':
		case 'M':
		case 'N':
		case 'O':
		case 'P':
		case 'Q':
		case 'R':
		case 'S':
		case 'T':
		case 'U':
		case 'V':
		case 'W':
		case 'X':
		case 'Y':
		case 'Z':
		case 'a':
		case 'b':
		case 'c':
		case 'd':
		case 'e':
		case 'f':
		case 'g':
		case 'h':
		case 'i':
		case 'j':
		case 'k':
		case 'l':
		case 'm':
		case 'n':
		case 'o':
		case 'p':
		case 'q':
		case 'r':
		case 's':
		case 't':
		case 'u':
		case 'v':
		case 'w':
		case 'x':
		case 'y':
		case 'z':
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
		case '!':
		case '#':
		case '$':
		case '%':
		case '&':
		case '[':
		case ']':
		case '{':
		case '}':
		case '<':
		case '>':
		case ':':
		case '/':
		case '\\':
		case '?':
		case '@':
		case '*':
		case '+':
		case '^':
		case '_':
		case '`':
		case '-':
		case '~':
			break;
		default:
			return false;
		}
	}
	return true;
}

bool isVarName(string str)
{
	for (char c : str)
	{
		if (c == str.at(0))
		{
			switch (c)
			{
			case '0':
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
			case '|':
			case '!':
			case '#':
			case '$':
			case '%':
			case '&':
			case '(':
			case ')':
			case '[':
			case ']':
			case '{':
			case '}':
			case '.':
			case '<':
			case '>':
			case ':':
			case ';':
			case '/':
			case '?':
			case '@':
			case '*':
			case '=':
			case '+':
			case '^':
			case '`':
			case ',':
			case '-':
			case '~':
				return false;
			}
		}
		switch (c)
		{
		case 'A':
		case 'B':
		case 'C':
		case 'D':
		case 'E':
		case 'F':
		case 'G':
		case 'H':
		case 'I':
		case 'J':
		case 'K':
		case 'L':
		case 'M':
		case 'N':
		case 'O':
		case 'P':
		case 'Q':
		case 'R':
		case 'S':
		case 'T':
		case 'U':
		case 'V':
		case 'W':
		case 'X':
		case 'Y':
		case 'Z':
		case 'a':
		case 'b':
		case 'c':
		case 'd':
		case 'e':
		case 'f':
		case 'g':
		case 'h':
		case 'i':
		case 'j':
		case 'k':
		case 'l':
		case 'm':
		case 'n':
		case 'o':
		case 'p':
		case 'q':
		case 'r':
		case 's':
		case 't':
		case 'u':
		case 'v':
		case 'w':
		case 'x':
		case 'y':
		case 'z':
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
		case '!':
		case '#':
		case '$':
		case '<':
		case '>':
		case ':':
		case '/':
		case '?':
		case '_':
		case '`':
		case '~':
			break;
		default:
			return false;
		}
	}

	return true;
}

bool compareStr(string str1, string str2)
{
	return str1.compare(str2) == 0;
}
