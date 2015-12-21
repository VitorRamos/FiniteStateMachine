#include <GL/gl.h>
#include <GL/glut.h>
#include <fstream>

using std::ofstream;

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
//    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
//    glutInitWindowSize(640, 480);
//    glutCreateWindow("MaquinaDeEstados");
//
//    glutReshapeFunc(Reshape);
//    glutDisplayFunc(Display);
//
//    glClearColor(1,1,1,1);
//    glutMainLoop();

    MaquinaEstados RTL;
    RTL.AdicionaVariavelIn("btt_press");
    RTL.AdicionaVariavelIn("cont_1_igual5");
    RTL.AdicionaVariavelIn("cont_2_igual5");
    RTL.AdicionaVariavelIn("erro_s");
    RTL.AdicionaVariavelIn("fim_cont");
    RTL.AdicionaVariavelIn("RST");

    RTL.AdicionaVariavelOut("enable_1");
    RTL.AdicionaVariavelOut("enable_2");
    RTL.AdicionaVariavelOut("enable_3");
    RTL.AdicionaVariavelOut("enable_4");
    RTL.AdicionaVariavelOut("atv_cron");
    RTL.AdicionaVariavelOut("show_wait");
    RTL.AdicionaVariavelOut("es_des");
    RTL.AdicionaVariavelOut("clk_des");
    RTL.AdicionaVariavelOut("RST_OP");
    RTL.AdicionaVariavelOut("clk_des_luzProg");
    RTL.AdicionaVariavelOut("RST_luzProg");
    RTL.AdicionaVariavelOut("mostra_erro");
    RTL.AdicionaVariavelOut("luz_pronto");

    RTL.AdicionaEstado("inicial", 0b0000, {"enable_1=0", "enable_2=0", "enable_3=0", "enable_4=0",
                                           "atv_cron=0", "show_wait=1", "es_des=0", "clk_des=0", "RST_OP=1",
                                           "luz_pronto=0", "clk_des_luzProg=0", "RST_luzProg=1", "mostra_erro=0"});

    RTL.AdicionaEstado("prepara", 0b0001, {"enable_1=0", "enable_2=0", "enable_3=0", "enable_4=0",
                                           "atv_cron=0", "show_wait=1", "es_des=1", "clk_des=1", "RST_OP=0",
                                           "luz_pronto=0", "clk_des_luzProg=0", "RST_luzProg=0", "mostra_erro=0"});

    RTL.AdicionaEstado("espera_init", 0b0010, {"enable_1=0", "enable_2=0", "enable_3=0", "enable_4=0",
                                           "atv_cron=0", "show_wait=1", "es_des=0", "clk_des=0", "RST_OP=0",
                                           "luz_pronto=0", "clk_des_luzProg=0", "RST_luzProg=0", "mostra_erro=0"});

    RTL.AdicionaEstado("grava_seq", 0b0011, {"enable_1=0", "enable_2=0", "enable_3=0", "enable_4=0",
                                           "atv_cron=0", "show_wait=1", "es_des=0", "clk_des=1", "RST_OP=0",
                                           "luz_pronto=0", "clk_des_luzProg=1", "RST_luzProg=0", "mostra_erro=0"});


    RTL.AdicionaEstado("espera_btt", 0b0100, {"enable_1=0", "enable_2=0", "enable_3=0", "enable_4=0",
                                           "atv_cron=0", "show_wait=1", "es_des=0", "clk_des=0", "RST_OP=0",
                                           "luz_pronto=0", "clk_des_luzProg=0", "RST_luzProg=0", "mostra_erro=0"});

    RTL.AdicionaEstado("espera", 0b0101, {"enable_1=0", "enable_2=0", "enable_3=0", "enable_4=0",
                                           "atv_cron=0", "show_wait=1", "es_des=0", "clk_des=0", "RST_OP=0",
                                           "luz_pronto=0", "clk_des_luzProg=0", "RST_luzProg=1", "mostra_erro=0"});

    RTL.AdicionaEstado("mostra_seq", 0b0110, {"enable_1=1", "enable_2=1", "enable_3=0", "enable_4=0",
                                           "atv_cron=0", "show_wait=1", "es_des=0", "clk_des=0", "RST_OP=0",
                                           "luz_pronto=0", "clk_des_luzProg=0", "RST_luzProg=0", "mostra_erro=0"});

    RTL.AdicionaEstado("bt1", 0b0111, {"enable_1=0", "enable_2=0", "enable_3=1", "enable_4=0",
                                           "atv_cron=0", "show_wait=1", "es_des=0", "clk_des=0", "RST_OP=0",
                                           "luz_pronto=1", "clk_des_luzProg=0", "RST_luzProg=0", "mostra_erro=0"});

    RTL.AdicionaEstado("botao", 0b1000, {"enable_1=0", "enable_2=0", "enable_3=1", "enable_4=0",
                                           "atv_cron=1", "show_wait=0", "es_des=0", "clk_des=0", "RST_OP=0",
                                           "luz_pronto=0", "clk_des_luzProg=0", "RST_luzProg=0", "mostra_erro=0"});

    RTL.AdicionaEstado("compTecla", 0b1001, {"enable_1=0", "enable_2=0", "enable_3=1", "enable_4=1",
                                           "atv_cron=1", "show_wait=0", "es_des=0", "clk_des=0", "RST_OP=0",
                                           "luz_pronto=0", "clk_des_luzProg=1", "RST_luzProg=0", "mostra_erro=0"});

    RTL.AdicionaEstado("erro", 0b1010, {"enable_1=0", "enable_2=0", "enable_3=0", "enable_4=0",
                                           "atv_cron=0", "show_wait=0", "es_des=0", "clk_des=0", "RST_OP=0",
                                           "luz_pronto=0", "clk_des_luzProg=0", "RST_luzProg=0", "mostra_erro=1"});

    RTL.AdicionaEstado("mostra_tela", 0b1011, {"enable_1=0", "enable_2=0", "enable_3=0", "enable_4=0",
                                           "atv_cron=0", "show_wait=0", "es_des=0", "clk_des=0", "RST_OP=0",
                                           "luz_pronto=0", "clk_des_luzProg=0", "RST_luzProg=0", "mostra_erro=0"});


    RTL.Liga("inicial", "prepara", "");
    RTL.Liga("prepara", "espera_init", "");
    RTL.Liga("espera_init", "espera_init", "!RST");
    RTL.Liga("espera_init", "espera_btt", "RST");
    RTL.Liga("espera_btt", "espera_btt", "!btt_press!cont_1_igual5");
    RTL.Liga("espera_btt", "grava_seq", "btt_press!cont_1_igual5");
    RTL.Liga("espera_btt", "espera", "cont_1_igual5");
    RTL.Liga("grava_seq", "grava_seq", "btt_press");
    RTL.Liga("grava_seq", "espera_btt", "!btt_press");
    RTL.Liga("espera", "espera", "!RST");
    RTL.Liga("espera", "mostra_seq", "RST");
    RTL.Liga("mostra_seq", "mostra_seq", "!fim_cont");
    RTL.Liga("mostra_seq", "bt1", "fim_cont");
    RTL.Liga("bt1", "bt1", "!btt_press");
    RTL.Liga("bt1", "compTecla", "btt_press");
    RTL.Liga("compTecla", "compTecla", "!btt_presserro_s");
    RTL.Liga("compTecla", "erro", "!erro_sbtt_press");
    RTL.Liga("compTecla", "botao", "!btt_press");
    RTL.Liga("botao", "botao", "!btt_press!cont_2_igual5");
    RTL.Liga("botao", "compTecla", "btt_press!cont_2_igual5");
    RTL.Liga("botao", "mostra_tela", "cont_2_igual5");
    RTL.Liga("erro", "erro", "!RST");
    RTL.Liga("erro", "inicial", "RST");
    RTL.Liga("mostra_tela", "mostra_tela", "!RST");
    RTL.Liga("mostra_tela", "inicial", "RST");

    RTL.Possibilidades(cout);
    ofstream salva("truth_table.txt");
    RTL.Possibilidades(salva);
    salva.close();
}
