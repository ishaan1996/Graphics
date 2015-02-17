INCLUDE = -I/usr/include/
LIBDIR  = -L/usr/X11R6/lib 
CC = g++

ifeq ($(shell uname),Darwin)
	CFLAGS = -Wall  $(COMPILERFLAGS) $(INCLUDE) $(LIBDIR)
else
	CFLAGS = -Wall
endif

PROG = top

SRCS = main.cpp

ifeq ($(shell uname),Darwin)
	LIBS = -framework OpenGL -framework GLUT -framework CoreFoundation 
else
	LIBS = -lglut -lGL -lGLU 
endif



all: $(PROG)

$(PROG):	$(SRCS)
	$(CC) $(CFLAGS) -o $(PROG) $(SRCS) $(LIBS)

clean:
	rm -f $(PROG)
