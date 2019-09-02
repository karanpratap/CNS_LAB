#include<bits/stdc++.h>
#define MAX 3
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

int determinantmod26(int arr[][MAX],int n){
	if(n==2)
		return (arr[0][0]*arr[1][1]-arr[0][1]*arr[1][0])>=0?(arr[0][0]*arr[1][1]-arr[0][1]*arr[1][0])%26:26+(arr[0][0]*arr[1][1]-arr[0][1]*arr[1][0])%26;
	else if(n==3)
		return (arr[0][0]*(arr[1][1]*arr[2][2]-arr[2][1]*arr[1][2])-arr[0][1]*(arr[1][0]*arr[2][2]-arr[1][2]*arr[2][0])+arr[0][2]*(arr[1][0]*arr[2][1]-arr[2][0]*arr[1][1]))>=0?(arr[0][0]*(arr[1][1]*arr[2][2]-arr[2][1]*arr[1][2])-arr[0][1]*(arr[1][0]*arr[2][2]-arr[1][2]*arr[2][0])+arr[0][2]*(arr[1][0]*arr[2][1]-arr[2][0]*arr[1][1]))%26:26+(arr[0][0]*(arr[1][1]*arr[2][2]-arr[2][1]*arr[1][2])-arr[0][1]*(arr[1][0]*arr[2][2]-arr[1][2]*arr[2][0])+arr[0][2]*(arr[1][0]*arr[2][1]-arr[2][0]*arr[1][1]))%26;
	return -1; //don't worry, this statement is just a filler to avoid the warning. It won't be used unless you specify an order other than 2 and 3.
}

void matrixInverse(int arr[][MAX],int n){
	if(n==2){
		int inv=extendedEuclidean(determinantmod26(arr,2),26);
		cout<<"Inverse of determinant of matrix="<<inv<<endl;
		//finding adjoint of the transpose
		swap(arr[0][0],arr[1][1]);
		arr[0][0]=((inv*arr[0][0])>=0)?(inv*arr[0][0])%26:26+inv*arr[0][0]%26;
		arr[1][1]=((inv*arr[1][1])>=0)?(inv*arr[1][1])%26:26+inv*arr[1][1]%26;
		arr[0][1]=((-arr[0][1]*inv)>=0)?(-arr[0][1]*inv)%26:26+(-arr[0][1]*inv)%26;
		arr[1][0]=((-arr[1][0]*inv)>=0)?(-arr[1][0]*inv)%26:26+(-arr[1][0]*inv)%26;
	}
	else if(n==3){
		int inv=extendedEuclidean(determinantmod26(arr,3),26),dummy[5][5];
		cout<<"Inverse of determinant of matrix="<<inv<<endl;
		//finding adjoint of the transpose
		for(int i=0;i<5;i++)
			for(int j=0;j<5;j++)
				dummy[i][j]=arr[i%3][j%3];

		for(int i=1;i<4;i++){
			for(int j=1;j<4;j++)
				if((i+j)%2==0)
					arr[j-1][i-1]=(dummy[i][j]*dummy[i+1][j+1]-dummy[i][j+1]*dummy[i+1][j]);
				//	arr[j-1][i-1]=((dummy[i][j]*dummy[i+1][j+1]-dummy[i][j+1]*dummy[i+1][j])>=0)?(inv*(dummy[i][j]*dummy[i+1][j+1]-dummy[i][j+1]*dummy[i+1][j]))%26:26+(inv*(dummy[i][j]*dummy[i+1][j+1]-dummy[i][j+1]*dummy[i+1][j]))%26;
				else
					arr[j-1][i-1]=(dummy[i][j]*dummy[i+1][j+1]-dummy[i][j+1]*dummy[i+1][j]);
				//	arr[j-1][i-1]=(-inv*(dummy[i][j]*dummy[i+1][j+1]-dummy[i][j+1]*dummy[i+1][j])>=0)?(-inv*(dummy[i][j]*dummy[i+1][j+1]-dummy[i][j+1]*dummy[i+1][j]))%26:26+(-inv*(dummy[i][j]*dummy[i+1][j+1]-dummy[i][j+1]*dummy[i+1][j]))%26;
		}

		cout<<"Checking..."<<endl;
		int res[3][3];
		for(int i=0;i<3;i++)
			for(int j=0;j<3;j++)
				res[i][j]=0;

		for(int i=0;i<3;i++)
			for(int j=0;j<3;j++)
				for(int k=0;k<3;k++)
					res[i][j]+=dummy[i][k]*arr[k][j];

		for(int i=0;i<3;i++){
			for(int j=0;j<3;j++)
				cout<<res[i][j]<<" ";
			cout<<endl;
		}
	}
}

int main(){
	int n;
	int arr[MAX][MAX];
	cout<<"Enter the order of the matrix:";
	cin>>n;

	cout<<"Enter the elements of the matrix:";
	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++)
			cin>>arr[i][j];
	
	matrixInverse(arr,3);

	cout<<"Inverted matrix is:"<<endl;
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++)
			cout<<arr[i][j]<<" ";
		cout<<endl;
	}

	return 0;
}
