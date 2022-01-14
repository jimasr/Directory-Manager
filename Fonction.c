#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "Structures.h"

#define nbcolonne 7

char * GetAdresse(PERSONNE * personne, unsigned char colonne){
	switch (colonne){
		case 0:
			return personne->prenom;
		case 1:
			return personne->nom;
		case 2:
			return personne->ville;
		case 3:
			return personne->codepostal;
		case 4:
			return personne->tel;
		case 5:
			return personne->email;
		case 6:
			return personne->profession;
		default:
			printf("La recuperation de cette adresse est impossible ! [colonne %d non renseigne dans la structure]\n",colonne);
			exit(EXIT_FAILURE);
	}
}

void SetAdresse(PERSONNE * personne, unsigned char colonne, char * adresse){
	switch (colonne){
		case 0:
			personne->prenom = adresse;
			break;
		case 1:
			personne->nom = adresse;
			break;
		case 2:
			personne->ville = adresse;
			break;
		case 3:
			personne->codepostal = adresse;
			break;
		case 4:
			personne->tel = adresse;
			break;
		case 5:
			personne->email = adresse;
			break;
		case 6:
			personne->profession = adresse;
			break;
		default:
			printf("L'assignation de cette adresse est impossible ! [colonne %d non renseigne dans la structure]\n",colonne);
			exit(EXIT_FAILURE);
	}
}

void GetColonne(unsigned char colonne){
	switch (colonne){
		case 0:
			printf("Prenom");
			break;
		case 1:
			printf("Nom");
			break;
		case 2:
			printf("Ville");
			break;
		case 3:
			printf("Code Postal");
			break;
		case 4:
			printf("Telephone");
			break;
		case 5:
			printf("Adresse Email");
			break;
		case 6:
			printf("Profession");
			break;
		default:
			printf("L'affichage du nom de la colonne est impossible ! [colonne %d non renseigne dans la structure]\n",colonne);
			exit(EXIT_FAILURE);
	}
}

void StdClear(){
	char cara = 0;
	while (cara != '\n' && cara != EOF)
		cara = getchar();
}

void Clear(){
	#if _WIN32 || _WIN64
		system("cls");
	#else
		system("clear");
	#endif
}

unsigned int Select(unsigned int debut,unsigned int fin){
	unsigned int reponse;
	do{
		printf(" > ");
		scanf("%d",&reponse);
		StdClear();
		if (reponse<debut || reponse>fin)
			printf("Veuillez rentrer un nombre correct  !\n");
	} while (reponse<debut || reponse>fin);
	return reponse;
}

void VerifStr(char * chaine){
	char buffer = 1;
	unsigned int i;
	
	while(chaine[i]!='\0'){
		if(chaine[i] == '\n'){
			chaine[i] = '\0';
			buffer = 0;
		}
		else if (chaine[i]==',')
			chaine[i]=' ';
		i++;
	}
	if(buffer == 1)
		StdClear();
}

void VerifPattern(char * chaine , unsigned char colonne ,unsigned int limite){
	unsigned char verif;
	unsigned int taille;
	unsigned int i;
	do{
		taille = strlen(chaine);
		verif = 1;
		if (taille!=0){	
			i = 0;
			if(colonne == 3 || colonne == 4){
				if(colonne == 3 && taille != 5){
					verif = 0;
					printf("\tNombre de caracteres invalide [ format : XXXXX ] > ");
				}

				if(colonne == 4 && taille != 14){
					verif = 0;
					printf("\tNombre de caracteres invalide [ format : XX.XX.XX.XX.XX ] > ");
				}

				while(i < taille && verif == 1){
					switch (colonne) {
						case 3:
							if (chaine[i]>'9' || chaine[i]<'0'){
								verif = 0;
								printf("\tRentrer uniquement des entiers [ XXXXX ] > ");
							}
							break;
						case 4:
							if((i+1)%3 == 0){
								if (chaine[i] != '.'){
									verif = 0;
									printf("\tFormat incorrect [ XX.XX.XX.XX.XX ] > ");
								}
							}
							else if (chaine[i]>'9' || chaine[i]<'0'){
								printf("\tRentrer uniquement des entiers [ XX.XX.XX.XX.XX ] > ");
								verif = 0;
							}
							break;
					}
					i++;
				}
			}else if (colonne == 5){
				i = 0;
				verif = 0;
				while(i < taille){
					if (chaine[i]=='@')
						verif++;
					i++;
				}
				if (verif == 0)
					printf("\tUn @ est necessaire dans un email > ");
				if (verif > 1){
					printf("\tUn email contient seulement un @ > ");
					verif = 0;
				}
			}

			if(verif==0){
				fgets(chaine,limite,stdin);
				VerifStr(chaine);
			}
		}

	}while(verif == 0);
}

