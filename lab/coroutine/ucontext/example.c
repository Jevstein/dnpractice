/*
 *  example.c 
 *  example
 *
 *  Created by Jevstein on 2018/11/11 14:44.
 *  Copyright @ 2018year Jevstein. All rights reserved.
 *
 *  �ο�: https://blog.csdn.net/qq910894904/article/details/41911175
 *
 *  ���ĺ���:
 *    //��ʼ��ucp�ṹ�壬����ǰ�������ı��浽ucp��
 *    int getcontext(ucontext_t *ucp);
 *
 *    //���õ�ǰ��������Ϊucp��setcontext��������ucpӦ��ͨ��getcontext����makecontext
 *      ȡ�ã�������óɹ��򲻷���
 *    int setcontext(const ucontext_t *ucp);
 *
 *    //�޸�ͨ��getcontextȡ�õ�������ucp(����ζ�ŵ���makecontextǰ�����ȵ���getcontext),
 *      Ȼ�����������ָ��һ��ջ�ռ�ucp->stack�����ú�̵�������ucp->uc_link
 *    void makecontext(ucontext_t *ucp, void (*func)(), int argc, ...);
 *
 *    //���浱ǰ�����ĵ�oucp�ṹ���У�Ȼ�󼤻�upc�����ġ�
 *    int swapcontext(ucontext_t *oucp, ucontext_t *ucp);
 */
#include <stdio.h>
#include <ucontext.h>
#include <unistd.h>

void context_func1()
{
	ucontext_t context;

	puts("flag1");//ִ��1��

	getcontext(&context);
	puts("flag2");//ѭ��ִ��
	sleep(1);
	setcontext(&context);

	puts("flag3");//����ִ��
}

void child_func(void * arg)
{
	puts("1");
	puts("11");
	puts("111");
	puts("1111");
}

void context_func2()
{
	char stack[1024 * 128];
	ucontext_t child, main;

	puts("flag1");
	getcontext(&child); //��ȡ��ǰ������
	child.uc_stack.ss_sp = stack;//ָ��ջ�ռ�
	child.uc_stack.ss_size = sizeof(stack);//ָ��ջ�ռ��С
	child.uc_stack.ss_flags = 0;
	child.uc_link = &main;//���ú��������
	//child.uc_link = NULL;//�޺�������ģ������"flag_main"

	puts("flag2");
	makecontext(&child, (void(*)(void))child_func, 0);//�޸�������ָ��child_func����

	puts("flag3");
	swapcontext(&main, &child);//�л���child�����ģ����浱ǰ�����ĵ�main

	puts("flag_main");//��������˺�������ģ�func1����ָ�����᷵�ش˴�
}

int main(int argc, const char *argv[]){
	printf("========= ucontext test =========\n");

#if 0
	context_func1();
#else
	context_func2();
#endif

	printf("========= the end =========\n");

	return 0;
}

//complie:
// $ g++ -o ../../../bin/ucontext_example example.c