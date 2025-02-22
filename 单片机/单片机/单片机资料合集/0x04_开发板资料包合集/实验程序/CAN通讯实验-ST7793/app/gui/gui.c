#include "gui.h"

#ifdef USE_FONT_UPDATE
#include "ff.h"
#include "diskio.h"
#endif

#ifdef USE_FLASH_CHAR
#include "flash.h"
#else
#include "asciicode.h"
#endif

#ifdef USE_FONT_UPDATE
#include "malloc.h"
#endif
/****************************************************************************
* Function Name  : GUI_Dot
* Description    : 在彩屏上面画一点
* Input          : x：点的X坐标
*                * y：点的Y坐标
*                * color：点的颜色
* Output         : None
* Return         : None
****************************************************************************/

void GUI_Dot(uint16_t x, uint16_t y, uint16_t color)
{  
	TFT_SetWindow(x, y, x, y);  //设置点的位置
	TFT_WriteData(color);       //画点	
}

/****************************************************************************
* Function Name  : GUI_Box
* Description    : 给一个区域涂上颜色
* Input          : sx：起始X坐标, sy：其实Y坐标, 
*                * ex：终止X坐标, ey：终止Y坐标,
*                * color：方框的颜色
* Output         : None
* Return         : None
****************************************************************************/

void GUI_Box(uint16_t xState, uint16_t yState, uint16_t xEnd, uint16_t yEnd, uint16_t color)
{ 
	uint16_t temp;

    if((xState > xEnd) || (yState > yEnd))
    {
        return;
    }   
	TFT_SetWindow(xState, yState, xEnd, yEnd); 
    xState = xEnd - xState + 1;
	yState = yEnd - yState + 1;

	while(xState--)
	{
	 	temp = yState;
		while (temp--)
	 	{	
			TFT_WriteData(color);
		}
	}
}

/****************************************************************************
* Function Name  : GUI_DrowSign
* Description    : 画一个十字的标记
* Input          : x：标记的X坐标；
*                * y：标记的Y坐标
*                * color：标记的颜色
* Output         : None
* Return         : None
****************************************************************************/

void GUI_DrowSign(uint16_t x, uint16_t y, uint16_t color)
{
    uint8_t i;

    /* 画点 */
    TFT_SetWindow(x-1, y-1, x+1, y+1);
    for(i=0; i<9; i++)
    {
        TFT_WriteData(color);    
    }

    /* 画竖 */
    TFT_SetWindow(x-4, y, x+4, y);
    for(i=0; i<9; i++)
    {
        TFT_WriteData(color);    
    }

    /* 画横 */
    TFT_SetWindow(x, y-4, x, y+4);
    for(i=0; i<9; i++)
    {
        TFT_WriteData(color);    
    }
}

#ifndef USE_FLASH_CHAR
/****************************************************************************
* Function Name  : GUI_Show12ASCII
* Description    : 写12号ASCII码
* Input          : x：起始X坐标
*                * y：起始Y坐标
*                * p：字符串首地址
*                * wordColor：字体颜色
*                * backColor：背景颜色
* Output         : None
* Return         : None
****************************************************************************/

void GUI_Show12ASCII(uint16_t x, uint16_t y, uint8_t *p, 
                     uint16_t wordColor, uint16_t backColor)
{
	uint8_t i, wordByte, wordNum;
	uint16_t color;

	while(*p != '\0')   //检测是否是最后一个字
	{
        /* 在字库中的ASCII码是从空格开始的也就是32开始的，所以减去32 */
		wordNum = *p - 32;
		
        TFT_SetWindow(x, y, x+7, y+15);           //字宽*高为：8*16
		for (wordByte=0; wordByte<16; wordByte++) //每个字模一共有16个字节
		{
			color = ASCII8x16[wordNum][wordByte];
			for (i=0; i<8; i++) 
			{
				if ((color&0x80) == 0x80)
				{
					TFT_WriteData(wordColor);
				} 						
				else
				{
					TFT_WriteData(backColor);
				} 	
				color <<= 1;
			}
		}

		p++;    //指针指向下一个字
		
        /* 屏幕坐标处理 */
        x += 8;
        if(x > 233)   //TFT_XMAX -8
        {
            x = 0;
            y += 16;    
        }
	}
}

#else

/****************************************************************************
* Function Name  : GUI_Show12Char
* Description    : 通过FLASH字库显示12号字母和汉字（使用GBK）
* Input          : x：起始X坐标
*                * y：起始Y坐标
*                * ch：字符串首地址
*                * wordColor：字体颜色
*                * backColor：背景颜色
* Output         : None
* Return         : None
****************************************************************************/

