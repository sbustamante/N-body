#include <allvars.h>


/********************************************************************
 NOMBRE:     initial_conditions
 FUNCION:    genera condiciones iniciales para distribucion en un 
	     archivo de salida.
 ARGUMENTOS: estructura 'cluster' para inicializar las particulas
	     en la distribucion, archivo de parametros.Nombre de 
	     archivo de salida
 RETORNA:    0							    
 LOG:        21/01/2011    Creacion                                
********************************************************************/
int initial_conditions( struct cluster galaxy[1], 
			double prmt[NMAX2], 
			char filename[] )
{  
    int i;
    char distribution[10];
    FILE *file;
    //Cubo Uniforme
    if( prmt[TYP_DIS]==0 ){
	uniform_cube( galaxy, prmt );
	sprintf( distribution, "uniform_cube" );}
    
     //Esfera Uniforme
     if( prmt[TYP_DIS]==1 ){
 	uniform_spheroid( galaxy, prmt );
 	sprintf( distribution, "uniform_spheroid" );}
    
    //Disco Uniforme
    if( prmt[TYP_DIS]==2 ){
	uniform_disk( galaxy, prmt );
	sprintf( distribution, "uniform_disk" );}

    //Galaxy Model 1
    if( prmt[TYP_DIS]==3 ){
	galaxy_model_1( galaxy, prmt );
	sprintf( distribution, "galaxy_model_1" );}

    //Galaxy Model 1
    if( prmt[TYP_DIS]==4 ){
	collision( galaxy, prmt );
	sprintf( distribution, "collision" );}
	
    printf( "  * Condiciones iniciales generadas!\n");
    
    //Galaxy Model 2
    if( prmt[TYP_DIS]==5 ){
	galaxy_model_2( galaxy, prmt );
	sprintf( distribution, "galaxy_model_2" );}

    //Impresion en archivo
    file = fopen( filename, "w" );
    fprintf( file, "#Masa\t\tX\t\tY\t\tZ\t\tVx\t\tVy\t\tVz\t\tSoft\t\tInter\tP0\tP1\tP2\tP3\tP4\tP5\tP6\tP7\tP8\tP9\n" );
    for( i=0; i<galaxy[0].N; i++ )
	fprintf( file,"%lf\t%lf\t%lf\t%lf\t%lf\t%lf\t%lf\t%lf\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n", 
		 galaxy[0].prts[i].m, 
		 galaxy[0].prts[i].r[0], galaxy[0].prts[i].r[1], galaxy[0].prts[i].r[2],
		 galaxy[0].prts[i].v[0], galaxy[0].prts[i].v[1], galaxy[0].prts[i].v[2], 
		 galaxy[0].prts[i].eps, galaxy[0].prts[i].inter,
		 galaxy[0].prts[i].compa[0], galaxy[0].prts[i].compa[1],
		 galaxy[0].prts[i].compa[2], galaxy[0].prts[i].compa[3],
		 galaxy[0].prts[i].compa[4], galaxy[0].prts[i].compa[5],
 		 galaxy[0].prts[i].compa[6], galaxy[0].prts[i].compa[7],
 		 galaxy[0].prts[i].compa[8], galaxy[0].prts[i].compa[9]);
	  
    fclose(file);

    printf( "\tDistribución: %s\n\tArchivo de salida: '%s'\n", 
	    distribution, filename );
    return 0;
}


