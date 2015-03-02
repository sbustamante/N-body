# N-body
A very basic implementation of a N-body simulation

## Compiling
This code comes with two different modules. The first one is a generator of initial conditions. 
For compiling this module you must run

  $ make IC.out
  

The other module, and the principal one, is Nbody. This can be compiled as

  $ make Nbody.out
  
Each module calls the file **parametros.conf**. There you can configure the integrator scheme and
the initial conditions IC (read the parameter file in order to see the available IC).
Each set of ICs must be provided with a set of parameters. Consult the file **distributions.c** for 
the parameters required by each IC.
