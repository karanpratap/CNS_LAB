#include<bits/stdc++.h>
#include<arpa/inet.h>
using namespace std;

int encryption(int M, int PU[2]){
	int C=1;
    for(int i=1; i<=PU[0]; i++)
        C = (C*M)%PU[1];
	return C;
}

int main(){
	char server_msg[256];
	int serv_socket=socket(AF_INET,SOCK_STREAM,0);
	struct sockaddr_in server_address, clin_address;
	server_address.sin_family=AF_INET;
	int port_no;
	cout<<"Enter the port no : ";
	cin>>port_no;
	server_address.sin_port=htons(port_no);
	inet_aton("127.0.0.1",&server_address.sin_addr); 

	bind(serv_socket,(struct sockaddr*)&server_address,sizeof(server_address));

	listen(serv_socket,5);
	
	int client_socket;
	int clien_len=sizeof(clin_address);
	client_socket=accept(serv_socket,(struct sockaddr*)&clin_address,(unsigned int*)&clien_len);
	
	int PU[2], M, C;
	recv(client_socket,PU,sizeof(PU),0);
	cout<<"Public key recieved : {"<<PU[0]<<", "<<PU[1]<<"}"<<endl;
	cout<<"Enter the plaintext message M(<"<<PU[1]<<") to encrypt:";
	cin>>M;
	C=encryption(M,PU);
	cout<<"Encrypted message:"<<C<<endl;
	cout<<"Sending encrypted message to client...";
	send(client_socket,&C,sizeof(C),0);
	cout<<"OK"<<endl;
	return 0;
}
