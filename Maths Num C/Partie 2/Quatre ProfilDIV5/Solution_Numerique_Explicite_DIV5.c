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
	float dt = (M_PI/(300.*c))/5;
	float t = 0.;
    float M = dx / (c * dt);
    float tn = (2. * M_PI)/dt;
	float P01[n];
	float P02[n];
	float P03[n];
	float P04[n];

	// commande permettant de générer un fichier
	FILE * pf;
	
	// Vecteur P_0
    float Pn[n];

	for(int i=0; i<nx; i++)
    {
		Pn[i]=sin(i*dx);
	}



	/* Print test Vecteur P_0 */

    for (int i = 0; i < nx; i++)
    {
        printf("%f\t", Pn[i]);
    }
    printf("\n");



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


	/* Print test Matrice B */

    for (int i = 0; i < nx; i++)
    {
        for (int j = 0; j < nx; j++)
        {
            printf("%f\t", B[i][j]);
        }
        printf("\n");
    }


	// Vecteur b
	float b[n];
	b[nx - 1] = sinf(10 * M_PI + c * t)/M;


	/* Print test Vecteur b */

    for (int i = 0; i < nx; i++)
    {
        printf("%f\t", b[i]);
    }
    printf("\n");


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
		
		// Calcul des éléments du vecteur pression P_n+1 au temps t = {0.5Pi, 1Pi, 1.5Pi, 2Pi}
		if((j >= (0.5*M_PI)/dt-1)&&(j <= (0.5*M_PI)/dt))
		{
			for(int i=0; i<nx; i++)
			{
				P01[i] = Pn[i];
			}
		}

		if((j >= (1.*M_PI)/dt-1)&&(j <= (1.*M_PI)/dt))
		{
			for(int i=0; i<nx; i++)
			{
				P02[i] = Pn[i];
			}
		}

		if((j >= (1.5*M_PI)/dt-1)&&(j <= (1.5*M_PI)/dt))
		{
			for(int i=0; i<nx; i++)
			{
				P03[i] = Pn[i];
			}
		}

		if((j >= (2.*M_PI)/dt-1)&&(j <= (2.*M_PI)/dt))
		{
			for(int i=0; i<nx; i++)
			{
				P04[i] = Pn[i];
			}
		}
	}

	// génération d'un fichier de format .txt
	pf =fopen ("graphes2div5.txt","w+");
	for(int i=0; i<nx; i++)
	{	
		x = i * dx;
		// affichage des valeurs de position (1 colonne) et de pression accoustique (4 colonnes)
		fprintf(pf,"%g %g %g %g %g\n",x,P01[i],P02[i],P03[i],P04[i]);
	}
	fclose(pf);
	return 0;
}