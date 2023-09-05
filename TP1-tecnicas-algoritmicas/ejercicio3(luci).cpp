#include <iostream>
#include "vector"

using namespace std;

int precio = 0;
int maxSum = 0;
vector<int> valores = {};
vector<char> solActual = {};
vector<vector<vector<char>>> dp = {};


bool IMPOSIBOL(int sumaActual){
    if (sumaActual > maxSum*2 or sumaActual < 0) return true;
    else return false;
}

vector<char> cambiar(vector<char> nuevoRes){
    int valor=valores[nuevoRes.size()];
    for(int j=0;j<nuevoRes.size();j++){
        if(valores[j+1]==valor){
            nuevoRes[j]='?';
            break;
        }
    }
    nuevoRes[nuevoRes.size()-1]='?';
}


void AFIP2(int i, int sumaActual){
    if(i==valores.size()){
        if(sumaActual==maxSum+precio){
            if(!dp[i][sumaActual/100].empty()) {
                vector<char> nuevoRes = dp[i-1][sumaActual/100];
                dp[i][sumaActual/100]=nuevoRes;
                solActual=dp[i][sumaActual/100];
                return;
            }else{
                dp[i][sumaActual/100]=dp[i-1][sumaActual/100];
                solActual=dp[i][sumaActual/100];
                return;
            }
        }
        return;
    }
    else if(!dp[i][sumaActual/100].empty()){
        vector<char> nuevoRes=dp[i][sumaActual/100];
        dp[i][sumaActual/100]=cambiar(nuevoRes);
        return;
    }
    else{
        if(valores[i]==0){
            vector<char> nuevoCero=dp[i-1][sumaActual/100];
            nuevoCero.push_back('?');
            dp[i][sumaActual/100]=nuevoCero;
            AFIP2(i+1,sumaActual);
            return;
        }
        vector<char> nuevoResSuma=dp[i-1][sumaActual/100];
        nuevoResSuma.push_back('+');
        dp[i][(sumaActual+valores[i])/100]=nuevoResSuma;
        AFIP2(i+1,sumaActual+valores[i]);

        vector<char> nuevoResResta=dp[i-1][sumaActual/100];
        nuevoResResta.push_back('-');
        dp[i][(sumaActual-valores[i])/100]=nuevoResResta;
        AFIP2(i+1,sumaActual-valores[i]);
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

        AFIP2(1,maxSum);
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
