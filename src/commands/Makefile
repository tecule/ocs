ocsnodes_SOURCES = ocsnodes.c
ocsnodes_OBJECTS = $(patsubst %c, %o, $(ocsnodes_SOURCES))
PROGRAMS = ocsnodes

CPPFLAGS = -I../../include
CFLAGS = -g -Wall
LDFLAGS = ../lib/log/liblog.a ../lib/net/libnet.a

all: $(PROGRAMS)

ocsnodes: $(ocsnodes_OBJECTS)
	gcc $(CFLAGS) -o ocsnodes $(ocsnodes_OBJECTS) $(LDFLAGS) 

%.o: %.c
	gcc -c $(CPPFLAGS) $(CFLAGS) -o $@ $<

.PHONY: clean	
clean:
	rm -f $(PROGRAMS) $(ocsnodes_OBJECTS)

