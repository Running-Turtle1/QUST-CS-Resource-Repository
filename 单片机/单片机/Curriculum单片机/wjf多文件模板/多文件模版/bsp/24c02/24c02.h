#ifndef __24C02_H__
#define __24C02_H__

/********************���������壩********************/
//AT24C02ָ����ַд����
void at24c02_write_one_byte(u8 addr,u8 dat);
//AT24C02ָ����ַ������
u8 at24c02_read_one_byte(u8 addr);
#endif