#include "stateMachine.h"

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

bool StateMachine::AddInput(string name)
{
    for(auto& var: inputs)
        if(var == name) // mesmo name variavel
            return false;
    inputs.push_back(name);
    return true;
}
bool StateMachine::AddOutput(string name)
{
    for(auto& var: outputs)
        if(var == name) // mesmo name variavel
            return false;
    outputs.push_back(name);
    return true;
}
bool StateMachine::AddState(string name, int id, string valor_out)
{
    //Verificar variaveis do valor_out
    for(auto& est: states)
        if( (paraMinusculo(name) == paraMinusculo(est.name)) || est.id == id ) // mesmo name ou id
            return false;
    states.push_back(State(name, id, valor_out));
    return true;
}
bool StateMachine::ConnectState(string estado1, string estado2, string cond)
{
    string test_cond= cond;
    while(test_cond.find("+")!=string::npos)
        test_cond.replace(test_cond.find("+"),1,"");
    while(test_cond.find("!")!=string::npos)
        test_cond.replace(test_cond.find("!"),1,"");
    for(auto& var: inputs)
        while(test_cond.find(var)!=string::npos)
            test_cond.replace(test_cond.find(var),var.size(),"");
    if(!test_cond.empty()) // condição invalida
        return false;
    int id= -1;
    for(auto& est: states) if(paraMinusculo(est.name) == paraMinusculo(estado2)) id= est.id;
    if(id == -1) // estado não existe
        return false;
    for(auto& est: states) if(paraMinusculo(est.name) == paraMinusculo(estado1)) est.Connect(id, cond);
    return true;
}
string StateMachine::ReplaceValues(string exp, string valores)
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
bool StateMachine::ProcessOp(string op)
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

int StateMachine::NextStateId(State estado_atual, string todosValores)
{
    for(unsigned int i=0; i<estado_atual.conditions.size(); i++)
        if(ProcessOp(ReplaceValues(estado_atual.conditions[i], todosValores)))
            return estado_atual.next_state_id[i];
    return estado_atual.id;
}
void StateMachine::Possibilities()
{
    int total_poss= inputs.size();
    int x= pow(2, total_poss);
    int n_var_est= round(log2(states.size()));

    string varOut;
    for(auto& var: outputs)
        varOut+=var;
    for(int i=0; i<n_var_est; i++)
        cout << "Ea" << i << ",";
    for(auto& var: inputs)
        cout << var << ",";
    for(int i=0; i<n_var_est; i++)
        cout << "," << "Ep" << i;
    for(auto& var: outputs)
        cout << "," << var;
    cout << endl;
    for(unsigned int i=0; i<states.size(); i++)
    {
        for(int j=0; j<x; j++)
        {
            string valores= intToBinary(j, total_poss), todosValores;
            for(unsigned int k=0; k<valores.size(); k++)
            {
                todosValores+=inputs[k]+"="+valores[k];
                if(k!=valores.size()-1) todosValores+=",";
            }
            string txt_cod_ea= intToBinary(states[i].id,2);
            string txt_cod_ep= intToBinary(NextStateId(states[i], todosValores),2);
            string txt_var_out= ReplaceValues(varOut, states[i].output);
//            cout << txt_cod_ea << " " << valores << " " << txt_cod_ep
//            << " " << ReplaceValues(varOut, states[i].output) << endl;
            for(unsigned int k=0; k<txt_cod_ea.size(); k++)
                cout << txt_cod_ea[k] << ",";
            for(unsigned int k=0; k<valores.size(); k++)
                cout << valores[k] << ",";
            cout << ",";
            for(unsigned int k=0; k<txt_cod_ep.size(); k++)
                cout << txt_cod_ep[k] << ",";
            for(unsigned int k=0; k<txt_var_out.size(); k++)
            {
                cout << txt_var_out[k];
                if(k != txt_var_out.size()-1) cout << ",";
            }
            cout << endl;
            NextStateId(states[i], todosValores);
        }
    }
}
