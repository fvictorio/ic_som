#include <vector>
#include <fstream>
#include "som.h"

#include <algorithm>

typedef pair<int, int> punto;

SOM::SOM (int m, int n, int entradas, int salidas) {
    this->m = m;
    this->n = n;
    this->entradas = entradas;
    this->salidas = salidas;
    mapa.resize(m, vector<neurona_som>(n));
}

void SOM::read (const char *filename) {
	int n;

    fstream file (filename, fstream::in);    
    file >> n;
    input.resize(n, vector<float>(entradas));
    result.resize(n, vector<float>(salidas));

	for(int K=0; K<n; ++K){
		for(int L=0; L<entradas; ++L){
			file >> input[K][L];
			file.ignore(); //csv o ssv funciona
		}
		
		for(int L=0; L<salidas; ++L){
			file >> result[K][L];
			file.ignore(); //csv o ssv funciona
		}
	}
}

void SOM::inicializar () {
    int ind;

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            ind = randomize(0, input.size() - 1);
            mapa[i][j].set_weights(input[ind]);
        }
    }
}

punto SOM::calcular (vector<float> patron) {
    int i_min, j_min;
    float dist_min, dist;

    // Tomo el primero
    i_min = 0;
    j_min = 0;
    dist_min = mapa[0][0].calcular_distancia(patron);

    for (int i = 0; i < m; i++) { 
        for (int j = 0; j < n; j++) {
            dist = mapa[i][j].calcular_distancia(patron);
            if (dist < dist_min) {
                i_min = i;
                j_min = j;
                dist_min = dist;
            }
        }
    }

    return punto(i_min, j_min);
}

void SOM::entrenar () {
    entrenar_topo();
    entrenar_trans();
    entrenar_fino();
}

void SOM::entrenar_topo () {
    punto ganador;
    float eta = 0.9;
    int n_epocas = 732, lambda = max(m, n)/2;

    for (int epoca = 0; epoca < n_epocas; epoca++) {
        for (int i = 0; i < input.size(); i++) {
            ganador = this->calcular(input[i]);
            entrenar_area(ganador, lambda, eta, input[i]);
        }
    }
}

void SOM::entrenar_trans () {
    punto ganador;
    float eta = 0.9, lambda = max(m, n)/2.0;
    float eta_i = 0.9, eta_f = 0.1, eta_dif = eta_f - eta_i;
    float lambda_i = max(m, n)/2.0, lambda_f = 1.0, lambda_dif = lambda_f - lambda_i;
    int n_epocas = 1000;

    for (int epoca = 0; epoca < n_epocas; epoca++) {
        for (int i = 0; i < input.size(); i++) {
            ganador = this->calcular(input[i]);
            entrenar_area(ganador, lambda, eta, input[i]);
        }
        // eta y lambda se reducen linealmente
        eta = eta_i - epoca * eta_dif / n_epocas;
        lambda = lambda_i - epoca * lambda_dif / n_epocas;
    }
}

void SOM::entrenar_fino () {
    punto ganador;
    float eta = 0.05;
    int n_epocas = 3000, lambda = 0;

    for (int epoca = 0; epoca < n_epocas; epoca++) {
        for (int i = 0; i < input.size(); i++) {
            ganador = this->calcular(input[i]);
            entrenar_area(ganador, lambda, eta, input[i]);
        }
    }
}

void SOM::entrenar_area (punto & ganador, int lambda, float eta, vector<float> & patron) {
    int a, b;

    for (int i = -lambda; i <= lambda; i++) {
        a = ganador.first + i;
        if (a < 0 || a >= m) continue;
        for (int j = -lambda; j <= lambda; j++) {
            b = ganador.second + j;
            if (b < 0 || b >= n) continue;
            mapa[a][b].entrenar(patron, eta);
        }
    }
}

