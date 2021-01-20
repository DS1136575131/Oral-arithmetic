#include<stdio.h>
#include<string.h>
#include <stdlib.h> 
#include <conio.h>
#include <windows.h>
#include <time.h>
#define N 10   //ʹ���������� 

/*********************************ȫ�ֱ�������*********************************/ 
struct SCORE
{ 
	char name[30]; 
	int  num_sum;		//��Ŀ����
	int	 num_true;  	//��ȷ��Ŀ��
	//char password[10]	//�û����� 
	char date[11];		//���ڣ�����������8+б��2+NULL1=11�� 
	char time[6];		//ʱ�䣨����Сʱ2+����2+ð��1+NULL1=6�� 
	char nf;			//��ǰ�û�nf=1�������Ϊ0		 
}score[N+1]; 

int user_num=0;			//��ǰʹ������
int user_id; 			//��ǰ�û����

/***********************************��������***********************************/ 
/*���ܺ���*/ 
int rand_num(int m,int n);			//��������� 
void swap(int *m,int *n);			//�������� 
void time_record(int n);			//ʱ���¼ 
static  void  setpos(int x,int y) ;	//���ù�� 

/*�������߼����*/ 
void  qa_process(int grade); 	//�������� 
void  grade_choice(); 			//�꼶ѡ�� 
void menu(); 					//�˵����� 
void login();					//��¼���� 
void file_save(); 				//�ļ����� 
void file_open();				//�ļ���ȡ 

/*���꼶��Ŀ����*/ 
float program_1();	
float program_2();
float program_3();
float program_4();
float program_5();
float program_6();

/***********************************��������***********************************/ 
int main()
{ 
	for(int i=1;i<N;i++)	//�����е÷���0 
		score[i].num_true=0; 
	file_open(); //��ȡ�����ļ�����
  	while(1)
  	{
    	system("cls"); 
		login();	//ѭ�����õ�¼���� 
	}
	return 0;
}


/**************����m��n��������� ***********/ 
int rand_num(int m,int n)
{
	srand((unsigned)time(NULL)+rand());  //����������ӣ��������+rand()��Ϊ���������������ʱ�ܲ�����ͬ���� 
	int num=rand()%(n-m+1)+m;      //rand()����0~32767�����忴�����������������ͨ����nȡ������0~n������� 
	return num;
}

/*********�����������ͱ�������ֵ ***************/ 
void swap(int* m,int* n)
{
	int i;
	i=*m;
	*m=*n;
	*n=i;
}


/*********��¼��ǰ����ʱ�䣨��score[n]�У� **********/ 
void time_record(int n)	//����ʹ�ô�ַ�������޸�ԭ������ֵ 
{
	char buff1[20],buff2[20],buff3[20];	//	��������/ʱ��ķֶ���Ϣ���ꡢ�¡��գ� 
	//char date[11],time[6];			//�������Ϻõ�����/ʱ�� 
    time_t t;	 
    struct tm * lt;
    time (&t);//��ȡʱ�����
    lt = localtime (&t);//תΪʱ��ṹ��
    
    itoa(lt->tm_year+1900,buff1,10);//�⺯��itoa()������ת��Ϊ�ַ���(����������Ϊ��ת����������)����ݴ�1900�꿪ʼ��Ҫ����1900���ǹ�Ԫ���� 
    itoa(lt->tm_mon+1,buff2,10);	//�·ݴ�0~11����Ҫ��1    
	itoa(lt->tm_mday,buff3,10);
	strcat(buff1,"/");		//���ֶε�������Ϣ���ӵ�һ�� 
	strcat(buff1,buff2); 
	strcat(buff1,"/"); 
	strcat(buff1,buff3);
	strcpy(score[n].date,buff1);	//�����Ϻõ����ڸ��Ƶ��ṹ��
	
    itoa(lt->tm_hour,buff1,10);		// ʱ����Ϣ¼�� 
    itoa(lt->tm_min,buff2,10);    
	//itoa(lt->tm_sec,buff3,10);
	strcat(buff1,"��");		//���ֶε�������Ϣ���ӵ�һ�� 
	strcat(buff1,buff2); 
	//strcat(buff1,"��"); 
	//strcat(buff1,buff3);
	strcpy(score[n].time,buff1);	//�����Ϻõ�ʱ�临�Ƶ��ṹ��	
}



