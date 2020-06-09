#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

string inA;
string inB;

extern "C" {
extern void loch();
extern int loch1();
extern unsigned int loch2(unsigned int* arr);
void mul(unsigned int* valA, unsigned int* valB, unsigned int* result, unsigned int sizeA, unsigned int sizeB);
}

unsigned int charToInt(char c);
void stringToArr(string s, unsigned int* arr);

int main()
{
	char c;
	printf("Odczyt z pliku?	t/n");
	//scanf("%d", c);
	cin>>c;
	if(c=='t' || c=='T')
	{
		printf("Podaj nazwę pliku wejściowego:\n");
		string in;
		cin>>in;
		ifstream inFile (in);
 		if (inFile.is_open())
  		{
    			//getline (inFile,inA);
    			//getline (inFile,inB);
			inFile >> inA;
			inFile >> inB;
    
    			inFile.close();
  		}
		else cout << "Unable to open file"; 
	
	}	
	else
	{
		printf("Podaj pierwszy czynnik iloczynu:\n");
		cin>>inA;
		printf("Podaj drugi  czynnik iloczynu:\n");
		cin>>inB;
	}	
	if(inA.size()%8!=0)
	{
		for(int i=0; i<inA.size()%8; i++)
		{
			inA.insert(0, 1, '0');
		}
	}
	unsigned int  sizeA = inA.size()/8;	
	if(inB.size()%8!=0)
	{
		for(int i=0; i<inB.size()%8; i++)
		{
			inB.insert(0, 1, '0');
		}
	}
	unsigned int sizeB = inB.size()/8;
//	cout<<inA<<endl;
//	cout<<inB<<endl;

	unsigned int* valA = new unsigned int [sizeA];
	unsigned int* valB = new unsigned int [sizeB];
	unsigned int* result = new unsigned int [sizeA + sizeB];
	stringToArr(inA,  valA);
	stringToArr(inB,  valB);
	for (int i=0; i<sizeA + sizeB; i++)
	{
		*(result + i) = 0;
	}

/*	printf("%d\n", sizeA);
	for(int i=0;i<sizeA;i++) 
	{	
		printf("%d ", i);
	}printf("aaaaaaaaaaaaaaaaaaa\n");
	for(int i=0;i<sizeB;i++) 
	{	
		printf("%d ", i);
	}
	printf("aaaaaaaaaaaaaaaaa\n");
	//loch2(valA);
*/
	mul(valA, valB, result, sizeA, sizeB);
	delete valA;
	delete valB;
	for(int i=0;i<sizeA;i++) 
	{	
		printf("%d ", i);
	}

	int r = *(result + sizeA + sizeB -1);
	if (r==0) sizeA--;
	printf("%x ", *(result + sizeA + sizeB -1 ));
	for(int i=sizeA + sizeB -2;i>=0 ;i--)
	{	
		
		printf("%08x ", *(result + i));
	}
	//printf("aaaaaaaaaaa\n");
	delete result;
}

unsigned int charToInt(char c){
	if (c > 64) return c-55;
	if (c > 47) return c-48;
	return -1;
}

void stringToArr(string s, unsigned int* arr){
	unsigned int multiplier=268435456;
	*(arr + s.size()/8-1)=0;
	for(int i=0, j=s.size()/8-1;i<s.size();i++)
	{
		//printf("%d ", *(arr + j)); //komórka arr przed dodawaniem
		*(arr + j) += charToInt(s[i])*multiplier;
		//printf("%d ", *(arr + j)); //komorka arr po dodawaniu
		//printf("%d %d  ", charToInt(s[i]), multiplier); // wartosc hex -> dec oraz mnoznik

		multiplier/=16;
		if (i % 8 == 7) 
		{
			j--;
			*(arr + j) =0;
			multiplier=268435456;
			//printf("\n");
		}
	}	
	//printf("\n");
}

