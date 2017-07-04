#ifndef ESTADO_H
#define ESTADO_H

#pragma once

#include <vector>
#include <string>
using std::string;
using std::vector;

class State
{
    string name;
    int id;
    string output;
    vector<string> conditions;
    vector<int> next_state_id;
public:
    State(string name, int id, string valor_out);
    void Connect(int next_state, string condition);
    friend class StateMachine;
};

#endif // ESTADO_H
