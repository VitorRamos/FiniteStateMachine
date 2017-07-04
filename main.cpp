#include <iostream>
using namespace std;

#include "stateMachine.h"
#include "states.h"

int main()
{
    StateMachine RTL;
    RTL.AddInput("a");
    RTL.AddInput("b");
    RTL.AddOutput("x");
    RTL.AddOutput("y");
    RTL.AddState("inicial", 0b0, "x=0,y=1");
    RTL.AddState("espera", 0b1, "x=1,y=1");
    RTL.AddState("bt1", 0b10, "x=0,y=0");
    RTL.ConnectState("inicial", "espera", "");
    RTL.ConnectState("espera", "espera", "!a");
    RTL.ConnectState("espera", "bt1", "a");
    RTL.ConnectState("bt1", "bt1", "b");
    RTL.ConnectState("bt1", "Inicial", "!b");
    RTL.Possibilities();
}
