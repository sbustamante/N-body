#include "allvars.h"


/**************************************************************************************************
 NAME:	     parameter_index
 FUNCTION:   returns the integer index associated to that parameter
 INPUTS:     name of the parameter
 RETURN:     index of the parameter
**************************************************************************************************/
int parameter_index( char parameter_name[] )
{
    int i, index=-1;
    //Declaring parameters (Exactly as configuration file)
    char *parameter_names[NMAX1];
    parameter_names[LBOX] = "lbox";
    parameter_names[NPAR] = "npar";
    parameter_names[NHIE] = "nhie";
    parameter_names[THEC] = "thec";
    parameter_names[EPSS] = "epss";
    
    //Searching index
    for( i=0; i<NMAX1; i++ )
	if( strcmp( parameter_names[i], parameter_name ) == 0 ){
	    index = i;
	    break;}
	    
    return index;
}


/**************************************************************************************************
 NAME:	     conf2dump
 FUNCTION:   converts a data file text in plain text 
 INPUTS:     name of configuration file
 RETURN:     0
**************************************************************************************************/
int conf2dump( char filename[] )
{
    char buf[NMAX1];
    //Parameters
    sprintf( buf, "grep -v \"#\" %s | grep -v \"^$\" | gawk -F\"=\" '{print $2}' > %s.values", 
	     filename, filename );
    system( buf );
    //Names
    sprintf( buf, "grep -v \"#\" %s | grep -v \"^$\" | gawk -F\"=\" '{print $1}' > %s.names", 
	     filename, filename );
    system( buf );

    return 0;
}


/**************************************************************************************************
 NAME:       read_parameters
 FUNCTION:   reads the file with given name and load information of array given
 INPUTS:     array where it returns reading data and file name 
	     with configuration file
 RETURN:     0 if file read ok
	     1 if file dont exist
**************************************************************************************************/
int read_parameters( float parameters[],
		     char filename[] )
{
    char buf[NMAX1], filenamedump[NMAX1];
    char names[NMAX1];
    FILE *file_names, *file_values;

    //Load of File
    file_values = fopen( filename, "r" );
    if( file_values==NULL ){
	printf( "  * The file '%s' don't exist!\n", filename );
	return 1;}
    fclose(file_values);
    
    //Converting to plain text
    conf2dump( filename );
    
    //Opening File with parameter names
    sprintf( filenamedump, "%s.names", filename );
    file_names = fopen( filenamedump, "r" );
    //Opening File with parameter values
    sprintf( filenamedump, "%s.values", filename );
    file_values = fopen( filenamedump, "r" );
    
    //Reading
    while( getc( file_values ) != EOF ){
	fscanf( file_names, "%s", names );
	fscanf( file_values, "%f", &parameters[ parameter_index( names ) ] );}
	
    fclose( file_names );
    fclose( file_values );
    
    printf( "  * The file '%s' has been loaded!\n", filename );

    sprintf( buf, "rm -rf %s.values %s.names", filename, filename );
    system( buf );
    
    return 0;
}


/**************************************************************************************************
 NAME:       IC_reader
 FUNCTION:   read input file with positions of particles
 INPUTS:     particle structure, input file name, parameters
 RETURN:     0 if file read ok
	     1 if file dont exist
**************************************************************************************************/
int IC_reader( struct particle particles[],
	       char filename[],
	       float *p )
{
    int i=0, j=0, Ndats;
    char cmd[100], filenamedump[100];
    FILE *file;
    float tmp;
    
    //File Detection
    file = fopen( filename, "r" );
    if( file==NULL ){
	printf( "  * The file '%s' don't exist!\n", filename );
	return 1;}
	
    //Read data
    for( i=0; i<(int)p[NPAR]; i++ )
    {
	fscanf( file,"%lf %lf %lf %lf", 
		&particles[i].m, &particles[i].r[X], &particles[i].r[Y], &particles[i].r[Z] );
    }
	
    fclose( file );

    printf( "  * The file '%s' has been loaded!\n", filename );

    return 0;
}


/**************************************************************************************************
 NAME:       out_particles
 FUNCTION:   print information of forces of each particles
 INPUTS:     particle structure, output file name, parameters
 RETURN:     0
**************************************************************************************************/
int out_particles( struct particle particles[],
		   char filename[],
		   float *p )
{
    int n, nh;
    FILE *file;
    
    //File Detection
    file = fopen( filename, "w" );

    //writing data
    for( n=0; n<(int)p[NPAR]; n++ )
    {
	fprintf( file, "%d\t%lf\t%lf\t%lf\n", 
	n, 
	particles[n].f[X], particles[n].f[Y], particles[n].f[Z] );
    }
	
    fclose( file );

    printf( "  * The file '%s' has been saved!\n", filename );

    return 0;
}