
#include "beep.h"

#include "os_error_hendler.h"


void Error_Hendler(OS_ERR  Errorflag)
{
	if(Errorflag){
	
	
		BEEP = 1;
		while(1);
	}
}