void OuvertureCSV(REPERTOIRE * repertoire){

	char ligne[300];
	char chemin[100];

	char unsigned i,j = 0;
	char unsigned column = 0;

	clock_t debut;
	clock_t fin;
	unsigned long temps; 

	printf("Rentrez le nom de votre annuaire > ");
	fgets(chemin,sizeof(chemin),stdin);
	VerifStr(chemin);

	printf("\n Voulez-vous l'ouvrir en mode avance ? \n");
	printf("\t1. Non\t");
	printf("\t2. Oui\n");

	repertoire->avance=Select(1,2)-1;

	repertoire->chemin = strdup(chemin);
	
	debut = clock();

	FILE *annuaire = fopen(chemin, "r+");
	if (annuaire == NULL){
		printf("Echec de l'ouverture du fichier\n");
		exit(EXIT_FAILURE);
	}

	repertoire->nblignes = 0;
	while (fgets(ligne, sizeof(ligne), annuaire) != NULL)
		repertoire->nblignes += 1;

	repertoire->informations = malloc(repertoire->nblignes * sizeof(PERSONNE));
	
	if (repertoire->informations == NULL){
		printf("Echec de l'allocation du tableau d'informations !\n");
		exit(EXIT_FAILURE);
	}

	repertoire->nballoc = repertoire->nblignes;

	rewind(annuaire);
	repertoire->nblignes = 0;
	
	while (fgets(ligne, sizeof(ligne), annuaire) != NULL){
		i=0;
		j=0;
		column = 0;

		while (ligne[i]!='\0')
		{
			if (ligne[i]=='\n' || ligne[i]==','){
				ligne[i]='\0';
				SetAdresse(&repertoire->informations[repertoire->nblignes],column,strdup(&ligne[j]));
				if (GetAdresse(&repertoire->informations[repertoire->nblignes],column) == NULL){
					printf("Echec de l'allocation d'une valeur !\n");
					exit(EXIT_FAILURE);
				}
				j=i+1;
				column++;
			}
			i++;
		}
		repertoire->nblignes++;
	}
	fclose(annuaire);

	fin = clock();
	temps = (fin-debut) * 1000 / CLOCKS_PER_SEC;

	Clear();

	if (repertoire->avance==1)
		printf("\nOuverture du Fichier - [ Succes | %ld ms]\n",temps);
}

void InitSort(REPERTOIRE * repertoire){

	repertoire->indices = malloc(sizeof(int *)*nbcolonne);
	if(repertoire->indices == NULL){
		printf("Echec de l'allocation ! [indices]\n");
		exit(EXIT_FAILURE);
	}

	for (unsigned char column = 0; column < nbcolonne; column++){
		repertoire->indices[column] = malloc(sizeof(int *)*repertoire->nblignes);
		for (unsigned int row = 0; row < repertoire->nblignes; row++){
			repertoire->indices[column][row] = row;
		}
	}
}

void InsertSort(REPERTOIRE * repertoire){
	int i,j;
	int petit;

	clock_t debut;
	clock_t fin;
	unsigned long temps; 

	if(repertoire->nblignes > 0){

		if(repertoire->avance == 1)
			printf("Replacement par tri insertion indirecte sur %d colonnes :\n",nbcolonne);

		for (unsigned char column = 0; column < nbcolonne; column++){
			i=1;
			debut = clock();
			while (i<repertoire->nblignes){
				petit = repertoire->indices[column][i];
				j=i-1;
				
				while (j>=0 && strcasecmp(GetAdresse(&repertoire->informations[petit],column),
										GetAdresse(&repertoire->informations[repertoire->indices[column][j]],column))<0){
					repertoire->indices[column][j+1] = repertoire->indices[column][j];
					j--;
				}
				repertoire->indices[column][j+1] = petit;
				i++;
			}
			if(repertoire->avance == 1){
				fin = clock();
				temps = (fin-debut) * 1000 / CLOCKS_PER_SEC;
				printf("\tTri colonne %d : %ld ms\n",column+1,temps);
			}
		}
	}
	else		
		if(repertoire->avance == 1)
			printf("L'annuaire ne peut pas etre trie car il est vide\n");
}

