#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int inf = 1e9;

int cantProv;
int costo=0;

vector<int> solParcial;

vector<int> chori;
vector<int> prov(cantProv, -1);
vector<vector<int>> dp;



int distMinimasEntre(int begin, int end){
    int res=0;
    for(int i=begin;i<=end;i++){
        int dist1 = abs(chori[begin] - chori[i]);
        int dist2 = abs(chori[end] - chori[i]);
        if(dist1 <= dist2){
            res += dist1;
        } else{
            res += dist2;
        }
    }
    return res;
}


int costoMinimo(int ultProv, int provsRestantes, int begin){
    // caso base
    if(provsRestantes == 0)
        return 0;

    else if(begin == chori.size())
        return inf;


    for(int i = begin; i < chori.size(); i++){
        int minActual;

        minActual = costoMinimo(chori[i], provsRestantes-1, i+1);
        if(provsRestantes == 1) {
            int minActual=distMinimasEntre(0, chori.size());
            dp[ultProv][provsRestantes]=minActual;
        }
        else if(dp[ultProv][provsRestantes] != -1){
            dp[ultProv][provsRestantes] = min(inf, minActual + distMinimasEntre(begin,i));
        } else {
            dp[ultProv][provsRestantes] = minActual + distMinimasEntre(begin,i);
        }
    }
    return dp[ultProv][provsRestantes];
}


int main(){
    vector<int> puesto = {5, 10, 15};
    int k = 1;
    chori = puesto;
    vector<vector<int>> s (puesto[puesto.size()-1]+1,vector<int>(k+1,-1));
    dp = s;


    int res = costoMinimo(0,k, 0);
    cout << res << endl;
}