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

string paraMinusculo(string str)
{
    string ret;
    for(unsigned int i=0; i<str.size(); i++)
        ret+=tolower(str[i]);
    return ret;
}

void MaquinaEstados::AdicionaEstado(string nome, int id)
{
    for(auto& est: estados)
        if( (paraMinusculo(nome) == paraMinusculo(est.nome)) || est.id == id ) // mesmo nome ou id
            return;
    estados.push_back(Estado(nome, id));
}
void MaquinaEstados::AdicionaVariavel(string nome)
{
    for(auto& var: variaveis)
        if(var == nome) // mesmo nome variavel
            return ;
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
    string test_cond= cond;
    while(test_cond.find("+")!=string::npos)
        test_cond.replace(test_cond.find("+"),1,"");
    while(test_cond.find("!")!=string::npos)
        test_cond.replace(test_cond.find("!"),1,"");
    for(auto& var: variaveis)
        while(test_cond.find(var)!=string::npos)
            test_cond.replace(test_cond.find(var),var.size(),"");
    if(!test_cond.empty()) // condição invalida
        return;
    int id= -1;
    for(auto& est: estados) if(paraMinusculo(est.nome) == paraMinusculo(e2)) id= est.id;
    if(id == -1) // estado não existe
        return;
    for(auto& est: estados) if(paraMinusculo(est.nome) == paraMinusculo(e1)) est.Liga(id, cond);
}
int MaquinaEstados::ProximoEstadoId(Estado estado_atual, string todosValores)
{
    for(unsigned int i=0; i<estado_atual.condicoes.size(); i++)
        if(ProcessaOp(SubstitueValores(estado_atual.condicoes[i], todosValores)))
            return estado_atual.estado_proximo_id[i];
    return estado_atual.id;
}
void MaquinaEstados::Possibilidades()
{
    int total_poss= variaveis.size();
    int x= pow(2, total_poss);

    int n_var_est= round(log2(estados.size()));

    for(unsigned int i=0; i<n_var_est; i++)
        cout << "Ea" << i << ",";
    for(auto& var: variaveis)
        cout << var << ",";
    for(unsigned int i=0; i<n_var_est; i++)
        cout << "," << "Ep" << i;
    cout << endl;
    for(unsigned int i=0; i<estados.size(); i++)
    {
        for(int j=0; j<x; j++)
        {
            string valores= intToBinary(j, total_poss), todosValores;
            for(unsigned int k=0; k<valores.size(); k++)
            {
                todosValores+=variaveis[k]+"="+valores[k];
                if(k!=valores.size()-1) todosValores+=",";
            }
            string txt_cod_ea= intToBinary(estados[i].id,2);
            string txt_cod_ep= intToBinary(ProximoEstadoId(estados[i], todosValores),2);

//            cout << txt_cod_ea << " " << valores << " " << txt_cod_ep << endl;
            for(unsigned int k=0; k<txt_cod_ea.size(); k++)
                cout << txt_cod_ea[k] << ",";
            for(unsigned int k=0; k<valores.size(); k++)
                cout << valores[k] << ",";
            cout << ",";
            for(unsigned int k=0; k<txt_cod_ep.size(); k++)
            {
                cout << txt_cod_ep[k];
                if(k!=txt_cod_ep.size()-1) cout << ",";
            }
            cout << endl;
            ProximoEstadoId(estados[i], todosValores);
        }
    }
}
