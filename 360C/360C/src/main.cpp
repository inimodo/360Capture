#include"main.h"

GDCONSOLE gd_Console;
GD2DCODEC gd_Codec;
GDCANVAS gd_Img;
GD3DCODEC gd_World;

GFOBJECT gd_Plane;
GFOBJECT gd_ReciverObject;

GDCAMERA gd_camera;

GDVEC3 gd_PointOne;
GDVEC3 gd_PointTwo;


GDVEC3 gd_Reciver[4];

GDCOLOR gd_GraphValues(80,230,0);
GDCOLOR gd_GraphLine(255,255,255);
GDCOLOR gd_GraphXColor(255, 0, 0);
GDCOLOR gd_GraphYColor(0, 255, 0);
GDCOLOR gd_GraphZColor(0, 0, 255);
GDCOLOR gd_PlaneColor(60, 60, 60);
GDCOLOR gd_ReciverColor(200, 120, 80);

GDVEC2 o_Drawpos(0,0);

GRAPH g_GraphSenderOne;

WORD w_MaxDistance = 1000; //SETTING
WORD w_Datastream[M_DATABUFFER][4];

HANDLE hwd_usb;

TRIFORM o_Form[4];
WORD triangle::w_Public[4][4];

void setup()
{
	for (INT i_Index = 0; i_Index < 4; i_Index++) {
		o_Form[i_Index].SetSides(i_Index);
	}

	o_Form[0].GetPoints(0, GDVEC3(0, 0, 0));
	o_Form[1].GetPoints(1, o_Form[0].o_Point[1]);
	o_Form[2].GetPoints(2, o_Form[1].o_Point[1]);
	o_Form[3].GetPoints(3, o_Form[2].o_Point[1]);

	GDVEC3 gd_AvrCenter;
	for (INT i_Index = 0; i_Index < 4; i_Index++)
	{
		gd_Reciver[i_Index] = GDVEC3(M_TICKTOM(o_Form[i_Index].o_Point[1].f_Pos[0]), 0, M_TICKTOM(o_Form[i_Index].o_Point[1].f_Pos[2]));
		gd_AvrCenter = gd_AvrCenter + gd_Reciver[i_Index];
	}

	gd_AvrCenter = GDVEC3(gd_AvrCenter.f_Pos[0] * (1.0f / 4.0f), 0, gd_AvrCenter.f_Pos[2] * (1.0f / 4.0f));

	for (INT i_Index = 0; i_Index < 4; i_Index++)
	{
		gd_Reciver[i_Index] = gd_Reciver[i_Index] - gd_AvrCenter;
	}
}


unsigned char __WAY gdmain(win::GDWIN * gd_win)
{
	gd_win->i_Width = 16 * 80;
	gd_win->i_Height = 9 * 80;

	gd_camera.i_Dimensions[0] = gd_win->i_Width;
	gd_camera.i_Dimensions[1] = gd_win->i_Height;//1 11
	gd_camera.i_Frustum[0] = 1;
	gd_camera.i_Frustum[1] = 30;
	gd_camera.i_Position.f_Pos[1] = 2.5;//2
	gd_camera.i_Position.f_Pos[2] = 15;//16


	gd_Console.Create();
	gd_Img.Prepare(gd_win->i_Width, gd_win->i_Height);
	gd_Codec = GD2DCODEC(&gd_Img);
	gd_World = GD3DCODEC(&gd_Img, &gd_camera);

	g_GraphSenderOne.Prepare(M_GRAPH_WIDTH,M_GRAPH_HEIGHT,M_GRAPH_OFFSET,w_MaxDistance);
	g_GraphSenderOne.o_Values = &gd_GraphValues ;
	g_GraphSenderOne.o_Lines= &gd_GraphLine;


	printf("Load: files\\plane.obj Loading Resultet in %X \n", gd_Plane.Read((const LPSTR)"files\\plane.obj"));
	printf("Load: files\\reciver.obj Loading Resultet in %X \n\n", gd_ReciverObject.Read((const LPSTR)"files\\reciver.obj"));


	TRIFORM::w_Public[0][0] = 35 * 400;
	TRIFORM::w_Public[0][1] = 40 * 400;
	TRIFORM::w_Public[0][2] = 30 * 400;
	TRIFORM::w_Public[1][0] = 20 * 400;
	TRIFORM::w_Public[1][1] = 50 * 400;
	TRIFORM::w_Public[1][2] = 35 * 400;
	TRIFORM::w_Public[2][0] = 40 * 400;
	TRIFORM::w_Public[2][1] = 40 * 400;
	TRIFORM::w_Public[2][2] = 20 * 400;
	TRIFORM::w_Public[3][0] = 30 * 400;
	TRIFORM::w_Public[3][1] = 50 * 400;
	TRIFORM::w_Public[3][2] = 40 * 400;

	hwd_usb = CreateThread(0, 0, usbprocess, 0, 0, NULL);

	setup();
	return TRUE;
}


