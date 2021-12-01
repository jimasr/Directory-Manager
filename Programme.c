#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define taille 30
#define tailletel 16
#define taillecodep 6
#define tailleemail	60

//-----Declaration de la structures des informations-----//

typedef struct StructureCSV
{
	char prenom[taille], nom[taille];
	char ville[taille], codepostal[taillecodep];
	char tel[tailletel], email[tailleemail];
	char profession[taille];
} Personne;


//--------Declaration des Prototypes de fonctions-------//

void Pause();
void Clear();
void OuvertureCSV(Personne (*personne)[],int * nbrow);
void Affichage(Personne *personne, int index, char mode);
void Suppression(Personne (*personne)[], int index, int * nbrow);
void Choix(Personne (*personne)[], int index, int * nbrow);
void Empty(char * chaine, unsigned char formatage);
void Modification(Personne *personne);
void ModifVal(Personne(*personne), int colonne);
void Sauvegarde(Personne (*personne)[], int nbrow);
void Filtre(Personne (*personne)[], int nbrow, int choix);
void Ajout(Personne *personne, int *nbrow);
char *OriganisationCSV(Personne *personne, int colonne);
char Minuscule(char lettre);
void stdclean();
void Triage(Personne(*personne)[],int nbrow);

//------Detecte le systeme d'exploitation et adapte le commande systeme() en fonction du systeme------//
void Clear(){
	#if _WIN32 || _WIN64
		system("cls");
	#else
		system("clear");
	#endif
}

void Pause(){
	#if __APPLE__
		system("echo - Appuyez sur une touche -");
		system("read touche");
	#elif _WIN32 || _WIN64
		system("Pause. >nul | echo  - Appuyez sur une touche -");
	#elif unix
		system('read -n1 -r -p " - Appuyez sur un touche " - ');
	#endif
}

unsigned char Taille(char colonne){
	if (colonne == 3)
		return taillecodep;
	if (colonne == 4)
		return tailletel;
	if (colonne == 5)
		return tailleemail;
	return taille;
}

//----------Fonction d'affichage d'une personne----------//
void Affichage(Personne *personne, int index,char mode){
	// mode : 0 = Affichage compact
	// mode : 1 = Affichage complet
	if(mode == 1){
		//--Affichage des informations d'une personne--//
		printf("Information sur la personne %d :\n\n", index+1);

		printf("Nom : ");
		Empty((*personne).nom,0);
		printf("\tPrenom : ");
		Empty((*personne).prenom,0);

		printf("\n\nLieu de residence : ");
		Empty((*personne).ville,0);
		printf(" [ ");
		Empty((*personne).codepostal,0);
		printf(" ]");

		printf("\nProfession : ");
		Empty((*personne).profession,0);

		printf("\n\nContact :\n");

		printf("\t- Telephone : ");
		Empty((*personne).tel,0);

		printf("\n\t- Email: ");
		Empty((*personne).email,0);
	}else{
		printf("Personne %d : ", index+1);
		Empty((*personne).nom,taille);
		Empty((*personne).prenom,taille);
		Empty((*personne).ville,taille);
		Empty((*personne).tel,tailletel);
	}

	printf("\n");
}

//---Fonction qui affiche N/A quand pas d'information----//
void Empty(char * chaine, unsigned char formatage){
	if (strlen(chaine) > 0){
		printf("%s", chaine);
		if (formatage>0){
			for(int i=strlen(chaine); i<formatage;i++)
				printf(" ");
			printf(" | ");
		}
	}
	else{
		printf("N/A");
		if (formatage>0){
			for(int i=3; i<formatage;i++)
				printf(" ");
			printf(" | ");
		}
	}
}

//---------Fonction qui ouvre et assigne le CSV----------//
void OuvertureCSV(Personne (*personne)[], int *nbrow){
	//---------Declaration des variable---------//

	char ligne[200];

	char unsigned i, j;

	char column = 0;
	*nbrow = 0;

	//-----------Ouverture du CSV-----------//

	FILE *annuaire = fopen("Annuaire.csv", "r");

	//------Gestion d'échec d'ouverture-------//
	if (annuaire == NULL)
	{
		printf("Echec de l'ouverture du fichier");
		exit(EXIT_FAILURE);
	}

	//-------------Lecture du CSV-------------//

	//Recommence tant que la ligne du fichier n'est pas vide
	while (fgets(ligne, sizeof(ligne), annuaire) != NULL)
	{
		j = 0;
		column = 0;

		//Parcours la ligne lettre par lettre
		for (i = 0; ligne[i] != '\0'; i++)
		{
			//Considère une nouvelle colonne à chaque ',' et exclu le retour chariot
			if (ligne[i] == ',' || ligne[i] == '\n')
			{
				//Assigne le caractère null a la fin de chaque valeurs
				OriganisationCSV(&(*personne)[*nbrow], column)[j] = '\0';
				j = 0;
				column++;
			}
			else
			{
				//Assigne le caractère actuel à sa colonne
				OriganisationCSV(&(*personne)[*nbrow], column)[j] = ligne[i];
				j++;
			}
		}
		*nbrow += 1;
	}

	//------------Fermeture du CSV------------//

	fclose(annuaire);
}

