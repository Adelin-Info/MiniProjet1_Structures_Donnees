#include <stdlib.h>
#include <stdio.h>
#include <time.h>

// Q 2.4
// 1) Allocation dynamique d'un tableau 2D
void alloue_matrice(int ***M, int n) {
	int i,j;
	*M = (int**)malloc(n*sizeof(int*));   
	for (i=0; i<n; i++) {
		(*M)[i]=(int*)malloc(n*sizeof(int)); 
    }
}

// 2) Libération de la mémoire d'un tableau 2D
void desalloue_matrice(int **M, int n){
	int i;
	for (i=0; i<n; i++){
		free(M[i]);     
    }
	free(M); 
}

// 3) Remplissage de la matrice par des valeurs aléatoires entre 0 et V exclus
void remplir_matrice(int **M, int n, int V){
	srand(time(NULL));
	int i,j; 
	for (i=0; i<n; i++){ 
		for (j=0; j<n; j++){
			M[i][j]=rand()%V; 
        }
    }
}

// 4) Affichage
void afficher_matrice(int **M, int n){
	int i,j;
	for (i=0; i<n; i++){
		printf("[ ");
		for (j=0; j<n; j++){
			printf("%d ",M[i][j]);
		}
		printf("]\n");
	}
}

// ********************************************************

// Q 2.5
// 1) 
int premier_algo(int **M, int n){
	int i,j,k,l;
	for (i=0; i<n; i++){                                            
		for (j=0; j<n; j++){                                        
			for (k=0; k<n; k++){
				for (l=0; l<n; l++){                                // chaque case de la matrice parcourt toute la matrice 
					if ((M[i][j]==M[k][l]) && ((i!=k)&&(j!=l))){    // si des valeurs sont identiques et on des indices différents, on renvoie False qui correspond à 0
						return 0;                                   // sinon on renvoi True qui correspond à 1
					}				 
                }
            }
        }
    }
	return 1;
}

// 2)
int second_algo(int **M, int n, int V){
	int *tab=(int*)malloc(sizeof(int)*V);   // initialisation d'un tableau 1D de taille V, qui correspond à la borne maximale
	int i,j;
	for (i=0; i<n; i++){
		for (j=0; j<n; j++){
			if (tab[M[i][j]]==1){          // si la case d'indice M[i][j] (la valeur de la case ij de la matrice) est egale à 1, c'est-à-dire qu'on n'est déjà tombé sur cette valeur pendant notre parcours de la matrice
				free(tab);                 // alors on libère la mémoire occupé par le tableau et on renvoi False, correspondant à 0
				return 0;
			}
			else {
				tab[M[i][j]]=1;            // sinon on affecte 1 à la case d'indice M[i][j]
			}
		}
	}
	free(tab);                            // si toutes les valeurs sont différentes, on libère la mémoire occupé par tab et on renvoi True, correspondant à 1
	return 0;
}

// ****************************************************************

// Q 2.6
// 1)
void Algo1(int **M1, int **M2, int **P, int n){   
	int i,j,k;
	for(i=0; i<n; i++){
		for(j=0; j<n; j++){
			P[i][j]=0;                          // initialisation de la case à 0 après chaque case de P ayant obtenu leur valeur de la somme des produits
			for (k=0; k<n; k++){
				P[i][j]+=(M1[i][k])*(M2[k][j]);     //somme des produits entre les valeur de la ligne i de M1 et les valeur de la colonne j de M2
			}
		}
	}
}

// 2)
void Algo2(int **Msup, int **Minf, int **P, int n){
	int i,j,k;
	for (i=0; i<n; i++){
		for (j=0; j<n; j++){
			P[i][j]=0;                                     // initialisation de la case à 0 après chaque case ayant obtenu leur valeur de la somme des produits
			for (k=0; k<n; k++){
				if ((Minf[i][k]!=0)&&(Msup[k][j]!=0)){     // si les valeurs de Minf et Msup sont différent de 0 alors on fait la somme des produits 
					P[i][j]+=(Minf[i][k])*(Msup[k][j]);    // sinon on ne fait rien et on passe au tour suivant
				}
			}
		}
	}
}


