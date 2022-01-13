#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Structures.h"
#include "Fonction.h"

int main(){

	unsigned int reponse;
	unsigned char correspondance;
	unsigned char programme = 1;

	REPERTOIRE repertoire;

	printf("\n\t- Gestionnaire d'annuaire - Version 2 -\n\n");

	OuvertureCSV(&repertoire);

	Clear();

	InitSort(&repertoire);
	ShellSort(&repertoire);

	while (programme == 1){

		printf("Menu principale :");

		if (repertoire.avance == 1)
			printf(" [ Mode avance ]\n\n - Les affichages de personnes sont desactivees pour un calcul precis des temps d'executions -");

		printf("\n\n\t1. Afficher l'annuaire\n");
		printf("\t2. Rechercher dans l'annuaire\n");
		printf("\t3. Ajouter une personne\n");
		printf("\t4. Sauvegarder\n");
		printf("\t5. Informations\n");
		printf("\t6. Mode Avance\n");
		printf("\t7. Quitter\n");
	
		reponse = Select(1,7);

		printf("\n");
		
		switch (reponse){
			case 1:
				if (repertoire.avance != 1){
					for (unsigned int i = 0; i < repertoire.nblignes; i++)
						Affichage(&repertoire,i,0);
				}else
					printf("Le mode avance est active ! Aucun affichage n'est donc realise \n");
				
				break;
			
			case 2:

				Clear();
				printf("Menu de recherche :\n\n");
				printf("\t 1. Par Index\n");
				printf("\t 2. Valeurs Multiples\n");
				printf("\t 3. Valeurs Manquantes\n");
				for (unsigned char i = 4; i <= 10; i++){
					printf("\t%2d. Par ",i);
					GetColonne(i-4);
					printf("\n");
				}
				printf("\t11. Quitter\n");

				reponse = Select(1,11);
				printf("\n");

				if  (reponse ==  1){
					if (repertoire.avance!=1){
						printf("Rentrez l'indice de la personne (%d personnes renseigne) [0 pour quitter] ",repertoire.nblignes);
						reponse = Select(0,repertoire.nblignes);
						if (reponse != 0){
							reponse--;
							Clear();
							Affichage(&repertoire,reponse,1);
							correspondance = 2;
						}
						else
							correspondance = 0;
					}else{
						printf("Le mode avance est active ! Aucun affichage n'est donc realise \n");
						correspondance = 0;
					}
				}

				if (reponse ==  2)
					correspondance = Recherche(&repertoire);

				if (reponse ==  3)
					correspondance = MissingData(&repertoire);

				if (reponse>=4 && reponse<=10){
					Clear();
					correspondance = Filtre(&repertoire, reponse-4);
				}

				if (reponse ==  11){
					correspondance = 0;
					printf("Retour au menu principal\n");
				}
		
				if (correspondance > 0){
					if (correspondance == 1){
						printf("Selectionnez l'ID de la personne que vous voulez selectionner [0 pour quitter]");
						reponse = Select(0,repertoire.nblignes);
						if(reponse==0)
							correspondance=0;
						else{
							reponse--;
							Clear();
							printf("\n");
							Affichage(&repertoire,reponse,0);
						}
					}
					if(correspondance > 0){

						printf("\nQue voulez vous faire : \n");
						printf("\t1. Supprimer\n");
						printf("\t2. Modifier\n");
						printf("\t3. Quitter\n");
						switch (Select(1,3)){
						case 1:
							Suppression(&repertoire,reponse);
							break;
						case 2:
							Modification(&repertoire,reponse);
							break;
						case 3:
							break;
						default:
							printf("Incoherence dans le choix de modification\n");
						}
					}
				}

				break;
			case 3:
				Ajout(&repertoire);
				break;

			case 4:
				Sauvegarde(&repertoire);
				break;

			case 5:
				Statistiques(&repertoire);
				break;
			
			case 6:
				if (repertoire.avance == 0){
					repertoire.avance =1;
					printf(" Le mode avance vient d'etre active\n");
				}
				else{
					repertoire.avance =0;
					printf(" Le mode avance vient d'etre desactive\n");
				}
				break;

			case 7:
				programme = 0;
				MemoryCls(&repertoire);
				printf("\nA bientot !\n\n");
				break;
			
			default:
				printf("Ce menu n'a pas encore ete fait !\n");
		}
		Pause();
		Clear();
	}

	return 0;
}