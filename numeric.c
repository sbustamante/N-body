#include "allvars.h"


/**************************************************************************************************
 NAME:	     leap_frog
 FUNCTION:   returns the integrated properties of the i-th particle using the leap-frog algorithm
 INPUTS:     particle index, current time, position array, velocity array, acceleration array
 RETURN:     0
**************************************************************************************************/
int leap_frog( int i,
	       double t,
	       double r[3],
	       double v[3],
	       double a[3] )
{
    int ic;
    double at[3];
    
    //Calculating next acceleration
    direct_force( i, at );
    
    //Integrating
    for( ic=0; ic<3; ic++ )
    {
	r[ic] = part[i].r[ic] + part[i].v[ic]*p[TSTP] + 0.5*part[i].a[ic]*p[TSTP]*p[TSTP];
	v[ic] = part[i].v[ic] + 0.5*( part[i].a[ic] + at[ic] )*p[TSTP];
	a[ic] = at[ic];
	//Periodic box
#ifdef PERIODIC_BOX
	if( r[ic] >= p[LBOX]/2.0 )
	    r[ic] -= p[LBOX];
	if( r[ic] < -p[LBOX]/2.0 )
	    r[ic] += p[LBOX];
#endif
    }
    
    return 0;
}
