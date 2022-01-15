# SAE-C
An insight on what C programming can do! Check out our first semester project of University Bachelor of Technology, a project on customer directory management with the possibilites in data manipulation and data configuration.

## Getting Started
Git clone the project :  
```
https://github.com/Irophin/SAE-C.git
````
An executable file __Gestionnaire.exe__ is already included in the package. To execute the file according to your OS : 

Windows :   
```
.\Gestionnaire.exe
```

UNIX based OS :   
```
./Gestionnaire.exe
```
To create the same executable file using GCC :  

Run this command in your terminal to compile all .c file
```
gcc *.c -o [file name]
```


## Usage
The program is a system fully capable of exploiting the database just by using the menu. A file with the extension .csv is required before launching into the configuration menu.
### Initiallisation

Enter the name of file (caps sensitive) to exploit the data. The data must be in the format firstname, lastname, city, postcode, phonenumber, email, occupation separated with commas.
```
      - Gestionnaire d'annuaire - Version 2 - 
      
Rentrez le nom de votre annuaire >
```
     
### Mode
There are two possible modes : 
1. Normal Mode  

   Normal mode is non-dev mode that display a normal use of customer directory management.
   
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
### 
## Authors
[Lilian Baudry](https://github.com/Irophin)  
[Hazim ASRI](https://github.com/wockehs001)
## License
Copyright (c) Lilian BAUDRY / Hazim ASRI . All rights reserved.

Licensed under the [MIT License](https://github.com/microsoft/calculator/blob/master/LICENSE)
## 
