opt = -O3 -Wall -std=c2x

all: clean altermac

altermac: mac_spoofer.o
	# Indented with a tab character
	cc ${opt} mac_spoofer.o -o $@

mac_spoofer.o: mac_spoofer.c
	# Indented with a tab character
	cc ${opt} -c $^

clean:
	rm -f altermac *.o
