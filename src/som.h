#ifndef SOM_H
#define SOM_H

#include <vector>
#include <utility>
#include "neurona_som.h"

typedef pair<int, int> punto;

using namespace std;

class SOM {
public:
    SOM (int m, int n, int entradas, int salidas=0);
    void read (const char *filename);
    void inicializar ();
    punto calcular (vector<float> patron);
    void entrenar ();
    void entrenar_topo ();
    void entrenar_trans ();
    void entrenar_fino ();
    void entrenar_area (punto & ganador, int lambda, float eta, vector<float> & patron);

private:
    vector<vector<neurona_som> > mapa;
    int m, n; // dimensiones
    int entradas, salidas;
    vector<vector<float> > input, result;
};

#endif
