#include <stdio.h>
#include <math.h>

/* 
* Retourne la somme des diviseurs propres d'un entier donné
*/
int sommeDiviseur(int nombre){	
	int i;
	int somme = 0; // somme initialisé 
	
    // boucle sur seulement sqrt du nombre, car boucle calcule plus d'un diviseur à la fois
	for(i=1; i < sqrt(nombre); ++i){
        if (nombre%i == 0){ // si est divisible
        	somme += i;     // on ajoute ce diviseur  

            if(i != 1){     // on peut ajouter un autre diviseur 
                somme += (nombre/i); 
            }
        }  
    } 
    return somme;	
}


/*
* Calcul la somme des diviseurs en utilisant un pointeur
* retourne rien
*/
void sommeDiviseurPointers(int nombre,int *ptr){
    *ptr = sommeDiviseur(nombre);
}


/* 
* Retourne 1 si si l'entier entré est parfait 
* Retourne 0 si l'entier entré n'est pas parfait
*/
int estParfait(int nombre){
    int somDiv = sommeDiviseur(nombre);
    
    if(somDiv==nombre){ // la condition d'être parfait
        return 1;
    }
    return 0;           // sinon pas parfait
}


/* 
* Affiche les diviseurs selon le modèle demandé
* prend en entré le nombre dont on veut les diviseurs et l'index (le combien ième nombre)
*/
void afficheDiviseur(int nombre, int index){
    int i;

    // le premier diviseur est 1
    printf("%d) %6d = 1", index, nombre);
	for(i=2; i < nombre; i++){
        if (nombre%i == 0){          
            printf(" + %d",i) ; 
        }  
    }
    printf("\n");
}


int main(){

    int tab[3] = {6,28,2004};
    int grandeur = sizeof(tab)/sizeof(tab[0]); // grandeur du tableau (3)
    int i;

    // Imprime la somme des diviseurs
    for(i=0; i < grandeur ; i++){
        int nb = tab[i];
        printf("\n %d\n \n",sommeDiviseur(nb));
    }


    int sum; // variable contenant la somme des diviseurs
    for(i=0; i < grandeur ; i++){    
        int nb = tab[i];
        sommeDiviseurPointers(nb,&sum);
        
        printf("%d\n \n",sum);
    }


    int index = 1;
    // Pour les nombre entre 5 et 10 000, affiche les nombres parfaits avec leur diviseurs
    for(i=5; i<10000; i++){
        if(estParfait(i)==1){  
            afficheDiviseur(i, index);
            index++;	   
        }  
    } 
}