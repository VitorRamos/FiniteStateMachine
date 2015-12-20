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
    vector<string> variaveis;
    vector<Estado> estados;
public:
    void AdicionaEstado(string nome, int id);
    void AdicionaVariavel(string nome);
    string SubstitueValores(string exp, string valores);
    bool ProcessaOp(string op);
    void Liga(string e1, string e2, string cond);
    int ProximoEstado(Estado estado_atual, string todosValores);
    void Possibilidades();
};
#endif // MAQUINAESTADOS_H
