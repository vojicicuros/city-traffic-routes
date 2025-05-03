#ifndef GRADSKA_MREZA_H
#define GRADSKA_MREZA_H

#include "Linija.h"
#include "Stajaliste.h"
#include "Graph.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <list>
#include <map>

using namespace std;


//struktura koju koristimo za funkciju presedanja
struct strukturaPresedanja {
	strukturaPresedanja(int a, Linija* b) {
		stanica = a; prevoz = b;
	}
	int stanica;
	Linija* prevoz;
};

class GradskaMreza {
public:
	GradskaMreza();		//konstruktor 
	~GradskaMreza();	//destruktor

	//ucitavanje
	void ucitajLinijeFajl(const string& filepath);
	void ucitajStajalistaFajl(const string& filepath);

	//info funkcije
	void infoLinija(const string& sifra);
	void infoStajaliste(const string& sifra);

	//staticke informacije za liniju
	void statistikaLinija(const string& sifra);

	//najkraca putanja izmedju 2 stajalista
	void najkracaPutanja(const string& pocetna, const string& krajnja);
	string bfsMreza(Stajaliste* from, Stajaliste* to);

	//najmanji broj presedanja
	void najkracaPutanja2(const string& pocetna, const string& krajnja);
	string dfsMreza(Stajaliste* from, Stajaliste* to);
	void brPresedanja(vector<Stajaliste*> ruta, int redniBrRute, vector<int>& presedanjaBrojac, map<int, int> mymap);

	//print pomocni
	void printLinije();
	void printStajalista();

private:
	vector<Linija*> linije;
	vector<Stajaliste*> stajalista;

	Graph* mrezaGraf;

	void ucitajLiniju(const string& myLine);
	void ucitajStajaliste(const string& myLine);

	Linija* nadjiLiniju(const string& sifra);
	Stajaliste* nadjiStajaliste(const string& sifra);

	vector<vector<strukturaPresedanja*>> presedanja;

	//string printLinijaInfo(Linija* linija);
	//string printStajalisteInfo(Stajaliste* stajaliste);
};



#endif // !GRADSKA_MREZA_H
