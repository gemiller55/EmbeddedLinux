/* GPIO example for BeableBone platform */
/* Copyright ProtectedLogic 2012 */
/*      ECM             */
#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<sys/mman.h>

#define u32             unsigned long

#define GPIO1_BASEADDR          0x4804C000              // from TI spec, pg 162
#define GPIO1_CRTL                      0x130                   // '', pg. 4216
#define GPIO1_OE                        0x134                   // '', pg. 4216
#define GPIO1_DATAOUT           0x13C                   // '', pg. 4216
#define USER_LED                        1<<24                   // various

int main(argc, argv)
{
        u32 fd;
        u32     virtAddr;
        volatile u32 counter;
        u32 reg = 0;


        fd = open("/dev/mem", O_RDWR|O_SYNC);

        if (fd == -1)
        {
                printf("error in open\n");
                return 0;
        }
        virtAddr = mmap(0,4096,PROT_READ|PROT_WRITE,MAP_SHARED,fd,GPIO1_BASEADDR
);
        //printf("%8.8x\n",virtAddr);

        /* set the control register */

        *((u32 *)(virtAddr + GPIO1_CRTL)) = (u32)0;

        /* set the output enable register, reset = 0xFFFFFFFF => all are inputs
*/

        *((u32 *)(virtAddr + GPIO1_OE)) = (u32)0;
      while(1)
        {

                printf("%d,%8.8x\n",counter,reg);
                reg^=USER_LED;                                          // toggl
e
                *((u32 *)(virtAddr + GPIO1_DATAOUT)) = reg;


                counter = 0;

                while((counter++) != 0x1000000);


        }

 