/**************�ʴ𼰴��б�����*************/ 
void  qa_process(int grade)   
{ 
	
	char f=1;	//f=0ʱ���� 
	float ans,ans_my;
	while(f!='0')	//���ַ���ʽ���룬�ж�ʱҲ���ַ�0�ж� 
	{
		switch(grade)
		{
			case 1:ans=(float)program_1();break;	//��ͳһת��Ϊ������
			case 2:ans=(float)program_2();break;	//��ͳһת��Ϊ������
			case 3:ans=(float)program_3();break;	//��ͳһת��Ϊ������
			case 4:ans=(float)program_4();break;	//��ͳһת��Ϊ������
			case 5:ans=(float)program_5();break;	//��ͳһת��Ϊ������
			case 6:ans=(float)program_6();break;	//��ͳһת��Ϊ������		 
		}
		scanf("%f",&ans_my);
		if(ans-ans_my<0.0001)	//����ȷʱ���𰸲��ò�Ĵ�С�ж϶Դ����ٳ��������������
		{ 
			score[user_id].num_true++; 	//��ȷ������1
			printf("\n�ش���ȷ��"); 	
		} 
		else
		{
			printf("\n�ش������ȷ��Ϊ%g",ans);   // ��%f%e�н϶̵����������
		}
		setbuf(stdin,NULL); //�����뻺������Ϊ��,��ֹ����scanf 
		score[user_id].num_sum++; 	//�����Ƿ���ȷ����������1
		time_record(user_id);		//��¼��ǰʱ��
		printf("\n����0�������˵��������������������");
		scanf("%c",&f);
	}
	
}


/**************�꼶ѡ�񴰿�**************/ 
void  grade_choice()   
{ 
	int i;
	while(1)
	{	
		system("cls");	//����
		printf("�����������꼶��1~6����"); 
		scanf("%d",&i);
		if(i<1 || i>6) //����û���������ֳ�����Χ
			printf("����������������룡");
		else
		{
			qa_process(i);	//���������������Ӧ�꼶����Ŀ
			return;
		}
	}
}



/***************����ȷ��Ŀ������************/ 
void  sorting()   
{ 
	struct SCORE t;
	bool f=1;
	for(int i=1;i<user_num;i++)	//ʹ��ð������ð���������ȶ��������㷨���ԱȽ���������н�������ʱЧ�ʱ�ѡ������ߣ�
	{
		f=1;
		for(int j=1;j<user_num-i;j++)
			if(score[j].num_true<score[j+1].num_true)
			{
				t=score[j];
				score[j]=score[j+1];
				score[j+1]=t;
				f=0;	//������λ�ý�������f��0 
			}
		if(f=1)			//�ڲ�ѭ������f��ȻΪ1˵������ѭ��û�з�����λ�ý������������Ѿ����
			break;		//��ǰ����ѭ�� 
	}
}


/****************�����鿴****************/ 
void  ranking()   
{ 
	sorting();	//��score[]����ȷ��Ŀ���������� 
	for(int i=1;i<=user_num;i++)	//���ҵ�ǰ�û�����������λ�ã�����ᵼ�µ�ǰ�û����ݵ���λ����ʱuser_id��Ҫ���£� 
	{
		if(score[i].nf==1)
		{
			user_id=i;	//���õ�ǰ�û����
			break;		//�ҵ���ǰ�û�λ�ü�����ǰ�������� 
		} 
	} 
	
	system("cls");	//����
	printf("\t\t\t���а�\n\n");	// ��ӡ����
	printf("����\t�û���\t�÷�\t����\t\tʱ��\n\n"); //��ӡ�������û���	
	for(int i=1;i<=user_num;i++)
	{
		printf("%d\t%s\t",i,score[i].name); //��ӡ�������û���
		printf("%d\t",score[i].num_true); //��ӡ�÷�
		printf("%s\t",score[i].date); //��ӡ����		 
		printf("%s\n",score[i].time); //��ӡʱ�䲢����		
	} 
	
	printf("��������������˵�");	
	_getch(); 
}



