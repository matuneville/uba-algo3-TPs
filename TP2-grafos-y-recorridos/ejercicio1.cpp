#include <iostream>
#include <set>
#include "vector"
using namespace std;

vector<vector<int>> aristas;
set<pair<int,int>> importantes;

int n=10;
int m;

int NO_LO_VI = 0, EMPECE_A_VER = 1, TERMINE_DE_VER = 2;
vector<int> estado;
vector<int> memo;

vector<vector<int>> tree_edges;
vector<int> back_edges_con_extremo_inferior_en;
vector<int> back_edges_con_extremo_superior_en;

vector<vector<bool>> elimine;
vector<int> padre;

void dfs(int v, int p = -1) {
    estado[v] = EMPECE_A_VER;
    for (int u : aristas[v]) {
        if(elimine[u][v] and elimine[v][u])
            continue;
        if (estado[u] == NO_LO_VI) {
            tree_edges[v].push_back(u);
            padre[u]=v;
            dfs(u, v);
        }
        else if (u != padre[v]) {
            if (estado[u] == EMPECE_A_VER) {
                back_edges_con_extremo_superior_en[v]++;
            }
            else // estado[u] == TERMINE_DE_VER
                back_edges_con_extremo_inferior_en[v]++;
        }
    }
    estado[v] = TERMINE_DE_VER;
}

int cubren(int v, int p) {
    if (memo[v] != -1) return memo[v];
    int res = 0;
    for (int hijo : tree_edges[v]) {
        if (hijo != p) {
            res += cubren(hijo, v);
        }
    }
    res += back_edges_con_extremo_superior_en[v];
    res -= back_edges_con_extremo_inferior_en[v];
    memo[v] = res;
    return res;
}

bool existePuente(){
    bool res=false;
    for(int i = 1; i < n; i++){
        if (memo[i] == 0) {
            res = true;
            break;
        }
    }
    return res;
}

void hallarImportantes(){
    for (int i = 0; i < n; ++i){
        for (int j = 0; j < aristas[i].size(); j++){
            int elem_j = aristas[i][j];
            elimine[i][elem_j] = true;
            elimine[elem_j][i] = true;

            estado.assign(n, NO_LO_VI);
            padre.assign(n,-1);
            tree_edges.assign(n, {});
            back_edges_con_extremo_inferior_en.assign(n, 0);
            back_edges_con_extremo_superior_en.assign(n, 0);

            dfs(0,-1);

            memo.assign(n,-1);
            cubren(0,-1);
            if(existePuente()){
                pair<int, int> aristaImp = make_pair(i, elem_j);
                if (not importantes.count(make_pair(aristaImp.second, aristaImp.first))) {
                    importantes.insert(aristaImp);
                }
            }
            elimine[i][elem_j] = false;
            elimine[elem_j][i] = false;
        }
    }
}


int main() {

    int tests;
    cin >> tests;
    vector<set<pair<int,int>>> todasLasImportantes;

    for (int i = 0; i < tests; ++i) {
        cin >> n >> m;

        aristas.assign(n, {});
        for (int j = 0; j < m; ++j) {
            int v, w;
            cin >> v >> w ;
            aristas[v].push_back(w);
            aristas[w].push_back(v);
        }

        estado.assign(n, NO_LO_VI);
        memo.assign(n,-1);
        tree_edges.assign(n, {});
        elimine.assign(aristas.size(),vector<bool>(n,false));
        back_edges_con_extremo_inferior_en.assign(n, 0);
        back_edges_con_extremo_superior_en.assign(n, 0);
        hallarImportantes();

        todasLasImportantes.push_back(importantes);

        importantes={};
    }
    for (int i = 0; i < tests; ++i){
        cout << todasLasImportantes[i].size() << endl;
        for(pair<int,int> arist : todasLasImportantes[i]){
            cout << arist.first << " " << arist.second << endl;
        }
    }

    return 0;
}