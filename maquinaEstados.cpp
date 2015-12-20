#include "maquinaEstados.h"

// Utilitarios
string intToBinary(int n, int nbits= 0)
{
    string ret;
    while(n>0)
    {
        if(n%2==0) ret+="0";
        else ret+="1";
        n/=2;
    }
    reverse(ret.begin(), ret.end());
    if(nbits == 0)
        return ret == "" ? "0" : ret;
    int totalBits= nbits-ret.size();
    for(int i=0; i<totalBits; i++)
        ret.insert(0,"0");
    return ret;
}

void MaquinaEstados::AdicionaEstado(string nome, int id)
{
    estados.push_back(Estado(nome, id));
}
void MaquinaEstados::AdicionaVariavel(string nome)
{
    variaveis.push_back(nome);
}
string MaquinaEstados::SubstitueValores(string exp, string valores)
{
    while(valores.find("=")!=string::npos)
    {
        string valor= valores.substr(valores.find("=")+1, 1);
        string letra= valores.substr(valores.find("=")-1, 1);
        if(exp.find(letra)!=string::npos)
            exp.replace(exp.find(letra), 1, valor);
        valores.replace(valores.find("="), 1, "");
    }
    return exp;
}
bool MaquinaEstados::ProcessaOp(string op)
{
    // Processa not
    while(op.find("!0") != string::npos)
        op.replace(op.find("!0"), 2, "1");
    while(op.find("!1") != string::npos)
        op.replace(op.find("!1"), 2, "0");
    // Processa and
    while(op.find("00") != string::npos)
        op.replace(op.find("00"), 2, "0");
    while(op.find("01") != string::npos)
        op.replace(op.find("01"), 2, "0");
    while(op.find("10") != string::npos)
        op.replace(op.find("10"), 2, "0");
    while(op.find("11") != string::npos)
        op.replace(op.find("11"), 2, "1");
    //Processa or
    if(op.find("1")!=string::npos || op.empty())
        return true;
    return false;
}
void MaquinaEstados::Liga(string e1, string e2, string cond)
{
    int id= -1;
    for(auto& est: estados) if(est.nome == e2) id= est.id;
    for(auto& est: estados) if(est.nome == e1) est.Liga(id, cond);
}
int MaquinaEstados::ProximoEstado(Estado estado_atual, string todosValores)
{
    for(unsigned int i=0; i<estado_atual.condicoes.size(); i++)
    {
        if(ProcessaOp(SubstitueValores(estado_atual.condicoes[i], todosValores)))
        {
            return estado_atual.estado_proximo[i];
        }
    }
    return estado_atual.id;
}
void MaquinaEstados::Possibilidades()
{
    int total_poss= variaveis.size();
    int x= pow(2, total_poss);
    for(unsigned int i=0; i<estados.size(); i++)
    {
        for(int j=0; j<x; j++)
        {
            string valores= intToBinary(j, total_poss), todosValores;
            for(unsigned int k=0; k<valores.size(); k++)
            {
                todosValores+=variaveis[k]+"="+valores[k];
                if(k!=valores.size()-1)
                    todosValores+=",";
            }
            cout << intToBinary(estados[i].id,2) << " " << valores << " "
            << intToBinary(ProximoEstado(estados[i], todosValores),2) << endl;
            ProximoEstado(estados[i], todosValores);
        }
    }
}

