/* For PLL */
#define RCC2_R            (*((volatile unsigned long *)0x400FE070))
#define RCC2_USERCC2      0x80000000       /*use RCC2 put bit 31 =1*/
#define RCC2_DIV400       0x40000000       /*to create a 7 bit divisor using the 400 MHz PLL output, */
#define RCC2_SYSDIV2      0x1F800000       /*bit from 23 to 28 System Clock Divisor 2 */
#define RCC2_SYSDIV2LSB   0x00400000       /*bit 22 When DIV400 is set, this bit becomes the LSB of SYSDIV2*/
#define RCC2_PWRDN2       0x00002000       /*bit 13 =1 The PLL is powered down  */
#define RCC2_BYPASS2      0x00000800       /* bit 11 */
#define RCC2_OSCSRC2      0x00000070       /*6-4bits*/
#define RCC2_OSCSRC2_Main 0x00000000       /*main osci*/
#define RCC_R             (*((volatile unsigned long *)0x400FE060))
#define RCC_XTAL_16MZ     0x00000540       /*6-10 bits*/
#define RCC_XTAL          0x000007C0       /*6-10 bits =0--0111,1100,0000*/
#define RIS_R             (*((volatile unsigned long *)0x400FE050))
#define RIS_PLLLRIS       0x00000040       //bit 6
void Init_PLL(void);
