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

int gcd(int a, int b){
    return b==0 ? a : gcd(b, a%b);
}

int encryption(int M, int PU[2]){
	int C=1;
    for(int i=1; i<=PU[0]; i++)
        C = (C*M)%PU[1];
	return C;
}

int decryption(int C, int PR[2]){
    int M = 1;
    for(int i=1;i<=PR[0];i++)
        M=(M*C)%PR[1];
    return M;
}

int main(){

	//establishing the connection
	string host;	
	cout<<"Enter the host IP:";
	cin>>host;

	int network_socket;
	network_socket=socket(AF_INET,SOCK_STREAM,0);

	struct sockaddr_in server_address;
	server_address.sin_family=AF_INET;
	int port_no;
	printf("Enter the port no : ");
	cin>>port_no;
	server_address.sin_port=htons(port_no); 
	//server_address.sin_addr.s_addr= INADDR_ANY; 
	
	inet_aton(host.c_str(),&server_address.sin_addr);

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
	
	do{
		e=rand()%(phin-2)+2;
	}while(gcd(e,phin)!=1);

	d=extendedEuclidean(e,phin);

	int PU[2]={e,n};
	int PR[2]={d,n};
	int M, C, N1, N2, PUa[2], temp, K;
	srand(time(NULL));

	cout<<"Private key (B) calculated: {"<<PR[0]<<", "<<PR[1]<<"}"<<endl;
	cout<<"Public key (B): {"<<PU[0]<<", "<<PU[1]<<"}"<<endl;
	cout<<"Sending public key to server...";
	send(network_socket,PU,sizeof(PU),0);
	cout<<"OK"<<endl;
	recv(network_socket,PUa,sizeof(PUa),0);
	cout<<"Public key (A) recieved : {"<<PUa[0]<<", "<<PUa[1]<<"}"<<endl<<endl;

	cout<<"Recieving ciphertext 1 from server...";
	recv(network_socket,&C,sizeof(C),0);
	cout<<"OK"<<endl;
	cout<<"Recieved encrypted message E(PUb, [N1||IDa]): "<<C<<endl<<endl;

	M=decryption(C,PR);
	N1=M%100;

	cout<<"Decrypted message for E(PUb, [N1||IDa]) : "<<M<<endl;
	cout<<"N1 extracted is : "<<N1<<endl<<endl;
	
	N2=rand()%100;
	M=N1*100+N2;
	C=encryption(M,PUa);
	
	cout<<"Encrypted message E(PUa, [N1||N2]) is:"<<C<<endl;
	cout<<"Sending encrypted message E(PUa, [N1||N2]) to server...";
	send(network_socket,&C,sizeof(C),0);
	cout<<"OK"<<endl<<endl;
	
	cout<<"Recieving encrypted message E(PUb,N2) from server...";
	recv(network_socket,&C,sizeof(C),0);
	cout<<"OK"<<endl;
	cout<<"Recieved encrypted message E(PUb,N2): "<<C<<endl<<endl;

	temp=decryption(C,PR);
	
	if(N2==temp)
		cout<<"N2 recieved is correct:"<<temp<<endl<<endl;
	else
		cout<<"Value of N2 recieved doesn't match original value:"<<temp<<endl<<endl;
	
	cout<<"Recieving secret key in encrypted message E(PUb, E(PRa,K)) from server...";
	recv(network_socket,&C,sizeof(C),0);
	cout<<"OK"<<endl;
	cout<<"Recieved encrypted message E(PUb, E(PRa,K)): "<<C<<endl<<endl;

	cout<<"Performing decryption D(PUa, D(PRb,M)) to obtain secret key...";
	K=decryption(decryption(C,PR),PUa);
	cout<<"OK"<<endl;

	cout<<"Secret key obtained:"<<K<<endl;

	return 0;
}
