#include<stdio.h>
#include<stdlib.h>
#include<ctype.h> 
#include <string.h>
#include <windows.h>
//����ȫ�ֱ��� 
int Authority=-1;//ֵΪ1Ϊ��ͨ�û���Ϊ2Ϊ����Ա�˻� 
//��������
int CheckInputNumber(char *Input);
int IndexPage();
int LoginConfirm();
void LoginReset();
int ChangePassword(int Number);
int CreatAccount();
int ReadAccount();
int DelUser(int Number);


//Public Section 

int CheckInputNumber(char *Input)//ȷ��ȫ��Ϊ���ֺ󷵻����ֵ�intֵ�����򷵻�-1 
{
	int Output=0,LengthInput=0,Count=0;
	if(isdigit(*Input)==0)
	{
		return -1;
	}else
	return atoi(Input);
}

//The main Page

int main()
{ 
	if(LoginConfirm()==1)
	{
		Authority=0;
	}else
	if(LoginConfirm()==2)
	{
		Authority=1;
	}
	printf("%d",Authority) ;
	LoginReset();
	for(;;)
	{
		IndexPage();
	}
 } 
int IndexPage()
{
	ReadPress(); 
	ReadBookInf();
	system("cls");
	char Input='\0';
	printf(" ########################################################################################\n");
	printf(" ######################################ͼ�����ϵͳ######################################\n");
	printf(" ########################################################################################\n\n");
	printf("                                    ����<1>�Թ���ͼ��                   \n\n");
	printf("                                  ����<2>�鿴ͼ�������               \n\n");
	printf("                                  ����<3>�����߽��в�ѯ                  \n\n");
	printf("                                  ����<4>���������в�ѯ                  \n\n");
	printf("                                   ����<5>�鿴ͼ���б�               \n\n");
	printf("                                   ����<6>����ͼ������                \n\n");
	printf("                                     ����<7>�����˻�                    \n\n");
	printf("                                   ����<8>�˳�����ϵͳ                   \n\n");
	printf("########################################################################################\n\n");
	printf("\n\n��������Ҫ���еĲ�����") ;
	scanf("%1s",&Input);
	if(Input=='1'){system("cls");ManageBookInf();}else
	if(Input=='2'){system("cls");ManagePressInf();}else
	if(Input=='3'){system("cls");QueryWriter();}else
	if(Input=='4'){system("cls");QueryBookName();}else
	if(Input=='5'){system("cls");ShowBookInf();RankBookInf();}else
	if(Input=='6'){system("cls");OutputExcel();}else
	if(Input=='7'){system("cls");ReadAccount();}
	if(Input=='8'){exit(0);}else{system("cls");IndexPage();}
}

 //Login section
 
