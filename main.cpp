#include <iostream>
#include <map>
#include <vector>

using namespace std;

struct Estado
{
    string nome;
    vector<string> condicoes;
    vector<string> estado_proximo;
    void Liga(string estado_prox, string condicao)
    {
        estado_proximo.push_back(estado_prox);
        condicoes.push_back(condicao);
    }
    string ProximoEstado(string todasCond)
    {
        for(int i=0; i<condicoes.size(); i++)
        {
            if(todasCond.find(condicoes[i]) != string::npos)
            {
                return estado_proximo[i];
            }
        }
    }
};
int main()
{
    Estado
}
