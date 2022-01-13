#ifndef STUCTURE
#define STUCTURE

typedef struct {
	char * prenom;
	char * nom;
	char * ville;
	char * codepostal;
	char * tel;
	char * email;
	char * profession;
}PERSONNE;

typedef struct {
	PERSONNE * informations;
	char * chemin;
	unsigned int ** indices;
	unsigned int nballoc;
	unsigned int nblignes;
	unsigned char avance;
}REPERTOIRE;

#endif
