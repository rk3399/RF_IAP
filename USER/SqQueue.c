
#include "SqQueue.h"

void ArraySqQueueInit(ArraySqQueueTypeDef *ArraySqQueueStructer,u8 *buf,SqQueueTypeDef bufMaxSize)
{
	ArraySqQueueStructer->ArrayZeroAddr = buf;
	ArraySqQueueStructer->front = 0;
	ArraySqQueueStructer->rear = 0;
	ArraySqQueueStructer->ArrayMaxSize = bufMaxSize;
	ArraySqQueueStructer->ArrayCurrentSize = 0;
}

////����ѭ�������п�
//u8 IsEmptyQueue(ArraySqQueueTypeDef *ArraySqQueueStructer)
//{
//	return (ArraySqQueueStructer->front == ArraySqQueueStructer->rear) ? 1 : 0;
//}

////����ѭ����������
//u8 IsFullQueue(ArraySqQueueTypeDef *ArraySqQueueStructer)
//{
//	return ((ArraySqQueueStructer->rear + 1) % ArraySqQueueStructer->ArrayMaxSize == ArraySqQueueStructer->front) ? 1 : 0;
//}

//����ѭ������Ԫ�س���
u8 OutputQueueElement(ArraySqQueueTypeDef *ArraySqQueueStructer, u8 *ReceElement)
{
	//if(IsEmptyQueue(ArraySqQueueStructer) != 1)        //����δ��
	if(ArraySqQueueStructer->ArrayCurrentSize > 0){
       *ReceElement = ArraySqQueueStructer->ArrayZeroAddr[ArraySqQueueStructer->front] ;
		
		ArraySqQueueStructer->front = (ArraySqQueueStructer->front + 1) % ArraySqQueueStructer->ArrayMaxSize;
		
		ArraySqQueueStructer->ArrayCurrentSize--;
		return 1;
	}
	else
		return 0;
}
//����ѭ������Ԫ�����
u8 InputQueueElement(ArraySqQueueTypeDef *ArraySqQueueStructer, u8 ReceElement)
{
    //if(IsFullQueue(ArraySqQueueStructer) != 1)        //����δ��
    if(ArraySqQueueStructer->ArrayCurrentSize < ArraySqQueueStructer->ArrayMaxSize){
		ArraySqQueueStructer->ArrayZeroAddr[ ArraySqQueueStructer->rear] = ReceElement;
        ArraySqQueueStructer->rear = (ArraySqQueueStructer->rear + 1) % ArraySqQueueStructer->ArrayMaxSize;    //βָ��ƫ�� 
		ArraySqQueueStructer->ArrayCurrentSize++;
		return 1;
    }
	else
		return 0;

}

