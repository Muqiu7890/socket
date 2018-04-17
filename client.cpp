#include<stdio.h>
#include<conio.h>
#include<winsock2.h>
#pragma comment(lib,"ws2_32.lib")
#define MAX_PWD_LEN 32
#define MAX_USN_LEN 32
char username[MAX_USN_LEN];
char password[MAX_PWD_LEN];
SOCKET sockClient;
char recvn[50];//缓存区 
int connect(char *SrvIP,int SrvPort)
{
	WSADATA wsaData;
	if(WSAStartup(MAKEWORD(2,2),&wsaData))
	{
		
		printf("初始化错误\n");
		return 1;
	} else
	printf("初始化成功\n"); //初始化 
	
	sockClient=socket(AF_INET,SOCK_STREAM,0);
	if(sockClient==SOCKET_ERROR)
	{
		printf("建立套接字错误\n");
		return 0; 
	} else
	printf("Socket created.\n");//建立socket 

	SOCKADDR_IN addrSrv;
    addrSrv.sin_addr.s_addr=inet_addr(SrvIP);//ip 
	addrSrv.sin_family=AF_INET;
	addrSrv.sin_port=htons(SrvPort);//端口 
	
	if(connect(sockClient,(SOCKADDR*)&addrSrv,sizeof(SOCKADDR)) == -1)//发送连接请求到服务端 
	{
		printf("连接服务器失败\n");
		return 3;
	} else
	printf("成功连接到服务器\n\n");
	
	send(sockClient,"CONNECT",strlen("CONNECT")+1,0);//和服务端进行通信 
	return 0;
		
	 }
	  
	 void getspwd(char *pwdin)//用户输入密码 
	 {
	 	
	 	char ctemp;
	 	int itemp=0;
	 	printf("密码："); 
	 	while((ctemp=getch())!='\r')
	 	{
	 		
	 		printf("*");
	 		pwdin[itemp]=ctemp;
	 		itemp++;
		 }
		 pwdin[itemp]=0;
		 printf("\n");
	 }
	 
	 int login(char *username)//登陆 
	 {
	 	send(sockClient,"LOGIN",strlen("LOGIN")+1,0);
	 	send(sockClient,username,strlen(username)+1,0);
	 	recv(sockClient,recvn,50,0);
	 	if(!strcmp(recvn,"1"))
	 	{
	 		printf("无此用户\n");
	 		return 1;
	 		
		 }
		 getspwd(password);
		 send(sockClient,password,strlen(password)+1,0);
		 recv(sockClient,recvn,50,0);
		 if(!strcmp(recvn,"1"))
		 {
		 	printf("密码错误\n");
		 	return 2;
		 }
		 printf("注册成功\n");
		 return 0;
	 }
	 
	 int query(char *clsnum)//成绩查询 
	 {
	 	send(sockClient,"QUERY",strlen("QUERY")+1,0);//send 发送消息 
	 	send(sockClient,clsnum,strlen(clsnum)+1,0);
	 	recv(sockClient,recvn,50,0);
	 	printf("%s\n",recvn);
	 	return 0;
	 }
	 
	 int queryavg()//平均分 
	 {
	 	send(sockClient,"QUERYAVG",strlen("QUERYAVG")+1,0);
	 	recv(sockClient,recvn,50,0);
	 	printf("%s\n",recvn);
	 	return 0;	
	 }
	 
	 int bye()//关闭 
	 {
	 	send(sockClient,"BYE",strlen("BYE")+1,0);
	 	closesocket(sockClient);
	 	WSACleanup();
	 	exit(0);
	 }
	 
  int main()
	 {
	 	printf("成绩查询系统 客户机\n");
	 	while(1)
	 	{
	 		char com[100];
	 		char option[20]={0};//指令 
	 		char contxt[5][32]={0};//内容 
	 		gets(com);
	 		int i=0,j=0,k=0;
	 		while(com[i]!=0)
	 		{
	 			while(com[i]!=' ')
	 			{
	 				option[i]=com[i];//获取指令 
					 i++;
				 }
	 			i++;
	 			while(com[i]!=0)
	 			{
	 				while(com[i]==' ')
	 				{
	 					j++;
	 					k=0;
	 					i++;
					 }
					 contxt[j][k]=com[i];//获取指令后的内容 
					 i++;
					 k++;
				 }
	
			 }
			 if(!strcmp(option,"CONNECT"))
			 {
			 	int portn=atoi(contxt[1]);
			 	if(connect(contxt[0],portn))
			 	{
			 		getchar();
			 		exit(1);
			 	}
				 
			 }else if(!strcmp(option,"LOGIN"))
			 {
				login(contxt[0]); 
				}else if(!strcmp(option,"QUERY"))
			 {
			 	query(contxt[0]);
			 }else if(!strcmp(option,"QUERYAVG"))
			 {  
			    queryavg();
		    }else if(!strcmp(option,"BYE"))
		    {
		    	bye();
			}
			
		 }
		 return 0;
  }
 
 
