#include <smoke.h>

bit A;
//bit E;


void Delay(unsigned int xms)		
{
	unsigned char i, j;
 while(xms--)
 { 
	 i = 2;
	j = 239;
	do
	{
		while (--j);
	} while (--i); 
 }
	
}

bit Smoke1( )
{
 
	A=Fu;
  if(A==0)
	 {
 	   Delay(5);
			if(A==0)
			 {A=0;}
						
	 }	
return A;
 }	


//bit Smoke2( )
//{
// 
//	E=Su;
//  
//  if(E==0)
//	 {
//   	 Delay(5);
//					if(E==0)
//					{E=0;}
//						
//	 }	
//return E;
// }	
