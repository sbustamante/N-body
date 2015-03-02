#include <allvars.h>


/*****************************************************************
 NOMBRE:     dynamic_function
 FUNCION:    integra un paso del sistema de N particulas
 ARGUMENTOS: arreglo 'cluster' con estado de particulas, paso de
	     de integracion,y entero con especificacion de metodo
	     de integracion a utilizar.
	     0 --- Runge Kutta 4
	     1 --- Euler primer orden
 RETORNA:    0
 LOG:        27/01/2011    Creacion
*****************************************************************/
int dynamic_function( struct cluster galaxy[1],
		      double t,
		      struct intg_step f[MAXNPARTICLES] )
{
    int i, j, k;
    double force_all;
    double eps;

    for( i=0; i<galaxy[0].N; i++ ){
	f[i].r[X] = galaxy[0].prts[i].v[X];
	f[i].r[Y] = galaxy[0].prts[i].v[Y];
	f[i].r[Z] = galaxy[0].prts[i].v[Z];
	
	f[i].v[X] = 0;
	f[i].v[Y] = 0;
	f[i].v[Z] = 0;

	if( galaxy[0].prts[i].inter != -1 )
	    for( j=0; j<galaxy[0].prts[i].inter; j++ ){
		k = galaxy[0].prts[i].compa[j];
		if( k != i ){

		    eps = 0.5*(galaxy[0].prts[i].eps + galaxy[0].prts[k].eps );
		    
		    force_all = -GC*galaxy[0].prts[k].m
		    /pow( distance( galaxy[0].prts[k].r, galaxy[0].prts[i].r ) + eps , 3 );
		    
		    f[i].v[X] += force_all*(galaxy[0].prts[i].r[X]-galaxy[0].prts[k].r[X]);
		    f[i].v[Y] += force_all*(galaxy[0].prts[i].r[Y]-galaxy[0].prts[k].r[Y]);
		    f[i].v[Z] += force_all*(galaxy[0].prts[i].r[Z]-galaxy[0].prts[k].r[Z]);}}
	else
	    for( j=0; j<galaxy[0].N; j++ ){
		if( j != i ){

		    eps = 0.5*(galaxy[0].prts[i].eps + galaxy[0].prts[j].eps );
		    
		    force_all = -GC*galaxy[0].prts[j].m
		    /pow( distance( galaxy[0].prts[j].r, galaxy[0].prts[i].r ) + eps , 3 );
		    
		    f[i].v[X] += force_all*(galaxy[0].prts[i].r[X]-galaxy[0].prts[j].r[X]);
		    f[i].v[Y] += force_all*(galaxy[0].prts[i].r[Y]-galaxy[0].prts[j].r[Y]);
		    f[i].v[Z] += force_all*(galaxy[0].prts[i].r[Z]-galaxy[0].prts[j].r[Z]);}}}
		    
    return 0;
}