/********************************************************************
 NOMBRE:     uniform_cube                                           
 FUNCION:    genera una distribucion uniforme sobre un cubo de     
             lados dados                                           
 ARGUMENTOS: estructura 'cluster' para retorno de posicion y      
	     velocidad de cada particula y arreglo con parametros 
 COORDENADAS:							    
	     *Coord 1 -- Lado x
	     *Coord 2 -- Lado y
	     *Coord 3 -- Lado z
	     *Veloc 1 -- Magnitud maxima velocidad
	     *Veloc 2 -- NULL
	     *Veloc 3 -- NULL                 			    
 RETORNA:    0							    
 LOG:        15/09/2009    Creacion           
	     26/01/2011	   Implementacion estructura cluster
********************************************************************/
int uniform_cube( struct cluster galaxy[1], 
		  double prmt[NMAX2] )
{
    int i,j;

    srand48(time(NULL));
    //Asignacion de posiciones y velocidades
    for( i=0; i<galaxy[0].N; i++ ){
		
	//Masas
	galaxy[0].prts[i].m = prmt[MAS_MIN]+drand48()*(prmt[MAS_MAX]-prmt[MAS_MIN]);
	
        //Posiciones
	galaxy[0].prts[i].r[X] = drand48()*prmt[COOR_1];
	galaxy[0].prts[i].r[Y] = drand48()*prmt[COOR_2];
	galaxy[0].prts[i].r[Z] = drand48()*prmt[COOR_3];

	//Velocidades
	do{
	galaxy[0].prts[i].v[X] = (1-2*drand48())*prmt[VEL_1];
	galaxy[0].prts[i].v[Y] = (1-2*drand48())*prmt[VEL_1];
	galaxy[0].prts[i].v[Z] = (1-2*drand48())*prmt[VEL_1];
	}while( galaxy[0].prts[i].v[X]*galaxy[0].prts[i].v[X]
	+ galaxy[0].prts[i].v[Y]*galaxy[0].prts[i].v[Y]
	+ galaxy[0].prts[i].v[Z]*galaxy[0].prts[i].v[Z] > prmt[VEL_1]*prmt[VEL_1] );

	//Parametro de suavizado
	galaxy[0].prts[i].eps = prmt[SOF_MIN]+drand48()*(prmt[SOF_MAX]-prmt[SOF_MIN]);
	
	//Interacciones de cada particula
	galaxy[0].prts[i].inter = -1;
	
	for( j=0; j<10; j++ )
	    galaxy[0].prts[i].compa[j] = 0;}
	
		
    return 0;
}


/********************************************************************
 NOMBRE:     uniform_spheroid                    
 FUNCION:    genera una distribucion uniforme sobre un cubo de     
             lados dados                                           
 ARGUMENTOS: estructura 'cluster' para retorno de posicion y      
	     velocidad de cada particula y arreglo con parametros 
 COORDENADAS:							    
	     *Coord 1 -- Radio x
	     *Coord 2 -- Radio y
	     *Coord 3 -- Radio z
	     *Veloc 1 -- Magnitud maxima velocidad
	     *Veloc 2 -- NULL
	     *Veloc 3 -- NULL
 RETORNA:    0							    
 LOG:        15/09/2009    Creacion             
 	     26/01/2011	   Implementacion estructura cluster
********************************************************************/                                          
int uniform_spheroid( struct cluster galaxy[1], 
		      double prmt[NMAX2] )
{
    int i,j;

    srand48(time(NULL));

    //Asignacion de posiciones y velocidades
    for( i=0; i<galaxy[0].N; i++ ){
		
	//Masas
	galaxy[0].prts[i].m = prmt[MAS_MIN]+drand48()*(prmt[MAS_MAX]-prmt[MAS_MIN]);
	
        //Posiciones
	do{
	galaxy[0].prts[i].r[X] = (1-2*drand48())*prmt[COOR_1];
	galaxy[0].prts[i].r[Y] = (1-2*drand48())*prmt[COOR_2];
	galaxy[0].prts[i].r[Z] = (1-2*drand48())*prmt[COOR_3];
	}while( 
	galaxy[0].prts[i].r[X]*galaxy[0].prts[i].r[X]/(prmt[COOR_1]*prmt[COOR_1])
	+ galaxy[0].prts[i].r[Y]*galaxy[0].prts[i].r[Y]/(prmt[COOR_2]*prmt[COOR_2])
	+ galaxy[0].prts[i].r[Z]*galaxy[0].prts[i].r[Z]/(prmt[COOR_3]*prmt[COOR_3]) > 1 );

	//Velocidades
	do{
	galaxy[0].prts[i].v[X] = (1-2*drand48())*prmt[VEL_1];
	galaxy[0].prts[i].v[Y] = (1-2*drand48())*prmt[VEL_1];
	galaxy[0].prts[i].v[Z] = (1-2*drand48())*prmt[VEL_1];
	}while( galaxy[0].prts[i].v[X]*galaxy[0].prts[i].v[X]
	+ galaxy[0].prts[i].v[Y]*galaxy[0].prts[i].v[Y]
	+ galaxy[0].prts[i].v[Z]*galaxy[0].prts[i].v[Z] > prmt[VEL_1]*prmt[VEL_1] );

	//Parametro de suavizado
	galaxy[0].prts[i].eps = prmt[SOF_MIN]+drand48()*(prmt[SOF_MAX]-prmt[SOF_MIN]);
	
	//Interacciones de cada particula
	galaxy[0].prts[i].inter = -1;
	
	for( j=0; j<10; j++ )
	    galaxy[0].prts[i].compa[j] = 0;}
		
    return 0;
}


