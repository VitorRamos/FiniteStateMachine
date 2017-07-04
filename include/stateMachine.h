#ifndef MAQUINAESTADOS_H
#define MAQUINAESTADOS_H

#pragma once
#include "states.h"

#include <iostream>
#include <algorithm>
#include <math.h>
#include <vector>
#include <string>

using std::string;
using std::cout;
using std::endl;
using std::vector;

class StateMachine
{
    vector<string> outputs;
    vector<string> inputs;
    vector<State> states;
public:
    bool AddInput(string nome);
    bool AddOutput(string nome);
    bool AddState(string nome, int id, string valor_out);
    bool ConnectState(string estado1, string estado2, string cond);
    string ReplaceValues(string exp, string valores);
    bool ProcessOp(string op);
    int NextStateId(State estado_atual, string todosValores);
    void Possibilities();
};
#endif // MAQUINAESTADOS_H