unsigned char __WAY gdupdate(win::GDWIN * gd_win)
{
	//auto a_TimeA = std::chrono::high_resolution_clock::now();
	gd_Img.CleanBuffer();




	gd_World.DrawObject(&gd_Plane, &gd_PlaneColor);
	for (INT i_Index = 0; i_Index < 4; i_Index++)
	{
		gd_ReciverObject.p_Anchor = gd_Reciver[i_Index];
		gd_World.DrawObject(&gd_ReciverObject, &gd_ReciverColor);
		gd_World.DrawEdge(&gd_Reciver[i_Index], &gd_Reciver[(i_Index + 1)%4], &gd_ReciverColor);
	}


	o_Drawpos = GDVEC2(M_GRAPH_OFFSET, M_GRAPH_OFFSET);
	g_GraphSenderOne.DisplayData(w_Datastream[0], M_DATABUFFER);
	gd_Codec.DrawCanvas(g_GraphSenderOne.o_Graph.d_pOutputStream,&o_Drawpos, g_GraphSenderOne.o_Graph.i_Pixels);
	g_GraphSenderOne.DisplayData(w_Datastream[1], M_DATABUFFER);
	o_Drawpos = GDVEC2(M_GRAPH_WIDTH+ M_GRAPH_OFFSET*2, M_GRAPH_OFFSET);
	gd_Codec.DrawCanvas(g_GraphSenderOne.o_Graph.d_pOutputStream,&o_Drawpos, g_GraphSenderOne.o_Graph.i_Pixels);
	g_GraphSenderOne.DisplayData(w_Datastream[2], M_DATABUFFER);
	o_Drawpos = GDVEC2(M_GRAPH_OFFSET, M_GRAPH_HEIGHT+ M_GRAPH_OFFSET);
	gd_Codec.DrawCanvas(g_GraphSenderOne.o_Graph.d_pOutputStream,&o_Drawpos, g_GraphSenderOne.o_Graph.i_Pixels);
	g_GraphSenderOne.DisplayData(w_Datastream[3], M_DATABUFFER);
	o_Drawpos = GDVEC2(M_GRAPH_WIDTH+ M_GRAPH_OFFSET*2, M_GRAPH_HEIGHT+ M_GRAPH_OFFSET);
	gd_Codec.DrawCanvas(g_GraphSenderOne.o_Graph.d_pOutputStream,&o_Drawpos, g_GraphSenderOne.o_Graph.i_Pixels);


	gd_PointOne = GDVEC3(5, 0, -5);
	gd_PointTwo = GDVEC3(5, 0, 1) ;
	gd_World.DrawEdge(&gd_PointOne, &gd_PointTwo, &gd_GraphXColor);
	gd_PointTwo = GDVEC3(5, 4, -5);
	gd_World.DrawEdge(&gd_PointOne, &gd_PointTwo, &gd_GraphYColor);
	gd_PointTwo = GDVEC3(1, 0, -5);
	gd_World.DrawEdge(&gd_PointOne, &gd_PointTwo, &gd_GraphZColor);


	SetScreenBuffer(gd_Img.d_pOutputStream, gd_win->i_Width, gd_win->i_Height);

	//auto a_TimeB = std::chrono::high_resolution_clock::now();
	//auto a_Time = std::chrono::duration_cast<std::chrono::milliseconds>(a_TimeB - a_TimeA).count();
	//system("cls");
	//printf("%dms \n", a_Time);

	return TRUE;
}

void __WAY gdclose() 
{
	gd_Img.Dispose();
	CloseHandle(hwd_usb);
}

