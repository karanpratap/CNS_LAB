#include<bits/stdc++.h>
#define MAX 50
using namespace std;

const char filler='x';
char overrideChar;

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

bool contains(char arr[],char ch){
	for(int i=0;i<strlen(arr);i++)
		if(arr[i]==ch)
			return true;
	return false;
}

int main(){
	char msg[MAX], structuredMsg[MAX];
	int noOfKeys, structuredMsgLength=0;

	cout<<"Enter the message in plaintext:";
	cin>>msg;

	cout<<"Message Recieved:"<<msg<<endl;

	cout<<"Enter the number of keys:";
	cin>>noOfKeys;
	
	//declerations, initializations depending on the number of keys
	int distinctCount[noOfKeys];
	char keys[noOfKeys][MAX];
	char matrix[noOfKeys][5][5];
	char distinct[noOfKeys][26];
	char ciphertext[noOfKeys][MAX];
	char decryptedText[noOfKeys][MAX];
	
	for(int i=0;i<noOfKeys;i++)
		distinctCount[i]=0;

	//Taking input keywords
	cout<<"Enter the "<<noOfKeys<<" key(s):"<<endl;
	for(int i=0;i<noOfKeys;i++){
		cout<<"Key "<<i+1<<":";
		cin>>keys[i];
	}
	
	do{
		cout<<"Enter the character to override the other in the matrices (i/j):";
		cin>>overrideChar;
	}while(overrideChar!='i' &&  overrideChar!='j');

	//Structuring the message - Generating pairs and adding filler characters
	for(int i=0;i<strlen(msg);){
		if(msg[i+1]!='\0')
			if(msg[i]==msg[i+1]){
				structuredMsg[structuredMsgLength++]=(msg[i]=='i' || msg[i]=='j')?overrideChar:msg[i];
				structuredMsg[structuredMsgLength++]=filler;
				i++;
			}
			else{
				structuredMsg[structuredMsgLength++]=(msg[i]=='i' || msg[i]=='j')?overrideChar:msg[i];
				structuredMsg[structuredMsgLength++]=(msg[i+1]=='i' || msg[i+1]=='j')?overrideChar:msg[i+1];
				i+=2;
			}
		else{
			structuredMsg[structuredMsgLength++]=(msg[i]=='i' || msg[i]=='j')?overrideChar:msg[i];
			structuredMsg[structuredMsgLength++]=filler;
			i++;
		}
	}
	structuredMsg[structuredMsgLength]='\0';

	//Generating the 5x5 matrices corresponding to the keys
	for(int i=0;i<noOfKeys;i++){
		//Generating distinct characters present in each of the keys
		bool visited[26]={false};
		int pointer=0, row=0, col=0;
		distinctCount[i]=0;
		for(int j=0;j<strlen(keys[i]);j++){
			if(!contains(distinct[i],(keys[i][j]=='i' || keys[i][j]=='j')?overrideChar:keys[i][j])){
				distinct[i][distinctCount[i]++]=(keys[i][j]=='i' || keys[i][j]=='j')?overrideChar:keys[i][j];
			}
		}
		
		//Inserting the distinct chars in the matrix
		for(int j=0;j<distinctCount[i];j++){
			matrix[i][row][col]=distinct[i][j];
			visited[distinct[i][j]-97]=true;
			if(matrix[i][row][col]==overrideChar)
				visited[8]=visited[9]=true;
			row=(col<4)?row:((row+1)%5);
			col=(col+1)%5;
		}
		
		//Inserting the leftover characters in the matrix
		while(pointer<26){
			if(!visited[pointer]){
				matrix[i][row][col]=(pointer==8 || pointer==9)?overrideChar:pointer+97;
				visited[pointer]=true;
				if(pointer==8 || pointer==9)
					visited[8]=visited[9]=true;
				row=(col<4)?row:((row+1)%5);
				col=(col+1)%5;
			}
			pointer++;
		}
	}
	
	cout<<"Echoing back the distinct characters in all the keys for test purposes:"<<endl;
	for(int i=0;i<noOfKeys;i++){
		cout<<"Key "<<i+1<<" ["<<distinctCount[i]<<"] : ";
		for(int j=0;j<distinctCount[i];j++)
			cout<<distinct[i][j]<<" ";
		cout<<endl;
	}

	cout<<"Echoing back the matrices for testing purposes:"<<endl;
	for(int i=0;i<noOfKeys;i++){
		cout<<"Matrix for key "<<i+1<<" :"<<endl;
		for(int j=0;j<5;j++){
			for(int k=0;k<5;k++){
				cout<<matrix[i][j][k]<<" ";
			}
			cout<<endl;
		}
	}

	cout<<"The message after structuring is: "<<structuredMsg<<endl;

	//Encrypting the message corresponding to all the keys
	for(int i=0;i<noOfKeys;i++){
		int j=0;
		for(j=0;j<structuredMsgLength;j+=2){	
			if(rowOf(matrix[i],structuredMsg[j])==rowOf(matrix[i],structuredMsg[j+1])){
				ciphertext[i][j]=matrix[i][rowOf(matrix[i],structuredMsg[j])][(colOf(matrix[i],structuredMsg[j])+1)%5];
				ciphertext[i][j+1]=matrix[i][rowOf(matrix[i],structuredMsg[j+1])][(colOf(matrix[i],structuredMsg[j+1])+1)%5];
			}
			else if(colOf(matrix[i],structuredMsg[j])==colOf(matrix[i],structuredMsg[j+1])){
				ciphertext[i][j]=matrix[i][(rowOf(matrix[i],structuredMsg[j])+1)%5][colOf(matrix[i],structuredMsg[j])];
				ciphertext[i][j+1]=matrix[i][(rowOf(matrix[i],structuredMsg[j+1])+1)%5][colOf(matrix[i],structuredMsg[j])];
			}
			else{
				ciphertext[i][j]=matrix[i][rowOf(matrix[i],structuredMsg[j])][colOf(matrix[i],structuredMsg[j+1])];
				ciphertext[i][j+1]=matrix[i][rowOf(matrix[i],structuredMsg[j+1])][colOf(matrix[i],structuredMsg[j])];
			}
			cout<<endl;
		}
		ciphertext[i][structuredMsgLength]='\0';
		cout<<"Ciphertext corresponding to Key "<<i+1<<" : "<<ciphertext[i]<<endl;
	}
	

	//Decrypting corresponding to all the keys
	for(int i=0;i<noOfKeys;i++){
		int j=0;
		for(j=0;j<structuredMsgLength;j+=2){
			if(rowOf(matrix[i],ciphertext[i][j])==rowOf(matrix[i],ciphertext[i][j+1])){
				decryptedText[i][j]=matrix[i][rowOf(matrix[i],ciphertext[i][j])][(colOf(matrix[i],ciphertext[i][j])==0)?4:(colOf(matrix[i],ciphertext[i][j])-1)%5];
				decryptedText[i][j+1]=matrix[i][rowOf(matrix[i],ciphertext[i][j+1])][(colOf(matrix[i],ciphertext[i][j+1])==0)?4:(colOf(matrix[i],ciphertext[i][j+1])-1)%5];
			}
			else if(colOf(matrix[i],ciphertext[i][j])==colOf(matrix[i],ciphertext[i][j+1])){
				decryptedText[i][j]=matrix[i][(rowOf(matrix[i],ciphertext[i][j])==0)?4:(rowOf(matrix[i],ciphertext[i][j])-1)%5][colOf(matrix[i],ciphertext[i][j])];
				decryptedText[i][j+1]=matrix[i][(rowOf(matrix[i],ciphertext[i][j+1])==0)?4:(rowOf(matrix[i],ciphertext[i][j+1])-1)%5][colOf(matrix[i],ciphertext[i][j])];
			}
			else{
				decryptedText[i][j]=matrix[i][rowOf(matrix[i],ciphertext[i][j])][colOf(matrix[i],ciphertext[i][j+1])];
				decryptedText[i][j+1]=matrix[i][rowOf(matrix[i],ciphertext[i][j+1])][colOf(matrix[i],ciphertext[i][j])];
			}
			cout<<endl;
		}
		decryptedText[i][structuredMsgLength]='\0';
		cout<<"Decrypted text corresponding to Key "<<i+1<<" ["<<structuredMsgLength<<"]: "<<decryptedText[i]<<endl;
	}	
	
	return 0;
}
