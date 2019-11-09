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
	srand(time(NULL));
	char server_msg[256];
	int serv_socket=socket(AF_INET,SOCK_STREAM,0);
	struct sockaddr_in server_address, clin_address;
	server_address.sin_family=AF_INET;
	int port_no;
	cout<<"Enter the port no : ";
	cin>>port_no;
	server_address.sin_port=htons(port_no);
	//inet_aton("127.0.0.1",&server_address.sin_addr); 
	server_address.sin_addr.s_addr=INADDR_ANY;

	bind(serv_socket,(struct sockaddr*)&server_address,sizeof(server_address));

	listen(serv_socket,5);
	
	int client_socket;
	int clien_len=sizeof(clin_address);
	client_socket=accept(serv_socket,(struct sockaddr*)&clin_address,(unsigned int*)&clien_len);
	
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
	int M, C, N1, N2, IDA, PUb[2], K;
	
	cout<<"Private key (A) calculated: {"<<PR[0]<<", "<<PR[1]<<"}"<<endl;
	cout<<"Public key (A): {"<<PU[0]<<", "<<PU[1]<<"}"<<endl;
	
	recv(client_socket,PUb,sizeof(PUb),0);
	cout<<"Public key (B) recieved : {"<<PUb[0]<<", "<<PUb[1]<<"}"<<endl;
	cout<<"Sending own public key to client...";
	send(client_socket,PU,sizeof(PU),0);
	cout<<"OK"<<endl<<endl;

	cout<<"Enter the identification of A(<"<<PU[1]/100<<"):";
	cin>>IDA;
	N1=rand()%100;
	cout<<"Selected N1 : "<<N1<<endl;
	M=IDA*100+N1;
	C=encryption(M,PUb);
	cout<<"Encrypted message E(PUb, [N1||IDa]):"<<C<<endl;
	cout<<"Sending encrypted message E(PUb, [N1||IDa]) to client...";
	send(client_socket,&C,sizeof(C),0);
	cout<<"OK"<<endl<<endl;

	cout<<"Recieving encrypted message E(PUa, [N1||N2]) from client...";
	recv(client_socket,&C,sizeof(C),0);
	cout<<"OK"<<endl;
	cout<<"Recieved encrypted message E(PUa, [N1||N2]): "<<C<<endl<<endl;

	M=decryption(C,PR);
	N2=M%100;

	cout<<"Decrypted message for E(PUa, [N1||N2]): "<<M<<endl;
	cout<<"N2 extracted is : "<<N2<<endl<<endl;
	
	M=N2;
	C=encryption(M,PUb);

	cout<<"Encrypted message E(PUb,N2) is:"<<C<<endl;
	cout<<"Sending encrypted message E(PUb,N2) to client...";
	send(client_socket,&C,sizeof(C),0);
	cout<<"OK"<<endl<<endl;

	cout<<"Now selecting secret key...";
	K=rand()%PU[1];
	cout<<"OK"<<endl;

	C=encryption(encryption(K,PR),PUb);

	cout<<"Selected secret key:"<<K<<endl;
	cout<<"Encrypted message E(PUb, E(PRa,K)) to be sent to client : "<<C<<endl<<endl;

	cout<<"Sending encrypted message E(PUb, E(PRa,K)) to the client...";
	send(client_socket,&C,sizeof(C),0);
	cout<<"OK"<<endl;

	return 0;
}
