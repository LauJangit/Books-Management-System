#include<stdio.h>
#include<windows.h>
#include<string.h>
#include <malloc.h>
#include<ctype.h>
//�ṹ��
struct _BookInf //�鱾��Ϣ
{
	char BookName[100];//����
	char Writer[50];//����
	int PressNum;//������
	char BookID[13];//���
	int Prize;//�۸�
	char IndexNum[50];//������
	int Stock;//ʣ��
	struct BookInf *Next;
}BookInf[101];//<------------------------------------��������99������ 
struct RBookInf //�鱾��Ϣ<--------------------------����ר�ýṹ�� 
	{
		char BookName[100];//����
		char Writer[50];//����
		int PressNum;//������
		char BookID[13];//���
		int Prize;//�۸�
		char IndexNum[50];//������
		int Stock;//ʣ��
	}RBookInf[101];//<------------------------------��������99������
struct _PressInf//<------------------------------��������Ϣ�ṹ�� 
{
	char PressName[100];
	int BookQuantity;
}PressInf[102];//<------------------------------------��������99������
//���뺯��
void prints(char Array[],int Num)//<---------------��������ַ�����Array[],Num��������ַ�������������ɿո��㣬�Դﵽ�����Ч�� 
{
	printf("%s",Array);
	int Length=strlen(Array),Remain=Num-Length;
	if(Remain>0)
	{
		for(;Remain>=0;Remain--)
		{
			printf(" ");
		}
	}
 } 
