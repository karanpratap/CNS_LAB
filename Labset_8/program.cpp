//Author : karanpratap
//Program : RC4

#include<bits/stdc++.h>
#define MAX 256
using namespace std;

void swap(int* a, int* b){
	int temp;
	temp=*a;
	*a=*b;
	*b=temp;
}

void initializationAndPermutation(int S[MAX], int T[MAX], int key[MAX], int keylen){
	int j=0;
	for(int i=0;i<MAX;i++){
		S[i]=i;
		T[i]=key[i%keylen];
	}
	for(int i=0;i<MAX;i++){
		j=(j+S[i]+T[i])%MAX;
		swap(&S[i],&S[j]);
	}
}

void streamGeneration(int S[MAX], int inputLength, int genKeys[MAX]){
	int i=0,j=0,t,k=0;
	for(int i=1;i<=inputLength;i++){
		j=(j+S[i])%MAX;
		swap(&S[i],&S[j]);
		t=(S[i]+S[j])%MAX;
		genKeys[k++]=S[t];
	}
}

void encryption(int plaintext[MAX], int inputLength, int genKeys[MAX]){
	for(int i=0;i<inputLength;i++){
		cout<<plaintext[i]<<" xor "<<genKeys[i]<<" = ";
		plaintext[i]=plaintext[i]^genKeys[i];
		cout<<plaintext[i]<<endl;
	}
}

void decryption(int ciphertext[MAX], int inputLength, int genKeys[MAX]){
	for(int i=0;i<inputLength;i++){
		cout<<ciphertext[i]<<" xor "<<genKeys[i]<<" = ";
		ciphertext[i]=ciphertext[i]^genKeys[i];
		cout<<ciphertext[i]<<endl;
	}	
}

int main(){
	int keylen, key[MAX], genKeys[MAX];
	int S[MAX], T[MAX];
	int text[MAX], inputLength;
	cout<<"Enter the key length:";
	cin>>keylen;
	cout<<"Enter the key with space separated values:";
	for(int i=0;i<keylen;i++)
		cin>>key[i];

	initializationAndPermutation(S,T,key,keylen);
	
	cout<<"Enter the length of plaintext:";
	cin>>inputLength;

	cout<<"Enter the space separated plaintext bytes:";
	for(int i=0;i<inputLength;i++)
		cin>>text[i];
	
	streamGeneration(S,inputLength,genKeys);

	cout<<endl<<"GENERATED KEY BYTES:"<<endl;
	for(int i=0;i<inputLength-1;i++)
		cout<<genKeys[i]<<" -> ";
	cout<<genKeys[inputLength-1]<<endl;	
	cout<<"These bytes are XORed with the plaintext bytes to generate the ciphertext."<<endl<<endl;

	encryption(text,inputLength, genKeys);

	cout<<"Ciphertext for the given plaintext is:";
	for(int i=0;i<inputLength;i++)
		cout<<text[i]<<" ";
	cout<<endl<<endl;

	cout<<"To decrypt, the cipher text bytes are XORed with the key bytes."<<endl;

	decryption(text,inputLength, genKeys);

	cout<<"Plaintext for the given ciphertext is:";
	for(int i=0;i<inputLength;i++)
		cout<<text[i]<<" ";
	cout<<endl;

	return 0;
}
