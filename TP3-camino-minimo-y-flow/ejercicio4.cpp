#include "iostream"
#include "vector"
#include "queue"

using namespace std;

vector<vector<int>> capacity;
vector<vector<int>> adj;
vector<vector<int>> capacityP;
int INF = 1e9;

int maxArista, minArista;

int x;

int bfs(int s, int t, vector<int>& parent) {
    fill(parent.begin(), parent.end(), -1);
    parent[s] = -2;
    queue<pair<int, int>> q;
    q.push({s, INF});

    while (!q.empty()) {
        int cur = q.front().first;
        int flow = q.front().second;
        q.pop();

        for (int next : adj[cur]) {
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
    vector<int> parent(adj.size());
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

// actualizamos capacidades como c/k cuando chequeamos la capacidad de k herramientas por amigo
void actualizar_capacity(int d){
    for(int i=1;i<adj.size();i++){
        for(int j: adj[i]){
            if(d != 0){
                capacityP[i][j] = capacity[i][j]/d;
            }else {
                capacityP[i][j] = 0;
            }
        }
    }
}

// esta es la función principal que va buscando de forma binaria el número de herramientas que llevará cada amigo
// luego, el resultado será k*x, siendo x cantidad de amigos y k el número de herramientas hallado
int find_result(){
    int low = 1, high = maxArista, mid = (low+high)/2;
    int res = mid;

    while(low <= high){
        actualizar_capacity(mid);
        int flujo_max = maxflow(0, adj.size()-1);
        capacityP[0][1]=x;
        if(low == 0 and high == 1){mid = 0; break;}
        if(flujo_max >= x)
            low = mid+1;
        else
            high = mid-1;
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

        capacity.assign(N+1, vector<int>(N+1, 0));
        capacityP.assign(N+1, vector<int>(N+1, 0));
        adj.assign(N+1, {});

        adj[0].push_back(1); //conecto fuente a taller
        adj[1].push_back(0);
        capacity[0][1]=x; 
        capacityP[0][1]=x;

        maxArista = -INF;
        minArista = INF;
        // conecto esquinas con calles
        for (int j = 0; j < M; j++){
            int u, v, c;
            cin >> u >> v >> c;
            if(c > maxArista) maxArista = c;
            if(c < minArista) minArista = c;
            adj[u].push_back(v);
            adj[v].push_back(u);
            capacity[u][v] = c;
        }

        output.push_back(find_result());
    }

    for (int i = 0; i < tests; ++i) {
        cout << output[i] << endl;
    }
}
