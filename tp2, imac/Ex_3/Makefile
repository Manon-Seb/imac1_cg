CC       =  gcc
CFLAGS   = -Wall -O2 -g
LIB      = -I/Library/Frameworks/SDL.framework/Headers -I/opt/local/include `sdl-config --cflags --libs` -framework Cocoa -framework OpenGL
INCLUDES = -I/usr/X11R6/include

OBJ      = Ex3.o 
RM       = rm -f
BIN      = Ex3
DIRNAME  = $(shell basename $$PWD)
BACKUP   = $(shell date +`basename $$PWD`-%m.%d.%H.%M.tgz)
STDNAME  = $(DIRNAME).tgz

all : $(BIN)

$(BIN) : $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIB) $(INCLUDES)  -o $(BIN)
	@echo "--------------------------------------------------------------"
	@echo "                 to execute type: ./$(BIN) &"
	@echo "--------------------------------------------------------------"

Ex3.o : Ex3.c
	@echo "compile exercice"
	$(CC) $(CFLAGS) -c $<  
	@echo "done..."

clean :	
	@echo "**************************"
	@echo "CLEAN"
	@echo "**************************"
	$(RM) *~ $(OBJ) $(BIN) 

tar : clean 
	@echo "**************************"
	@echo "TAR"
	@echo "**************************"
	cd .. && tar cvfz $(BACKUP) $(DIRNAME)
