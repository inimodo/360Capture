#pragma once
#include<twogd.h>



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