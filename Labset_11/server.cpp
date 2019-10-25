//Author : karanpratap
//Program : RSA Algorithm [Server Side Code]

#include<bits/stdc++.h>
#include<arpa/inet.h>
using namespace std;

map<char,string> codes{
	{'a',"00"},{'b',"01"},{'c',"02"},{'d',"03"},{'e',"04"},{'f',"05"},{'g',"06"},{'h',"07"},{'i',"08"},{'j',"09"},{'k',"10"},{'l',"11"},{'m',"12"},{'n',"13"},{'o',"14"},{'p',"15"},{'q',"16"},{'r',"17"},{'s',"18"},{'t',"19"},{'u',"20"},{'v',"21"},{'w',"22"},{'x',"23"},{'y',"24"},{'z',"25"},{'A',"26"},{'B',"27"},{'C',"28"},{'D',"29"},{'E',"30"},{'F',"31"},{'G',"32"},{'H',"33"},{'I',"34"},{'J',"35"},{'K',"36"},{'L',"37"},{'M',"38"},{'N',"39"},{'O',"40"},{'P',"41"},{'Q',"42"},{'R',"43"},{'S',"44"},{'T',"45"},{'U',"46"},{'V',"47"},{'W',"48"},{'X',"49"},{'Y',"50"},{'Z',"51"}
};

int encryption(int M, int PU[2]){
	int C=1;
    for(int i=1; i<=PU[0]; i++)
        C = (C*M)%PU[1];
	return C;
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
	string msg, decMsg="";
	int PU[2], M, C;
	recv(client_socket,PU,sizeof(PU),0);
	cout<<"Public key recieved : {"<<PU[0]<<", "<<PU[1]<<"}"<<endl;
	cout<<"Enter the plaintext message to encrypt:";
	cin>>msg;
	for(int i=0;i<msg.length();i++)
		decMsg+=codes[msg[i]];
	cout<<"Equivalent decimal string is:"<<decMsg<<endl;
	cout<<"Encrypting plaintext blocks..."<<endl;
	for(int i=0;i<decMsg.length()/4;i++){
		const char* c=decMsg.substr(i*4,4).c_str();
		M=atoi(c);
		C=encryption(M,PU);
		cout<<"Encrypted block corresponding to block ["<<M<<"] = "<<C<<endl;
		send(client_socket,&C,sizeof(C),0);
	}
	C=-1;
	send(client_socket,&C,sizeof(C),0); //Send -1 to mark end of transfer
	return 0;
}
