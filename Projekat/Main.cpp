
#include "GradskaMreza.h"
#include "Linija.h"
#include "Stajaliste.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

void main() {
	cout << "Dobrodosli u simulator mreze gradskog prevoza. Molimo Vas, odaberite opciju:" << endl;
	cout << "1. Ucitavanje podataka o mrezi gradskog prevoza" << endl;
	cout << "0. Kraj rada" << endl;

	int odluka1;
	cin >> odluka1;

	if (odluka1 == 1) {
		string linijePutanja, stajalistaPutanja;
		cout << "Molimo Vas, unesite putanju do fajla sa stajalistima:" << endl;
		stajalistaPutanja = "stajalista.txt";	//PROMENI AAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
		cout << "Molimo Vas, unesite putanju do fajla sa linijama gradskog prevoza:" << endl;
		linijePutanja = "linije.txt";

		GradskaMreza* gradskaMreza = new GradskaMreza;
		gradskaMreza->ucitajStajalistaFajl(stajalistaPutanja);
		gradskaMreza->ucitajLinijeFajl(linijePutanja);

		cout << "Mreza gradskog prevoza je uspesno ucitana. Molim Vas, odaberite opciju:" << endl;
		
		/*cout << "LINIJE: \n";
		gradskaMreza->printLinije();	//pomocni printevi
		cout << "\n\n";
		cout << "STAJALISTA: \n";
		gradskaMreza->printStajalista();
		cout << "\n\n";*/

		while (1) {
			
			cout << "1. Prikaz informacija o stajalistu" << endl;
			cout << "2. Prikaz osnovnih informacija o liniji gradskog prevoza" << endl;
			cout << "3. Prikaz statistickih informacija o liniji gradskog prevoza" << endl;
			cout << "4. Pronalazak najkrace putanje izmedju dva stajalista (BFS metoda)" << endl;
			cout << "5. Pronalazak putanje izmedju dva stajalista sa najmanjim brojem presedanja (DFS metoda)" << endl;
			cout << "0. Kraj rada" << endl;
			int odluka2;
			cin >> odluka2;
			string sifra;
			switch (odluka2) {
			case 1:
				cout << "Molimo Vas, unesite sifru stajalista cije osnovne informacije zelite da prikazete." << endl;
				cin >> sifra;
				gradskaMreza->infoStajaliste(sifra);
				cout << "Generisan je fajl sa osnovnim informacijama o stajalistu." << endl;
				break;
			case 2:
				cout << "Molimo Vas, unesite oznaku linije cije osnovne informacije zelite da prikazete." << endl;
				cin >> sifra;
				gradskaMreza->infoLinija(sifra);
				cout << "Generisan je fajl sa osnovnim informacijama o liniji." << endl;
				break;
			case 3:
				cout << "Molimo Vas, unesite oznaku linije ciju statistiku zelite da prikazete." << endl;
				cin >> sifra;
				gradskaMreza->statistikaLinija(sifra);
				cout << "Generisan je fajl sa osnovnim informacijama o liniji." << endl;
				break;
			case 4:
			{
				string pocetna, krajnja;
				sifra = "";
				cout << "Molimo Vas, unesite oznaku pocetnog stajalista za pronalazenje najkrace putanje." << endl;
				cin >> pocetna;
				cout << "Molimo Vas, unesite oznaku krajnjeg stajalista za pronalazenje najkrace putanje." << endl;
				cin >> krajnja;
				gradskaMreza->najkracaPutanja(pocetna, krajnja);
				cout << "Generisan je fajl sa informacijama o najkracoj putanji izmedju pocetneg i krajnjeg stajalista." << endl;
				break;
			}
			case 5:
			{
				string pocetna, krajnja;
				sifra = "";
				cout << "Molimo Vas, unesite oznaku pocetnog stajalista za pronalazenje putanje sa najmanjim brojem presedanja." << endl;
				cin >> pocetna;
				cout << "Molimo Vas, unesite oznaku krajnjeg stajalista za pronalazenje putanje sa najmanjim brojem presedanja." << endl;
				cin >> krajnja;
				gradskaMreza->najkracaPutanja2(pocetna, krajnja);
				cout << "Generisan je fajl sa informacijama o putanji izmedju pocetneg i krajnjeg stajalista sa najmanjim brojem presedanja." << endl;
				break;
			}
			case 0:
				return;
			}
		}

		delete gradskaMreza;
	}
	else return;
}