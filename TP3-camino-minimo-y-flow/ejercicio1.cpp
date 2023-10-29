#include "iostream"
#include "vector"
using namespace std;

int N;
int P;
int inf=1e9;
vector<int> dist;
vector<vector<pair<int,int>>> adj;


void relax(int u, int v, int w){
    if (dist[v] > dist[u]+w){
        dist[v]=dist[u]+w;
    }
}

void DAGshortestPath(){ // buscar shortest path en DAG, algoritmo de la biblia (Cormen's Introduction to Algorithms)
    for (int i = 0; i < 4*N; ++i) {
        for (auto v: adj[i]) {
            relax(i,v.first,v.second);
        }
    }
}

void armarListaAdj(){
    for(int j=0; j<N; j++){
        adj[j].push_back(make_pair(j+1,1)); // armo grafo de 4 niveles para que sólo pueda usar 3 pasadizos
        adj[j+N].push_back(make_pair(j+N+1,1)); // basicamente se repiten los N salones 4 veces
        adj[j+2*N].push_back(make_pair(j+2*N+1,1));
        adj[j+3*N].push_back(make_pair(j+3*N+1,1));
    }
    for(int p=1; p<=P; p++){
        int a, b;
        cin >> a >> b;
        a--, b--;    // los pasadizos van dirigidos de arriba hacia abajo
        adj[a].push_back(make_pair(b+N,2));
        adj[a+N].push_back(make_pair(b+2*N,2));
        adj[a+2*N].push_back(make_pair(b+3*N,2));
    }
}



int main() {
    int tests;
    cin>> tests;
    vector<int> output;

    for(int k=1; k<= tests; k++){
        cin >> N >> P;
        adj.assign(4*N,{});
        armarListaAdj();               // en esa función se explica cómo se arma la lista de adyacencia
        dist.assign(4*N,inf);   // inicializo single-source distances
        dist[0]=0;
        DAGshortestPath();      // como ya queda topologicamente ordenado, puedo buscar el camino minimo

        int res = inf;
        int final = N-1;
        for (int i = 0; i < 4; ++i) { // busco el mínimo de los 4 finales obtenidos
            if(dist[final] < res) res = dist[final];
            final += N;
        }

        output.push_back(res+1); // +1 porque arranca en el primer salon con costo 1
    }

    for (int i = 0; i < tests; ++i) {
        cout << output[i] << endl;
    }
    return 0;
}
