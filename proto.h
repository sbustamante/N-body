// IO Module
int conf2dump( char * );
int in2dump( char * );
int read_parameters( char * );
int IC_reader( char * );
int out_snapshot( char * );

//Physics Module
double distance( double * , double * );
double magnitude( double * );
int direct_force( int, double * );

//Numeric Module
int leap_frog( int, double, double *, double *, double * );