void ShellSort(REPERTOIRE * repertoire){
	unsigned int i,j;
	unsigned int interval;
	int petit;

	clock_t debut;
	clock_t fin;
	unsigned long temps; 

	if(repertoire->nblignes > 0){
	
		if(repertoire->avance == 1)
			printf("\n- Tri shell indirect sur %d colonnes :\n",nbcolonne);

		for (unsigned char column = 0; column < nbcolonne; column++){
			debut = clock();
			interval = repertoire->nblignes / 2;
			while (interval>0)
			{	
				i=interval;
				while (i<repertoire->nblignes){
					petit = repertoire->indices[column][i];
					j=i;
					
					while (j>=interval && strcasecmp( GetAdresse(&repertoire->informations[repertoire->indices[column][j-interval]],column),
													GetAdresse(&repertoire->informations[petit],column)) > 0){

						repertoire->indices[column][j]=repertoire->indices[column][j-interval];
						j=j-interval;
					}
					repertoire->indices[column][j]=petit;
					
					i++; 
				}
				interval = interval/2;
			}
			if(repertoire->avance == 1){
				fin = clock();
				temps = (fin-debut) * 1000 / CLOCKS_PER_SEC;
				printf("\tTri colonne %d : %ld ms\n",column+1,temps);
			}
		}
		if(repertoire->avance == 1)
			printf("\n");
	}
	else		
		if(repertoire->avance == 1)
			printf("L'annuaire ne peut pas etre trie car il est vide\n");

}

int VerifTri(REPERTOIRE * repertoire){
	for (unsigned char i = 0; i < nbcolonne; i++)
		for (unsigned int j = 1; j < repertoire->nblignes; j++)
			if (strcasecmp( GetAdresse(&repertoire->informations[repertoire->indices[i][j-1]],i),
						    GetAdresse(&repertoire->informations[repertoire->indices[i][j]],i)) > 0)
				return 0;
	return 1;
}

void MemoryCls(REPERTOIRE * repertoire){
	for (unsigned int colonne = 0; colonne < nbcolonne; colonne++)	{
		for (unsigned int ligne = 0; ligne < repertoire->nblignes; ligne++){
			free(GetAdresse(&repertoire->informations[ligne],colonne));	
		}
		free(repertoire->indices[colonne]);	
	}
	free(repertoire->informations);
	free(repertoire->indices);
	free(repertoire->chemin);
	if(repertoire->avance==1)
		printf("\nNettoyage de la memoire - [ Succes ]\n");
}

void Empty(char * chaine, unsigned char formatage){

	unsigned char taille = strlen(chaine);
	
	if (strlen(chaine) > 0)
		printf("%s", chaine);
	else{
		printf("N/A");
		taille = 3;
	}
	while (taille<formatage){
		printf(" ");
		taille++;
	}

}

void Affichage(REPERTOIRE * repertoire, unsigned int index, unsigned char mode){

	/* 
	Mode : 0 = Affichage compact
	Mode : 1 = Affichage complet
	*/

	if(repertoire->avance == 0){
	
		if(mode == 0){

			printf("Personne %4d : ", index+1);
			Empty(repertoire->informations[index].nom,25);
			printf(" | ");
			Empty(repertoire->informations[index].prenom,20);
			printf(" | ");
			Empty(repertoire->informations[index].profession,20);
			printf(" | ");
			Empty(repertoire->informations[index].tel,14);
			printf(" | ");
			Empty(repertoire->informations[index].email,45);
			printf(" | ");
			Empty(repertoire->informations[index].ville,25);
			printf(" [ ");
			Empty(repertoire->informations[index].codepostal,5);
			printf(" ] ");

		}else{

			printf("\nInformations sur la personne %d :\n\n", index+1);

			printf("Nom : ");
			Empty(repertoire->informations[index].nom,0);
			printf("\tPrenom : ");
			Empty(repertoire->informations[index].prenom,0);

			printf("\n\nLieu de residence : ");
			Empty(repertoire->informations[index].ville,0);
			printf(" [ ");
			Empty(repertoire->informations[index].codepostal,0);
			printf(" ]");

			printf("\nProfession : ");
			Empty(repertoire->informations[index].profession,0);

			printf("\n\nContact :\n");

			printf("\t- Telephone : ");
			Empty(repertoire->informations[index].tel,0);

			printf("\n\t- Email: ");
			Empty(repertoire->informations[index].email,0);
		}

		printf("\n");
	}
	
}

