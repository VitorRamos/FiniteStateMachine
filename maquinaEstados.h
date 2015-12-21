#ifndef MAQUINAESTADOS_H
#define MAQUINAESTADOS_H

#pragma once
#include "estado.h"

#include <iostream>
#include <algorithm>
#include <fstream>
#include <math.h>
#include <vector>
#include <string>

using namespace std;

class MaquinaEstados
{
    vector<string> variaveis_out;
    vector<string> variaveis_in;
    vector<Estado> estados;
public:
    bool AdicionaVariavelIn(string nome);
    bool AdicionaVariavelOut(string nome);
    bool AdicionaEstado(string nome, int id, vector<string> valor_out);
    bool Liga(string estado1, string estado2, string cond);
    string SubstitueValores(string exp, vector<string> valores);
    bool ProcessaOp(string op);
    int ProximoEstadoId(Estado estado_atual, vector<string> todosValores);
    void Possibilidades(ostream& out);
};
#endif // MAQUINAESTADOS_H
