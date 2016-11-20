KitraSample: main.o kitra_input.o kitra_output.o kitra_packet_generator.o kitra_small_utility.o
	cc -o KitraSample main.o kitra_input.o kitra_output.o kitra_packet_generator.o kitra_small_utility.o

main.o: main.c
	cc -c main.c
	
kitra_input.o: kitra_input.c kitra_input.h
	cc -c kitra_input.c
kitra_output.o: kitra_output.c kitra_output.h
	cc -c kitra_output.c
kitra_packet_generator.o: kitra_input.c kitra_packet_generator.h
	cc -c kitra_packet_generator.c
kitra_small_utility.o: kitra_small_utility.c kitra_small_utility.h
	cc -c kitra_small_utility.c
	
clean:
		rm KitraSample main.o kitra_input.o kitra_input.o kitra_output.o kitra_packet_generator.o kitra_small_utility.o