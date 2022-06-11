#include<stdlib.h>
#include"passung.h"

int main(int argc, char **argv) {
	if (argc == 2) {
		passung_t *passung = passung_getInfo(argv[1]);
		passung_printInfo(passung);
	}
	if (argc == 3) {
		passung_t *passung0 = passung_getInfo(argv[1]);
		passung_printInfo(passung0);
		printf("---------------\n");
		passung_t *passung1 = passung_getInfo(argv[2]);
		passung_printInfo(passung1);
		printf("---------------\n");
		passung_vergleich(passung0, passung1);
	}

	return EXIT_SUCCESS;
}