int LoginConfirm()
{
	char input[1000]="";
	FILE *fp=fopen("softwaretranspot.ini","rb");
	if(!fp)
	{
		fclose(fp);
		exit(1);
	}
	while(!feof(fp))
	{
		fscanf(fp,"%s",input);
		if(input[0]=='0'&&input[1]=='0')
		{
			fclose(fp);
			return 1;
		}else
		if(input[0]=='1'&&input[1]=='1')
		{
			fclose(fp);
			return 2;
		}else
		fclose(fp);
		exit(1);
	}
	return 0;
}
void LoginReset()
{
	system("del softwaretranspot.ini");
	system("del Restart.bat"); 
}
//Account section
int ChangePassword(int Number)
{
	int LengthText=0,Count=0,CountUser=0,CountPassword=0,ForCount1=0,ForCount2=0,Type=0,Count1=0,Count2=0,Count3=0;
	printf("��������˻���������(����Ϊ6-15)��");
	char AccountText[20000]={""},AccountUser[1000][20]={""},AccountPassword[1000][20]={""},InputPassword[20]={""};
	scanf("%17s",InputPassword);
	FILE *fp=fopen("logFile.dat","rb");
	if(!fp)
	{
		fclose(fp);
		printf("Ȩ��ϵͳ�������⣬���������ã�");
		system("pause");
		IndexPage();
	}
		while(!feof(fp))
	{
		fscanf(fp,"%s",AccountText);
	}
	fseek(fp,0,SEEK_SET);
	fseek(fp,0,SEEK_END);
	LengthText=ftell(fp);
	fclose(fp);
	for(;Count<=LengthText;Count++)
	{
		if(AccountText[Count]=='*')
		{
			Type=0;
			ForCount1=0;
			Count1++;
			Count++;
		}
		if(AccountText[Count]=='#')
		{
			Type=1;
			ForCount2=0;
			Count2++;
			Count++;
		}
		if(Type==0)
		{
			AccountUser[Count1-1][ForCount1]=AccountText[Count];
			ForCount1++;
		}
		if(Type==1)
		{
			AccountPassword[Count2][ForCount2]=AccountText[Count];
			ForCount2++;
		}
	}
	fclose(fp);
	system("del softwaretranspot.ini");
	FILE *rfp=fopen("logFile.dat","wt+");
	if(!rfp)
	{
		fclose(rfp);
		printf("Ȩ��ϵͳ�������⣬���������ã�");
		system("pause");
		IndexPage();
	}
	fprintf(rfp,"*");
	for(Count3=1;Count3<Count1;Count3++)
	{
		if(AccountUser[Count3-1]=="")
		{
			continue;
		}
		if((Count3-1)==Number)
		{
			strcpy(AccountPassword[Count3],InputPassword);
		}
		fprintf(rfp,"%s#%s*",AccountUser[Count3-1],AccountPassword[Count3]);
	}
	fclose(rfp);
	ReadAccount();
}
int CreatAccount()
{
	char Username[20]={""},Password[30]={""};
	FILE *fp=fopen("logFile.dat","a");
	if(!fp)
	{
		fclose(fp);
		printf("Ȩ��ϵͳ�������⣬���������ã�");
		system("pause");
		IndexPage();
	}
	system("cls");
	printf("�������µ��û���(����3-10λ)��");
	scanf("%15s",Username);
	printf("�������µ�����(����6-15λ)��");
	scanf("%17s",Password);
	fprintf(fp,"%s#%s*",Username,Password);
	printf("�����ɹ���");
	fclose(fp);
	system("pause"); 
	ReadAccount(); 
}
int DelUser(int Number)
{
	int LengthText=0,Count=0,CountUser=0,CountPassword=0,ForCount1=0,ForCount2=0,Type=0,Count1=0,Count2=0,Count3=0;
	char AccountText[20000]={""},AccountUser[1000][20]={""},AccountPassword[1000][20]={""};
	FILE *fp=fopen("logFile.dat","rb");
	if(!fp)
	{
		fclose(fp);
		printf("Ȩ��ϵͳ�������⣬���������ã�");
		system("pause");
		IndexPage();
	}
		while(!feof(fp))
	{
		fscanf(fp,"%s",AccountText);
	}
	fseek(fp,0,SEEK_SET);
	fseek(fp,0,SEEK_END);
	LengthText=ftell(fp);
	fclose(fp);
	for(;Count<=LengthText;Count++)
	{
		if(AccountText[Count]=='*')
		{
			Type=0;
			ForCount1=0;
			Count1++;
			Count++;
		}
		if(AccountText[Count]=='#')
		{
			Type=1;
			ForCount2=0;
			Count2++;
			Count++;
		}
		if(Type==0)
		{
			AccountUser[Count1-1][ForCount1]=AccountText[Count];
			ForCount1++;
		}
		if(Type==1)
		{
			AccountPassword[Count2][ForCount2]=AccountText[Count];
			ForCount2++;
		}
	}
	fclose(fp);
	system("del softwaretranspot.ini");
	FILE *rfp=fopen("logFile.dat","wt+");
	if(!rfp)
	{
		fclose(rfp);
		printf("Ȩ��ϵͳ�������⣬���������ã�");
		system("pause");
		IndexPage();
	}
	fprintf(rfp,"*");
	for(Count3=1;Count3<Count1;Count3++)
	{
		if(AccountUser[Count3-1]=="")
		{
			continue;
		}
		if((Count3-1)==Number)
		{
			continue;
		}
		fprintf(rfp,"%s#%s*",AccountUser[Count3-1],AccountPassword[Count3]);
	}
	fclose(rfp);
	ReadAccount();
}
int ReadAccount()
{
	if(Authority!=1)
	{
		printf("���Ȩ�޲��㣬�޷����Ĵ����ã�");
		system("pause");
		IndexPage();
	}
	int LengthText=0,Count=0,CountUser=0,CountPassword=0,ForCount1=0,ForCount2=0,Type=0,Count1=0,Count2=0;
	char AccountText[20000]={""},AccountUser[1000][20]={""},AccountPassword[1000][20]={""};
	FILE *fp=fopen("logFile.dat","r");
	if(!fp)
	{
		fclose(fp);
		printf("Ȩ��ϵͳ�������⣬���������ã�");
		system("pause");
		IndexPage();
	}
		while(!feof(fp))
	{
		fscanf(fp,"%s",AccountText);
	}
	fseek(fp,0,SEEK_SET);
	fseek(fp,0,SEEK_END);
	LengthText=ftell(fp);
	fclose(fp);
	for(;Count<=LengthText;Count++)
	{
		if(AccountText[Count]=='*')
		{
			Type=0;
			ForCount1=0;
			Count1++;
			Count++;
		}
		if(AccountText[Count]=='#')
		{
			Type=1;
			ForCount2=0;
			Count2++;
			Count++;
		}
		if(Type==0)
		{
			AccountUser[Count1-1][ForCount1]=AccountText[Count];
			ForCount1++;
		}
		if(Type==1)
		{
			AccountPassword[Count2][ForCount2]=AccountText[Count];
			ForCount2++;
		}
	}
	int a=1,b=0,retnumber=0,OperateType=0;
	char number[4]={""},Operate[2]={""},InputType='\0';
	printf("\n\n\t\t\t#####################################################\n");
	printf("\t\t\t################### �� �� �� �� #####################\n");
	printf("\t\t\t#####################################################\n");
	printf("\n\t\t\t     ���                  �û���        ����");
	for(;a<=(Count1-1);a++,b++)
	{
		printf("\n\t\t\t    �� �� %d����������������%s        %s",a,AccountUser[b],AccountPassword[a]);
		if(AccountUser[b]==""||AccountPassword[a]=="")
		{
			break;
		}
	}
	printf("\n\n\t\t\t#####################################################\n\n\n\n");
	printf("����<a>����ĳ���˻�����\t����<b>����˻�\t����<c>����������\n\n");
	scanf("%1s",&InputType);
	if(InputType=='a')
	{
	printf("������һ���˻���ţ����س����и���:");
	for(;;)
	{
		scanf("%3s",number);
		retnumber=CheckInputNumber(number);  
		if(retnumber>(a))
		{
			printf("��Ǹ��û�и��˺�\n");
			system("pause"); 
			ReadAccount();
		}
		if(retnumber>=0)
	{
			break;
	}
	}
	system("cls");
	printf("��ѡ����˻���Ϊ��%s\n\n\n\n\n\t\t\t\t#####################################\n\n\t\t\t\t\t����<1>���ĸ��˻�������\n\t\t\t\t\t����<2>ɾ�����˻�\n\t\t\t\t\t����<3>���ع������\n\n\t\t\t\t#####################################\n",AccountUser[retnumber-1]);
	printf("\n\n��������Ҫ���еĲ���:");
	scanf("%1s",Operate); 
	if(Operate[0]=='1'){ChangePassword(retnumber-1);}else
	if(Operate[0]=='2'){DelUser(retnumber-1);}else
	if(Operate[0]=='3'){ReadAccount();}else{ReadAccount();}
	}else
	if(InputType=='b')
	{
		CreatAccount();
	}else
	if(InputType=='c')
	{
		IndexPage();
	}else
	{
		system("cls");
		ReadAccount();
	}
}
void Restart()
{
	FILE *fp=fopen("softwaretranspot.ini","a");
	if(!fp)
	{
		fclose(fp);
		exit(1);
	}
	if(Authority==1)
	{
		fprintf(fp,"00");
	}else
	if(Authority==2)
	{
		fprintf(fp,"11");
	}
	fclose(fp);
	system("del Restart.bat");
	FILE *fp1=fopen("Restart.bat","a");
	if(!fp1)
	{
		fclose(fp1);
		exit(1);
	}
	fprintf(fp1,"taskkill /im TGProm.exe /f\nstart TGProm.exe\nexit");
	fclose(fp1);
	system("start Restart.bat");
}

