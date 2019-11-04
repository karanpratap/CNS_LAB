//Author : karanpratap
//Program : RSA Algorithm [Client Side Code]

#include<bits/stdc++.h>
#include<arpa/inet.h>
#define MAX 100
using namespace std;

map<string,char> invCodes{
	{"00",'a'},{"01",'b'},{"02",'c'},{"03",'d'},{"04",'e'},{"05",'f'},{"06",'g'},{"07",'h'},{"08",'i'},{"09",'j'},{"10",'k'},{"11",'l'},{"12",'m'},{"13",'n'},{"14",'o'},{"15",'p'},{"16",'q'},{"17",'r'},{"18",'s'},{"19",'t'},{"20",'u'},{"21",'v'},{"22",'w'},{"23",'x'},{"24",'y'},{"25",'z'},{"26",'A'},{"27",'B'},{"28",'C'},{"29",'D'},{"30",'E'},{"31",'F'},{"32",'G'},{"33",'H'},{"34",'I'},{"35",'J'},{"36",'K'},{"37",'L'},{"38",'M'},{"39",'N'},{"40",'O'},{"41",'P'},{"42",'Q'},{"43",'R'},{"44",'S'},{"45",'T'},{"46",'U'},{"47",'V'},{"48",'W'},{"49",'X'},{"50",'Y'},{"51",'Z'}
};

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
	string host;
	cout<<"Enter the server IP address:";
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
	
	//for(e=2;e<phin;e++){
	//	if(gcd(e,phin)==1)
	//		break;
	//}

	srand(time(NULL));
	do{
		e=2+rand()%(phin-2);
	}while(gcd(e,phin)!=1);

	d=extendedEuclidean(e,phin);

	int PU[2]={e,n};
	int PR[2]={d,n};
	int C,M;
	string decMsg="",msg="";

	cout<<"Private key calculated: {"<<PR[0]<<", "<<PR[1]<<"}"<<endl;
	cout<<"Public key: {"<<PU[0]<<", "<<PU[1]<<"}"<<endl;
	cout<<"Sending public key to server...";
	send(network_socket,PU,sizeof(PU),0);
	cout<<"OK"<<endl;
	cout<<"Recieving ciphertext from server...";
	while(1){
		recv(network_socket,&C,sizeof(C),0);
		if(C==-1) break;
		cout<<"Recieved CipherText block : "<<C<<endl;
		M=decryption(C,PR);
		string temp="0000"+to_string(M);
		decMsg+=temp.substr(temp.length()-4,4);
	}
	cout<<"Equivalent plaintext Blocks are : ";
	for(int i=0;i<decMsg.length()/4;i++){
		cout<<decMsg.substr(i*4,4)<<" ";
		msg+=invCodes[decMsg.substr(i*4,2)];
		msg+=invCodes[decMsg.substr(i*4+2,2)];
	}

	cout<<"Decrypted message is : "<<msg<<endl;
	
	return 0;
}
