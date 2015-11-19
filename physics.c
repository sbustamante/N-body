#include "allvars.h"


/**************************************************************************************************
 NAME:	     distance
 FUNCTION:   returns the distance between two vectors
 INPUTS:     vector 1, vector 2
 RETURN:     distance
**************************************************************************************************/
double distance( double r1[3],
  		 double r2[3] )
{
    int i;
    double dist = 0;
    
    for( i=0; i<3; i++ )
	dist += (r1[i]-r2[i])*(r1[i]-r2[i]);
    
    return pow(dist, 0.5);
}


/**************************************************************************************************
 NAME:	     magnitude
 FUNCTION:   returns the magnitude of a vector
 INPUTS:     vector 1
 RETURN:     magnitude
**************************************************************************************************/
double magnitude( double r[3] )
{
    int i;
    double mag = 0;
    
    for( i=0; i<3; i++ )
	mag += r[i]*r[i];
    
    return pow(mag, 0.5);
}



/**************************************************************************************************
 NAME:	     direct_force
 FUNCTION:   returns the force calculation using direct force
 INPUTS:     particles, parameters
 RETURN:     0
**************************************************************************************************/
int direct_force( struct particle *particles,
		  float *p )
{
    int i, j, ic;
    double dist;
      
    //Sweeping all the particles
    for( i=0; i<(int)p[NPAR]; i++ )
    {
	//Initializing force
	for( ic=0; ic<3; ic++ )
	    particles[i].f[ic] = 0;
	  
	for( j=0; j<(int)p[NPAR]; j++ )
	    if( i != j )
	    {
		//Calculating distance
		dist = pow(pow(distance( particles[i].r, particles[j].r ),2) + p[EPSS]*p[EPSS], 0.5);
		for( ic=0; ic<3; ic++ )
		    particles[i].f[ic] += -GC*particles[j].m/pow( dist,3 )*( particles[i].r[ic] - particles[j].r[ic] );
	    }
	for( ic=0; ic<3; ic++ )
	    particles[i].f[ic] *= particles[i].m;
    }
    
    return 0;
}