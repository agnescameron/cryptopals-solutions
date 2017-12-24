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

string scorecard = "etaoinshrdlu";
int scores[255];
string sents[255];
int scorenum = 0;

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

	for(int i=0; i<8; i++){
		// reverse direction
		int bit = byteString[7-i] - '0';
		count = count + pow_2(i)*bit;
		//cout << "bit is " << bit << ", so adding " << pow_2(i)*bit <<", count is " << count << endl;
	}
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


void bytes_to_ascii(string &encodedString){
	//cout << "converting to base 64!, here encodedString is " << encodedString << endl;

	string tempString;
	for (int i = 0; i < encodedString.size()/8; i++){
		string byteString;
		for (int j=0; j<8; j++){
			byteString = byteString + encodedString[8*i + j];
			}

		//cout << "byteString here is " << byteString << endl;		
		int count = counter(byteString);
		char ascii = count;	

		//cout << "count is  " << count << endl;			
		tempString = tempString + ascii;
	}
	encodedString = tempString;
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

void calculate_score(string xorstr){
	int score = 0;

	for(int i=0; i<xorstr.size(); i++){
		for(int j=0; j<scorecard.size(); j++){
			if(xorstr[i] == scorecard[j]){
			score = score + (12-j);
			}
		}
	}

	//cout << xorstr << "  scores   " << score << endl;

	scores[scorenum] = score;
	scorenum++;
}

void xor_test(string encodedString){
	
	for (int i=0; i< 255; i++){
	string testByte = dec_to_bytes(i);
	
	string xorstr;

	for (int j=0; j< encodedString.size()/8; j++){
			for (int k=0; k<8; k++){
				int x = testByte[k]^encodedString[j*8 + k];
				xorstr = xorstr + to_string(x);
			}
		}
		bytes_to_ascii(xorstr);
		sents[scorenum] = xorstr;
		calculate_score(xorstr);
	}
}

void findmax(){
	const int N = sizeof(scores)/sizeof(int);
	cout << "index of max element is " << distance(scores, max_element(scores, scores + N)) << endl;

	cout << "best sentence is \'" << sents[88] << "\', which scores " << scores[88] << endl;
}


int main(){

	string encodedString = "1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736";
	//hex_to_ascii(encodedString);
	//cout << "in ascii, is " << encodedString << endl;


	hex_to_bytes(encodedString);
	xor_test(encodedString);

	findmax();


}