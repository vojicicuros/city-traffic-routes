#ifndef STAJALISTE_H
#define STAJALISTE_H

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Linija;

class Stajaliste {
public:
	Stajaliste();	//konstruktor
	Stajaliste(string naziv, int a) {
		this->naziv = naziv;
		this->sifra = a;
	}
	~Stajaliste();	//destruktor

	//pomocne funkcije
	string getNaziv() { return this->naziv; }
	int getSifra() { return this->sifra; }
	void addLinija(Linija* linija) { this->linije.push_back(linija); }
	vector<Linija*> zajednickeLinije(vector<Linija*>& stackLinije, string naziv);
	
	//print
	void printStajaliste();

	//info
	string stajalisteInfo();
private:
	int sifra;
	string naziv;
	vector<Linija*> linije ;
};


#endif // 