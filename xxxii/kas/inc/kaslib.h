// Modified 'kaslib.h' File
// Used to obtain threshold values with 'src/a.cpp' file.

#include <bits/stdc++.h>

#define SEED 69
#define BTLR 10'000'000LL;

using namespace std;

namespace {
// Można zmienić te wartości.
long long N = 1'000'000'000'000'000'000ll;
int bajtalary = BTLR;

// Aby zmienić losowość należy zamienić 1 na dowolną inną liczbę typu int.
mt19937_64 rng(SEED);

long long X;
bool gra_zakonczona = false;
bool czy_zainicjalizowany = false;
int wygrane = 0;

long long wylosuj_liczbe() {
    return uniform_int_distribution<long long>(1, N)(rng);
}

void inicjalizuj_gre() {
    X = wylosuj_liczbe();
}

void inicjalizuj_interakcje() {
    if (czy_zainicjalizowany) return;
    inicjalizuj_gre();
    czy_zainicjalizowany = true;
}

void proba_zakonczenia() {
    if (!bajtalary) {
    	// cout << "Liczba wygranych: " << to_string(wygrane) << endl;
    	// exit(0);
        gra_zakonczona = true;
    }
}

void zjedz_bajtalara() {
    proba_zakonczenia();
    --bajtalary;
}
}

long long DajN() {
    inicjalizuj_interakcje();
    return N;
}

long long Pytaj(long long y) {
    inicjalizuj_interakcje();
    assert(1 <= y && y <= N);
    zjedz_bajtalara();
    proba_zakonczenia();
    return __gcd(X, y);
}

void Szturchnij() {
    inicjalizuj_interakcje();
    zjedz_bajtalara();
    X = wylosuj_liczbe();
    proba_zakonczenia();
}

void Odpowiedz(long long y) {
    inicjalizuj_interakcje();
    assert(1 <= y && y <= N);
    zjedz_bajtalara();
    assert(X == y);
    ++wygrane;
    proba_zakonczenia();
    inicjalizuj_gre();
}

bool GraZakonczona() {
    return gra_zakonczona;
}

long long Wygrane() {
    return wygrane;
}

void OdNowa() {
    rng.seed(SEED);

    bajtalary = BTLR;
    X = 0;
    czy_zainicjalizowany = false;
    gra_zakonczona = false;
    wygrane = 0;
}
