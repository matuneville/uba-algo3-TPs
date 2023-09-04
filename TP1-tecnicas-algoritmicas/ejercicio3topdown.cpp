#include <iostream>
#include "vector"

using namespace std;

int precio = 0;
int maxSum = 0;
vector<int> valores = {};
vector<char> solActual = {};
vector<vector<vector<char>>> dp = {};
vector<char> solVacia = {};

vector<char> comparoSignos(vector<char> s1, vector<char> s2){
    int i=0;
    while(i!=s1.size()){
        if (s1[i]=='A') break;
        if (s1[i] != s2[i] && (s1[i] != '?' or s2[i] != '?')){
            s1[i]='?';
        }
        i++;
    }
    return s1;
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
            if(solActual.empty()) {
                solActual = resActual;
                dp[i][(sumaActual + maxSum) / 100] = resActual;
                return;
            }
            else {
                vector<char> sol = comparoSignos(resActual, solActual);
                dp[i][(sumaActual + maxSum) / 100] = sol;
                solActual = sol;
            }
            return;
        }
    }

    else if(IMPOSIBOL(sumaActual, sumaRestante)) return;

    else if (dp[i][(sumaActual+maxSum)/100] != solVacia){
        vector<char> comparado = comparoSignos(dp[i][(sumaActual+maxSum)/100], resActual);
        dp[i][(sumaActual+maxSum)/100] = comparado;
        return;
    }

    else{
        resActual[i] = '+';
        AFIP(i+1, resActual, sumaActual + valores[i], sumaRestante - valores[i]);
        dp[i][((sumaActual+valores[i])+maxSum)/100] = resActual;

        //dp[i][((sumaActual+valores[i])+maxSum)/100] = resActual

        resActual[i] = '-';
        AFIP(i+1, resActual, sumaActual - valores[i], sumaRestante - valores[i]);
        dp[i][((sumaActual-valores[i])+maxSum)/100] = resActual;
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

        solVacia = resActual;


        for (int n : valores){
            maxSum += n;
        }

        vector<vector<vector<char>>> dp_nuevo (valores.size()+1, vector<vector<char>>(((2*maxSum) / 100)+1, solVacia));
        dp = dp_nuevo; // dado una suma actual, se indexa en [(sumaActual + maxSum)/100]

        AFIP(0,resActual,0,sumaTotal);
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
