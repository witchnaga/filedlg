#Makefile

PROGRAM	= filedlg
OBJS	= filedlg.o ../command.o ../entry.o

DEBUG   =

CC		= gcc
CFLAGS	= -Wall $(DEBUG)
LDFLAGS = $$(pkg-config --cflags --libs gtk+-2.0)


.SUFFIXES: .c .o

$(PROGRAM): $(OBJS)
		$(CC) $(LDFLAGS) -o $(PROGRAM) $^

# suffix rule
.c.o:
		$(CC) $(LDFLAGS) $(CFLAGS) -c $<

.PHONY: clean
clean:
		$(RM) $(PROGRAM) $(OBJS)

