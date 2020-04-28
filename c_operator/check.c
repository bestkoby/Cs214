#include<stdio.h>
#include<stdlib.h>

void clean(char *var) {
    int i = 0;
    while(var[i] != '\0') {
        var[i] = '\0';
        i++;
    }
}
int pair(char* m, char* n){
	int lengthm = 0;
        while(m[lengthm++]);
	int lengthn = 0;
        while(n[lengthn++]);
	if(lengthm == lengthn){
		int i;
		for(i = 0; i < lengthm -1; i++){
			if(m[i] != n[i]){
				return 0;
			}
		}
	}else{
		return 0;
	}
	return 1;
}

int isoperatorl(char* c){
        if(pair(c,"AND")|| pair(c,"OR") || pair(c,"NOT")){
                return 1;
        }else{
              	return 0;
        }
}
int isoperatora(char* c){
        if(pair(c,"-") || pair(c,"+") || pair(c,"*") || pair(c,"/")){
                return 1;
        }else{
              	return 0;
        }
}
int isoperantl(char* c){
        if(pair(c,"true")){
		 return 1;
        }
	int length = 0;
        while(c[length++]);
        if(c[0] == 'f' && c[1] == 'a' && c[2] == 'l' && c[3] == 's' && c[4] == 'e' && length == 7){
		return 1;
	}
	return 0; 
}
int isoperanta(char* c){
        if(pair(c,"0") || pair(c,"1") || pair(c,"2") || pair(c,"3")||pair(c,"4") ||
	 pair(c,"5") || pair(c,"6") || pair(c,"7") || pair(c,"8") || pair(c,"9")){
                return 1;
        }else{
              	return 0;
        }
}

int typecheck(char c[]){
	if(isoperatorl(c) ){
		return 1;
	}else if(isoperatora(c)){
		return 2;
	}else if(isoperantl(c)){
		return 3;
	}else if(isoperanta(c)){
		return 4;
	}else{
		return 5;
	}
}

int main(int argc, char** argv){
	int e = 0;
	int l = 0;
	int a = 0;
	

	//check if there are more than 2 arguments 
	if(argc > 2){
		printf("too many arguments");
		exit(0);
	}
	
	//find the length of argv[1] since strlen is not allowed. 
	int length = 0;
	while(argv[1][length++]);

	//
	if(length == 1){
		printf("Scan error in expression %d: incomplete expression ""\n", e);
	}
		

	int type = 0;
	int tokencourt = 0;
	char token2[] = "";
	int index = 0; 
	int i;
	int pp = 0;
	for(i = 0; i<length-1;i++){
		
		if(argv[1][i]== ';'){
			e = e+1;
			type = 0;
			tokencourt = 0; 
			clean(token2);
			index = 0;
			pp = 0;
			
			if((length - i) == 2){
                		printf("Scan error in expression %d: incomplete expression ""\n", e);
        		}
		}else{

		

        	if(argv[1][i] != ' ' && argv[1][i] != ';' ){
                token2[index] = argv[1][i];
					index++;
			
       		 }

			if(argv[1][i] == ' ' || argv[1][i] == ';' || i == (length-2))	{
							
				int mycase = typecheck(token2);
				if(mycase == 1){
					if(type==0){
						if(pair(token2,"NOT")){
							if(tokencourt <=3){
								l=l+1;
								tokencourt = tokencourt +1;
							}
						}else{
							printf("Error: Parse error in expression %d: unexpected operator %s\n", e, token2);
						}
					}else if(type == 1 || type ==2){
						printf("Error: Parse error in expression %d: unexpected operator %s\n", e, token2);	
					}else if(type == 3){
						 if(tokencourt <=3){
								 tokencourt = tokencourt +1;
								l=l+1;
							}
					}else if(type == 4){
						printf("Error: Parse error in expression %d: operand type mismatch\n", e);	
					}
				}
				if(mycase == 2){
					if(type==0){
						
						printf("Error: Parse error in expression %d: unexpected operator %s\n", e, token2);
						
					}else if(type == 1 || type ==2){
						printf("Error: Parse error in expression %d: unexpected operator %s\n", e, token2);	
					}else if(type == 4){
						 if(tokencourt <=3){
								a=a+1;
								tokencourt = tokencourt +1;    
							}
					}else if(type ==3){
						printf("Error: Parse error in expression %d: operand type mismatch\n", e);	
					}
				}
				if(mycase == 3){
					
					if(type == 4 || type ==3 ){
						printf("Error: Parse error in expression %d: unexpected operand %s\n", e, token2);	
					}else if(type == 2){
						printf("Error: Parse error in expression %d: type operator mismatch\n", e);	
					}else if(type == 1 || type == 0){
						tokencourt = tokencourt +1;   
					} 
				}
				if(mycase == 4){
				
					if(type == 3 || type ==4 ){
						printf("Error: Parse error in expression %d: unexpected operand %s\n", e, token2);	
					}else if(type == 1){
						printf("Error: Parse error in expression %d: operator type mismatch\n", e);	
					}else if(type == 2 || type == 0){
                                                tokencourt = tokencourt +1;    
                                        }

				}
				if(mycase == 5){
				
					if(type == 0){
						printf("Error: Parse error in expression %d: unknown identifier%s\n", e, token2); 
						mycase = 0;
					}else if(type == 1 || type == 2){
						printf("Error: Parse error in expression %d: unknown operand %s\n", e, token2);
					}else if(type == 3 || type == 4){
						printf("Error: Parse error in expression %d: unknown operator %s\n", e, token2);
					}
				
				}
			

			
			//reset
		      		if(tokencourt == 3 && argv[1][i+1] != ';' && pp == 0){
					pp = 1;
					printf("Error: Parse error in expression %d: expression was not ended \n", e);
				}else if(tokencourt < 3 && tokencourt>0 && (argv[1][i+1] == ';' || i == (length-2))){
					if(mycase == 1 || mycase == 2){
						printf("Error: Parse error in expression %d: missing operand \n", e);
					}else if(mycase == 3 || mycase == 4){
						printf("Error: Parse error in expression %d: missing operator \n", e);					}
				}
				type = mycase;
				clean(token2);
				index = 0;
			}
		}
 	   }

	printf("Found %d expressions; %d logical and %d arithmetic.\n", (e+1), l, a);
}
