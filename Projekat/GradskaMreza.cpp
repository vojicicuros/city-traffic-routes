#include "GradskaMreza.h"

//konstruktor
GradskaMreza::GradskaMreza() {

}

//destruktor
GradskaMreza::~GradskaMreza() {
	//brisanje vektora linija
	for (int i = 0; i < this->linije.size(); i++) {
		delete this->linije[i];
	}
	this->linije.clear();

	//brisanje vektora stajalista
	for (int i = 0; i < this->stajalista.size(); i++) {
		delete this->stajalista[i];
	}
	this->stajalista.clear();

	//brisanje grafa (adjacency matrix)
	delete this->mrezaGraf;

	//brisanje vektora presedanja
	for (int i = 0; i < this->presedanja.size(); i++) {
		for (int j = 0; j < this->presedanja[i].size(); j++) {
			delete this->presedanja[i][j];
		}
		this->presedanja[i].clear();
	}
}



void GradskaMreza::ucitajStajalistaFajl(const string& filepath) {
	//otvara fajl za citanje
	ifstream my_file;
	my_file.open(filepath);
	//cita liniju po liniju
	string my_line;
	if (my_file.is_open()) {
		while (getline(my_file, my_line))
			ucitajStajaliste(my_line);
	}
	//zatvara fajl
	my_file.close();
}

void GradskaMreza::ucitajStajaliste(const string& myLine) {
	int pos = 0, cnt = 0, curr, sifra_broj;
	string naziv, sifra;
	while (myLine[pos] != ' ') { pos++; cnt++; }
	//sifra stajalista
	sifra.append(myLine, 0, cnt); sifra_broj = stoi(sifra);
	pos++; cnt = 0;
	//naziv stajalista
	curr = pos;
	while (myLine[pos] != '\0') { pos++; cnt++; }
	naziv.append(myLine, curr, cnt);

	//inicijalizovanje i dodavanje novog stajalista u vektor
	Stajaliste* novo_stajaliste = new Stajaliste(naziv, sifra_broj);
	this->stajalista.push_back(novo_stajaliste);
}

void GradskaMreza::ucitajLinijeFajl(const string& filepath) {
	//otvara fajl za citanje
	ifstream my_file;
	my_file.open(filepath);
	//cita liniju po liniju
	string my_line;
	if (my_file.is_open()) {
		while (getline(my_file, my_line))
			ucitajLiniju(my_line);
	}
	//zatvara fajl
	my_file.close();
}

void GradskaMreza::ucitajLiniju(const string& myLine) {
	//sredjivanje imena;
	int pos = 0, cnt = 0, curr;
	string naziv, time_a, time_b, time_c, time_d, time_e;
	while (myLine[pos] != ' ') { pos++; cnt++; }
	naziv.append(myLine, 0, cnt);
	pos += 2; cnt = 0; curr = pos;
	while (myLine[pos] != ':') { pos++; cnt++; } time_a.append(myLine, curr, cnt);
	int a = stoi(time_a);
	pos ++; cnt = 0; curr = pos;
	while (myLine[pos] != '-') { pos++; cnt++; } time_b.append(myLine, curr, cnt);
	int b = stoi(time_b);
	pos++; cnt = 0; curr = pos;
	while (myLine[pos] != ':') { pos++; cnt++; } time_c.append(myLine, curr, cnt);
	int c = stoi(time_c);
	pos++; cnt = 0; curr = pos;
	while (myLine[pos] != '#') { pos++; cnt++; } time_d.append(myLine, curr, cnt);
	int d = stoi(time_d);
	pos++; cnt = 0; curr = pos;
	while (myLine[pos] != ']') { pos++; cnt++; } time_e.append(myLine, curr, cnt);
	int e = stoi(time_e);

	//incijalizovanje objekta Linija
	Linija* nova_linija = new Linija(naziv, a, b, c, d, e);

	//ucitavanje brojeva stajalista za novu Liniju
	pos++;
	while (myLine[pos] != '\0') {
		pos++; cnt = 0; curr = pos;
		int stanica_broj;
		string stanica;
		while (myLine[pos] != ' ' && myLine[pos] != '\0') { pos++; cnt++; }
		stanica.append(myLine, curr, cnt);
		stanica_broj = stoi(stanica);
		for (int i = 0; i < this->stajalista.size(); i++) {
			if (this->stajalista[i]->getSifra() == stanica_broj) {
				nova_linija->addStajaliste(this->stajalista[i]);
				this->stajalista[i]->addLinija(nova_linija);
				break;
			}
		}
	}

	//dodavanje nove linije u vektor svih linija
	this->linije.push_back(nova_linija);
}

