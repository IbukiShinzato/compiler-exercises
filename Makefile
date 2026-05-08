PACKAGE = calculator
SRCS	= lex.c main.c token.c syntax.c
OBJS	= $(SRCS:.c=.o)
#HEADERS = 
CC	= gcc
CFLAGS	= -g -O2 -Wall

all: $(PACKAGE)

$(PACKAGE) : $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@

.o : $(SRCS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJS) *~ $(PACKAGE)
