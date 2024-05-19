#include <iostream>
#include "labirint.h"
#include <string>

/*
10
10
4,7
2,9
6
2,10
*/

using namespace std;


int main() {
    int broj_redova = 0;
    cin>>broj_redova;
    int broj_kolona = 0;
    cin>>broj_kolona;
    Labirint l(broj_redova,broj_kolona);

    string rupa = "";

    int trenutni_broj = 3;
    for(int i = 0; i < (broj_redova-2)/2; i++){
        string broj = "";
        vector<int> vektor_rupa;
        cin>>rupa;
        for (char karakter : rupa) {
            if (karakter != ',') {
                broj+= karakter;
            }
            else{
                vektor_rupa.push_back(stoi(broj)-1);
                broj = "";
            }
        }
        vektor_rupa.push_back(stoi(broj)-1);
        l.Unesi(vektor_rupa, trenutni_broj);
        trenutni_broj += 4;
    }
    cout<<l.udaljenost('A', 9, 'J', 8)<<" je najmanja udaljenost!"<<endl;
}
