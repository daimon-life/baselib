#include <cmath>
#include <cstdlib>

#define AUDIO_DB(vol_nornalized) (20 * log10(vol_nornalized) )

// 取值在 0 ~ 20log(32767)
static double AudioGetDecibel(short* lpData, int nSampleNum, double & dbLeft, double & dbRight) 
{
	if (nSampleNum <= 0) 
	{
		dbLeft = 0.0;
		dbRight = 0.0;

		return 0.0;
	}
	for (int k = 0; k < nSampleNum; k++) 
	{
		int nleft = lpData[0];
		int nRight = lpData[1];

		dbLeft += (int)abs((int)nleft);
		dbRight += (int)abs((int)nRight);
		lpData = lpData + 2;
	}
	if (dbLeft) 
	{
		double temp = dbLeft / nSampleNum;
		temp = temp < 1 ? 1 : temp;

		dbLeft = AUDIO_DB(temp);
	}

	if (dbRight) 
	{
		double temp = dbRight / nSampleNum;
		temp = temp < 1 ? 1 : temp;

		dbRight = AUDIO_DB(temp);
	}

	return (dbLeft + dbRight) / 2;
}

// 混音
static void MixAudioS16(char* pSrcData, char* pSubData, int nBytes)
{
    short *data1 = (short*)pSrcData;
    short *data2 = (short*)pSubData;
    int samples = nBytes / 2;

    for (int i = 0; i < samples; i++) 
    {
        int s1 = int(*data1);
        int s2 = int(*data2);
        int v = s1 + s2;

        if (v > 32767) 
	{
            v = 32767;
        } 
	else if (v < -32768) 
	{
            v = -32768;
        }

        *data1 = (short)v;

        data1++;
        data2++;
    }
}
