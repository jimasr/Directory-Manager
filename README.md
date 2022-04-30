# SAE-C
An insight on what C programming can do! Check out our first semester project of University Bachelor of Technology, a project on customer directory management. Entirely developed in C language, it is designed and optimised to the maximum in order to extract the information from a customer directory as fast and as simply as possible. 
The structure and the dynamic usage of memory in the programme provides a robust system in data manipulation even when working with a big amount of data thus enhances and guarantees an optimal user experience As for now, our program is still in French language but for the upcoming version, we will definitely provide a multi language support.  

## Getting Started
Git clone the project :  
```
https://github.com/BaudryLilian/Directory-Manager.git
````
We’ve provided an executable file __Gestionnaire.exe__ in the package for Windows OS users. 

Windows :   
```
.\Gestionnaire.exe
```

To create the same executable file using GCC :  

Run this command in your terminal to compile all .c files (user has to be placed in the root directory of the project). 
```
gcc *.c -o [file name]
```


## Usage
The program is a system fully capable of exploiting the database just by using the menu. A file with the extension .csv is required before launching into the configuration menu.
### Initialisation

Enter the name of the file (caps sensitive) to exploit the data. The data must be in the format 

<table align="center">
	<td>first name</td>
	<td>last name</td>
	<td>city</td>
	<td>postcode</td>
	<td> phone number</td>
	<td>email</td>
	<td>occupation </td>
</table>

separated with commas.
```
      - Gestionnaire d'annuaire - Version 2 - 
      
Rentrez le nom de votre annuaire >
```
     
### Mode
There are two possible modes : 
1. Normal Mode  

   Normal mode is non-dev mode that displays a normal use of customer directory management.
   
2. Advanced Mode  

   Gives an in-depth study on the precise time taken for each completion of a procedure.

```
Voulez-vous l'ouvrir en mode avancé ?
      1. Non      2. Oui
>
```

### Menu
```
Menu Principale : 

      1. Afficher l'annuaire
      2. Rechercher dans l'annuaire
      3. Ajouter une personne
      4. Sauvegarder
      5. Informations
      6. Mode Avance
      7. Quitter

```
### Listing All Clients

(1) is for listing all clients, the sequence is organised in the same manner as the source file.
### Search Engine

```
Menu de recherche :

         1. Par Index
         2. Valeurs Multiples
         3. Valeurs Manquantes
         4. Par Prenom
         5. Par Nom
         6. Par Ville
         7. Par Code Postal
         8. Par Telephone
         9. Par Adresse Email
        10. Par Profession
        11. Quitter
 >
```
(2) is our search engine. We implemented a hybrid algorithm consisting in using binary search and linear search to speed up the process of searching a client. This search engine can search a precise case insensitive value by giving the index ie. the client's number, or by giving several values. (4-10) is our filtering mechanism consisting of several indications to search a person.  The filtering method will also work in sorting the clients based on the column thanks to the Shell sorting algorithm.  

```
Indications :
        Tous    :  [*]   Commence par : [...*]   Contient : [*...*]
        Exact   : [...]  Finit par    : [*...]
```

'*' in this case is used to represent any chaine of character. It is definitely possible to view all the clients, lexicographically sorted from a column associated by simply entering a single *.
Users are also given the possibility to modify the data of a client once the result of the search is a success. 

### Adding a Client
 
User has to manually add a client by entering the number (3). Here, users will be prompted to enter all the values for a client. Not entering a value will simply write N/A in the column associated. All formatage errors will be included and automatically treated by the programme. At the end, a brief resume of what had been done will be shown.
### Saving 

All the data manipulation that has been done until now is being written in the random access memory (RAM) therefore (4) will allow users to save their modification in a file. They can either write a completely new file or rewrite the previous document they had entered to simply overwrite the file. 

### Informations

(5) provides simple information on the user's environment. This includes the name of the file being used, the number of clients being saved, and the number of memory cases being shown in the example below.  

```
Nom du fichier utilise : Annuaire.csv
        - Nombre de personnes renseignees : 5001 personnes
        - Nombre de personnes alloues     : 5001 cases
        - Verification du tri indirect    : [ Succes ]
        - Mode Avance                     : [ Desactive ]

        - Appuyez sur entree pour continuer -
```

### Advanced Mode

(6) provides a possibility of transitioning from normal mode to advanced mode or vice versa. 

### End Session

Users can exit the program any time by using (7). The failure in manually saving the modifications will result in data losses when the memory is freed. 

## Authors
[Lilian Baudry](https://github.com/BaudryLilian)  
[Hazim ASRI](https://github.com/wockehs001)
## Licence
Copyright (c) Lilian BAUDRY / Hazim ASRI . All rights reserved.

