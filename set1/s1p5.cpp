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
#include <stddef.h>

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

	for(int i=0; i<4; i++){
		// reverse direction
		int bit = byteString[3-i] - '0';
		count = count + pow_2(i)*bit;
		cout << "bit is " << bit << ", so adding " << pow_2(i)*bit <<", count is " << count << endl;
	}
	return count;
}


string dec_to_bytes(int n){
	{
    string r;
    while(n!=0) {r=(n%2==0 ?"0":"1")+r; n/=2;}


    int sz =  r.size();

    if(sz < 8){
    	for(int i=0; i<(8-sz); i++){
    		r = '0' + r;
    	}
	}

    return r;
	}
}


void xor_strings(string &encodedString, string keyString){
	string xorstr;

	for (int i=0; i< encodedString.size()/24; i++){
		for (int j=0; j< 24; j++){
				int x = keyString[j]^encodedString[i*24 + j];
				xorstr = xorstr + to_string(x);
		}
	}
	encodedString = xorstr;
}


void ascii_to_binary(string &asciiString){
	int ascii;
	string tempString;

	for(int i=0; i<asciiString.length(); i++){
		ascii = asciiString[i];
		tempString = tempString + dec_to_bytes(ascii);
	}

	asciiString = tempString;
}


void bytes_to_hex(string &encodedString){
	//cout << "converting to base 64!, here encodedString is " << encodedString << endl;

	string tempString;
	for (int i = 0; i < encodedString.size()/4; i++){
		string byteString;
		for (int j=0; j<4; j++){
			byteString = byteString + encodedString[4*i + j];
			}

			cout << "byteString here is " << byteString << endl;		
			int count = counter(byteString);
			char hexstr = hexstring[count];	

		//cout << "count is  " << count << endl;			
		tempString = tempString + hexstr;
	}
	encodedString = tempString;
}


int main(){
	string encodedString = "Burning 'em, if you ain't quick and nimble I go crazy when I hear a cymbal";
	string keyString = "ICE";

	ascii_to_binary(encodedString);
	cout <<  "binary encoded message is " << encodedString << endl;
	ascii_to_binary(keyString);
	cout <<  "binary encoded key is " << encodedString << endl;

	xor_strings(encodedString, keyString);
	cout <<  "xored strings are " << encodedString << endl;

	bytes_to_hex(encodedString);

cout << "encoded hex string is " << encodedString << endl;

}