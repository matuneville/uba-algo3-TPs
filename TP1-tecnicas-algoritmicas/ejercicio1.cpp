#include "iostream"
#include "vector"

using namespace std;

using tablero = vector<vector<char>>;
using coord = pair<int, int>;
using direc = int; // 0: arriba, 1: abajo, 2: izquierda, 3: derecha

// variables globales
tablero tab = {{}};
vector<vector<bool>> visitado;
int h = tab.size(); // alto
int w = tab[0].size(); // ancho
int camino_min = 1e9;
int camino_max = -1;

vector<pair<coord, direc>> siguientes(coord pos, direc prev_dir);

bool esValida(coord pos){
    if ((pos.first < 0 or pos.first >= h) or (pos.second < 0 or pos.second >= w)) return false;
    if(tab[pos.first][pos.second] == '#') return false;

    return true;
}

void encontrarCaminos(coord pos, direc prev_dir, int actual ){
    // no solucion
    if(visitado[pos.first][pos.second])
        return ;

    // solucion
    if(pos.first == h-1 and pos.second == w-1){
        camino_min = actual < camino_min ? actual : camino_min;
        camino_max = actual > camino_max ? actual : camino_max;
        return ;
    }

    vector<pair<coord, direc>> siguientesPos = siguientes(pos, prev_dir); // devuelvo a los lugares que puede visitar

    int sigsLen = siguientesPos.size();
    for (int i = 0; i < sigsLen; i++) {
        pair<coord, direc> sgte = siguientesPos[i];
        visitado[pos.first][pos.second] = true;
        encontrarCaminos(sgte.first, sgte.second, actual + 1);
        visitado[pos.first][pos.second] = false;
    }
}