//������ 
void ReadPress()//��ȡ������<---------------------�ӳ������ļ��ж�ȡ��������Ϣ�������������Ϣ�ṹ���� 
{
	int Count=0,PressID=0; 
	char TMPPressID[100]={""},PressName[100]={""};
	for(;Count<=101;Count++)//��ʼ���ṹ�� 
    {
    	strcpy(PressInf[Count].PressName," ");
    	PressInf[Count].BookQuantity=0;
	}
	Count=0;
	FILE*  fp;
    fp = fopen("PressInf.db", "r");//��ʼ��ȡ�������ļ� 
    if (!fp)
    {
		printf("�ļ��򿪴���");
        return;//<-------------------------------
    }
    strcpy(PressInf[100].PressName,"����������");//�����һ����Ϊdefault�� 
    while(fscanf(fp,"%s%s",TMPPressID,PressName))//��ȡ�������ļ� 
    {
    	if(atoi(TMPPressID)==PressID){break;}
		PressID=atoi(TMPPressID);//ת��������ַ�Ϊ���� 
		strcpy(PressInf[PressID].PressName,PressName); 
	}
	fclose(fp);
}
//��ȡ����
void DevideData(char *Readchar,char *BookName,char *Writer,char *PressNum,char *BookID,char *Prize,char *IndexNum,char *Stock) 
{//<---------------------��Readchar�е����ݷֿ��� ���Ҷ�һЩ�ᵼ������Ĵ�����з��� 
	int Cnt=0,Count=0;
	if(Readchar[Cnt]!='|'){printf("\n���ݶ�ȡ��������ϵ����Ա");return;}else{Cnt++;}//<----------
	while(Readchar[Cnt]!='|'){BookName[Count]=Readchar[Cnt];Count++;Cnt++;}Count=0;Cnt++;
	while(Readchar[Cnt]!='|'){Writer[Count]=Readchar[Cnt];Count++;Cnt++;}Count=0;Cnt++;
	while(Readchar[Cnt]!='|'){PressNum[Count]=Readchar[Cnt],Count++;Cnt++;}Count=0;Cnt++;
	while(Readchar[Cnt]!='|'){BookID[Count]=Readchar[Cnt];Count++;Cnt++;}Count=0;Cnt++;
	while(Readchar[Cnt]!='|'){Prize[Count]=Readchar[Cnt];Count++;Cnt++;}Count=0;Cnt++;
	while(Readchar[Cnt]!='|'){IndexNum[Count]=Readchar[Cnt];Count++;Cnt++;}Count=0;Cnt++;
	while(Readchar[Cnt]!='|'){if(Readchar[Cnt]=='\0'){break;}Stock[Count]=Readchar[Cnt];Count++;Cnt++;}
}
void ReadBookInf ()//��ȡ�ļ� <-----------------------------���鱾�ļ��ж�ȡ�鱾��Ϣ�������鱾��Ϣ�ṹ���� 
{
	int Count=0;
	char Readchar[1000]={""},TMPPressNum[5]={""},TMPPrize[5]={""},TMPStock[5]={""};
	FILE*  fp;
    fp = fopen("BookInf.db", "r");//���ļ� 
    if (!fp)
    {
		printf("�ļ��򿪴���");
        return;//<------------------------------- 
    }
	while(fgets(Readchar,1000,fp))//<----���ļ��л�ȡ��Ϣ 
	{
		if(Count>100){break;}
		DevideData(Readchar,BookInf[Count].BookName,BookInf[Count].Writer,TMPPressNum,BookInf[Count].BookID,TMPPrize,BookInf[Count].IndexNum,TMPStock);//<--�ֿ����� ���������� 
		BookInf[Count].Stock=atoi(TMPStock);BookInf[Count].Prize=atoi(TMPPrize);BookInf[Count].PressNum=atoi(TMPPressNum);
		Count++;
	}
	fclose(fp);
}
void ShowPressInf()//<-----------------------------------��ʾ��������Ϣ 
{
	int Count=0;
	for(;Count<100;Count++)
	{
		PressInf[BookInf[Count].PressNum].BookQuantity++;//���ÿ��������ĳ���ͼ������ 
	} 
	int PressID=0;
	printf(" ########################################################################################\n");
	printf(" ##########################################������########################################\n");
	printf(" ########################################################################################\n\n");
	printf("                  ���������         ����������                ����������                        \n\n");
	for(;PressID<99;PressID++)
	{
		if(strcmp(PressInf[PressID].PressName," ")==0)//�ԱȲ鿴�ṹ�����Ƿ�����Ϣ������ޣ���������ѭ�� 
		{
			continue;
		}
		printf("                      ");
		if(PressID>=10)
    	{
    		printf("%d",PressID);
		}else
		{
			printf("%d ",PressID);
		}
		printf("           ");
		prints(PressInf[PressID].PressName,18);
		printf("             %d\n",PressInf[PressID].BookQuantity);
	}
	printf("\n ########################################################################################\n");
}
void ShowBookInf()//<-----------------------------------��ʾͼ����Ϣ 
{
	int Count=0;
	system("cls");
	printf(" ########################################################################################\n");
	printf(" ######################################����ͼ����Ϣ######################################\n");
	printf(" ########################################################################################\n\n");
	printf("             �� ��          �� ��    �� �� ��            �� ��            �۸� ����  ���\n\n");
	for(Count=0;Count<100;Count++)
	{
		if(BookInf[Count].Stock==0&&BookInf[Count].Prize==0){continue;}//�ӽṹ���л�ȡ��Ϣ������ʾ���� 
		printf("  ");prints(BookInf[Count].BookName,25);prints(BookInf[Count].Writer,8);prints(PressInf[BookInf[Count].PressNum].PressName,18);printf("ISBN");prints(BookInf[Count].BookID,13);
		printf(" ��%d ",BookInf[Count].Prize);prints(BookInf[Count].IndexNum,5);printf(" %d\n",BookInf[Count].Stock);
	}
	printf("\n ########################################################################################\n");
}
void ShowSingleBookInf(int Count)//<----------------------��ʾ��Count���ṹ���е���Ϣ
{
	printf("  ");prints(BookInf[Count].BookName,25);prints(BookInf[Count].Writer,8);prints(PressInf[BookInf[Count].PressNum].PressName,18);printf("ISBN");prints(BookInf[Count].BookID,13);
	printf(" ��%d ",BookInf[Count].Prize);prints(BookInf[Count].IndexNum,5);printf(" %d\n",BookInf[Count].Stock);
}
void AddBookInf()//<-----------------------����鱾��Ϣ 
{
	char Input[2]={""},InputName[100]={""},InputWriter[50]={""},InputBookID[20]={""},TMPPrize[20]={""},InputIndexNum[50]={""},TMPStock[20]={""},TMPPressNum[2]={""};
	int InputPrize=0,InputStock=0,InputPressNum=0,Count=0; 
	printf(" ######################################����鱾##########################################\n");
	printf(" ########################################################################################\n\n");
	printf(" ������õ�������:");
	scanf("%100s",InputName); 
	printf(" ������õ������������:");
	scanf("%50s",InputWriter); 
	printf(" ������õ�������:");
	printf(" ISBN ");
	scanf("%13s",InputBookID);
	printf(" ������õ���ļ۸�:");
	scanf("%20s",TMPPrize);
	InputPrize=atoi(TMPPrize);
	printf(" ������õ����������:");
	scanf("%50s",InputIndexNum);
	printf(" ������õ��������:");
	scanf("%20s",TMPStock);
	InputStock=atoi(TMPStock);//���ַ�����תΪ���� 
	ShowPressInf();//��ʾ�鱾��Ϣ 
	printf("������õ��������ı��");
	scanf("%2s",TMPPressNum);
	InputPressNum=atoi(TMPPressNum);
	while(strcmp(PressInf[InputPressNum].PressName," ")==0)
	{
		printf("�ó����粻���ڣ��Ƿ�Ҫ��ӳ�����(Y/N)");//<----------------------------��ӳ����� 
		scanf("%1s",Input);
		if(Input[0]=='Y'||Input[0]=='y')
		{
			AddPressInf(InputPressNum);
			break;
		}
		if(Input[0]=='N'||Input[0]=='n')
		{
			InputPressNum=100;//ѡ����Ӻ� 
			break;
		}
	}
    FILE *fp= fopen("BookInf.db", "a");//���ļ� 
    if (!fp)
    {
		printf("�ļ��򿪴���");
        return;//<-------------------------------
    }
    fprintf(fp,"|%s|%s|%d|%s|%d|%s|%d|\n",InputName,InputWriter,InputPressNum,InputBookID,InputPrize,InputIndexNum,InputStock);
    fclose(fp);
	printf("��ӳɹ���");
	system("pause");
	ReadPress(); 
	ReadBookInf();system("cls");
} 
int AddPressInf(int InputPressNum)
{
	char TMPInputNum[2]={""},TMPPressName[100]={""}; 
	int InputNum=0;
	if(InputPressNum>100&&InputPressNum<0)
	{
		system("cls");
		ReadPress();
		while(InputPressNum>=100&&InputPressNum<=0)
		{
			printf("�������µĳ�����ı��(1-99)");
			scanf("%2s",TMPInputNum);
			InputPressNum=atoi(TMPInputNum);
		}
	}
	printf("�������µĳ����������");
	scanf("%100s",TMPPressName);
	FILE *fp= fopen("PressInf.db", "a");//���ļ� 
    if (!fp)
    {
		printf("�ļ��򿪴���");
        return;//<-------------------------------
    }
    fprintf(fp,"%d %s\n",InputPressNum,TMPPressName);
    fclose(fp);
	return; 
}
void DelBookInf()
{
	int Count=0,Status=101;
	char InputBookID[13]={""},Input[1]={""}; 
	printf("��������Ҫɾ������ı��:ISBN "); 
	scanf("%30s",InputBookID);
	for(Count=0;Count<100;Count++)
	{
		if(strcmp(BookInf[Count].BookID,InputBookID)==0)
		{
			printf("��ȷ���Ƿ�Ҫɾ���Ȿ�������(Y/N)");
			printf("\n             �� ��          �� ��    �� �� ��            �� ��            �۸� ����  ���\n\n");
			ShowSingleBookInf(Count);
			scanf("%1s",Input);
			if(Input[0]=='Y'||Input[0]=='y')
			{
				Status=Count;
				break;
			}else {return;};
			memset(BookInf[Status].BookName,0,sizeof(BookInf[Status].BookName));
			memset(BookInf[Status].Writer,0,sizeof(BookInf[Status].Writer));
			memset(BookInf[Status].BookID,0,sizeof(BookInf[Status].BookID));
			memset(BookInf[Status].IndexNum,0,sizeof(BookInf[Status].IndexNum));
			BookInf[Status].PressNum=0;BookInf[Status].Prize=0;BookInf[Status].Stock=0;
			printf("%d,%d,%d",BookInf[Status].PressNum,BookInf[Status].Prize,BookInf[Status].Stock=0);
		}
	}
	system("del BookInf.db");
	system("pause");
	FILE *fp= fopen("BookInf.db", "a");//���ļ� 
    if (!fp)
    {
		printf("�ļ��򿪴���");
        return;//<-------------------------------
    }
	for(Count=0;Count<100;Count++)
	{
		if(Count==Status){continue;}
		if(BookInf[Count].Stock==0&&BookInf[Count].PressNum==0){continue;}
		fprintf(fp,"|%s|%s|%d|%s|%d|%s|%d|\n",BookInf[Count].BookName,BookInf[Count].Writer,BookInf[Count].PressNum,BookInf[Count].BookID,BookInf[Count].Prize,BookInf[Count].IndexNum,BookInf[Count].Stock);
	}
	fclose(fp);
	printf("ϵͳ��������ɾ�������ݣ�");
	system("pause");
	Restart();
 } 
