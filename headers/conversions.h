void hexToBinary(char hex[17], char bin[65]){
	for(int i=0;i<64;i+=4){
		switch(hex[i/4]){
			case '0': bin[i]='0';
					  bin[i+1]='0';
					  bin[i+2]='0';
					  bin[i+3]='0';
					break;
			case '1': bin[i]='0';
					  bin[i+1]='0';
					  bin[i+2]='0';
					  bin[i+3]='1';
					break;
			case '2': bin[i]='0';
					  bin[i+1]='0';
					  bin[i+2]='1';
					  bin[i+3]='0';
					break;
			case '3': bin[i]='0';
					  bin[i+1]='0';
					  bin[i+2]='1';
					  bin[i+3]='1';
					break;
			case '4': bin[i]='0';
					  bin[i+1]='1';
					  bin[i+2]='0';
					  bin[i+3]='0';
					break;
			case '5': bin[i]='0';
					  bin[i+1]='1';
					  bin[i+2]='0';
					  bin[i+3]='1';
					break;
			case '6': bin[i]='0';
					  bin[i+1]='1';
					  bin[i+2]='1';
					  bin[i+3]='0';
					break;
			case '7': bin[i]='0';
					  bin[i+1]='1';
					  bin[i+2]='1';
					  bin[i+3]='1';
					break;
			case '8': bin[i]='1';
					  bin[i+1]='0';
					  bin[i+2]='0';
					  bin[i+3]='0';
					break;
			case '9': bin[i]='1';
					  bin[i+1]='0';
					  bin[i+2]='0';
					  bin[i+3]='1';
					break;
			case 'A': bin[i]='1';
					  bin[i+1]='0';
					  bin[i+2]='1';
					  bin[i+3]='0';
					break;
			case 'B': bin[i]='1';
					  bin[i+1]='0';
					  bin[i+2]='1';
					  bin[i+3]='1';
					break;
			case 'C': bin[i]='1';
					  bin[i+1]='1';
					  bin[i+2]='0';
					  bin[i+3]='0';
					break;
			case 'D': bin[i]='1';
					  bin[i+1]='1';
					  bin[i+2]='0';
					  bin[i+3]='1';
					break;
			case 'E': bin[i]='1';
					  bin[i+1]='1';
					  bin[i+2]='1';
					  bin[i+3]='0';
					break;
			case 'F': bin[i]='1';
					  bin[i+1]='1';
					  bin[i+2]='1';
					  bin[i+3]='1';
					break;
			case 'a': bin[i]='1';
					  bin[i+1]='0';
					  bin[i+2]='1';
					  bin[i+3]='0';
					break;
			case 'b': bin[i]='1';
					  bin[i+1]='0';
					  bin[i+2]='1';
					  bin[i+3]='1';
					break;
			case 'c': bin[i]='1';
					  bin[i+1]='1';
					  bin[i+2]='0';
					  bin[i+3]='0';
					break;
			case 'd': bin[i]='1';
					  bin[i+1]='1';
					  bin[i+2]='0';
					  bin[i+3]='1';
					break;
			case 'e': bin[i]='1';
					  bin[i+1]='1';
					  bin[i+2]='1';
					  bin[i+3]='0';
					break;
			case 'f': bin[i]='1';
					  bin[i+1]='1';
					  bin[i+2]='1';
					  bin[i+3]='1';
					break;
			default: break;
		}
	}
	bin[64]='\0';
}
