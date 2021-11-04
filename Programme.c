#include <stdio.h>
#include <string.h>

typedef struct donnees{
	char nom[20], prenom[20];
	char ville[20], codepostal[5];
	char tel[10], email[40];
	char profession[20];
}personne;


int main()
{
	FILE *annuaire = fopen("Annuaire.csv","r");
	char ligne[135];
	int i;
	int nbrow=1;

	while(fgets(ligne,sizeof(ligne),annuaire) != NULL && nbrow<=10){
		printf("\n\nPersonne numero %d :\n-	", nbrow);
		for(i=0;ligne[i]!='\n';i++){
			if (ligne[i]==',')
				printf("\n-	");
			else
				printf("%c", ligne[i]);
		}
		nbrow++;
	}
}