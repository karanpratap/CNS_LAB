//Author: karanpratap
//Program: Hill Cipher

#include<bits/stdc++.h>
#define MAX 10

using namespace std;

void swap(int *a,int *b){
	int temp;
	temp=*a;
	*a=*b;
	*b=temp;
}

int extendedEuclidean(int num,int n){
	int P[MAX],Q[MAX];
	int i=0,temp;
	if(num==1)
		return num;
	while(1){
		Q[i]=n/num;
		temp=n;
		n=num;
		num=temp%num;
		if(i==0 || i==1)
			P[i]=i;
		else
			P[i]=((P[i-2]-P[i-1]*Q[i-2])>=0)?(P[i-2]-P[i-1]*Q[i-2])%26:26+(P[i-2]-P[i-1]*Q[i-2])%26;
		if(num!=0)
			i++;
		else
			return ((P[i-1]-P[i]*Q[i-1])>=0)?(P[i-1]-P[i]*Q[i-1])%26:26+(P[i-1]-P[i]*Q[i-1])%26;
	}
}

int determinantmod263(int arr[3][3]){
	return (arr[0][0]*(arr[1][1]*arr[2][2]-arr[2][1]*arr[1][2])-arr[0][1]*(arr[1][0]*arr[2][2]-arr[1][2]*arr[2][0])+arr[0][2]*(arr[1][0]*arr[2][1]-arr[2][0]*arr[1][1]))>=0?(arr[0][0]*(arr[1][1]*arr[2][2]-arr[2][1]*arr[1][2])-arr[0][1]*(arr[1][0]*arr[2][2]-arr[1][2]*arr[2][0])+arr[0][2]*(arr[1][0]*arr[2][1]-arr[2][0]*arr[1][1]))%26:26+(arr[0][0]*(arr[1][1]*arr[2][2]-arr[2][1]*arr[1][2])-arr[0][1]*(arr[1][0]*arr[2][2]-arr[1][2]*arr[2][0])+arr[0][2]*(arr[1][0]*arr[2][1]-arr[2][0]*arr[1][1]))%26;
}

int determinantmod262(int arr[2][2]){
	return (arr[0][0]*arr[1][1]-arr[0][1]*arr[1][0])>=0?(arr[0][0]*arr[1][1]-arr[0][1]*arr[1][0])%26:26+(arr[0][0]*arr[1][1]-arr[0][1]*arr[1][0])%26;
}

void matrixInverse3(int arr[3][3]){
	int inv=extendedEuclidean(determinantmod263(arr),26),dummy[5][5];
		//finding adjoint of the transpose
		for(int i=0;i<5;i++)
			for(int j=0;j<5;j++)
				dummy[i][j]=arr[i%3][j%3];

		for(int i=1;i<4;i++){
			for(int j=1;j<4;j++)
				arr[j-1][i-1]=((dummy[i][j]*dummy[i+1][j+1]-dummy[i][j+1]*dummy[i+1][j])>=0)?(inv*(dummy[i][j]*dummy[i+1][j+1]-dummy[i][j+1]*dummy[i+1][j]))%26:26+(inv*(dummy[i][j]*dummy[i+1][j+1]-dummy[i][j+1]*dummy[i+1][j]))%26;
		}
}

void matrixInverse2(int arr[2][2]){
	int inv=extendedEuclidean(determinantmod262(arr),26);
	//finding adjoint of the transpose
	swap(arr[0][0],arr[1][1]);
	arr[0][0]=((inv*arr[0][0])>=0)?(inv*arr[0][0])%26:26+inv*arr[0][0]%26;
	arr[1][1]=((inv*arr[1][1])>=0)?(inv*arr[1][1])%26:26+inv*arr[1][1]%26;
	arr[0][1]=((-arr[0][1]*inv)>=0)?(-arr[0][1]*inv)%26:26+(-arr[0][1]*inv)%26;
	arr[1][0]=((-arr[1][0]*inv)>=0)?(-arr[1][0]*inv)%26:26+(-arr[1][0]*inv)%26;
}

