#include "iostream"
#include "vector"
#include "queue"
using namespace std;

#define matriz vector<vector<int>>

matriz lat;
matriz dist;
matriz ady;
int n;

/* Pseudocódigo a replicar:
 *
 *  para cada (k = 1 ... n)             // por cada vertice vemos:
 *      para cada (i = 1 ... n)
 *          para cada (j = 1 ... n)             // para cada par de vertices i,j
 *              if not (lat[i][j] <= lat[i][k] + lat[k][j]) return IMPOSIBLE
 * */

bool check_floyd_warshall(){    // chequea si la matriz de latencias es una "matriz Floyd-Warshall" (como el ej13 de la guia)
    for(int k = 1; k <= n; k++)
        for(int i = 1; i <= n; i++)
            for(int j = 1; j <= n; j++)
                if(lat[i][j] > lat[i][k] + lat[k][j]) return false;

    return true;
}


void quitar_innecesarias(){     // para tener la mínima cantidad de aristas necesarias
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= n; j++)
            for(int k = 1; k <= n; k++)
                if (lat[i][j] == lat[i][k] + lat[k][j] and k!=i and k!=j)
                    ady[i][j] = 0;
}


vector<int> bfs(int raiz){
    vector<int> distancias(n+1, -1);  // -1 = inf
    distancias[raiz] = 0;
    queue<int> q;
    q.push(raiz);
    while (not q.empty()) {
        int nodo = q.front();
        q.pop();
        for (int neighbor = 1; neighbor <= n; ++neighbor) {
            if (ady[nodo][neighbor] == 1 && distancias[neighbor] == -1) {
                // si hay conexion a vecino no visitado, actualizo distancia
                distancias[neighbor] = distancias[nodo] + 1;
                q.push(neighbor);
            }
        }
    }
    return distancias;
}



int main(){
    int tests;
    cin>> tests;

    vector<matriz> output(tests, {{}});
    matriz vacio = {{}};

    for(int k=0; k < tests; k++){
        int n_test;
        cin >> n_test;
        n = n_test;
        lat.assign(n+1, vector<int>(n+1, 0));
        ady.assign(n+1, vector<int>(n+1, 0));
        dist.assign(n+1, vector<int>(n+1, 0));

        for(int j=2; j<=n; j++){
            for(int h=1; h<j; h++){
                int l;
                cin >> l;

                lat[j][h]=l; // armamos matriz de latencias
                lat[h][j]=l; // de manera simétrica

                ady[j][h]=1; // armamos matriz de adyacencia
                ady[h][j]=1; // para luego quitar aristas más fácilmente
            }
        }

        int answer = check_floyd_warshall(); // O(n³)

        if(answer == 1){
            quitar_innecesarias(); // O(n³)

            // hacer bfs con matriz de adyacencia por cada uno para calcular diastancias minimas
            // O( n * BFS) = O(n (n²)) = O(n³)
            for(int i = 1; i <= n ; i++){
                dist[i] = bfs(i); // devuelve distancias
            }
            output[k] = dist;
        }
    }

    for (int i = 0; i < tests; ++i) {
        if(output[i] == vacio){
            cout<< "IMPOSIBLE" << endl;
            continue;
        }
        cout<< "POSIBLE"<< endl;
        for (int j = 1; j < output[i].size(); ++j) {
            for (int k = 1; k < output[i].size(); ++k) {
                cout << output[i][j][k] << " ";
            }
            cout << endl;
        }
    }
}


/* test 4
 *     1 | 2 | 3 | 4   // matriz de latencias
 * 1 | 0   1   3   2
 * 2 | 1   0   2   1
 * 3 | 3   2   0   2
 * 4 | 2   1   2   0
 * */

/* test 2
 *     1 | 2 | 3    // matriz de latencias
 * 1 | 0   1   3
 * 2 | 1   0   1   lat 1-3 <= lat 1-2 + lat 2-3 ? FALSO
 * 3 | 3   1   0
 * */