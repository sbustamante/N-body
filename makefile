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
#Print Tree information
# OPT   +=  -DPRINT_TREE
#Print Particles Forces
OPT   +=  -DPRINT_FORCES

#--------------------------------------------------------------------------------------------------
# Find below the compilation options
#--------------------------------------------------------------------------------------------------

CC	= gcc

CFLAGS	= $(OPT)

LIBS	= -lm

EXEC   = Nbody

OBJS   = main.o  inout.o  force.o

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