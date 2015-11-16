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
#define NHIE		2		//Maximal number of hierarchies
#define THEC		3		//Threshold angle
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
//Structure of particles including tree information
struct particle
{
    //Mass
    double m;
    //Position
    double r[3];
    //Velocity
    double v[3];
    //Force
    double f[3];
};


/**************************************************************************************************
			      HEADERS
**************************************************************************************************/
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "proto.h"