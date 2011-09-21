#include <iostream>
#include <cmath>
#include <cstdlib>
#include "util.h"

static const float EPS = 1E-5;

int randomize (int lower, int upper) {
	return rand() % (upper-lower+1) + lower;
}

float randomize (float lower, float upper) {
	return float(rand())/RAND_MAX * (upper-lower) + lower;
}


bool comparar_vectores (vector<float> & a, vector<float> & b) {
    // Devuelve true si son iguales

    if (a.size() != b.size()) {
        cerr << "comparar_vectores: distinto size" << endl;
		cerr << a.size() << ' ' << b.size() << '\n';
        throw 1;
    }
    for (int i = 0; i < a.size(); i++) {
        if (fabs(a[i] - b[i]) > EPS) {
            return false;
        }
    }
    return true;
}

vector<float> sumar_vectores (vector<float> & a, vector<float> & b) {
    vector<float> c(a.size());
    if (a.size() != b.size()) {
        cerr << "sumar_vectores: distinto size" << endl;
        throw 1;
    }

    for (int i = 0; i < a.size(); i++) {
        c[i] = a[i] + b[i];
    }
    return c;
}

vector<float> restar_vectores (vector<float> & a, vector<float> & b) {
    vector<float> c(a.size());
    if (a.size() != b.size()) {
        cerr << "restar_vectores: distinto size" << endl;
        throw 1;
    }

    for (int i = 0; i < a.size(); i++) {
        c[i] = a[i] - b[i];
    }
    return c;
}

float multiplicar_vectores (vector<float> & a, vector<float> & b) {
    float accum = 0;
    vector<float> c(a.size());
    if (a.size() != b.size()) {
        cerr << "multiplicar_vectores: distinto size" << endl;
        throw 1;
    }

    for (int i = 0; i < a.size(); i++) {
        accum += a[i] * b[i];
    }

    return accum;
}

vector<float> dividir_vector (vector<float> & a, float divisor) {
    vector<float> b(a.size());
    for (int i = 0; i < a.size(); i++) {
        b[i] = a[i] / divisor;
    }
    return b;
}

float norma2 (vector<float> & a) {
    float accum = 0;
    for (int i = 0; i < a.size(); i++) {
        accum += a[i]*a[i];
    }
    return sqrt(accum);
}

int signo (float a) {
    if (a > 0) return 1;
    else       return -1;
}

void imprimir_vector (vector<float> & a) {
    for (int i = 0; i < a.size(); i++) {
        cout << a[i] << " ";
    }
    cout << endl;
}
