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
vector<unsigned int> naiveMul(const vector<unsigned int>& a, const vector<unsigned int>& b);
vector<unsigned int> karMul(const vector<unsigned int>& a, const vector<unsigned int>& b);
vector<unsigned int> stringToArr(string s);
string makeLenghtPowerOf2 (string s);

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
    vector<unsigned int> result;

    cout<<endl<<endl<<endl<<endl;
    for (int i=0; i<valA.size(); i++)
	{
		//cout<<hex<<setfill('0')<<i<<"mmmmmmmmmmm: "<<valA[i] <<endl;
	}
    //cout<<valA.size();

    //cout<<endl<<endl;

    //cout<<endl<<endl;
	chrono::high_resolution_clock::time_point t1;
	chrono::high_resolution_clock::time_point t2;




	t1 = chrono::high_resolution_clock::now();
	result = karMul(valA, valB);
	t2 = chrono::high_resolution_clock::now();

	vector<unsigned int> tra = naiveMul(valA,valB);



	for (int i=0; i<result.size(); i++)
	{
		cout<<hex<<setfill('0')<<setw(8)<<result[i] << " ";
	}

	cout<<endl;

	for (int i=0; i<tra.size(); i++)
	{
		cout<<hex<<setfill('0')<<setw(8)<<tra[i] << " ";
	}

/*	int r = *(result + sizeA + sizeB -1);
	if (r==0) sizeA--;
	//printf("%x ", *(result + sizeA + sizeB -1 ));
	cout<<hex<<*(result + sizeA + sizeB -1 )<<" ";
	for(int i=sizeA + sizeB -2;i>=0 ;i--)
	{
	//	printf("%08x ", *(result + i));
		cout<<hex<<setfill('0')<<setw(8)<<*(result + i)<<" ";
	}*/

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

vector<unsigned int> naiveMul(const vector<unsigned int>& a, const vector<unsigned int>& b)
{
    size_t length = a.size(); // rozmiar tablic
    vector<unsigned int> res(2 * length); // tablica wyjsciowa


    unsigned long long buf=0;


    for (int i=0; i<a.size(); i++)
	{
		//cout<<hex<<setfill('0')<<i<<" a: "<<a[i] <<endl;
	}

    for (int i=0; i<b.size(); i++)
	{
		//cout<<hex<<setfill('0')<<i<<" b: "<<b[i] <<endl;
	}

    /*for (unsigned int i=0; i<a.size(); i++){
        for(unsigned int j=0; j<b.size(); j++){
            buf = (unsigned long long)(b[i]) * (unsigned long long)(a[j]);
            cout<<hex<<buf<<" "<<a[i]<<" "<<b[i]<<endl<<endl;
            if(0xffffffff-res[i+j] < (buf<<32)>>32) //OVflow check
                res[i+j+1] +=1;
            res[i+j] += buf;
            if(0xffffffff-res[i+j+1] < buf>>32) //OVflow check
                res[i+j+2] += 1;
            res[i+j+1] += buf>>32;
        }
    }*/
    for (int i = 0; i < length; ++i)
    {
        for (int j = 0; j < length; ++j)
        {
            buf = (unsigned long long)a[i] * b[j];
            if(0xffffffff-res[i+j] < (buf<<32)>>32)
            {
                res[i+j+1] +=1;
                for(int k=1;res[i+j+k]==0;k++)
                {
                    res[i+j+k+1]+=1;
                }
                //cout<<dec<<"p1------------------------: "<<i<<" "<<j<<endl;
            }
            res[i+j] += buf;
            if(0xffffffff-res[i+j+1] < buf>>32)
            {
                //cout<<"p2------------------------"<<endl;
                res[i+j+2] += 1;
                for(int k=2;res[i+j+k]==0;k++)
                {
                    res[i+j+k+1]+=1;
                }
            }
            res[i+j+1] += buf>>32;
            //cout<<dec<<"a:  "<<i<<" b: "<<j <<endl;
            //cout<<hex<<"buf: "<<buf<<endl;
            for (int k=0; k<res.size(); k++)
            {
                //cout<<hex<<setfill('0')<<setw(8)<<res[k]<<" ";
            }
            //cout<<endl<<endl;
        }
    }

    return res;
}

