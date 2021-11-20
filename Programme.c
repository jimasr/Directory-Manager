#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//-----Declaration de la structures des informations-----//

typedef struct StructureCSV{
	char nom[35], prenom[35];
	char ville[35], codepostal[6];
	char tel[16], email[35];
	char profession[35];
}Personne;

//--------Declaration des Prototypes de fonctions-------//

void Pause();
void Clear();
void OuvertureCSV(Personne (*personne)[],int * nbrow);
void Affichage(Personne *personne, int index);
void Suppression(Personne (*personne)[], int index, int * nbrow);
void Choix(Personne (*personne)[], int index, int * nbrow);
void Empty(char chaine[]);
void Modification(Personne *personne);
void OriganisationCSV(Personne *personne,int colonne,char cara, int pos);
int Selection(Personne (*personne)[],int * nbrow);
void Sauvegarde(Personne (*personne)[],int nbrow);
void Filtre(Personne (*personne)[], int nbrow, int choix);

	//--------Fonction main--------//
	int main()
{

	//Création d'un tableau contenant toutes les informations de toutes les personnes
	Personne information[10000];
	//Création du pointeur vers le tableau de structure
	Personne (*pt_info)[] = &information;

	int nbrow = 0;
	//Création du pointeur vers le nombre de ligne
	int *pt_row = &nbrow;

	//Entées utilisateur
	int reponse;

	//Booléen qui fait boucler le programme
	char programme = 1;

	OuvertureCSV(pt_info, pt_row);

	//------------Affichage Titre------------//

	printf("\n\t\t--- Version 1 - Ouverture et Recherche dans un CSV ---\n\n");
	
	//Boucle le programme tant que l'utilisateur veux
	while (programme == 1)
	{
		//------------Affichage Menu-------------//

		//------------Menu principal-------------//
		printf(" - Que voulez-vous faire ?\n");
		printf("\t1. Rechercher une personne\n");
		printf("\t2. Ajouter une personne\n");
		printf("\t3. Trier l'annuaire\n");
		printf("\t4. Sauvegarder\n");
		printf("\t5. Quitter\n");
		printf(" > ");
		scanf("%d",&reponse);
		fflush(stdin);

		//------Switch de fonctionnalité------//
		switch (reponse)
		{
		case 1:	
			//--------Sous menu de recherche----------//
			printf("\n\t----------------\n\n");

			printf("\t1. Rechercher par index\n");
			printf("\t2. Par Prenom\n");
			printf("\t3. Par Nom\n");
			printf("\t4. Par Ville\n");
			printf("\t5. Par code postal\n");
			printf("\t6. Par telephone\n");
			printf("\t7. Par email\n");
			printf("\t8. Retour\n");
			printf(" > ");
			scanf("%d",&reponse);
			fflush(stdin);

			//---------Switch de recherche--------//
			switch(reponse){

				//Recherche par index
				case 1:
					do{
						printf("\nRentrez l'index de la personne dont vous voulez les informations (0 pour quitter) : ");
						reponse = Selection(pt_info,pt_row);
						if (reponse != 0){
							printf("\n\t-- Recherche en cours --\n\n");
							Affichage(&information[reponse-1],reponse);
							Choix(pt_info,reponse-1, pt_row);
							printf("\n");
							Pause();
							Clear();
						}
					}while(reponse != 0);
					break;
				case 2: case 3: case 4: case 5: case 6: case 7:
					Clear();
					Filtre(pt_info, nbrow, reponse-1);
					break;
				//Retour
				case 8:break;

				//Gestion d'erreur saisie
				default:
					printf("\n Une erreur s'est produite\n\n");

			}
			printf("\n > Retour au menu principal\n\n");
			Pause();
			Clear();

			break;
		case 4:
			printf("\n- Voulez-vous sauvegarder toutes les modifications? (0 pour quitter et 1 pour sauvegarder)\n");
			printf(" > ");
			do
			{
				scanf("%d", &reponse);
				if(reponse==1)
				{
					Sauvegarde(pt_info, nbrow);
					printf("\nSauvegarde reussite!");
				}
				else
				{
					printf("\nUne erreur s'est produite");
				}

			}while(reponse!=0 && reponse!=1);
			printf("\n > Retour au menu principal\n\n");
			Pause();
			Clear();
			break;
		//-------------Quitter------------//
		case 5:
			//Fin de la boucle programme
			printf("\n - A bientot !\n\n");
			programme = 0;
			break;
			
		//-----Gestion d'erreur saisie----//
		default:	
			Clear();
			printf("\nUne erreur s'est produite, veuillez rentrer un numero correct !\n\n");
		}

	}
	//------La requete pour sauvegarder les modifications--//


	//Arrêt du programme
	return 0;
}

//------Detecte le systeme d'exploitation et adapte le commande systeme() en fonction de system------//

void Clear()
{
	#if __APPLE__ && __LINUX__
		system("clear");
	#elif _WIN32 && _WIN64
		system("cls");
	#endif

}

