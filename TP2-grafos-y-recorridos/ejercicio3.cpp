#include "iostream"
#include "vector"
#include "tuple"
#include "algorithm"
using namespace std;

//             u     v    di     ri
typedef tuple<int, int, float, float> arista;

// nodo  vecinos con di, ri
vector<arista> Graph;
int n;
int m;

class DSU {

    public:
        DSU(){
            padre = vector<int>(n);
            for(int v = 0; v < n; v++)
                padre[v] = v;
            tamano = vector<int>(n,1);
        }

        int find(int v){
            while(padre[v] != v) v = padre[v];
            return v;
        }

        void unite(int u, int v){
            u = find(u); v = find(v);
            if(tamano[u] < tamano[v]) swap(u,v);
            padre[v] = u;
            tamano[u] += tamano[v];
        }

    private:
        vector<int> padre;
        vector<int> tamano;
};

tuple<int,int,int> kruskal(float c){
    long long res = 0;
    vector<tuple<int,int,int,int,int>> E (m,{0,0,0,0,0});
    for(int i = 0; i < E.size(); i++){
        float parcial = get<2>(Graph[i]) - c * get<3>(Graph[i]);
        E[i] = {parcial,get<0>(Graph[i]),get<1>(Graph[i]),get<2>(Graph[i]),get<3>(Graph[i])};
    }
    sort(E.begin(),E.end());
    DSU dsu;

    int aristas = 0;
    int D = 0, R = 0;
    for(int i = int(E.size())-1; i >= 0 ; i--){
        //u y v estan en distinta cc?
        if(dsu.find(get<1>(E[i])) != dsu.find(get<2>(E[i]))){
            D += get<3>(E[i]);
            R += get<4>(E[i]);
            dsu.unite(get<1>(E[i]),get<2>(E[i]));
            res += get<0>(E[i]);
            aristas++;
        }

        if(aristas == n-1) break;
    }
    if(aristas == n-1) return {res,D,R};
    else cout<<"IMPOSSIBLE\n";
}

tuple<int,int> conexiones(){
    float c = 0;
    for(auto & i : Graph){ // inicio con el C mas grande
        c += get<3>(i);
    }

    float mid = c/2; // para la busqueda binaria
    tuple<int,int,int> res;

    while(mid != c){
        res = kruskal(mid);
        if(get<0>(res) >= 0){
            mid = (c+mid)/2;
        }
        else{
            c = mid;
        }
    }

    return {get<1>(res), get<2>(res)};
}