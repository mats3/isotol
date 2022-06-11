#include"passung.h"

int nennmassbereich[] = { 3, 6, 10, 14, 18, 24, 30, 40, 50, 65, 80, 100, 120, 140, 160, 180, 200, 225, 250, 280, 315, 355, 400, 450, 500 };

int getNennmassbereich(int nennmass) {
	for (int i = 0; i < 26; i++) {
		if (nennmass <= nennmassbereich[i]) {
			return i;
		}
	}

	return -1; 
}

passung_t *passung_getInfo(char *passungStr) {
	passung_t *passung = malloc(sizeof(passung_t));
	passung->nennmass = 0;

	int i = 0;
	while (passungStr[i] >= 0x30 && passungStr[i] <= 0x39) {
		passung->nennmass *= 10;
		passung->nennmass += (passungStr[i] - 0x30);	
		i++;
	}

	char *toleranzklasse = &passungStr[i];

	passung->grundabmass = passungStr[i++];

	while (passungStr[i] != '\0') {
		passung->toleranzgrad *= 10;
		passung->toleranzgrad += (passungStr[i] - 0x30);
		i++;
	}

	// es, ei
	int bereichPos = getNennmassbereich(passung->nennmass);
	char pathToPassung[50] = PASUSENG_PATH;
	strcat(pathToPassung, toleranzklasse);

	FILE *passungFile = fopen(pathToPassung, "r");

	for (int i = 0; i < bereichPos; i++) {
		char c;
		while ((c = fgetc(passungFile)) != '\n') { }
	}

	fscanf(passungFile, "%d,%d", &passung->toleranz.es, &passung->toleranz.ei); 

	passung->hoechstmass = passung->nennmass + (double)passung->toleranz.es / 1000;
	passung->mindestmass = passung->nennmass + (double)passung->toleranz.ei / 1000;

	return passung;
}

void passung_printInfo(passung_t *passung) {
	printf("Passung: %11d%c%d\n",
			passung->nennmass,
			passung->grundabmass,
			passung->toleranzgrad);
	printf("Nennmass: %10dmm\n", passung->nennmass);
	printf("[ES, es]: %10dμm\t(Oberes Grenzabmass)\n", passung->toleranz.es);
	printf("[EI, ei]: %10dμm\t(Unteres Grenzabmass)\n", passung->toleranz.ei);
	printf("Höchstmass: %8.3fmm\n", passung->hoechstmass);
	printf("Mindestmass: %7.3fmm\n", passung->mindestmass);
}

bool negativValues(int value) {
	if (value <= 0) { return true; }
	return false;
}

void passung_vergleich(passung_t *passung0, passung_t *passung1) {
	char passungsArt[50];
	int hoechstspiel;
	int hoechstuebermass;
	int mindestspiel;
	int mindestuebermass;

	hoechstspiel = passung0->toleranz.es - passung1->toleranz.ei;
	hoechstuebermass = passung1->toleranz.es - passung0->toleranz.ei;
	mindestspiel = passung0->toleranz.ei - passung1->toleranz.es;
	mindestuebermass = passung1->toleranz.ei - passung0->toleranz.es;

	if (negativValues(hoechstuebermass) && negativValues(mindestuebermass)) {
		strcpy(passungsArt, "Spielpassung");
	} else if (negativValues(hoechstspiel) && negativValues(mindestspiel)) {
		strcpy(passungsArt, "Presspassung");
	} else {
		strcpy(passungsArt, "Übergangspassung");
	}

	printf("Passung: %s\n", passungsArt);
	if (negativValues(hoechstspiel)) {
		printf("Höchstspiel: %7c\n", '-');
	} else { printf("Höchstspiel: %7dμm\n", hoechstspiel); }

	if (negativValues(hoechstuebermass)) {
		printf("Höchstübermass: %4c\n", '-');
	} else { printf("Höchstübermass: %4dμm\n", hoechstuebermass); }

	if (negativValues(mindestspiel)) {
		printf("Mindestspiel: %6c\n", '-');
	} else { printf("Mindestspiel: %6dμm\n", mindestspiel); }

	if (negativValues(mindestuebermass)) {
		printf("Mindestübermass: %3c\n", '-');
	} else { printf("Mindestübermass: %3dμm\n", mindestuebermass); }
}
