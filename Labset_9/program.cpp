//Program : Blum, Blum, Shub PRNG (BBS)

#include<bits/stdc++.h>
using namespace std;

int binToDecimal(string input){
	int res=0;
	for(int i=0;i<input.length();i++)
        res+=(input[input.length()-1-i]-48)*pow(2,i);
	return res;
}

string decToBinary(int input){
	bitset<48> b(input);
	return b.to_string();
}

int gcd(int a, int b){
	return (b==0)?a:gcd(b,a%b);
}

long long aPowbModn(int a, int b, int n){
	long long c=0,f;
	string bStr=decToBinary(b);
	for(int i=0;i<bStr.length();i++){
		c=c*2;
		f=(f*f)%n;
		if(bStr[i]=='1'){
			c+=1;
			f=(f*a)%n;
		}
	}
	return f;
}

string BBS_PRNG(int p,int q, int noOfBits){
	string res="";
	srand(time(NULL));
	int n=p*q;
	int s=rand()%n+p;
	
	while(gcd(s,n)!=1)
		s++;

	cout<<"s = "<<s<<endl;

	int x=aPowbModn(s,2,n);
	int b=0;
	for(int i=0;i<noOfBits;i++){
		x=aPowbModn(x,2,n);
		b=x%2;
		res+=b+48;
	}
	return res;
}

//Since rabin-miller test is said to have a probability of a wrong result for 25% values less than n, we check for 25% values of n
bool rabinMillerTest(int n){
	srand(time(NULL));
	int nBup=n;
	int k=0,q,a;
	bool flag=false;
	
	while(n%2==0){
		k++;
		n/=2;
	}
	q=n;

	for(int i=0;i<nBup/4;i++){
		a=rand()%(n-3)+2;
		cout<<"a for iteration "<<i+1<<" : "<<a<<" || ";
		
		if(aPowbModn(a,q,n)==1){
			cout<<"inconclusive for a="<<a<<endl;
			continue;
		}
	
		for(int j=0;j<k;j++){
			if(aPowbModn(a,pow(2,j)*q,n)==n-1){
				cout<<"inconclusive for a="<<a<<endl;
				continue;
			}
		}
		cout<<"composite for a="<<a<<endl;
		flag=true;
	}
	
	return flag;
}

int main(){
	int p,q,n;
	cout<<"Enter the values of prime numbers p and q [such that p=3 mod 4 and q=3 mod 4] : ";
	cin>>p>>q;
	cout<<"Enter number of bits for the newly generated random number:";
	cin>>n;
	string randomNumber=BBS_PRNG(p,q,n);
	cout<<"Generated Random number in binary:"<<randomNumber<<endl;
	cout<<"Generated random number in decimal:"<<binToDecimal(randomNumber)<<endl;
	bool test=rabinMillerTest(73);
	//bool test=rabinMillerTest(binToDecimal(randomNumber));
	cout<<"Result of applying RABIN-MILLER test : "<<endl;
	if(test)
		cout<<binToDecimal(randomNumber)<<" is composite"<<endl;
	else
		cout<<binToDecimal(randomNumber)<<" is prime"<<endl;
	return 0;
}