/**************�趨����̨���ڹ��λ�� ***************/ 
static  void  setpos(int x,int y)   
{ 
    COORD   point ={x,y}; //���Ҫ���õ�λ��x,y
    HANDLE  HOutput = GetStdHandle(STD_OUTPUT_HANDLE); //ʹ��GetStdHandle(STD_OUTPUT_HANDLE)����ȡ��׼����ľ��
    SetConsoleCursorPosition(HOutput,point); //���ù��λ��
}


/*********************�˵�******************/ 
void menu()
{
  int i,j;
  while(1)	//�˵���������ѭ������ʽ���У���������ܺ������ص��˵����棬ֻ����Ҫ���ص�¼������˳�ϵͳʱ���ܽ���ѭ�� 
  {
	  system("cls");  
	  printf("\t\t\tСѧ����ϵͳ\t\t\t\n\n\n");
	  printf("\t\t\t1.������ϰ\t\t\t\n");
	  printf("\t\t\t2.�鿴����\t\t\t\n");
	  printf("\t\t\t3.���ص�¼����\t\t\t\n");
	  printf("\t\t\t4.�˳�ϵͳ\t\t\t\n\n");
	  printf("�������Ž����Ӧ���ܣ�");
	  scanf("%d",&i);
	  switch(i)
	  {
	    case 1: grade_choice();	break;	
		case 2: ranking();		break;
		case 3: file_save();return;	//ֱ��ͨ�������˵��������ص���һ�㣬������¼���� ������ǰ�Զ������ļ� 
		case 4: file_save();exit(0);break;//�����������У�����ǰ�Զ������ļ� 
		default:
		  printf("������������������");
		  Sleep(1);
	  }
  }
}


/**************��¼����**************/ 
void login()
{
  char name[30];
  int a;	 
  system("cls");
  printf("\n\n\n");
  printf("\t* * * * * * * * * * * * * * * * * *\n");
  printf("\t*                                 *\n");
  printf("\t*       Сѧ����ϵͳ��¼          *\n");
  printf("\t*                                 *\n");
  printf("\t*   �������û�����                *\n");
  printf("\t*                                 *\n");
  printf("\t* * * * * * * * * * * * * * * * * *\n");
  setpos(25,7); 
  scanf("%s",name);	//������û���  
  for(int i=1;i<=user_num;i++)	//���Ҹ��û����Ƿ��Ѵ��� 
  {
  	if(strcmp(score[i].name,name)==0)	//strcmp()�ַ����ԱȺ���������ֵΪ1ʱ˵�������ַ�����ͬ 
  	{
  		printf("\n\n\n���û����Ѵ��ڣ�����1ȷ�ϵ�¼���û����������������������\n");
		scanf("%d",&a);
		if(a==1)
		{
			user_id=i;	//��¼��ǰ�û����
			menu();		//�����˵� 
			return;		//�Ӳ˵�����ʱֱ�ӽ������������е�¼���� 
		}
		else
			return; 	//��������ͨ��ֱ�ӽ�����ǰ���������µ��õ�¼����ʵ�� 
  	}
  } 	//��ѭ������˵��������û��������ڣ���Ҫ�����µ��û��� 
  
  
  strcpy(score[++user_num].name,name);	//�û���user_num��1����������û������Ƶ��¿ռ� 
  user_id=user_num; 					//��¼��ǰ�û����
  time_record(user_id);						//ʱ���¼ 
  printf("\n\n\n�û�ע��ɹ�����������������˵���");	
  _getch();   
  menu(); 
}


/*****************�����ļ�*******************/
void file_save()
{
    FILE *fp=fopen("ComputerRanking.txt","w+");	//���Դ�ComputerRanking.txt 
    if (fp==NULL)    //����ļ������� 
    {
            printf("�޷������ļ�!");
			_getch();  
			return;           
    }	
    
    system("cls"); 	     
    for(int i=1;i<=user_num;i++)
    {
		printf("д������Ϊ%d���û�����",i);
		fprintf(fp,"%d\t",i);
		fprintf(fp,"%s\t",score[i].name);
		fprintf(fp,"%d\t",score[i].num_true);
		fprintf(fp,"%s\t",score[i].date);
		fprintf(fp,"%s\n",score[i].time);						
    }
    
    fclose(fp); 
	printf("д����ɣ�\n");		
	printf("��������������˵�");	
	_getch();		 
	return;		
}


