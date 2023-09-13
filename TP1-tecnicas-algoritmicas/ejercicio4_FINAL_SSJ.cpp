#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int inf = 1e9;

int cantProv;
int costo=0;

vector<int> solParcial;

int Kproovs;

vector<int> chori;
vector<int> prov(cantProv, -1);
vector<vector<vector<int>>> dp{};

int distanciaSol;

int distMinimasEntre(int iPrev, int iActual, int provsRestantes){ // funciona para k > 1
    int res = 0;

    int end = iActual, begin = iPrev;

    if(provsRestantes == Kproovs) // para contar los de la izquierda de primer prov
        begin = 1;

    if(provsRestantes == 1) // para contar los de la derecha de ultimo prov
        end = chori.size();

    for (int i = begin; i < end; i++) {
        int dist1 = abs(chori[iPrev] - chori[i]);
        int dist2 = abs(chori[iActual] - chori[i]);

        res += min(dist1, dist2);
    }
    return res;
}


void menorLexi(vector<int> solActual){
    for(int i = 0; i < solActual.size(); i++){
        if(solActual[i] < solParcial[i]){
            solParcial = solActual;
            return;
        }
    }
}


void locacionProvedurias(int iActual, int iPrev, int K, vector<int> solActual) {
    if(K == 0){
        if(solParcial[0] == -1 && dp[Kproovs][solActual[0]][0] == distanciaSol) // como siempre hay solucion da igual si esta era o no una solucion de la distancia
            solParcial = solActual;
        else {
            if(dp[Kproovs][solActual[0]][0] == distanciaSol)
                menorLexi(solActual);
        }
        return;
    }


    else if(iActual == chori.size()-1){
        /* que pasa acá? */
        return;
    }

    int no_pongo = dp[K][iActual][iPrev];
    int si_pongo = dp[K-1][iActual][iActual] + distMinimasEntre(iPrev, iActual, K);

    if(no_pongo < si_pongo)
        locacionProvedurias(iActual+1, iPrev, K, solActual);

    else if(no_pongo > si_pongo) {
        solActual[Kproovs - K] = chori[iActual];
        locacionProvedurias(iActual+1,iActual,K-1,solActual);
    }

    else{ // caso iguales
        locacionProvedurias(iActual+1, iPrev, K, solActual);
        solActual[Kproovs - K] = chori[iActual];
        locacionProvedurias(iActual+1,iActual,K-1,solActual);
    }
}


int costoMinimo(int iActual, int iPrev, int provsRestantes){

    if(provsRestantes == 0)
        return 0;

    else if(provsRestantes > chori.size() - iActual)
        return inf;

    int res;

    if(dp[provsRestantes][iActual][iPrev] != -1){
        return dp[provsRestantes][iActual][iPrev];
    }

    int pongoProv = costoMinimo(iActual+1, iActual, provsRestantes-1);
    pongoProv += distMinimasEntre(iPrev, iActual, provsRestantes);

    int noPongoProv = costoMinimo(iActual+1, iPrev, provsRestantes);

    res = min(pongoProv, noPongoProv);

    return (dp[provsRestantes][iActual][iPrev] = res);
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

        Kproovs = cantProv;

        vector<int> provi(cantProv,-1);
        prov = provi;

        vector<int> choriNuevo(cantPuesto+1,0);
        chori = choriNuevo;
        chori[0] = inf;

        for (int j = 1; j < cantPuesto+1; ++j) {
            int puesto=0;
            cin >> puesto;
            chori[j] = puesto;
        }

        // N x N x K
        vector<vector<vector<int>>> memo(cantProv+1, vector<vector<int>>(chori.size()+1,vector<int>(chori.size()+1, -1)));
        dp = memo;

        distanciaSol = costoMinimo(1,0,cantProv);

        /*   ACA VA LA NUEVA FUNCION     */
        vector<int> nuevaSol(cantProv, -1);
        solParcial=nuevaSol;



        locacionProvedurias(1,0,Kproovs,nuevaSol);

        dp = {};
        //
        results.push_back(solParcial);
        resCostos.push_back(distanciaSol);
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