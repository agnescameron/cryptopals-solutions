


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
#include <streambuf>

using namespace std;
string hexstring = "0123456789abcdef";

vector<vector<int>> scoreVector;


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

void splitblocks(int keySize, string buffstring, vector<vector <string> > &blockVector){
	ascii_to_binary(buffstring);

	//for each key-size block of bytes
	for(int i=0; i<buffstring.size()/(keySize*8); i++){
		//make byte blocks from each keysize block
		vector<string> tempVector;
		for(int j=0; j<keySize; j++){
			//bytes
			string byteString;
			for(int k=0; k<8; k++)
				byteString = byteString + buffstring[i*8*keySize + j*8 + k];
			//write to temporary vector
			tempVector.push_back(byteString);
		} 
		blockVector.push_back(tempVector);
	}

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

string xor_bytes(string asc, string byte){
	string xorstr;
	for (int i=0; i<8; i++){
		int x = byte[i]^asc[i];
		xorstr = xorstr + to_string(x);
		}
		return xorstr;
}

void testblocks(int keysize, vector<vector <string> > blockVector){

for(int asc=0; asc<255; asc++){
	string ascii = dec_to_bytes(asc);

//select every keysize block, starting with offset, and test each w/ every letter of 255
	for(int j=0; j<keysize; j++){
		string xorstr;
		for(int i=0; i<blockVector.size(); i++){
			xorstr = xorstr + xor_bytes(ascii, blockVector[i][j]);
		}
		bytes_to_ascii(xorstr);
		cout << xorstr << endl;
	}
}


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

void sortScores(vector<float> &keySizeScores){
	sort(keySizeScores.begin(), keySizeScores.end());
	for (int i=0; i<10; i++){
		cout << "keysize score " << keySizeScores[i] << endl;
	}
}

int findmin(vector<float> &scores){
	vector<float>::iterator minElement;
	minElement = min_element(scores.begin(), scores.end());
	int minFind = distance(scores.begin(), minElement);

	cout << "index of min element is " << minFind << endl;
	cout << "min score " << *minElement << endl;

	return minFind + 2;

}

void testKeySize(vector<float> &keySizeScores){
	vector<string> testStrings;
	ifstream encryptedFile("encrypted.txt");
	encryptedFile.seekg(0, std::ios::end);
	int length = encryptedFile.tellg(); 
	encryptedFile.seekg(0, std::ios::beg);
	char buffer [length];
	encryptedFile.read(buffer, length);
	encryptedFile.close();

	for(int i=2; i<40; i++){

		string string1;
		string string2;

		vector<string> testStrings;

		//select two keystrings
		for(int j=0; j<2; j++){
			//of length i
			string tempString;
			for(int k=0; k<i; k++){
				tempString = tempString + buffer[j*i + k];
			}
			//cout << "tempString is " << tempString << endl;
			testStrings.push_back(tempString);
		}
		string1	= testStrings[0];
		string2	= testStrings[1];

		ascii_to_binary(string1);
		ascii_to_binary(string2);
		
		int ham = hamming_dist(string1, string2);
		keySizeScores.push_back(ham/(float)i);
	} 

	string buffstring(buffer, length);
	//sortScores(keySizeScores);
	int keySize = findmin(keySizeScores);
	vector<vector <string> >blockVector;

	splitblocks(keySize, buffstring, blockVector);
	testblocks(keySize, blockVector);

}

int main(){
	vector<float> keySizeScores;

	testKeySize(keySizeScores);
	//cout << "hamming dist is " << ham << endl;

}