void Suppression(REPERTOIRE * repertoire, unsigned int index){
	if (repertoire->nblignes>0){

		repertoire->nblignes -= 1;
		repertoire->informations[index] = repertoire->informations[repertoire->nblignes];

		printf("\tPersonne correctement supprimee\n");

		// Pas du tout optimise mais pas encore d'alternative
		ShellSort(repertoire);
	}else
		printf("Aucune personne renseigne\n");
	
} 

void ModifVal(PERSONNE * personne, unsigned char colonne){
	char buffer[100];

	printf("\nModification [");
	GetColonne(colonne);
	printf("] : ");

	fgets(buffer,sizeof(buffer),stdin);
	VerifStr(buffer);
	VerifPattern(buffer, colonne,sizeof(buffer));

	SetAdresse(personne,colonne,realloc(GetAdresse(personne,colonne),sizeof(char)*(strlen(buffer)+1)));
	if(GetAdresse(personne,colonne) == NULL){
		printf("Echec de la reallocation d'une donnee de la personne!\n");
		exit(EXIT_FAILURE);
	}
	strcpy(GetAdresse(personne,colonne),buffer);
}

void Modification(REPERTOIRE * repertoire, unsigned int index){
	if (repertoire->nblignes>0)
	{
		printf("\nQuel colonne voulez-vous modifier :\n");
		for (unsigned char i = 0; i < nbcolonne; i++){
			printf("\t%d. ",i+1);
			GetColonne(i);
			printf("\n");
		}
		ModifVal(&repertoire->informations[index],Select(1,nbcolonne)-1);
		Clear();
		Affichage(repertoire,index,1);
		printf("\n");
		InsertSort(repertoire);
	}else
		printf("Aucune personne renseignee\n");
	
}

void Ajout(REPERTOIRE * repertoire){
	
	char buffer[100];

	if (repertoire->nblignes == repertoire->nballoc){
		repertoire->informations = realloc(repertoire->informations, (repertoire->nblignes + 1 ) * sizeof(PERSONNE));
		if (repertoire->informations == NULL){
			printf("Echec de la reallocation d'une nouvelle personne !\n");
			exit(EXIT_FAILURE);
		}

		repertoire->nballoc+=1;

		for (int i = 0; i < nbcolonne; i++){
			repertoire->indices[i] = realloc(repertoire->indices[i],(repertoire->nblignes + 1 ) * sizeof(int *));
			if (repertoire->indices[i] == NULL){
				printf("Echec de la reallocation du tableau d'indices !\n");
				exit(EXIT_FAILURE);
			}
			repertoire->indices[i][repertoire->nblignes]=repertoire->nblignes;
		}
	}

	Clear();

	printf("\n - Creation d'une nouvelle personne -\n\n");

	for (unsigned char i = 0; i < nbcolonne; i++){
		GetColonne(i);
		printf(" : ");
		fgets(buffer,sizeof(buffer),stdin);
		VerifStr(buffer);
		VerifPattern(buffer,i,sizeof(buffer));

		SetAdresse(&repertoire->informations[repertoire->nblignes],i,strdup(buffer));
		if(GetAdresse(&repertoire->informations[repertoire->nblignes],i) == NULL){
			printf("Echec de l'allocation  d'une donnee de la personne !\n");
			exit(EXIT_FAILURE);
		}

	}
	printf("\n");
	Affichage(repertoire,repertoire->nblignes,0);
	repertoire->nblignes+=1;
	InsertSort(repertoire);

}

