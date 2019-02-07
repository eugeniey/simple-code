#include <stdio.h>
#include <string.h>
#include <stdlib.h>


// Structure qui contient tous les employees et leurs descriptions
struct Employes{
	char prenom[25]; 
	char nom[25];
	char poste;
	float heure;
	float salaire;
};


/* 
* Lit le fichier  
* Prend en entré le nombre d'employé et un pointeur d'un tableau de structure
* la fonction donne une valeur à ces pointeurs, afin de conserver l'information
*/
void lireFichier(int *nbEmploye, struct Employes *tabEmploi){
	FILE* fichDonne; 
	fichDonne = fopen("employes.dat","r");

	if(fichDonne == NULL){
		printf("Impossible d'ouvrir le fichier employes.dat");
		exit(1);
	}

	// Déclaration de toutes les variables du fichier
	char prenom[25]; 
	char nom[25];
	char poste; 
	float heure;
	float salaire;
	int iter = 0;   // nombre d'employés

	while(!feof(fichDonne)){
		// Extraction de l'information
		fscanf(fichDonne,"%s %s %c %f %f", nom, prenom, &poste, &heure, &salaire);
		
		// Place toutes les informations dans le tableau 
		strcpy(tabEmploi[iter].prenom, prenom);
		strcpy(tabEmploi[iter].nom, nom);
		tabEmploi[iter].poste = poste;
		tabEmploi[iter].heure = heure;
		tabEmploi[iter].salaire = salaire;

		iter++;		
	}
	*nbEmploye = iter ;
	fclose(fichDonne);
}


/* 
* Retourne le nombre d'employés de poste 'posteRech'
* qui travaillent plus de 'heureRech' heures 
*/
int rechercheHeure(char posteRech, float heureRech, struct Employes tabEmploye[],
int nbEmploye){
	int i;
	int nombre=0;

	for(i=0; i<nbEmploye; i++){
		if(tabEmploye[i].poste == posteRech){
			if(tabEmploye[i].heure > heureRech)
				
				nombre++;
		}		
	}
	return nombre;
}


/* 
* Affiche le nom et prénom des employés selon le poste 
*/
void afficheEmploye(char post, struct Employes tabEmployes[], int nbEmploye){

	int i;
	
	for(i=0; i<nbEmploye; i++){
		if(tabEmployes[i].poste == post){

			printf("%s %s a un salaire hebdomadaire de %.2f$ \n",tabEmployes[i].prenom, 
			tabEmployes[i].nom, tabEmployes[i].salaire);
		}		
	}
}


/* 
* Compare deux noms ensembles et détermine l'ordre alphabétique
* utiliser dans la fonction qsort, qui trie le tableau
*/
int comparaison(const void *j, const void *k){
	const struct Employes *dj = j, *dk = k;
	return stricmp(dj -> nom, dk -> nom);
}


/* 
* Permet de trier le tableau des employés selon leurs noms
* pour la recherche dichotomique
*/
void triage(struct Employes tabEmployes[], int nbEmploye){
	int size;
	size = sizeof(*tabEmployes);

	// Fonction qui trie efficacement le tableau des employés selon leurs noms 
	qsort(tabEmployes, nbEmploye, size, comparaison);
}


/* 
* Effectue une recherche dichotomique 
* prend en entrée le tableau d'employé, le nom recherché
* ainsi qu'une borne inférieur et supérieur d'indice du tableau 
* Retourne l'index du tableau où se trouve le nom 
*/
int rechercheDichotomique(struct Employes tabEmployes[], char element[], int borneInf, int borneSup){

	// Définit le milieu du tableau (le tableau change récursivement)
	int milieu = (borneInf + (borneSup) ) /2 ;

	if (borneSup>=borneInf){

		// Si l'élément recherché est au milieu du tableau 
		if(stricmp(tabEmployes[milieu].nom,element) == 0)
			return milieu;

		// Si l'élément recherché est plus petit que le milieu
		// alors on cherche dans la première moitié du tableau
		if(stricmp(tabEmployes[milieu].nom,element) > 0)
			return rechercheDichotomique(tabEmployes,element,borneInf,milieu-1);

		// Si l'élément recherché est plus grand que le milieu
		// alors on cherche dans la deuxième moitié du tableau
		if(stricmp(tabEmployes[milieu].nom,element) < 0)
			return rechercheDichotomique(tabEmployes,element,milieu+1,borneSup);
	}

	// Si l'élément n'est pas trouvé
	return -1;
}


void main(){

	struct Employes tabEmployes[30]; // tableau de structure de maximum 30 employé
	int nbEmploye;                   // nombre d'employé total
	char P,O,S,A;                    // différents postes

	// Lecture du fichier qui donne une valeur aux arguments
	lireFichier(&nbEmploye, tabEmployes);

	// Interface du menu	
	printf("\n Information disponible: \n");
	printf("    1) Le nombre d'employes total \n");
	printf("    2) Le nombre de programmeurs qui travaillent plus de 45h par semaine\n");
	printf("    3) Le nombre d'operateurs qui travaillent plus de 40.5h par semaine \n");
	printf("    4) Le nombre de secretaires qui travaillent plus de 35h par semaine \n");
	printf("    5) Le nom et salaire des employes operateurs \n");
	printf("    6) Le nom et salaire des employes programmeurs \n");
	printf("    7) Le poste d'un employe \n");
	printf("    8) Quitter le menu \n");
	
	int choix;
	printf(" \n Quel est l'option desiree? \n");
	scanf("%d",&choix);
	printf("\n");

	switch(choix){
		case 1 :
			printf("Le nombre d'employes total est: %d",nbEmploye);
			break;

		case 2:
			printf("Le nombre de programmeurs qui travaillent plus de 45h par semaine est: ");
			printf("%d \n",rechercheHeure('P',45,tabEmployes,nbEmploye));
			break;

		case 3:
			printf("Le nombre d'operateurs qui travaillent plus de 40.5h par semaine est: ");
			printf("%d \n",rechercheHeure('O',40.5,tabEmployes,nbEmploye));
			break;

		case 4:
			printf("Le nombre de secretaires qui travaillent plus de 35h par semaine est: ");
			printf("%d \n",rechercheHeure('S',35,tabEmployes,nbEmploye));
			break;

		case 5:
			printf("Liste des noms et salaires des employes operateurs: \n");
			afficheEmploye('O',tabEmployes,nbEmploye);
			break;

		case 6:
			printf("Liste des noms et salaires des employes programmeurs: \n");
			afficheEmploye('P',tabEmployes,nbEmploye);
			break;
	
		case 7: 
			{
			char nomEmploye[25];
			printf("\n Quel est le nom de l'employe (de la forme NOM PRENOM)? \n");
			scanf("%s",&nomEmploye);

			triage(tabEmployes,nbEmploye); // triage du tableau pour la recherche 
			int index = rechercheDichotomique(tabEmployes,nomEmploye,0,nbEmploye);

			// si l'employé est trouvé
			if (index != -1){
				char post = tabEmployes[index].poste;
				
				printf(" Cet employe est un ");
				switch(post){
					case 'P':
						printf("programmeur");
						break;
					case 'O':
						printf("operateur");
						break;
					case 'A':
						printf("analyste");
						break;
					case 'S':
						printf("secretaire");
						break;
				}
			}
			// si l'employé n'est pas trouvé
			else{
				printf(" Cet employe n'existe pas");
				break; }
			}

		case 8:
			break;
	}
}
