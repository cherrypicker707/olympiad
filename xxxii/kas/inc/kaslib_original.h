// Original 'kaslib.h' File

#include <bits/stdc++.h>

using namespace std;

namespace {
// Można zmienić te wartości.
long long N = 1'000'000'000'000'000'000ll;
int bajtalary = 10'000'000;

// Aby zmienić losowość należy zamienić 1 na dowolną inną liczbę typu int.
mt19937_64 rng(0);

long long X;
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
    	cout << "Liczba wygranych: " << to_string(wygrane) << endl;
    	exit(0);
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
