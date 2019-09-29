//Author: karanpratap
//Program: Playfair Cipher [Exam Version]

#include<bits/stdc++.h>
#define MAX 50
using namespace std;

const char filler='x';
char overrideChar;

bool contains(char arr[],char ch){
	for(int i=0;i<strlen(arr);i++)
		if(arr[i]==ch)
			return true;
	return false;
}

//A function to return the row of a character (0-indexed) in a character matrix
int rowOf(char arr[5][5], char ch){
	for(int i=0;i<5;i++){
		for(int j=0;j<5;j++){
			if(arr[i][j]==ch)
				return i;
		}
	}
	return -1;
}

//A function to return the column of a character (0-indexed) in a character matrix
int colOf(char arr[5][5], char ch){
	for(int i=0;i<5;i++){
		for(int j=0;j<5;j++){
			if(arr[i][j]==ch)
				return j;
		}
	}
	return -1;
}

//Generate a 5X5 matrix given a key and reference to the matrix
void generateMatrix(string key, char matrix[5][5]){
	char distinct[26];
	bool visited[26]={false};
	int pointer=0, row=0, col=0;
	int distinctCount=0;
	for(int j=0;j<key.length();j++){
		if(!contains(distinct,(key[j]=='i' || key[j]=='j')?overrideChar:key[j])){
			distinct[distinctCount++]=(key[j]=='i' || key[j]=='j')?overrideChar:key[j];
		}
	}
	
	cout<<"Echoing back the distinct characters in the key for test purposes: ["<<distinctCount<<"] : ";
	for(int j=0;j<distinctCount;j++)
		cout<<distinct[j]<<" ";
	cout<<endl;

	//Inserting the distinct chars in the matrix
	for(int j=0;j<distinctCount;j++){
		matrix[row][col]=distinct[j];
		visited[distinct[j]-97]=true;
		if(matrix[row][col]==overrideChar)
			visited[8]=visited[9]=true;
		row=(col<4)?row:((row+1)%5);
		col=(col+1)%5;
	}
	
	//Inserting the leftover characters in the matrix
	while(pointer<26){
		if(!visited[pointer]){
			matrix[row][col]=(pointer==8 || pointer==9)?overrideChar:pointer+97;
			visited[pointer]=true;
			if(pointer==8 || pointer==9)
				visited[8]=visited[9]=true;
			row=(col<4)?row:((row+1)%5);
			col=(col+1)%5;
		}
		pointer++;
	}
}

//Structuring the message - Generating pairs and adding filler characters
string structureMessage(string msg){
	string structuredMsg="";
	for(int i=0;i<msg.length();){
		if((i+1)!=msg.length())
			if(msg[i]==msg[i+1]){
				structuredMsg+=(msg[i]=='i' || msg[i]=='j')?overrideChar:msg[i];
				structuredMsg+=filler;
				i++;
			}
			else{
				structuredMsg+=(msg[i]=='i' || msg[i]=='j')?overrideChar:msg[i];
				structuredMsg+=(msg[i+1]=='i' || msg[i+1]=='j')?overrideChar:msg[i+1];
				i+=2;
			}
		else{
			structuredMsg+=(msg[i]=='i' || msg[i]=='j')?overrideChar:msg[i];
			structuredMsg+=filler;
			i++;
		}
	}
	return structuredMsg;
}

string encrypt(string msg, char matrix[5][5]){
	string ciphertext="";
	for(int j=0;j<msg.length();j+=2){	
		if(rowOf(matrix,msg[j])==rowOf(matrix,msg[j+1])){
			ciphertext+=matrix[rowOf(matrix,msg[j])][(colOf(matrix,msg[j])+1)%5];
			ciphertext+=matrix[rowOf(matrix,msg[j+1])][(colOf(matrix,msg[j+1])+1)%5];
		}
		else if(colOf(matrix,msg[j])==colOf(matrix,msg[j+1])){
			ciphertext+=matrix[(rowOf(matrix,msg[j])+1)%5][colOf(matrix,msg[j])];
			ciphertext+=matrix[(rowOf(matrix,msg[j+1])+1)%5][colOf(matrix,msg[j])];
		}
		else{
			ciphertext+=matrix[rowOf(matrix,msg[j])][colOf(matrix,msg[j+1])];
			ciphertext+=matrix[rowOf(matrix,msg[j+1])][colOf(matrix,msg[j])];
		}
	}
	return ciphertext;
}

string decrypt(string ciphertext, char matrix[5][5]){
	string decryptedText="";
	for(int j=0;j<ciphertext.length();j+=2){
		if(rowOf(matrix,ciphertext[j])==rowOf(matrix,ciphertext[j+1])){
			decryptedText+=matrix[rowOf(matrix,ciphertext[j])][(colOf(matrix,ciphertext[j])==0)?4:(colOf(matrix,ciphertext[j])-1)%5];
			decryptedText+=matrix[rowOf(matrix,ciphertext[j+1])][(colOf(matrix,ciphertext[j+1])==0)?4:(colOf(matrix,ciphertext[j+1])-1)%5];
		}
		else if(colOf(matrix,ciphertext[j])==colOf(matrix,ciphertext[j+1])){
			decryptedText+=matrix[(rowOf(matrix,ciphertext[j])==0)?4:(rowOf(matrix,ciphertext[j])-1)%5][colOf(matrix,ciphertext[j])];
			decryptedText+=matrix[(rowOf(matrix,ciphertext[j+1])==0)?4:(rowOf(matrix,ciphertext[j+1])-1)%5][colOf(matrix,ciphertext[j])];
		}
		else{
			decryptedText+=matrix[rowOf(matrix,ciphertext[j])][colOf(matrix,ciphertext[j+1])];
			decryptedText+=matrix[rowOf(matrix,ciphertext[j+1])][colOf(matrix,ciphertext[j])];
		}
	}
	return decryptedText;
}

int main(){
	string msg, structuredMsg;
	int structuredMsgLength=0;

	cout<<"Enter the message in plaintext:";
	cin>>msg;
	cout<<"Message Recieved:"<<msg<<endl;
	
	//declerations, initializations depending on the number of keys
	string key, ciphertext, decryptedText;
	char matrix[5][5], ch;
	
	do{
		cout<<"Enter the character to override the other in the matrices (i/j):";
		cin>>overrideChar;
	}while(overrideChar!='i' &&  overrideChar!='j');
	
	msg=structureMessage(msg);
	
	//Loop until user wants to enter keys
	do{
		//Taking input key
		cout<<"Enter the key:";
		cin>>key;
		
		//Generating the 5x5 matrix
		//Generating distinct characters
		generateMatrix(key,matrix);

		cout<<"Echoing back the matrix for testing purposes:"<<endl;
		for(int j=0;j<5;j++){
			for(int k=0;k<5;k++){
				cout<<matrix[j][k]<<" ";
			}
			cout<<endl;
		}

		cout<<"The message after structuring is: "<<msg<<endl;

		//Encrypting the message corresponding to the key
		ciphertext=encrypt(msg,matrix);
		cout<<"Ciphertext for key ~"<<key<<"~ : "<<ciphertext<<endl;

		//Decrypting corresponding to the key	
		decryptedText=decrypt(ciphertext,matrix);
		cout<<"Decrypted text corresponding to Key ~"<<key<<"~ : "<<decryptedText<<endl;
		
		cout<<endl<<"Enter more keys(Y/N):";
		cin>>ch;
	}while(ch=='Y' || ch=='y');
	
	return 0;
}
