#**************************************************************************************************
#	NBODY
#**************************************************************************************************
# Sebastian Bustamante (Heidelberg Institute for Theoretical Studies)

#--------------------------------------------------------------------------------------------------
# From the next list you can activate/deactivate the options to be applied to your run. If you 
# modify some of these values, make sure that you recompile the code by typing "make clean; make 
# TreeCode"
#--------------------------------------------------------------------------------------------------
#Generate initial conditions
# OPT   +=  -DINITIAL_CONDITIONS
#Periodic conditions
OPT   +=  -DPERIODIC_BOX
#Potential energy
OPT   +=  -DEVAL_POTENTIAL

#--------------------------------------------------------------------------------------------------
# Find below the compilation options
#--------------------------------------------------------------------------------------------------

CC	= gcc

CFLAGS	= $(OPT)

LIBS	= -lm

EXEC   = Nbody

OBJS   = main.o  inout.o  physics.o  numeric.o

INCL   = allvars.h  proto.h  makefile

EDITOR = kate

#Compiling
$(EXEC): $(OBJS) 
	$(CC) $(OBJS) $(LIBS) -o  $(EXEC)

$(OBJS): $(INCL) 

edit:
	$(EDITOR) *.c *.h &

clean:
	rm -f $(OBJS) $(EXEC)