#include  "delay.h"
void delay_nms(uint16_t time)
{    
   uint16_t i=0;  
   while(time--)
   {
      i=12000;  //�Լ�����
      while(i--) {};    
   }
}