void Sauvegarde(REPERTOIRE * repertoire){
	char buffer[100];
	unsigned char colonne;
	unsigned int ligne;

	printf("Veuillez rentrer le nom du fichier de sauvegarde : ");
	fgets(buffer,sizeof(buffer),stdin);
	VerifStr(buffer);

	FILE * sauvegarde = fopen(buffer, "w");
	if (sauvegarde == NULL){
		printf("Echec de le l'ouverture du fichier de sauvegarde !\n");
		exit(EXIT_FAILURE);
	}
	
	for (ligne = 0; ligne < repertoire->nblignes; ligne++){
		for (colonne = 0; colonne < nbcolonne-1; colonne++){
			if (fprintf(sauvegarde,"%s,",GetAdresse(&repertoire->informations[ligne],colonne)) == 0){
				printf("Echec de l'ecriture dans le fichier de sauvegarde ! [Valeur intermediaire]\n");
				exit(EXIT_FAILURE);
			}
		}
		if(fprintf(sauvegarde,"%s\n",GetAdresse(&repertoire->informations[ligne],colonne)) == 0){
			printf("Echec de l'ecriture dans le fichier de sauvegarde ! [Valeur finale]\n");
			exit(EXIT_FAILURE);
		}
	}
	fclose(sauvegarde);
	printf("\t- Ficher correctement sauvegarde sous le nom de '%s'\n",buffer);
}

unsigned char MissingData(REPERTOIRE * repertoire){

	unsigned int compteur = 0;
	clock_t debut;
	clock_t fin;
	unsigned long temps; 

	debut = clock();

	for (unsigned int ligne = 0; ligne< repertoire->nblignes; ligne++){
		for (unsigned char colonne = 0;colonne<nbcolonne;colonne++){
			if (strlen(GetAdresse(&repertoire->informations[ligne],colonne))==0){
				Affichage(repertoire,ligne,0);
				compteur++;
				break;
			}
		}	
	}

	fin = clock();
	temps = (fin-debut) * 1000 / CLOCKS_PER_SEC;

	printf("\n Temps de recherche [ Elements Manquants ] : %ld ms\n",temps);

	if (compteur>0){
		printf("\n\t - %d personnes avec des donnees manquantes trouvees ",compteur);
		if (repertoire->nblignes>0)
			printf(" [%d %% de l'annuaire] -", compteur * 100 / repertoire->nblignes);
		printf("\n\n");
		return 1;
	}
	printf("\n\t - Aucune correspondances trouvees -\n\n");
	return 0;
}

void Statistiques(REPERTOIRE * repertoire){
	printf("\nNom du fichier utilise : %s \n",repertoire->chemin);
	printf("\t- Nombre de personnes renseignees : %d personnes\n",repertoire->nblignes);
	printf("\t- Nombre de personnes alloues     : %d cases\n",repertoire->nballoc);
	printf("\t- Verification du tri indirect    : ");
	if(VerifTri(repertoire)==1) 
		printf("[ Succes ]\n");
	else 
		printf("[ Echec ]\n");
	printf("\t- Mode Avance                     : ");
	if(repertoire->avance==1) 
		printf("[ Active ]\n");
	else 
		printf("[ Desactive ]\n");
}

unsigned int DicoSearchLimit(REPERTOIRE * repertoire,unsigned char colonne, char * filtre , unsigned char limite ){

	unsigned int milieu;
	unsigned int ide = 0;
	unsigned int ifi = repertoire->nblignes-1;

	while (ide<=ifi){
		milieu = (ide+ifi)/2;

		if (strncasecmp(GetAdresse(&repertoire->informations[repertoire->indices[colonne][milieu]],colonne),filtre,limite) == 0){
			while(milieu>0 && strncasecmp(GetAdresse(&repertoire->informations[repertoire->indices[colonne][milieu-1]],colonne),filtre,limite) == 0)
				milieu--;
			return milieu;
		}
		if (strncasecmp(GetAdresse(&repertoire->informations[repertoire->indices[colonne][milieu]],colonne),filtre,limite)<0)
            ide = milieu+1;
        else
            ifi = milieu-1;
	}
	return repertoire->nblignes;
}