/********************************************************************
 NOMBRE:     uniform_disk                                           
 FUNCION:    genera una distribucion uniforme sobre un disco       
 ARGUMENTOS: estructura 'cluster' para retorno de posicion y      
	     velocidad de cada particula y arreglo con parametros 
 COORDENADAS:							    
	     *Coord 1 -- Radio x
	     *Coord 2 -- Radio y
	     *Coord 3 -- Altura z
	     *Veloc 1 -- Magnitud maxima velocidad plano x-y
	     *Veloc 2 -- Magnitud maxima velocidad dirección z
	     *Veloc 3 -- NULL
 RETORNA:    0							    
 LOG:        15/09/2009    Creacion             
 	     26/01/2011	   Implementacion estructura cluster
********************************************************************/
int uniform_disk( struct cluster galaxy[1], 
		  double prmt[NMAX2] )
{
    int i,j;

    srand48(time(NULL));
    //Asignacion de posiciones y velocidades
    for( i=0; i<galaxy[0].N; i++ ){
		
	//Masas
	galaxy[0].prts[i].m = prmt[MAS_MIN]+drand48()*(prmt[MAS_MAX]-prmt[MAS_MIN]);
	
        //Posiciones
	do{
	galaxy[0].prts[i].r[X] = (1-2*drand48())*prmt[COOR_1];
	galaxy[0].prts[i].r[Y] = (1-2*drand48())*prmt[COOR_2];
	}while( 
	galaxy[0].prts[i].r[X]*galaxy[0].prts[i].r[X]/(prmt[COOR_1]*prmt[COOR_1])
	+ galaxy[0].prts[i].r[Y]*galaxy[0].prts[i].r[Y]/(prmt[COOR_2]*prmt[COOR_2]) > 1 );
	
	galaxy[0].prts[i].r[Z] = (1-2*drand48())*prmt[COOR_3]/2.;

	//Velocidades
	do{
	galaxy[0].prts[i].v[X] = (1-2*drand48())*prmt[VEL_1];
	galaxy[0].prts[i].v[Y] = (1-2*drand48())*prmt[VEL_1];
	galaxy[0].prts[i].v[Z] = (1-2*drand48())*prmt[VEL_2];
	}while( (galaxy[0].prts[i].v[X]*galaxy[0].prts[i].v[X]
	+ galaxy[0].prts[i].v[Y]*galaxy[0].prts[i].v[Y])/(prmt[VEL_1]*prmt[VEL_1])
	+ galaxy[0].prts[i].v[Z]*galaxy[0].prts[i].v[Z]/(prmt[VEL_2]*prmt[VEL_2]) > 1.0 );

	//Parametro de suavizado
	galaxy[0].prts[i].eps = prmt[SOF_MIN]+drand48()*(prmt[SOF_MAX]-prmt[SOF_MIN]);
	
	//Interacciones de cada particula
	galaxy[0].prts[i].inter = -1;
	for( j=0; j<10; j++ )
	    galaxy[0].prts[i].compa[j] = 0;}
	
		
    return 0;
}


