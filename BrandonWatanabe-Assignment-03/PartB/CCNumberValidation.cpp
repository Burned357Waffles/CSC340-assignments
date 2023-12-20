#include <iostream>
#include <iomanip> 
#include <string>
#include <vector>

using namespace std;

bool isvalidcc(const string&);
int doubleDigits(const string&);
int sumDigits(const string&);

int main()
{
	//
	// PLEASE DO NOT CHANGE function main
	//
	vector<string> cardnumbers = {
		 "371449635398431", "4444444444444448", "4444424444444440", "4110144110144115",
		"4114360123456785", "4061724061724061", "5500005555555559", "5115915115915118",
		"5555555555555557", "6011016011016011", "372449635398431", "4444544444444448",
		"4444434444444440", "4110145110144115", "4124360123456785", "4062724061724061",
		"5501005555555559", "5125915115915118", "5556555555555557", "6011116011016011",
		 "372449635397431", "4444544444444448", "4444434444544440", "4110145110184115",
		"4124360123457785", "4062724061724061", "5541005555555559", "5125115115915118",
		"5556551555555557", "6011316011016011"
	};

	int i;
	vector<string>::iterator itr;

	for (i = 1, itr = cardnumbers.begin(); itr != cardnumbers.end(); ++itr, i++) {
		cout << setw(2)  << i << " " 
			 << setw(17) << *itr 
			 << ((isvalidcc(*itr)) ? " is valid" : " is not valid") << endl;
	}

	return 0; 
}

int doubleDigits(const string& number)
{
	int total = 0;
	for (int i = number.size() - 2; i >= 0; i -=2)
	{
		int tempInt = number[i] - '0';
		tempInt = 2*tempInt;
		if (tempInt >= 10)
		{
			int first = tempInt / 10 % 10;
			int second = tempInt % 10;
			total += first + second;
		}
		else total += tempInt;
	}
	return total;
}
int sumDigits(const string& number)
{
	int total = 0;
	for (int i = number.size() - 1; i >= 0; i -= 2)
	{
		int tempInt = number[i] - '0';
		total += tempInt;
	}
	return total;
}

bool isvalidcc(const string& number)
{
	int size = number.size();
	if (number.size() < 13 && number.size() > 16)
	{
		return false;
	}

	int element = number[0] - '0';
	int element2 = number[1] - '0';
	if (element != 4 && element != 5 && element != 6)
	{
		if (element == 3)
		{
			if (element2 != 7)
			{
				return false;
			}
		}
		else return false;
	}
		
	int step1 = doubleDigits(number);
	int step2 = sumDigits(number);
	return (step1 + step2) % 10 == 0;
}