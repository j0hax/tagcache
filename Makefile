CC = gcc
CFLAGS = -Wall
PREFIX = /usr/local

tagcache: clean
	$(CC) tagcache.c -o tagcache

install: tagcache
	mkdir -p $(DESTDIR)$(PREFIX)/bin
	mv tagcache $(DESTDIR)$(PREFIX)/bin
	chmod 755 $(DESTDIR)$(PREFIX)/bin/tagcache

clean:
	rm -fv tagcache *.o *.a *.so

check: tagcache
	./tagcache
	rm CACHEDIR.TAG
