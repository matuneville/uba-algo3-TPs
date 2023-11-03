#include "iostream"
#include "vector"
#include "queue"

using namespace std;

int n;
vector<vector<int>> capacity;
vector<vector<int>> adj;
vector<vector<int>> capacityP;
vector<vector<int>> nuevoAdj;
int INF = 1e9;

int maxArista;

int x;

int bfs(int s, int t, vector<int>& parent) {
    n = adj.size()-1;
    fill(parent.begin(), parent.end(), -1);
    parent[s] = -2;
    queue<pair<int, int>> q;
    q.push({s, INF});

    while (!q.empty()) {
        int cur = q.front().first;
        int flow = q.front().second;
        q.pop();

        for (int next : nuevoAdj[cur]) {
            if (parent[next] == -1 && capacityP[cur][next]) {
                parent[next] = cur;
                int new_flow = min(flow, capacityP[cur][next]);
                if (next == t)
                    return new_flow;
                q.push({next, new_flow});
            }
        }
    }

    return 0;
}

int maxflow(int s, int t) {
    int flow = 0;
    vector<int> parent(n);
    int new_flow;

    while (new_flow = bfs(s, t, parent)) {
        flow += new_flow;
        int cur = t;
        while (cur != s) {
            int prev = parent[cur];
            capacityP[prev][cur] -= new_flow;
            capacityP[cur][prev] += new_flow;
            cur = prev;
        }
    }

    return flow;
}

void actualizar_capacity(int d){
    for(int i=x+1;i<adj.size();i++){
        for(int j = x+1; j < adj.size();j++){
            capacityP[i][j] /= d;
        }
    }
}

void grafoSinDirecciones(){
    for(int i=0;i<adj.size();i++){
        for(auto j: adj[i]){
            nuevoAdj[i].push_back(j);
            nuevoAdj[j].push_back(i);
        }
    }
}


int find_result(){
    int low = 0, high = maxArista, mid = (low+high)/2;
    int res = mid;

    while(low != high){
        capacityP = capacity;
        actualizar_capacity(mid);
        nuevoAdj.assign(adj.size(),{}); // grafo sin direcciones para usar en el bfs
        grafoSinDirecciones(); // arma el grafo mencionado arriba

        int flujo_max = maxflow(0, adj.size()-1);
        if(flujo_max == x)
            low = mid;
        else
            high = mid;
        mid = (low+high)/2;
    }

    res = mid;
    return res*x;
}


int main (){
    int tests;
    cin >> tests;
    vector<int> output;

    for (int i = 0; i < tests; i++){

        int N, M;
        cin >> N >> M >> x;

        capacity.assign(M+x+1, vector<int>(M+x+1, 0));
        adj.assign(M+x+1, {});


        for(int k=1;k<=x;k++){
            adj[0].push_back(k); //conecto fuente a cada amigo
            capacity[0][k]=1;
            adj[k].push_back(x+1); //conecto cada amigo a la primera esquina
            capacity[k][x+1]=1;
        }

        maxArista = -INF;
        // conecto esquinas con calles
        for (int j = 0; j < M; j++){
            int u, v, c;
            cin >> u >> v >> c;
            if(c > maxArista) maxArista = c;
            adj[x+u].push_back(x+v);
            capacity[x+u][x+v] = c;
        }

        n = M+x+1;
        output.push_back(find_result());
    }

    for (int i = 0; i < tests; ++i) {
        cout << output[i] << endl;
    }
}