unsigned int DicoSearch(REPERTOIRE * repertoire,unsigned char colonne, char * filtre){

	unsigned int milieu;
	unsigned int ide = 0;
	unsigned int ifi = repertoire->nblignes-1;

	while (ide<=ifi){
		milieu = (ide+ifi)/2;

		if (strcasecmp(GetAdresse(&repertoire->informations[repertoire->indices[colonne][milieu]],colonne),filtre) == 0){
			while(milieu>0 && strcasecmp(GetAdresse(&repertoire->informations[repertoire->indices[colonne][milieu-1]],colonne),filtre) == 0)
				milieu--;
			return milieu;
		}
		if (strcasecmp(GetAdresse(&repertoire->informations[repertoire->indices[colonne][milieu]],colonne),filtre)<0)
            ide = milieu+1;
        else
            ifi = milieu-1;
	}
	return repertoire->nblignes;
}

char Lower(char cara){
	if (cara>='A' && cara <= 'Z')
		return cara+32;
	return cara;
}

unsigned char SubString(char * chaine, char * souschaine){
	unsigned char i = 0;
	unsigned char j = 0;
	unsigned char verif = 0;

	if(chaine[0]=='\0' && souschaine[0]=='\0') 
		return 1;
	else
	{
		j=0;
		while(chaine[j] != '\0')
		{
			while(chaine[j] !='\0' && Lower(chaine[j]) != Lower(souschaine[0])) 
				j++;

			if(Lower(chaine[j]) == Lower(souschaine[0]))
			{
				verif = 1;
				i=1;
				j++;
				while(verif == 1 && souschaine[i] != '\0')
				{
					if(Lower(souschaine[i]) != Lower(chaine[j]))
					 	verif = 0;
					i++;
					j++;
				}
				if(verif == 1)
					return 1;
			}
		}
	}
	return 0;
	 
}

unsigned char Filtre(REPERTOIRE * repertoire, unsigned char colonne){

	clock_t debut;
	clock_t fin;
	unsigned long temps; 

	char filtre[100];
	unsigned char taille;
	unsigned int indice;
	unsigned char type; 
	unsigned char present;
	unsigned int compteur = 0;

	do{
		printf("\nIndications :\n");
		printf("\tTous    :  [*] \t Commence par : [...*] \t Contient : [*...*]\n");
		printf("\tExact   : [...]\t Finit par    : [*...]\n\n");

		printf("Filtrage par ");
		GetColonne(colonne);
		printf(" : ");
		fgets(filtre,sizeof(filtre),stdin);
		VerifStr(filtre);
		printf("\n");

		taille = strlen(filtre);

		if (taille == 0){
			Clear();
			printf("Veuillez rentrer un filtre correct !\n");
		}
	}while (taille==0);

	/*
		Type 0 [*]     : [ Non Compatiable recherche optimisée ] : Affiche tous les lignes
		Type 1 [...]   : [   Compatiable recherche optimisée   ] : Affiche les personnes avec des informations qui correspondent au filtre
		Type 2 [*...]  : [ Non Compatiable recherche optimisée ] : Affiche les personnes avec des informations qui commencent par le filtre
		Type 3 [...*]  : [   Compatiable recherche optimisée   ] : Affiche les personnes avec des informations qui finissent par le filtre
		Type 4 [*...*] : [ Non Compatiable recherche optimisée ] : Affiche les personnes avec des informations qui contiennent le filtre
	*/

	type = 1;
	if (taille == 1 && filtre[0] == '*')
		type = 0;
	else if (taille > 1) {
		if (filtre[0] == '*'){
			type = 2;
			if (filtre[taille-1] == '*'){
				type = 4;
				filtre[taille-1] = '\0';
				taille-=1;
			}
			taille-=1;
		}else if (filtre[taille-1] == '*'){
			type = 3;
			filtre[taille-1] = '\0';
			taille -=1;
		}
	}

	debut = clock();
			
	if (type == 1){
		indice = DicoSearch(repertoire,colonne,filtre);
		if (indice!=repertoire->nblignes)
			while (indice<repertoire->nblignes && strcasecmp(GetAdresse(&repertoire->informations[repertoire->indices[colonne][indice]],colonne),filtre) == 0){
				Affichage(repertoire,repertoire->indices[colonne][indice],0);
				compteur += 1;
				indice += 1;
			}
	}
	else if (type == 3){
		indice = DicoSearchLimit(repertoire,colonne,filtre,taille);
		if (indice!=repertoire->nblignes)
			while (indice<repertoire->nblignes && strncasecmp(GetAdresse(&repertoire->informations[repertoire->indices[colonne][indice]],colonne),filtre,taille) == 0){
				Affichage(repertoire,repertoire->indices[colonne][indice],0);
				compteur += 1;
				indice += 1;
			}

	}else{
		for (unsigned int ligne = 0; ligne < repertoire->nblignes; ligne++){
			present = 0;
			switch (type)
			{
				case 0:
					present = 1;
					break;
				case 2:
					if (strcasecmp(&filtre[1], &GetAdresse(&repertoire->informations[repertoire->indices[colonne][ligne]],colonne)
											[strlen(GetAdresse(&repertoire->informations[repertoire->indices[colonne][ligne]],colonne)) - taille]) ==0)
						present = 1;
					break;
				case 4:
					if(SubString(GetAdresse(&repertoire->informations[repertoire->indices[colonne][ligne]],colonne),&filtre[1])==1)
						present = 1;
					break;
				default:
					printf("Erreur de type de filtre\n");
			}
			if (present == 1){
				Affichage(repertoire,repertoire->indices[colonne][ligne],0);
				compteur += 1;
			}
		}
	}

	fin = clock();
	temps = (fin-debut) * 1000 / CLOCKS_PER_SEC;

	printf("\n Temps de recherche [filtre] : %ld ms\n",temps);

	if (compteur>0){
		printf("\n\t - %d correspondances trouvees -\n\n",compteur);
		return 1;
	}
	printf("\n\n\t - Aucune correspondances trouvees -\n\n");
	return 0;
}

