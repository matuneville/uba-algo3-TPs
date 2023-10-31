#include "iostream"
#include "vector"
#include "queue"
using namespace std;

#define matriz vector<vector<int>>
#define subtableros vector<vector<pair<int, int>>>

matriz adj;
matriz nuevoAdj;
matriz tablero;
subtableros pares;

int N; // N del tamaño del tablero
int Nodos; // Cantidad de nodos del grafo bipartito
int segundoSubconj;
int INF = 1e9;
vector<vector<int>> capacity;

// esta funcion es para crear el grafo bipartito de subfilas x subcolumnas
void make_pares(){
    // primero armo por filas
    int nodo = 1;
    int i = 0, j = 0;
    bool check_nodo = false; // con este chequeo si aumento o no el numero de nodo a agregar

    while(i < N){
        check_nodo = false;
        while(j < N){
            if(tablero[i][j] == 1 and check_nodo){
                nodo++;
                check_nodo = false;
                continue;
            }
            else if(tablero[i][j] == 0) {
                check_nodo = true;
                pares[i][j].first = nodo;
            }
            j++;
        }
        i++;
        if(check_nodo) nodo++;
        j = 0;
    }

    // a partir de aca se analiza el segundo subconjunto del grafo bipartito para el matching
    segundoSubconj = nodo;

    // ahora armamos por columnas
    i = 0, j = 0;
    while(j < N){
        check_nodo = false;
        while(i < N){
            if(tablero[i][j] == 1 and check_nodo){
                nodo++;
                check_nodo = false;
                continue;
            }
            else if(tablero[i][j] == 0) {
                check_nodo = true;
                // pares[i][j] = {pares[i][j].first, nodo};
                pares[i][j].second = nodo;
            }
            i++;
        }
        j++;
        if(check_nodo) nodo++;
        i = 0;
    }
    Nodos = nodo-1;
}


void armarGrafo(){
    // creamos adyacencias de la fuente
    vector<int> fuente; // el indice 0 es para fuente

    for(int i=1;i<segundoSubconj;i++){
        fuente.push_back(i);
    }
    adj[0]=fuente;


    // por cada vértice de subfilas ponemos las adyacencias
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            pair<int,int> actual = pares[i][j];
            if(actual.first != -1) adj[actual.first].push_back(actual.second);
        }
    }

    // por cada vértice de subcolumnas ponemos aristas a t
    for(int i=segundoSubconj;i<adj.size()-1;i++){
        int t = adj.size()-1;
        vector<int> sumidero = {t};
        adj[i]=sumidero;
    }

    // ahora ya quedo armado, ajd[0] es el vertice fuente y adj[Nodos+2-1] es el vertice sumidero
    // y adj[1], adj[2], ..., adj[Nodos] son los vertices de cada subconjunto del grafo bipartito
}


void armarCapacity(){
    capacity.assign(adj.size(),vector<int>(adj.size(),0));
    for(int i=0;i<adj.size();i++){
        for(auto j: adj[i]){
            capacity[i][j] = 1;
        }
    }
}


// adj = {{1,2},{3,4},{3},{5},{5},{}} (ejemplo test1)
// nuevoAdj = {{1,2},{0,3,4},{0,3},{1,2,5},{1,5},{3,4}}
void grafoSinDirecciones(){
    for(int i=0;i<adj.size();i++){
        for(auto j: adj[i]){
            nuevoAdj[i].push_back(j);
            nuevoAdj[j].push_back(i);
        }
    }
}

// BFS para grafo no dirigido, por eso la funcion grafoSinDirecciones
int bfs(int s, int t, vector<int>& parent) {
    fill(parent.begin(), parent.end(), -1);
    parent[s] = -2;
    queue<pair<int, int>> q;
    q.push({s, INF});

    while (!q.empty()) {
        int cur = q.front().first;
        int flow = q.front().second;
        q.pop();

        for (int next : nuevoAdj[cur]) {
            if (parent[next] == -1 && capacity[cur][next]) {
                parent[next] = cur;
                int new_flow = min(flow, capacity[cur][next]);
                if (next == t)
                    return new_flow;
                q.push({next, new_flow});
            }
        }
    }
    return 0;
}

// algoritmo de Edmond-Karp
int maxflow(int s, int t) {
    int n = adj.size();
    int flow = 0;
    vector<int> parent(n);
    int new_flow;

    while (new_flow = bfs(s,t, parent)) {
        flow += new_flow;
        int cur = t;
        while (cur != s) {
            int prev = parent[cur];
            capacity[prev][cur] -= new_flow;
            capacity[cur][prev] += new_flow;
            cur = prev;
        }
    }

    return flow;
}


int main(){
    int tests;
    cin >> tests;
    vector<int> output;
    for(int i = 1 ; i <= tests; i++){
        cin >> N;
        tablero.assign(N,vector<int>(N,0));
        for(int j = 0; j < N; j++){
            for(int k = 0; k < N; k++){
                int in;
                cin >> in;
                if (in) tablero[j][k] = 1;
            }
        }

        pares.assign(N, vector<pair<int,int>>(N, {-1, -1}));
        make_pares();
        adj.assign(Nodos + 2, vector<int>()); // lo armo con size(grafo bipartito) + source + sink
        armarGrafo();
        armarCapacity();
        nuevoAdj.assign(adj.size(),{}); // grafo sin direcciones para usar en el bfs
        grafoSinDirecciones(); // arma el grafo mencionado arriba
        int res= maxflow(0,adj.size()-1);
        output.push_back(res);
    }
    for (int i = 0; i < tests; ++i) {
        cout << output[i] << endl;
    }

}