void GUI_Show12Char(uint16_t x, uint16_t y, uint8_t *ch, 
                    uint16_t wordColor, uint16_t backColor)
{
    uint8_t i, j, color, buf[32];
    uint16_t asc;
    uint32_t wordAddr = 0;

    while(*ch != '\0')
    {
        /*显示字母 */
        if(*ch < 0x80)  //ASCII码从0~127
        {
            /* 在字库中的ASCII码是从空格开始的也就是32开始的，所以减去32 */
    		wordAddr = *ch - 32;
            wordAddr *= 16;
            wordAddr += GUI_FLASH_ASCII_ADDR;
            
            /* 读取FLASH中该字的字模 */
            FLASH_ReadData(buf, wordAddr, 16);
            
            /* 显示该文字 */		
            TFT_SetWindow(x, y, x+7, y+15);           //字宽*高为：8*16
    		for (j=0; j<16; j++) //每个字模一共有16个字节
    		{
    			color = buf[j];
    			for (i=0; i<8; i++) 
    			{
    				if ((color&0x80) == 0x80)
    				{
    					TFT_WriteData(wordColor);
    				} 						
    				else
    				{
    					TFT_WriteData(backColor);
    				} 	
    				color <<= 1;
    			}
    		}
    
    		ch++;    //指针指向下一个字
    		
            /* 屏幕坐标处理 */
            x += 8;
            if(x > 233)   //TFT_XMAX -8
            {
                x = 0;
                y += 16;    
            }            
        }
        /* 显示汉字 */
        else
        {
            /* 将汉字编码转换成在FLASH中的地址 */
            asc = *ch - 0x81;     //高字节是表示分区，分区是从0x81到0xFE,所以转换成地址-0x80
            wordAddr = asc * 190; //每个分区一共有190个字
    
            asc = *(ch + 1); //低字节代表每个字在每个分区的位置，它是从0x40到0xFF
            if(asc < 0x7F)   //在0x7F位置有个空位，但是我们取模不留空，所以大于0x7F之后多减一
            {
                asc -= 0x40;
            }
            else
            {
                asc -= 0x41;
            }
            
            wordAddr += asc; //求出在GBK中是第几个字
            wordAddr *= 32;  //将字位置转换位FLASH地址
            wordAddr += GUI_FLASH_12CHAR_ADDR; //加上首地址
    
            /* 读取FLASH中该字的字模 */
            FLASH_ReadData(buf, wordAddr, 32);
    
            /* 在彩屏上面显示 */
            TFT_SetWindow(x, y, x+15, y+15);
            for(i=0; i<32; i++)
            {
                 
                color = buf[i];            
                for(j=0; j<8; j++) 
        		{
        			if((color & 0x80) == 0x80)
        			{
        				TFT_WriteData(wordColor);
        			} 						
        			else
        			{
        				TFT_WriteData(backColor);
        			} 
        			color <<= 1;
        		}//for(j=0;j<8;j++)结束
            }
    
            /* 屏幕坐标处理 */
            x += 16;
            if(x > 225)   //TFT_XMAX -15
            {
                x = 0;
                y += 16;    
            }
    
            /* 写下一个字，每个汉字占两个字节所以+2 */
            ch += 2;             
        }
    }    
}
/****************************************************************************
* Function Name  : GUI_Show12Chinese
* Description    : 通过FLASH字库显示12号汉字（使用GBK）
* Input          : x：起始X坐标
*                * y：起始Y坐标
*                * cn：字符串首地址
*                * wordColor：字体颜色
*                * backColor：背景颜色
* Output         : None
* Return         : None
****************************************************************************/

void GUI_Show16Chinese(uint16_t x, uint16_t y, uint8_t *cn, 
                       uint16_t wordColor, uint16_t backColor)
{   
    uint8_t i, j, color, buf[63];
    uint16_t asc;
    uint32_t wordAddr = 0;    
    while(*cn != '\0')
    {  
        /* 将汉字编码转换成在FLASH中的地址 */
        asc = *cn - 0x81;     //高字节是表示分区，分区是从0x81到0xFE,所以转换成地址-0x80
        wordAddr = asc * 190; //每个分区一共有190个字

        asc = *(cn + 1); //低字节代表每个字在每个分区的位置，它是从0x40到0xFF
        if(asc < 0x7F)   //在0x7F位置有个空位，但是我们取模不留空，所以大于0x7F之后多减一
        {
            asc -= 0x40;
        }
        else
        {
            asc -= 0x41;
        }
        
        wordAddr += asc; //求出在GBK中是第几个字
        wordAddr *= 63;  //将字位置转换位FLASH地址
        wordAddr += GUI_FLASH_16CHAR_ADDR; //加上首地址

        /* 读取FLASH中该字的字模 */
        FLASH_ReadData(buf, wordAddr, 63);

        /* 在彩屏上面显示 */
        TFT_SetWindow(x, y, x+23, y+20);
        for(i=0; i<63; i++)
        {
            color = buf[i];            
            for(j=0; j<8; j++) 
    		{
    			if((color & 0x80) == 0x80)
    			{
    				TFT_WriteData(wordColor);
    			} 						
    			else
    			{
    				TFT_WriteData(backColor);
    			} 
    			color <<= 1;
    		}//for(j=0;j<8;j++)结束
        }

        /* 屏幕坐标处理 */
        x += 21;
        if(x > 218)   //TFT_XMAX -21
        {
            x = 0;
            y += 21;    
        }

        /* 写下一个字，每个汉字占两个字节所以+2 */
        cn += 2;      
    }    
}

