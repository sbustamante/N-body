#include <allvars.h>


/*****************************************************************
 NOMBRE:     distance
 FUNCION:    calcula la distancia entre dos vectores
 ARGUMENTOS: dos arreglos de 3 dimensiones
 RETORNA:    0
 LOG:        27/01/2011    Creacion
*****************************************************************/
double distance( double r1[3],
		 double r2[3] )
{    
    return pow( (r1[X]-r2[X])*(r1[X]-r2[X]) +
		(r1[Y]-r2[Y])*(r1[Y]-r2[Y]) +
		(r1[Z]-r2[Z])*(r1[Z]-r2[Z]), 0.5 );
}


/*****************************************************************
 NOMBRE:     integration_step
 FUNCION:    integra un paso del sistema de N particulas
 ARGUMENTOS: arreglo 'cluster' con estado de particulas, paso de
	     de integracion,y entero con especificacion de metodo
	     de integracion a utilizar.
	     0 --- Runge Kutta 4
	     1 --- Euler primer orden
 RETORNA:    0
 LOG:        27/01/2011    Creacion
*****************************************************************/
int integration_step( struct cluster galaxy[1], 
		      double t,
		      double h, 
		      int method )
{    
    //RK4 de primer orden
    if( method==0 )
	rk4_step( galaxy, t, h );
  
    //Euler de primer orden
    if( method==1 )
	euler_step( galaxy, t, h );

    return 0;
}


/*****************************************************************
 NOMBRE:     euler_step
 FUNCION:    integrador por metodo de euler
 ARGUMENTOS: arreglo 'cluster' con estado de particulas, paso de
	     de integracion.
 RETORNA:    0
 LOG:        27/01/2011    Creacion
*****************************************************************/
int euler_step( struct cluster galaxy[1],
		double t,
		double h )
{
    int i;
    struct intg_step f[MAXNPARTICLES];
    
    //funcion dinamica
    dynamic_function( galaxy, t, f );

    for( i=0; i<galaxy[0].N; i++ ){
	galaxy[0].prts[i].r[X] = galaxy[0].prts[i].r[X] + h*f[i].r[X];
	galaxy[0].prts[i].r[Y] = galaxy[0].prts[i].r[Y] + h*f[i].r[Y];
	galaxy[0].prts[i].r[Z] = galaxy[0].prts[i].r[Z] + h*f[i].r[Z];
	
	galaxy[0].prts[i].v[X] = galaxy[0].prts[i].v[X] + h*f[i].v[X];
	galaxy[0].prts[i].v[Y] = galaxy[0].prts[i].v[Y] + h*f[i].v[Y];
	galaxy[0].prts[i].v[Z] = galaxy[0].prts[i].v[Z] + h*f[i].v[Z];}
    
    return 0;
}


/*****************************************************************
 NOMBRE:     rk4_step
 FUNCION:    integrador por metodo de rk4
 ARGUMENTOS: arreglo 'cluster' con estado de particulas, paso de
	     de integracion.
 RETORNA:    0
 LOG:        28/01/2011    Creacion
*****************************************************************/
int rk4_step( struct cluster galaxy[1],
	      double t,
	      double h )
{
    int i, k;
    struct cluster glx_h[1];
    struct intg_step k1[MAXNPARTICLES], k2[MAXNPARTICLES], k3[MAXNPARTICLES], k4[MAXNPARTICLES];
    
    //Inicializacion
    for( i=0; i<galaxy[0].N; i++ ){
	for( k=0; k<3; k++ ){
	    glx_h[0].prts[i].r[k] = galaxy[0].prts[i].r[k];
	    glx_h[0].prts[i].v[k] = galaxy[0].prts[i].v[k];}}
    
    //Calculo k1
    dynamic_function( galaxy, t, k1 );
    
    for( i=0; i<galaxy[0].N; i++ ){
	for( k=0; k<3; k++ ){
	    galaxy[0].prts[i].r[k] = glx_h[0].prts[i].r[k] + h*k1[i].r[k]/2.0;
	    galaxy[0].prts[i].v[k] = glx_h[0].prts[i].v[k] + h*k1[i].v[k]/2.0;}}
	    
    //Calculo k2
    dynamic_function( galaxy, t + h/2.0, k2 );
    
    for( i=0; i<galaxy[0].N; i++ ){
      	for( k=0; k<3; k++ ){
	    galaxy[0].prts[i].r[k] = glx_h[0].prts[i].r[k] + h*k2[i].r[k]/2.0;
	    galaxy[0].prts[i].v[k] = glx_h[0].prts[i].v[k] + h*k2[i].v[k]/2.0;}}

    //Calculo k3
    dynamic_function( galaxy, t + h/2.0, k3 );
    
    for( i=0; i<galaxy[0].N; i++ ){
	for( k=0; k<3; k++ ){
	    galaxy[0].prts[i].r[k] = glx_h[0].prts[i].r[k] + h*k3[i].r[k];
	    galaxy[0].prts[i].v[k] = glx_h[0].prts[i].v[k] + h*k3[i].v[k];}}
    
    //Calculo k4
    dynamic_function( galaxy, t + h, k4 );

    //Calculo del siguiente paso
    for( i=0; i<galaxy[0].N; i++ ){
	for( k=0; k<3; k++ ){
	    galaxy[0].prts[i].r[k] = glx_h[0].prts[i].r[k] + h*( k1[i].r[k] + 2*k2[i].r[k] + 2*k3[i].r[k] + k4[i].r[k] )/6.;
	    galaxy[0].prts[i].v[k] = glx_h[0].prts[i].v[k] + h*( k1[i].v[k] + 2*k2[i].v[k] + 2*k3[i].v[k] + k4[i].v[k] )/6.;}}
    
    return 0;
}