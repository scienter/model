EXEC = show
CC = gcc 
OBJS = main.o parameterSetting.o findparam.o boundary.o saveFile.o
INCL = parameter.h
LIBS = -lm
$(EXEC):$(OBJS)
	$(CC) $(OBJS) $(LIBS) -o $(EXEC)
$(OBJS):$(INCL)
clean:
	@rm -f *.o *~ $(EXEC)
