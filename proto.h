// IO Module
int conf2dump( char * );
int in2dump( char * );
int read_parameters( float *, char * );
int IC_reader( struct particle *, char *, float * );
int out_particles( struct particle *, char *, float * );

//Force Module
double distance( double * , double * );
double magnitude( double * );
int direct_force( struct particle *, float * );