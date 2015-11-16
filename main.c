#include "allvars.h"
/*Usage:	
 	   ./TreeCode.out 
	   *	<parameter_file> 
 	   *	<IC_file> 
 	   *	<Out_tree_filename>
 	   *	<Out_force_filename>
*/

int main( int argc, char *argv[] )
{
    int n;    
    //Parameters
    float p[NMAX1];
    //Structures
    struct particle *particles;
    
    
    printf( "\n\n******************************** NBODY CODE ********************************\n" );
    //Loading Configuration File
    read_parameters( p, argv[1] );
   
    //Allocating memory for particles
    particles = (struct particle *)calloc( (int)(p[NPAR]), sizeof( struct particle ) );
     
    //Loading or generating initial conditions
#ifdef INITIAL_CONDITIONS
#else
    //Reading ICs
    IC_reader( particles, argv[2], p );
#endif
    
    //Computing forces by using Direct sum method--------------------------------------------------
    direct_force( particles, p );
    	    
    //Storing result of Tree forces
#ifdef PRINT_FORCES
  #ifdef PRINT_TREE
    out_particles( particles, argv[4], p );
  #else
    out_particles( particles, argv[3], p );
 #endif
#endif
    
    return 0;
}