void Pause(){
    #if __APPLE__
        system("echo - Appuyez sur une touche -");
        system("read touche");
	#elif _WIN32
        system("Pause. >nul | echo  - Appuyez sur une touche -");
	#elif _WIN64
        system("Pause. >nul | echo  - Appuyez sur une touche -");
	#elif __LINUX__
        system('read -n1 -r -p " - Appuyez sur un touche " - ');
	#endif
}

//----------Fonction d'affichage d'une personne----------//
void Affichage(Personne *personne, int index){

	//--Affichage des informations d'une personne--//
	printf("Information sur la personne %d :\n\n", index);

	printf("Nom : ");
	Empty((*personne).nom);
	printf("\tPrenom : ");
	Empty((*personne).prenom);

	printf("\n\nLieu de residence : ");
	Empty((*personne).ville);
	printf(" [ ");
	Empty((*personne).codepostal);
	printf(" ]");

	printf("\nProfession : ");
	Empty((*personne).profession);

	printf("\n\nContact :\n");

	printf("\t- Telephone : ");
	Empty((*personne).tel);

	printf("\n\t- Email: ");
	Empty((*personne).email);

	printf("\n");

}

//---Fonction qui affiche N/A quand pas d'information----//
void Empty(char chaine[]){
	if (strlen(chaine)>0)
		printf("%s",chaine);
	else
		printf("N/A");
}

//---------Fonction qui ouvre et assigne le CSV----------//
void OuvertureCSV(Personne (*personne)[],int * nbrow){
	//---------Declaration des variable---------//

	char ligne[200];

	char unsigned i,j;

	char column = 0;
	*nbrow = 0;

	//-----------Ouverture du CSV-----------//

	FILE *annuaire = fopen("Annuaire.csv","r");

	//------Gestion d'échec d'ouverture-------//
	if(annuaire == NULL){
		printf("Echec de l'ouverture du fichier");
		exit(EXIT_FAILURE);
	}

	//-------------Lecture du CSV-------------//

	//Recommence tant que la ligne du fichier n'est pas vide
	while(fgets(ligne,sizeof(ligne),annuaire) != NULL){
		j=0;
		column=0;

		//Parcours la ligne lettre par lettre
		for(i=0;ligne[i]!='\0';i++){
			//Considère une nouvelle colonne à chaque ',' et exclu le retour chariot
			if(ligne[i]==',' || ligne[i]=='\n'){
				//Assigne le caractère null a la fin de chaque valeurs
				OriganisationCSV(&(*personne)[*nbrow],column,'\0',j);
				j = 0;
				column++;
			}else{
				//Assigne le caractère actuel à sa colonne
				OriganisationCSV(&(*personne)[*nbrow],column,ligne[i],j);
				j++;
			}
		}
		*nbrow+=1;
	}
	
	//------------Fermeture du CSV------------//

	fclose(annuaire);

}

//-----Assigne un caractère a sa colonne dans le CSV-----//
void OriganisationCSV(Personne *personne,int colonne,char cara, int pos){
	switch(colonne){
		case 0:
			(*personne).prenom[pos] = cara;     break;
		case 1:
			(*personne).nom[pos] = cara;        break;
		case 2:
			(*personne).ville[pos] = cara;      break;
		case 3:
			(*personne).codepostal[pos] = cara; break;
		case 4:
			(*personne).tel[pos] = cara;        break;
		case 5:
			(*personne).email[pos] = cara;      break;
		case 6:
			(*personne).profession[pos] = cara; break;
	}
}

//----Vérifie l'appartenance d'un index à l'annuaire-----//
int Selection(Personne (*personne)[],int * nbrow){
	int index = 0;
	do{
		printf(" > ");
		scanf("%d",&index);
		fflush(stdin);
		if (index < 0)
			printf("\tUne erreur s'est produite, veuillez rentrer un nombre correct.\n");
		else if (index>*nbrow){
			printf("\tAttention, la valeur %d est trop eleve, [%d personnes renseignees]\n",index,*nbrow);
		}
		
	}while(index < 0 || index>*nbrow);

	//Retourne un nombre entre 0 et le nombre de ligne
	return index;
}

//--Fonction permettant le choix - modifier ou supprimer--//
void Choix(Personne (*personne)[], int index, int * nbrow){
	int reponse;
	do{
		//Menu choix suppression ou modification
		printf("\n- Que voulez-vous faire ?\n");
		printf("\t1. Supprimer cette personne\n");
		printf("\t2. Modifier cette personnes\n");
		printf("\t3. Retour\n");
		printf(" > ");
		scanf("%d",&reponse);
		fflush(stdin);

		//Menu des choix
		switch(reponse){
			case 1 :
				Suppression(personne,index,nbrow);
				break;
			case 2:
				Modification(&(*personne)[index]);
				break;
			case 3:
				break;

			default:
				printf("\nUne erreur c'est produite veuillez rentrer un numero correct\n");
				break;
		}
	}while(reponse <1 || reponse>3);
}

