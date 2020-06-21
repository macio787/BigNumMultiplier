#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream>
#include <chrono>
#include <iomanip>
#include <math.h>
#include <vector>

using namespace std;

unsigned long long  charToInt(char c);
void equalizeLength(string &str1, string &str2);
vector<unsigned long long> naive(const vector<unsigned int>& a, const vector<unsigned int>& b);
vector<unsigned long long> karatsuba(const vector<unsigned int>& a, const vector<unsigned int>& b);
void setForOutput(vector<unsigned long long>& output);
vector<unsigned int> stringToArr(string s);
string makeLenghtPowerOf2 (string s);

unsigned long long base = 0x100000000;
const int lenForNaive = 10;

int main()
{
	string inA;
	string inB;
	char c;
	printf("Odczyt z pliku?	t/n");
	cin>>c;
	if(c=='t' || c=='T')
	{
		printf("Podaj nazwe pliku wejsciowego:\n");
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



    equalizeLength(inA, inB);
	inA=makeLenghtPowerOf2(inA);
    inB=makeLenghtPowerOf2(inB);

    vector<unsigned int> valA = stringToArr(inA);
    vector<unsigned int> valB = stringToArr(inB);
    vector<unsigned long long> result;

	chrono::high_resolution_clock::time_point t1;
	chrono::high_resolution_clock::time_point t2;

	t1 = chrono::high_resolution_clock::now();
	result = karatsuba(valA, valB);
	t2 = chrono::high_resolution_clock::now();

	vector<unsigned long long> tra = naive(valA,valB);

    setForOutput(result);
    setForOutput(tra);

	for (int i=result.size()-1; i>=0; i--)
	{
	    if(result[i]==0)continue;
		cout<<hex<<setfill('0')<<setw(8)<<result[i];
	}

	cout<<endl;

	chrono::duration<double> pomiar = chrono::duration_cast<chrono::duration<double>>(t2 - t1);
cout <<"wykonanie mnozenia zajelo: "<<fixed<<setprecision (12) << pomiar.count() << " s"<<endl;


}

unsigned long long charToInt(char c)
{
	if (c > 96) return c-87;
	if (c > 64) return c-55;
	if (c > 47) return c-48;
	return -1;
}

void equalizeLength(string &str1, string &str2)
{
    int len1 = str1.size();
    int len2 = str2.size();
    if (len1 < len2)
    {
        for (int i = 0 ; i < len2 - len1 ; i++)
        {
                        str1.insert(0,1,'0');
        }
    }
    else if (len1 > len2)
    {
        for (int i = 0 ; i < len1 - len2 ; i++)
        {
            str2.insert(0,1,'0');
        }
    }
}

vector<unsigned long long> naive(const vector<unsigned int>& a, const vector<unsigned int>& b)
{
    size_t length = a.size(); // rozmiar tablic
    vector<unsigned long  long> res(2 * length); // tablica wynikowa
    unsigned long long buf=0; // bufor na wynik czastkowy
    for (int i = 0; i < length; ++i)
    {
        for (int j = 0; j < length; ++j)
        {
            buf = (unsigned long long)a[i] * b[j];
            if(0xffffffff-res[i+j] < (buf<<32)>>32) // wykrycie i obsluga przeniesienia
            {
                int k=1;
                while(res[i+j+k]>=0xffffffff)
                {
                    res[i+j+k]=0;
                    k++;
                }
                res[i+j+k] +=1;
            }
            res[i+j] += (buf<<32)>>32;
            if(0xffffffff-res[i+j+1] < buf>>32) // wykrycie i obsluga przeniesienia
            {
                int k=2;
                while(res[i+j+k]>=0xffffffff)
                {
                    res[i+j+k]=0;
                    k++;
                }
                res[i+j+k] +=1;
            }
            res[i+j+1] += buf>>32;
        }
    }
    return res;
}

vector<unsigned long long> karatsuba(const vector<unsigned int>& a, const vector<unsigned int>& b)
{
    size_t len = a.size(); // dlugosc tablic
    vector<unsigned long long> res(2 * len); // tablica wyjsciowa
    if (len <= lenForNaive)   // jesli dlugosc tablicy jest odpowiednio mala tzn. nie jest wieksza niz rozmiar slowa maszynowego to wynik obliczany jest za pomoca zwyklej metody
    {
        return (vector<unsigned long long>) naive(a, b);
    }
    size_t k = len / 2; // miejsce podzialu tablicy

    // podzial na nizsze i wyzsze bity tablic, h - wyzsze, l - nizsze
    vector<unsigned int> al{ a.begin(), a.begin() + k };
    vector<unsigned int> bl{ b.begin(), b.begin() + k };
    vector<unsigned int> ah{ a.begin() + k, a.end() };
    vector<unsigned int> bh{ b.begin() + k, b.end() };
    // tablice przeznaczone na wspolczynniki c2 i c0
    vector<unsigned long long> c2 = karatsuba(ah, bh);
    vector<unsigned long long> c0 = karatsuba(al, bl);

    // sumy:  as = al + ah oraz bs = bl + bh
    vector<unsigned int> as(k);
    vector<unsigned int> bs(k);

    for (int i = 0; i < k; i++)
    {
        as[i] = ah[i] + al[i];
        bs[i] = bh[i] + bl[i];
    }

    // iloczyn sum (al+ah)*(bl+bh)
    vector<unsigned long long> c1 = karatsuba(as, bs);
    // wyrazenie (al+ah)*(bl+bh) - c2 - c0
    for (int i = 0; i < len; i++)
    {
        c1[i] -= c0[i] + c2[i];
    }
    // do wyniku na pozycjach wiekszych niż dlugosc argumentow dodawane sa wartosci c0
    for (int i = len; i < 2 * len; i++)
    {
        res[i] = c2[i - len];
    }
    // do wyniku na pozycjach mniejszych niż dlugosc argumentow dodawane sa wartosci c0
    for (int i = 0; i < len; i++)
    {
        res[i] = c0[i];
    }
    // dodanie c1
    for (int i = k; i < len + k; i++)
    {
        res[i] += c1[i - k];
    }

    return res;
}

vector<unsigned int> stringToArr(string s)
{
	unsigned int multiplier=1;
	vector<unsigned int> ret;
	for(int i=s.size()-1 ,n=0;i>=0;i--)
	{
	    n += charToInt(s[i])*multiplier;
		multiplier*=16;
		if (i % 8 == 0)
		{
			ret.push_back(n);
			n=0;
			multiplier=1;
		}
	}
	return ret;
}

string makeLenghtPowerOf2 (string s)
{
    int pwr = 1;
    while (pwr < s.size())
    {
        pwr*=2;
    }
    for(int i=s.size();i<pwr;i++)
    {
        s.insert(0,1,'0');
    }
    while(s.size()%8!=0)
    {
        s.insert(0,1,'0');
    }
    return s;
}

void setForOutput(vector<unsigned long long>& output)
{
    for (auto i = 0; i < output.size() - 1; ++i)
    {
        output[i + 1] += output[i] / base;
        output[i] %= base;
    }
}