void ChangeBookInf()
{
	char InputBookID[13]={""},Input[1]={""},Readchar[1000]={""},TMPPressNum[2]={""},TMPPrize[20]={""},TMPStock[20]={""}; 
	int Count=0;
	printf("��������Ҫ���ĵ���ı��:ISBN "); 
	scanf("%30s",InputBookID);
	for(Count=0;Count<100;Count++)
	{
		if(strcmp(BookInf[Count].BookID,InputBookID)==0)
		{
			printf("��ȷ���Ƿ�Ҫ�޸��Ȿ�����Ϣ(Y/N)");
			printf("\n             �� ��          �� ��    �� �� ��            �� ��            �۸� ����  ���\n\n");
			ShowSingleBookInf(Count);
			scanf("%1s",Input);
			if(Input[0]=='Y'||Input[0]=='y')
			{
				printf("�����ı��ļ����޸Ĳ����棡");
				FILE *fpc= fopen("Result.tmp", "a");
				fprintf(fpc,"|%s|%s|%d|%s|%d|%s|%d|\n",BookInf[Count].BookName,BookInf[Count].Writer,BookInf[Count].PressNum,BookInf[Count].BookID,BookInf[Count].Prize,BookInf[Count].IndexNum,BookInf[Count].Stock);
				fclose(fpc);
				printf("\n������ڱ���������");
				system("notepad.exe Result.tmp");
				memset(BookInf[Count].BookName,0,sizeof(BookInf[Count].BookName));
				memset(BookInf[Count].Writer,0,sizeof(BookInf[Count].Writer));
				memset(BookInf[Count].BookID,0,sizeof(BookInf[Count].BookID));
				memset(BookInf[Count].IndexNum,0,sizeof(BookInf[Count].IndexNum));
				system("pause");
				FILE *fpo= fopen("Result.tmp", "r");
				if (!fpo)
 			   {
					printf("�ļ��򿪴���");
  			        return;//<-------------------------------
  				}
  				fgets(Readchar,1000,fpo);
  				DevideData(Readchar,BookInf[Count].BookName,BookInf[Count].Writer,TMPPressNum,BookInf[Count].BookID,TMPPrize,BookInf[Count].IndexNum,TMPStock);
  				BookInf[Count].PressNum=atoi(TMPPressNum);BookInf[Count].Prize=atoi(TMPPrize);BookInf[Count].Stock=atoi(TMPStock);
				fclose(fpo);
				system("del Result.tmp");
				system("del BookInf.db");
				FILE *fp= fopen("BookInf.db", "a");//���ļ� 
   				if (!fp)
   				{
					printf("�ļ��򿪴���");
   			    	return;//<-------------------------------
    			}
				for(Count=0;Count<100;Count++)
				{
					if(BookInf[Count].PressNum==0&&BookInf[Count].Stock==0){continue;}
					fprintf(fp,"|%s|%s|%d|%s|%d|%s|%d|\n",BookInf[Count].BookName,BookInf[Count].Writer,BookInf[Count].PressNum,BookInf[Count].BookID,BookInf[Count].Prize,BookInf[Count].IndexNum,BookInf[Count].Stock);
				}
				fclose(fp);
				printf("�޸���ɣ�");
				system("pause");
				break;
			}else{break;}
		}
	}
	ReadPress();
	ReadBookInf();system("cls");
}
void ManageBookInf()
{
	ReadPress(); 
	ReadBookInf();
	system("cls");
	ShowBookInf();
	char Input[2]={""}; 
	printf("                                  ����<1>�����鱾                \n"); 
	printf("                                 ����<2>�޸��鱾��Ϣ              \n"); 
	printf("                                  ����<3>ɾ���鱾                 \n");
	printf("                                 ����<4>�������˵�                \n");
	printf(" ########################################################################################\n");
	printf("  ������������еĲ�����");
	scanf("%1s",Input);
	if(Input[0]=='1'){system("cls");AddBookInf();}else
	if(Input[0]=='2'){ChangeBookInf();}else
	if(Input[0]=='3'){DelBookInf();}else
	if(Input[0]=='4'){system("cls");IndexPage();}
	ManageBookInf();
} 
void ManagePressInf()
{
	ShowPressInf();
	int Count=0;
	char Input[2]={""}; 
	printf(" ########################################################################################\n");
	do 
	{
		printf("  �����������������ʾ����������ͼ��:");
		scanf("%2s",Input);
	}while(strcmp(PressInf[atoi(Input)].PressName," ")==0);
	printf("\n             �� ��          �� ��    �� �� ��            �� ��            �۸� ����  ���\n\n");
	for(Count=0;Count<100;Count++)
	{
		if(BookInf[Count].PressNum==atoi(Input))
		{
			ShowSingleBookInf(Count);
		}
	}
	system("pause");
	IndexPage(); 
}
void QueryWriter()//<------------------------------------------------------------------- 
{
	ShowBookInf();
	char Input[20]={""}; 
	int Count=0,Count1=0;
	printf("  ��������������:");
	scanf("%20s",Input);
	printf(" ########################################################################################\n");
	printf("\n             �� ��          �� ��    �� �� ��            �� ��            �۸� ����  ���\n\n");
	for(Count1=0;Count1<100;Count1++)
	{
		if(strstr(BookInf[Count1].Writer,Input)!=NULL)
		{
			ShowSingleBookInf(Count1);
			Count=1;
		}
	}
	if(Count==0)
	{
		printf("�Ҳ��������ߵ��鼮\n");
	}
	printf("\n ########################################################################################\n");
	system("pause");
	IndexPage(); 
}
void QueryBookName()
{
	ShowBookInf();
	char Input[20]={""}; 
	int Count=0,Count1=0;
	printf("  �������鱾����:");
	scanf("%20s",Input);
	printf(" ########################################################################################\n");
	printf("\n             �� ��          �� ��    �� �� ��            �� ��            �۸� ����  ���\n\n");
	for(Count1=0;Count1<100;Count1++)
	{
		if(strstr(BookInf[Count1].BookName,Input)!=NULL)
		{
			ShowSingleBookInf(Count1);
			Count=1;
		}
	}
	if(Count==0)
	{
		printf("�Ҳ��������ֵ��鼮\n");
	}
	printf("\n ########################################################################################\n");
	system("pause");
	IndexPage(); 
}
void Rank(int Sequence)
{
	if(Sequence==0)//<-------------------------------------------------------------
	{
		int Count1=0,Count2=0,Size=100;
	    for(Count1=1;Count1<Size-1;Count1++)
	    {
    	    for(Count2=0;Count2<Size-Count1;Count2++)
    	    {
    	        if(strcmp(RBookInf[Count2].BookID,RBookInf[Count2+1].BookID)>0)
    	        {
    	            RBookInf[101]=RBookInf[Count2];
    	            RBookInf[Count2]=RBookInf[Count2+1];
     	           RBookInf[Count2+1]=RBookInf[101];
        	    }
        	} 
    	}
	}else
	if(Sequence==1)
	{
		int Count1=0,Count2=0,Size=100;
		for(Count1=0;Count1<Size;Count1++)
		{
			for(Count2=1;Count2<Size;Count2++)
			{
				if(strcmp(RBookInf[Count2].BookID,RBookInf[Count2-1].BookID)>0)
				{
					RBookInf[101]=RBookInf[Count2];
					RBookInf[Count2]=RBookInf[Count2-1];
					RBookInf[Count2-1]=RBookInf[101];
				}
			}
		}
	}else
	if(Sequence==2)
	{
		int Count1=0,Count2=0,Size=100;
	    for(Count1=1;Count1<Size-1;Count1++)
	    {
    	    for(Count2=0;Count2<Size-Count1;Count2++)
    	    {
    	        if(RBookInf[Count2].Prize>RBookInf[Count2+1].Prize)
    	        {
    	            RBookInf[101]=RBookInf[Count2];
    	            RBookInf[Count2]=RBookInf[Count2+1];
     	           RBookInf[Count2+1]=RBookInf[101];
        	    }
        	} 
    	}
	}else
	if(Sequence==3)
	{
		int Count1=0,Count2=0,Size=100;
		for(Count1=0;Count1<Size;Count1++)
		{
			for(Count2=1;Count2<Size;Count2++)
			{
				if(RBookInf[Count2].Prize>RBookInf[Count2-1].Prize)
				{
					RBookInf[101]=RBookInf[Count2];
					RBookInf[Count2]=RBookInf[Count2-1];
					RBookInf[Count2-1]=RBookInf[101];
				}
			}
		}
	}
	int Count=0;
	system("cls");
	printf(" ########################################################################################\n");
	printf(" ######################################����ͼ����Ϣ######################################\n");
	printf(" ########################################################################################\n\n");
	printf("             �� ��          �� ��    �� �� ��            �� ��            �۸� ����  ���\n\n");
	for(Count=0;Count<100;Count++)
	{
		if(RBookInf[Count].Stock==0&&RBookInf[Count].Prize==0){continue;}
		printf("  ");prints(RBookInf[Count].BookName,25);prints(RBookInf[Count].Writer,8);prints(PressInf[RBookInf[Count].PressNum].PressName,18);printf("ISBN");prints(RBookInf[Count].BookID,13);
		printf(" ��%d ",RBookInf[Count].Prize);prints(RBookInf[Count].IndexNum,5);printf(" %d\n",RBookInf[Count].Stock);
	}
	printf("\n ########################################################################################\n");
 } 
