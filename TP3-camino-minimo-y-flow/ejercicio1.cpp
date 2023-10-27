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

void dagShortPaths(){
    for (int i = 0; i < 4*N; ++i) {
        for (auto v: adj[i]) {
            relax(i,v.first,v.second);
        }
    }
}

void armarListaAdj(){
    for(int j=0; j<N; j++){
        adj[j].push_back(make_pair(j+1,1)); // armo grafo de 4 niveles para que sólo pueda usar 3 pasadizos
        adj[j+N].push_back(make_pair(j+N+1,1));
        adj[j+2*N].push_back(make_pair(j+2*N+1,1));
        adj[j+3*N].push_back(make_pair(j+3*N+1,1));
    }
    for(int p=1; p<=P; p++){
        int a, b;
        cin >> a >> b;
        a--, b--;
        adj[a].push_back(make_pair(b+N,2));
        adj[a+N].push_back(make_pair(b+2*N,2));
        adj[a+2*N].push_back(make_pair(b+3*N,2));
    }
}

int buscarMinimo(){
    vector<int> candidatos;
    candidatos.push_back(dist[N-1]);
    candidatos.push_back(dist[2*N-1]);
    candidatos.push_back(dist[3*N-1]);
    candidatos.push_back(dist[4*N-1]);

    int res=candidatos[0];
    for(int i=1; i< candidatos.size(); i++){
        if(candidatos[i]<res){
            res=candidatos[i];
        }
    }
    return res+1;
}



int main() {
    int tests;
    cin>> tests;
    vector<int> output;

    for(int k=1; k<= tests; k++){
        cin >> N >> P;
        adj.assign(4*N,{});
        armarListaAdj();
        dist.assign(4*N,inf);
        dist[0]=0;
        dagShortPaths();

        int res=buscarMinimo();
        output.push_back(res);
    }

    for (int i = 0; i < tests; ++i) {
        cout << output[i] << endl;
    }
    return 0;
}
