CC=gcc
AFLAGS=-Wall -g
LDFLAGS= -lmysqlclient
OBJS= add.cgi del.cgi mod.cgi sel.cgi adds.cgi score.cgi upscore.cgi scoredel.cgi Shielddel.cgi courseadd.cgi coursedel.cgi coursesel.cgi courseup.cgi schooladd.cgi schooldel.cgi schoolup.cgi schoolsel.cgi

all:$(OBJS)

$(OBJS):%.cgi:%.c
	$(CC) $(AFLAGS) $< cgic.c -o $@ $(LDFLAGS)

.PHONY:clean
clean:
	rm ./*.cgi
install:
		cp *.cgi /usr/lib/cgi-bin/sx

		cp *.html /var/www/html

	#	cp ~/github/cgi-stu/stu/index.html /var/www/html/index.html
		#cp ~/github/cgi-stu/stu/score.html /var/www/html/score.html
		#cp ~/github/cgi-stu/stu/course.html /var/www/html/course.html