unsigned char Recherche(REPERTOIRE * repertoire){
	unsigned int i;
	unsigned int colonne;
	int reponse;

	clock_t debut;
	clock_t fin;
	unsigned long temps; 

	char prenom[100];
	char nom[100];
	char autres[100];

	printf("Methode de recherche :\n");
	printf("\t1. Prenom | Nom | Telephone\n");
	printf("\t2. Prenom | Nom | Email\n");
	printf("\t3. Quitter\n");

	reponse = Select(1,3);

	if (reponse != 3){
		printf("\nPrenom : ");
		fgets(prenom,sizeof(prenom),stdin);
		VerifStr(prenom);

		printf("Nom : ");
		fgets(nom,sizeof(nom),stdin);
		VerifStr(nom);
		
		if(reponse == 1) colonne = 4;
		else colonne = 5;

		GetColonne(colonne);
		printf(" : ");
		fgets(autres,sizeof(autres),stdin);
		VerifStr(autres);

		debut = clock();

		i=DicoSearch(repertoire,colonne,autres);
		if (i != repertoire->nblignes){ 
			while (i<repertoire->nblignes && strcasecmp(GetAdresse(&repertoire->informations[repertoire->indices[colonne][i]],colonne),autres) == 0){
				if (strcasecmp(GetAdresse(&repertoire->informations[repertoire->indices[colonne][i]],1),nom)==0){
					if (strcasecmp(GetAdresse(&repertoire->informations[repertoire->indices[colonne][i]],0),prenom)==0){
						Affichage(repertoire,repertoire->indices[colonne][i],1);
						fin = clock();
						temps = (fin-debut) * 1000 / CLOCKS_PER_SEC;
						printf("\n Temps de recherche [filtre] : %ld ms\n",temps);
						return 1;
					}
				}
				i++;
			}
		}
		fin = clock();	
		temps = (fin-debut) * 1000 / CLOCKS_PER_SEC;
		printf("\n Temps de recherche [filtre] : %ld ms\n",temps);
		printf("Aucune correspondance trouvee !\n");
	}
	return 0;
}

void Pause(){
	printf("\n");
	#if __APPLE__
		system("echo - Appuyez sur une touche -");
		system("read touche");
	#elif _WIN32 || _WIN64
		system("Pause. >nul | echo  - Appuyez sur une touche -");
	#elif unix
		system('read -n1 -r -p " - Appuyez sur un touche " - ');
	#endif
}