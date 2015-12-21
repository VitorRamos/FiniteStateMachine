#ifndef MAQUINAESTADOS_H
#define MAQUINAESTADOS_H

#pragma once
#include "estado.h"

#include <iostream>
#include <algorithm>
#include <math.h>
#include <vector>
#include <string>

using std::string;
using std::cout;
using std::endl;
using std::vector;

class MaquinaEstados
{
    vector<string> variaveis_out;
    vector<string> variaveis_in;
    vector<Estado> estados;
public:
    bool AdicionaVariavelIn(string nome);
    bool AdicionaVariavelOut(string nome);
    bool AdicionaEstado(string nome, int id, string valor_out);
    bool Liga(string estado1, string estado2, string cond);
    string SubstitueValores(string exp, string valores);
    bool ProcessaOp(string op);
    int ProximoEstadoId(Estado estado_atual, string todosValores);
    void Possibilidades();
};
#endif // MAQUINAESTADOS_H
