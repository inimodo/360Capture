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


void triangle::SetSides(int i_Point) 
{

	w_Sides[0] = w_Public[i_Point][0];
	w_Sides[1] = w_Public[(i_Point + 1)%4][0];
	w_Sides[2] = w_Public[i_Point][1];


}
void triangle::GetPoints(int i_Point,GDVEC3 o_Origin)
{

	float R= (float)w_Sides[0], r= (float)w_Sides[1], d = (float)w_Sides[2];
	float x = (d*d - r * r + R * R) / (2 * d);
	float a = (sqrtf(  (-d+r-R)*(-d-r+R)*(-d+r+R)*(d+r+R) )/d)/2;
	this->o_Point[0] = GDVEC3(o_Origin.f_Pos[0],0, o_Origin.f_Pos[2]);
	switch (i_Point)
	{
	case 0:
		this->o_Point[1] = GDVEC3(o_Origin.f_Pos[0]+x, 0, o_Origin.f_Pos[2]+a);
		this->o_Point[2] = GDVEC3(o_Origin.f_Pos[0]+d, 0, o_Origin.f_Pos[2]);
		break;
	case 1:
		this->o_Point[1] = GDVEC3(o_Origin.f_Pos[0] + a, 0, o_Origin.f_Pos[2] -x);
		this->o_Point[2] = GDVEC3(o_Origin.f_Pos[0] , 0, o_Origin.f_Pos[2]-d);
		break;
	case 2:
		this->o_Point[1] = GDVEC3(o_Origin.f_Pos[0] -x , 0, o_Origin.f_Pos[2] - a);
		this->o_Point[2] = GDVEC3(o_Origin.f_Pos[0]-d, 0, o_Origin.f_Pos[2] );
		break;
	case 3:
		this->o_Point[1] = GDVEC3(o_Origin.f_Pos[0] - a, 0, o_Origin.f_Pos[2] + x);
		this->o_Point[2] = GDVEC3(o_Origin.f_Pos[0], 0, o_Origin.f_Pos[2]+d);
		break;
	}
}
