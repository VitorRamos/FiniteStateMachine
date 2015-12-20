#ifndef ESTADO_H
#define ESTADO_H

#pragma once

#include "maquinaEstados.h"

#include <vector>
#include <string>
using std::string;
using std::vector;

class Estado
{
    friend class MaquinaEstados;
    string nome;
    int id;
    vector<string> condicoes;
    vector<int> estado_proximo;
public:
    Estado(string nome, int id);
    void Liga(int estado_prox, string condicao);
};

#endif // ESTADO_H
