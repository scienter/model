EXEC = show
CC = gcc 
OBJS = main.o parameterSetting.o findparam.o boundary_PS.o saveFile.o laser.o updateMomenta_PS.o updatePosition_PS.o
INCL = parameter.h
LIBS = -lm
$(EXEC):$(OBJS)
	$(CC) $(OBJS) $(LIBS) -o $(EXEC)
$(OBJS):$(INCL)
clean:
	@rm -f *.o *~ $(EXEC)
