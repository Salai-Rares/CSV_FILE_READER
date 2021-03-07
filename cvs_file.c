#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_LEN 1500
#define MAX_RECORDS 2500
#define MAX_NAME 300
FILE *fp = NULL;
int releaseYear;

typedef struct music{
	char song[MAX_NAME];
	char artist[MAX_NAME];
	int releaseYear;
	}MUSIC;

MUSIC records[MAX_RECORDS];
int contor=0;

char *strremove(char *str, const char *sub){
	//strstr returneaza un pointer spre prima aparite a lui sub in str
	//memmove muta la adresa lui p primii strlen(p+len)+1 bytes incepand cu adresa lui p+len 
	size_t len = strlen(sub);
	if (len > 0){
		char *p =str;
		while ((p = strstr(p, sub)) != NULL){
			memmove(p, p+len, strlen(p+len)+1);
		}
	}
	return str;
}


void print_array_of_MUSIC(MUSIC* arr,int len){
	int i;
	//afisam toate records-urile din tablou ce au acelasi an cu cel pe care il dam de la tastatura ca argument
	for(i=0;i<len;i++){
	if(releaseYear==arr[i].releaseYear)
	printf("%s | %s | %d\n",arr[i].song,arr[i].artist,arr[i].releaseYear);
	}
}

void readFile(){
	char buff[LINE_LEN];
	
	while(fgets(buff, LINE_LEN, fp)){

		MUSIC record;
		if(buff[0] == '\"'){
		//tratam cazul in care numele melodiei incepe cu " si are virugle inanutru
			//++buff; // creste adresa cu 1 ~ buff[1]
			// * valoarea adresei
			char aux[LINE_LEN];
			int i = 1;


			do{

				aux[i-1] = buff[i]; //dereferentiere, adica iau valoarea de la adresa buff 
						    //si o bag la val din adr lui aux
				i++;

			}
			while(*(buff+i) != '\"');
			//pozitionam terminatorul de sir de caracter
			aux[i-1] = '\0';
			//verficam daca numele melodiei nu este mai mare decat maximul nostru definit in structura
			if(strlen(aux)>MAX_NAME){
			perror("This song name is too large for our structure");
			exit(1);
			}
			//copiem in campul song numele melodiei
			strcpy(record.song,aux);
			//printf("%s\n",aux);
			//shiftam la stanga ca sa nu mai avem numele melodiei 
			char *buff2 = strremove(buff, aux);
			//luam cu functia strtok in primul apel o sa avem in tok = "" deoarece nu am sters si ghilemele cu functia de mai sus
			char * tok = strtok(buff2,",");
			//doar dupa al doilea apel , cel cu NULL avem numele artistului
			tok=strtok(NULL,",");
			//verificam sa nu avem numele artistului prea mare
			if(strlen(tok)>MAX_NAME){
			perror("This artist name is too large for our structure");
			exit(2);
			}
			//copiem numele artistului in structura 
			strcpy(record.artist,tok);
			//acum la urmatorul strtok o sa avem in tok anul pe care il transformaam in int cu atoi
			tok=strtok(NULL,",");
			record.releaseYear=atoi(tok);
			//introducem record-ul in tabloul de records si incrementam contorul
			records[contor++]=record;


		}
		else {
			//cazul genereal cand nu avem virgule in numele melodiei
			//primul strotk ne da numele melodiei
			char *tok = strtok(buff, ",");
			if(strlen(tok)>MAX_NAME){
			perror("This song name is too large for our structure");
			exit(1);
			}
			//copiem numele in campul structurii
			strcpy(record.song, tok);
			//al doilea strtok ne da numele artistului
			tok = strtok(NULL, ",");
			if(strlen(tok)>MAX_NAME){
			perror("This artist name is too large for our structure");
			exit(2);
			}
			//il copiem
			strcpy(record.artist, tok);
			//aici avem anul
			tok = strtok(NULL, ",");
			record.releaseYear = atoi(tok);
			//introducem record-ul in tabloul de records si incrementam contorul
			records[contor++]=record;
		}
		


		//aux[1]=hxhbx 
		//*(aux+1) == hxhbx
	}

	
}



int main(int argc, char **argv){
	if(argc != 3){
		printf("the number of arguments is wrong!!!");
		exit(-1);
	}

	if ((fp  = fopen(argv[1], "r")) == NULL){
		perror(argv[1]);
		exit(-1);
	}
	//releaseYear este global si avem in el anul dat ca argument argv[2]
	releaseYear = atoi(argv[2]);
	//apelam functia readFile
	readFile();
	//records este o variabila globala asa ca o putem apela functia print cu ea aici in main si contorul la fel o variabila globala, in contor avem numarul de records din tablou
	print_array_of_MUSIC(records,contor);

	/*MUSIC test;
	strcpy(test.song , "a");
	strcpy(test.artist , "rares");
	test.releaseYear = 345;
	printf("%s, %s, %d\n", test.song, test.artist, test.releaseYear); */


	
	

	return 0;
}
