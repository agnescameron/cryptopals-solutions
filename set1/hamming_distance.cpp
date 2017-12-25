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


void ascii_to_binary(string &asciiString){
	int ascii;
	string tempString;

	for(int i=0; i<asciiString.length(); i++){
		ascii = asciiString[i];
		tempString = tempString + dec_to_bytes(ascii);
	}

	asciiString = tempString;
}


int hamming_dist(string string1, string string2){
	
	int ham=0;

	for (int i=0; i<string1.length(); i++){
		if(string1[i] != string2[i]){
			ham = ham + 1;
		}
	}
	return ham;
}

int main(){
	string string1 = "this is a test";
	string string2 = "wokka wokka!!!";

	ascii_to_binary(string1);
	ascii_to_binary(string2);
	
	int ham = hamming_dist(string1, string2);
	
	cout << "hamming dist is " << ham << endl;

}