void GradskaMreza::infoLinija(const string& sifra) {
	//otvara fajl za pisanje
	ofstream my_file;
	Linija* selektovanaLinija = nadjiLiniju(sifra);
	if (selektovanaLinija) {
		string filepath = "linija_" + selektovanaLinija->getNaziv() + ".txt";
		my_file.open(filepath);
		if (my_file.is_open()) {
			my_file << selektovanaLinija->linijaInfo();
		}
	}
	//zatvara fajl
	my_file.close();

}

void GradskaMreza::infoStajaliste(const string& sifra) {
	//otvara fajl za pisanje
	ofstream my_file;
	Stajaliste* selektovanoStajaliste = nadjiStajaliste(sifra);
	if (selektovanoStajaliste) {
		string filepath = "stajaliste_" + to_string(selektovanoStajaliste->getSifra()) + ".txt";
		my_file.open(filepath);
		if (my_file.is_open()) {
			my_file << selektovanoStajaliste->stajalisteInfo();
		}
	}
	//zatvara fajl
	my_file.close();
}

void GradskaMreza::statistikaLinija(const string& sifra) {
	//otvara fajl za pisanje
	ofstream my_file;
	Linija* selektovanaLinija = nadjiLiniju(sifra);
	if (selektovanaLinija) {
		string filepath = "statistika_" + selektovanaLinija->getNaziv() + ".txt";
		my_file.open(filepath);
		if (my_file.is_open()) {
			string text = selektovanaLinija->getNaziv() + "\n";
			vector<Linija*> stackLinije = selektovanaLinija->zajednickeLinije();
			for (int i = 0; i < stackLinije.size(); i++) {
				if (stackLinije[i]->getNaziv() != selektovanaLinija->getNaziv()) {
					text.append(stackLinije[i]->getNaziv());
					text.append(" ");
				}
			}
			text.append("\n");
			text.append(to_string(selektovanaLinija->brPolazaka()));
			my_file << text;
		}
	}
	//zatvara fajl
	my_file.close();
}

void GradskaMreza::najkracaPutanja(const string& pocetna, const string& krajnja) {
	//otvara fajl za pisanje
	ofstream my_file;
	Stajaliste* pocetnoStajaliste = this->nadjiStajaliste(pocetna);
	Stajaliste* krajnjeStajaliste = this->nadjiStajaliste(krajnja);
	if (pocetnoStajaliste && krajnjeStajaliste) {
		string filepath = "putanja_" + to_string(pocetnoStajaliste->getSifra()) + "_" + to_string(krajnjeStajaliste->getSifra()) + ".txt";
		my_file.open(filepath);
		if (my_file.is_open()) {
			string text = bfsMreza(pocetnoStajaliste, krajnjeStajaliste);
			my_file << text;
		}
	}
	//zatvara fajl
	my_file.close();
}

