SUBDIRS = src # test

.PHONY: clean

all:
	for dir in $(SUBDIRS); do \
		$(MAKE) -C $$dir; \
	done
	
clean:
	for dir in $(SUBDIRS); do \
		$(MAKE) -C $$dir clean; \
	done