vector<unsigned int> karMul(const vector<unsigned int>& a, const vector<unsigned int>& b)
{
    size_t len = a.size();  // dlugosc tablic
    vector<unsigned int> res(2 * len);  // tablica wyjsciowa
    if (len <= 4)   // jesli dlugosc tablicy jest odpowiednio mala tzn. nie jest wieksza niz rozmiar slowa maszynowego
                    // to wynik obliczany jest za pomoc¹ zwyklej metody
    {
        return naiveMul(a, b);
    }
    size_t k = len / 2; // miejsce podzialu tablicy
    // podzial na nizsze i wyzsze bity tablic, h - wyzsze, l - nizsze
    vector<unsigned int> al{ a.begin(), a.begin() + k };
    vector<unsigned int> ah{ a.begin() + k, a.end() };
    vector<unsigned int> bl{ b.begin(), b.begin() + k };
    vector<unsigned int> bh{ b.begin() + k, b.end() };


    cout<<endl<<"al:  "<<endl;
    for (int i=0; i<al.size(); i++)
	{
		cout<<hex<<setfill('0')<<setw(8)<<al[i] << " ";
	}

	cout<<endl<<"ah:  "<<endl;
    for (int i=0; i<ah.size(); i++)
	{
		cout<<hex<<setfill('0')<<setw(8)<<ah[i] << " ";
	}


    vector<unsigned int> c2 = karMul(ah, bh);
    vector<unsigned int> c0 = karMul(al, bl);

    // suma a1 + a0 i b1 + b0
    vector<unsigned int> as(k);
    vector<unsigned int> bs(k);

    int middleflag=1;

    for (int i = 0; i < k; ++i)
    {
        if(ah[i] >= al[i]) as[i] = ah[i] - al[i];
        else
        {
            middleflag=-1;
            as[i] = al[i] - ah[i];
        }
        if(bh[i] >= bl[i]) bs[i] = bh[i] - bl[i];
        else
        {
            middleflag*=-1;
            bs[i] = bl[i] - bh[i];
        }
    }

    cout<<endl<<"as:  "<<endl;
    for (int i=0; i<as.size(); i++)
	{
		//<<hex<<setfill('0')<<setw(8)<<as[i] << " ";
	}
    cout<<endl<<"bs:  "<<endl;
    for (int i=0; i<bs.size(); i++)
	{
		//cout<<hex<<setfill('0')<<setw(8)<<bs[i] << " ";
	}


    // obliczenie (a1+a0)*(b1+b0)
    //cout<<endl<<"eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee"<<endl;
    vector<unsigned int> c1 = karMul(as, bs); // (a1+a0)*(b1+b0)
    // (a1+a0)*(b1+b0) - c2 - c0
    /*for (int i = 0; i < len; ++i)
    {
        unsigned long long sum = (unsigned long long) c0[i] + c2[i];
        unsigned long long cone = (unsigned long long) c1[i];
        if(sum > cone)
        {
            cone +=0x100000000;
            //if(c1[i+1]>0) c1[i+1]-=1;
        }
        cone -= sum;
        c1[i] = cone;
    }*/
    // do pozycji wynikow mniejszych niz poczatkowa dlugosc dodawane jest c0
    for (int i = 0; i < len; ++i)
    {
        res[i] = c0[i];
    }
    // dodawane jest c2 na odpowiednich pozycjach
    for (int i = len; i < 2 * len; ++i)
    {
        res[i] = c2[i - len];
    }
    // dodanie c1
    for (int i = k; i < len + k; ++i)
    {
        unsigned long long buf = (unsigned long long) res[i] + c0[i - k];
        buf += (unsigned  long long) c2[i - k];
        if(middleflag==1) buf -= (unsigned  long long) c2[i - k];
        else buf += (unsigned  long long) c2[i - k];
        res[i] = buf;
        if (buf>0xffffffff) res[i+1]++;
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
    //cout<<ret.size()<<endl;
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


