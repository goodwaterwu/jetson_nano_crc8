include Makefile.in

OBJS = crc8.o
EXECFILE = crc8

.PHONY: all

all: crc8

.PHONY: crc8

crc8: $(OBJS)
	@$(CC) $(OBJS) $(CFLAGS) $(LDFLAGS) $(LIBS) -o $@
	$(info package compiled)

%.o: %.c
	$(CC) -c $< $(CFLAGS) $(LDFLAGS) $(LIBS) -o $@

.PHONY: strip

strip:
	$(STRIP) $(EXECFILE)

.PHONY: install

install:
	@install -d $(DESTDIR)/sbin $(DESTDIR)/include
	@install -m 755 $(EXECFILE) $(DESTDIR)/sbin
	@install -m 755 *.h $(DESTDIR)/include
	$(info package installed)

.PHONY: uninstall

uninstall:
	@rm -rf $(INSTALLDIR)
	$(info package removed)

.PHONY: clean

clean:
	@rm $(OBJS) $(EXECFILE)
	$(info package cleaned)
