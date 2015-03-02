/********************************************************************
			       MACROS
********************************************************************/
//Macros generales
#define MAXNPARTICLES 	10000
#define NMAX1 		10
#define NMAX2 		100
#define NMAX3 		1000

//Constantes fisicas
#define GC		1

//Macros de parametros
#define N_PART		0
#define T_STEP		1
#define T_MAX		2

#define TYP_INT		3

#define TYP_DIS		4
#define COOR_1		5
#define COOR_2		6
#define COOR_3		7
#define VEL_1		8
#define VEL_2		9
#define VEL_3		10
#define MAS_MIN		11
#define MAS_MAX		12
#define SOF_MIN		13
#define SOF_MAX		14

//Macros de variables
#define X		0
#define Y		1
#define Z		2


/********************************************************************
			     ESTRUCTURAS
********************************************************************/

struct particle{
    double m;
    double r[3], v[3];
    double Ek, Ep;
    
    double eps;
    signed int inter;
    int compa[10];};


struct cluster{
    int N;
    double t_snap;
    double Ek, Ep;
    struct particle prts[MAXNPARTICLES];};
    
    
struct intg_step{
    double r[3], v[3];};
    
   
/********************************************************************
			      HEADERS
********************************************************************/
#include <stdio.h>
#include <math.h>
#include <proto.h>
#include <stdlib.h>
#include <time.h>