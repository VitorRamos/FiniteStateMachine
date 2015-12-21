#include <iostream>
using namespace std;

#include "maquinaEstados.h"
#include "estado.h"

int main()
{
    MaquinaEstados RTL;
    RTL.AdicionaVariavelIn("a");
    RTL.AdicionaVariavelIn("b");
    RTL.AdicionaVariavelOut("x");
    RTL.AdicionaVariavelOut("y");
    RTL.AdicionaEstado("inicial", 0b0, "x=0,y=1");
    RTL.AdicionaEstado("espera", 0b1, "x=1,y=1");
    RTL.AdicionaEstado("bt1", 0b10, "x=0,y=0");
    RTL.Liga("inicial", "espera", "");
    RTL.Liga("espera", "espera", "!a");
    RTL.Liga("espera", "bt1", "a");
    RTL.Liga("bt1", "bt1", "b");
    RTL.Liga("bt1", "Inicial", "!b");
    RTL.Possibilidades();
}
