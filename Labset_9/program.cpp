//Program : Blum, Blum, Shub PRNG (BBS)

#include<bits/stdc++.h>
using namespace std;

int binToDecimal(string input){
	int res=0;
	for(int i=0;i<input.length();i++)
        res+=(input[input.length()-1-i]-48)*pow(2,i);
	return res;
}

string BBS_PRNG(int p,int q){
	string res="";
	srand(time(NULL));
	int n=p*q;
	int s=rand()%n+p;
	
	while(true){
		if(s%p!=0 && s%q!=0)
			break;
		s++;
	}

	cout<<"s = "<<s<<endl;

	int x=(s*s)%n;
	int b=0;
	for(int i=0;i<16;i++){
		x=(x*x)%n;
		b=abs(x%2);
		cout<<"Bit "<<i+1<<" generated: "<<b<<endl;
		res+=b+48;
	}
	return res;
}

string rabinMillerTest(int n){
	srand(time(NULL));
	int a=rand()%(n-3)+2;
	int k=1;
	int flag=0, q=1;
	while(k<=16){
		for(q=1;pow(2,k)*q<n-1;q+=2)
			if(pow(2,k)*q==n-1){
				flag=1;
				break;
			}
		if(flag)
			break;
		k++;
	}
	
	if((int)pow(a,q)%n==1)
		return "inconclusive";
	
	for(int j=0;j<k;j++){
		if((int)pow(a,pow(2,j)*q)%n==n-1)
			return "inconclusive";
	}

	return "composite";
}

int main(){
	string randomNumber=BBS_PRNG(503,383);
	cout<<"Generated Random number in binary:"<<randomNumber<<endl;
	cout<<"Generated random number in decimal:"<<binToDecimal(randomNumber)<<endl;
	string test=rabinMillerTest(binToDecimal(randomNumber));
	cout<<"Result of applying RABIN-MILLER test : "<<test<<endl;
	return 0;
}
