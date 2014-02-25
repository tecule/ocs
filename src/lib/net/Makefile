libnet_a_SOURCES = common.c
libnet_a_OBJECTS = $(patsubst %c, %o, $(libnet_a_SOURCES))
LIBRARY = libnet.a

AR = ar
RANLIB = ranlib

CPPFLAGS = -I../../include
CFLAGS = -g -Wall
ARFLAGS = cru

all: $(LIBRARY)

$(LIBRARY): $(libnet_a_OBJECTS)
	$(AR) $(ARFLAGS) $(LIBRARY) $(libnet_a_OBJECTS)
	$(RANLIB) $(LIBRARY)

%.o: %.c
	gcc -c $(CPPFLAGS) $(CFLAGS) -o $@ $<

.PHONY: clean
clean:
	rm -f $(LIBRARY) $(libnet_a_OBJECTS)

