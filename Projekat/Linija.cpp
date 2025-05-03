#include "Linija.h"

Linija::Linija() {
}

Linija::~Linija() {

}

int Linija::brPolazaka() {
	return ((this->kraj_sat - this->start_sat) * 60 + this->kraj_min - this->start_min) / this->minuti + 1;
}

vector<Linija*> Linija::zajednickeLinije() {
	string text;
	vector<Linija*> stackLinije;
	for (int i = 0; i < this->stajalista.size(); i++) {
		this->stajalista[i]->zajednickeLinije(stackLinije, this->naziv);
	}
	return stackLinije;
}

void Linija::printLinija() {
	cout << this->naziv << " [" << this->start_sat << ":" << this->start_min << "-" << this->kraj_sat << ":" << this->kraj_min << "#" << this->minuti << "] ";
	for (int i = 0; i < this->stajalista.size(); i++) cout << this->stajalista[i]->getSifra() << " ";
	cout << endl;
}

string Linija::linijaInfo() {
	string info = this->naziv + " " + this->stajalista[0]->getNaziv() + "->" + this->stajalista[this->stajalista.size() - 1]->getNaziv() + "\n";
	for (int i = 0; i < this->stajalista.size(); i++) {
		info.append(to_string(this->stajalista[i]->getSifra()) + " " + this->stajalista[i]->getNaziv() + "\n");
	}

	return info;
}
