
#include "ds18b20.h"

#include "cmsis_os2.h"

uint8_t DS18B20_Read_Byte(void)
{
        uint8_t i=0,dat=0;

        for (i=0;i<8;i++)
        {
        DQ_OUT();//����Ϊ����ģʽ
        DQ(0); //����
        delay_us(2);
        DQ(1); //�ͷ�����
        DQ_IN();//����Ϊ����ģʽ
        delay_us(12);
        dat>>=1;
        if( DQ_GET() )
        {
            dat=dat|0x80;
        }
        delay_us(50);
     }
        return dat;
}
void DS18B20_Write_Byte(uint8_t dat)
{
        uint8_t i;
        DQ_OUT();//�������ģʽ
        for (i=0;i<8;i++)
        {
                if ( (dat&0x01) ) //д1
                {
                        DQ(0);
                        delay_us(2);
                        DQ(1);
                        delay_us(60);
                }
                else //д0
                {
                        DQ(0);//����60us
                        delay_us(60);
                        DQ(1);//�ͷ�����
                        delay_us(2);
                }
                dat=dat>>1;//������һλ
        }
}
uint8_t DS18B20_Check(void)
{
        uint8_t timeout=0;
        //��λDS18B20
        DQ_OUT(); //����Ϊ���ģʽ
        DQ(1);
        delay_us(15);
        DQ(0); //����DQ
        delay_us(740); //����750us
        DQ(1); //����DQ
        delay_us(20);  //15us
    //����Ϊ����ģʽ
        DQ_IN();
    //�ȴ����ͣ�����˵����Ӧ��
        while ( DQ_GET() &&timeout<240)
        {
                timeout++;//��ʱ�ж�
                delay_us(1);
        }
        //�豸δӦ��
        if(timeout>=240)
                return 1;
        timeout=0;
        //�ȴ�18B20�ͷ�����
        while ( !DQ_GET() &&timeout<240)
        {
                timeout++;//��ʱ�ж�
                delay_us(1);
        };
    //�ͷ�����ʧ��
        if(timeout>=240)
                return 1;
        return 0;
}
void DS18B20_Start(void)
{
        DS18B20_Check();                //��ѯ�Ƿ����豸Ӧ��
        DS18B20_Write_Byte(0xcc);   //�������������豸����Ѱַ
        DS18B20_Write_Byte(0x44);   //�����¶�ת��
}
float DS18B20_GetTemperture(void)
{
        uint16_t temp;
        uint8_t dataL=0,dataH=0;
        float value;
        DS18B20_Start();
        osDelay(750);
        DS18B20_Check();
        DS18B20_Write_Byte(0xcc);//�������������豸����Ѱַ
        DS18B20_Write_Byte(0xbe);// ��ȡ��������
        dataL=DS18B20_Read_Byte(); //LSB
        dataH=DS18B20_Read_Byte(); //MSB
        temp=(dataH<<8)+dataL;//��������
        if(dataH&0X80)//��λΪ1��˵���Ǹ��¶�
        {
                temp=(~temp)+1;
                value=temp*(-0.0625);
        }
        else
        {
                value=temp*0.0625;
        }
        return value;
}