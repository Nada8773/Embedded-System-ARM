#include "adc.h"
#include "lcd.h"

int main ()
{
	uint32 temp;
	LCD_init();
	ADC_init();
  lcd_displayString("Tempe");
    LCD_goToRowColumn(0,10);
	lcd_displayCharacter('C');
	while (1)
	{
		LCD_goToRowColumn(0,7);
		temp=adc_readchannel(2);
		temp=(temp*150*5)/(1023*1.5);

	 LCD_intgerToString(temp);
	}

	return 0;
}
