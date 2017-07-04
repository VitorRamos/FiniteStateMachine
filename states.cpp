#include "states.h"

State::State(string name, int id, string output)
{
    this->id= id;
    this->name= name;
    this->output= output;
}
void State::Connect(int next_state, string condition)
{
    next_state_id.push_back(next_state);
    conditions.push_back(condition);
}
