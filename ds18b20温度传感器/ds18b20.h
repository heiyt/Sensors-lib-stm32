/*
* ������������Ӳ�������������չ����Ӳ�����Ϲ���ȫ����Դ
 * �����������www.lckfb.com
 * ����֧�ֳ�פ��̳���κμ������⻶ӭ��ʱ����ѧϰ
 * ������̳��https://oshwhub.com/forum
 * ��עbilibili�˺ţ������������塿���������ǵ����¶�̬��
 * ��������׬Ǯ���������й�����ʦΪ����
 * Change Logs:
 * Date           Author       Notes
 * 2024-03-29     LCKFB-LP    first version
 */
#ifndef _BSP_DS18B20_H_
#define _BSP_DS18B20_H_

#include "stm32f1xx.h"
#include "gpio.h"

//�˿���ֲ
#define PORT_DQ         DQ_GPIO_Port
#define GPIO_DQ         DQ_Pin

//����DQ���ģʽ
#define DQ_OUT()  {\
GPIO_InitTypeDef  GPIO_InitStructure;\
GPIO_InitStructure.Pin = GPIO_DQ;\
GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;\
GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;\
HAL_GPIO_Init(PORT_DQ, &GPIO_InitStructure);\
}
//����DQ����ģʽ
#define DQ_IN()   {\
GPIO_InitTypeDef  GPIO_InitStructure;\
GPIO_InitStructure.Pin = GPIO_DQ;\
GPIO_InitStructure.Mode = GPIO_MODE_INPUT;\
HAL_GPIO_Init(PORT_DQ, &GPIO_InitStructure);\
}
//��ȡDQ���ŵĵ�ƽ�仯
#define DQ_GET()        HAL_GPIO_ReadPin(PORT_DQ, GPIO_DQ)
//DQ���
#define DQ(x)           HAL_GPIO_WritePin(PORT_DQ, GPIO_DQ, (x?GPIO_PIN_SET:GPIO_PIN_RESET))

void DS18B20_Reset(void);
uint8_t DS18B20_Check(void);
void DS18B20_Start(void);
float DS18B20_GetTemperture(void);

#endif