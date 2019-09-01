//Author : karanpratap
//Program : Extended Eucledian Algorithm

#include<bits/stdc++.h>
#define MAX 10

using namespace std;

int extendedEuclidean(int num,int n){
	int P[MAX],Q[MAX];
	int i=0,temp;
	while(1){
		Q[i]=n/num;
		temp=n;
		n=num;
		num=temp%num;
		if(i==0 || i==1)
			P[i]=i;
		else
			P[i]=((P[i-2]-P[i-1]*Q[i-2])>=0)?(P[i-2]-P[i-1]*Q[i-2])%26:26+(P[i-2]-P[i-1]*Q[i-2]);
		if(num!=0)
			i++;
		else
			return ((P[i-1]-P[i]*Q[i-1])>=0)?(P[i-1]-P[i]*Q[i-1])%26:26+(P[i-1]-P[i]*Q[i-1]);
	}
}

int main(){
	int multInverse,num;
	cout<<"Enter the number whose multiplicative inverse is to be calculated:";
	cin>>num;
	multInverse=extendedEuclidean(num,26);
	cout<<"Multiplicative Inverse of "<<num<<" is "<<multInverse<<endl;
	return 0;
}
