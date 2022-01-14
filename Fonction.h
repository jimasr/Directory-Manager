#ifndef FONCTION
#define FONCTION

/**
: Entree personne : adresse d'une structure de type PERSONNE
: Entree colonne  : unsigned char
: Entree adresse  : adresse du premier caractère d'une chaine
: Precondition    : 0 <= colonne <= 6
: Postcondition   : assigne a la colonne de la personne donnee, une nouvelle adresse 
*/
void SetAdresse(PERSONNE * personne, unsigned char colonne, char * adresse);

/**
: Entree personne : adresse d'une structure de type PERSONNE
: Entree colonne  : unsigned char
: Sortie Adresse  : l'adresse vers une chaîne de caractere
: Precondition    : 0 <= colonne <= 6 
: Postcondition   : renvoie l'adresse de la chaîne de caractere e la colonne de la personne donnée
*/
char * GetAdresse(PERSONNE * personne, unsigned char colonne);

/**
: Entree repertoire : adresse d'une structure de type REPERTOIRE
: Precondition      : le fichier doit etre un CSV de 7 colonnes et une ligne ne doit pas depasser 300 caractères 
: Postcondition     : demande le chemin de l'annuaire et s'il faut activer le mode avance
: 					  puis ouvre et affecter dynamiquement toutes les valeurs du fichier CSV donnee, dans le répertoire
*/
void OuvertureCSV(REPERTOIRE * repertoire);

/**
: Entree repertoire : adresse d'une structure de type REPERTOIRE
: Precondition      : les tableaux d'indices doivent faire la meme taille que le tableau d'informations
: Postcondition     : le tableau d'indice doit etre initialise et pret pour un tri indirect sur le tableau d'informations
*/
void InitSort(REPERTOIRE * repertoire);

/**
: Entree repertoire : adresse d'une structure de type REPERTOIRE
: Precondition      : le tableau d'information du repertoire ne doit pas etre vide
: Postcondition     : les tableaux d'indice de chaque colonne doivent etre utilisable pour trier le tableau correctement (alphabetique)
:				      l'algorithme de tri par insertion indirect sera utilise
*/
void ShellSort(REPERTOIRE * repertoire);

/**
: Entree repertoire : adresse d'une structure de type REPERTOIRE
: Precondition      : le tableau d'information du repertoire ne doit pas etre vide
: Postcondition     : les tableaux d'indice de chaque colonne doivent etre utilisable pour trier le tableau correctement (alphabetique)
:	                  l'algorithme de tri de shell indirect sera utilise
*/
void InsertSort(REPERTOIRE * repertoire);

/**
: Entree repertoire : adresse d'une structure de type REPERTOIRE
: Sortie tri        : unsigned char
: Postcondition     : retourne 1 si les tableaux d'indices permettent un tri correct (alphabetique) du tableau d'informations, 0 si ce n'est pas le cas 
*/
int VerifTri(REPERTOIRE * repertoire);

/**
: Entree repertoire : adresse d'une structure de type REPERTOIRE
: Entree index      : unsigned int
: Precondition      : le tableau d'information ne doit pas etre vide
: Postcondition     : supprime la personne a l'index donnee
:				      puis re-tri le tableau d'information indirectement en consequence
*/
void Suppression(REPERTOIRE * repertoire, unsigned int index);

/**
: Entree repertoire : adresse d'une structure de type REPERTOIRE
: Entree index      : unsigned int
: Precondition      : le tableau d'information ne doit pas etre vide
: Postcondition     : demande a l'utilisateur quelle colonne de la personne qu'il veut modifier et appelle la fonction ModifVal en consequence
:				      le tableau est par la suite re-trie
*/
void Modification(REPERTOIRE * repertoire, unsigned int index);

/**
: Entree repertoire : adresse d'une structure de type REPERTOIRE
: Entree index      : unsigned int
: Precondition      : le tableau d'information ne doit pas etre vide
: Postcondition     : modifie la valeur de la personne donnee a la colonne demandee
*/
void ModifVal(PERSONNE * personne, unsigned char colonne);

/**
: Entree repertoire : adresse d'une structure de type REPERTOIRE
: Postcondition     : ajoute une personne a la fin du fichier en demandant ses informations et re-tri le tableau en consequence
*/
void Ajout(REPERTOIRE * repertoire);

/**
: Entree repertoire : adresse d'une structure de type REPERTOIRE
: Entree colonne    : unsigned char
: Sortie indication : unsigned char
: Postcondition		: demande une chaine de caractere et l'utilise pour filtrer les personnes sur la colonne demandes
:					: la chaine de caractere pouvant contenir des informations sur le type de filtre demande
*/
unsigned char Filtre(REPERTOIRE * repertoire, unsigned char colonne);

