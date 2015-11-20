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
	dist += ( r1[i] - r2[i] )*( r1[i] - r2[i] );
    
    return pow( dist, 0.5 );
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
    
    return pow( mag, 0.5 );
}



/**************************************************************************************************
 NAME:	     direct_force
 FUNCTION:   returns the force calculation using direct force
 INPUTS:     particle id, acceleration array
 RETURN:     0
**************************************************************************************************/
int direct_force( int i,
		  double a[3] )
{
    int j, ic;
    double dist;
    double rj[3];
      
    //Initializing acceleration
    for( ic=0; ic<3; ic++ )
	a[ic] = 0;
    
    //Initializing potential
    part[i].ep = 0;  
    
    for( j=0; j<(int)p[NPAR]; j++ )
	//Checking self contribution and type of interacting particles
	if( i != j && ( part[i].int_typ == part[j].typ || part[i].int_typ == 0 ) )
	{
	    for( ic=0; ic<3; ic++ )
		rj[ic] = part[j].r[ic];
	    //Periodic box
#ifdef PERIODIC_BOX
	    for( ic=0; ic<3; ic++ )
		if( part[j].r[ic] - part[i].r[ic] >= p[LBOX]/2.0 )
		    rj[ic] -= p[LBOX];
		else if( part[j].r[ic] - part[i].r[ic] < -p[LBOX]/2.0 )
		    rj[ic] += p[LBOX];
#endif
	    //Calculating distance
	    dist = distance( part[i].r, rj );
	    dist = pow( dist*dist + p[EPSS]*p[EPSS], 0.5 );
	    for( ic=0; ic<3; ic++ )
		a[ic] += -GC*part[j].m/pow( dist,3 )*( part[i].r[ic] - rj[ic] );
#ifdef EVAL_POTENTIAL
	    //Potential energy
	    part[i].ep += -GC*part[i].m*part[j].m/dist;
#endif
	}
    return 0;
}


/**************************************************************************************************
 NAME:	     energy
 FUNCTION:   returns the energy of the system, i.e. kinetic and potential
 INPUTS:     kinetic energy pointer, potential energy pointer
 RETURN:     0
**************************************************************************************************/
int energy( double *et,
	    double *ep )
{
    int i, ic;
    double dist;
    double rj[3];
      
    //Initializing energies
    *et = 0;
    *ep = 0;
    
    for( i=0; i<(int)p[NPAR]; i++ )
    {
	*et += 0.5*part[i].m*pow( magnitude( part[i].v ), 2 );
	*ep += part[i].ep;
    }
    
    return 0;
}