//Author : karanpratap
//Program : Labset 5 - DES Algorithm Key Generation

#include <bits/stdc++.h>
#include "./conversions.h"
using namespace std;

//declaring all the tables
int PC1[8][7]={{57,49,41,33,25,17,9},{1,58,50,42,34,26,18},{10,2,59,51,43,35,27},{19,11,3,60,52,44,36},{63,55,47,39,31,23,15},{7,62,54,46,38,30,22},{14,6,61,53,45,37,29},{21,13,5,28,20,12,4}};
int PC2[6][8]={{14,17,11,24,1,5,3,28},{15,6,21,10,23,19,12,4},{26,8,16,7,27,20,13,2},{41,52,31,37,47,55,30,40},{51,45,33,48,44,49,39,56},{34,53,46,42,50,36,29,32}};
int shift[16]={1,1,2,2,2,2,2,2,1,2,2,2,2,2,2,1};

void permutedChoiceOne(char binaryInput[65], char resPC1[8][7]){
	int pointer=0;
	for(int i=0;i<8;i++)
		for(int j=0;j<7;j++)
			resPC1[i][j]=binaryInput[PC1[i][j]-1];
}

void leftCircularShift(char resPC1[8][7], int number){
	for(int k=0;k<number;k++){
		char tempC=resPC1[0][0];
		char tempD=resPC1[4][0];
		for(int i=0;i<4;i++){
			for(int j=0;j<6;j++){
				resPC1[i][j]=resPC1[i][j+1];
				resPC1[i+4][j]=resPC1[i+4][j+1];
			}
			resPC1[i][6]=(i<3)?resPC1[i+1][0]:tempC;
			resPC1[i+4][6]=(i<3)?resPC1[i+5][0]:tempD;
		}
	}
}

void permutedChoiceTwo(char resPC1[8][7], char resPC2[6][8]){
	for(int i=0;i<6;i++)
		for(int j=0;j<8;j++){
			resPC2[i][j]=(PC2[i][j]%7==0)?resPC1[PC2[i][j]/7-1][6]:resPC1[PC2[i][j]/7][PC2[i][j]%7-1];
		}
}

int main(){
	ofstream keyOut;
	keyOut.open("keys.txt");
	char key[17], binaryKey[65], resPC1[8][7], resPC2[6][8];
	cout<<"Input the 64 bit key in hexadecimal:";
	cin>>key;
	hexToBinary(key,binaryKey);
	cout<<"Hexadecimal key converted to binary: "<<binaryKey<<endl;
	cout<<"Result after applying permuted choice 1:"<<endl;
	permutedChoiceOne(binaryKey,resPC1);
	for(int i=0;i<8;i++){
		for(int j=0;j<7;j++)
			cout<<resPC1[i][j];
		cout<<endl;
	}
	cout<<endl;
	for(int i=0;i<16;i++){
		leftCircularShift(resPC1,shift[i]);
		permutedChoiceTwo(resPC1,resPC2);
		cout<<"key "<<i+1<<":";
		for(int i=0;i<6;i++)
			for(int j=0;j<8;j++){
				cout<<resPC2[i][j];
				keyOut<<resPC2[i][j];
			}
		cout<<endl;
		keyOut<<endl;
	}
	keyOut.close();
	return 0;
}
