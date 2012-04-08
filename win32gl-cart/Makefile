
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
CFLAGS =  -O2 #-std=gnu++0x
else
CFLAGS =  -g #-std=gnu++0x
endif

CINCL_COMM = -I./

INCLS = $(CINCL_COMM)

MACRO = #Nothing yet

CLIB_GL = -lopengl32
CLIB_PUB = ${CLIB_GL} -lGdi32

LIBS =  $(CLIB_PUB) 

APP=win32gl-cart

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