int main(){
	
	// Initialisation des variables et des matrices dont on aura besoin pour les questions
	clock_t temps_initial;
	clock_t temps_final;
	double temps_cpu1;
	double temps_cpu2;
	srand(time(NULL));
	int v = 100;
	int res;
	int i,j;
	int **M;
	int **M1;
	int **M2;
	int **P;
	int **Minf;
	int **Msup;
	int n;
	printf("Choisissez la taille des matrices : ");
	scanf("%d",&n);
	
	// ************** Q 2.5 **************
	
	// Allocation, Remplissage et Affichage de M
	alloue_matrice(&M,n);
	remplir_matrice(M,n,v);
	printf("\n M : \n");
	afficher_matrice(M,n);
	printf("\n");
	
	// Teste si la matrice possède des valeurs différentes
	res=premier_algo(M,n);
	if (res==0){
		printf("Les valeurs de la matrice ne sont pas toutes différentes\n");
	}
	else{
		printf("Les valeurs de la matrice sont différentes\n");
	}
	
	res=second_algo(M,n,v);
	if (res==0){
		printf("Les valeurs de la matrice ne sont pas toutes différentes\n");
	}
	else{
		printf("Les valeurs de la matrice sont différentes\n");
	}
	
	//Calcule du temps pris par la fonction premier_algo 
	temps_initial = clock();                // Nombre de ticks consommé par le programme jusqu'ici
	premier_algo(M,n);
	temps_final = clock();                  // Nombre de ticks consommé par le programme jusqu'ici
	temps_cpu1 = ((double)(temps_final-temps_initial))/CLOCKS_PER_SEC;  // Conversion des ticks en secondes
	
	// Calcule du temps pris par la fonction second_algo 
	temps_initial = clock();
	second_algo(M,n,v);
	temps_final = clock();
	temps_cpu2 = ((double)(temps_final-temps_initial))/CLOCKS_PER_SEC;
	printf("%d %f %f\n",n,temps_cpu1,temps_cpu2);
	
	// ************** Q 2.5 **************
	
	// M1
	alloue_matrice(&M1,n);
	remplir_matrice(M1,n,v);
	printf("\nM1 : \n");
	afficher_matrice(M1,n);
	printf("\n");
	
	// M2
	alloue_matrice(&M2,n);
	remplir_matrice(M2,n,v);
	printf("\nM2 : \n");
	afficher_matrice(M2,n);
	printf("\n");

	// Msup dont les cases avec i>j sont égales à 0 sinon le reste ont des valeurs aléatoires entre 0 et V exclus
	alloue_matrice(&Msup,n);
	for(i=0; i<n; i++){
		for(j=0; j<n; j++){
			if (i>j){
				Msup[i][j]=0;
			}
			else {
				Msup[i][j]=rand()%v;
			}
		}
	}
	printf("\nMsup : \n");
	afficher_matrice(Msup,n);
	printf("\n");
	
	
	// Minf dont les cases avec i<j sont égales à 0 sinon le reste ont des valeurs aléatoires entre 0 et V exclus
	alloue_matrice(&Minf,n);
	for(i=0; i<n; i++){
		for(j=0; j<n; j++){
			if (i<j){
				Minf[i][j]=0;
			}
			else {
				Minf[i][j]=rand()%v;
			}
		}
	}
	printf("\nMinf : \n");
	afficher_matrice(Minf,n);
	printf("\n");
	
	// Produit de deux matrices et de deux matrices triangulaires
	alloue_matrice(&P,n);
	Algo1(M1,M2,P,n);
	printf("M1 * M2 : \n");
	afficher_matrice(P,n);
	printf("\n");
	
	Algo2(Msup,Minf,P,n);
	printf("Minf * Msup : \n");
	afficher_matrice(P,n);
	printf("\n");
	
	// Calcule du temps pris par la fonction Algo1 
	temps_initial = clock();
	Algo1(M1,M2,P,n);
	temps_final = clock();
	temps_cpu1 = ((double)(temps_final-temps_initial))/CLOCKS_PER_SEC;
		
	// Calcule du temps pris par la fonction Algo2 
	temps_initial = clock();
	Algo2(Msup,Minf,P,n);
	temps_final = clock();
	temps_cpu2 = ((double)(temps_final-temps_initial))/CLOCKS_PER_SEC;
	printf("%d %f %f\n",n,temps_cpu1,temps_cpu2);

	
	// Libération de la mémoire allouée pour les matrices 
	desalloue_matrice(M,n);
	desalloue_matrice(M1,n);
	desalloue_matrice(M2,n);
	desalloue_matrice(P,n);
	desalloue_matrice(Msup,n);
	desalloue_matrice(Minf,n);
	return 0;
}
			