#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

const int inf = 1e9;
vector<int> chori;
int Kproovs=0;

int sumaRestante(int i){
    int res=0;
    for(int j=i+1;j<chori.size();j++){
        int dist = abs(chori[i] - chori[j]);

        res += dist;
    }

    return res;
}

int distanciasEntre(int i, int j, int provRestantes) {
    int res = 0;

    int begin = i, end = j;

    if(provRestantes==Kproovs-1){
        begin=0;
    }

    if(provRestantes == 1){
        end=chori.size()-1;
    }


    for (int h = begin; h <= end; h++) {
        int dist1 = abs(chori[i] - chori[h]);
        int dist2 = abs(chori[j] - chori[h]);

        res += min(dist1, dist2);
    }

    return res;
}

int costoMinimo(int iActual, int provRestantes){
    if(provRestantes==0){
        return sumaRestante(iActual);
    }

    if(iActual==chori.size()){
        return 0;
    }
    int res=inf;
    int resActual=0;

    if(provRestantes==1){
        for(int j=iActual+1;j<chori.size();j++) {
            int resActual = distanciasEntre(iActual, j, provRestantes);
            if(resActual<res){
                res=resActual;
            }
        }
    }
    else {
        for (int j = iActual + 1; j < chori.size(); j++) {
            int dist1 = distanciasEntre(iActual, j, provRestantes);
            int costoActual = costoMinimo(j, provRestantes - 1);

            resActual = dist1+costoActual;
            if(resActual<res){
                res=resActual;
            }
        }
    }
    return res;
}

int main() {
    chori={1, 2, 3, 700, 701, 702, 750, 890, 891, 19000}; // 1 2 3 700 701 702 750 890 891 19000
    int k=6;
    Kproovs=k;
    int res = costoMinimo(0,k);
    cout << res << endl;
    return 0;
}