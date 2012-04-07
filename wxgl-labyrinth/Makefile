
ifeq "$(APPDIR)" ""
APPDIR=.
endif

OUTDIR=${APPDIR}/bin
OBJDIR=${APPDIR}/obj
OUTLIBDIR=${APPDIR}/lib
INCDIR=${APPDIR}/inc
SRCDIR=${APPDIR}

ifeq "$(ECHORESULT)" "1"
CC=g++
AR=ar -c
RM=rm
ECHO=echo
else
CC=@g++
AR=@ar -c
RM=@rm
ECHO=@echo
endif

ifeq "$(TARGET)" "release"
CFLAGS =  -O2 # -std=gnu++0x
else
CFLAGS =  -g # -std=gnu++0x
endif

WX_SOURCE_ROOT=U:\wxWidgets

CINCL_WX = -I${WX_SOURCE_ROOT}\include -I${WX_SOURCE_ROOT}\lib\gcc_dll\mswud
CINCL_COMM = -I. 

INCLS = $(CINCL_COMM) ${CINCL_WX}

MACRO = #Nothing yet

CLIB_WX = -L${WX_SOURCE_ROOT}\lib\gcc_dll -lwxmsw29ud -lwxmsw29ud_gl
CLIB_GL = -L./lib -lopengl32 -lglu32 -lglut32
CLIB_PUB = ${CLIB_GL} ${CLIB_WX}

LIBS =  $(CLIB_PUB) -L../lib 

APP=wxgl-labyrinth

APP_SRC=$(notdir $(wildcard ${SRCDIR}/*.cpp))
APP_OBJ=$(patsubst %.c,%.o,$(patsubst %.cpp,%.o,${APP_SRC}))

all : ${APP} 

vpath %.cpp ${SRCDIR} #:${SRCDIR}/other_src
vpath %.c   ${SRCDIR} #:${SRCDIR}/other_src

%.o: %.cpp
	@echo "In Compling $< ......"
	${ECHO} $(CC) $(CFLAGS) $(MACRO) -c -o $@ $< $(INCLS)
	$(CC) $(CFLAGS) $(MACRO) -c -o $@ $< $(INCLS)
	@echo "OK"
    
%.o: %.c
	@echo "In Compling $< ......"
	${ECHO} $(CC) $(CFLAGS) $(MACRO) -c -o $@ $< $(INCLS)
	$(CC) $(CFLAGS) $(MACRO) -c -o $@ $< $(INCLS)
	@echo "OK"

${APP} : $(APP_OBJ)
	@echo "In process of link $@ ...... "
	${ECHO} ${CC} -o $@ $(CFLAGS) $^ $(LIBS)
	${CC} -o $@ $(CFLAGS) $^ $(LIBS)
	@echo "OK"

clean :
	rm -f ${APP} ${APP}.exe ${APP_OBJ}
	
run : ${APP}
	${APP}



