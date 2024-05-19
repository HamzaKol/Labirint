#ifndef LABIRINT_H
#define LABIRINT_H

#include <vector>

using namespace std;

class Labirint {
    int broj_redova;
    int broj_kolona;
    vector<vector<int>> labirint;

public:
    Labirint(int br, int bk);
    void Unesi(vector<int> red, int redni_broj);
    void Ispisi();
    int udaljenost(char pocetni_red_char, int pocetna_kolona, char krajnji_red_char, int krajnja_kolona);
};

#endif // LABIRINT_H
