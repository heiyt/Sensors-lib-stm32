/**
 * ************************************************************************
 *
 * @file MAX30102.c
 * @author zxr
 * @brief
 *
 * ************************************************************************
 * @copyright Copyright (c) 2024 zxr
 * ************************************************************************
 */
#include "max30102.h"

uint16_t fifo_red;  //����FIFO�еĺ������
uint16_t fifo_ir;   //����FIFO�еĺ��������

/**
 * ************************************************************************
 * @brief ��MAX30102�Ĵ���д��һ��ֵ
 *
 * @param[in] addr  �Ĵ�����ַ
 * @param[in] data  ��������
 *
 * @return
 * ************************************************************************
 */
uint8_t max30102_write_reg(uint8_t addr, uint8_t data)
{
  HAL_I2C_Mem_Write(&hi2c2, MAX30102_Device_address,	addr,	1,	&data,1,HAL_MAX_DELAY);
  return 1;
}


/**
 * ************************************************************************
 * @brief ��ȡMAX30102�Ĵ�����һ��ֵ
 *
 * @param[in] addr  �Ĵ�����ַ
 *
 * @return
 * ************************************************************************
 */
uint8_t max30102_read_reg(uint8_t addr )
{
  uint8_t data=0;
  HAL_I2C_Mem_Read(&hi2c2, MAX30102_Device_address, addr, 1, &data, 1, HAL_MAX_DELAY);
  return data;
}


/**
 * ************************************************************************
 * @brief MAX30102��������λ
 *
 *
 * @return
 * ************************************************************************
 */
uint8_t Max30102_reset(void)
{
	if(max30102_write_reg(REG_MODE_CONFIG, 0x40))
        return 1;
    else
        return 0;
}

/**
 * ************************************************************************
 * @brief MAX30102������ģʽ����
 *
 *
 * ************************************************************************
 */
void MAX30102_Config(void)
{
	max30102_write_reg(REG_INTR_ENABLE_1,0xc0);//// INTR setting
	max30102_write_reg(REG_INTR_ENABLE_2,0x00);//
	max30102_write_reg(REG_FIFO_WR_PTR,0x00);//FIFO_WR_PTR[4:0]
	max30102_write_reg(REG_OVF_COUNTER,0x00);//OVF_COUNTER[4:0]
	max30102_write_reg(REG_FIFO_RD_PTR,0x00);//FIFO_RD_PTR[4:0]

	max30102_write_reg(REG_FIFO_CONFIG,0x0f);//sample avg = 1, fifo rollover=false, fifo almost full = 17
	max30102_write_reg(REG_MODE_CONFIG,0x03);//0x02 for Red only, 0x03 for SpO2 mode 0x07 multimode LED
	max30102_write_reg(REG_SPO2_CONFIG,0x27);	// SPO2_ADC range = 4096nA, SPO2 sample rate (50 Hz), LED pulseWidth (400uS)
	max30102_write_reg(REG_LED1_PA,0x32);//Choose value for ~ 10mA for LED1
	max30102_write_reg(REG_LED2_PA,0x32);// Choose value for ~ 10mA for LED2
	max30102_write_reg(REG_PILOT_PA,0x7f);// Choose value for ~ 25mA for Pilot LED
}

/**
 * ************************************************************************
 * @brief ��ȡFIFO�Ĵ���������
 *
 *
 * ************************************************************************
 */
void max30102_read_fifo(void)
{
  uint16_t un_temp;
  fifo_red=0;
  fifo_ir=0;
  uint8_t ach_i2c_data[6];

  //read and clear status register
  max30102_read_reg(REG_INTR_STATUS_1);
  max30102_read_reg(REG_INTR_STATUS_2);

  ach_i2c_data[0]=REG_FIFO_DATA;

	HAL_I2C_Mem_Read(&hi2c2,MAX30102_Device_address,REG_FIFO_DATA,1,ach_i2c_data,6,HAL_MAX_DELAY);

  un_temp=ach_i2c_data[0];
  un_temp<<=14;
  fifo_red+=un_temp;
  un_temp=ach_i2c_data[1];
  un_temp<<=6;
  fifo_red+=un_temp;
  un_temp=ach_i2c_data[2];
	un_temp>>=2;
  fifo_red+=un_temp;

  un_temp=ach_i2c_data[3];
  un_temp<<=14;
  fifo_ir+=un_temp;
  un_temp=ach_i2c_data[4];
  un_temp<<=6;
  fifo_ir+=un_temp;
  un_temp=ach_i2c_data[5];
	un_temp>>=2;
  fifo_ir+=un_temp;

	if(fifo_ir<=10000)
	{
		fifo_ir=0;
	}
	if(fifo_red<=10000)
	{
		fifo_red=0;
	}
}



