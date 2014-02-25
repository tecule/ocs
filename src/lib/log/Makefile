liblog_a_SOURCES = log.c
liblog_a_OBJECTS = $(patsubst %c, %o, $(liblog_a_SOURCES))
LIBRARY = liblog.a

AR = ar
RANLIB = ranlib

CPPFLAGS = -I../../include
CFLAGS = -g -Wall
ARFLAGS = cru

all: $(LIBRARY)

$(LIBRARY): $(liblog_a_OBJECTS)
	$(AR) $(ARFLAGS) $(LIBRARY) $(liblog_a_OBJECTS)
	$(RANLIB) $(LIBRARY)

%.o: %.c
	gcc -c $(CPPFLAGS) $(CFLAGS) -o $@ $<

.PHONY: clean
clean:
	rm -f $(LIBRARY) $(liblog_a_OBJECTS)

