#include"main.h"

#define M_COM "\\\\.\\COM4"

#define M_COM_DATABUFFER 64
DWORD __WAY usbprocess(LPVOID lp_Void)
{
	HANDLE hwd_COM;
	DCB o_COMInfo;

	CHAR c_pDataBuffer[M_COM_DATABUFFER][4];
	CHAR c_pComBuffer[M_COM_DATABUFFER];
	CHAR c_Temp;
	DWORD dw_Bytes;

	hwd_COM = CreateFile(M_COM,GENERIC_READ| GENERIC_WRITE,0,NULL,OPEN_EXISTING,0,NULL);
	o_COMInfo.BaudRate = CBR_57600;
	o_COMInfo.ByteSize = 8;
	o_COMInfo.StopBits = ONESTOPBIT;
	o_COMInfo.Parity = NOPARITY;
	SetCommState(hwd_COM,&o_COMInfo);

	if (hwd_COM == INVALID_HANDLE_VALUE) printf("USB: Unable open connection to port %s", M_COM);
	else {
		printf("USB: Connection to port %s was succsessful!", M_COM);
		int i_Index = 0;
		while (1)
		{
			ReadFile(hwd_COM,&c_Temp,sizeof(CHAR), &dw_Bytes,NULL);
			if (c_Temp == '(') 
			{
				i_Index = 0;
			}
			c_pComBuffer[i_Index] = c_Temp;

			if (c_Temp == ')')
			{
				for (INT i_BufferIndex = 0,i_NodeIndex=0,i_CharSize=0; c_pComBuffer[i_BufferIndex]!=')'; i_BufferIndex++)
				{
					if (c_pComBuffer[i_BufferIndex] == '#') 
					{
						i_BufferIndex++;
						if (i_NodeIndex >= 4 || i_BufferIndex >= M_COM_DATABUFFER)break;
						for (INT i_DataBuffer = 0; c_pComBuffer[i_BufferIndex+ i_DataBuffer] != ')'&&c_pComBuffer[i_BufferIndex+ i_DataBuffer] != '#'; i_DataBuffer++)
						{
							c_pDataBuffer[i_NodeIndex][i_DataBuffer] = c_pComBuffer[i_BufferIndex + i_DataBuffer];
							i_CharSize++;
						}
						c_pDataBuffer[i_NodeIndex][i_CharSize] = '\0';

						i_NodeIndex++;
					}
				}
				for (INT i_StreamIndex = 0; i_StreamIndex < 4; i_StreamIndex++)
				{
					for (INT i_ValueIndex = 0; i_ValueIndex < M_DATABUFFER-1; i_ValueIndex++)
					{
						w_Datastream[i_StreamIndex][i_ValueIndex] = w_Datastream[i_StreamIndex][i_ValueIndex + 1];
					}
					w_Datastream[i_StreamIndex][M_DATABUFFER - 1] = atoi(c_pDataBuffer[i_StreamIndex]);

				}

			}
			i_Index++;

		}
	}
	return 0;
}



DWORD __WAY inputprocess(LPVOID lp_Void)
{
	while (1)
	{
		if (GetAsyncKeyState(VK_SPACE) != 0) {
			c_Sellection++;
			c_Sellection = c_Sellection % (4- c_Mode);

			while (GetAsyncKeyState(VK_SPACE) != 0) {}
		}

		if (GetAsyncKeyState(VK_RETURN) != 0) {
			float f_Setting[4] = {0,0,0,0};
			for (INT i_Stream = 0; i_Stream < 4; i_Stream++)
			{
				for (INT i_Value = 0; i_Value < M_DATABUFFER; i_Value++)
				{
					f_Setting[i_Stream] += w_Datastream[i_Stream][i_Value];
				}

			}
			for (INT i_Stream = 0; i_Stream < M_DATABUFFER; i_Stream++) f_Setting[i_Stream] /= M_DATABUFFER;

			TRIFORM::w_Public[c_Sellection][0] = f_Setting[(c_Sellection + 1) % 3];
			TRIFORM::w_Public[c_Sellection][1] = f_Setting[(c_Sellection + 2) % 3];
			TRIFORM::w_Public[c_Sellection][2] = f_Setting[(c_Sellection + 3) % 3];

			while (GetAsyncKeyState(VK_RETURN) != 0) {}
		}
		Sleep(10);
	}
	return 0;
}