/********************************************************************
 NOMBRE:     galaxy_model_1                                           
 FUNCION:    genera una distribucion de anillo con particula en el 
	     centro que representa nucleo de galaxia, cada particula
	     solo interactua con la central y estan en orbita 
	     circular.
 ARGUMENTOS: estructura 'cluster' para retorno de posicion y      
	     velocidad de cada particula y arreglo con parametros 
 COORDENADAS:							    
	     *Coord 1 -- Radio
	     *Coord 2 -- Numero de Anillos
	     *Coord 3 -- NULL
	     *Veloc 1 -- NULL
	     *Veloc 2 -- NULL
	     *Veloc 3 -- NULL
	     *Maxim Mass -- Masa nucleo
	     *Minim Masa -- Masa estrellas
 RETORNA:    0							    
 LOG:        15/09/2009    Creacion             
 	     26/01/2011	   Implementacion estructura cluster
********************************************************************/
int galaxy_model_1( struct cluster galaxy[1], 
		    double prmt[NMAX2] )
{
    int i, j, k;
    int spr;
    
    double r, th, v_cir;
    
    spr = prmt[N_PART]/(1.0*prmt[COOR_2]);

    //Particula central
    galaxy[0].prts[0].m = prmt[MAS_MAX];
    galaxy[0].prts[0].r[X] = 0;
    galaxy[0].prts[0].r[Y] = 0;
    galaxy[0].prts[0].r[Z] = 0;
    
    galaxy[0].prts[0].v[X] = 0;
    galaxy[0].prts[0].v[Y] = 0;
    galaxy[0].prts[0].v[Z] = 0;
    
    //Asignacion de posiciones y velocidades
    k = 1;
    for( i=1; i<=prmt[COOR_2]; i++ ){
	r = prmt[COOR_1]*i/(1.0*prmt[COOR_2]);
	v_cir = sqrt( GC*prmt[MAS_MAX]/r );
	for( j=0; j<spr; j++ ){
	    //Masas
	    galaxy[0].prts[k].m = prmt[MAS_MIN];
	    th = 2*M_PI*j/(1.0*spr);
	    
	    galaxy[0].prts[k].r[X] = r*cos( th );
	    galaxy[0].prts[k].r[Y] = r*sin( th );
	    galaxy[0].prts[k].r[Z] = 0;
	    
	    galaxy[0].prts[k].v[X] = -v_cir*sin( th );
	    galaxy[0].prts[k].v[Y] = v_cir*cos( th );
	    galaxy[0].prts[k].v[Z] = 0;

	    //Parametro de suavizado
	    galaxy[0].prts[k].eps = prmt[SOF_MIN]+drand48()*(prmt[SOF_MAX]-prmt[SOF_MIN]);
	
	    //Interacciones de cada particula
	    galaxy[0].prts[k].inter = 1;
	    galaxy[0].prts[k].compa[0] = 0;
	    k++;}}
	
		
    return 0;
}


/********************************************************************
 NOMBRE:     collision
 FUNCION:    genera una colision entre dos galaxias
 ARGUMENTOS: estructura 'cluster' para retorno de posicion y      
	     velocidad de cada particula y arreglo con parametros 
 COORDENADAS:							    
	     *Coord 1 -- Radio
	     *Coord 2 -- Numero de Anillos
	     *Coord 3 -- NULL
	     *Veloc 1 -- NULL
	     *Veloc 2 -- NULL
	     *Veloc 3 -- NULL
	     *Maxim Mass -- Masa nucleo
	     *Minim Masa -- Masa estrellas
 RETORNA:    0							    
 LOG:        01/02/2011    Creacion             
********************************************************************/
int collision( struct cluster galaxy[1], 
	       double prmt[NMAX2] )
{
    int i, j, k, l;
    int spr;
    
    double X1, Y1, Z1;
    double VX1, VY1, VZ1;
    double r, th, v_cir;
    
    spr = prmt[N_PART]/(2.0*prmt[COOR_2]);


    //Particula central 1
    galaxy[0].prts[0].m = prmt[MAS_MAX];
    galaxy[0].prts[0].r[X] = 0;
    galaxy[0].prts[0].r[Y] = 0;
    galaxy[0].prts[0].r[Z] = 0;
    
    galaxy[0].prts[0].v[X] = 0;
    galaxy[0].prts[0].v[Y] = 0;
    galaxy[0].prts[0].v[Z] = 0;
    
    galaxy[0].prts[0].inter = 1;
    galaxy[0].prts[0].compa[0] = 1;
    
    
    //Particula central 2
    X1 = 100;
    Y1 = 0;
    Z1 = 50;
    VX1 = 0;
    VY1 = -0.4;
    VZ1 = -0.4;
    galaxy[0].prts[1].m = prmt[MAS_MAX];
    
    galaxy[0].prts[1].r[X] = X1;
    galaxy[0].prts[1].r[Y] = Y1;
    galaxy[0].prts[1].r[Z] = Z1;
    
    galaxy[0].prts[1].v[X] = VX1;
    galaxy[0].prts[1].v[Y] = VY1;
    galaxy[0].prts[1].v[Z] = VZ1;
    
    galaxy[0].prts[1].inter = 1;
    galaxy[0].prts[1].compa[0] = 0;
    
    
    //Asignacion de posiciones y velocidades
    k = 2;
    for( i=1; i<=prmt[COOR_2]; i++ ){
	r = prmt[COOR_1]*i/(1.0*prmt[COOR_2]);
	v_cir = sqrt( GC*prmt[MAS_MAX]/r );
	for( j=0; j<spr; j++ ){
	    th = 2*M_PI*j/(1.0*spr);
	  
	    //GALAXIA 1==============================
	    //Masas
	    galaxy[0].prts[k].m = prmt[MAS_MIN];
	    
	    galaxy[0].prts[k].r[X] = r*cos( th );
	    galaxy[0].prts[k].r[Y] = r*sin( th );
	    galaxy[0].prts[k].r[Z] = 0;
	    
	    galaxy[0].prts[k].v[X] = -v_cir*sin( th );
	    galaxy[0].prts[k].v[Y] = v_cir*cos( th );
	    galaxy[0].prts[k].v[Z] = 0;
	    
	    //Parametro de suavizado
	    galaxy[0].prts[k].eps = prmt[SOF_MIN]+drand48()*(prmt[SOF_MAX]-prmt[SOF_MIN]);
	
	    //Interacciones de cada particula
	    galaxy[0].prts[k].inter = 2;
	    galaxy[0].prts[k].compa[0] = 0;
	    galaxy[0].prts[k].compa[0] = 1;
	    
	    k += 1;}}
		
    return 0;
}


