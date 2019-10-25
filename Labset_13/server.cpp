//Author : karanpratap
//Program : Diffie-Hellman Key Exchange [Server]

#include<bits/stdc++.h>
#include<arpa/inet.h>
using namespace std;

int calculatePublicY(int x, int alpha, int q){
	int y=1;
	for(int i=1;i<=x;i++)
		y=(y*alpha)%q;
	return y;
}

int calculateKey(int x,int y,int q){
	int K=1;
	for(int i=1;i<=x;i++)
		K=(K*y)%q;
	return K;
}

int main(){
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
	
	srand((unsigned)time(0));
	int qandAlpha[2];
	cout<<"Enter the value of q and alpha:";
	cin>>qandAlpha[0]>>qandAlpha[1];
	int xa=rand()%qandAlpha[0];

	cout<<"Sharing q and alpha with client...";
	send(client_socket,qandAlpha,sizeof(qandAlpha),0);
	cout<<"OK"<<endl;
	
	cout<<"selected X(A)="<<xa<<endl;

	int ya=calculatePublicY(xa,qandAlpha[1],qandAlpha[0]);
	
	int yb,K;
	cout<<"Sending public Y(A) to client...";
	send(client_socket,&ya,sizeof(ya),0);
	cout<<"OK"<<endl;

	cout<<"Recieving public Y(B) from client...";
	recv(client_socket,&yb,sizeof(yb),0);
	cout<<"OK"<<endl;
	cout<<"Recieved Y(B) = "<<yb<<endl;

	K=calculateKey(xa,yb,qandAlpha[0]);

	cout<<"Calculated key K by server = "<<K<<endl;

	return 0;
}
