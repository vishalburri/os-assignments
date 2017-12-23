TARGET = thread sort
CC=gcc

all: $(TARGET)

%: %.c
	$(CC) $< -lpthread -o $@

clean:
	rm -f $(TARGET)
