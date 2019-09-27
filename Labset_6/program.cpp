//Author: karanpratap
//Program: 48-bit input generation for S-box

#include<bits/stdc++.h>
#include "../headers/conversions.h"

using namespace std;

//global initializations
//	Expansion Table (E)
int expansionTable[8][6]={{32,1,2,3,4,5},{4,5,6,7,8,9},{8,9,10,11,12,13},{12,13,14,15,16,17},{16,17,18,19,20,21},{20,21,22,23,24,25},{24,25,26,27,28,29},{28,29,30,31,32,1}};

void functionE(char R[33], char intermediate[49]){
	for(int i=0;i<8;i++)
		for(int j=0;j<6;j++)
			intermediate[i*6+j]=R[expansionTable[i][j]-1];
	intermediate[48]='\0';
}

//Function to xor 2 arguements and store result in arg1
void xor48(char arg1[49], char arg2[49]){
	for(int i=0;i<48;i++)
		arg1[i]=(arg1[i]==arg2[i])?48:49;
	//arg1[48]='\0';
}

int main(){
	int roundNum, roundNumBup, pointer=0;
	char ch, inputHex[17], inputBin[65], R[33], intermediate[49], subkey[49];
	cout<<"Enter the round number:";
	cin>>roundNum;
	ifstream keysFile;
	keysFile.open("keys.txt",ios::in);
	keysFile.seekg((roundNum==1)?(roundNum-1)*48:(roundNum-1)*48+1,keysFile.beg);
	cout<<"Round No:"<<roundNum<<endl;
	for(int i=0;i<48;i++){
		keysFile>>ch;
		subkey[pointer++]=ch;
	}
	subkey[48]='\0';
	keysFile.close();
	cout<<"Subkey for Round Number "<<roundNum<<":"<<subkey<<endl;
	cout<<"Enter the 64 bit Input in hexadecimal:";
	cin>>inputHex;
	hexToBinary(inputHex, inputBin);
	//extracting right hand side 32 bits of input
	for(int i=0;i<32;i++)
		R[i]=inputBin[i+32];
	R[32]='\0';
	functionE(R, intermediate);
	cout<<"The calculated Expansion table output is:"<<intermediate<<endl;
	xor48(intermediate,subkey);
	cout<<"Calculated input for the S-boxes for round : "<<intermediate<<endl;
	return 0;
}
