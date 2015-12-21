#include <GL/gl.h>
#include <GL/glut.h>

#include "maquinaEstados.h"
#include "estado.h"

void Reshape(int w, int h)
{
    const float ar= (float)w/h;
    glViewport(0,0,w,h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0,ar,0,1);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void Display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



    glutSwapBuffers();
}

int main()
{
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(640, 480);
    glutCreateWindow("MaquinaDeEstados");

    glutReshapeFunc(Reshape);
    glutDisplayFunc(Display);

    glClearColor(1,1,1,1);
    glutMainLoop();
//    MaquinaEstados RTL;
//    RTL.AdicionaVariavelIn("a");
//    RTL.AdicionaVariavelIn("b");
//    RTL.AdicionaVariavelOut("x");
//    RTL.AdicionaVariavelOut("y");
//    RTL.AdicionaEstado("inicial", 0b0, "x=0,y=1");
//    RTL.AdicionaEstado("espera", 0b1, "x=1,y=1");
//    RTL.AdicionaEstado("bt1", 0b10, "x=0,y=0");
//    RTL.Liga("inicial", "espera", "");
//    RTL.Liga("espera", "espera", "!a");
//    RTL.Liga("espera", "bt1", "a");
//    RTL.Liga("bt1", "bt1", "b");
//    RTL.Liga("bt1", "Inicial", "!b");
//    RTL.Possibilidades();
}
