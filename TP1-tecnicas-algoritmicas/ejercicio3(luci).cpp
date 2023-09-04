#include <iostream>
#include "vector"

using namespace std;

int precio = 0;
int maxSum = 0;
vector<int> valores = {};
vector<char> solActual = {};
vector<vector<vector<char>>> dp = {};

vector<char> comparoSignos(vector<char> s1, vector<char> s2){
    vector<char> res=s1;
    for(int i=0;i<res.size();i++)
        if (s1[i] != s2[i] && (s1[i] != '?' or s2[i] != '?')){
            res[i]='?';
        }
    return res;
}

bool IMPOSIBOL(int sumaActual){
    if (sumaActual > maxSum*2 or sumaActual < 0) return true;
    else return false;
}

void AFIP(int i, int sumaActual, vector<char> resActual){ // sumaActual se inicia como sumaMax, i empieza en 1
    if(sumaActual==maxSum+precio && valores.size()-1==resActual.size()){
        if(!dp[i][sumaActual/100].empty()){
            dp[i][sumaActual/100]=comparoSignos(dp[i][sumaActual/100],resActual);
        } else{
            dp[i][sumaActual/100]=resActual;
        }
        solActual=dp[i][sumaActual/100];
        return;
    }

    else if(resActual.size()==valores.size()-1) return;
    else if(IMPOSIBOL(sumaActual)) return;

    else if(!dp[i][(sumaActual)/100].empty()){
        comparoSignos(dp[i][(sumaActual)/100],resActual);
        return;
    }

    else{
        vector<char> nuevoResSuma=dp[i-1][sumaActual/100];
        nuevoResSuma.push_back('+');
        dp[i][(sumaActual+valores[i])/100]=nuevoResSuma;
        AFIP(i+1,sumaActual+valores[i],nuevoResSuma);

        vector<char> nuevoResResta=dp[i-1][sumaActual/100];
        nuevoResResta.push_back('-');
        dp[i][(sumaActual-valores[i])/100]=nuevoResResta;
        AFIP(i+1,sumaActual-valores[i],nuevoResResta);
    }
    return;
}

int main(){
    int tests;
    cin >> tests;
    vector<vector<char>> results;
    for (int i = 0; i < tests; i++){

        int cantValores, precioActual;
        cin >> cantValores >> precioActual;
        vector<int> nuevoValores(cantValores+1, 0);
        valores = nuevoValores;

        precio = precioActual;
        for(int j = 1; j <= cantValores; j++){
            int valor=0;
            cin >> valor;
            valores[j] = valor;
        }
        int sumaTotal = 0;
        for(int n: valores) sumaTotal += n;

        vector<char> resActual={};

        for (int n : valores){
            maxSum += n;
        }

        vector<vector<vector<char>>> dp_nuevo (valores.size()+1, vector<vector<char>>(((2*maxSum) / 100)+1, vector<char>()));

        dp = dp_nuevo; // dado una suma actual, se indexa en [(sumaActual + maxSum)/100]

        AFIP(1,maxSum,resActual);
        maxSum = 0;
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
