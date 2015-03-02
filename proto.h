// Data Module
int conf2dump( char * );
int in2dump( char * );
int read_parameters( double *, char * );
int data_in( struct cluster *, char * );
int data_out( struct cluster *, char * );

// Numeric Module
double distance( double *, double * );
int integration_step( struct cluster *, double , double , int );
int euler_step( struct cluster *, double , double );
int rk4_step( struct cluster *, double , double );

// Physics Module
int dynamic_function( struct cluster *, double , struct intg_step * );

// Initial Distribution Module
int initial_conditions( struct cluster *, double *, char * );
int uniform_cube( struct cluster *, double * );
int uniform_spheroid( struct cluster *, double * );
int uniform_disk( struct cluster *, double * );
int collision( struct cluster *, double * );
int galaxy_model_1( struct cluster *, double * );
int galaxy_model_2( struct cluster *, double * );
