#include <iostream>
#include <vector>
#include <stack>
#include <iomanip>
#include <time.h>
#define WYSOKOSC_PLANSZY 15
#define STALA_PLANSZOWA p.ilosc_kolumn * 4 + (p.ilosc_kolumn - 1) * 2
#define ILOSC_MAX_BLOCZKOW   p.ilosc_kolumn * p.ilosc_bloczkow*  p.ilosc_kolumn * p.ilosc_bloczkow
using namespace std;
class bloczek;
class plansza;
void wczytaj(plansza& p, int& r, int& n);
class plansza {
public:
	int ilosc_kolumn;
	int ilosc_bloczkow;
	typedef stack<bloczek>kolumna;
	vector<kolumna> pole;
	kolumna* ta;
	friend void wczytaj(plansza& p, int& r, int& n);
	void rysuj(plansza p, bloczek*& tab);
	void tworzenie(plansza& p, bloczek*& tab);
	void strzal(plansza& p, bloczek*& tab);
	void wzrost(plansza& p, bloczek*& tab, int& iterator, int r, int n, int& bloczki, int rnd);
	bool przegrana(plansza& p);
	bool wygrana(plansza& p);
};
class bloczek {
public:
	string cialo;
	int numer;
	bloczek() {
		cialo = "####";
		numer = 0;
	}
	void losuj(plansza& p, bloczek*& tab);
	~bloczek() {}
};
void wczytaj(plansza& p, int& r, int& n) {
	int spr = 0;
	cout << "Podaj ilosc kolumn:" << endl;
	cin >> p.ilosc_kolumn;
	cout << "Podaj ilosc bloczkow w kolumnie wieksza niz 0 i mniejsza niz " << WYSOKOSC_PLANSZY - 6 << ":" << endl;
	while (spr != 1) {
		cin >> p.ilosc_bloczkow;
		if (p.ilosc_bloczkow > 0 && p.ilosc_bloczkow < (WYSOKOSC_PLANSZY - 6))
			spr = 1;
		else cout << "Zla wartosc, podaj wartosc ponownie:" << endl;
	}
	cout << "Co r+rnd ruchow do wszystkich kolumn dodawany jest jeden bloczek zmniejszajac przestrzen dla gracza. Parametr rnd jest wartoscia losowa z przedzialu[0, n)" << endl;
	cout << "Wybierz parametr r:" << endl;
	cin >> r;
	cout << "Wybierz parametr n:" << endl;
	cin >> n;
}
void plansza::rysuj(plansza p, bloczek*& tab) {
	for (int i = 0; i < STALA_PLANSZOWA; i++)
		cout << "-";
	cout << endl;
	typedef stack<bloczek>kopia;
	int roz2;
	kopia* kopie = new kopia[p.ilosc_kolumn];
	kopia* kopie2 = new kopia[p.ilosc_kolumn];
	for (int i = 0; i < ilosc_kolumn; i++) {
		int roz = p.ta[i].size();
		for (int j = 0; j < roz; j++) {
			kopie[i].push(p.ta[i].top());
			kopie2[i].push(p.ta[i].top());
			p.ta[i].pop();
		}
	}
	for (int i = 0; i < p.ilosc_bloczkow; i++) {
		for (int j = 0; j < p.ilosc_kolumn; j++) {
			roz2 = kopie2[j].size();
			if (i < roz2) {
				cout << kopie[j].top().cialo << "  ";
				p.ta[j].push(kopie[j].top());
				kopie[j].pop();
			}
			else cout << "      ";
		}
		cout<<endl;
	}
	int max = 0;
	for (int i = 0; i < p.ilosc_kolumn; i++) {
		if (ta[i].size() > max) {
			max = ta[i].size();
		}
	}
	for (int i = 0; i < WYSOKOSC_PLANSZY-max-1; i++)
		cout << endl;
	cout << setw((STALA_PLANSZOWA) / 2 + 2) << "=[]=" << endl;
	for (int i = 0; i < STALA_PLANSZOWA; i++)
		cout << "-";
	cout << endl;
	delete[]kopie;
	delete[]kopie2;
}
void plansza::tworzenie(plansza& p, bloczek*& tab) {
	int it = 0;
	ta = new kolumna[p.ilosc_kolumn];
	for (int i = 0; i < p.ilosc_kolumn; i++) {
		p.pole.push_back(ta[i]);
		for (int j = 0; j < p.ilosc_bloczkow; j++) {
			ta[i].push(tab[it]);
			it++;
		}
	}
}
void bloczek::losuj(plansza& p, bloczek*& tab) {
	srand(time(NULL));
	for (int i = 0; i < ILOSC_MAX_BLOCZKOW; i++) {
		tab[i].numer = i;
		if (rand() % 12 == 0) {
			tab[i].cialo = "#%%#";
		}
		else if (rand() % 12 == 1) {
			tab[i].cialo = "#oo#";
		}
	}
}
void plansza::strzal(plansza& p, bloczek*& tab) {
	int s;
	cout << "Wybierz kolumne do strzalu: " << endl;
	cin >> s;
	if (s <= p.ilosc_kolumn) {
		if (p.ta[s - 1].top().cialo == "####") {
			p.ta[s - 1].pop();
		}
		else if (p.ta[s - 1].top().cialo == "#%%#") {
			if (p.ta[s - 1].size() == 1) {
				p.ta[s - 1].pop();
			}
			if (p.ta[s - 1].size() > 1) {
				p.ta[s - 1].pop();
				p.ta[s - 1].pop();
			}
		}
		else if (p.ta[s - 1].top().cialo == "#oo#") {
			if (p.ta[s - 1].size() == 2) {
				p.ta[s - 1].pop();
				p.ta[s - 1].pop();
			}
			if (p.ta[s - 1].size() == 1) {
				p.ta[s - 1].pop();
			}
			else if (p.ta[s - 1].size() > 2) {
				p.ta[s - 1].pop();
				p.ta[s - 1].pop();
				p.ta[s - 1].pop();
			}
		}	
	}
	else cout << "Podano zle dane" << endl;
}
void plansza::wzrost(plansza& p, bloczek*& tab, int& iterator, int r, int n, int& bloczki, int rnd) {
	if (iterator == r + rnd) {
		for (int i = 0; i < p.ilosc_kolumn; i++) {
			ta[i].push(tab[bloczki]);
			bloczki++;
		}
		p.ilosc_bloczkow++;
		iterator = 0;
	}
}
bool plansza::przegrana(plansza& p) {
	for (int i = 0; i < p.ilosc_kolumn; i++) {
		if (p.ta[i].size() == WYSOKOSC_PLANSZY - 1) {
			return 0;
		}
	}
}
bool plansza::wygrana(plansza& p) {
	for (int i = 0; i < p.ilosc_kolumn; i++) {
		if (p.ta[i].size() == 0) {
			return 0;
		}
	}
}
int main() {
	int r;
	int n;
	int iterator = 0;
	plansza p;
	wczytaj(p, r, n);
	int bloczki = p.ilosc_kolumn * p.ilosc_bloczkow;
	srand(time(NULL));
	int rnd;
	rnd = rand() % n;
	cout << "Plansza rosnie co " << r + rnd << "ruchow" << endl;
	bloczek* tab = new bloczek[ILOSC_MAX_BLOCZKOW];
	tab->losuj(p, tab);
	p.tworzenie(p, tab);
	p.rysuj(p, tab);
	while (p.przegrana(p) && p.wygrana(p)) {
		p.strzal(p, tab);
		iterator++;
		p.wzrost(p, tab, iterator, r, n, bloczki, rnd);
		p.rysuj(p, tab);
	}
	if (p.wygrana(p) == 0) {
		cout << "Wygrales!!" << endl;
	}
	else if (p.przegrana(p) == 0) {
		cout << "Przegrales!!" << endl;
	}
	cout << "Koniec gry";
	delete[]tab;
}
