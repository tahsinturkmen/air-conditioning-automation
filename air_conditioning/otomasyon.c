#include <16f877.h>
#include <ctype.h>
#device ADC = 10
#use delay(clock = 4000000)
#include <lcd.c>


/********************************************\
          LCD PIN ASSIGNMENTS 
       LCD_ENABLE_PIN -->  PIN_D0
       LCD_RS_PIN     -->  PIN_D1
       LCD_RW_PIN     -->  PIN_D2
       LCD_DATA4      -->  PIN_D4
       LCD_DATA5      -->  PIN_D5
       LCD_DATA6      -->  PIN_D6
       LCD_DATA7      -->  PIN_D7

\***********************************************/



/***function declarations***/
char keypad();
int temp2(void);
int temp1();
void system_app(void);

/*global variables*/
char rakam ;
int sicaklik,sicaklik2;
int x ;
int k;
int z;


/*@Start of main function*/


void main(){

set_tris_b(0x01);
set_tris_c(0xF0);
set_tris_d(0x00);
set_tris_a(0x3F);
output_c(0x00);
output_b(0x00);



setup_adc(ADC_CLOCK_DIV_32);
setup_adc_ports(ALL_ANALOG);

lcd_init();





while(TRUE){


system_app();


}//end for while()

}//end for main()




/* 1.definition of temperature sensor */

int temp1(){

   set_adc_channel(4);
   delay_us(20);
   sicaklik= read_adc()/2;
   return sicaklik;
}


/* 2.definiton of temperature sensor */

int temp2(void){

   set_adc_channel(1);
   delay_us(20);
   sicaklik2 = (read_adc()/2);
   return sicaklik2;

}





/* Keypad function definition */

char keypad(){

output_c(0x00);
 output_high(PIN_C0);


 if(input(PIN_C4)){delay_ms(20);rakam =7;}
  if(input(PIN_C5)){delay_ms(20);rakam=8;}
   if(input(PIN_C6)){delay_ms(20);rakam=9; }
    if(input(PIN_C7)){delay_ms(300);rakam='A'; }
    
    output_low(PIN_C0); 
    
    output_high(PIN_C1);
 
 if(input(PIN_C4)){delay_ms(20);rakam = 4;}
  if(input(PIN_C5)){delay_ms(20);rakam=5;}
   if(input(PIN_C6)){delay_ms(20);rakam=6;}
    if(input(PIN_C7)){delay_ms(20);rakam='B'; }
    
    output_low(PIN_C1); 
    
    output_high(PIN_C2);
 
 if(input(PIN_C4)){delay_ms(20);rakam =1;}
  if(input(PIN_C5)){delay_ms(20);rakam=2; }
   if(input(PIN_C6)){delay_ms(20);rakam=3; }
    if(input(PIN_C7)){delay_ms(20);rakam='C';}
    
    output_low(PIN_C2); 
    
    output_high(PIN_C3);
 
 if(input(PIN_C4)){delay_ms(20);rakam = '*';}
  if(input(PIN_C5)){delay_ms(20);rakam=0;}
   if(input(PIN_C6)){delay_ms(20);rakam= '#'; }
    if(input(PIN_C7)){delay_ms(20);rakam='D'; }
    
    output_low(PIN_C3); 
 

return rakam;

}



/* @This function provides condition statements and loop controls for the application 
   @Has no parameters and does not return a value to the real world 
*/

