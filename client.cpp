#include<stdio.h>
#include<conio.h>
#include<winsock2.h>
#pragma comment(lib,"ws2_32.lib")
#define MAX_PWD_LEN 32
#define MAX_USN_LEN 32
char username[MAX_USN_LEN];
char password[MAX_PWD_LEN];
SOCKET sockClient;
char recvn[50];//������ 
int connect(char *SrvIP,int SrvPort)
{
	WSADATA wsaData;
	if(WSAStartup(MAKEWORD(2,2),&wsaData))
	{
		
		printf("��ʼ������\n");
		return 1;
	} else
	printf("��ʼ���ɹ�\n"); //��ʼ�� 
	
	sockClient=socket(AF_INET,SOCK_STREAM,0);
	if(sockClient==SOCKET_ERROR)
	{
		printf("�����׽��ִ���\n");
		return 0; 
	} else
	printf("Socket created.\n");//����socket 

	SOCKADDR_IN addrSrv;
    addrSrv.sin_addr.s_addr=inet_addr(SrvIP);//ip 
	addrSrv.sin_family=AF_INET;
	addrSrv.sin_port=htons(SrvPort);//�˿� 
	
	if(connect(sockClient,(SOCKADDR*)&addrSrv,sizeof(SOCKADDR)) == -1)//�����������󵽷���� 
	{
		printf("���ӷ�����ʧ��\n");
		return 3;
	} else
	printf("�ɹ����ӵ�������\n\n");
	
	send(sockClient,"CONNECT",strlen("CONNECT")+1,0);//�ͷ���˽���ͨ�� 
	return 0;
		
	 }
	  
	 void getspwd(char *pwdin)//�û��������� 
	 {
	 	
	 	char ctemp;
	 	int itemp=0;
	 	printf("���룺"); 
	 	while((ctemp=getch())!='\r')
	 	{
	 		
	 		printf("*");
	 		pwdin[itemp]=ctemp;
	 		itemp++;
		 }
		 pwdin[itemp]=0;
		 printf("\n");
	 }
	 
	 int login(char *username)//��½ 
	 {
	 	send(sockClient,"LOGIN",strlen("LOGIN")+1,0);
	 	send(sockClient,username,strlen(username)+1,0);
	 	recv(sockClient,recvn,50,0);
	 	if(!strcmp(recvn,"1"))
	 	{
	 		printf("�޴��û�\n");
	 		return 1;
	 		
		 }
		 getspwd(password);
		 send(sockClient,password,strlen(password)+1,0);
		 recv(sockClient,recvn,50,0);
		 if(!strcmp(recvn,"1"))
		 {
		 	printf("�������\n");
		 	return 2;
		 }
		 printf("ע��ɹ�\n");
		 return 0;
	 }
	 
	 int query(char *clsnum)//�ɼ���ѯ 
	 {
	 	send(sockClient,"QUERY",strlen("QUERY")+1,0);//send ������Ϣ 
	 	send(sockClient,clsnum,strlen(clsnum)+1,0);
	 	recv(sockClient,recvn,50,0);
	 	printf("%s\n",recvn);
	 	return 0;
	 }
	 
	 int queryavg()//ƽ���� 
	 {
	 	send(sockClient,"QUERYAVG",strlen("QUERYAVG")+1,0);
	 	recv(sockClient,recvn,50,0);
	 	printf("%s\n",recvn);
	 	return 0;	
	 }
	 
	 int bye()//�ر� 
	 {
	 	send(sockClient,"BYE",strlen("BYE")+1,0);
	 	closesocket(sockClient);
	 	WSACleanup();
	 	exit(0);
	 }
	 
  int main()
	 {
	 	printf("�ɼ���ѯϵͳ �ͻ���\n");
	 	while(1)
	 	{
	 		char com[100];
	 		char option[20]={0};//ָ�� 
	 		char contxt[5][32]={0};//���� 
	 		gets(com);
	 		int i=0,j=0,k=0;
	 		while(com[i]!=0)
	 		{
	 			while(com[i]!=' ')
	 			{
	 				option[i]=com[i];//��ȡָ�� 
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
					 contxt[j][k]=com[i];//��ȡָ�������� 
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
 
 
