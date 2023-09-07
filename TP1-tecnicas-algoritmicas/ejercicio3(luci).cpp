#include <iostream>
#include "vector"
#include <algorithm>
using namespace std;

vector<pair<int,int>> valoresG={};
int precioPoda=0;
int sumaRestante=0;

bool IMPOSIBOL(int sumaActual, int sumaRestante){
    bool res=false;
    if(sumaRestante>0){
        if(sumaActual-sumaRestante > precioPoda)
            res=true;
    }
    else{
        if (sumaActual+sumaRestante < precioPoda)
            res=true;
    }
    return res;
}

bool   puedoMas(vector<pair<int,int>> valores, int precio, int iBorrar,int indice, int sumaRestante){
    if(precio == 0 && indice == valores.size()) {
        return true;
    }
    else if(precio != 0 && indice == valores.size()) {
        return false;
    }
    else if(IMPOSIBOL(precio, sumaRestante)) return false;
    if(indice != iBorrar){
        return puedoMas(valores, precio + valores[indice].first,iBorrar,indice+1,sumaRestante+valores[indice].first) or puedoMas(valores, precio - valores[indice].first,iBorrar,indice+1,sumaRestante-valores[indice].first);
    }
    else{
        return puedoMas(valores, precio ,iBorrar,indice+1,sumaRestante+valores[indice].first) or puedoMas(valores, precio ,iBorrar,indice+1,sumaRestante-valores[indice].first);
    }
}



vector<char> AFIP(int precio){
    vector<pair<char,int>> res (valoresG.size(), make_pair('A',0));
    for(int i = 0; i < valoresG.size(); i++){
        bool mas = puedoMas(valoresG, precio - valoresG[i].first, i, 0, sumaRestante);
        bool menos = puedoMas(valoresG, precio + valoresG[i].first, i, 0,sumaRestante);
        if(mas && menos)
            res[i] = make_pair('?',valoresG[i].second);
        else if(mas)
            res[i] = make_pair('+',valoresG[i].second);
        else
            res[i] = make_pair('-',valoresG[i].second);
    }
    sort(res.begin(), res.end(), [](const std::pair<int, int>& a, const std::pair<int, int>& b) {
        return a.second < b.second;
    });
    vector<char> result (valoresG.size(), 'A');
    for(int i=0;i<res.size();i++){
        result[i]=res[i].first;
    }
    return result;
}

int main(){
    int tests;
    cin >> tests;
    vector<vector<char>> results;
    int precio=0;
    for (int i = 0; i < tests; i++){
        precio=0;
        int cantValores, precioActual;
        cin >> cantValores >> precioActual;
        vector<pair<int,int>> nuevoValores(cantValores, make_pair(0,0));
        valoresG = nuevoValores;

        precio = precioActual;
        for(int j = 0; j < cantValores; j++){
            int valor=0;
            cin >> valor;
            valoresG[j] = make_pair(valor,j);
        }
        int sumaTotal = 0;
        for(pair<int,int> n: valoresG) sumaTotal += n.first;

        vector<char> resActual(valoresG.size(),'A');

        precioPoda=precio;
        sumaRestante=sumaTotal;

        sort(valoresG.begin(), valoresG.end(), [](const std::pair<int, int>& a, const std::pair<int, int>& b) {
            return a.first > b.first;
        });

        results.push_back(AFIP(precio));
        sumaTotal = 0;
    }
    for(int i = 0; i < tests;i++){
        for (int j = 0; j < results[i].size(); j++) {
            cout<< results[i][j];
        }
        if(i != tests-1) cout << endl;
    }
    return 0;
}
