#include <iostream>
#include "vector"

using namespace std;

int precio = 0;
vector<int> valores = {};

vector<char> solActual = {}; // cuidado en main !! cuando inicie un nuevo afip, hay que reasignar solActual VACIO !!!

void comparoSignos(vector<char> s1){
    if(solActual.empty())
        solActual = s1;
    else{
        for (int i = 0; i < s1.size(); i++) {
            if (s1[i] != solActual[i] && (s1[i] != '?' or solActual[i] != '?')) {
                solActual[i] = '?';
            }
        }
    }
}

bool IMPOSIBOL(int sumaActual, int sumaRestante){
    bool res=false;
    if(sumaRestante>0){
        if(sumaActual-sumaRestante > precio)
            res=true;
    }
    else{
        if (sumaActual+sumaRestante < precio)
            res=true;
    }
    return res;
}

void AFIP(int i, vector<char> resActual, int sumaActual, int sumaRestante){
    if(i == valores.size()){
        if(sumaActual == precio){
            comparoSignos(resActual);
        }
    }

    else if(IMPOSIBOL(sumaActual, sumaRestante)) return;
    else if (sumaActual + sumaRestante == precio){
        for(int j = i; j < valores.size(); j++){
            resActual[j] = '+';
        }
        AFIP(valores.size(), resActual, precio, 0);
    }
    else if(sumaActual - sumaRestante == precio){
        for(int j = i; j < valores.size(); j++){
            resActual[j] = '-';
        }
        AFIP(valores.size(), resActual, precio, 0);
    }
    else{
        resActual[i] = '+';
        AFIP(i+1, resActual, sumaActual + valores[i], sumaRestante - valores[i]);
        resActual[i] = '-';
        AFIP(i+1, resActual, sumaActual - valores[i], sumaRestante - valores[i]);
    }
}

int main(){
    int tests;
    cin >> tests;
    vector<vector<char>> results;
    for (int i = 0; i < tests; i++){
        int cantValores, precioActual;
        cin >> cantValores >> precioActual;
        vector<int> nuevoValores(cantValores, 0);
        valores = nuevoValores;

        precio = precioActual;
        for(int j = 0; j < cantValores; j++){
            int valor=0;
            cin >> valor;
            valores[j] = valor;
        }
        int sumaTotal = 0;
        for(int n: valores) sumaTotal += n;

        vector<char> resActual(valores.size(),'A');

        AFIP(0,resActual,0,sumaTotal);

        results.push_back(solActual);
        solActual = {};
    }
    for(int i = 0; i < tests;i++){
        for (int j = 0; j < results[i].size(); j++) {
            cout<< results[i][j];
        }
        if(i != tests-1) cout << endl;
    }
}
