#ifndef UTIL_H
#define UTIL_H

#include <vector>

using namespace std;

int randomize (int lower, int upper);
float randomize (float lower, float upper);

bool comparar_vectores (vector<float> & a, vector<float> & b);

vector<float> sumar_vectores (vector<float> & a, vector<float> & b);

vector<float> restar_vectores (vector<float> & a, vector<float> & b);

float multiplicar_vectores (vector<float> & a, vector<float> & b);

vector<float> dividir_vector (vector<float> & a, float divisor);

float norma2 (vector<float> & a);

int signo (float a);

void imprimir_vector (vector<float> & a);

#endif