void hillCipher(char msg[], int k2[2][2], int k3[3][3]){
	//encryption
	int msgMatrix2[MAX][2], msgMatrix3[MAX][3], cipherText2[MAX][2], cipherText3[MAX][3];
	int noOfRows2, noOfRows3;
	int pointer=0, j;
	noOfRows2=(strlen(msg)%2==0)?strlen(msg)/2:strlen(msg)/2+1;
	noOfRows3=(strlen(msg)%3==0)?strlen(msg)/3:strlen(msg)/3+1;
	
	for(int i=0;i<noOfRows2;i++)
		for(j=0;j<2;j++){
			msgMatrix2[i][j]=(msg[pointer]!='\0')?msg[pointer++]-97:'x'-97;
			cipherText2[i][j]=0;
		}

	pointer=0; //resetting pointer

	for(int i=0;i<noOfRows3;i++)
		for(j=0;j<3;j++){
			msgMatrix3[i][j]=(msg[pointer]!='\0')?msg[pointer++]-97:'x'-97;
			cipherText3[i][j]=0;
		}

	for(int i=0;i<noOfRows2;i++)
			for(int j=0;j<2;j++)
				for(int k=0;k<2;k++)
					cipherText2[i][j]=(cipherText2[i][j]+msgMatrix2[i][k]*k2[k][j])%26;
	
	for(int i=0;i<noOfRows3;i++)
			for(int j=0;j<3;j++)
				for(int k=0;k<3;k++)
					cipherText3[i][j]=(cipherText3[i][j]+msgMatrix3[i][k]*k3[k][j])%26;

	cout<<"CipherText from 2x2 matrix:";
	for(int i=0;i<noOfRows2;i++){
		for(j=0;j<2;j++){
			cout<<(char)(cipherText2[i][j]+97);
			msgMatrix2[i][j]=0;
		}
	}
	cout<<endl;

	cout<<"CipherText from 3x3 matrix:";
	for(int i=0;i<noOfRows3;i++){
		for(j=0;j<3;j++){
			cout<<(char)(cipherText3[i][j]+97);
			msgMatrix3[i][j]=0;
		}
	}
	cout<<endl;

	//decryption
	cout<<"Calculated Inverse of 2x2 key matrix:"<<endl;
	matrixInverse2(k2);
	matrixInverse3(k3);
	for(int i=0;i<2;i++){
		for(j=0;j<2;j++)
			cout<<k2[i][j]<<" ";
		cout<<endl;
	}
	cout<<endl;
	cout<<"Calculated Inverse of 3x3 key matrix:"<<endl;
	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++)
			cout<<k3[i][j]<<" ";
		cout<<endl;
	}
	
	for(int i=0;i<noOfRows2;i++)
			for(int j=0;j<2;j++)
				for(int k=0;k<2;k++)
					msgMatrix2[i][j]=(msgMatrix2[i][j]+cipherText2[i][k]*k2[k][j])%26;
	
	for(int i=0;i<noOfRows3;i++)
			for(int j=0;j<3;j++)
				for(int k=0;k<3;k++)
					msgMatrix3[i][j]=(msgMatrix3[i][j]+cipherText3[i][k]*k3[k][j])%26;

	cout<<"DeCipheredText from 2x2 matrix:";
	for(int i=0;i<noOfRows2;i++){
		for(j=0;j<2;j++){
			cout<<(char)(msgMatrix2[i][j]+97);
		}
	}
	cout<<endl;

	cout<<"DeCipheredText from 3x3 matrix:";
	for(int i=0;i<noOfRows3;i++){
		for(j=0;j<3;j++){
			cout<<(char)(msgMatrix3[i][j]+97);
		}
	}
	cout<<endl;

}

int main(){
	char msg[30];
	int key2[2][2], key3[3][3];
	cout<<"Enter the message in plaintext:";
	cin>>msg;

	cout<<"Enter the 2x2 key matrix:"<<endl;
	for(int i=0;i<2;i++)
		for(int j=0;j<2;j++)
			cin>>key2[i][j];

	cout<<"Enter the 3x3 key matrix:"<<endl;
	for(int i=0;i<3;i++)
		for(int j=0;j<3;j++)
			cin>>key3[i][j];
	
	hillCipher(msg, key2, key3);	
	return 0;
}
