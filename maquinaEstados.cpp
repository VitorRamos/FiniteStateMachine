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

bool MaquinaEstados::AdicionaVariavelIn(string nome)
{
    for(auto& var: variaveis_in)
        if(var == nome) // mesmo nome variavel
            return false;
    variaveis_in.push_back(nome);
    return true;
}
bool MaquinaEstados::AdicionaVariavelOut(string nome)
{
    for(auto& var: variaveis_out)
        if(var == nome) // mesmo nome variavel
            return false;
    variaveis_out.push_back(nome);
    return true;
}
bool MaquinaEstados::AdicionaEstado(string nome, int id, vector<string> valor_out)
{
    //Verificar variaveis do valor_out
    for(auto& est: estados)
        if( (paraMinusculo(nome) == paraMinusculo(est.nome)) || est.id == id ) // mesmo nome ou id
            return false;
    estados.push_back(Estado(nome, id, valor_out));
    return true;
}
bool MaquinaEstados::Liga(string estado1, string estado2, string cond)
{
    string test_cond= cond;
    while(test_cond.find("+")!=string::npos)
        test_cond.replace(test_cond.find("+"),1,"");
    while(test_cond.find("!")!=string::npos)
        test_cond.replace(test_cond.find("!"),1,"");
    for(auto& var: variaveis_in)
        while(test_cond.find(var)!=string::npos)
            test_cond.replace(test_cond.find(var),var.size(),"");
    if(!test_cond.empty()) // condição invalida
        return false;
    int id= -1;
    for(auto& est: estados) if(paraMinusculo(est.nome) == paraMinusculo(estado2)) id= est.id;
    if(id == -1) // estado não existe
        return false;
    for(auto& est: estados) if(paraMinusculo(est.nome) == paraMinusculo(estado1)) est.Liga(id, cond);
    return true;
}
string MaquinaEstados::SubstitueValores(string exp, vector<string> valores)
{
    for(unsigned int i=0; i<valores.size(); i++)
    {
        string letra= valores[i].substr(0, valores[i].find("="));
        string valor= valores[i].substr(valores[i].find("=")+1, 1);
         if(exp.find(letra)!=string::npos)
            exp.replace(exp.find(letra), letra.size(), valor);
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

int MaquinaEstados::ProximoEstadoId(Estado estado_atual, vector<string> todosValores)
{
    for(unsigned int i=0; i<estado_atual.condicoes.size(); i++)
    {
//        cout << SubstitueValores(estado_atual.condicoes[i], todosValores) << endl;
        if(ProcessaOp(SubstitueValores(estado_atual.condicoes[i], todosValores)))
            return estado_atual.estado_proximo_id[i];
    }
    return estado_atual.id;
}
void MaquinaEstados::Possibilidades(ostream& out)
{
    int n_var_in= variaveis_in.size();
    int x= pow(2, n_var_in);
    int n_var_est= round(log2(estados.size()));

    string varOut;
    for(auto& var: variaveis_out)
        varOut+=var;
    for(int i=0; i<n_var_est; i++)
        out << "Ea" << i << ",";
    for(auto& var: variaveis_in)
        out << var << ",";
    for(int i=0; i<n_var_est; i++)
        out << "," << "Ep" << i;
    for(auto& var: variaveis_out)
        out << "," << var;
    out << endl;
    for(unsigned int i=0; i<estados.size(); i++)
    {
        for(int j=0; j<x; j++)
        {
            string valores= intToBinary(j, n_var_in); // ,todosValores;
            vector<string> todosValores;
            for(unsigned int k=0; k<valores.size(); k++)
            {
                string aux= variaveis_in[k]+"="+valores[k];
                todosValores.push_back(aux);
            }
            string txt_cod_ea= intToBinary(estados[i].id, n_var_est);
            string txt_cod_ep= intToBinary(ProximoEstadoId(estados[i], todosValores), n_var_est);
            string txt_var_out= SubstitueValores(varOut, estados[i].valor_out);
//            out << txt_cod_ea << " " << valores << " " << txt_cod_ep
//            << " " << SubstitueValores(varOut, estados[i].valor_out) << endl;
            for(unsigned int k=0; k<txt_cod_ea.size(); k++)
                out << txt_cod_ea[k] << ",";
            for(unsigned int k=0; k<valores.size(); k++)
                out << valores[k] << ",";
            for(unsigned int k=0; k<txt_cod_ep.size(); k++)
                out << "," << txt_cod_ep[k];
            for(unsigned int k=0; k<txt_var_out.size(); k++)
                out << "," << txt_var_out[k];
            out << endl;
            ProximoEstadoId(estados[i], todosValores);
        }
    }
}
