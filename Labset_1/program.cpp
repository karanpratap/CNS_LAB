#include<bits/stdc++.h>
using namespace std;

int fact(int n){
	if(n==1 || n==0)
		return 1;
	return n*fact(n-1);
}

int distinctCount=0, noOfPerms=0, totalChars=0;

void permute(string a, int l, int r, char perm[][27]){
    //perms.open("permutations.txt",ios::app);
    if (l == r){
		noOfPerms++;
        for(int i=0;i<distinctCount;i++){
			perm[noOfPerms][i]=a[i];
		}
    }
    else{
        for (int i = l; i <= r; i++){
            swap(a[l], a[i]);
            permute(a, l+1, r, perm);
            swap(a[l], a[i]);
        }
    }
}

bool contains(char arr[],char ch){
    for(int i=0;i<distinctCount;i++)
        if(arr[i]==ch)
            return true;
    return false;
}

int indexOf(char arr[],char ch){
    for(int i=0;i<distinctCount;i++)
        if(arr[i]==ch)
            return i;
    return -1;
}

int main(){
    srand(time(0));
    char ch, distinct[27], key[27];
    ifstream infile;
    ofstream cipher;
    //perms<<"Enable reality"<<endl;
    infile.open("plaintext.txt",ios::in);
    cout<<"Reading from the file plaintext"<<endl;
    while(infile>>skipws>>ch){
        cout<<ch;
        if(contains(distinct,ch))
            continue;
        distinct[::distinctCount++]=ch;
        totalChars++;
    }
	cout<<endl;
	infile.close();
	char perms[fact(totalChars)][27];
	
    infile.open("plaintext.txt",ios::in);
	int frequency[distinctCount]={0};
 	
	while(infile>>skipws>>ch){
		frequency[indexOf(distinct,ch)]+=1;
	}

	infile.close();
    infile.open("plaintext.txt",ios::in);
    
	cout<<"Distinct Characters["<<distinctCount<<"]: ";
    for(int i=0;i<distinctCount;i++)
        cout<<distinct[i]<<" ";
    cout<<endl;

    //cout<<"Permutations of all distinct characters:\n";
    permute(distinct,0,distinctCount-1,perms);
	
	int random=rand()%noOfPerms;
    for(int i=0;i<distinctCount;i++){
        key[i]=perms[random][i];
    }
    cout<<endl<<"Key:";
    for(int i=0;i<distinctCount;i++){
        cout<<key[i]<<" ";
    }
    int idx;
    cout<<"\n";
    cipher.open("ciphertext.txt");
    infile.close();
    infile.open("plaintext.txt",ios::in);

    cout<<"Frequency Table:\n";
    cout<<" Frequency | Plaintext character | Ciphertext Character"<<endl;
	
	for(int i=0;i<distinctCount;i++){
		cout<<" "<<setw(9)<<left<<setprecision(2)<<frequency[i]/(float)totalChars<<" | "<<setw(19)<<left<<distinct[i]<<" | "<<setw(15)<<left<<key[i]<<endl;
	}

    while(infile>>skipws>>ch){
        cipher<<key[indexOf(distinct,ch)];
	}
    infile.close();

    return 0;
}
