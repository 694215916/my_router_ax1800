EXEC = mtdc_test

all: $(EXEC)

mtdc_test: mtdc_test.o
	$(CC) $(LDFLAGS) -o $@ $^ $(LDLIBS)
clean:
	-rm -f $(EXEC) *.elf *.gdb *.o

