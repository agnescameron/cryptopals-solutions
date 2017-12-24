//converts hexadecimal to binary to base 64

#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <algorithm>
#include <math.h>
#include <vector>
#include <ctime>
#include <ctype.h>
#include <sstream>
#include <fstream>
#include <math.h>

using namespace std;

string hexstring = "0123456789abcdef";

//recursive integer powers
int pow_2(int exponent)
{
  if (exponent == 0)
    return 1;

  if (exponent == 1)
    return 2;

  return 2 * pow_2(exponent - 1);
}

int counter(string byteString){
	int count = 0;
		//cout << "byteString is " << byteString << endl;
	for(int i=0; i<4; i++){
		// reverse direction
		int bit = byteString[3-i] - '0';
		count = count + pow_2(i)*bit;
		//cout << "bit is " << bit << ", so adding " << pow_2(i)*bit <<", count is " << count << endl;
	}
		//cout << "counting, count is " << count << endl;
	return count;
}


void hex_to_bytes(string &encodedString){
	//cout << "converting to bytes!" << endl;


	//sixteen distinct symbols give numbers 0-15 (0-f)
	//one hexadecimal digit = 1 nibble (4 bits), e.g. half a byte
    string tempString;

	//loops through encodedString char by char (range-based for loop, c++11)
	for(int i = 0; i < encodedString.size(); ++i) {

		switch (encodedString[i])
				{
					case '0': tempString = tempString+ "0000"; break;
					case '1': tempString = tempString+ "0001"; break;
					case '2': tempString = tempString+ "0010"; break;
					case '3': tempString = tempString+ "0011"; break;
					case '4': tempString = tempString+ "0100"; break;
					case '5': tempString = tempString+ "0101"; break;
					case '6': tempString = tempString+ "0110"; break;
					case '7': tempString = tempString+ "0111"; break;
					case '8': tempString = tempString+ "1000"; break;
					case '9': tempString = tempString+ "1001"; break;
					case 'a': tempString = tempString+ "1010"; break;
					case 'b': tempString = tempString+ "1011"; break;
					case 'c': tempString = tempString+ "1100"; break;
					case 'd': tempString = tempString+ "1101"; break;
					case 'e': tempString = tempString+ "1110"; break;
					case 'f': tempString = tempString+ "1111"; break;
				}

		}
		encodedString = tempString;
}

string xor_hex(string string1, string string2){
	string xorstr;

	for (int i=0; i< string1.size(); i++){
		int st1 = string1[i] - '0';
		int st2 = string2[i] - '0';

		int x = st1^st2;
		xorstr = xorstr + to_string(x);
	}

	return xorstr;
}

void bytes_to_hex(string &encodedString){
	//cout << "converting to base 64!, here encodedString is " << encodedString << endl;

	string tempString;
	for (int i = 0; i < encodedString.size()/4; i++){
		string byteString;
		for (int j=0; j<4; j++){
			byteString = byteString + encodedString[4*i + j];
			}

		//cout << "byteString here is " << byteString << endl;		
		int count = counter(byteString);
		char hexstr = hexstring[count];	

		//cout << "count is  " << count << endl;			
		tempString = tempString + hexstr;
	}
	encodedString = tempString;
}


int main(){

	string string1 = "1c0111001f010100061a024b53535009181c";
	string string2 = "686974207468652062756c6c277320657965";

	hex_to_bytes(string1);
	hex_to_bytes(string2);

 	cout << "strings in bytes are:  " << endl << "string 1 " << string1 << endl << "string 2 " << string2 << endl;

	string encodedString = xor_hex(string1, string2);

	cout << "xored string in b64 is " << encodedString << endl;

	bytes_to_hex(encodedString);

	cout << "final hex string is " << encodedString << endl;
}