#endif


#ifdef USE_FONT_UPDATE

/****************************************************************************
* Function Name  : GUI_FontUpdate
* Description    : 更新字库
* Input          : updateState：选择更新的字库
* Output         : None
* Return         : None
****************************************************************************/

void GUI_FontUpdate(uint8_t updateState)
{
    FRESULT res;
	FIL fsrc;
	UINT  br;
    uint32_t wordAddr, i, j;

#ifdef __MALLOC_H	
    uint8_t *p;
    p = malloc(4096);                  //开辟一个内存块
    if(p == 0)
    {
        return;
    }
#else
	uint8_t buffer[512];
#endif    	

    /* 更新ASCII字库 */
    if((updateState & GUI_UPDATE_ASCII) == GUI_UPDATE_ASCII)
    {
        /* 设置写入起始地址 */
        wordAddr = GUI_FLASH_ASCII_ADDR;
        j = 0;

        /* 打开读取文件 */
        res = f_open(&fsrc, GUI_ASCII_FILE, FA_READ);	
    	if(res == FR_OK)  //打开成功
        { 
         	for (;;)      //开始读取数据
         	{       
#ifdef __MALLOC_H	
                res = f_read(&fsrc, p, 4096, &br);
    
                /* 将读取到的数据写入FLASH */
                FLASH_WriteData(p, wordAddr, br);
          	    wordAddr += br;   //写入地址增加

#else
                res = f_read(&fsrc, buffer, sizeof(buffer), &br);
    
                /* 将读取到的数据写入FLASH */
                FLASH_WriteData(buffer, wordAddr, br);
          	    wordAddr += br;   //写入地址增加
#endif
                j += br;
                i = j * 100 / 1456;
                GUI_Box(0, 80, i, 90, RED);    

                if (res || br == 0)
    			{
    				break;    // error or eof 
    			}
            } 
        }
    	 
        f_close(&fsrc);  //不论是打开，还是新建文件，一定记得关闭
    }

    /* 更新12号汉字库 */
    if((updateState & GUI_UPDATE_12CHAR) == GUI_UPDATE_12CHAR)
    {
        wordAddr = GUI_FLASH_12CHAR_ADDR;
        j = 0;

        res = f_open(&fsrc, GUI_12CHAR_FILE, FA_READ);
    	
    	if(res == FR_OK) 
        {  
         	for (;;)  
         	{      
#ifdef __MALLOC_H	
                res = f_read(&fsrc, p, 4096, &br);
    
                /* 将读取到的数据写入FLASH */
                FLASH_WriteData(p, wordAddr, br);
          	    wordAddr += br;   //写入地址增加
#else
                res = f_read(&fsrc, buffer, sizeof(buffer), &br);
    
                FLASH_WriteData(buffer, wordAddr, br);
          	    wordAddr += br;
#endif
                j += br;
                i = j * 100 / 766080;
                GUI_Box(0, 95, i, 105, RED);    

    
                if (res || br == 0)
    			{
    				break;    // error or eof 
    			}
            } 
        }
        f_close(&fsrc);  //不论是打开，还是新建文件，一定记得关闭
    }
    
    /* 更新16号汉字库 */
    if((updateState & GUI_UPDATE_16CHAR) == GUI_UPDATE_16CHAR)
    {
        
        wordAddr = GUI_FLASH_16CHAR_ADDR;
        j = 0;

        res = f_open(&fsrc, GUI_16CHAR_FILE, FA_READ);	
    	if(res == FR_OK) 
        { 
         	for (;;)  
         	{       
#ifdef __MALLOC_H	
                res = f_read(&fsrc, p, 4096, &br);
    
                /* 将读取到的数据写入FLASH */
                FLASH_WriteData(p, wordAddr, br);
          	    wordAddr += br;   //写入地址增加
#else
                res = f_read(&fsrc, buffer, sizeof(buffer), &br);
    
                FLASH_WriteData(buffer, wordAddr, br);
          	    wordAddr += br;
#endif
                j += br;
                i = j * 100 / 1508220;
                GUI_Box(0, 110, i, 120, RED);    

    
                if (res || br == 0)
    			{
    				break;    // error or eof 
    			}
            } 
        }
    	 
        f_close(&fsrc);  //不论是打开，还是新建文件，一定记得关闭
    }
#ifdef __MALLOC_H	
    free(p);
#endif
} 
 
#endif


