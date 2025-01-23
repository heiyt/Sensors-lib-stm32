/**
* ************************************************************************
 *
 * @file algorithm.h
 * @author zxr
 * @brief
 *
 * ************************************************************************
 * @copyright Copyright (c) 2024 zxr
 * ************************************************************************
 */
#ifndef __ALGORITHM_H
#define __ALGORITHM_H

#define FFT_N 			1024    //���帵��Ҷ�任�ĵ���
#define START_INDEX 	8  		//��Ƶ������ֵ

struct compx     	//����һ�������ṹ
{
    float real;
    float imag;
};

typedef struct		//����һ��ֱ���˲����ṹ��
{
    float w;
    int init;
    float a;
}DC_FilterData;		//���ڴ洢ֱ���˲����Ĳ���


typedef struct		//����һ�������˲����ṹ��
{
    float v0;
    float v1;
}BW_FilterData;		//���ڴ洢�����˲����Ĳ���



double my_floor(double x);

double my_fmod(double x, double y);

double XSin( double x );

double XCos( double x );

int qsqrt(int a);


struct compx EE(struct compx a,struct compx b);

void FFT(struct compx *xin);

int find_max_num_index(struct compx *data,int count);
int dc_filter(int input,DC_FilterData * df);
int bw_filter(int input,BW_FilterData * bw);


#endif


