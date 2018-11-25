#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    unsigned int eax;
    unsigned int ebx;
    unsigned int ecx;
    unsigned int edx;
} reg_st;

void getCpuId(unsigned int in_eax, reg_st *reg)
{
    __asm__ volatile (
        "cpuid;"
        : "=a"(reg->eax), "=b"(reg->ebx), "=c"(reg->ecx), "=d"(reg->edx)
		: "a"(in_eax)
		: 
        );
}



int main(int argc, char *argv[])
{
    
    reg_st reg;    
    char buf[64];
    
    memset( buf, 0x00, sizeof(buf) );
    
    getCpuId(0x00000000, &reg);
	printf("CPU Support\t: %x\n", reg.eax);
	//printf("CPU : %.4s%.4s%.4s\n", (char *)&reg.ebx, (char *)&reg.edx, (char *)&reg.ecx);
	
	if(reg.eax >= 1)
	{
	    getCpuId(0x00000001, &reg);
	    printf("CPU Core(s)\t: %d\n", (reg.ebx >> 16) & 0xff);
	    printf("CPU Family\t: %d\n", (reg.eax >> 8) & 0x0f);
	    printf("CPU Model\t: %d\n", (reg.eax >> 4) & 0x0f);
	    
	    printf("FMA Enable\t: %d\n", ((reg.ecx >> 12) & 0x01));
	}
	
	getCpuId(0x80000000, &reg);
	printf("CPU Ex Support\t: %x\n", reg.eax);
	
	if(reg.eax > 0x80000004)
	{
	    int eax_adr = 0x80000002;
	    char cpuname[64]={0};
	    
	    int i;
	    for(i=0;i<3;i++)
	    {
	        getCpuId(eax_adr+i, &reg);
	        memcpy(&cpuname[i << 4], &reg.eax, 4);
	        memcpy(&cpuname[(i << 4) +4], &reg.ebx, 4);
	        memcpy(&cpuname[(i << 4) +8], &reg.ecx, 4);
	        memcpy(&cpuname[(i << 4) +12], &reg.edx, 4);
	    }
	    
	    printf("CPU Name\t: %s\n", cpuname);
	}
	
	if(reg.eax > 0x80000005) printf("ok");
	
    short int n[4] = {1000,2000,3000,4000};
    short int m[4] = {1000,1000,1000,1000};
    short int d[4];
    
    __asm__ volatile (
        "movq (%1), %%mm0\n"
        "movq (%2), %%mm1\n"
        "psubsw %%mm1,%%mm0\n"
        "movq %%mm0,%0\n"
        "emms"
        : "=g"(d)
        : "r"(&n), "r"(&m)
        : "memory","cc", "%mm0", "%mm1"
        );
    
    printf("%d %d %d %d\n", d[0],d[1],d[2],d[3]);
    
    //char a = 3;
    //printf("%d", a);
    
    return 0;
}