/**
: Entree repertoire : adresse d'une structure de type REPERTOIRE
: Sortie indication : unsigned int
: Postcondition     : demande a l'utilisateur 3 valeurs a chercher et affiche la personne s'il y a une correspondance et retourne l'indice la personne,
: 					: retourne le nombre de lignes s'il n'y en a pas
*/
unsigned int Recherche(REPERTOIRE * repertoire);

/**²²
: Entree repertoire   : adresse d'une structure de type REPERTOIRE
: Sortie indication   : unsigned char
: Postcondition       : affiche toutes les personnes avec des données manquantes
*/
unsigned char MissingData(REPERTOIRE * repertoire);

/**
: Entree repertoire   : adresse d'une structure de type REPERTOIRE
: Postcondition       : sauvegarde les informations dans le fichier indique par l'utilisateur
*/
void Sauvegarde(REPERTOIRE * repertoire);

/**
: Entree cara    : char
: Sortie caralwr : char
: Postcondition  : renvoie le caractere d'entree en minuscule s'il etait en majuscule sinon renvoie le caractere original
*/
char Lower(char cara);

/**
: Entree chaine     : adresse du 1er caractère d'une chaine
: Entree souschaine : adresse du 1er caractère d'une chaine
: Sortie verif      : unsigned char
: Postcondition     : renvoie 1 si souschaine est contenu dans la chaine, sinon 0
*/
unsigned char SubString(char * chaine, char * souschaine);

/**
: Entree repertoire : adresse d'une structure de type REPERTOIRE
: Entree colonne    : unsigned char
: Entree Filtre     : adresse du 1er element du filtre
: Sortie indice     : unsigned int
: Postcondition     : renvoie l'indice de la première apparition des personnes correspondant exactement au filtre
:	                  renvoie le nombre de ligne si il n'y a aucune correspondance
*/
unsigned int DicoSearch(REPERTOIRE * repertoire,unsigned char colonne, char * filtre);

/**
: Entree repertoire : adresse d'une structure de type REPERTOIRE
: Entree colonne    : unsigned char
: Entree filtre     : adresse du 1er element du filtre
: Sortie indice     : unsigned int
: Postcondition     : renvoie l'indice de la premiere apparition des personnes auquel le debut de la valeur correspond au filtre
:	                  renvoie le nombre de ligne s'il n'y a aucune correspondace
*/
unsigned int DicoSearchLimit(REPERTOIRE * repertoire,unsigned char colonne, char * filtre , unsigned char limite );

/**
: Entree repertoire : adresse d'une structure de type REPERTOIRE
: Postcondition     : donne des informations sur le repertoire ( chemin / nombre de lignes / nombre d'allocations / etat du Tri / etat mode avance)
*/
void Statistiques(REPERTOIRE * repertoire);

/**
: Entree repertoire : adresse d'une structure de type REPERTOIRE
: Entree index      : unsigned int
: Entree mode       : unsigned char
: Postcondition     : affiche les informations de la personne a l'index donne, mais aussi dans le mode demande (compact ou non)
*/
void Affichage(REPERTOIRE * repertoire, unsigned int index, unsigned char mode);

/**
: Entree chaine    : adresse du 1er element d'une chaine
: Entree formatage : unsigned char
: Postcondition    : affiche le contenu de la chaine avec un taille minimal de "formatage" caracteres
:				   : affiche N/A si une valeur n'est pas renseignee
*/
void Empty(char * chaine, unsigned char formatage);

/**
: Entree colonne : unsigned char
: Precondition   : 0 <= colonne <= 6
: Postcondition  : affiche dans le terminal le titre de la colonne donnee
*/
void GetColonne(unsigned char colonne);

/**
: Entree colonne : unsigned char
: Postcondition  : clear le buffer stdin
*/
void StdClear();

/**
: Entree repertoire : adresse d'une structure de type REPERTOIRE
: Postcondition     : libere tous les espaces alloue au repertoire.
*/
void MemoryCls(REPERTOIRE * repertoire);

/**
: Entree chaine : adresse du 1er element d'une chaîne
: Postcondition : supprime les ',' les remplace par ' ' retire aussi le '\n' tout en vidant le buffer stdin si besoin  
*/
void VerifStr(char * chaine);

/**
: Entree chaine  : adresse du 1er element d'une chaine
: Entree colonne : unsigned char
: Entree limite  : unsigned int
: Postcondition  : verifie le format de la chaîne en fonction de la colonne et la redemande si le format est incorrect
*/
void VerifPattern(char * chaine , unsigned char colonne ,unsigned int limite);

/**
: Entree debut  : unsigned int
: Entree fin    : unsigned int
: Sortie choix  : unsigned int
: Postcondition : retourne le choix de l'utilisateur, qui est obligatoirement entre les bornes début et fin comprises
*/
unsigned int Select(unsigned int debut,unsigned int fin);

/**
: Postcondition : mets en pause le programme
*/
void Pause();

/**
: Postcondition : clear le terminal
*/
void Clear();

#endif