#include "labirint.h"
#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <iomanip>
#include <utility>

Labirint::Labirint(int br, int bk){
    broj_redova = br;
    broj_kolona = bk;
    vector<int> pomocna1(bk, -1);
    vector<int> pomocna0(bk, 0);
    for(int i = 0; i < br; i++){
        if((i == 0 || i%2 == 0) && (i != br-1)){
            labirint.push_back(pomocna1);
            labirint.push_back(pomocna0);
            labirint.push_back(pomocna0);
            broj_redova+=2;
        }
        else{
            labirint.push_back(pomocna1);
        }
    }
}

void Labirint::Unesi(vector<int> red, int redni_broj){
    for(int i = 0; i<red.size(); i++){
        labirint[redni_broj][red[i]] = 0;
        labirint[redni_broj+1][red[i]] = 0;
    }
}
int Labirint::udaljenost(char pocetni_red_char, int pocetna_kolona, char krajnji_red_char, int krajnja_kolona){
    int pocetni_red = int(pocetni_red_char) - int('A');
    int krajnji_red = int(krajnji_red_char) - int('A');
    pocetna_kolona -= 1;
    krajnja_kolona -= 1;
    pocetni_red += 2*ceil(pocetni_red/2.0);
    krajnji_red += 2*ceil(krajnji_red/2.0);
    vector<int> udaljenosti_red(labirint[0].size(), -1);
    vector<vector<int>> DP(labirint.size(), udaljenosti_red);
    vector<pair<int, int>> pomocni;
    pomocni.push_back(make_pair(pocetni_red, pocetna_kolona));
    DP[pocetni_red][pocetna_kolona] = 0;
    while(pomocni.size()){
        pair<int, int> trenutni = pomocni[pomocni.size() - 1];
        pomocni.pop_back();
        if(trenutni.first > 0){
            if(labirint[trenutni.first - 1][trenutni.second] != -1){
                if(DP[trenutni.first - 1][trenutni.second] == -1){
                    DP[trenutni.first - 1][trenutni.second] = DP[trenutni.first][trenutni.second] + 1;
                    pomocni.push_back(make_pair(trenutni.first - 1, trenutni.second));
                }
                else{
                    if(DP[trenutni.first][trenutni.second] + 1 < DP[trenutni.first - 1][trenutni.second]){
                        DP[trenutni.first - 1][trenutni.second] = DP[trenutni.first][trenutni.second] + 1;
                        pomocni.push_back(make_pair(trenutni.first - 1, trenutni.second));
                    }
                }
            }
        }
        if(trenutni.second > 0){
            if(labirint[trenutni.first][trenutni.second - 1] != -1){
                if(DP[trenutni.first][trenutni.second - 1] == -1){
                    DP[trenutni.first][trenutni.second - 1] = DP[trenutni.first][trenutni.second] + 1;
                    pomocni.push_back(make_pair(trenutni.first, trenutni.second - 1));
                }
                else{
                    if(DP[trenutni.first][trenutni.second] + 1 < DP[trenutni.first][trenutni.second - 1]){
                        DP[trenutni.first][trenutni.second - 1] = DP[trenutni.first][trenutni.second] + 1;
                        pomocni.push_back(make_pair(trenutni.first, trenutni.second - 1));
                    }
                }
            }
        }
        if(trenutni.first < labirint.size()-1){
            if(labirint[trenutni.first + 1][trenutni.second] != -1){
                if(DP[trenutni.first + 1][trenutni.second] == -1){
                    DP[trenutni.first + 1][trenutni.second] = DP[trenutni.first][trenutni.second] + 1;
                    pomocni.push_back(make_pair(trenutni.first + 1, trenutni.second));
                }
                else{
                    if(DP[trenutni.first][trenutni.second] + 1 < DP[trenutni.first + 1][trenutni.second]){
                        DP[trenutni.first + 1][trenutni.second] = DP[trenutni.first][trenutni.second] + 1;
                        pomocni.push_back(make_pair(trenutni.first + 1, trenutni.second));
                    }
                }
            }
        }

        if(trenutni.second < labirint[0].size()-1){
            if(labirint[trenutni.first][trenutni.second + 1] != -1){
                if(DP[trenutni.first][trenutni.second + 1] == -1){
                    DP[trenutni.first][trenutni.second + 1] = DP[trenutni.first][trenutni.second] + 1;
                    pomocni.push_back(make_pair(trenutni.first, trenutni.second + 1));
                }
                else{
                    if(DP[trenutni.first][trenutni.second] + 1 < DP[trenutni.first][trenutni.second + 1]){
                        DP[trenutni.first][trenutni.second + 1] = DP[trenutni.first][trenutni.second] + 1;
                        pomocni.push_back(make_pair(trenutni.first, trenutni.second + 1));
                    }
                }
            }
        }
    }

    //Crtanje Puta
    vector<vector<int>> put(labirint);
    pair<int, int> trenutni;
    pair<int, int> kraj;
    if((krajnji_red > 0) && (labirint[krajnji_red - 1][krajnja_kolona] != -1) &&
       (DP[krajnji_red - 1][krajnja_kolona] > 0)){
        trenutni = make_pair(krajnji_red - 1, krajnja_kolona);
    }
    else if((krajnja_kolona != 0) && (labirint[krajnji_red][krajnja_kolona-1] != -1)){
        trenutni = make_pair(krajnji_red, krajnja_kolona - 1);
    }
    else if((krajnja_kolona < broj_kolona) && (labirint[krajnji_red][krajnja_kolona + 1] != -1) &&
            (DP[krajnji_red][krajnja_kolona + 1] > 0)){
        trenutni = make_pair(krajnji_red, krajnja_kolona + 1);
        if((krajnja_kolona != 0) && (labirint[krajnji_red][krajnja_kolona-1] != -1) &&
           (DP[krajnji_red][krajnja_kolona - 1] < DP[trenutni.first][trenutni.second])){
            trenutni = make_pair(krajnji_red, krajnja_kolona - 1);
        }
    }
    else{
        trenutni = make_pair(krajnji_red + 1, krajnja_kolona);
    }
    if(DP[trenutni.first][trenutni.second] == -1){
        cout<<"Nije pronadjen put!"<<endl;
        return -1;
    }
    else{
        kraj = trenutni;
        put[trenutni.first][trenutni.second] = DP[trenutni.first][trenutni.second];
    }
    while(true){
        if(DP[trenutni.first][trenutni.second] == 1){
            break;
        }
        if(DP[trenutni.first - 1][trenutni.second] != -1){
            if(trenutni.first > 0){
                if(DP[trenutni.first - 1][trenutni.second] < DP[trenutni.first][trenutni.second]){
                    put[trenutni.first - 1][trenutni.second] = DP[trenutni.first - 1][trenutni.second];
                    trenutni.first = trenutni.first - 1;
                    continue;
                }
            }
        }
        if(trenutni.second > 0){
            if(DP[trenutni.first][trenutni.second - 1] != -1){
                if(DP[trenutni.first][trenutni.second - 1] < DP[trenutni.first][trenutni.second]){
                    put[trenutni.first][trenutni.second - 1] = DP[trenutni.first][trenutni.second - 1];
                    trenutni.second = trenutni.second - 1;
                    continue;
                }
            }
        }
        if(trenutni.first < labirint.size() - 1){
            if(DP[trenutni.first + 1][trenutni.second] != -1){
                if(DP[trenutni.first + 1][trenutni.second] < DP[trenutni.first][trenutni.second]){
                    put[trenutni.first + 1][trenutni.second] = DP[trenutni.first + 1][trenutni.second];
                    trenutni.first = trenutni.first + 1;
                    continue;
                }
            }
        }
        if(trenutni.second < labirint[0].size()){
            if(DP[trenutni.first][trenutni.second - 1] != -1){
                if(DP[trenutni.first][trenutni.second + 1] < DP[trenutni.first][trenutni.second]){
                    put[trenutni.first][trenutni.second + 1] = DP[trenutni.first][trenutni.second + 1];
                    trenutni.second = trenutni.second + 1;
                    continue;
                }
            }
        }
    }
    int duzina = to_string(int(put.size()/4) * put[0].size()).length();
    for(int i = 0; i < put.size(); i++){
        for(int j = 0; j < put[0].size(); j++){
            if(put[i][j] == -1){
                cout<<setw(duzina)<<to_string(j+1)<<" ";
            }
            else if(put[i][j] == 0){
                cout<<setw(duzina)<<""<<" ";
            }
            else{
                cout<<setw(duzina)<<to_string(put[i][j])<<" ";
            }
        }
        cout<<endl;
    }

    return DP[kraj.first][kraj.second];
}
