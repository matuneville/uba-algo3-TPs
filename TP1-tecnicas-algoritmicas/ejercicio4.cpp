#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

int cantProv;
int costo=0;

vector<int> solParcial;

vector<int> chori;
vector<int> prov(cantProv, -1); // global, finalllllll


int provedMasCercana(int n, vector<int>& proved){
    int distanciaMin=abs(n-proved[0]);

    for(int i=0;i<proved.size();i++){
        int distanciaActual=abs(n-proved[i]);
        if(distanciaActual<distanciaMin){
            distanciaMin=distanciaActual;
        }
    }
    //qe pasa perkin//  esta bien // ta lista
    return distanciaMin;
}

int calcularCosto(vector<int>& proved){
    int res=0;
    for(int n: chori){
        int k = provedMasCercana(n,proved);
        res+=k;
    }
    return res;
}

bool menorLexicParcial(){ // true si solParcial menor que prov
    for(int i = 0; i != solParcial.size(); i++){
        if(solParcial[i] < prov[i]){
            return true;
        }
    }
    return false;
}


void choripanes(int iChori, int iProv){

    if(cantProv - iProv  > chori.size() - iChori) // no tiene solucion
        return;

    else if(iProv == cantProv) {
        // analizar solParcial y sol Actual !
        if(prov[0] != -1){
            if (calcularCosto(solParcial) < calcularCosto(prov)) { // O(n²)
                prov = solParcial;// O(n)
                costo = calcularCosto(prov);
            } else if (calcularCosto(solParcial) == calcularCosto(prov)) {
                if (menorLexicParcial()) {
                    prov = solParcial;
                    costo = calcularCosto(prov);
                }
            }
        } else{
            prov=solParcial;
            costo = calcularCosto(prov);
        }
    }
    else {
        // la pongo
        solParcial[iProv] = chori[iChori];
        choripanes(iChori+1,iProv+1);

        // no la pongo (nunca la pongo)
        solParcial[iProv] = -1;
        choripanes(iChori+1,iProv);
    }
}


int main(){
    int tests;
    cin >> tests;
    vector<vector<int>> results;
    vector<int> resCostos;

    for(int i = 0; i < tests; i++){
        int cantPuesto;
        cin >> cantPuesto;
        cin >> cantProv;
        vector<int> provi(cantProv,-1);
        prov = provi;
        solParcial = provi;
        vector<int> choriNuevo(cantPuesto,0);
        chori = choriNuevo;
        for (int j = 0; j < cantPuesto; ++j) {
            int puesto=0;
            cin >> puesto;
            chori[j]=puesto;
        }

        choripanes(0,0);

        results.push_back(prov);
        resCostos.push_back(costo);
    }

    for(int i = 0; i < tests;i++){
        cout << resCostos[i] << endl;
        for (int j = 0; j < results[i].size(); j++) {
            if(j == results[i].size()-1)
                cout<< results[i][j];
            else
                cout<< results[i][j] << " ";
        }
        if(i != tests-1) cout << endl;
    }

    return 0;
}