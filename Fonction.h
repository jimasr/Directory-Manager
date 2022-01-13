#ifndef FONCTION
#define FONCTION

/**
: Entree personne : adresse d'une structure de type PERSONNE
: Entree colonne  : unsigned char
: Entree adresse  : adresse du première caractère d'une chaine
: Precondition    : 0 <= colonne <= 6
: Postcondition   : Assigne a la colonne demande de la personne donnée une nouvelle adresse 
*/
void SetAdresse(PERSONNE * personne, unsigned char colonne, char * adresse);

/**
: Entree personne : adresse d'une structure de type PERSONNE
: Entree colonne  : unsigned char
: Sortie Adresse  : l'adresse vers une chaine de caractère
: Precondition    : 0 <= colonne <= 6 
: Postcondition   : Renvoie l'adresse de la chaine de caractère a la colonne demandée de la personne donnée
*/
char * GetAdresse(PERSONNE * personne, unsigned char colonne);

/**
: Entree personne : L'adresse d'une structure de type PERSONNE
: Postcondition   : Permet d'ouvrir et d'affecter dynamiquement tous les valeurs d'un fichier CSV donnée
*/
void OuvertureCSV(REPERTOIRE * repertoire);

/**
: Entree repertoire : L'adresse d'une structure de type REPERTOIRE
: Precondition      : le tableau d'information  du répertoire ne doit pas être vide
: Postcondition     : Le tableau d'indice doit être initialise et près pour un tri indirect
*/
void InitSort(REPERTOIRE * repertoire);

/**
: Entree repertoire : L'adresse d'une structure de type REPERTOIRE
: Postcondition     : Les tableaux d'indice de chaque colonne doivent être utilisable pour trier le tableau
:				      L'algorithme de tri par insertion indirect sera utilise
*/
void ShellSort(REPERTOIRE * repertoire);

/**
: Entree repertoire : adresse d'une structure de type REPERTOIRE
: Postcondition     : les tableaux d'indice de chaque colonne doivent être utilisable pour trier le tableau
:	                  l'algorithme de tri de shell indirect sera utilise
*/
void InsertSort(REPERTOIRE * repertoire);

/**
: Entree repertoire : L'adresse d'une structure de type REPERTOIRE
: Sortie tri        : unsigned char
: Postcondition     : Cette fonction retourne 1 si les tableaux d'indices permet un tri correct, 0 si ce n'est pas le cas 
*/
int VerifTri(REPERTOIRE * repertoire);

/**
: Entree personne : L'adresse d'une structure de type REPERTOIRE
: Entree index    : unsigned int
: Precondition    : le tableau d'information ne doit pas etre vide
: Postcondition   : Supprime la personne à la position index
:				    retri le tableau
*/
void Suppression(REPERTOIRE * repertoire, unsigned int index);

/**
: Entree personne : L'adresse d'une structure de type REPERTOIRE
: Entree index    : unsigned int
: Precondition    : le tableau d'information ne doit pas etre vide
: Postcondition   : demande à l'utilisateur quelle colonne de la peronne il veut modifier et appelle la fonction de modification
:				    le tableau est pas la suite retrié
*/
void Modification(REPERTOIRE * repertoire, unsigned int index);

/**
: Entree personne : adresse d'une structure de type REPERTOIRE
: Entree index    : unsigned int
: Precondition    : Le tableau d'information ne doit pas être vide
: Postcondition   : Modifie la valeur de la personne donnée a la valeur donnée
:				    Le tableau est pas la suite retrié
*/
void ModifVal(PERSONNE * personne, unsigned char colonne);

/**
: Entree personne : adresse d'une structure de type REPERTOIRE
: Postcondition   : rajoute une personne a la fin du fichier et retri les tableaux d'indices en fonction des valeurs rentrée
*/
void Ajout(REPERTOIRE * repertoire);


/**
: Entree personne : adresse d'une structure de type REPERTOIRE
: Entree colonne  : unsigned char
: Postcondition   : Demande une chaine de caractère et l'utilise pour filtrer sur les personnes par la colonne demandé
*/
unsigned char Filtre(REPERTOIRE * repertoire, unsigned char colonne);

