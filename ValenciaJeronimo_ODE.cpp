#include <iostream>
#include <math.h>

double t_min = 0.0;
double t_max= 20.0;
double N = 50000;
double h = (t_max-t_min)/N;

double q = 1.5;
double m = 2.5;

double derivadaX(double t, double x, double y, double z, double v_x, double v_y, double v_z, double B_x, double B_y, double B_z);
double derivadaY(double t, double x, double y, double z, double v_x, double v_y, double v_z, double B_x, double B_y, double B_z);
double derivadaZ(double t, double x, double y, double z, double v_x, double v_y, double v_z, double B_x, double B_y, double B_z);
double derivadaVX(double t, double x, double y, double z, double v_x, double v_y, double v_z, double B_x, double B_y, double B_z);
double derivadaVY(double t, double x, double y, double z, double v_x, double v_y, double v_z, double B_x, double B_y, double B_z);
double derivadaVZ(double t, double x, double y, double z, double v_x, double v_y, double v_z, double B_x, double B_y, double B_z);

int main()
{	
	double x[int((t_max-t_min)/h)];
	double y[int((t_max-t_min)/h)];
	double z[int((t_max-t_min)/h)];

	double v_x[int((t_max-t_min)/h)];
	double v_y[int((t_max-t_min)/h)];
	double v_z[int((t_max-t_min)/h)];

	double B_x[int((t_max-t_min)/h)];
	double B_y[int((t_max-t_min)/h)];
	double B_z[int((t_max-t_min)/h)];

	//Condiciones iniciales

	x[0] = 1.0;	
	y[0] = 0.0;
	z[0] = 0.0;

	v_x[0] = 0.0;
	v_y[0] = 2.0;
	v_z[0] = 1.0;
	
	for(int j=0; j<N; j++)
	{
		B_x[j] = 0.0;
		B_y[j] = 0.0;
		B_z[j] = 3.0;
	}

	double t = t_min;	
	std::cout << t << " " << x[0] << " " << y[0] << " " << z[0] << " " << v_x[0] << " " << v_y[0] << " " << v_z[0] << std::endl;	
	for(int i=1;i<N;i++)
	{	
		double k1,k2,k3,k4 = 0;

		//Runge-kutta para X
	
		k1 = h * derivadaX(t,x[i-1],y[i-1],z[i-1],v_x[i-1],v_y[i-1],v_z[i-1],B_x[i-1],B_y[i-1],B_z[i-1]);
		
		k2 = h * derivadaX(t+0.5*h,x[i-1]+0.5*k1,y[i-1]+0.5*k1,z[i-1]+0.5*k1,v_x[i-1]+0.5*k1,v_y[i-1]+0.5*k1,v_z[i-1]+0.5*k1,B_x[i-1]+0.5*k1,B_y[i-1]+0.5*k1,B_z[i-1]+0.5*k1);
		
		k3 = h * derivadaX(t+0.5*h,x[i-1]+0.5*k2,y[i-1]+0.5*k2,z[i-1]+0.5*k2,v_x[i-1]+0.5*k2,v_y[i-1]+0.5*k2,v_z[i-1]+0.5*k2,B_x[i-1]+0.5*k2,B_y[i-1]+0.5*k2,B_z[i-1]+0.5*k2);
		
		k4 = h * derivadaX(t+h,x[i-1]+k3,y[i-1]+k3,z[i-1]+k3,v_x[i-1]+k3,v_y[i-1]+k3,v_z[i-1]+k3,B_x[i-1]+k3,B_y[i-1]+k3,B_z[i-1]+k3);	
	
		x[i] = x[i-1] + (1.0/6.0)*(k1+2.0*k2+2.0*k3+k4);

		//Runge-kutta para Y
	
		k1,k2,k3,k4 = 0;		
		
		k1 = h * derivadaY(t,x[i-1],y[i-1],z[i-1],v_x[i-1],v_y[i-1],v_z[i-1],B_x[i-1],B_y[i-1],B_z[i-1]);
		
		k2 = h * derivadaY(t+0.5*h,x[i-1]+0.5*k1,y[i-1]+0.5*k1,z[i-1]+0.5*k1,v_x[i-1]+0.5*k1,v_y[i-1]+0.5*k1,v_z[i-1]+0.5*k1,B_x[i-1]+0.5*k1,B_y[i-1]+0.5*k1,B_z[i-1]+0.5*k1);
		
		k3 = h * derivadaY(t+0.5*h,x[i-1]+0.5*k2,y[i-1]+0.5*k2,z[i-1]+0.5*k2,v_x[i-1]+0.5*k2,v_y[i-1]+0.5*k2,v_z[i-1]+0.5*k2,B_x[i-1]+0.5*k2,B_y[i-1]+0.5*k2,B_z[i-1]+0.5*k2);
		
		k4 = h * derivadaY(t+h,x[i-1]+k3,y[i-1]+k3,z[i-1]+k3,v_x[i-1]+k3,v_y[i-1]+k3,v_z[i-1]+k3,B_x[i-1]+k3,B_y[i-1]+k3,B_z[i-1]+k3);	
	
		y[i] = y[i-1] + (1.0/6.0)*(k1+2.0*k2+2.0*k3+k4);
	
		//Runge-kutta para Z
	
		k1,k2,k3,k4 = 0;		
		
		k1 = h * derivadaZ(t,x[i-1],y[i-1],z[i-1],v_x[i-1],v_y[i-1],v_z[i-1],B_x[i-1],B_y[i-1],B_z[i-1]);
		
		k2 = h * derivadaZ(t+0.5*h,x[i-1]+0.5*k1,y[i-1]+0.5*k1,z[i-1]+0.5*k1,v_x[i-1]+0.5*k1,v_y[i-1]+0.5*k1,v_z[i-1]+0.5*k1,B_x[i-1]+0.5*k1,B_y[i-1]+0.5*k1,B_z[i-1]+0.5*k1);
		
		k3 = h * derivadaZ(t+0.5*h,x[i-1]+0.5*k2,y[i-1]+0.5*k2,z[i-1]+0.5*k2,v_x[i-1]+0.5*k2,v_y[i-1]+0.5*k2,v_z[i-1]+0.5*k2,B_x[i-1]+0.5*k2,B_y[i-1]+0.5*k2,B_z[i-1]+0.5*k2);
		
		k4 = h * derivadaZ(t+h,x[i-1]+k3,y[i-1]+k3,z[i-1]+k3,v_x[i-1]+k3,v_y[i-1]+k3,v_z[i-1]+k3,B_x[i-1]+k3,B_y[i-1]+k3,B_z[i-1]+k3);	
	
		z[i] = z[i-1] + (1.0/6.0)*(k1+2.0*k2+2.0*k3+k4);
	
		//Runge-kutta para V_x
	
		k1,k2,k3,k4 = 0;		
		
		k1 = h * derivadaVX(t,x[i-1],y[i-1],z[i-1],v_x[i-1],v_y[i-1],v_z[i-1],B_x[i-1],B_y[i-1],B_z[i-1]);
		
		k2 = h * derivadaVX(t+0.5*h,x[i-1]+0.5*k1,y[i-1]+0.5*k1,z[i-1]+0.5*k1,v_x[i-1]+0.5*k1,v_y[i-1]+0.5*k1,v_z[i-1]+0.5*k1,B_x[i-1]+0.5*k1,B_y[i-1]+0.5*k1,B_z[i-1]+0.5*k1);
		
		k3 = h * derivadaVX(t+0.5*h,x[i-1]+0.5*k2,y[i-1]+0.5*k2,z[i-1]+0.5*k2,v_x[i-1]+0.5*k2,v_y[i-1]+0.5*k2,v_z[i-1]+0.5*k2,B_x[i-1]+0.5*k2,B_y[i-1]+0.5*k2,B_z[i-1]+0.5*k2);
		
		k4 = h * derivadaVX(t+h,x[i-1]+k3,y[i-1]+k3,z[i-1]+k3,v_x[i-1]+k3,v_y[i-1]+k3,v_z[i-1]+k3,B_x[i-1]+k3,B_y[i-1]+k3,B_z[i-1]+k3);	
	
		v_x[i] = v_x[i-1] + (1.0/6.0)*(k1+2.0*k2+2.0*k3+k4);
	
		//Runge-kutta para V_y
	
		k1,k2,k3,k4 = 0;		
		
		k1 = h * derivadaVY(t,x[i-1],y[i-1],z[i-1],v_x[i-1],v_y[i-1],v_z[i-1],B_x[i-1],B_y[i-1],B_z[i-1]);
		
		k2 = h * derivadaVY(t+0.5*h,x[i-1]+0.5*k1,y[i-1]+0.5*k1,z[i-1]+0.5*k1,v_x[i-1]+0.5*k1,v_y[i-1]+0.5*k1,v_z[i-1]+0.5*k1,B_x[i-1]+0.5*k1,B_y[i-1]+0.5*k1,B_z[i-1]+0.5*k1);
		
		k3 = h * derivadaVY(t+0.5*h,x[i-1]+0.5*k2,y[i-1]+0.5*k2,z[i-1]+0.5*k2,v_x[i-1]+0.5*k2,v_y[i-1]+0.5*k2,v_z[i-1]+0.5*k2,B_x[i-1]+0.5*k2,B_y[i-1]+0.5*k2,B_z[i-1]+0.5*k2);
		
		k4 = h * derivadaVY(t+h,x[i-1]+k3,y[i-1]+k3,z[i-1]+k3,v_x[i-1]+k3,v_y[i-1]+k3,v_z[i-1]+k3,B_x[i-1]+k3,B_y[i-1]+k3,B_z[i-1]+k3);	
	
		v_y[i] = v_y[i-1] + (1.0/6.0)*(k1+2.0*k2+2.0*k3+k4);

		//Runge-kutta para V_z
	
		k1,k2,k3,k4 = 0;		
		
		k1 = h * derivadaVZ(t,x[i-1],y[i-1],z[i-1],v_x[i-1],v_y[i-1],v_z[i-1],B_x[i-1],B_y[i-1],B_z[i-1]);
		
		k2 = h * derivadaVZ(t+0.5*h,x[i-1]+0.5*k1,y[i-1]+0.5*k1,z[i-1]+0.5*k1,v_x[i-1]+0.5*k1,v_y[i-1]+0.5*k1,v_z[i-1]+0.5*k1,B_x[i-1]+0.5*k1,B_y[i-1]+0.5*k1,B_z[i-1]+0.5*k1);
		
		k3 = h * derivadaVZ(t+0.5*h,x[i-1]+0.5*k2,y[i-1]+0.5*k2,z[i-1]+0.5*k2,v_x[i-1]+0.5*k2,v_y[i-1]+0.5*k2,v_z[i-1]+0.5*k2,B_x[i-1]+0.5*k2,B_y[i-1]+0.5*k2,B_z[i-1]+0.5*k2);
		
		k4 = h * derivadaVZ(t+h,x[i-1]+k3,y[i-1]+k3,z[i-1]+k3,v_x[i-1]+k3,v_y[i-1]+k3,v_z[i-1]+k3,B_x[i-1]+k3,B_y[i-1]+k3,B_z[i-1]+k3);	
	
		v_z[i] = v_z[i-1] + (1.0/6.0)*(k1+2.0*k2+2.0*k3+k4);

		std::cout << t << " " << x[i] << " " << y[i] << " " << z[i] << " " << v_x[i] << " " << v_y[i] << " " << v_z[i] << std::endl;	

		t = t+h;
	}
		
	return 0;
}

double derivadaX(double t, double x, double y, double z, double v_x, double v_y, double v_z, double B_x, double B_y, double B_z)
{
	return v_x;
}

double derivadaY(double t, double x, double y, double z, double v_x, double v_y, double v_z, double B_x, double B_y, double B_z)
{
	return v_y;
}

double derivadaZ(double t, double x, double y, double z, double v_x, double v_y, double v_z, double B_x, double B_y, double B_z)
{
	return v_z;
}

double derivadaVX(double t, double x, double y, double z, double v_x, double v_y, double v_z, double B_x, double B_y, double B_z)
{
	return (q/m)*(v_y*B_z-v_z*B_y);
}

double derivadaVY(double t, double x, double y, double z, double v_x, double v_y, double v_z, double B_x, double B_y, double B_z)
{
	return (q/m)*(v_z*B_x-v_x*B_z);
}

double derivadaVZ(double t, double x, double y, double z, double v_x, double v_y, double v_z, double B_x, double B_y, double B_z)
{
	return (q/m)*(v_x*B_y-v_y*B_x);
}























