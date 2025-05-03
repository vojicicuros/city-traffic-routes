#include "Stajaliste.h"
#include "Linija.h"

Stajaliste::Stajaliste() {
}

Stajaliste::~Stajaliste() {
}

vector<Linija*> Stajaliste::zajednickeLinije(vector<Linija*>& stackLinije, string naziv) {
	for (int i = 0; i < this->linije.size(); i++) {
		int flag = 1;
		for (int j = 0; j < stackLinije.size(); j++) {
			if (this->linije[i]->getNaziv() == stackLinije[j]->getNaziv() || this->linije[i]->getNaziv()==naziv) { 
				flag = 0; break; 
			}
		}
		if (flag) {
			stackLinije.push_back(this->linije[i]);
		}
	}
	return stackLinije;
}

void Stajaliste::printStajaliste() {
	cout << this->sifra << " " << this->naziv << endl;
}

string Stajaliste::stajalisteInfo() {
	string info = to_string(this->sifra) + " " + this->naziv + " [";
	for (int i = 0; i < this->linije.size(); i++) {
		info.append(this->linije[i]->getNaziv());
		if (i != this->linije.size() - 1) info.append(" ");
	}
	info.append("]");
	return info;
}
