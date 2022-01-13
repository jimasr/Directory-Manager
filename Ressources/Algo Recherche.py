def recherche_dico(tab : tableau de X, indice : tableau de int, e : X ):
"""
: Entrée tab:tableau de X
: Entrée indice : tableau de int
: Entrée e : X
: Sortie milieu : int
: Precondition
:   Le tableau n'est pas vide
:   Pour tout i compris entre 0 et tab-2, on a tab[i]<=tab[i+1]
: Postcondition
:	Retourne l'indice de la 1ere apparition de l'element recherché
: Déclaration
:   ide,ifi : int 
"""
#Debut
	ide = 0
	ifi = tab.size-1
	
	while ide<=ifi:
		milieu = (ide+ifi)//2
		if tab[indice[milieu]] == e:
			while milieu>0 and tab[indice[milieu-1]] == e:
				milieu = milieu - 1
			#endwhile
			return(milieu)
		#endif
		
		if tab[indice[milieu]] < e:
			ide = milieu+1
		else:
			ifi = milieu-1
		#elif
	#enwhile
	return(-1)
#fin


def recherche_seq(tab : tableau de X,indice : tableau de int, e : X ):
"""
	: Entrée tab : tableau de X
	: Entrée indice : tableau de int
	: Entrée e : X
	: Precondition
	:   Le tableau n'est pas vide
	:   Pour tout i compris entre 0 et tab-2, on a tab[i]<=tab[i+1]
	: Postcondition
	:	Affiche tous les elements correspondant a une recherche
	: Déclaration :
	:	i : int
"""
#Debut
	i = recherche_dico(tab,indice, e);

	if i != -1 :
		while i < tab.size and tab[indice[i]]==e:
			print("correspondance trouvée : ", tab[i] , ", à l'indice : ", i)
			i = i+1
		#Endwhile
	else:
		print("Aucune correspondance trouvée")
	#Endif
#Fin