/********************��ȡ�ļ�*********************/ 
void  file_open()
{
	char buff[20];		//�ַ�����ȡ����
	int n;				//���ͻ��� 
	FILE *fp= fopen("ComputerRanking.txt","rb");
    if(fp==NULL)
    {
        printf("���ļ�ʧ��!\n");
        printf("��������������˵�");	
		_getch(); 
        return; 
    }	
    
    user_num=0;
    for(int i=1;fscanf(fp, "%s", buff)!=EOF;i++)	//ѭ����ȡ���ݣ�ÿ��ѭ����ȡһ�� 
    { 
    	printf("%s\t",buff);
    	fscanf(fp, "%s", buff);		//��ȡ�û�����������forѭ���ж�����б���ȡ���ˣ�
		strcpy(score[i].name,buff);	//����ȡ�����û�������ṹ��
		printf("%s\t",score[i].name);
		
		fscanf(fp, "%s", buff);		//��ȡ�÷֣����ַ�����ʽ�� 
		score[i].num_true=atoi(buff); //ת��Ϊ���ͱ��� atoi()�ַ���ת����
		printf("%d\t",score[i].num_true);
		 
    	fscanf(fp, "%s", buff);		//��ȡ���� 
		strcpy(score[i].date,buff);	
		printf("%s\t",score[i].date);

		fscanf(fp, "%s", buff);		//��ȡʱ�� 
		strcpy(score[i].time,buff);	
		printf("%s\n",score[i].time);	
		score[i].nf=0;			//���Ϊ��ʷ���ݣ�nf=1��ʾ������Ϊ��ǰ�û����ݣ�	 
    	user_num++;				//��¼����
    } 
    
    fclose(fp);
    printf("�����ļ���ȡ�ɹ�!\n");
	printf("������������¼����!\n");	
	_getch();          
}



/***********����һ�꼶��Ŀ****************/ 
float program_1()
{
	system("cls");
	int num1=rand_num(0,100),num2=rand_num(0,100),answer;
	char c=rand_num(0,1);		//һ�꼶ֻ�мӼ���������������ɵ�0,1ѡ��Ӽ� 
	if(c)	//c=1ʱΪ�ӷ�
	{
		answer=num1+num2;	// �����
		while(answer>100)		//  �ʹ���100ʱ����ѡ 
		{
			num1=rand_num(0,100);
			num2=rand_num(0,100); 
			answer=num1+num2;
		} 
		printf("%d+%d=",num1,num2);	//��ӡ��Ŀ	 
	}		
	else	//����Ϊ���� 
	{
		if(num1<num2)
			swap(&num1,&num2);
		answer=num1-num2;
		printf("%d-%d=",num1,num2);	//��ӡ��Ŀ
	} 
	return answer; 
}



