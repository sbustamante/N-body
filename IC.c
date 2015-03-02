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
	struct cluster galaxy[1];
	FILE *Data;
	char trash[NMAX2];

	//Recoleccion de datos de entrada
	Data=fopen("parametros.conf","r");
	for(i=0;i<9;i++)
		fscanf(Data,"%lf\t%s\n",&IC[i],trash);
	fclose(Data);

	
	//Cubic Uniform distribution (with random velocities)
	switch( IC[TYP_DIS] == 0 )
	    uniform_cube(galaxy, IC);
	//Spherical Uniform distribution (with random velocities)
	switch( IC[TYP_DIS] == 1 )
	    uniform_sphere(galaxy, IC);
	//Disk Uniform Distribution (with random velocities)
	switch( IC[TYP_DIS] == 2 )
	    uniform_disk(galaxy, IC);
	switch( IC[TYP_DIS] == 3 )
	//Disk Uniform distribution (with circular velocities)
	uniform_disk_vel_ang(galaxy, IC);
	
	
	//Output datas
	Data=fopen("datos.in","w");
	for(i=0;i<IC[N_PART];i++)
		fprintf(Data,"%lf %lf %lf %lf %lf %lf %lf %lf\n"\
		, galaxy[0].prts[i].m, galaxy[0].prts[i].r[X], galaxy[0].prts[i].r[Y], galaxy[0].prts[i].r[Z]\
		, galaxy[0].prts[i].v[X], galaxy[0].prts[i].v[Y], galaxy[0].prts[i].v[Z], galaxy[0].prts[i].eps);
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
