#include <allvars.h>

//Uso: Nbody.out 
//		<(1-Null) si desea correr las IC.	(0) si desea proveer las IC con datos.in>
//		<(1-Null) si desea hacer video.		(0) si no desea hacer video>

int main( int argc, char *argv[] )
{
    int i=0,j=0;
    double t=0;
    double prmt[NMAX2];
    char str[NMAX2];
    FILE *script;

    double T, V;
    struct cluster galaxy[1];
  
    printf( "\n\n***************** NBODY SIMULATION *****************\n" );

    //Lectura de parametros
    if( read_parameters( prmt, "parametros.conf")==1 ) return 0;
    galaxy[0].N = (int)prmt[N_PART];

    //Generacion y lectura de condiciones iniciales
    if( argv[1]==NULL || atoi(argv[1])==1 )
 	initial_conditions( galaxy, prmt, "datos.in" );
    else
      	if( data_in( galaxy, "datos.in")==1 ) return 0;

    while( t<prmt[T_MAX] )
    {
	//Tiempo actual de la simulacion
	galaxy[0].t_snap = t;
	
	//Video --------------------------
	if( argv[2]==NULL || atoi(argv[2])==1 ){
	    //Impresion de datos	  
	    sprintf( str, "./datos/Galaxy%05d", j );
	    data_out( galaxy, str );
	    //Inicializacion de Script gnuplot
	    script = fopen( "script.gpl", "w" );
	    sprintf( str, "set terminal png\nset output '_tmp-%05d.png'\nset nokey\n", j );
	    fprintf( script, "%s", str );
	    sprintf( str, "set title 't = %lf'\n", t );
	    fprintf( script, "%s", str );
	    sprintf( str, "set xrange [%lf:%lf] \nset yrange [%lf:%lf]\n", -100.,100.,-100.,100. );
	    fprintf( script, "%s", str );
	    sprintf( str, "plot './datos/Galaxy%05d' u 2:3 w p ls 14",j );
	    fprintf( script, "%s", str );
	    fclose(script);
	    system("gnuplot script.gpl");}
	
	//Paso del sistema
	printf( " t = %lf\n", t );
	
	//Paso de integracion
	integration_step( galaxy, t, prmt[T_STEP], prmt[TYP_INT] );
	
	t += prmt[T_STEP];
	j++;
    }
    //Impresion de datos
    data_out( galaxy, "data_states.dat" );

     if( argv[2]==NULL || atoi(argv[2])==1 ){    
	//Eliminacion de archivos temporales -----------------
// 	system("rm -rf *.tmp");
 	system("ffmpeg -qscale 1 -r 10 -b 9600 -i _tmp-%05d.png  video.mp4");
//         system("convert -delay .1 -loop 0 *.png animacion.gif");
	system("rm -rf *.png");
	system("rm -rf script.gpl");}
    
    
    return 0;
}