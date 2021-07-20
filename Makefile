
LIBFLAGS	= -lm

PROGRAMS	= hijridate

all: $(PROGRAMS)

hijridate: main.c hijri.c hijri.h
	gcc main.c hijri.c $(LIBFLAGS) -o hijridate

clean:
	rm *.out *.o
