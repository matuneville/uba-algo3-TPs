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


void locacionProvedurias(int iActual, int iPrev, int K, vector<int> solActual) {

    while(K>0){
        int no_pongo = dp[K][iActual+1][iPrev];
        int si_pongo = dp[K-1][iActual+1][iActual] + distMinimasEntre(iPrev, iActual, K);

        if(no_pongo == -1){
            no_pongo = inf;
        }
        if(si_pongo == -1){
            si_pongo = inf;
        }
        if(no_pongo >= si_pongo){
            solActual[Kproovs - K] = chori[iActual];
            iPrev = iActual;
            iActual++;
            K--;
        }
        else{
            iActual++;
        }
    }
    solParcial = solActual;
}

bool esConsecutivo(vector<int> chori){
    bool res = true;
    for(int i=1;i<chori.size()-1;i++){
        if(chori[i]!=chori[i+1]-1){
            res=false;
            break;
        }
    }
    return res;
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

        vector<int> nuevaSol(cantProv, -1);
        solParcial=nuevaSol;

        if(esConsecutivo(chori) && cantProv==1){
            distanciaSol= distMinimasEntre(chori.size()/2,chori.size()/2,1);
            solParcial={chori[chori.size()/2]};
        }
        else{
            // N x N x K
            vector<vector<vector<int>>> memo(cantProv+1, vector<vector<int>>(chori.size()+1,vector<int>(chori.size()+1, -1)));
            dp = memo;

            distanciaSol = costoMinimo(1,0,cantProv);

            /*   ACA VA LA NUEVA FUNCION     */

            locacionProvedurias(1,0,Kproovs,nuevaSol);
        }

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