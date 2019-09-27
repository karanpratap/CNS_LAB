//Program to convert Hexadecimal to binary and vice versa.

#include<bits/stdc++.h>
using namespace std;

string hexToBinary(string input){
	stringstream s;
	s<<hex<<input;
	unsigned n;
	s>>n;
	bitset<16> b(n);
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
	string input;
	int bits;
	cout<<"Enter hexadecimal input:";
	cin>>input;
	cout<<"Binary of the given hexadecimal is:"<<hexToBinary(input)<<endl;
	cout<<"Enter binary input:";
	cin>>input;
	cout<<"Binary to Hex Test:"<<binaryToHex(input)<<endl;
	return 0;
}
