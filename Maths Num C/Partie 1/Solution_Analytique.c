#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#define ETU 8.0


int main ()
{
	// déclaration des paramètres du problème
	float c=(1.+ETU)/10.;
	float t0= 0.5*M_PI,t1=M_PI,t2=1.5*M_PI,t3=2.*M_PI;
	int nx=100+ETU;
	float dx=(10.*M_PI)/nx;
	float x;

	// commande permettant de générer un fichier
	FILE * pf;

	// génération d'un fichier de format .txt
	pf= fopen("graphes1.txt","w+");
	for (int i=0; i<nx; i++)
	{
		x=i*dx;
		// affichage des valeurs de position (1 colonne) et des pressions accoustiques (4 colonnes)
		fprintf(pf,"%g %g %g %g %g\n",x,sin(x+c*t0),sin(x+c*t1),sin(x+c*t2),sin(x+c*t3));
	}
	fclose(pf);
	return 0;
}