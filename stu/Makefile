CC=gcc
AFLAGS=-Wall -g
LDFLAGS= -lmysqlclient
OBJS= add.cgi del.cgi mod.cgi sel.cgi adds.cgi score.cgi upscore.cgi

all:$(OBJS)

$(OBJS):%.cgi:%.c
	$(CC) $(AFLAGS) $< cgic.c -o $@ $(LDFLAGS)

.PHONY:clean
clean:
	rm ./*.cgi
install:
		cp *.cgi /usr/lib/cgi-bin/sx

		cp ~/github/cgi-stu/stu/index.html /var/www/html/index.html
