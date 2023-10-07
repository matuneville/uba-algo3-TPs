#include "vector"
#include "queue"
#include "iostream"
using namespace std;

typedef pair<int,int> vertice;

int n;
int m;
int inf = 1e9;

// X     Y       vecinos
vector<vector<vector<vertice>>> grafo;
vector<vector<bool>> visitado;
vector<vector<int>> distancia;
vertice posInicial;
vertice posFinal;
int dx[] = {-1, 1, 0, 0}; // las cuatro direcciones a las que se puede ir
int dy[] = {0, 0, -1, 1};
vector<vector<int>> matriz;


void crearGrafo() { // O(m*n*n*m)
    for (int x = 0; x < n; ++x) {
        for (int y = 0; y < m; ++y) {
            for (int i = 0; i < 4; ++i) {
                int nuevoX = x + dx[i];
                int nuevoY = y + dy[i];
                if (nuevoX >= 0 && nuevoX < n && nuevoY >= 0 && nuevoY < m) {
                    grafo[x][y].push_back(vertice(nuevoX, nuevoY));
                }
            }
        }
    }
}

int bfs(vertice s) {
    visitado[s.first][s.second] = true;
    queue<pair<vertice,int>> q;
    q.push({s,0});
    while (!q.empty()) {
        pair<vertice,int> v = q.front();
        q.pop();
        for (auto u : grafo[v.first.first][v.first.second]) {
            if (!visitado[u.first][u.second] && !(distancia[v.first.first][v.first.second] + 1 >= matriz[u.first][u.second])) {
                visitado[u.first][u.second] = true;
                distancia[u.first][u.second] = distancia[v.first.first][v.first.second] + 1;
                int dist = distancia[u.first][u.second];
                q.push({u,dist});
                if( posFinal.first == u.first and posFinal.second == u.second)
                    return dist;
            }
        }
    }
    return -1; // no llega nunca a w
}


int main(){
    int tests;
    cin>> tests;

    vector<vertice> output(tests, {-1,-1});

    for (int i = 0; i < tests; ++i) {

        cin >> n >> m;

        matriz.assign(n, vector<int>(m, inf));
        grafo.assign(n, vector<vector<vertice>>(m));

        for (int k = 0; k < n; ++k) {
            for (int j = 0; j < m; ++j) {
                int x;
                cin >> x;
                if (x != 0) matriz[k][j] = x;
            }
        }

        int inicio1, inicio2;
        cin >> inicio1 >> inicio2;
        vertice inicio = {inicio1, inicio2};

        int fin1, fin2;
        cin >> fin1 >> fin2;
        vertice fin = {fin1, fin2};

        if (inicio == fin){
            vertice res = {0, 0};
            output[i] = res;
            continue;
        }

        posInicial = vertice(inicio.first,inicio.second);
        posFinal = vertice(fin.first,fin.second);
        crearGrafo();

        visitado.assign(n, vector<bool>(m));
        distancia.assign(n,vector<int>(m, 0));

        int res1 = bfs(posInicial);
        if(res1 == -1)
            continue;

        posInicial = fin;
        posFinal = inicio;
        visitado.assign(n, vector<bool>(m, false));

        int res2 = bfs(posInicial);
        if(res2 == -1)
            continue;

        pair<int,int> res = {res1, res2};
        output[i] = res;
    }

    for (int i = 0; i < tests; ++i) {
        if(output[i].first == -1 or output[i].second == -1)
            cout << "IMPOSIBLE" << endl;
        else cout << output[i].first << " " << output[i].second << endl;
    }

    return 0;

}
