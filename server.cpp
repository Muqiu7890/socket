#include<stdio.h>
#include<conio.h>
#include<winsock2.h>
#define CLS_NUM 3 
#define USER_NUM 3 
#pragma comment(lib,"ws2_32.lib")
char cls[USER_NUM][CLS_NUM+1][70]={{"ƽ���֣�80","���� 80","�ߴ� 80","Ӣ�� 80"},{"ƽ���֣�90","���� 90","�ߴ�90","Ӣ�� 90"}};
char user[USER_NUM][2][50]={{"xiaohong","11111"},{"xiaoming","55555"},{"xiaogang","99999"}};
int usern=0;
int main ()
{
	printf("�ɼ���ѯϵͳ ������\n");
	 
	 WSAData wsaData;
	 if(WSAStartup(MAKEWORD(2,2),&wsaData))// WSAStartup()�����׽��ֿ⣬�����׽��� 
	 {
	 	printf("��ʼ������\n");
	 	return 1;
	 }
	 	printf("��ʼ���ɹ�\n"); //��ʼ�� 

	 
	 SOCKET sockSrv;
	 sockSrv=socket(AF_INET,SOCK_STREAM,0);//IPv4�����ͣ�protocol
	 if(sockSrv==SOCKET_ERROR)
	 {
	 	printf("�����׽��ִ���\n");
	 	return 2;
	 }
	printf("Socket created.\n");//�����׽��� 

	 SOCKADDR_IN addrSrv;
	 addrSrv.sin_addr.s_addr=inet_addr("127.0.0.1");//��ַ 
	 addrSrv.sin_family=AF_INET;
	 addrSrv.sin_port=htons(8888);//�˿ں� 
	 bind(sockSrv,(SOCKADDR*)&addrSrv,sizeof(SOCKADDR));//��
	  
	listen(sockSrv,5);//���� 
	
	printf("�ɹ���������\n");
    
    SOCKADDR_IN addrClient;
    int len=sizeof(SOCKADDR);
    while(1)
    {
    	int i;
    	SOCKET sockConn=accept(sockSrv,(SOCKADDR*)&addrClient,&len);//�������󣬽����������󣬷���һ���µĶ�Ӧ�ڴ˴����ӵ��׽��֣�accept()��
    	char sendBuf[50];
    	char recvBuf[50];
    	while(strcmp(recvBuf,"BYE"))
    	{
    		ed:if(recv(sockConn,recvBuf,50,0)==SOCKET_ERROR)//recv��ȡ��Ϣ���� 
    		{
    			strcpy(recvBuf,"BYE");
			}
		
		
		    if(!strcmp(recvBuf,"LOGIN"))
		    {
			    //printf("LOGIN\n");
			    recv(sockConn,recvBuf,50,0);//�÷��ص��׽��ֺͿͻ��˽���ͨ��
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
				    printf("�޴��û�\n");
				    goto ed;
			    }else
			    {
				    send(sockConn,"0",strlen("0")+1,0);
					printf("�û�����\n");
			    }
			    recv(sockConn,recvBuf,50,0);
			    if(strcmp(recvBuf,user[usern][1]))
			    {
				    send(sockConn,"1",strlen("1")+1,0);
				    printf("�������\n");
				    goto ed;	
			    }else
			    {
				     send(sockConn,"0",strlen("0")+1,0);
				     printf("������ȷ\n");
			    }
			    printf("�ɹ���½\n");
		    }else if(!strcmp(recvBuf,"QUERY"))//�ɼ���ѯ 
		        {
			       printf("%s\n",recvBuf);
			       recv(sockConn,recvBuf,50,0);
			       int tem=atoi(recvBuf);
			       if(tem>3||tem<1)
			       {
				   send(sockConn,"�޴˿γ̣����ѯ",strlen("�޴˿γ̣����ѯ")+1,0);
				   printf("�γ̴����ûѡ\n");
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
	    closesocket(sockConn);//�ر�SOCKET 
    }
}

