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
vector<vector<int>> dp;


int distMinimasEntre(int iPrev, int iActual, int provsRestantes){ // funciona para k > 1
    int res = 0;

    int end = iActual, begin = iPrev;

    if(provsRestantes == Kproovs)
        begin = 1;

    if(provsRestantes == 1)
        end = chori.size();

    for (int i = begin; i < end; i++) {
        int dist1 = abs(chori[iPrev] - chori[i]);
        int dist2 = abs(chori[iActual] - chori[i]);

        res += min(dist1, dist2);
    }

    return res;
}


int costoMinimo(int iActual, int iPrev, int provsRestantes){

    if(provsRestantes == 0)
        return 0;

    else if(iActual == chori.size())
        return inf;

    int pongoProv = costoMinimo(iActual+1, iActual, provsRestantes-1);
    pongoProv += distMinimasEntre(iPrev, iActual, provsRestantes);

    int noPongoProv = costoMinimo(iActual+1, iPrev, provsRestantes);

    int res = min(pongoProv, noPongoProv);

    return res;
}

int main(){
    vector<int> puesto = {inf};
    int k = 6;
    Kproovs = k;

    chori = puesto;
    vector<vector<int>> s (puesto[puesto.size()-1]+1,vector<int>(k+1,-1));
    //dp = s;

    int res = costoMinimo(1, 0, k);
    cout << res << endl;
}
