#include"main.h"

GDCONSOLE gd_Console;
GD2DCODEC gd_Codec;
GDCANVAS gd_Img;

#define M_GRAPH_WIDTH 230
#define M_GRAPH_HEIGHT 120
#define M_GRAPH_OFFSET 10

GDCOLOR gd_GraphLine(255,255,255);
GDCOLOR gd_GraphValues(255,0,255);

GDVEC2 o_Drawpos(0,0);

GRAPH g_GraphSenderOne;

WORD w_MaxDistance = 1000; //SETTING
#define TESTWORDSIZE 100
WORD w_Testword[TESTWORDSIZE];

unsigned char __WAY gdmain(win::GDWIN * gd_win)
{
	gd_win->i_Width = 16 * 70;
	gd_win->i_Height = 9 * 70;

	gd_Console.Create();
	gd_Img.Prepare(gd_win->i_Width, gd_win->i_Height);
	gd_Codec = GD2DCODEC(&gd_Img);


	g_GraphSenderOne.Prepare(M_GRAPH_WIDTH,M_GRAPH_HEIGHT,M_GRAPH_OFFSET,w_MaxDistance);
	g_GraphSenderOne.o_Values = &gd_GraphValues ;
	g_GraphSenderOne.o_Lines= &gd_GraphLine;

	for (INT i_Index = 0; i_Index < TESTWORDSIZE; i_Index++)
	{
		w_Testword[i_Index] = rand()%w_MaxDistance;

	}

	system("pause");


	return TRUE;
}



unsigned char __WAY gdupdate(win::GDWIN * gd_win)
{
	gd_Img.CleanBuffer();


	g_GraphSenderOne.DisplayData(w_Testword, TESTWORDSIZE);
	gd_Codec.DrawCanvas(g_GraphSenderOne.o_Graph.d_pOutputStream,&o_Drawpos, g_GraphSenderOne.o_Graph.i_Pixels);

	SetScreenBuffer(gd_Img.d_pOutputStream, gd_win->i_Width, gd_win->i_Height);
	system("pause");
	system("cls");
	return TRUE;
}

void __WAY gdclose() 
{
	gd_Img.Dispose();
}

