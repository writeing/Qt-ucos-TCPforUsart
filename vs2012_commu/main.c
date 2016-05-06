#include <includes.h>
#include <winsock.h>
#include <stdio.h>
/*
*********************************************************************************************************
*                                                CONSTANTS
*********************************************************************************************************
*/

#define  TASK_STK_SIZE    1024
#define  TASK_START_PRIO    5
#pragma comment(lib, "ws2_32.lib") 
/*
*********************************************************************************************************
*                                                VARIABLES
*********************************************************************************************************
*/

OS_STK        AppStartTaskStk[10][TASK_STK_SIZE];

OS_EVENT *MainBox;


SOCKET sclient;
struct sockaddr_in sin;
struct sockaddr_in remoteAddr;  
int len;
int revRet;
char recvData[255];  

/*
*********************************************************************************************************
*                                            FUNCTION PROTOTYPES
*********************************************************************************************************
*/

static  void  AppStartTask(void *p_arg);
static  void test2(void *pdata);
static void test3(void *pdate);

static void getStr(void *pdate);

void sendStr();
void sysinit(void);
#if OS_VIEW_MODULE > 0
static  void  AppTerminalRx(INT8U rx_data);
#endif

/*
*********************************************************************************************************
*                                                _tmain()
*
* Description : This is the standard entry point for C++ WIN32 code.  
* Arguments   : none
*********************************************************************************************************
*/

void main(int argc, char *argv[])
{
	INT8U  err;


#if 0
    BSP_IntDisAll();                       /* For an embedded target, disable all interrupts until we are ready to accept them */
#endif

    OSInit();                              /* Initialize "uC/OS-II, The Real-Time Kernel"                                      */
	sysinit();
	OSTaskCreate(AppStartTask,(void *)0,(OS_STK *)&AppStartTaskStk[0][TASK_STK_SIZE-1],2);
	OSTaskCreate(test2,		  (void *)0,(OS_STK *)&AppStartTaskStk[1][TASK_STK_SIZE-1],3);
	OSTaskCreate(test3,		  (void *)0,(OS_STK *)&AppStartTaskStk[2][TASK_STK_SIZE-1],4);
	OSTaskCreate(getStr,	  (void *)0,(OS_STK *)&AppStartTaskStk[3][TASK_STK_SIZE-1],5);

#if OS_TASK_NAME_SIZE > 11
    OSTaskNameSet(APP_TASK_START_PRIO, (INT8U *)"Start Task", &err);
#endif

#if OS_TASK_NAME_SIZE > 14
    OSTaskNameSet(OS_IDLE_PRIO, (INT8U *)"uC/OS-II Idle", &err);
#endif

#if (OS_TASK_NAME_SIZE > 14) && (OS_TASK_STAT_EN > 0)
    OSTaskNameSet(OS_STAT_PRIO, "uC/OS-II Stat", &err);
#endif

    OSStart();                             /* Start multitasking (i.e. give control to uC/OS-II)                               */
}
void init()
{
	WORD socketVersion = MAKEWORD(2,2);
	WSADATA wsaData; 
	if(WSAStartup(socketVersion, &wsaData) != 0)
	{
		return ;
	}
}
void sysinit()
{
	init();
	sclient = socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
	sin.sin_family = AF_INET;
	sin.sin_port = htons(8888);
	sin.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	len = sizeof(sin);
	bind(sclient, (struct sockaddr *)&sin, sizeof(sin));
	//sendto(sclient,sendData,strlen(sendData),0,(sockaddr *)&sin,len);
}



void  AppStartTask (void *p_arg)
{
    p_arg = p_arg;
    while (TRUE)                                 /* Task body, always written as an infinite loop.                             */
	{       		
	//	OS_Printf("Delay 1 second and print\n");  /* your code here. Create more tasks, etc.                                    */
        OSTimeDlyHMSM(0, 0, 1, 0);       
    }
}

void test2(void *pdata)
{

	pdata = pdata;
	while(TRUE)
	{
	
		OSTimeDlyHMSM(0, 0, 2, 0); 
	}	
}

void test3(void *pdata)
{
	//char *msg;
	//msg = (char *)malloc(sizeof(char));
	char buf[10]="0";
	pdata = pdata;
	
	while(TRUE)
	{		
		memset(buf,'A',sizeof(buf)-1);
		sendStr(buf);
		OSTimeDlyHMSM(0, 0, 1, 0); 

	}
}

void sendStr(char *pdate)
{	
	int addlen = sizeof(remoteAddr);
	pdate = pdate;
	
	printf("%d\n",sendto(sclient,pdate,strlen(pdate),0,(PSOCKADDR)&remoteAddr,addlen));
}
void getStr(void *pdate)
{	  	
	int addlen = sizeof(remoteAddr);
	pdate = pdate;
	while (1)
	{		   
		revRet = recvfrom(sclient, recvData, 255, 0,(PSOCKADDR)&remoteAddr, &addlen);
		if(revRet > 0)  
		{  
			recvData[revRet] = 0x00; 
			printf("%s\n",recvData);  
		}  
		revRet = 0;
		memset(recvData,'\0',sizeof(recvData));
		OSTimeDlyHMSM(0, 0, 0, 100);
	}	
}