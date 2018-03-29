/* 
ecvt.c  --  an implementation of ecvt()

Choose your browser's option to Save As... to download this code example. Send
the program to your AS/400 using FTP or similar method and include it in your source
code with the line below.

#include "ecvt.c"

This program was developed on a V3R7 system.  There is a notable difference between
this version of ecvt() and that of other platforms.  This relates to the use
of _INF, INFINITY, and NAN macros.  None of these macros exist in AS/400 header files,
so as such, are not directly supported.  However, the HUGE_VAL macro is supported for
the incoming Value parameter.  To simulate the action of ecvt() on other platforms,
the HUGE_VAL macro is translated to return "INF" as the resultant string of ecvt().
NAN is supported using another workaround, the isnan() workaround.

This code fragment that is furnished by IBM is a simple example to provide an
illustration. This example has not been thoroughly tested under all conditions.
IBM, therefore, cannot guarantee or imply reliability, serviceability, or function
of this program. All code contained herein is provided to you "AS IS". THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
EXPRESSLY DISCLAIMED.

*/

#include <stdio.h>
#include <string.h>


#define QPIDECVTBUFSIZE 128

typedef struct {
    unsigned long lobits;
    unsigned long hibits;
    } BITMASK;

typedef union {
    BITMASK bm;
    double  dv;
    } OVERLAY;

#define EXPBITS  0x7FF00000
#define ALLZEROS 0x00000000
#define CHKEXP   0x000FFFFF

/****** prototypes ******/
int isnan(double fres);
int finite(double fres);
char* ecvt(double Value, int NumberOfDigits, int* DecimalPointer, int* Sign);
/************************/


char* DoubleToStr(double Value, char *pbuf,int len, int NumberOfDigits, int* DecimalPointer, int* Sign)
{
	char* QPIDecvt_buffer=pbuf;
  char buf[len];
  int idx=0;
//  int idx2;
  int aft=0;

	MEMSET(QPIDecvt_buffer,0,len);
  if (!finite(Value))
     {
			 *DecimalPointer=0;
			 if (Value < 0) *Sign = 1; else *Sign = 0;
			 MEMCPY(QPIDecvt_buffer,"INF",4);
			 return QPIDecvt_buffer;
     }
  if (isnan(Value))
     {
			 *Sign=0;
			 *DecimalPointer=0;
			 MEMCPY(QPIDecvt_buffer,"NAN",4);
			 return QPIDecvt_buffer;
     }

  *Sign = 0;
  sprintf(buf, "%#+1.*E",NumberOfDigits-1,Value);

  switch (buf[idx])
     {
     case '-':
        *Sign = 1;
        aft++;
        break;
     case '+':
        aft++;
        break;
     }

  QPIDecvt_buffer[0] = buf[1];

  for (idx=1; idx < NumberOfDigits; idx++)
     QPIDecvt_buffer[idx] = buf[idx+2];

  QPIDecvt_buffer[NumberOfDigits] = '\0';
  sscanf(buf+NumberOfDigits+4, "%d", DecimalPointer);
  (*DecimalPointer) ++;
  return QPIDecvt_buffer;
}




int isnan( double fres ) {

    OVERLAY value;

    value.dv = fres;
    if ( ( (value.bm.lobits & EXPBITS) == EXPBITS )  &&
                 ( ( (value.bm.lobits & CHKEXP)  != ALLZEROS ) ||
                 ( value.bm.hibits != ALLZEROS ) ) )
        return( 1 ); /* Yes, it is not a number NaN */
    else
                return( 0 ); /* it is a number */
}



int finite( double fres ) {

    OVERLAY value;

    value.dv = fres;
    if ( ( (value.bm.lobits & EXPBITS) == EXPBITS )  &&
		 ( (value.bm.lobits & CHKEXP)  == ALLZEROS ) &&
		 ( value.bm.hibits == ALLZEROS ) )
        return( 0 ); /* No, it is not a finite number */
    else
		return( 1 ); /* it is a finite number */
}
