#ifndef LINIJA_H
#define LINIJA_H

#include "Stajaliste.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Linija {
public:
	Linija();	//default konstruktor
	Linija(string naziv, int a, int b, int c, int d, int e) {
		this->naziv = naziv;
		this->start_sat = a; this->start_min = b;
		this->kraj_sat = c; this->kraj_min = d;
		this->minuti = e;
	}
	~Linija();	//destruktor

	//pomocne funkcije
	string getNaziv() { return this->naziv; }
	void addStajaliste(Stajaliste* stajaliste) { this->stajalista.push_back(stajaliste); }
	int brPolazaka();
	vector<Linija*> zajednickeLinije();
	int getBrStajalista() { return this->stajalista.size(); };
	Stajaliste* getStajaliste(int i) { return this->stajalista[i]; }

	//print
	void printLinija();
	string linijaInfo();
protected:

private:
	string naziv;
	int start_sat;
	int start_min;
	int kraj_sat;
	int kraj_min;
	int minuti;
	vector<Stajaliste*> stajalista;
};

#endif // !LINIJA_H