/********************************************************************
 NOMBRE:     galaxy_model_2
 FUNCION:    genera una distribucion uniforme sobre un disco con 
	     velocidades circulares constantes
 ARGUMENTOS: estructura 'cluster' para retorno de posicion y      
	     velocidad de cada particula y arreglo con parametros 
 COORDENADAS:							    
	     *Coord 1 -- Radio
	     *Coord 2 -- Numero de Anillos
	     *Coord 3 -- Distancia z
	     *Veloc 1 -- Magnitud velocidad circular velocidad plano x-y
	     *Veloc 2 -- Magnitud maxima velocidad dirección z
	     *Veloc 3 -- NULL
 RETORNA:    0							    
 LOG:        15/09/2009    Creacion             
 	     26/01/2011	   Implementacion estructura cluster
********************************************************************/
int galaxy_model_2( struct cluster galaxy[1], 
		  double prmt[NMAX2] )
{
    int i,j,k;
    int spr;
    
    double r, th;

    srand48(time(NULL));
    
    spr = prmt[N_PART]/(prmt[COOR_2]);

    //Asignacion de posiciones y velocidades
    k = 0;
    for( i=1; i<=prmt[COOR_2]; i++ ){
	r = prmt[COOR_1]*i/(1.0*prmt[COOR_2]);
	for( j=0; j<=spr; j++ ){
	    //Masas
	    galaxy[0].prts[k].m = prmt[MAS_MIN]+drand48()*(prmt[MAS_MAX]-prmt[MAS_MIN]);
	    th = 2*M_PI*j/(1.0*spr);
	    
	    galaxy[0].prts[k].r[X] = r*cos( th );
	    galaxy[0].prts[k].r[Y] = r*sin( th );
	    galaxy[0].prts[k].r[Z] = (1-2*drand48())*prmt[COOR_3]/2.;
	    
	    galaxy[0].prts[k].v[X] = -prmt[VEL_1]*sin( th );
	    galaxy[0].prts[k].v[Y] =  prmt[VEL_1]*cos( th );
	    galaxy[0].prts[k].v[Z] = (1-2*drand48())*prmt[VEL_2];

	    //Parametro de suavizado
	    galaxy[0].prts[k].eps = prmt[SOF_MIN]+drand48()*(prmt[SOF_MAX]-prmt[SOF_MIN]);
	
	    //Interacciones con todas las particulas
	    galaxy[0].prts[k].inter = -1;
	    k++;}}
	    
    return 0;
}