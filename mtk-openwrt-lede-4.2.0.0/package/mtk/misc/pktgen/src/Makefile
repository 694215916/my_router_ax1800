all: ethernet_pt 

ethernet_pt: ethernet_test_thread.o
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ ethernet_test_thread.o
#	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^ -lpthread

romfs:
	$(ROMFSINST) /bin/ethernet_pt

clean:
	-rm -f ethernet_pt *.elf *.gdb *.o

