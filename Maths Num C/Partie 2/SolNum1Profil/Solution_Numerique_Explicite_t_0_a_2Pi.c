#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#define ETU 8.0
#define n 108

int main()
{
	// déclaration des paramètres du problème
    float c = (1.+ETU)/10.;
	int nx = 100+ETU;
	float dx = (10.*M_PI)/nx;
    float x;
	float dt = M_PI/(300.*c);
	float t = 0.;
    float M = dx / (c * dt);
    float tn = (2. * M_PI)/dt;
	float Pcustom[n];

	// commande permettant de générer un fichier
	FILE * pf;
	
    // Lire la valeur que vous avez choisi pour calculer la pression à un point de t dans l'intervalle [0,2π]
    char str[100];
    float t_custom;

    printf("Entrez une valeur de temps t_custom entre 0 et 2π: ");
    scanf("%f", &t_custom);

    if((t_custom >= 0 )&&(t_custom <= 2 * M_PI))
    {
        // Vecteur initial P_0
        float Pn[n];

	    for(int i=0; i<nx; i++)
        {
		    Pn[i]=sin(i*dx);
	    }

	    // Matrice B
	    float B[n][n]={0};
	
	    for(int i=0; i<nx; i++)
	    {
		    B[i][i] = 1 - 1/M;			
	    }

	    for(int i=0; i<nx - 1; i++)
	    {
		    B[i][i+1] = 1/M;		
	    }

	    // Vecteur b
	    float b[n];
	    b[nx - 1] = sinf(10 * M_PI + c * t)/M;


	    // Vecteur pression P_n+1
	    float Pn1[n];

	    for(float j=0; j<=tn - 1; j++)
	    {
		    // Vecteur pression P_n+1 calculé à partir du vecteur pression P_n
		    for(int i=0; i<nx - 1; i++)
		    {
			    Pn1[i]= B[i][i]*Pn[i] + B[i][i+1]*Pn[i+1] + b[i];	
		    }

			// Dernier élément du vecteur pression P_n+1
		    Pn1[nx - 1]= B[nx - 1][nx - 1]*Pn[nx - 1] + b[nx - 1];

			// incrementation du temps t à chaque tour de boucle
		    t = t + dt;

			// recalcul du vecteur variable b
		    b[nx - 1] = sinf(10 * M_PI + c * t)/M;


		    // Affectation des éléments du vecteur P_n+1 au vecteur P_n
		    for(int i=0; i<nx; i++)
		    {
			    Pn[i]=Pn1[i];
		    }

			// Calcul des éléments du vecteur pression P_n+1 au temps t = t_custom
            if((j >= (t_custom)/dt-1)&&(j <= (t_custom)/dt))
		    {
			    for(int i=0; i<nx; i++)
			    {
				    Pcustom[i] = Pn[i];
			    }
		    }
        }

		// génération d'un fichier de format .txt
        pf =fopen ("graphescustomexplicit.txt","w+");
	    for(int i=0; i<nx; i++)
	        {	
	            x = i * dx;
				// affichage des valeurs de position (1 colonne) et de pression accoustique (1 colonne)
		        fprintf(pf,"%g %g\n",x,Pcustom[i]);
	        }
	    fclose(pf);
        }
    

    else
    {
        printf("Erreur, temps t_custom est en dehors de l'intervalle [0,2π]...\n");
        printf("Priez de recommencer en prennant temps t_custom dans l'intervalle [0,2π].\n");
    }
    return 0;
}
