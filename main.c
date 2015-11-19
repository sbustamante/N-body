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
    int i, it;
    double t;
    char out_filename[NMAX1];
    
    printf( "\n\n******************************** NBODY CODE ********************************\n" );
    printf( "  by: Sebastian Bustamante (sebastian.bustamante@h-its.org)\n" );
    //Loading Configuration File
    read_parameters( argv[1] );
    //Allocating memory for particles
    part = (struct particle *)calloc( (int)(p[NPAR]), sizeof( struct particle ) );
     
    //Loading or generating initial conditions
#ifdef INITIAL_CONDITIONS
#else
    //Reading ICs
    IC_reader( argv[2] );
#endif
    
    //Integration
    printf( "  * Starting integration\n" );
    t = 0; it = 0;
    while( t<=p[TMAX] )
    {
	//Leap-frog
	for( i=0; i<(int)p[NPAR]; i++ )
	    leap_frog( i, t, part[i].r, part[i].v, part[i].a );
	//printing snapshot
	sprintf( out_filename, "%s_%d", argv[3], it );
	out_snapshot( out_filename );
	//Time step
	t += p[TSTP]; it ++;
    }
    printf( "  * %d snapshots produced\n", it-1 );
    
    printf( "  * Nbody done successfully\n" );
    printf( "****************************************************************************\n\n" );
    return 0;
}