vector<pair<coord, direc>> siguientes(coord pos, direc prev_dir){
    const char forma = tab[pos.first][pos.second];
    vector<pair<coord,direc>> siguientesPos = {};
    // cada elemento dirá cuál será la siguiente pos a jugar, y desde que dirección vamos a ella

    coord arriba = make_pair(pos.first-1,pos.second);
    coord abajo = make_pair(pos.first+1,pos.second);
    coord derecha = make_pair(pos.first,pos.second+1);
    coord izquierda = make_pair(pos.first,pos.second-1);

    vector<pair<int,int>> direcciones_posibles={arriba,abajo,izquierda,derecha};


    // 0: arriba, 1: abajo, 2: izquierda, 3: derecha
    // -1: direccion especial para el primer llamado
    switch (forma) {
        case 'I':
            if (prev_dir == -1){
                if(esValida(abajo)) siguientesPos.push_back(make_pair(abajo,0));
                if(esValida(derecha)) siguientesPos.push_back(make_pair(derecha,2));
            }
            else if (prev_dir == 0) {
                if (esValida(abajo)) siguientesPos.push_back(make_pair(abajo, 0));
            }
            else if (prev_dir == 1) {
                if(esValida(arriba)) siguientesPos.push_back(make_pair(arriba,1));
            }
            else if(prev_dir == 2){
                if(esValida(derecha)) siguientesPos.push_back(make_pair(derecha,2));
            }
            else{
                if(esValida(izquierda))siguientesPos.push_back(make_pair(izquierda,3));
            }
            break;

        case 'L':
            if (prev_dir == -1){
                if(esValida(abajo)) siguientesPos.push_back(make_pair(abajo,0));
                if(esValida(derecha)) siguientesPos.push_back(make_pair(derecha,2));
            }
            else if (prev_dir == 0) {
                if(esValida(izquierda)) {
                    if (pos.first != h-1)
                        siguientesPos.push_back(make_pair(izquierda, 3));
                }
                if(esValida(derecha)) siguientesPos.push_back(make_pair(derecha,2));
            }
            else if (prev_dir == 1) {
                if(esValida(izquierda)) {
                    if (pos.first != 0)
                        siguientesPos.push_back(make_pair(izquierda, 3));
                }
                if(esValida(derecha)) siguientesPos.push_back(make_pair(derecha,2));
            }
            else if (prev_dir == 2) {
                if(esValida(arriba)) {
                    if (pos.second != w-1)
                        siguientesPos.push_back(make_pair(arriba, 1));
                }
                if(esValida(abajo))siguientesPos.push_back(make_pair(abajo,0));
            }
            else if (prev_dir == 3) {
                if(esValida(arriba)) {
                    if (pos.second != 0)
                        siguientesPos.push_back(make_pair(arriba, 1));
                }
                if(esValida(abajo))siguientesPos.push_back(make_pair(abajo,0));
            }
            break;

        case '+':
            if (prev_dir == -1){
                if(esValida(abajo))siguientesPos.push_back(make_pair(abajo,0));
                if(esValida(derecha))siguientesPos.push_back(make_pair(derecha,2));
            }
            else if (prev_dir == 0) {//proba ahora
                if(esValida(abajo)) siguientesPos.push_back(make_pair(abajo,0));
                if(esValida(izquierda)) {
                    if (pos.first != h-1)
                        siguientesPos.push_back(make_pair(izquierda, 3));
                }
                if(esValida(derecha)) siguientesPos.push_back(make_pair(derecha,2));
            }
            else if (prev_dir == 1) {(make_pair(izquierda,3));
                if(esValida(arriba)) siguientesPos.push_back(make_pair(arriba,1));
                if(esValida(izquierda)) {
                    if (pos.first != 0)
                        siguientesPos.push_back(make_pair(izquierda, 3));
                }
                if(esValida(derecha)) siguientesPos.push_back(make_pair(derecha,2));
            }
            else if (prev_dir == 2) {
                if(esValida(arriba)) {
                    if (pos.second != w-1)
                        siguientesPos.push_back(make_pair(arriba, 1));
                }
                if(esValida(abajo)) siguientesPos.push_back(make_pair(abajo,0));
                if(esValida(derecha)) siguientesPos.push_back(make_pair(derecha,2));
            }
            else if (prev_dir == 3) {
                if (esValida(arriba)) {
                    if (pos.second != 0)
                        siguientesPos.push_back(make_pair(arriba, 1));
                }
                if (esValida(abajo)) siguientesPos.push_back(make_pair(abajo,0));
                if (esValida(izquierda)) siguientesPos.push_back(make_pair(izquierda,3));
            }
            break;

        default: // caso #
            break;
    }
    return siguientesPos;
}

int main() {
    int jeugos = 0;
    cin >> jeugos;
    vector<pair<int, int>> salidas;
    for (int i = 0; i < jeugos; i++) {
        cin >> h >> w;
        tab = tablero(h, vector<char>(w));
        visitado = vector<vector<bool>>(h, vector<bool>(w, false));


        for (int k = 0; k < h; k++) {
            for (int j = 0; j < w; j++) {
                cin >> tab[k][j];
            }
        }

        if (w > 0 and h > 0) {
            if ((tab[h - 1][w - 1] == '#') or (tab[0][0] == '#') or (tab[0][1] == '#' and tab[1][0] == '#')) {
                salidas.push_back(make_pair(1e9, -1));
                continue;//
            }
            if (w > 1 and h > 1) {
                if (tab[h - 2][w - 1] == '#' and tab[h - 1][w - 2] == '#') {
                    salidas.push_back(make_pair(1e9, -1));
                    continue;
                }
            }
        }
        encontrarCaminos(make_pair(0, 0), -1, 0);
        salidas.push_back(make_pair(camino_min, camino_max));
        camino_max = -1;
        camino_min = 1e9;
    }

    for (pair<int, int> jugada: salidas) {
        if (jugada.first != 1e9) {
            cout << "POSIBLE " << jugada.first << " " << jugada.second << endl;
        } else
            cout << "IMPOSIBLE" << endl;
    }
}