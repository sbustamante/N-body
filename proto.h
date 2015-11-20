// IO Module
int conf2dump( char * );
int in2dump( char * );
int read_parameters( char * );
int IC_reader( char * );
int out_snapshot( char * );
int out_energy( char *, double, double, double );

//Physics Module
double distance( double * , double * );
double magnitude( double * );
int direct_force( int, double * );
int energy( double *, double * );

//Numeric Module
int leap_frog( int, double, double *, double *, double * );