#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream>
#include <chrono>
#include <iomanip>

using namespace std;


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
	string inA;
	string inB;

	char c;
	printf("Odczyt z pliku?	t/n");
	cin>>c;
	if(c=='t' || c=='T')
	{
		printf("Podaj nazwę pliku wejściowego:\n");
		string in;
		cin>>in;
		ifstream inFile (in);
 		if (inFile.is_open())
  		{
    			getline (inFile,inA);
    			getline (inFile,inB);
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
	unsigned int valA[sizeA];
	unsigned int valB[sizeB];
	unsigned int result[sizeA + sizeB];
	stringToArr(inA,  valA);
	stringToArr(inB,  valB);
	for (int i=0; i<sizeA + sizeB; i++)
	{
		*(result + i) = 0;
	}

	std::chrono::high_resolution_clock::time_point t1;
	std::chrono::high_resolution_clock::time_point t2;

	t1 = std::chrono::high_resolution_clock::now();
	mul(valA, valB, result, sizeA, sizeB);
	t2 = std::chrono::high_resolution_clock::now();

	int r = *(result + sizeA + sizeB -1);
	if (r==0) sizeA--;
	//printf("%x ", *(result + sizeA + sizeB -1 ));
	cout<<hex<<*(result + sizeA + sizeB -1 )<<" ";
	for(int i=sizeA + sizeB -2;i>=0 ;i--)
	{	
	//	printf("%08x ", *(result + i));
		cout<<hex<<setfill('0')<<setw(8)<<*(result + i)<<" ";
	}

	std::chrono::duration<double> pomiar = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);
std::cout <<"wykonanie mnozenia zajelo: "<<std::fixed<<std::setprecision (12) << pomiar.count() << " s"<<std::endl;


}

unsigned int charToInt(char c){
	if (c > 96) return c-87;
	if (c > 64) return c-55;
	if (c > 47) return c-48;
	return -1;
}

void stringToArr(string s, unsigned int* arr){
	unsigned int multiplier=268435456;
	*(arr + s.size()/8-1)=0;
	for(int i=0, j=s.size()/8-1;i<s.size();i++)
	{
		*(arr + j) += charToInt(s[i])*multiplier;
		multiplier/=16;
		if (i % 8 == 7) 
		{
			j--;
			*(arr + j) =0;
			multiplier=268435456;
		}
	}	
}