void RankBookInf()
{ 
	int Cnt=0;
	for(;Cnt<=99;Cnt++)
	{
		RBookInf[Cnt].PressNum=BookInf[Cnt].PressNum;RBookInf[Cnt].Prize=BookInf[Cnt].Prize;
		RBookInf[Cnt].Stock=BookInf[Cnt].Stock;
		strcpy(RBookInf[Cnt].BookName,BookInf[Cnt].BookName);
		strcpy(RBookInf[Cnt].Writer,BookInf[Cnt].Writer);
		strcpy(RBookInf[Cnt].BookID,BookInf[Cnt].BookID);
		strcpy(RBookInf[Cnt].IndexNum,BookInf[Cnt].IndexNum);
	}
	for(;;)
	{
		char Input[1]={""}; 
		printf("    <1>�����������  <2>�������  <3>��Ž���  <4>�۸�����  <5>�۸���  <6>���������� ");
		printf("\n ########################################################################################\n");
		printf("\n\n��������Ҫ���еĲ�����") ;
		scanf("%1s",&Input);
		if(Input[0]=='1'){system("cls");ReadBookInf();ShowBookInf();RankBookInf();}else
		if(Input[0]=='2'){system("cls");Rank(0);}else
		if(Input[0]=='3'){system("cls");Rank(1);}
		if(Input[0]=='4'){system("cls");Rank(2);}else
		if(Input[0]=='5'){system("cls");Rank(3);}else
		if(Input[0]=='6'){system("cls");IndexPage();}
	}
}
void OutputExcel()
{
	printf("\n ########################################################################################\n");
	printf("      ���ڵ�������Excel");
	system("del Output.csv");
	system("cls");
	FILE* fp;
    fp = fopen("Output.csv", "a");//���ļ� 
    if (!fp)
    {
		printf("����ʧ�ܣ�");
        return;//<-------------------------------
    }
    int Count=0;
    fprintf(fp,"����,����,������,���,�۸�,����,���\n");
	for(;Count<100;Count++)
	{
		if(BookInf[Count].PressNum==0&&BookInf[Count].Stock==0){continue;}
		fprintf(fp,"%s,%s,%s,%s,%d,%s,%d\n",BookInf[Count].BookName,BookInf[Count].Writer,PressInf[BookInf[Count].PressNum].PressName,BookInf[Count].BookID,BookInf[Count].Prize,BookInf[Count].IndexNum,BookInf[Count].Stock);
	}
	fclose(fp);
	printf("������ɣ�");
	system("pause");
	system("start Output.csv");
	system("cls");
	IndexPage();
 }
