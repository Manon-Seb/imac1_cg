CC       =  gcc
CFLAGS   = -Wall -O2 -g
LIB      = -I/Library/Frameworks/SDL.framework/Headers -I/opt/local/include `sdl-config --cflags --libs` -framework Cocoa -framework OpenGL
INCLUDES = -I/usr/X11R6/include

OBJ      = correction_td01.o 
RM       = rm -f
BIN      = correction_td01
DIRNAME  = $(shell basename $$PWD)
BACKUP   = $(shell date +`basename $$PWD`-%m.%d.%H.%M.tgz)
STDNAME  = $(DIRNAME).tgz

all : $(BIN)

$(BIN) : $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIB) $(INCLUDES)  -o $(BIN)
	@echo "--------------------------------------------------------------"
	@echo "                 to execute type: ./$(BIN) &"
	@echo "--------------------------------------------------------------"

correction_td01.o : correction_td01.c
	@echo "compile correction_td01"
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
