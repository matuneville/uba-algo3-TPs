#include "vector"
#include "queue"
#include "iostream"
using namespace std;


struct vertice {
    int x;
    int y;
    int d;

    vertice(int x, int y, int d) : x(x), y(y), d(d) {}
};

int n;
int m;
int inf = 1e9;

// X     Y     D        vecinos
vector<vector<vector<vector<vertice>>>> grafo;
vector<vector<vector<bool>>> visitado;
vector<vector<vector<int>>> distancia;
pair<int,int> posInicial;
pair<int,int> posFinal;
int dx[] = {-1, 1, 0, 0}; // las cuatro direcciones a las que se puede ir
int dy[] = {0, 0, -1, 1};
vector<vector<int>> matriz;


void crearGrafo() { // O(m*n*k)
    for (int x = 0; x < n; ++x) {
        for (int y = 0; y < m; ++y) {
            for (int d = 0; d < n * m; ++d) {
                for (int i = 0; i < 4; ++i) {
                    int nuevoX = x + dx[i];
                    int nuevoY = y + dy[i];
                    if (nuevoX >= 0 && nuevoX < n && nuevoY >= 0 && nuevoY < m) {
                        if (d+1 < matriz[nuevoX][nuevoY]) {
                            grafo[x][y][d].push_back(vertice(nuevoX, nuevoY, d+1));
                        }
                    }
                }
            }
        }
    }
}

int bfs(vertice s) {
    visitado[s.x][s.y][s.d] = true;
    queue<pair<vertice,int>> q;
    q.push({s,0});
    while (!q.empty()) {
        pair<vertice,int> v = q.front();
        q.pop();
        for (auto u : grafo[v.first.x][v.first.y][v.first.d]) {
            if (!visitado[u.x][u.y][u.d]) {
                visitado[u.x][u.y][u.d] = true;
                distancia[u.x][u.y][u.d] = distancia[v.first.x][v.first.y][v.first.d] + 1;
                int dist = distancia[u.x][u.y][u.d];
                q.push({u,dist});
                if( posFinal.first == u.x and posFinal.second == u.y)
                    return dist;
            }
        }
    }
    return -1; // no llega nunca a w
}


int main(){
    int tests;
    cin>> tests;

    vector<pair<int,int>> output(tests, {-1,-1});

    for (int i = 0; i < tests; ++i) {

        cin >> n >> m;

        matriz.assign(n, vector<int>(m, inf));
        grafo.assign(n, vector<vector<vector<vertice>>>(m, vector<vector<vertice>>(n*m)));

        for (int k = 0; k < n; ++k) {
            for (int j = 0; j < m; ++j) {
                int x;
                cin >> x;
                if (x != 0) matriz[k][j] = x;
            }
        }

        int inicio1, inicio2;
        cin >> inicio1 >> inicio2;
        pair<int,int> inicio = {inicio1, inicio2};

        int fin1, fin2;
        cin >> fin1 >> fin2;
        pair<int,int> fin = {fin1, fin2};

        if (inicio == fin){
            pair<int,int> res = {0, 0};
            output[i] = res;
            continue;
        }

        posInicial = inicio;
        posFinal = fin;
        crearGrafo();

        visitado.assign(n, vector<vector<bool>>(m, vector<bool>(n*m,false)));

        // ######## ######## ######## ######## ######## ######## ######## ######## ######## ######## ######## ######## ######## ########
        // ######## ######## ######## ######## ######## ######## ######## ######## ######## ######## ######## ######## ######## ########

                        // esta shit no anda,
                        // explota toda la memoria cuando utilizo vector distancia en el 2do test

                        distancia.clear();

                        vector<int> d1(n*m,0);
                        vector<vector<int>> d2(m, d1);
                        vector<vector<vector<int>>> d3(n, d2);
                        distancia = d3;

        // ######## ######## ######## ######## ######## ######## ######## ######## ######## ######## ######## ######## ######## ########
        // ######## ######## ######## ######## ######## ######## ######## ######## ######## ######## ######## ######## ######## ########

        int res1 = bfs({posInicial.first, posInicial.second, 0});

        if(res1 == -1)
            continue;

        posInicial = fin;
        posFinal = inicio;

        visitado.assign(n, vector<vector<bool>>(m, vector<bool>(n*m,false)));

        distancia.assign(n, d2);

        int res2 = bfs({posInicial.first, posInicial.second, res1});

        if(res2 == -1)
            continue;

        pair<int,int> res = {res1, res1+res2};
        output[i] = res;
    }

    for (int i = 0; i < tests; ++i) {
        if(output[i].first == -1 or output[i].second == -1)
            cout << "IMPOSIBLE" << endl;
        else cout << output[i].first << " " << output[i].second << endl;
    }

}