void system_app(void){



if(input(PIN_A4)){               // system on off

temp1();
temp2();
keypad();


if( keypad() == 0 ){

   lcd_gotoxy(1,1);
   printf(lcd_putc,"temp1 ve temp2");
   lcd_gotoxy(1,2);
   printf(lcd_putc,"enter * for set");
}


if(keypad()== '*'){
   
   printf(lcd_putc,"\f");
   
int count = 0;
int count2 = 0;
rakam =0;
int y =0;

while( keypad() != '#' ){
y =keypad();
   if( count == 0 ){
         if((count2 !=2) && (count2 !=3) && count2 != 4){
            lcd_gotoxy(1,1);
            printf(lcd_putc,"temp1 enter *");
         }
   }
 if( count2 == 2 && count !=2){
            lcd_gotoxy(1,1);
            printf(lcd_putc,"temp2 enter *");
              lcd_gotoxy(1,2);
            printf(lcd_putc,"cikis#");
   }

if( count == 1 || count2 ==3){
      lcd_gotoxy(1,2);
      printf(lcd_putc,"rakam1");
}
else if( count == 2 || count2 == 4 ){
      lcd_gotoxy(1,2);
      printf(lcd_putc,"rakam2");
}

delay_ms(10);

if( y == '*' ){
      count++;
      count2++;
      rakam=0;
}


if( count2 == 3 || count2 == 4 ){
      count = 0;
      
}

if( y != '*' ){
      k=y;
}

if( (y > 0) && (y < 9) && (count == 1) ){
      x = y;
      rakam=0;
      lcd_gotoxy(1,2);
      printf(lcd_putc,"rakam1");
      lcd_gotoxy(8,2);
      printf(lcd_putc,"%d",x);
      lcd_gotoxy(1,1);
      printf(lcd_putc,"enterfornum2 *");
}

if( (y > 0) && (y < 9) && (count == 2) ){
      x = ( x * 10 ) + k;
       lcd_gotoxy(1,2);
      printf(lcd_putc,"rakam2");
      lcd_gotoxy(8,2);
      printf(lcd_putc,"%d",x);
      count = 0;
      rakam = 0;
      lcd_gotoxy(1,2);
      printf(lcd_putc,"\f");
     
     
      
}

if( (y > 0) && (y < 9) && (count2 == 3) ){
      z = y;
      rakam=0;
      lcd_gotoxy(1,2);
      printf(lcd_putc,"rakam1");
      lcd_gotoxy(8,2);
      printf(lcd_putc,"%d",z);
      lcd_gotoxy(1,1);
      printf(lcd_putc,"enterfornum2 *");
}

if( (y > 0) && (y < 9) && (count2 == 4) ){
      z = ( z * 10 ) + k;
       lcd_gotoxy(1,2);
      printf(lcd_putc,"rakam1");
      lcd_gotoxy(8,2);
      printf(lcd_putc,"%d",z);
      count2 = 0;
      rakam = 0;
      lcd_gotoxy(1,2);
      printf(lcd_putc,"cikis#");
      delay_ms(1000);
}

if( keypad() == '#' ){
      printf(lcd_putc,"\f");
}

}
}

if( keypad() == 'A' ){
      printf(lcd_putc,"\f");
      output_high(PIN_B1);
      lcd_gotoxy(1,2);
       printf(lcd_putc,"PIN_B1 = 1");
      delay_ms(300);
}

if( keypad() != 'A' ){
 
      output_low(PIN_B1);
}


if( keypad() == 'B' ){
      printf(lcd_putc,"\f");
      output_high(PIN_B2);
      lcd_gotoxy(1,2);
       printf(lcd_putc,"PIN_B2 = 1");
      delay_ms(300);
}
if( keypad() != 'B' ){
      output_low(PIN_B2);
}




if( (keypad() != 'A') && (keypad() != 'B') && (x > 0) && !(keypad() == 0 ) ){ //start  for condition temp1 and temp2
    lcd_gotoxy(6,2);
         printf(lcd_putc," ");
      
   if( temp1() < x ){
         output_high(PIN_B3);
       
         lcd_gotoxy(1,1);
         printf(lcd_putc,"temp1");
         lcd_gotoxy(7,1);
         printf(lcd_putc,"%d",temp1());
         
         lcd_gotoxy(9,1);
         printf(lcd_putc,"Limit");
         lcd_gotoxy(15,1);
         printf(lcd_putc,"%d",x);
   }
   else if( temp1() > x && x > 0){
         output_low(PIN_B3);
       
         lcd_gotoxy(1,1);
         printf(lcd_putc,"temp1");
         lcd_gotoxy(7,1);
         printf(lcd_putc,"%d",temp1());
         
         lcd_gotoxy(9,1);
         printf(lcd_putc,"Limit");
         lcd_gotoxy(15,1);
         printf(lcd_putc,"%d",x);
   
   }
   
   if( temp2() < z){
         output_high(PIN_B4);
          lcd_gotoxy(1,2);
         printf(lcd_putc,"temp2");
         
         
         lcd_gotoxy(7,2);
         printf(lcd_putc,"%d",temp2());
         
          lcd_gotoxy(9,2);
         printf(lcd_putc,"Limit");
         lcd_gotoxy(15,2);
         printf(lcd_putc,"%d",z);
   }
   
      else if( temp2() > z && z > 0){
         output_low(PIN_B4);
       
         lcd_gotoxy(1,2);
         printf(lcd_putc,"temp1");
         lcd_gotoxy(7,2);
         printf(lcd_putc,"%d",temp2());
         
          lcd_gotoxy(9,2);
         printf(lcd_putc,"Limit");
         lcd_gotoxy(15,2);
         printf(lcd_putc,"%d",z);
   
   }
} // end  for condition temp1 and temp2
}// end for system on off (if(input(PIN_A4)))
else {
printf(lcd_putc,"\f");
output_b(0x00);
}



}


