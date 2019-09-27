//Author: karanpratap
//Program: 48-bit input generation for S-box

#include<bits/stdc++.h>
using namespace std;

//global initializations
//	Expansion Table (E)
int expansionTable[8][6]={{32,1,2,3,4,5},{4,5,6,7,8,9},{8,9,10,11,12,13},{12,13,14,15,16,17},{16,17,18,19,20,21},{20,21,22,23,24,25},{24,25,26,27,28,29},{28,29,30,31,32,1}};

string functionE(string input){
	string res;
	for(int i=0;i<8;i++)
		for(int j=0;j<6;j++)
			res+=input[expansionTable[i][j]-1];
	return res;
}

//Function to xor 2 arguements and store result in arg1
string xorOperation(string arg1, string arg2){
	string res="";
	for(int i=0;i<arg1.length();i++)
		res+=(arg1[i]==arg2[i])?"0":"1";
	return res;
}

string hexToBinary64(string input){
	stringstream s;
	s<<hex<<input;
	unsigned long n;
	s>>n;
	bitset<64> b(n);
	return b.to_string();
}

string binaryToHex(string input){
	char hexChars[16]={'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
	string res="0x";
	for(int i=3;i<=input.length();i+=4){
		int temp=0;
		for(int j=0;j<4;j++)
			temp+=(input[i-j]-48)*pow(2,j);
		res+=hexChars[temp];
	}
	return res;
}

int main(){
	int roundNum;
	char ch; 
	string input, intermediate, subkey;
	cout<<"Enter the round number:";
	cin>>roundNum;
	ifstream keysFile;
	keysFile.open("keys.txt",ios::in);
	keysFile.seekg((roundNum==1)?(roundNum-1)*48:(roundNum-1)*48+1,keysFile.beg);
	cout<<"Round No:"<<roundNum<<endl;
	for(int i=0;i<48;i++){
		keysFile>>ch;
		subkey+=ch;
	}
	keysFile.close();
	cout<<"Subkey for Round Number "<<roundNum<<":"<<subkey<<endl;
	cout<<"Enter the 64 bit Input in hexadecimal:";
	cin>>input;
	input=hexToBinary64(input);
	
	intermediate=functionE(input.substr(32,32)); //sending right 32 bits to the expansion function
	cout<<"The calculated Expansion table output is:"<<intermediate<<endl;
	
	//Performing XOR with the round's subkey and displaying the result
	cout<<"Calculated input for the S-boxes for round : "<<xorOperation(intermediate,subkey)<<endl;
	cout<<"S-box input in hexadecimal:"<<binaryToHex(xorOperation(intermediate,subkey))<<endl;
	return 0;
}
