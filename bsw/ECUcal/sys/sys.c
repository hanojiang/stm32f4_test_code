#include "sys.h"  
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ���������ɣ��������������κ���;
//ALIENTEK STM32F407������
//ϵͳʱ�ӳ�ʼ��	
//����ʱ������/�жϹ���/GPIO���õ�
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2014/5/2
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) �������������ӿƼ����޹�˾ 2014-2024
//All rights reserved
//********************************************************************************
//�޸�˵��
//��
//////////////////////////////////////////////////////////////////////////////////  


//THUMBָ�֧�ֻ������
// //�������·���ʵ��ִ�л��ָ��WFI  
void WFI_SET(void)
{
	__asm volatile("WFI");		  
}
//�ر������ж�(���ǲ�����fault��NMI�ж�)
void INTX_DISABLE(void)
{
	__asm volatile("CPSID I");
	__asm volatile("BX LR");  
}
//���������ж�
void INTX_ENABLE(void)
{
	__asm volatile("CPSIE I");
	__asm volatile("BX LR");
}
//����ջ����ַ
//addr:ջ����ַ
void MSR_MSP(u32 addr) 
{
	__asm volatile("MSR MSP, r0");		//set Main Stack value
	__asm volatile("BX r14");
}
















