#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//-----Declaration de la structures des informations-----//

typedef struct StructureCSV{
	char nom[40], prenom[20];
	char ville[20], codepostal[6];
	char tel[21], email[40];
	char profession[40];
}Personne;

int main()
{
	//---------Declaration des variable---------//

	char ligne[200];

	char unsigned i,j;

	int nbrow = 0;
	char column = 0;

	int unsigned reponse;
	char programme = 1;


	//-----------Ouverterture du CSV-----------//

	FILE *annuaire = fopen("Annuaire.csv","r");

	if(annuaire == NULL){
		printf("Echec de l'ouverture du fichier");
		exit(EXIT_FAILURE);
	}

	//-------------Lecture du CSV-------------//

	//Cration d'un tableau contenant toutes les informations de toutes les personnes
	Personne information[10000];

	//Recommence tant que la ligne du fichier n'est pas vide
	while(fgets(ligne,sizeof(ligne),annuaire) != NULL){
		j=0;
		column=0;

		//Parcours la ligne lettre par lettre
		for(i=0;ligne[i]!='\0';i++){
			//Considère une nouvelle colonne a chaque ',' et exclu le retour chariot
			if(ligne[i]==',' || ligne[i]=='\n'){
				j = 0;
				column++;
			}else{
				//Assigne les caracteres de la ligne a la colonne associée
				switch(column){
					case 0:
						information[nbrow].nom[j] = ligne[i];
						break;
					case 1:
						information[nbrow].prenom[j] = ligne[i];
						break;
					case 2:
						information[nbrow].ville[j] = ligne[i];
						break;
					case 3:
						information[nbrow].codepostal[j] = ligne[i];
						break;
					case 4:
						information[nbrow].tel[j] = ligne[i];
						break;
					case 5:
						information[nbrow].email[j] = ligne[i];
						break;
					case 6:
						information[nbrow].profession[j] = ligne[i];
						break;
				}
				j++;
			}
		}
		nbrow++;
	}
	
	//------------Fermeture du CSV------------//

	fclose(annuaire);

	//------------Affichage Titre------------//

	system("cls");
	printf("\n\t\t--- Version 1 - Ouverture et Recherche par index ---\n\n");

	//------------Affichage Menu------------//

	while (programme == 1)
	{
	
		//------Selection de fonctionnalité------//
		
		printf(" - Que voulez-vous faire ?\n");
		printf("\t1. Recherche par index\n");
		printf("\t2. ...\n");
		printf("\t3. ...\n");
		printf("\t4. ...\n");
		printf("\t5. Quitter\n");
		printf(" > ");
		scanf("%d",&reponse);
		fflush(stdin);

		//------Switch de fonctionnalité------//

		switch (reponse)
		{
		case 1:
			//------Recherche par index------//
			do{
				printf("\nRentrez l'index de la personne dont vous voulez les informations (0 pour quitter) : ");
				scanf("%d",&reponse);
				fflush(stdin);

				if (reponse < 0)
					printf("\n\tUne erreur c'est produite, veuillez rentrer un nombre correct.\n");

				else if(reponse>0){
					if (reponse<nbrow){
						//--Affichage des n-iems valeurs d'information--//
						printf("\n\t-- Recherche en cours --\n\n");
						printf("Le personne %d ",reponse);
						reponse--;
						if(strlen(information[reponse].nom)>0 || strlen(information[reponse].prenom))
							printf("s'appelle : %s %s\n",information[reponse].nom,information[reponse].prenom);
						else
							printf("Aucune information trouvee sur son nom/prenom\n");

						if(strlen(information[reponse].ville)>0)
							printf("Cette personne vit a %s [%s]\n",information[reponse].ville,information[reponse].codepostal);
						else
							printf("Aucune information trouvee sur son lieu de residence\n");

						printf("Sa profession est : ");
						if(strlen(information[reponse].profession)>0)
							printf("%s\n",information[reponse].profession);
						else
							printf("N/A\n");

						printf("\nContact :\n");

						printf("\t- Telephone : ");
						if(strlen(information[reponse].tel)>0)
							printf("%s\n",information[reponse].tel);
						else
							printf("N/A\n");

						printf("\t- Email : ");
						if(strlen(information[reponse].email)>0)
							printf("%s\n",information[reponse].email);
						else
							printf("N/A\n");

						printf("\n");
						system("Pause. >nul | echo  - Appuyez sur une touche -");
						system("cls");
					}
					else{
						printf("Attention, la valeur %d est trop eleve, [%d personnes renseignees] ",reponse,nbrow-1);
					}
				}

				else{
					printf("\n > Retour au menu principal\n\n");
					system("Pause. >nul | echo  - Appuyez sur une touche -");
					system("cls");
				}
			}while(reponse != 0);
			break;
		case 5:
			//---------Arret programme--------//
			printf("\n - A bientot !\n\n");
			programme = 0;
			break;
		
		default:
			//-----Gestion d'erreur saisie----//
			system("cls");
			printf("\nUne erreur c'est produite, veuillez rentrer un numero correct !\n\n");
		}

	}
	return 0;
}