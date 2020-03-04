/* Keypad Rows Pins Config */
#define KEYPAD_ROWS_MaxNum  4

#define Keypad_Row0_PORT   'A'
#define Keypad_Row0_PIN     0

#define Keypad_Row1_PORT   'A'
#define Keypad_Row1_PIN     1

#define Keypad_Row2_PORT   'A'
#define Keypad_Row2_PIN     2

#define Keypad_Row3_PORT   'A'
#define Keypad_Row3_PIN     3

/* configure all ports for rows  keypad*/  
#define KEYPAD_ROWS_PORTS   {Keypad_Row0_PORT , Keypad_Row1_PORT , Keypad_Row2_PORT , Keypad_Row3_PORT}
/* configure all pins for column  keypad*/  
#define KEYPAD_ROWS_PINS    {Keypad_Row0_PIN , Keypad_Row1_PIN , Keypad_Row2_PIN, Keypad_Row3_PIN}




/* Keypad Cols Pins Config */
#define KEYPAD_COLS_MaxNum   4

#define Keypad_Col0_PORT    'B'
#define Keypad_Col0_PIN      0

#define Keypad_Col1_PORT    'B'
#define Keypad_Col1_PIN      1

#define Keypad_Col2_PORT    'B'
#define Keypad_Col2_PIN      2

#define Keypad_Col3_PORT    'B'
#define Keypad_Col3_PIN      3
 
/* configure all ports for column  keypad*/  
#define KEYPAD_COLS_PORTS    {Keypad_Col0_PORT , Keypad_Col1_PORT , Keypad_Col2_PORT , Keypad_Col3_PORT}
/* configure all pins for column  keypad*/  
#define KEYPAD_COLS_PINS     {Keypad_Col0_PIN , Keypad_Col1_PIN , Keypad_Col2_PIN, Keypad_Col3_PIN}


 /* configure the keypad buttons */
#define KEYPAD_KEYS           {{1,2,3,4},{5,6,7,8},{9,10,11,12},{13,14,15,16}}


#define KEYPAD_NO_KeyPressed  0xff











