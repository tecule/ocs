ocs_server_SOURCES = ocs_server.c
ocs_server_OBJECTS = $(patsubst %c, %o, $(ocs_server_SOURCES))
PROGRAMS = ocs_server

CPPFLAGS = -I../../include
CFLAGS = -g -Wall
LDFLAGS = ../lib/log/liblog.a ../lib/net/libnet.a

all: $(PROGRAMS)

$(PROGRAMS): $(ocs_server_OBJECTS)
	gcc $(CFLAGS) -o $(PROGRAMS) $(ocs_server_OBJECTS) $(LDFLAGS) 

%.o: %.c
	gcc -c $(CPPFLAGS) $(CFLAGS) -o $@ $<

.PHONY: clean	
clean:
	rm -f $(PROGRAMS) $(ocs_server_OBJECTS)

