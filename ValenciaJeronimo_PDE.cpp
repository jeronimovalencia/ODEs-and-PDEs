#include <iostream>
#include <math.h>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

//Discretización de las variables


int nt = 9000;
int M = nt/9;

double L = 1;


double c=300;
double x_min = 0;
double x_max = L;
double delta_x = 0.01;
const int nx = 100;

double xy[nx][nx];
double delta_t = (1.0/((5)*c))*delta_x;
double t_final = nt*delta_t;

int main()
{
	double u_futuro[nx][nx];
	double u_presente[nx][nx];
	double u_pasado[nx][nx];
	
	//Condicion inicial
	double u_inicial[nx][nx];
	
	string linea="";
  	ifstream inicial ("init.dat");		
	
	if (inicial.is_open())
	{
		int i=0;
		while (getline(inicial,linea))
		{	
			for(int j=0; j<nx;j++)
			{
				string dato = linea.substr(0, linea.find("  ")); 
				double datoDouble=0.0;
				stringstream data(dato);
				data >> datoDouble; 
				u_inicial[i][j] = datoDouble;
				linea.erase(0, linea.find("  ") + 2);
			}
			i++;
		}
		inicial.close();
	}

	//Condicion de frontera cerradas
	
	ofstream archivo;
	archivo.open("datosTamborCerradas.dat");	
	

	for(int i=0; i<nx; i++)
	{
		u_futuro[0][i]=0;
		u_futuro[nx-1][i]=0;
		u_futuro[i][0]=0;
		u_futuro[i][nx-1]=0;
	}

	for(int m=0;m<nx;m++)
	{
		for(int k=0; k<nx; k++)
		{
			u_pasado[m][k] = u_inicial[m][k];
		}
	}

	//Diferencias finitas
	for(int i=1;i<nx-1;i++)
	{
		for(int k=1; k<nx-1;k++)
		{
			u_presente[i][k] = pow((delta_t/delta_x),2)*pow(c,2)*(u_pasado[i+1][k]-2*u_pasado[i][k]+u_pasado[i-1][k]) + pow((delta_t/delta_x),2)*pow(c,2)*(u_pasado[i][k+1]-2*u_pasado[i][k]+u_pasado[i][k-1]) + 2*u_pasado[i][k] - u_pasado[i][k];
		}
	}

	for(int t=0;t<=nt;t++)
	{
		for(int i=1; i<nx-1;i++)
		{
			for(int k=1;k<nx-1;k++)
			{
				u_futuro[i][k] = pow((delta_t/delta_x),2)*pow(c,2)*(u_presente[i+1][k]-2.0*u_presente[i][k]+u_presente[i-1][k]) + pow((delta_t/delta_x),2)*pow(c,2)*(u_presente[i][k+1]-2.0*u_presente[i][k]+u_presente[i][k-1])  + 2.0*u_presente[i][k] - u_pasado[i][k];
			}
		}		
		
		for(int l=0;l<nx;l++)
		{
			for(int m=0; m<nx; m++)
			{
				u_pasado[l][m] = u_presente[l][m];
				u_presente[l][m] = u_futuro[l][m];	
			}
		}

		
		if(t%M == 0)
		{
			for(int m=0; m<nx; m++)
			{
				archivo << u_presente[nx/2][m] << " ";	
			}
			archivo << std::endl;
		}
	}

	for(int l=0;l<nx;l++)
	{
		for(int m=0; m<nx; m++)
		{
			archivo << u_presente[l][m] << " ";	
		}
		archivo << std::endl; 
	}

	//Condicion de frontera abiertas
	
	ofstream archivo2;
	archivo2.open("datosTamborAbiertas.dat");

	ofstream archivo3;
	archivo3.open("datosTamborInicial.dat");
	
	for(int m=0;m<nx;m++)
	{
		for(int k=0; k<nx; k++)
		{
			u_pasado[m][k] = u_inicial[m][k];
		}
	}

	//Diferencias finitas
	
	//Cargar la primera condición presente
	for(int i=1;i<nx-1;i++)
	{
		for(int k=1; k<nx-1;k++)
		{
			u_presente[i][k] = pow((delta_t/delta_x),2)*pow(c,2)*(u_pasado[i+1][k]-2*u_pasado[i][k]+u_pasado[i-1][k]) + pow((delta_t/delta_x),2)*pow(c,2)*(u_pasado[i][k+1]-2*u_pasado[i][k]+u_pasado[i][k-1]) + 2*u_pasado[i][k] - u_pasado[i][k];
				
		}
	}

	for(int p=0; p<nx;p++)
	{	
		u_presente[0][p] = u_presente[1][p];
		u_presente[nx-1][p] = u_presente[nx-2][p];
		u_presente[p][0] = u_presente[p][1];
		u_presente[p][nx-1] = u_presente[p][nx-2];	

	}

	//Método

	for(int t=0;t<=nt;t++)
	{
			for(int i=1;i<nx-1;i++)
			{
				for(int k=1; k<nx-1;k++)
				{
					u_futuro[i][k] = pow((delta_t/delta_x),2)*pow(c,2)*(u_presente[i+1][k]-2*u_presente[i][k]+u_presente[i-1][k]) + pow((delta_t/delta_x),2)*pow(c,2)*(u_presente[i][k+1]-2*u_presente[i][k]+u_presente[i][k-1]) + 2*u_presente[i][k] - u_pasado[i][k];	
				}
			}

			for(int p=0; p<nx;p++)
			{	
				u_futuro[0][p] = u_futuro[1][p];
				u_futuro[nx-1][p] = u_futuro[nx-2][p];
				u_futuro[p][0] = u_futuro[p][2];
				u_futuro[p][nx-1] = u_futuro[p][nx-2];	

			}

			for(int i=0; i<nx;i++)
			{
				for(int j=0; j<nx;j++)
				{
					u_pasado[i][j] = u_presente[i][j];
					u_presente[i][j] = u_futuro[i][j];
				}
			}

			if(t%M == 0)
			{
				for(int m=0; m<nx; m++)
				{
					archivo2 << u_presente[nx/2][m] << " ";	
				}
				archivo2 << std::endl;
			}
	}

	for(int l=0;l<nx;l++)
	{
		for(int m=0; m<nx; m++)
		{
			archivo2 << u_presente[l][m] << " ";
			archivo3 << u_inicial[l][m] << " ";	
		}
		archivo2 << std::endl; 
		archivo3 << std::endl; 
		
	}
	
	return 0;
}


