//BFS koji vraca sredjen string koji se upisuje u fajl
string GradskaMreza::bfsMreza(Stajaliste* from, Stajaliste* to) {
	//BFS ALGORITHM
	string text;

	//graf
	this->mrezaGraf = new Graph(this->stajalista.size(), this->linije.size());	
	
	//mapa
	map<int, int> mymap;
	for (int i = 0; i < this->stajalista.size(); i++) {
		mymap.insert(pair<int, int>(this->stajalista[i]->getSifra(), i));
	}

	//pravljenje matrice
	for (int i = 0; i < this->linije.size(); i++) {
		for (int j = 0; j < this->linije[i]->getBrStajalista() - 1; j++) {
			int a = this->linije[i]->getStajaliste(j)->getSifra();
			int b = this->linije[i]->getStajaliste(j+1)->getSifra();
			mrezaGraf->addEdge(mymap.at(a), mymap.at(b));
			mrezaGraf->addLinija(mymap.at(a), mymap.at(b), this->linije[i], i);
		}
	}

	//pozivanje bfs funkcije za graf
	vector<int> putanja = mrezaGraf->bfs(mymap.at(from->getSifra()), mymap.at(to->getSifra()), mymap);
	vector<Stajaliste*> output;
	for (int i = 0; i < putanja.size(); i++) output.push_back(this->stajalista[putanja[i]]);
	
	//string text
	Linija* tekuci = nullptr, * stari = nullptr;
	for (int i = 0; i < putanja.size() - 1; i++) {
		vector<Linija*> prevoz = mrezaGraf->getLinije(putanja[i], putanja[i + 1]);
		for (int j = 0; j < prevoz.size(); j++) 
			if (prevoz[j]) {
				tekuci = prevoz[j]; 
				break;
			}
		if (i == 0) text.append("->" + tekuci->getNaziv() + "\n");
		text.append(to_string(output[i]->getSifra()));
		if (stari && (stari != tekuci)) {
			text.append("\n" + stari->getNaziv() + "->" + tekuci->getNaziv() + "\n");
			text.append(to_string(output[i]->getSifra()) + " ");
		}
		else {
			text.append(" ");
		}
		if (i == putanja.size() - 2) {
			text.append(to_string(output[i+1]->getSifra()));
		}

		stari = tekuci;
		
	}

	//print putanje u konzoli
	for (int i = 0; i < putanja.size(); i++) cout << this->stajalista[putanja[i]]->getSifra() << " ";
	cout << endl;

	return text;
}

void GradskaMreza::najkracaPutanja2(const string& pocetna, const string& krajnja) {
	//otvara fajl za pisanje
	ofstream my_file;
	Stajaliste* pocetnoStajaliste = this->nadjiStajaliste(pocetna);
	Stajaliste* krajnjeStajaliste = this->nadjiStajaliste(krajnja);
	if (pocetnoStajaliste && krajnjeStajaliste) {
		string filepath = "putanja_" + to_string(pocetnoStajaliste->getSifra()) + "_" + to_string(krajnjeStajaliste->getSifra()) + ".txt";
		my_file.open(filepath);
		if (my_file.is_open()) {
			string text = dfsMreza(pocetnoStajaliste, krajnjeStajaliste);
			my_file << text;
		}
	}
	//zatvara fajl
	my_file.close();
}

//DFS koji vraca sredjen string koji se upisuje u fajl
string GradskaMreza::dfsMreza(Stajaliste* from, Stajaliste* to) {
	string text;

	//graf
	this->mrezaGraf = new Graph(this->stajalista.size(), this->linije.size());

	//mapa
	map<int, int> mymap;
	for (int i = 0; i < this->stajalista.size(); i++) {
		mymap.insert(pair<int, int>(this->stajalista[i]->getSifra(), i));
	}

	//pravljenje matrice 
	for (int i = 0; i < this->linije.size(); i++) {
		for (int j = 0; j < this->linije[i]->getBrStajalista() - 1; j++) {
			int a = this->linije[i]->getStajaliste(j)->getSifra();
			int b = this->linije[i]->getStajaliste(j + 1)->getSifra();
			mrezaGraf->addEdge(mymap.at(a), mymap.at(b));
			mrezaGraf->addLinija(mymap.at(a), mymap.at(b), this->linije[i], i);
		}
	}

	//pozivanje dfs funkcije za graf 
	vector<vector<int>> putanje = mrezaGraf->dfs(mymap.at(from->getSifra()), mymap.at(to->getSifra()), mymap);

	//vektor vektora output; sve rute po stajalistima od pocetne do krajnje stanice
	vector<vector<Stajaliste*>> output;
	for (int i = 0; i < putanje.size(); i++) {
		vector<Stajaliste*> pom;
		for (int j = 0; j < putanje[i].size(); j++)
			pom.push_back(this->stajalista[putanje[i][j]]);
		output.push_back(pom);
	}

	//brojanje presedanja
	vector<int> presedanjaBrojac (putanje.size(), 0);
	for (int i = 0; i < putanje.size(); i++) {
		brPresedanja(output[i], i, presedanjaBrojac, mymap);
	}

	//selektovanje rute sa najmanje presedanja
	int min = presedanjaBrojac[0], minIndex = 0;
	for (int i = 1; i < presedanjaBrojac.size(); i++) {
		if (presedanjaBrojac[i] < min) {
			min = presedanjaBrojac[i];
			minIndex = i;
		}
	}
	vector<Stajaliste*> selektovanaRuta = output[minIndex];
	vector<strukturaPresedanja*> selektovanaPresedanja;
	for (int i = 0; i < this->presedanja[minIndex].size(); i++)
		selektovanaPresedanja.push_back(this->presedanja[minIndex][i]);

	//print svih ruta od pocetnog do krajnjeg stajalista
	for (int i = 0; i < presedanja.size(); i++) {
		cout << presedanjaBrojac[i] << endl;
		for (int j = 0; j < output[i].size(); j++) {
			cout << output[i][j]->getSifra() << " ";
		}
		cout << "\n";
	}

	//string text
	int j = 0;
	for (int i = 0; i < selektovanaRuta.size(); i++) {
		if (j < selektovanaPresedanja.size() && (selektovanaRuta[i]->getSifra() == selektovanaPresedanja[j]->stanica)) {
			if (i == 0) text.append("->" + selektovanaPresedanja[j]->prevoz->getNaziv() + "\n");
			else {
				text.append(" " + to_string(selektovanaRuta[i]->getSifra()));
				text.append("\n" + selektovanaPresedanja[j - 1]->prevoz->getNaziv() + "->" + selektovanaPresedanja[j]->prevoz->getNaziv() + "\n");
				//expception za selektovanaPresedanja[j]->prevoz==NULL
			}
			j++;
		}
		else {
			text.append(" ");
		}

		text.append(to_string(selektovanaRuta[i]->getSifra()));
		
	}


	return text;
}

