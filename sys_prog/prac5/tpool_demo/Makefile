CC = gcc

LDFLAGS += -lpthread

test:main.c thread_pool.c
	$(CC) $^ -o $@ $(LDFLAGS)

debug:main.c thread_pool.c
	$(CC) $^ -o $@ $(LDFLAGS) -DDEBUG

clean:
	$(RM) .*.sw? test debug *.o

.PHONY:all clean