/************���ɶ��꼶��Ŀ***************/ 
float program_2()
{
	system("cls");
	int num1,num2,answer;
	char c=rand_num(0,4);		//����c��ֵѡ��Ӽ��˳����� 
	if(c==0)		//c=0ʱΪ100���ڼӼ���
	{
	 	answer=program_1();	//ֱ�ӵ���1�꼶��Ŀ������ʵ�� 
	}		
	else if(c==1)	//c=1ʱΪ��ʮ���ӷ����� 
	{
		answer=101;		  //�Ƚ�answer��Ϊ101����֤�ܽ������ѭ��	
		while(answer>100) //ͨ��ѭ������һ���С��100�ļ��� 
		{
			num1=rand_num(0,100);
			num2=rand_num(0,100); 
			answer=num1+num2;
		} 
		num1*=10;	//�����ֱ�Ϊ��10�� 
		num2*=10; 
		answer=num1+num2;
		printf("%d+%d=",num1,num2);	//��ӡ��Ŀ
	}
	else if(c==2)	//c=2ʱΪ��10����
	{
		num1=rand_num(0,100);
		num2=rand_num(0,100);
		if(num1<num2)
			swap(&num1,&num2);
		num1*=10;	//�����ֱ�Ϊ��10�� 
		num2*=10; 
		answer=num1-num2;
		printf("%d-%d=",num1,num2);	//��ӡ��Ŀ
	}
	else if(c==3)	//c=3ʱΪ�˷�������10���ڣ� 
	{
		num1=rand_num(0,9);
		num2=rand_num(0,9);
		answer=num1*num2;
		printf("%d*%d=",num1,num2);	//��ӡ��Ŀ
	}
	else			//���������������̺ͳ���10���ڣ���ͨ���ѳ˷�ת��Ϊ����ʵ�� 
	{ 
		num1=rand_num(0,9);
		num2=rand_num(0,9);
		answer=num1*num2;
		printf("%d/%d=",answer,num2);	//ֱ�Ӱѳ˻���Ϊ��Ŀ�ı����� 
		answer=num1;					//�𰸻�Ϊ����1 
	}
	return answer; 
}


/****************�������꼶��Ŀ***************/ 
float program_3()
{
	system("cls");
	int num1,num2,answer;
	char c=rand_num(0,3);		//����c��ֵѡ��Ӽ��˳����� 	
	if(c==0)	//10000���ڼӷ�
	{
		answer=10001;
		while(answer>10000)		//����С��10000��һ����� 
		{
			num1=rand_num(0,10000);
			num2=rand_num(0,10000); 
			answer=num1+num2;
		} 
		printf("%d+%d=",num1,num2);	//��ӡ��Ŀ	 
	}
	else if(c=1)	//10000���ڼ��� 
	{
		num1=rand_num(0,10000);
		num2=rand_num(0,10000);		
		if(num1<num2)
			swap(&num1,&num2);
		answer=num1-num2;
		printf("%d-%d=",num1,num2);	//��ӡ��Ŀ
	} 
	else if(c=2)	//��λ���˷� 
	{
		num1=rand_num(0,100);
		num2=rand_num(0,100);		
		answer=num1*num2;
		printf("%dx%d=",num1,num2);	//��ӡ��Ŀ
	} 	
	else	//��λ����һλ������ 
	{
		num1=rand_num(0,100);
		num2=rand_num(0,10);		
		answer=101;
		while(answer>100)		//����С��100�Ļ� 
		{
			num1=rand_num(0,100);
			num2=rand_num(0,10); 
		} 
		printf("%d/%d=",answer,num2);	//��ӡ��Ŀ
		answer=num1; 
	} 
	return answer; 
}


/**************�������꼶��Ŀ****************/ 
float program_4()
{
	system("cls");
	float num1,num2,num3,answer;	//�����꼶��ʼ��ʹ�ø����� 
	char c=rand_num(0,3);
	if(c==0)	//10000���ڴ���λС���ӷ�
	{
		answer=10001;
		while(answer>10000)		//����С��10000��һ����� 
		{
			num1=(float)rand_num(0,10000);
			num2=(float)rand_num(0,10000); 
			answer=num1+num2;
		}
		num3=(float)rand_num(0,100)/100;	//������λ����С�� 
		num1+=num3;							//����1�������ɵ�С�� 
		num3=(float)rand_num(0,100)/100;
		num2+=num3;
		answer=num1+num2;				//���¼���� 
		printf("%.2f+%.2f=",num1,num2);		//��ӡ��Ŀ	 
	}
	else if(c==1)	//10000���ڴ���λС������
	{
		int n1,n2;		 
		n1=rand_num(0,10000);
		n2=rand_num(0,10000); 
		if(n1<n2)
			swap(&n1,&n2);			
		num3=(float)rand_num(0,100)/100;	//������λ����С�� 
		num1=n1+num3;							
		num3=(float)rand_num(0,100)/100;
		num2=n2+num3;
		answer=num1-num2;				//���¼���� 
		printf("%.2f-%.2f=",num1,num2);	//�����ͱ�����������λС��		
	}	
	else if(c=2)	//��λ��*��λ���˷� 
	{
		num1=(float)rand_num(0,100);
		num2=(float)rand_num(0,1000);		
		answer=num1*num2;
		printf("%.0fx%.0f=",num1,num2);	//��������������� 
	} 
	else	//��λ������λ������ 
	{
		num1=(float)rand_num(0,1000);
		num2=(float)rand_num(0,100);		
		answer=1001;
		while(answer>1000)		//����С��1000�Ļ� 
		{
			num1=(float)rand_num(0,1000);
			num2=(float)rand_num(0,100); 
			answer=num1*num2;
		} 
		printf("%.0f/.0f=",answer,num2);//���������������
		answer=num1; 
	} 	
	return answer; 
}


