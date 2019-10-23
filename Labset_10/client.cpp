#include<bits/stdc++.h>
#include<arpa/inet.h>
#define MAX 100

using namespace std;

int extendedEuclidean(int num,int n){
	int P[MAX]={0,1},Q[MAX]={0};
	int nRes=n;
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
			P[i]=((P[i-2]-P[i-1]*Q[i-2])>=0)?(P[i-2]-P[i-1]*Q[i-2])%nRes:nRes+(P[i-2]-P[i-1]*Q[i-2])%nRes;
		if(num!=0)
			i++;
		else
			return ((P[i-1]-P[i]*Q[i-1])>=0)?(P[i-1]-P[i]*Q[i-1])%nRes:nRes+(P[i-1]-P[i]*Q[i-1])%nRes;
	}
}

int gcd(int a, int b)
{
    return b==0 ? a : gcd(b, a%b);
}

int decryption(int C, int PR[2]){
    int M = 1;
    for(int i=1;i<=PR[0];i++)
        M=(M*C)%PR[1];
    return M;
}

int main(){

	//establishing the connection
	
	int network_socket;
	network_socket=socket(AF_INET,SOCK_STREAM,0);

	struct sockaddr_in server_address;
	server_address.sin_family=AF_INET;
	int port_no;
	printf("Enter the port no : ");
	cin>>port_no;
	server_address.sin_port=htons(port_no); 
	server_address.sin_addr.s_addr= INADDR_ANY; 

	int status=connect(network_socket,(struct sockaddr*)&server_address, sizeof(server_address));
	
	if(status<0){
		cout<<"Connection Error";
		exit(0);
	}
	
	int p,q,e,n,d,phin;

	cout<<"Enter the values of p and q:";
	cin>>p>>q;
	n=p*q;
	phin=(p-1)*(q-1);
	
	for(e=2;e<phin;e++){
		if(gcd(e,phin)==1)
			break;
	}

	d=extendedEuclidean(e,phin);

	int PU[2]={e,n};
	int PR[2]={d,n};
	int C;

	cout<<"Private key calculated: {"<<PR[0]<<", "<<PR[1]<<"}"<<endl;
	cout<<"Public key: {"<<PU[0]<<", "<<PU[1]<<"}"<<endl;
	cout<<"Sending public key to server...";
	send(network_socket,PU,sizeof(PU),0);
	cout<<"OK"<<endl;
	cout<<"Recieving ciphertext from server...";
	recv(network_socket,&C,sizeof(C),0);
	cout<<"OK"<<endl;
	cout<<"Recieved encrypted message : "<<C<<endl;

	int M=decryption(C,PR);

	cout<<"Decrypted message is : "<<M<<endl;

	return 0;
}