//-------Fonction de modification d'une personne---------//
void Modification(Personne *personne){
	int reponse;
	int i = 0;
	int taille;
	char modif;
	do{
		// Menu de choix de modifications
		printf("\n- Que voulez-vous Modifier ?\n");
		printf("\t1. Son prenom\n");
		printf("\t2. Son nom\n");
		printf("\t3. Sa ville\n");
		printf("\t4. Son code postal\n");
		printf("\t5. Son numero de telephone\n");
		printf("\t6. Son adresse mail\n");
		printf("\t7. Sa profession\n");
		printf("\t8. Retour\n");
		printf(" > ");
		scanf("%d",&reponse);
		fflush(stdin);

		if (reponse<1 || reponse>8)
			printf("Une erreur c'est produite, veuillez rentrez un nombre correct !");
			
	}while(reponse<1 || reponse>8);

	//Si l'utilisateur ne veux pas quitter
	if (reponse!=8){
		//Utilise la taille de la variable nom, comme taille max
		taille = sizeof((*personne).nom);

		//Adapte la taille max a la taille de la variable codepostal
		if (reponse==4)
			taille = sizeof((*personne).codepostal);

		//Adapte la taille max a la taille de la variable telephone
		else if (reponse == 5)
			taille = sizeof((*personne).tel);

		printf("\nRentrez la nouvelle valeur : ");

		//Boucle tante qu'il n'y a pas de retour chariot et que i est inférieur a la taille max
		while(modif!='\n' && i<taille-1 ){
			scanf("%c",&modif);
			if (modif!='\n'){
				OriganisationCSV(personne,reponse-1,modif,i);
				i++;
			}
		}
		fflush(stdin);
		//Assigne le caractère null a la fin de la valeur
		OriganisationCSV(personne,reponse-1,'\0',i);
		printf("\nCette valeur a correctement ete assigne\n");
	}

}

//--------Fonction de suppression d'une personne---------//
void Suppression(Personne (*personne)[], int index, int * nbrow){
	int i;
	//Écrase la valeur i, a supprimer, par la valeur a i+1
	for(i=index;i<*nbrow;i++)
		(*personne)[i] = (*personne)[i+1];

	//Enlève une ligne
	*nbrow-=1;
	printf("La personne %d vient d'etre supprimee [%d personnes restantes]\n",index+1, *nbrow);
}
//--------Fonction de sauvugarde---------//
void Sauvegarde(Personne (*personne)[],int nbrow){
	int i;
	FILE *annuairecopy = fopen("./AnnuaireNew.csv","w");

	if(annuairecopy==NULL)
	{
		//---------Operation echoué--------//
        printf("Le fichier ne peut pas être crée\n");
        exit(EXIT_FAILURE);
	}
	for(i=0;i<=nbrow; i++)
	{
		fprintf(annuairecopy, "%s,",(*personne)[i].prenom);
		fprintf(annuairecopy, "%s,",(*personne)[i].nom);
		fprintf(annuairecopy, "%s,",(*personne)[i].ville);
		fprintf(annuairecopy, "%s,",(*personne)[i].codepostal);
		fprintf(annuairecopy, "%s,",(*personne)[i].tel);
		fprintf(annuairecopy, "%s,",(*personne)[i].email);
		fprintf(annuairecopy, "%s\n",(*personne)[i].profession);
	}
	fclose(annuairecopy);
}

void Filtre(Personne (*personne)[], int nbrow, int choix)
{
	int ligne, colonne, programme, compteur;
	char cherchant[50];
	printf("Veuillez entrer les mots que vous voulez chercher\n");
	printf(" > ");
	fgets(cherchant, 50, stdin);

	switch (choix)
	{
		case 1:
			for (colonne=0; colonne<=nbrow; colonne++)
			{	
				programme = 1; //-----Reset programme à 1 à chaque fois, sinon programme reste 0 si c'est fause------//
				ligne = 0;
				do
				{
					if ((*personne)[colonne].prenom[ligne] == cherchant[ligne])
					{
						ligne++;
					}
					else programme = 0;
				} while (cherchant[ligne]!='\n' && programme==1);
				if(programme == 1) 
				{
					printf("-------------------------------------------------------------");
					printf("\n%s\n",(*personne)[colonne].prenom);
					printf("%s\n", (*personne)[colonne].nom);
					printf("%s\n", (*personne)[colonne].ville);
					printf("%s\n", (*personne)[colonne].codepostal);
					printf("%s\n", (*personne)[colonne].tel);
					printf("%s\n", (*personne)[colonne].email);
					printf("%s\n", (*personne)[colonne].profession);
					printf("-------------------------------------------------------------");
				}
				
			}

			break;

			// case 2:
			// 	break;
			// case 3:
			// 	break;
			// case 4:
			// 	break;
			// case 5:
			// 	break;
			// case 6:
			// 	break;
			// case 7:
			// 	break;
	}

}
