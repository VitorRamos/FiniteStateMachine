#include "estado.h"

Estado::Estado(string nome, int id)
{
    this->id= id;
    this->nome= nome;
}
void Estado::Liga(int estado_prox, string condicao)
{
    estado_proximo_id.push_back(estado_prox);
    condicoes.push_back(condicao);
}
