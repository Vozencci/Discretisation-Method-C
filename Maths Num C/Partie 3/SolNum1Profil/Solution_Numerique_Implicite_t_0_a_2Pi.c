#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#define ETU 8.0
#define n 108

int nn;
void display_vector( float x[n])
{
	int i;
	for (i=0;i<nn;i++) printf("%1f\n",x[i]);
}
void display_matrix(float A[n][n] , int nn)
{
	int i,j;
	for (i=0;i<nn;i++) 
    {
		for (j=0;j<nn;j++) 
        {
			printf("%f\t",A[i][j]);
		}
		printf("\n");
	}
}
void Matrix_U_Remontee( float U[n][n] , float y[n], float x[n],int nn) 
{
	int i,j;
	for(i=n-1;i>=0;i--)
	{
		float sum=0.;
		for(j=n-1;j>i;j--)
		{
			sum = sum+y[j]*U[i][j];
		}
		y[i]=(x[i]-sum)/U[i][i];
	} 
}	

void Matrix_L_Descente( float L[n][n] , float x[n], float b[n],int nn) 
{
	int i,j;
	for(i=0;i<n;i++)
	{
		float sum=0.;
		for(j=0;j<i;j++)
		{
			sum = sum+x[j]*L[i][j];
		}
		x[i]=(b[i]-sum)/L[i][i];
	} 
}

void Matrix_LU_factorization( float A[n][n] , float L[n][n] , float U[n][n], int nn)
{
    int i,j,k;
    for(j=0;j<n;j++)
    {
        L[j][j]=1;
        for(i=0;i<=j;i++)
        {
            float somme=0;
            for(k=0;k<=i-1;k++)  
            {
                somme = somme+ L[i][k]*U[k][j];
            }
            U[i][j]= A[i][j]-somme;
        }
        for(i=j+1;i<n;i++)
        {
            float somme2=0;
            for(k=0;k<=j-1;k++)
            {
                somme2 = somme2+ L[i][k]*U[k][j];
            }          
            L[i][j]= (A[i][j]-somme2)/U[j][j];
        }
    }
}

int main()
{
    float speed = (1.+ETU)/10.;
	int nx = 100+ETU;
	float dx = (10.*M_PI)/nx;
    float x;
	float dt = M_PI/(300.*speed);
	float t = 0.;
    float M = dx / (speed * dt);
    float tn = (2. * M_PI)/dt;
	float Pcustom[n];
	FILE * pf;
	
    // Lire la valeur que vous avez choisi pour calculer la pression à un point de t dans l'intervalle [0,2π]
    char str[100];
    float t_custom;

    printf("Entrez une valeur de temps t_custom entre 0 et 2π: ");
    scanf("%f", &t_custom);

    if((t_custom >= 0 )&&(t_custom <= 2 * M_PI))
    {
        // Vecteur P0
    	float Pn[n];

		for(int i=0; i<nx; i++)
			{
				Pn[i]=sin(i*dx);
			}

		/* Print test Vecteur P0 */

    	for (int i = 0; i < nx; i++)
    		{
    		    printf("%f\t", Pn[i]);
    		}
   		 printf("\n");



		// Matrice C
		float C[n][n]={0};
	
		for(int i=0; i<nx; i++)
			{
				C[i][i] = 1 + 1/M;			
			}

		for(int i=0; i<nx - 1; i++)
			{
				C[i][i+1] = - 1/M;		
			}


		/* Print test Matrice C */

    	for (int i = 0; i < nx; i++)
    		{
       			for (int j = 0; j < nx; j++)
				   {
        				printf("%f\t", C[i][j]);
        			}
        		printf("\n");
    		}


		// Vecteur c
		float c[n];
		c[nx - 1] = sinf(10 * M_PI + speed * t)/M;


		/* Print test Vecteur c */

    	for (int i = 0; i < nx; i++)
    		{
    			printf("%f\t", c[i]);
    		}
    	printf("\n");

    	// factoriser en LU
		float L[n][n];
		float U[n][n];
		Matrix_LU_factorization(C,L,U,nx);


		// Vecteur P1
		float Pn1[n];

		for(float j=0; j<=tn - 1; j++)
			{
				float y[nx];
				Pn[nx - 1]=Pn[nx - 1] + c[nx - 1]; // condition limite en x = 10pi
    			t = t + dt;
				c[nx - 1] = sinf(10 * M_PI + speed * t)/M;
				Matrix_L_Descente(L,y,Pn,nx); 
				Matrix_U_Remontee(U,Pn1,y,nx);

			// P0 prend valeur de P1
			for(int i=0; i<nx; i++)
				{
					Pn[i]=Pn1[i];
				}

        	if((j >= (t_custom)/dt-1)&&(j <= (t_custom)/dt))
	    	{
		    	for(int i=0; i<nx; i++)
		    	{
					Pcustom[i] = Pn[i];
		    	}
			}

        	pf =fopen ("graphescustomimplicit.txt","w+");
	    	for(int i=0; i<nx; i++)
	        	{	
	            	x = i * dx;
		        	fprintf(pf,"%g %g\n",x,Pcustom[i]);
	        	}
	    	fclose(pf);
    	}
	}

    else
    {
        printf("Erreur, temps t_custom est en dehors de l'intervalle [0,2π]...\n");
        printf("Priez de recommencer en prennant temps t_custom dans l'intervalle [0,2π].\n");
    }
    return 0;
}
