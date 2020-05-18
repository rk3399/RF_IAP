#pragma once

typedef  unsigned int SqQueueTypeDef;
typedef unsigned char u8;
typedef struct
{
    u8 *ArrayZeroAddr;//����ѭ�������׵�ַ
    SqQueueTypeDef front;//����ͷ����
    SqQueueTypeDef rear;//����β����
	SqQueueTypeDef ArrayMaxSize;//��������С
	SqQueueTypeDef ArrayCurrentSize;//���鵱ǰ��С
}ArraySqQueueTypeDef;

void ArraySqQueueInit(ArraySqQueueTypeDef *ArraySqQueueStructer,u8 *ArrayZeroAddr,SqQueueTypeDef ArrayMaxSize);

u8 OutputQueueElement(ArraySqQueueTypeDef *ArraySqQueueStructer, u8 *ReceElement);
u8 InputQueueElement(ArraySqQueueTypeDef *ArraySqQueueStructer, u8 ReceElement);