void GradskaMreza::brPresedanja(vector<Stajaliste*> ruta,int redniBrRute, vector<int>& presedanjaBrojac, map<int, int> mymap) {

	//vector<int> cntLinije(this->linije.size(), 0);
	vector<Linija*> tekuci, stari;

	//inicijalizovanje starog nullptr-a
	for (int i = 0; i < this->linije.size(); i++) 
		stari.push_back(nullptr);

	vector<strukturaPresedanja*> vektorPresedanje;
	for (int i = 0; i < ruta.size() - 1; i++) {
		//vektor intova za brojanje svake od linija da bismo videli kojom linijom najduze idemo do presedanja
		vector<int> cntLinije(this->linije.size(), 0);

		tekuci = this->mrezaGraf->getLinije(mymap.at(ruta[i]->getSifra()), mymap.at(ruta[i+1]->getSifra()));
		for (int j = 0; j < tekuci.size(); j++) {
			if (tekuci[j] != NULL)
				cntLinije[j]++;
		}
		int cnt = 0;

		//uporedjivanje linija izmedju 2 susedna cvora
		for (int j = 0; j < tekuci.size(); j++) {
			if (tekuci[j] && stari[j])
				break;
			else
				cnt++;
		}

		//presedanje
		//ukoliko su sve linije razlicite izmedju tekuceg i starog
		if (cnt == this->linije.size()) {
			//max element iz vektora cntLinije da bismo znali kojom smo linijom dosli pre presedanja
			presedanjaBrojac[redniBrRute]++;
			int maxValue = cntLinije[0];
			int maxIndex = 0;
			for (int t = 1; t < cntLinije.size(); t++) {
				if (cntLinije[t] > maxValue) {
					maxValue = cntLinije[t];
					maxIndex = t;
				}
			}
			strukturaPresedanja* presedanje = new strukturaPresedanja(ruta[i]->getSifra(), tekuci[maxIndex]);
			vektorPresedanje.push_back(presedanje);
			//for (int j = 0; j < this->linije.size(); j++) cntLinije[j] = 0;
		}

		stari = tekuci;

	}
	this->presedanja.push_back(vektorPresedanje);
}

Linija* GradskaMreza::nadjiLiniju(const string& sifra) {
	for (int i = 0; i < this->linije.size(); i++) {
		if (this->linije[i]->getNaziv() == sifra)
			return this->linije[i];
	}
	return nullptr;
}

Stajaliste* GradskaMreza::nadjiStajaliste(const string& sifra) {
	for (int i = 0; i < this->stajalista.size(); i++) {
		if (to_string(this->stajalista[i]->getSifra()) == sifra)
			return this->stajalista[i];
	}
	return nullptr;
}






//pomocne print funkcije

void GradskaMreza::printLinije() {
	for (int i = 0; i < this->linije.size(); i++) this->linije[i]->printLinija();
}

void GradskaMreza::printStajalista() {
	for (int i = 0; i < this->stajalista.size(); i++) this->stajalista[i]->printStajaliste();
}
