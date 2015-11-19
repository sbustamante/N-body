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
#define TMAX		2		//Integration time
#define TSTP		3		//Time step
#define EPSS		4		//Epsilon softening

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
};


/**************************************************************************************************
			      GLOBALS
**************************************************************************************************/
//Parameters
float p[NMAX1];
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