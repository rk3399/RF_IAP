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
	IAPCMDID CmdId;//����ID
	u8 *CmdStr;//�����ַ���
	u8 Attribute;//����Ķ�д�������� 00:��������01����������10��д���� 11����д����
	u8 CmdStrLen;//�����ַ�������
	IAPCmdCallbackFun CallbackFun; //����ص�����
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




//IAP�������
#define IAPTaskStackSize 512//*4�����ֽ���
#define IAPTaskPrio 20
extern OS_TCB IAPTaskTCB;
extern CPU_STK IAPTaskStack[IAPTaskStackSize];

void IAPTaskPtr(void *p_arg);
