CC = gcc
CFLAGC = -g -Wall -Wextra -Werror
SOURCES = my_tar.c
TARGET = my_tar

$(TARGET):$(SOURCES)
	$(CC) $(CFLAGC) -o $@ $^

clean:
	rm -f *.o

fclean: clean
	rm -f $(TARGET)

re: fclean all 