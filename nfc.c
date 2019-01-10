#include <wiringPi.h>
#include <wiringPiSPI.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include "RC522.h"

void IC_test ( void )
{
	char cStr [ 30 ];
	uint8_t ucArray_ID [ 4 ];    /*先后存放IC卡的类型和UID(IC卡序列号)*/
	uint8_t ucStatusReturn;      /*返回状态*/
	static uint8_t ucLineCount = 0;
	while ( 1 ) {
		/*寻卡*/
		if ( ( ucStatusReturn = PcdRequest ( PICC_REQALL, ucArray_ID ) ) != MI_OK ) { /*若失败再次寻卡*/
			ucStatusReturn = PcdRequest ( PICC_REQALL, ucArray_ID );
		}

		if ( ucStatusReturn == MI_OK  ) {
			/*防冲撞（当有多张卡进入读写器操作范围时，防冲突机制会从其中选择一张进行操作）*/
			if ( PcdAnticoll ( ucArray_ID ) == MI_OK ) {
				sprintf ( cStr, "The Card ID is: %02X%02X%02X%02X",
				          ucArray_ID [ 0 ],
				          ucArray_ID [ 1 ],
				          ucArray_ID [ 2 ],
				          ucArray_ID [ 3 ] );
				printf ( "%s\r\n", cStr );

				ucLineCount ++;
				if ( ucLineCount == 17 ) {
					ucLineCount = 0;
				}
			}
		}
	}
}

int main(void)
{
	RC522_setup(7);
	PcdReset ();
	M500PcdConfigISOType('A');
	printf ( "Start NFC scan\r\n" );
	while(1) {
		IC_test();
		delay(100);
	}
}
