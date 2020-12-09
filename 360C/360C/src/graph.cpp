#include"main.h"

void graphing::Prepare(int i_Width, int i_Height,int i_Offset,WORD w_Max)
{
	this->o_Graph.Prepare(i_Width,i_Height);
	this->o_Codec = GD2DCODEC(&o_Graph);
	this->i_LineOffset = i_Offset;
	this->w_Max = w_Max;
}

void graphing::DisplayData(WORD*i_pValue, int i_Values)
{
	this->o_Graph.CleanBuffer();
	GDVEC2 o_PointOne= GDVEC2(0, this->o_Graph.i_Pixels[1] - this->i_LineOffset),o_PointTwo;
	this->o_Codec.DrawHLine(&o_PointOne, this->o_Graph.i_Pixels[0],this->o_Lines);
	o_PointOne = GDVEC2(this->i_LineOffset, 0);
	this->o_Codec.DrawVLine(&o_PointOne, this->o_Graph.i_Pixels[1],this->o_Lines);


	float f_X = this->i_LineOffset;
	float f_Y = ((float)i_pValue[0] / (float)w_Max)*(float)(this->o_Graph.i_Pixels[1] - this->i_LineOffset) ;
	o_PointOne = GDVEC2(f_X, f_Y);

	for (int i_Index = 1; i_Index < i_Values; i_Index++)
	{
		f_X = ((float)i_Index/(float)i_Values)*(float)(this->o_Graph.i_Pixels[0] - this->i_LineOffset)+ this->i_LineOffset;
		f_Y = ((float)i_pValue[i_Index]/ (float)w_Max)*(float)(this->o_Graph.i_Pixels[1] - this->i_LineOffset) ;

		o_PointTwo = GDVEC2(f_X,f_Y);
		this->o_Codec.DrawLine(&o_PointOne,&o_PointTwo,this->o_Values);
		o_PointOne = o_PointTwo;

	}
}