//Author: karanpratap
//Program: Labset 4 - Matrix transposition cipher

#include<bits/stdc++.h>
#define MAX 10

using namespace std;

int indexOf(int arr[],int element,int len){
    for(int i=0;i<len;i++)
        if(arr[i]==element)
            return i;
    return -1;
}

void cipher(char msgMatrix[][MAX], int rows, int k, int key[]){
	//encryption
	int p=0;
	char cipherText[30], decrypted[MAX][MAX];
	for(int i=1;i<=k;i++){
		for(int j=0;j<rows;j++)
			cipherText[p++]=msgMatrix[j][indexOf(key,i,k)];
	}
	cipherText[p]='\0';
	cout<<cipherText<<endl;
	
	p=0;
	//decryption
	for(int i=1;i<=k;i++)
		for(int j=0;j<rows;j++)
			decrypted[j][indexOf(key,i,k)]=cipherText[p++];

	for(int i=0;i<rows;i++)
		for(int j=0;j<k;j++)
			cout<<decrypted[i][j];
}

int main(){
	char msg[30], msgMatrix[MAX][MAX];
	int key[MAX], pointer=0, k;
	cout<<"Enter the message in plaintext:";
	cin>>msg;
	cout<<"Enter the length of key:";
	cin>>k;
	int noOfRows=((strlen(msg)%k)==0)?strlen(msg)/k:strlen(msg)/k+1;
	cout<<"Enter the key:";
	
	for(int i=0;i<k;i++)
		cin>>key[i];
	
	cout<<"Matrix generated from the plaintext is:"<<endl<<endl;
	for(int i=0;i<k;i++)
		cout<<key[i]<<" ";
	cout<<endl<<"----------------------------------------"<<endl;
	for(int i=0;i<noOfRows;i++){
		for(int j=0;j<k;j++){
			msgMatrix[i][j]=(msg[pointer]!='\0')?msg[pointer++]:'x';
			cout<<msgMatrix[i][j]<<" ";
		}
		cout<<endl;
	}

	cipher(msgMatrix,noOfRows,k,key);
	cout<<endl;
	return 0;
}
