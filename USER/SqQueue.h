#pragma once

typedef  unsigned int SqQueueTypeDef;
typedef unsigned char u8;
typedef struct
{
    u8 *ArrayZeroAddr;//数组循环队列首地址
    SqQueueTypeDef front;//队列头索引
    SqQueueTypeDef rear;//队列尾索引
	SqQueueTypeDef ArrayMaxSize;//数组最大大小
	SqQueueTypeDef ArrayCurrentSize;//数组当前大小
}ArraySqQueueTypeDef;

void ArraySqQueueInit(ArraySqQueueTypeDef *ArraySqQueueStructer,u8 *ArrayZeroAddr,SqQueueTypeDef ArrayMaxSize);

u8 OutputQueueElement(ArraySqQueueTypeDef *ArraySqQueueStructer, u8 *ReceElement);
u8 InputQueueElement(ArraySqQueueTypeDef *ArraySqQueueStructer, u8 ReceElement);
