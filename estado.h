#ifndef ESTADO_H
#define ESTADO_H

#pragma once

#include <vector>
#include <string>
using std::string;
using std::vector;

class Estado
{
    string nome;
    int id;
    vector<string> condicoes;
    vector<int> estado_proximo_id;
public:
    Estado(string nome, int id);
    void Liga(int estado_prox, string condicao);

    friend class MaquinaEstados;
};

#endif // ESTADO_H
