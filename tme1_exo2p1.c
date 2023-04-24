#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>


// Q 2.1
// 1) Allocation dynamique d'un tableau 1D
void allouer_tableau(int **T, int n){
    *T = (int*)malloc(sizeof(int)*n);
}

//2) Libération de la mémoire d'un tableau 1D
void desallouer_tableau(int *T){
	free(T);
}

//3) Remplissage du tableau par des nombres aléatoire compris entre 0 et V exclus
void remplir_tableau(int *T, int n, int V){
	srand(time(NULL));
	int i;
	for(i=0; i<n; i++){
		T[i] = rand()%V; 
	}
}

//4) Affichage
void afficher_tableau(int *T, int n){
	printf("[ ");
	int i;
	for (i=0; i<n; i++){
		printf("%d ",T[i]);
	}
	printf("]");
}

// ***************************************************************

// Q 2.2
// 1)
int Algo1(int *T, int n){
	int s = 0;              //initialisation de la variable somme qui va stocker la somme des carrés des différences entre les éléments du tableau
	int i,j;
	for (i=0; i<n; i++){           // 2 boucles for pour parcourir le tableau prenant les éléments deux par deux  
		for (j=0; j<n; j++){
			s+=pow((T[i]-T[j]),2);
		}
	}
	return s; // renvoi de la somme
}

// 2)
int Algo2(int *T, int n){
	int s1=0;               // initialisation de la variable somme 1 qui va stocker la somme des éléments du tableau au carré
	int s2=0;               // initialisation de la variable somme 2 qui va stocker la somme des éléments du tableau
	int i;
	for (i=0; i<n; i++){    // boucle pour parcourir le tableau
		s1+= pow(T[i],2);
		s2+= T[i];
	}
	return 2*n*s1-2*pow(s2,2); // renvoi de la valeur obtenue grâce à la formule trouver à la question 2.2
}

int main(){
	
	// Initialisation des variables et du tableau qu'on va utiliser au cours de l'exercice
	clock_t temps_initial;
	clock_t temps_final;
	double temps_cpu1;
	double temps_cpu2;
	int v = 100;
	int n;
	int *T;
	printf("Choisissez la taille du tableau : ");
	scanf("%d",&n);
	allouer_tableau(&T,n);
	remplir_tableau(T,n,v);
	afficher_tableau(T,n);
	
	printf("\nLa somme par l'Algo1 : %d\n",Algo1(T,n));
	printf("La somme par l'Algo2 : %d\n",Algo2(T,n));
	
	// Calcule du temps pris par la fonction Algo1
	temps_initial = clock();   // Nombre de ticks consommé par le programme jusqu'ici  
	Algo1(T,n);
	temps_final = clock();     // Nombre de ticks consommé par le programme jusqu'ici
	temps_cpu1 = ((double)(temps_final - temps_initial))/CLOCKS_PER_SEC;    // Conversion des ticks en secondes
	
	// Calcule du temps pris par la fonction Algo2
	temps_initial = clock();
	Algo2(T,n);
	temps_final = clock();
	temps_cpu2 = ((double)(temps_final - temps_initial))/CLOCKS_PER_SEC;
	printf("%d %f %f\n",n,temps_cpu1,temps_cpu2);
	
	// Libération en mémoire du tableau
	desallouer_tableau(T);
	return 0;
}