
#include "SqQueue.h"

void ArraySqQueueInit(ArraySqQueueTypeDef *ArraySqQueueStructer,u8 *buf,SqQueueTypeDef bufMaxSize)
{
	ArraySqQueueStructer->ArrayZeroAddr = buf;
	ArraySqQueueStructer->front = 0;
	ArraySqQueueStructer->rear = 0;
	ArraySqQueueStructer->ArrayMaxSize = bufMaxSize;
	ArraySqQueueStructer->ArrayCurrentSize = 0;
}

////数组循坏队列判空
//u8 IsEmptyQueue(ArraySqQueueTypeDef *ArraySqQueueStructer)
//{
//	return (ArraySqQueueStructer->front == ArraySqQueueStructer->rear) ? 1 : 0;
//}

////数组循坏队列判满
//u8 IsFullQueue(ArraySqQueueTypeDef *ArraySqQueueStructer)
//{
//	return ((ArraySqQueueStructer->rear + 1) % ArraySqQueueStructer->ArrayMaxSize == ArraySqQueueStructer->front) ? 1 : 0;
//}

//数组循坏队列元素出队
u8 OutputQueueElement(ArraySqQueueTypeDef *ArraySqQueueStructer, u8 *ReceElement)
{
	//if(IsEmptyQueue(ArraySqQueueStructer) != 1)        //队列未空
	if(ArraySqQueueStructer->ArrayCurrentSize > 0){
       *ReceElement = ArraySqQueueStructer->ArrayZeroAddr[ArraySqQueueStructer->front] ;
		
		ArraySqQueueStructer->front = (ArraySqQueueStructer->front + 1) % ArraySqQueueStructer->ArrayMaxSize;
		
		ArraySqQueueStructer->ArrayCurrentSize--;
		return 1;
	}
	else
		return 0;
}
//数组循坏队列元素入队
u8 InputQueueElement(ArraySqQueueTypeDef *ArraySqQueueStructer, u8 ReceElement)
{
    //if(IsFullQueue(ArraySqQueueStructer) != 1)        //队列未满
    if(ArraySqQueueStructer->ArrayCurrentSize < ArraySqQueueStructer->ArrayMaxSize){
		ArraySqQueueStructer->ArrayZeroAddr[ ArraySqQueueStructer->rear] = ReceElement;
        ArraySqQueueStructer->rear = (ArraySqQueueStructer->rear + 1) % ArraySqQueueStructer->ArrayMaxSize;    //尾指针偏移 
		ArraySqQueueStructer->ArrayCurrentSize++;
		return 1;
    }
	else
		return 0;

}

