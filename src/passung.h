#ifndef PASSUNG_H
#define PASSUNG_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

#define PASUSENG_PATH "passungen/"

typedef struct toleranz_t {
	int es;
	int ei;
} toleranz_t;

typedef struct passung_t {
	int nennmass;
	char grundabmass;
	int toleranzgrad;

	int nennmassbereich;

	toleranz_t toleranz;
	double hoechstmass;
	double mindestmass;
} passung_t;

passung_t *passung_getInfo(char *passungStr);

void passung_printInfo(passung_t *passung);

void passung_vergleich(passung_t *passung0, passung_t *passung1);

#endif
