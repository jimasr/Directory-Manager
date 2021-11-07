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

void OuvertureCSV(Personne (*personne)[],int * nbrow);
void Affichage(Personne *personne, int index);
void Suppression(Personne (*personne)[], int index, int * nbrow);
void Choix(Personne (*personne)[], int index, int * nbrow);
void Empty(char chaine[]);
void Modification(Personne *personne);
void OriganisationCSV(Personne *personne,int colonne,char cara, int pos);
int Selection(Personne (*personne)[],int * nbrow);

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

int main(){

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
		printf("\t4. Quitter\n");
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
							system("Pause. >nul | echo  - Appuyez sur une touche -");
							system("cls");
						}
					}while(reponse != 0);
					break;
				
				//Retour
				case 8:break;

				//Gestion d'erreur saisie
				default:
					printf("\n Une erreur s'est produite\n\n");

			}
			printf("\n > Retour au menu principal\n\n");
			system("Pause. >nul | echo  - Appuyez sur une touche -");
			system("cls");
			break;

		//-------------Quitter------------//
		case 4:
			//Fin de la boucle programme
			printf("\n - A bientot !\n\n");
			programme = 0;
			break;

		//-----Gestion d'erreur saisie----//
		default:	
			system("cls");
			printf("\nUne erreur s'est produite, veuillez rentrer un numero correct !\n\n");
		}

	}

	//Arrêt du programme
	return 0;
}