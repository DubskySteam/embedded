# 1 "src/led.c"
# 1 "/home/dubsky/embedded/workspace/led//"
# 1 "<built-in>"
# 1 "<command-line>"
# 1 "src/led.c"
typedef unsigned int uint32_t;
# 13 "src/led.c"
int main (void)
{

 (*(volatile uint32_t *) (0x10012000 + 0x38)) &= ~(1 << 5);
 (*(volatile uint32_t *) (0x10012000 + 0x4)) &= ~(1 << 5);
 (*(volatile uint32_t *) (0x10012000 + 0x8)) |= 1 << 5;
 (*(volatile uint32_t *) (0x10012000 + 0xc)) |= (1 << 5);

 volatile uint32_t i = 0;
 while(1)
 {

  (*(volatile uint32_t *) (0x10012000 + 0xc)) &= ~(1 << 5);

   for (i = 0; i < 184210; i++){}

  (*(volatile uint32_t *) (0x10012000 + 0xc)) |= (1 << 5);
  for (i = 0; i < 184210; i++){}
 }
}