//-Renvoie l'adresse de la valeur associée a la colonne--//
char *OriganisationCSV(Personne *personne, int colonne){
	switch (colonne)
	{
	case 0:
		return (*personne).prenom;
	case 1:
		return (*personne).nom;
	case 2:
		return (*personne).ville;
	case 3:
		return (*personne).codepostal;
	case 4:
		return (*personne).tel;
	case 5:
		return (*personne).email;
	case 6:
		return (*personne).profession;
	}
}

//----Vérifie l'appartenance d'un index à l'annuaire-----//
int Selection(Personne personne[], int nbrow){
	int index = 0;
	do
	{
		printf(" > ");
		scanf("%d", &index);
		stdclean(stdin);
		if (index < 0)
			printf("\tUne erreur s'est produite, veuillez rentrer un nombre correct.\n");
		else if (index > nbrow)
		{
			printf("\tAttention, la valeur %d est trop eleve, [%d personnes renseignees]\n", index, nbrow);
		}

	} while (index < 0 || index > nbrow);

	//Retourne un nombre entre 0 et le nombre de ligne
	return index;
}

//--Fonction permettant le choix - modifier ou supprimer--//
void Choix(Personne (*personne)[], int index, int *nbrow){
	int reponse;
	do
	{
		//Menu choix suppression ou modification
		printf("\n- Que voulez-vous faire ?\n");
		printf("\t1. Supprimer cette personne\n");
		printf("\t2. Modifier cette personnes\n");
		printf("\t3. Retour\n");
		printf(" > ");
		scanf("%d", &reponse);
		stdclean(stdin);

		//Menu des choix
		switch (reponse)
		{
		case 1:
			Suppression(personne, index, nbrow);
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
	} while (reponse < 1 || reponse > 3);
}

//-------Fonction de modification d'une personne---------//
void Modification(Personne *personne){
	int reponse;
	int i = 0;
	char modif;
	do
	{
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
		scanf("%d", &reponse);
		stdclean(stdin);

		if (reponse < 1 || reponse > 8)
			printf("Une erreur c'est produite, veuillez rentrez un nombre correct !");

	} while (reponse < 1 || reponse > 8);

	//Si l'utilisateur ne veux pas quitter
	if (reponse != 8)
	{
		printf("\nRentrez la nouvelle valeur : ");
		ModifVal(personne, reponse - 1);
		printf("\nCette valeur a correctement ete assigne\n");
	}
}

//--------Fonction de suppression d'une personne---------//
void Suppression(Personne (*personne)[], int index, int *nbrow){
	int i;
	//Écrase la valeur i, a supprimer, par la valeur a i+1
	for (i = index; i < *nbrow; i++)
		(*personne)[i] = (*personne)[i + 1];

	//Enlève une ligne
	*nbrow -= 1;
	printf("La personne %d vient d'etre supprimee [%d personnes restantes]\n", index + 1, *nbrow);
}

//--------------Fonction de sauvegarde-------------------//
void Sauvegarde(Personne (*personne)[], int nbrow){
	int i;
	int j;
	FILE *annuairecopy = fopen("./AnnuaireNew.csv", "w");
	if (annuairecopy == NULL)
	{
		//---------Operation echoué--------//
		printf("Le fichier ne peut pas être crée\n");
		exit(EXIT_FAILURE);
	}
	for (i = 0; i <= nbrow; i++)
	{
		for(j=0; j<=5;j++){
			fprintf(annuairecopy, "%s,", OriganisationCSV(&(*personne)[i],j));
		}
		fprintf(annuairecopy, "%s\n", OriganisationCSV(&(*personne)[i],6));
	}
	fclose(annuairecopy);
}

//---------Fonction de filtre et recherche---------------//
void Filtre(Personne (*personne)[], int nbrow, int choix){
	int ligne;
	int compteur=0;
	int i;
	char verif,colonne;
	char recherche[50];
	char type;

	do{
		printf("\nVeuillez entrer les donnees que vous voulez chercher > ");
		fgets(recherche,sizeof(recherche),stdin);
		recherche[strlen(recherche)-1] = '\0';
		if (strlen(recherche)==0)
			printf("\nVeuillez rentrez une valeur correcte \n");
	}while(strlen(recherche)==0);

	if (recherche[0] == '*' && strlen(recherche)==1)
		type = 0;
	else if (recherche[strlen(recherche)-1] == '*')
	{
		recherche[strlen(recherche)-1] = '\0';
		if (recherche[0] == '*')
		{
			type = 3;
			//--Decaler et ecraser l'etoile--//
			for (i = 0; i < strlen(recherche); i++) recherche[i] = recherche[i + 1];
		}
		else
			type = 2;
	}
	else if(recherche[0] == '*')
	{
		type = 4;
		for (i = 0; i < strlen(recherche); i++) recherche[i] = recherche[i + 1];
	}
	else
		type=1;

	//
	//	Type 0 : Affiche tout (*)
	//	Type 1 : recherche exacte (xxx)
	//	Type 2 : recherche par Filtre (xxx*)
	//	Type 3 : Recherche par composé de   (*xxx*)
	//	Type 4 : Recherche pas commencement (*xxx)
	//

	for (ligne = 0; ligne < nbrow; ligne++)
	{

		if (type ==0)
			verif = 1;

		else if (type == 2){
			verif = 1;
			colonne=0;
			do{
				if (Minuscule(OriganisationCSV(&(*personne)[ligne], choix)[colonne]) == Minuscule(recherche[colonne]))
					colonne++;
				else
					verif = 0;
			} while (recherche[colonne] != '\0' && verif == 1);
		}

		else if (type==1){
			verif = 0;
			if (strcasecmp(OriganisationCSV(&(*personne)[ligne], choix),recherche)==0)
				verif = 1;
		}

		else if (type==3){
			int inclus;
			verif = 0;
			//---Si les deux chaines sont vides-----//
			if (OriganisationCSV(&(*personne)[ligne], choix)[0] == '\0' && recherche[0] == '\0')
				verif = 1;
			else
			{
				colonne = 0;
				while (OriganisationCSV(&(*personne)[ligne], choix)[colonne] != '\0' && verif == 0)
				{
					//---- Chercher le premier caractère de recherche dans tableau personne ------//
					while (OriganisationCSV(&(*personne)[ligne], choix)[colonne] != '\0' && OriganisationCSV(&(*personne)[ligne], choix)[colonne] != recherche[0]) colonne++;
					//--- Si le premier caractère est trouvé, chercher le reste -----//
					if (OriganisationCSV(&(*personne)[ligne], choix)[colonne] == recherche[0])
					{
						inclus = 1;
						i = 1;
						colonne++;
						//---Boucle pour verifier la prochaine char est s'il est toujours inclus ou pas--//
						while (inclus == 1 && recherche[i] != '\0') 
						{
							if (recherche[i] != OriganisationCSV(&(*personne)[ligne], choix)[colonne])
								inclus = 0;
							i++;
							colonne++;
						}
						if (inclus == 1)
							verif = 1;
					}
				}
			}
		}
		else if (type==4){
			verif = 1;
			//--commencer depuis la fin--//
			colonne = strlen(OriganisationCSV(&(*personne)[ligne], choix)) - 1;
			i = strlen(recherche) - 1;
			do
			{
				if (recherche[i] == OriganisationCSV(&(*personne)[ligne], choix)[colonne])
				{
					colonne--;
					i--;
				}
				else
					verif = 0;
			} while (colonne >= 0 && i >= 0 && verif == 1);
		}
		

		//Affichage de la personne trouvée
		if (verif == 1){
			Affichage(&(*personne)[ligne],ligne,0);
			compteur++;
		}
	}

	printf("\n\t - %d correspondances trouvees - \n",compteur);
}

//-------------Ajoute une nouvelle personne--------------//
void Ajout(Personne *personne, int *nbrow){

	printf("Prenom : ");
	ModifVal(personne, 0);
	printf("Nom : ");
	ModifVal(personne, 1);
	printf("Ville : ");
	ModifVal(personne, 2);
	printf("Code Postal : ");
	ModifVal(personne, 3);
	printf("Telephone : ");
	ModifVal(personne, 4);
	printf("Email : ");
	ModifVal(personne, 5);
	printf("Profesion : ");
	ModifVal(personne, 6);
	*nbrow += 1;

	printf("Cette personne a ete rajoutee !\n");
}

//---------Modifie la valeur d'une des colonnes----------//
void ModifVal(Personne *personne, int colonne){
	int i = 0;
	char modif;

	//Boucle tante qu'il n'y a pas de retour chariot et que i est inférieur a la taille max
	while (modif != '\n' && i < Taille(colonne) - 1)
	{
		scanf("%c", &modif);
		if (modif != '\n')
		{
			OriganisationCSV(personne, colonne)[i] = modif;
			i++;
		}
	}
	stdclean(stdin);
	//Assigne le caractère null a la fin de la valeur
	OriganisationCSV(personne, colonne)[i] = '\0';
}

//Affiche toutes les personnes avec des données manquantes//
void Manque(Personne (*personne)[], int nbrow){

	int i = 0;
	int j = 0;
	int cpt = 0;

	for(i=0; i<nbrow ; i++){
		j=0;
		while(j<7){
			if(strlen(OriganisationCSV(&(*personne)[i],j))==0){
				cpt++;
				Affichage(&(*personne)[i],i,0);
				break;
			}
			j++;
		}

	}
	printf("\n\t - %d personnes avec des donnees manquantes trouvees - \n\n",cpt);
}

char Minuscule(char lettre){
	if (lettre>='A' && lettre<='Z')
		return lettre+32;
	return lettre;
}

void Triage(Personne(*personne)[],int nbrow){
	int j;
	int i;
	Personne ppt;
	i=1;
	while (i < nbrow-1)
	{		
		ppt = (*personne)[i];
		j=i-1;
		while (j>=0 && strcasecmp((*personne)[j].nom,ppt.nom)>0)
		{
			(*personne)[j+1]=(*personne)[j];
			j=j-1;
		}
		(*personne)[j+1]=ppt;
		i++;
	}
}

void stdclean(){
	char c = 0;
	while (c != '\n' && c != EOF)
		c = getchar();
}
   
//--------------------Fonction main----------------------//
int main(){

	//Création d'un tableau contenant toutes les informations de toutes les personnes
	Personne information[7000];
	//Création du pointeur vers le tableau de structure
	Personne(*pt_info)[] = &information;

	int nbrow = 0;
	//Création du pointeur vers le nombre de ligne
	int *pt_row = &nbrow;

	//Entées utilisateur
	int reponse;
	int select;

	//Booléen qui fait boucler le programme
	char programme = 1;

	OuvertureCSV(pt_info, pt_row);
	Triage(pt_info,nbrow);

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
		scanf("%d", &reponse);
		stdclean();

		//------Switch de fonctionnalité------//
		switch (reponse)
		{
		case 1:
			do{
				//--------Sous menu de recherche----------//
				printf("\n\t----------------\n\n");

				printf("\t1. Rechercher par index\n");
				printf("\t2. Client avec des elements manquants\n");
				printf("\t3. Par Prenom\n");
				printf("\t4. Par Nom\n");
				printf("\t5. Par Ville\n");
				printf("\t6. Par code postal\n");
				printf("\t7. Par telephone\n");
				printf("\t8. Par email\n");
				printf("\t9. Par profession\n");
				printf("\t10. Retour\n");
				printf(" > ");
				scanf("%d", &reponse);
				stdclean(stdin);

				printf("nbligne : %d\n",nbrow);

				//---------options de recherches--------//
				if(reponse == 1){
					do
					{
						printf("\nRentrez l'index de la personne dont vous voulez les informations (0 pour quitter) : ");
						printf("%d\n",nbrow);
						select = Selection(information, nbrow);
						
						if (select != 0)
						{
							select--;
							printf("\n\t-- Recherche en cours --\n\n");
							Affichage(&information[select], select, 1);
							Choix(pt_info, select, pt_row);
							printf("\n");
							Pause();
							Clear();
						}
					} while (select != 0);
				}
				else if(reponse >=3 && reponse<=9){
					Clear();
					Filtre(pt_info, nbrow, reponse - 3);
				}
				else if(reponse!=10){
					printf("\n Une erreur s'est produite\n\n");
				}
			}while(reponse != 10);

			printf("\n > Retour au menu principal\n\n");
			Pause();
			Clear();

			break;

		case 2:
			printf("Creation d'un client : \n");
			Ajout(&information[nbrow], pt_row);
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
				if (reponse == 1)
				{
					Sauvegarde(pt_info, nbrow);
					printf("\nSauvegarde reussite!");
				}
				else
				{
					printf("\nUne erreur s'est produite");
				}

			} while (reponse != 0 && reponse != 1);
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