/**
: Entree repertoire : L'adresse d'une structure de type REPERTOIRE
: Postcondition     : Demande a l'utilisateur 3 valeurs a chercher et affiche la personne si il y a une correspondance
*/
unsigned char Recherche(REPERTOIRE * repertoire);

/**
: Entree personne : adresse d'une structure de type REPERTOIRE
: Postcondition   : affiche toutes les personnes avec des données manquantes
*/
unsigned char MissingData(REPERTOIRE * repertoire);

/**
: Entree personne : adresse d'une structure de type REPERTOIRE
: Postcondition   : sauvegarde les informations dans le fichier rentre par l'utilisateur
*/
void Sauvegarde(REPERTOIRE * repertoire);

/**
: Entree cara   : char
: Postcondition : renvoyé le caractère d'entrée en miniscule si s'il était en majuscule
: 	              sinon renvoie le caractère original
*/
char Lower(char cara);

/**
: Entree chaine     : adresse du 1er caractère d'une chaine
: Entree souschaine : adresse du 1er caractère d'une chaine
: Postcondition     : renvoie 1 si sous chaine est une contenu dans la chaine sinon 0
*/
unsigned char SubString(char * chaine, char * souschaine);

/**
: Entree personne : adresse d'une structure de type REPERTOIRE
: Entree colonne  : unsigned char
: Entree Filtre   : adresse du 1er element de mon filtre
: Postcondition   : renvoie l'indice de la première apparition des elements correspondant au filtre dans le tableau
:	                renvoie le nombre de ligne si il n'y a aucune correspondace
*/
unsigned int DicoSearch(REPERTOIRE * repertoire,unsigned char colonne, char * filtre);

/**
: Entree personne : adresse d'une structure de type REPERTOIRE
: Entree colonne  : unsigned char
: Entree Filtre   : adresse du 1er element de mon filtre
: Postcondition   : Renvoie l'indice de la première apparition des elements correspondant au filtre corepondant au début de la valeur dans le tableau
:	                Renvoie le nombre de ligne si il n'y a aucune correspondace
*/
unsigned int DicoSearchLimit(REPERTOIRE * repertoire,unsigned char colonne, char * filtre , unsigned char limite );

/**
: Entree personne : L'adresse d'une structure de type REPERTOIRE
: Postcondition   : Donne des infromations sur le tableau ( Chemin / nombre de ligne / nombre d'allocation / Etat du Tri / Etat mode avance)
*/
void Statistiques(REPERTOIRE * repertoire);

/**
: Entree personne : L'adresse d'une structure de type REPERTOIRE
: Entree index    : unsigned int
: Entree mode     : char
: Postcondition   : Affiche les informations de la personne a l'index données mais aussi dans le mode demandé (compact ou non)
*/
void Affichage(REPERTOIRE * repertoire, unsigned int index, unsigned char mode);

/**
: Entree chaine    : adresse du 1er element d'une chaine
: Entree formatage : unsigned int
: Postcondition    : Affiche les informations de la personne a l'index données mais aussi dans le mode demandé (compact ou non)
*/
void Empty(char * chaine, unsigned char formatage);

/**
: Entree colonne : unsigned char
: Postcondition  : Affiche dans le terminal le titre de la colonne donnée
*/
void GetColonne(unsigned char colonne);

/**
: Entree colonne : unsigned char
: Precondition   : 0 <= colonne <= 6
: Postcondition  : Clear le buffer stdin
*/
void StdClear();

/**
: Entree repertoire : L'adresse d'une structure de type REPERTOIRE
: Postcondition     : Libère tous les espaces alloue au repertoire
*/
void MemoryCls(REPERTOIRE * repertoire);

/**
: Entree chaine : adresse du 1er element d'une chaine
: Postcondition : Supprime les ',' et retire le '\n' et vide le buffer si besoin  
*/
void VerifStr(char * chaine);

/**
: Entree debut  : unsigned int
: Entree fin    : unsigned int
: Sortie choix  : unsigned int
: Postcondition : retourne le choix de l'utilisateur entre les bornes début et fin comprisent
*/
unsigned int Select(unsigned int debut,unsigned int fin);

/**
: Postcondition : Mets en pause le programme
*/
void Pause();

/**
: Postcondition : Clear le terminal
*/
void Clear();

#endif