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
    parameter_names[EPSS] = "epss";
    parameter_names[TMAX] = "tmax";
    parameter_names[TSTP] = "tstp";
    parameter_names[SSTP] = "sstp";
    
    //Searching index
    for( i=0; i<NMAX1; i++ )
	if( strcmp( parameter_names[i], parameter_name ) == 0 )
	{
	    index = i;
	    break;
	}
	    
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
 INPUTS:     filename with configuration file
 RETURN:     0 if file read ok
	     1 if file dont exist
**************************************************************************************************/
int read_parameters( char filename[] )
{
    char buf[NMAX1], filenamedump[NMAX1];
    char names[NMAX1];
    FILE *file_names, *file_values;

    //Load of File
    file_values = fopen( filename, "r" );
    if( file_values==NULL )
    {
	printf( "  * The file '%s' don't exist!\n", filename );
	return 1;
    }
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
    while( getc( file_values ) != EOF )
    {
	fscanf( file_names, "%s", names );
	fscanf( file_values, "%lf", &p[ parameter_index( names ) ] );
    }
	
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
 INPUTS:     input file name
 RETURN:     0 if file read ok
	     1 if file dont exist
**************************************************************************************************/
int IC_reader( char filename[] )
{
    int i;
    FILE *file;
    
    //File Detection
    file = fopen( filename, "r" );
    if( file==NULL )
    {
	printf( "  * The file '%s' don't exist!\n", filename );
	return 1;
    }
	
    //Reading data
    for( i=0; i<(int)p[NPAR]; i++ )
    {
	fscanf( file,"%lf %lf %lf %lf %lf %lf %lf %d %d %d",
		&part[i].m,
		&part[i].r[X], &part[i].r[Y], &part[i].r[Z],
		&part[i].v[X], &part[i].v[Y], &part[i].v[Z],
		&part[i].typ, &part[i].int_typ, &part[i].print );
    }
    
    //Calculating acceleration
    for( i=0; i<(int)p[NPAR]; i++ )
	direct_force( i, part[i].a );
	
    fclose( file );

    printf( "  * The file '%s' has been loaded!\n", filename );

    return 0;
}


/**************************************************************************************************
 NAME:       out_snapshot
 FUNCTION:   print information of forces of each particles
 INPUTS:     output file name
 RETURN:     0
**************************************************************************************************/
int out_snapshot( char filename[] )
{
    int i;
    FILE *file;
    
    //File Detection
    file = fopen( filename, "w" );

    //writing data
    for( i=0; i<(int)p[NPAR]; i++ )
	//Only printable particles
	if( part[i].print || i==0 )
	{
	    fprintf( file, "%lf\t%lf\t%lf\t%lf\t%lf\t%lf\t%lf\t%d\n", 
	    part[i].m,
	    part[i].r[X], part[i].r[Y], part[i].r[Z],
	    part[i].v[X], part[i].v[Y], part[i].v[Z],
	    part[i].typ );
	}
	
    fclose( file );

    return 0;
}


/**************************************************************************************************
 NAME:       out_energy
 FUNCTION:   print information of the energy
 INPUTS:     output file name, time, kinetic energy, potential energy
 RETURN:     0
**************************************************************************************************/
int out_energy( char filename[], 
		double t,
		double et, 
		double ep )
{
    int i;
    FILE *file;
    
    file = fopen( filename, "a" );

    fprintf( file, "%lf\t%lf\t%lf\t%lf\n", t, et, ep, et + ep );

    fclose( file );

    return 0;
}