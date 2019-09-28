//Author : karanpratap
//Program : Labset 5 - DES Algorithm Key Generation [Exam Version]

#include <bits/stdc++.h>
using namespace std;

//declaring all the tables
int PC1[8][7]={{57,49,41,33,25,17,9},{1,58,50,42,34,26,18},{10,2,59,51,43,35,27},{19,11,3,60,52,44,36},{63,55,47,39,31,23,15},{7,62,54,46,38,30,22},{14,6,61,53,45,37,29},{21,13,5,28,20,12,4}};
int PC2[6][8]={{14,17,11,24,1,5,3,28},{15,6,21,10,23,19,12,4},{26,8,16,7,27,20,13,2},{41,52,31,37,47,55,30,40},{51,45,33,48,44,49,39,56},{34,53,46,42,50,36,29,32}};
int shift[16]={1,1,2,2,2,2,2,2,1,2,2,2,2,2,2,1};

string hexToBinary64(string input){
	stringstream s;
	s<<hex<<input;
	unsigned long n;
	s>>n;
	bitset<64> b(n);
	return b.to_string();
}

string permutedChoiceOne(string input){
	string res="";
	for(int i=0;i<8;i++)
		for(int j=0;j<7;j++)
			res+=input[PC1[i][j]-1];
	return res;
}

string leftCircularShift(string input, int number){
	return input.substr(number,input.length()-number)+input.substr(0,number);
}

string permutedChoiceTwo(string input){
	string res="";
	for(int i=0;i<6;i++)
		for(int j=0;j<8;j++)
			res+=input[PC2[i][j]-1];
	return res;
}

int main(){
	ofstream keyOut;
	keyOut.open("keys.txt");
	string key;
	cout<<"Input the 64 bit key in hexadecimal:";
	cin>>key;
	key=hexToBinary64(key);
	cout<<"Hexadecimal key converted to binary: "<<key<<endl;
	key=permutedChoiceOne(key);
	cout<<"Result after applying permuted choice 1:"<<key<<endl;
	for(int i=0;i<16;i++){
		key=leftCircularShift(key.substr(0,28),shift[i])+leftCircularShift(key.substr(28,28),shift[i]);
		cout<<"key "<<i+1<<":"<<permutedChoiceTwo(key)<<endl;
		keyOut<<permutedChoiceTwo(key)<<endl;
	}
	keyOut.close();
	return 0;
}
