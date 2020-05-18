#pragma once

#include  <includes.h>


#define IAPMAXSIZE 2048
extern OS_TCB  *IAPSendTaskTCB;

typedef void (*IAPCmdCallbackFun)(u8 *arg0,u16 arg1);
typedef void (*IAPERRORCallbackfun)(void);

typedef enum{
	IAPCMD_GETINFO = 0,
	IAPCMD_READ,
	IAPCMD_ADD,
	IAPCMD_RENAME,
	IAPCMD_DEL,
	IAPCMD_GO,
	IAPCMD_READPRO,
	IAPCMD_WRITEPRO,
	IAPCMD_COUNT
}IAPCMDID;
typedef struct{
	IAPCMDID CmdId;//命令ID
	u8 *CmdStr;//命令字符串
	u8 Attribute;//命令的读写保护属性 00:不保护，01：读保护，10：写保护 11：读写保护
	u8 CmdStrLen;//命令字符串长度
	IAPCmdCallbackFun CallbackFun; //命令回调函数
}IAPCMDStructDef;




typedef enum{
	NONE_ERROR = 0,
	ERROR_DATA,
	ERROR_NOIAPCMD,
	ERROR_NOFOUNDCMD,
	ERROR_READPRO,
	ERROR_WRITEPRO,
	ERROR_CRC,
	ERROR_SADDR,
	IAPERROR_COUNT
	
}IAPERROR;

typedef struct{
	IAPERROR errid;
	
	IAPERRORCallbackfun Callbackfun;
	
}IAPERRORStructDef;




//IAP任务相关
#define IAPTaskStackSize 512//*4等于字节数
#define IAPTaskPrio 20
extern OS_TCB IAPTaskTCB;
extern CPU_STK IAPTaskStack[IAPTaskStackSize];

void IAPTaskPtr(void *p_arg);
