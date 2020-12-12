#pragma once
#include<twogd.h>
#include <chrono>


#define M_GRAPH_WIDTH 260
#define M_GRAPH_HEIGHT 100
#define M_GRAPH_OFFSET 10

#define M_NET_SIZE 5

#define M_DATABUFFER 100

#define M_TICKTOM(X) (((float)X*(1.0f/1000000.0f))*343.0f)

#define M_MODE_TRIANGLE 0x1
#define M_MODE_SQUARE 0x0

typedef class graphing 
{
private:
	GD2DCODEC o_Codec;
public:
	GDCANVAS o_Graph;
	GDCOLOR * o_Lines,* o_Values;
	int i_LineOffset;
	WORD w_Max;
	void Prepare(int i_Width,int i_Height,int i_Offset,WORD w_Max);
	void DisplayData(WORD*i_pValue,int i_Values);

} GRAPH;

typedef class triangle {
public:
	static WORD w_Public[4][4];

	WORD w_Sides[3];
	GDVEC3 o_Point[3];
	void SetSides(int i_Point);
	void GetPoints(int i_Point,GDVEC3 gd_Origin);
}TRIFORM;


extern WORD w_Datastream[M_DATABUFFER][4];
extern CHAR c_Sellection,c_Mode;


DWORD __WAY usbprocess(LPVOID lp_Void);
DWORD __WAY inputprocess(LPVOID lp_Void);