/***************�������꼶��Ŀ*****************/ 
float program_5()
{
	system("cls");
	float num1,num2,num3,answer;	//�����꼶��ʼ��ʹ�ø����� 
	char c=rand_num(0,1);
	if(c==0)	//ʹ�����꼶��Ŀ 
	{
	 	answer=program_4();
	}
	else if(c==1)	//10����С���˷�
	{
		num1=(float)rand_num(0,9);
		num2=(float)rand_num(0,9); 
		num3=(float)rand_num(0,100)/100;	//������λ����С�� 
		num1+=num3;						 
		num3=(float)rand_num(0,100)/100;
		num2+=num3;
		answer=num1*num2;				//���¼���� 
		printf("%.2fx%.2f=",num1,num2);		//��ӡ��Ŀ			
	}	
	else	//20���ڵ�С���������̱�����λС���ĳ�������
	{
		num1=(float)rand_num(0,20);
		num2=(float)rand_num(0,20);		
		answer=21;
		while(answer>20)		//����С��20�Ļ� 
		{
			num1=(float)rand_num(0,20);
			num2=(float)rand_num(0,20); 
			answer=num1*num2;
		} 
		num3=(float)rand_num(0,100)/100;	//������λ����С�� 
		num1+=num3;						 
		num3=(float)rand_num(0,100)/100; 
		num2+=num3;
		answer=num1*num2;
		answer=(int)(answer*100)/100.0; //ȥ�������С����������λС���� 
		printf("%.2f/.2f=",answer,num2);//������λС�����
		answer/=num2;	//���¼���� 
	} 
	return answer; 
}



/***************�������꼶��Ŀ****************/ 
float program_6()
{
	system("cls");
	float num1,num2,num3,answer;	//�����꼶��ʼ��ʹ�ø����� 
	char c=rand_num(0,6);
	if(c==0) //�ٷ���תС�� 
	{
		num1=(float)rand_num(0,100);
		printf("%.0f\%ת��ΪС���ǣ�",num1);		//����ٷֺ�Ҫ��\ȡ��%�Ĺ��� 
		answer=num1/100; 	 
	}
	else if(c==1)	//��Բ����� 
	{
		num1=(float)rand_num(0,20);
		printf("�뾶Ϊ%.0f��Բ������ǣ�pi=3.14����",num1);	 
		answer=3.14*num1*num1; 
	} 
	else if(c==2)	//��Բ���ܳ� 
	{
		num1=(float)rand_num(0,20);
		printf("�뾶Ϊ%.0f��Բ���ܳ��ǣ�pi=3.14����",num1);	 
		answer=3.14*num1*2; 
	}	
	else if(c==3)	//��Բ������� 
	{
		num1=(float)rand_num(0,20);
		num2=(float)rand_num(0,20);
		printf("����뾶Ϊ%.0f����Ϊ%.0f��Բ��������ǣ�pi=3.14����",num1,num2);	 
		answer=3.14*num1*num1*num2; 
	}
	else if(c==4)	//��Բ׶����� 
	{
		num1=(float)rand_num(0,20);
		num2=(float)rand_num(0,20);
		printf("����뾶Ϊ%.0f����Ϊ%.0f��Բ׶������ǣ�pi=3.14����",num1,num2);	 
		answer=3.14*num1*num1*num2/3; 
	}
	return answer;	
}
