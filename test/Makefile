#Makefile

PROGRAM	= testfiledlg
OBJS	= testfiledlg.o

DEBUG   =

CC		= gcc
CFLAGS	= -Wall $(DEBUG)


.SUFFIXES: .c .o

$(PROGRAM): $(OBJS)
		$(CC) -o $(PROGRAM) $^

# suffix rule
.c.o:
		$(CC) $(CFLAGS) -c $<

.PHONY: clean
clean:
		$(RM) $(PROGRAM) $(OBJS)

