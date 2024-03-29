#include <B212H.h>
#include "D:\CCS\i2c_Flex_LCD.c" 
const double SCALE = 20700;
unsigned int32 readCount(void) {
  unsigned int32 data;
  unsigned int8 j;
  output_bit(DT1, 1);
  output_bit(SCK, 0);
  data = 0;
  while (input(DT1));
  for (j = 0; j < 24; j++) {
    output_bit(SCK, 1);
    data = data << 1;
    output_bit(SCK, 0);
    if (input(DT1)) {
      data.0 = 1;//thay vinh update.
    }
  }
  output_bit(SCK, 1);
  data = data ^ 0x800000;
  output_bit(SCK, 0);
  return data;
}

int32 readAverage(void) {
  unsigned int32 sum = 0;
  for (int k = 0; k < 20; k++) {
    sum = sum + readCount();
  }
  sum = sum / 20;
  return sum;
}

void main() {  
int i=0,h=0;
 unsigned int32 read1 = 0, offset = 0;
  float gram = 0;
  offset = readAverage();
lcd_init(0x4E,16,2);
lcd_backlight_led(ON);
LCD_Clear();
  lcd_gotoxy(2, 1); 
printf(lcd_putc, "Hello everybody");
  lcd_gotoxy(6,2 ); 
 printf(lcd_putc, "18CDT1");  
  delay_ms(3000);
 LCD_Clear();
  lcd_gotoxy(5, 1); 
 printf(lcd_putc, "Loadcell");   
  delay_ms(1000);
 lcd_gotoxy(2,2 ); 
printf(lcd_putc, "Design By HuLa");   
 delay_ms(3000);
 while (TRUE) {
 
 read1 = readAverage();
    if (offset >= read1) {
      float val1 = (offset - read1);
      gram = val1;
    } else {
      float val2 = (read1 - offset);
      gram = val2;

    }
  
   
   if((gram/scale)>2)
   {
   if(h==0)
   {
    if(i<2){
    i++;
     LCD_Clear();
    lcd_gotoxy(1,1); 
     printf(lcd_putc, "Weight:Waiting...");  
     lcd_gotoxy(6,2 ); 
printf(lcd_putc, "HuLa");  
      }
      else
      {
       LCD_Clear();
      lcd_gotoxy(1,1); 
      printf(lcd_putc, "Weight: %f Kg", gram/scale); 
      
     lcd_gotoxy(6,2 ); 
     printf(lcd_putc, "HuLa");
     i=0;
     h=1;
      }
      }
      if(h==1)
      {
     LCD_Clear();
     lcd_gotoxy(1,1); 
     printf(lcd_putc, "Weight: %f Kg", gram/scale); 
     lcd_gotoxy(6,2 ); 
     printf(lcd_putc, "HuLa");
      }
      }
      else
      {
       output_toggle(led_blink);
     h=1-h;
     LCD_Clear();
     lcd_gotoxy(1,1);
     printf(lcd_putc, "Weight: %f Kg", gram/scale);  
     lcd_gotoxy(6,2 ); 
     printf(lcd_putc, "HuLa");  
      }
      printf("%f\n\r",gram/scale);
   }    
}


