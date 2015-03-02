#include <allvars.h>


/*****************************************************************
 NOMBRE:     conf2dump
 FUNCION:    convierte un archivo de configuracion comentado en 
             texto plano.
 ARGUMENTOS: nombre del archivo de configuracion
 RETORNA:    0
 LOG:        18/01/2011    Creacion
*****************************************************************/
int conf2dump( char filename[] )
{
    char cmd[100];
    sprintf( cmd, "grep -v \"#\" %s | grep -v \"^$\" | gawk -F\"=\" '{print $2}' > %s.dump", 
	     filename, filename );
    system( cmd );

    return 0;
}


/*****************************************************************
 NOMBRE:     in2dump
 FUNCION:    convierte un archivo de datos comentado en texto 
	     plano.
 ARGUMENTOS: nombre del archivo de configuracion
 RETORNA:    0
 LOG:        18/01/2011    Creacion
*****************************************************************/
int in2dump( char filename[] )
{
    char cmd[100];
    sprintf( cmd, "grep -v \"#\" %s > %s.dump", 
	     filename, filename );
    system( cmd );

    return 0;
}


/*****************************************************************
 NOMBRE:     read_parameters
 FUNCION:    lee un archivo de nombre dado y escribe la informa
             cion en un arreglo dado.
 ARGUMENTOS: arreglo donde se devuelven los datos leidos y el nom
	     bre del archivo de configuracion.
 RETORNA:    0 si el archivo fue leido
	     1 si el archivo no existe
 LOG:        18/01/2011    Creacion
*****************************************************************/
int read_parameters( double parameters[],
		     char filename[] )
{
    char cmd[100], filenamedump[100];
    int i=0;
    FILE *file;

    //Deteccion de archivo
    file = fopen( filename, "r" );
    if( file==NULL ){
	printf( "  * El archivo '%s' no existe!\n\tFIN DE LA SIMULACION.\n", filename );
	return 1;}
    fclose(file);
    
    //Conversion a texto plano
    conf2dump( filename );
    sprintf( filenamedump, "%s.dump", filename );
    file = fopen( filenamedump, "r" );
    
    //Lectura
    while( getc( file ) != EOF ){
	fscanf( file, "%lf", &parameters[i] );
	i++;}
    
    fclose( file );
    
    printf( "  * El archivo '%s' ha sido leido!\n", filename );

    sprintf( cmd, "rm -rf %s.dump", filename );
    system( cmd );
    
    return 0;
}


/********************************************************************
 NOMBRE:     data_in
 FUNCION:    lee archivo de entrada con masas, posiciones, 
	     velocidades y parametros de suevizados de todas las
	     partículas
 ARGUMENTOS: estructura tipo 'cluster', y cadena de 
	     caracteres con nombre de archivo de entrada.
 RETORNA:    0 si el archivo fue leido
	     1 si el archivo no existe
 LOG:        25/05/2008    Creacion                                
             30/06/2008    Implementacion de estructuras 
             21/01/2011    Modificación
********************************************************************/
int data_in( struct cluster galaxy[1],
	     char filename[] )
{
    int i=0;
    char cmd[100], filenamedump[100];
    FILE *file;
    

    //Deteccion de archivo
    file = fopen( filename, "r" );
    if( file==NULL ){
	printf( "  * El archivo '%s' no existe!\n\tFIN DE LA SIMULACION.\n", filename );
	return 1;}
    fclose(file);

    //Conversion a texto plano
    in2dump( filename );
    sprintf( filenamedump, "%s.dump", filename );
    file = fopen( filenamedump, "r" );
    
    //Lectura
    while( getc( file ) != EOF ){
	fscanf( file,"%lf %lf %lf %lf %lf %lf %lf %lf %d %d %d %d %d %d %d %d %d %d %d", 
		&galaxy[0].prts[i].m, 
		&galaxy[0].prts[i].r[0], &galaxy[0].prts[i].r[1], &galaxy[0].prts[i].r[2],
		&galaxy[0].prts[i].v[0], &galaxy[0].prts[i].v[1], &galaxy[0].prts[i].v[2], 
		&galaxy[0].prts[i].eps, &galaxy[0].prts[i].inter,
		&galaxy[0].prts[i].compa[0], &galaxy[0].prts[i].compa[1],
		&galaxy[0].prts[i].compa[2], &galaxy[0].prts[i].compa[3],
		&galaxy[0].prts[i].compa[4], &galaxy[0].prts[i].compa[5],
		&galaxy[0].prts[i].compa[6], &galaxy[0].prts[i].compa[7],
		&galaxy[0].prts[i].compa[8], &galaxy[0].prts[i].compa[9]);
	i++;}
	  
    fclose( file );

    printf( "  * El archivo '%s' ha sido leido!\n", filename );
    
    sprintf( cmd, "rm -rf %s.dump", filename );
    system( cmd );

    return 0;
}


/********************************************************************
 NOMBRE:     data_out
 FUNCION:    escribe archivo con masas, posiciones, velocidades y de 
             todas las partículas
 ARGUMENTOS: estructura 'cluster' con datos, y cadena de 
	     caracteres con nombre de archivo de salida.
 RETORNA:    0
 LOG:        21/01/2011    Creacion                                
********************************************************************/
int data_out( struct cluster galaxy[1],
	     char filename[] )
{
    int i=0;
    FILE *file;
    
    file = fopen( filename, "w" );
    
    fprintf( file, "#Simulacion N-Body\t\tTiempo Snapshot = %lf\n", galaxy[0].t_snap ); 
    fprintf( file, "#Masa\t\tX\t\tY\t\tZ\t\tVx\t\tVy\t\tVz\n" ); 
    
    //Escritura
    for( i=0; i<galaxy[0].N; i++ )
	fprintf( file, "%lf\t%lf\t%lf\t%lf\t%lf\t%lf\t%lf\n", 
		 galaxy[0].prts[i].m, 
		 galaxy[0].prts[i].r[0], galaxy[0].prts[i].r[1], galaxy[0].prts[i].r[2],
		 galaxy[0].prts[i].v[0], galaxy[0].prts[i].v[1], galaxy[0].prts[i].v[2]);
	  
    fclose( file );
    
    return 0;
}
