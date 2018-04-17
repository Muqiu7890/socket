#include<stdio.h>
#include<conio.h>
#include<winsock2.h>
#define CLS_NUM 3 
#define USER_NUM 3 
#pragma comment(lib,"ws2_32.lib")
char cls[USER_NUM][CLS_NUM+1][70]={{"平均分：80","高数 80","线代 80","英语 80"},{"平均分：90","高数 90","线代90","英语 90"}};
char user[USER_NUM][2][50]={{"xiaohong","11111"},{"xiaoming","55555"},{"xiaogang","99999"}};
int usern=0;
int main ()
{
	printf("成绩查询系统 服务器\n");
	 
	 WSAData wsaData;
	 if(WSAStartup(MAKEWORD(2,2),&wsaData))// WSAStartup()加载套接字库，创建套接字 
	 {
	 	printf("初始化错误\n");
	 	return 1;
	 }
	 	printf("初始化成功\n"); //初始化 

	 
	 SOCKET sockSrv;
	 sockSrv=socket(AF_INET,SOCK_STREAM,0);//IPv4，类型，protocol
	 if(sockSrv==SOCKET_ERROR)
	 {
	 	printf("建立套接字错误\n");
	 	return 2;
	 }
	printf("Socket created.\n");//建立套接字 

	 SOCKADDR_IN addrSrv;
	 addrSrv.sin_addr.s_addr=inet_addr("127.0.0.1");//地址 
	 addrSrv.sin_family=AF_INET;
	 addrSrv.sin_port=htons(8888);//端口号 
	 bind(sockSrv,(SOCKADDR*)&addrSrv,sizeof(SOCKADDR));//绑定
	  
	listen(sockSrv,5);//监听 
	
	printf("成功建立监听\n");
    
    SOCKADDR_IN addrClient;
    int len=sizeof(SOCKADDR);
    while(1)
    {
    	int i;
    	SOCKET sockConn=accept(sockSrv,(SOCKADDR*)&addrClient,&len);//请求到来后，接受连接请求，返回一个新的对应于此次连接的套接字（accept()）
    	char sendBuf[50];
    	char recvBuf[50];
    	while(strcmp(recvBuf,"BYE"))
    	{
    		ed:if(recv(sockConn,recvBuf,50,0)==SOCKET_ERROR)//recv获取消息内容 
    		{
    			strcpy(recvBuf,"BYE");
			}
		
		
		    if(!strcmp(recvBuf,"LOGIN"))
		    {
			    //printf("LOGIN\n");
			    recv(sockConn,recvBuf,50,0);//用返回的套接字和客户端进行通信
			    int flag=0;
			    for(int i=0;i<USER_NUM;i++)
			    {
				    if(!strcmp(recvBuf,user[i][0]))
				    {
					   flag=1;
					   usern=i;
				    }
			    }
			    if(flag==0)
			    {
				    send(sockConn,"1",strlen("1")+1,0);
				    printf("无此用户\n");
				    goto ed;
			    }else
			    {
				    send(sockConn,"0",strlen("0")+1,0);
					printf("用户存在\n");
			    }
			    recv(sockConn,recvBuf,50,0);
			    if(strcmp(recvBuf,user[usern][1]))
			    {
				    send(sockConn,"1",strlen("1")+1,0);
				    printf("密码错误\n");
				    goto ed;	
			    }else
			    {
				     send(sockConn,"0",strlen("0")+1,0);
				     printf("密码正确\n");
			    }
			    printf("成功登陆\n");
		    }else if(!strcmp(recvBuf,"QUERY"))//成绩查询 
		        {
			       printf("%s\n",recvBuf);
			       recv(sockConn,recvBuf,50,0);
			       int tem=atoi(recvBuf);
			       if(tem>3||tem<1)
			       {
				   send(sockConn,"无此课程，请查询",strlen("无此课程，请查询")+1,0);
				   printf("课程错误或没选\n");
				   goto ed; 
			       }
			       send(sockConn,cls[usern][tem],strlen(cls[usern][tem])+1,0);
			      // printf("QUERY SUCCESS\n");
		        }else if(!strcmp(recvBuf,"QUERYAVG"))
		             {
			            printf("%s\n",recvBuf);
			           send(sockConn,cls[usern][0],strlen(cls[usern][0])+1,0);
			            //printf("QUERYAVG SUCCESS\n");
		             }else{
			                 printf("%s\n",recvBuf);
		                  }
	    }
	    recv(sockConn,recvBuf,50,0);
	    closesocket(sockConn);//关闭SOCKET 
    }
}

