CC = gcc
CFLAGS = -Wall -Wextra -std=c99
TARGET = hangman

all: $(TARGET)

$(TARGET): hangman.o
	$(CC) $(CFLAGS) -o $(TARGET) hangman.o

hangman.o: hangman.c
	$(CC) $(CFLAGS) -c hangman.c

clean:
	rm -f *.o $(TARGET)
