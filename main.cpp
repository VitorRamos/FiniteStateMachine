#include <iostream>
using namespace std;

#include "maquinaEstados.h"
#include "estado.h"

int main()
{
    MaquinaEstados RTL;
    RTL.AdicionaVariavel("a");
    RTL.AdicionaVariavel("b");
    RTL.AdicionaEstado("inicial", 0b0);
    RTL.AdicionaEstado("espera", 0b1);
    RTL.AdicionaEstado("bt1", 0b10);
    RTL.Liga("inicial", "espera", "");
    RTL.Liga("espera", "espera", "!a");
    RTL.Liga("espera", "bt1", "a");
    RTL.Liga("bt1", "bt1", "b");
    RTL.Liga("bt1", "Inicial", "!b");
    RTL.Possibilidades();
}
