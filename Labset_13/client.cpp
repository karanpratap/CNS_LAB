//Author : karanpratap
//Program : Diffie-Hellman Key Exchange [Client]

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
	srand((unsigned)time(0));
	//establishing the connection
	string host;
	cout<<"Enter the server IP address";
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
	
	int qandAlpha[2];
	cout<<"Recieving q and alpha from server...";
	recv(network_socket,qandAlpha,sizeof(qandAlpha),0);
	cout<<"OK"<<endl;

	int xb=rand()%qandAlpha[0];
	cout<<"selected X(B)="<<xb<<endl;

	int yb=calculatePublicY(xb,qandAlpha[1],qandAlpha[0]);
	
	int ya, K;
	cout<<"Recieving public Y(A) from server...";
	recv(network_socket,&ya,sizeof(ya),0);
	cout<<"OK"<<endl;
	cout<<"Recieved Y(A) = "<<ya<<endl;

	cout<<"Sending public Y(B) to server...";
	send(network_socket,&yb,sizeof(yb),0);
	cout<<"OK"<<endl;

	K=calculateKey(xb,ya,qandAlpha[0]);

	cout<<"Calculated key K by server = "<<K<<endl;
	
	return 0;
}
