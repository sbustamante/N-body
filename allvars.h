/**************************************************************************************************
			      MACROS
**************************************************************************************************/
//General Macros
#define NMAX1		100
#define NMAX2		1000
#define MY_FREE(ptr)	free(ptr); ptr = NULL;

//Macros for Parameters
#define LBOX		0		//Length of the Simulation
#define NPAR		1		//Number of Particles
#define EPSS		2		//Epsilon softening
#define TMAX		3		//Integration time
#define TSTP		4		//Time step
#define SSTP		5		//Snapshot step

//Macros of Physical constants
#define GC		1		//Cavendish Constant

//Other macros
#define X		0		//X coordinate
#define Y		1		//Y coordinate
#define Z		2		//Z coordinate


/**************************************************************************************************
			      STRUCTURES
**************************************************************************************************/
struct particle
{
    //Mass
    double m;
    //Position
    double r[3];
    //Velocity
    double v[3];
    //Acceleration
    double a[3];
    //Potential
    double ep;
    
    //Type of particle
    int typ;
    //Interacting particles
    int int_typ;
    
    //Printable particle
    int print;
};


/**************************************************************************************************
			      GLOBALS
**************************************************************************************************/
//Parameters
double p[NMAX1];
//Structures
struct particle *part;
    

/**************************************************************************************************
			      HEADERS
**************************************************************************************************/
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "proto.h"