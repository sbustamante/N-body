#include <allvars.h>

/********************************************************************
 NOMBRE:     main                                                  
 FUNCION:    lee datos de entrada y genera distribucion	    
 ARGUMENTOS: --                                                    
 RETORNA:    0							    
 LOG:        15/09/2009    Creacion                                
********************************************************************/
int main(void){

	double IC[NMAX1];
	int i;
	struct particle stars[NMAX];
	FILE *Data;

	//Recoleccion de datos de entrada
	Data=fopen("parametros.conf","r");
	for(i=0;i<9;i++)
		fscanf(Data,"%lf\t%s\n",&IC[i],trash);
	fclose(Data);

	
	//Cubic Uniform distribution (with random velocities)
	switch( IC[TYP_DIS] == 0 )
	    uniform_cube(stars, IC);
	//Spherical Uniform distribution (with random velocities)
	switch( IC[TYP_DIS] == 1 )
	    uniform_sphere(stars, IC);
	//Disk Uniform Distribution (with random velocities)
	switch( IC[TYP_DIS] == 2 )
	    uniform_disk(stars, IC);
	switch( IC[TYP_DIS] == 3 )
	//Disk Uniform distribution (with circular velocities)
	uniform_disk_vel_ang(stars, IC);
	
	
	//Output datas
	Data=fopen("datosin.dat","w");
	for(i=0;i<IC[N_PART];i++)
		fprintf(Data,"%lf %lf %lf %lf %lf %lf %lf %lf\n"\
		, stars[i].m, stars[i].r[X], stars[i].r[Y], stars[i].r[Z]\
		, stars[i].v[X], stars[i].v[Y], stars[i].v[Z], stars[i].eps);
	fclose(Data);

	return 0;
}

/*
0    10000	Number_of_Particles
1	1	Coordinate_Distribution_1
2	1	Coordinate_Distribution_2
3	1	Coordinate_Distribution_3
4	1	Velocity_Maxim
5	1	Minim_Mass--(Range)
6	5	Maxim_Mass--(Range)
7	0.1	Minim_Softening_Parameter--(Range)
8	0.1	Maxim_Softening_Parameter--(Range)*/
