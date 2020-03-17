// pascal's triangle mod p.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
//

#include <stdio.h>
#include <math.h>
#include <malloc.h>
#define PI 3.141592653589793238462643383
unsigned char phase2color(double phase)
{
	int result = (cos(phase) + 1) * 128;
	if (result > 255)return 255;
	else return (unsigned char)result;
}
int main()
{
	FILE *fp;
	fopen_s(&fp, "result.bmp", "wb");
	if (fp == NULL)
	{
		puts("file opening failed");
		return 1;
	}
	unsigned int p, g, size;
	puts("prime, primitive root, size?");
	scanf_s("%u %u %u", &p, &g, &size);
	unsigned char *color = (unsigned char *)malloc(sizeof(unsigned char) * 3 * p);
	unsigned char *pixel = (unsigned char *)calloc(size + 1, sizeof(unsigned char));
	pixel[0] = 1;
	if (g == 0)
	{
		if (p == 2)g = 1;
		else
		{
			int x = (p - 1) / 2;
			int t = (p - 1) / 2;
			while (x & 1 == 0)x >>= 1;
			*color = 2;
			unsigned char *ptr = color + 1;
			bool isfirst = true;
			for (unsigned char j = 3; x > 1;)
			{
				if (x % j == 0)
				{
					if (isfirst)
					{
						t /= j;
						*ptr = j;
						++ptr;
						isfirst = false;
					}
					x /= j;
				}
				else
				{
					j += 2;
					isfirst = true;
				}
			}
			x = ptr - color;//���μ� ����
			*color = 0;
			for (;;)
			{
				
			}
		}
	}
	color[0] = color[1] = color[2] = 0;
	unsigned int t = 1;
	double x;
	for (unsigned int i = 0; i != p - 1; ++i)
	{
		for (unsigned char j = 0; j != 3; ++j)color[3 * t + j] = phase2color(((double)i / (p - 1) + (double)j / 3)* 2 * PI);
		t = (t * g) % p;
	}
	int w = 2 * size, h = size * sqrt(3);
	unsigned char bmpfileheader[14] = { 'B','M', 0,0,0,0, 0,0, 0,0, 54,0,0,0 };
	unsigned char bmpinfoheader[40] = { 40,0,0,0, 0,0,0,0, 0,0,0,0, 1,0, 24,0 };
	unsigned char bmppad[3] = { 0,0,0 };
	*(int *)(bmpfileheader + 2) = 54 + 3 * w*h;//filesize
	*(int *)(bmpinfoheader + 4) = w;//width
	*(int *)(bmpinfoheader + 8) = h;//height
	_fwrite_nolock(bmpfileheader, 1, 14, fp);
	_fwrite_nolock(bmpinfoheader, 1, 40, fp);
	size_t k = (4 - (w * 3) % 4) % 4;
	unsigned int nextskip = 0, numskip = 0;
	for (unsigned int i = 0; i < size; ++i)
	{
		if (i != nextskip)
		{
			for (unsigned int j = 0; j != size - i - 1; ++j)
				_fwrite_nolock(color, 3, 1, fp);
			for (unsigned int j = 0; j < i + 1; ++j)
			{
				_fwrite_nolock(color + 3 * pixel[j], 3, 1, fp);
				_fwrite_nolock(color + 3 * pixel[j], 3, 1, fp);
			}
			for (unsigned int j = 0; j != size - i - 1; ++j)
				_fwrite_nolock(color, 3, 1, fp);
			_fwrite_nolock(bmppad, 1, k, fp);
		}
		else
		{
			++numskip;
			nextskip = (2 + sqrt(3)) * numskip;
		}
		unsigned char temp = 0, temp2;
		for (unsigned int j = 0; j != size - i - 1; ++j)
			_fwrite_nolock(color, 3, 1, fp);
		for (unsigned int j = 0; j < i + 1; ++j)
		{
			temp2 = pixel[j];
			pixel[j] += temp;
			pixel[j] %= p;
			temp = temp2;
			_fwrite_nolock(color + 3 * temp, 3, 1, fp);
			_fwrite_nolock(color + 3 * temp, 3, 1, fp);
		}
		pixel[i + 1] = temp;
		for (unsigned int j = 0; j != size - i - 1; ++j)
			_fwrite_nolock(color, 3, 1, fp);
		_fwrite_nolock(bmppad, 1, k, fp);
	}
	_fclose_nolock(fp);
	free(color);
	free(pixel);
    return 0;
}
