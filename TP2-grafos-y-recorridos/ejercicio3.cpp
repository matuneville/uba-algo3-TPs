#include "iostream"
#include "vector"
#include "tuple"
#include "algorithm"
using namespace std;

//             u     v    di     ri
typedef tuple<int, int, long double, long double> arista;

// nodo  vecinos con di, ri
vector<arista> Graph;
int n;
int m;
long double epsilon = 0.00001;

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

tuple<long double,int,int> kruskal(long double c){
    long double res = 0;
    vector<tuple<long double,int,int,int,int>> E (m,{0,0,0,0,0});
    for(int i = 0; i < E.size(); i++){
        long double parcial = get<0>(Graph[i]) - c * get<1>(Graph[i]);
        E[i] = {parcial,-get<0>(Graph[i]),get<1>(Graph[i]),get<2>(Graph[i]),get<3>(Graph[i])};
    }

    sort(E.begin(), E.end());

    DSU dsu;

    int aristas = 0;
    int D = 0, R = 0;
    for(int i = int(E.size())-1; i >= 0 ; i--){
        //u y v estan en distinta cc?
        if(dsu.find(get<3>(E[i])) != dsu.find(get<4>(E[i]))){
            D += -get<1>(E[i]);
            R += get<2>(E[i]);
            dsu.unite(get<3>(E[i]),get<4>(E[i]));
            res += get<0>(E[i]);
            aristas++;
        }
        if(aristas == n-1) break;
    }

    if(aristas == n-1)
        return {res,D,R};

    // caso IMPOSIBLE, chequear que si es -1 hay que printear IMPOSIBLE
    return {-1,-1,-1};
}

tuple<int,int> conexiones(){
    long double c = 0;
    for(auto & i : Graph){ // inicio con el C mas grande
        c += get<1>(i);
    }
    c /= 2;
    tuple<int,int,int> resPeso;
    tuple<int,int> res={-10000,1};
    long double low = 0;
    while(abs(c-low) >= epsilon){ // si la diferencia es muy chica
        float coefRes = static_cast<float>(get<0>(res))/get<1>(res);
        long double mid = (c+low)/2;

        resPeso = kruskal(mid);

        if(get<0>(resPeso) >= 0) {
            low = mid;
            float coefPeso = static_cast<float>(get<1>(resPeso)) / get<2>(resPeso);
            if (coefPeso > coefRes) {
                res = {get<1>(resPeso), get<2>(resPeso)};
            }
        }
        else {
            c = mid;
        }
    }
    return res;
}

int main(){
    int tests;
    cin>> tests;

    vector<tuple<int,int>> output(tests, {-1,-1});

    for (int i = 0; i < tests; ++i) {

        cin >> n >> m;

        Graph.assign(m, arista(-1,-1,-1,-1));

        for (int k = 0; k < m; ++k) {
            int u; int v; int d; int r;
            cin >> u >> v >> d >> r;
            Graph[k]=arista(d,r,u,v);
        }

        tuple<int,int> res = conexiones();
        output[i]=res;

    }

    for (int i = 0; i < tests; ++i) {
        if(get<0>(output[i]) == -1 or get<1>(output[i]) == -1)
            cout << "IMPOSIBLE" << endl;
        else cout << get<0>(output[i]) << " " << get<1>(output[i]) << endl;
    }

    return 0;

}
