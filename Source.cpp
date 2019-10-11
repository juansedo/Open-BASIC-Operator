#include "HashTable.h"
#include <fstream>
#include <string>
using namespace std;
	

int main()
{
	char cadena[128];
	ifstream fe("C:\\Users\\juans\\Downloads\\KY\\obito.txt");
	string partes[20];
	while (!fe.eof()) {
		fe >> cadena;
		bool blank = false;
		int pos = -1;
		if (cadena[0] != ' ') 
		{
			pos = 0;
		}
		for (int i = 0; i < sizeof(cadena); ++i) 
		{
			if (cadena[i] == ' ' && !blank) 
			{
				pos++;
				blank = true;
			}
			if (cadena[i] != ' ') 
			{
				partes[pos] += cadena[i];
				blank = false;
			}
		}
		if (partes[0][1] == '@') 
		{	
			//declaration(cadena);
		}
		else if (partes[0][1] == '~')
		{
			//func(cadena);
		}
		else if (partes[0][1] == '*')
		{
			//assign(cadena);
		}
		else 
		{
			//throw "invalid command";
		}
	}
	fe.close();
	system("pause");
	return 0;
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
