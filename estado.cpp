#include "estado.h"

Estado::Estado(string nome, int id, string valor_out)
{
    this->id= id;
    this->nome= nome;
    this->valor_out= valor_out;
}
void Estado::Liga(int estado_prox, string condicao)
{
    estado_proximo_id.push_back(estado_prox);
    condicoes.push_back(condicao);
}
