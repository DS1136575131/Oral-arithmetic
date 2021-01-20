#include<stdio.h>
#include<string.h>
#include <stdlib.h> 
#include <conio.h>
#include <windows.h>
#include <time.h>
#define N 10   //使用人数上限 

/*********************************全局变量定义*********************************/ 
struct SCORE
{ 
	char name[30]; 
	int  num_sum;		//题目总数
	int	 num_true;  	//正确题目数
	//char password[10]	//用户密码 
	char date[11];		//日期（长度年月日8+斜杠2+NULL1=11） 
	char time[6];		//时间（长度小时2+分钟2+冒号1+NULL1=6） 
	char nf;			//当前用户nf=1，其余皆为0		 
}score[N+1]; 

int user_num=0;			//当前使用人数
int user_id; 			//当前用户编号

/***********************************函数声明***********************************/ 
/*功能函数*/ 
int rand_num(int m,int n);			//随机数生成 
void swap(int *m,int *n);			//交换变量 
void time_record(int n);			//时间记录 
static  void  setpos(int x,int y) ;	//设置光标 

/*程序主逻辑相关*/ 
void  qa_process(int grade); 	//答题流程 
void  grade_choice(); 			//年级选择 
void menu(); 					//菜单界面 
void login();					//登录界面 
void file_save(); 				//文件保存 
void file_open();				//文件读取 

/*各年级题目生成*/ 
float program_1();	
float program_2();
float program_3();
float program_4();
float program_5();
float program_6();

/***********************************函数定义***********************************/ 
int main()
{ 
	for(int i=1;i<N;i++)	//将所有得分置0 
		score[i].num_true=0; 
	file_open(); //读取本地文件数据
  	while(1)
  	{
    	system("cls"); 
		login();	//循环调用登录窗口 
	}
	return 0;
}


/**************生成m到n的随机整数 ***********/ 
int rand_num(int m,int n)
{
	srand((unsigned)time(NULL)+rand());  //重置随机种子，随机种子+rand()是为了连续产生随机数时能产生不同数字 
	int num=rand()%(n-m+1)+m;      //rand()生成0~32767（具体看编译器）的随机数，通过除n取余生成0~n的随机数 
	return num;
}

/*********交换两个整型变量的数值 ***************/ 
void swap(int* m,int* n)
{
	int i;
	i=*m;
	*m=*n;
	*n=i;
}


/*********记录当前本地时间（在score[n]中） **********/ 
void time_record(int n)	//参数使用传址调用以修改原变量的值 
{
	char buff1[20],buff2[20],buff3[20];	//	保存日期/时间的分段信息（年、月、日） 
	//char date[11],time[6];			//保存整合好的日期/时间 
    time_t t;	 
    struct tm * lt;
    time (&t);//获取时间戳。
    lt = localtime (&t);//转为时间结构。
    
    itoa(lt->tm_year+1900,buff1,10);//库函数itoa()将整型转换为字符串(第三个参数为待转换数的数制)，年份从1900年开始，要加上1900才是公元纪年 
    itoa(lt->tm_mon+1,buff2,10);	//月份从0~11，需要加1    
	itoa(lt->tm_mday,buff3,10);
	strcat(buff1,"/");		//将分段的日期信息连接到一起 
	strcat(buff1,buff2); 
	strcat(buff1,"/"); 
	strcat(buff1,buff3);
	strcpy(score[n].date,buff1);	//将整合好的日期复制到结构体
	
    itoa(lt->tm_hour,buff1,10);		// 时间信息录入 
    itoa(lt->tm_min,buff2,10);    
	//itoa(lt->tm_sec,buff3,10);
	strcat(buff1,"：");		//将分段的日期信息连接到一起 
	strcat(buff1,buff2); 
	//strcat(buff1,"："); 
	//strcat(buff1,buff3);
	strcpy(score[n].time,buff1);	//将整合好的时间复制到结构体	
}



/**************问答及答案判别流程*************/ 
void  qa_process(int grade)   
{ 
	
	char f=1;	//f=0时返回 
	float ans,ans_my;
	while(f!='0')	//以字符形式输入，判断时也以字符0判断 
	{
		switch(grade)
		{
			case 1:ans=(float)program_1();break;	//答案统一转化为浮点数
			case 2:ans=(float)program_2();break;	//答案统一转化为浮点数
			case 3:ans=(float)program_3();break;	//答案统一转化为浮点数
			case 4:ans=(float)program_4();break;	//答案统一转化为浮点数
			case 5:ans=(float)program_5();break;	//答案统一转化为浮点数
			case 6:ans=(float)program_6();break;	//答案统一转化为浮点数		 
		}
		scanf("%f",&ans_my);
		if(ans-ans_my<0.0001)	//答案正确时（答案采用差的大小判断对错，减少程序运算产生误差报错）
		{ 
			score[user_id].num_true++; 	//正确题数加1
			printf("\n回答正确！"); 	
		} 
		else
		{
			printf("\n回答错误！正确答案为%g",ans);   // 以%f%e中较短的输出宽度输出
		}
		setbuf(stdin,NULL); //把输入缓冲区设为空,防止跳过scanf 
		score[user_id].num_sum++; 	//不管是否正确，总题数加1
		time_record(user_id);		//记录当前时间
		printf("\n输入0返回主菜单，输入其它任意键继续");
		scanf("%c",&f);
	}
	
}


/**************年级选择窗口**************/ 
void  grade_choice()   
{ 
	int i;
	while(1)
	{	
		system("cls");	//清屏
		printf("请输入您的年级（1~6）："); 
		scanf("%d",&i);
		if(i<1 || i>6) //如果用户输入的数字超过范围
			printf("输入错误，请重新输入！");
		else
		{
			qa_process(i);	//如果输入无误进入对应年级的题目
			return;
		}
	}
}



/***************按正确题目数排序************/ 
void  sorting()   
{ 
	struct SCORE t;
	bool f=1;
	for(int i=1;i<user_num;i++)	//使用冒泡排序（冒泡排序是稳定的排序算法，对比较有序的数列进行排序时效率比选择排序高）
	{
		f=1;
		for(int j=1;j<user_num-i;j++)
			if(score[j].num_true<score[j+1].num_true)
			{
				t=score[j];
				score[j]=score[j+1];
				score[j+1]=t;
				f=0;	//发生过位置交换即把f置0 
			}
		if(f=1)			//内层循环结束f依然为1说明本次循环没有发生过位置交换，即排序已经完成
			break;		//提前结束循环 
	}
}


/****************排名查看****************/ 
void  ranking()   
{ 
	sorting();	//将score[]按正确题目数进行排序 
	for(int i=1;i<=user_num;i++)	//查找当前用户的数据所在位置（排序会导致当前用户数据的移位，此时user_id需要更新） 
	{
		if(score[i].nf==1)
		{
			user_id=i;	//重置当前用户编号
			break;		//找到当前用户位置即可提前结束查找 
		} 
	} 
	
	system("cls");	//清屏
	printf("\t\t\t排行榜\n\n");	// 打印排行
	printf("排名\t用户名\t得分\t日期\t\t时间\n\n"); //打印排名及用户名	
	for(int i=1;i<=user_num;i++)
	{
		printf("%d\t%s\t",i,score[i].name); //打印排名及用户名
		printf("%d\t",score[i].num_true); //打印得分
		printf("%s\t",score[i].date); //打印日期		 
		printf("%s\n",score[i].time); //打印时间并换行		
	} 
	
	printf("按任意键返回主菜单");	
	_getch(); 
}



/**************设定控制台窗口光标位置 ***************/ 
static  void  setpos(int x,int y)   
{ 
    COORD   point ={x,y}; //光标要设置的位置x,y
    HANDLE  HOutput = GetStdHandle(STD_OUTPUT_HANDLE); //使用GetStdHandle(STD_OUTPUT_HANDLE)来获取标准输出的句柄
    SetConsoleCursorPosition(HOutput,point); //设置光标位置
}


/*********************菜单******************/ 
void menu()
{
  int i,j;
  while(1)	//菜单界面以死循环的形式运行，方便各功能函数返回到菜单界面，只有需要返回登录界面或退出系统时才能结束循环 
  {
	  system("cls");  
	  printf("\t\t\t小学口算系统\t\t\t\n\n\n");
	  printf("\t\t\t1.进入练习\t\t\t\n");
	  printf("\t\t\t2.查看排名\t\t\t\n");
	  printf("\t\t\t3.返回登录窗口\t\t\t\n");
	  printf("\t\t\t4.退出系统\t\t\t\n\n");
	  printf("请输出序号进入对应功能：");
	  scanf("%d",&i);
	  switch(i)
	  {
	    case 1: grade_choice();	break;	
		case 2: ranking();		break;
		case 3: file_save();return;	//直接通过结束菜单函数返回到上一层，重启登录窗口 ，结束前自动保存文件 
		case 4: file_save();exit(0);break;//结束程序运行，结束前自动保存文件 
		default:
		  printf("输入有误，请重新输入");
		  Sleep(1);
	  }
  }
}


/**************登录界面**************/ 
void login()
{
  char name[30];
  int a;	 
  system("cls");
  printf("\n\n\n");
  printf("\t* * * * * * * * * * * * * * * * * *\n");
  printf("\t*                                 *\n");
  printf("\t*       小学口算系统登录          *\n");
  printf("\t*                                 *\n");
  printf("\t*   请输入用户名：                *\n");
  printf("\t*                                 *\n");
  printf("\t* * * * * * * * * * * * * * * * * *\n");
  setpos(25,7); 
  scanf("%s",name);	//输入的用户名  
  for(int i=1;i<=user_num;i++)	//查找该用户名是否已存在 
  {
  	if(strcmp(score[i].name,name)==0)	//strcmp()字符串对比函数，返回值为1时说明两个字符串相同 
  	{
  		printf("\n\n\n该用户名已存在，输入1确认登录该用户，按其它任意键重新输入\n");
		scanf("%d",&a);
		if(a==1)
		{
			user_id=i;	//记录当前用户编号
			menu();		//启动菜单 
			return;		//从菜单返回时直接结束，重新运行登录函数 
		}
		else
			return; 	//重新输入通过直接结束当前函数并重新调用登录函数实现 
  	}
  } 	//该循环结束说明输入的用户名不存在，需要增加新的用户名 
  
  
  strcpy(score[++user_num].name,name);	//用户数user_num加1，将输入的用户名复制到新空间 
  user_id=user_num; 					//记录当前用户编号
  time_record(user_id);						//时间记录 
  printf("\n\n\n用户注册成功，按任意键进入主菜单！");	
  _getch();   
  menu(); 
}


/*****************保存文件*******************/
void file_save()
{
    FILE *fp=fopen("ComputerRanking.txt","w+");	//尝试打开ComputerRanking.txt 
    if (fp==NULL)    //如果文件不存在 
    {
            printf("无法建立文件!");
			_getch();  
			return;           
    }	
    
    system("cls"); 	     
    for(int i=1;i<=user_num;i++)
    {
		printf("写入排名为%d的用户数据",i);
		fprintf(fp,"%d\t",i);
		fprintf(fp,"%s\t",score[i].name);
		fprintf(fp,"%d\t",score[i].num_true);
		fprintf(fp,"%s\t",score[i].date);
		fprintf(fp,"%s\n",score[i].time);						
    }
    
    fclose(fp); 
	printf("写入完成！\n");		
	printf("按任意键返回主菜单");	
	_getch();		 
	return;		
}


/********************读取文件*********************/ 
void  file_open()
{
	char buff[20];		//字符串读取缓冲
	int n;				//整型缓冲 
	FILE *fp= fopen("ComputerRanking.txt","rb");
    if(fp==NULL)
    {
        printf("打开文件失败!\n");
        printf("按任意键返回主菜单");	
		_getch(); 
        return; 
    }	
    
    user_num=0;
    for(int i=1;fscanf(fp, "%s", buff)!=EOF;i++)	//循环读取数据，每次循环读取一行 
    { 
    	printf("%s\t",buff);
    	fscanf(fp, "%s", buff);		//读取用户名（排名在for循环判断语句中被读取过了）
		strcpy(score[i].name,buff);	//将读取到的用户名存入结构体
		printf("%s\t",score[i].name);
		
		fscanf(fp, "%s", buff);		//读取得分（以字符串形式） 
		score[i].num_true=atoi(buff); //转换为整型保存 atoi()字符串转整型
		printf("%d\t",score[i].num_true);
		 
    	fscanf(fp, "%s", buff);		//读取日期 
		strcpy(score[i].date,buff);	
		printf("%s\t",score[i].date);

		fscanf(fp, "%s", buff);		//读取时间 
		strcpy(score[i].time,buff);	
		printf("%s\n",score[i].time);	
		score[i].nf=0;			//标记为历史数据（nf=1表示该数据为当前用户数据）	 
    	user_num++;				//记录人数
    } 
    
    fclose(fp);
    printf("本地文件读取成功!\n");
	printf("按任意键进入登录窗口!\n");	
	_getch();          
}



/***********生成一年级题目****************/ 
float program_1()
{
	system("cls");
	int num1=rand_num(0,100),num2=rand_num(0,100),answer;
	char c=rand_num(0,1);		//一年级只有加减法，根据随机生成的0,1选择加减 
	if(c)	//c=1时为加法
	{
		answer=num1+num2;	// 计算答案
		while(answer>100)		//  和大于100时重新选 
		{
			num1=rand_num(0,100);
			num2=rand_num(0,100); 
			answer=num1+num2;
		} 
		printf("%d+%d=",num1,num2);	//打印题目	 
	}		
	else	//否则为减法 
	{
		if(num1<num2)
			swap(&num1,&num2);
		answer=num1-num2;
		printf("%d-%d=",num1,num2);	//打印题目
	} 
	return answer; 
}



/************生成二年级题目***************/ 
float program_2()
{
	system("cls");
	int num1,num2,answer;
	char c=rand_num(0,4);		//根据c的值选择加减乘除运算 
	if(c==0)		//c=0时为100以内加减法
	{
	 	answer=program_1();	//直接调用1年级题目生成器实现 
	}		
	else if(c==1)	//c=1时为整十数加法运算 
	{
		answer=101;		  //先将answer设为101，保证能进入后续循环	
		while(answer>100) //通过循环生成一组和小于100的加数 
		{
			num1=rand_num(0,100);
			num2=rand_num(0,100); 
			answer=num1+num2;
		} 
		num1*=10;	//将数字变为整10数 
		num2*=10; 
		answer=num1+num2;
		printf("%d+%d=",num1,num2);	//打印题目
	}
	else if(c==2)	//c=2时为整10减法
	{
		num1=rand_num(0,100);
		num2=rand_num(0,100);
		if(num1<num2)
			swap(&num1,&num2);
		num1*=10;	//将数字变为整10数 
		num2*=10; 
		answer=num1-num2;
		printf("%d-%d=",num1,num2);	//打印题目
	}
	else if(c==3)	//c=3时为乘法（乘数10以内） 
	{
		num1=rand_num(0,9);
		num2=rand_num(0,9);
		answer=num1*num2;
		printf("%d*%d=",num1,num2);	//打印题目
	}
	else			//除法（可整除，商和除数10以内），通过把乘法转换为除法实现 
	{ 
		num1=rand_num(0,9);
		num2=rand_num(0,9);
		answer=num1*num2;
		printf("%d/%d=",answer,num2);	//直接把乘积作为题目的被除数 
		answer=num1;					//答案换为乘数1 
	}
	return answer; 
}


/****************生成三年级题目***************/ 
float program_3()
{
	system("cls");
	int num1,num2,answer;
	char c=rand_num(0,3);		//根据c的值选择加减乘除运算 	
	if(c==0)	//10000以内加法
	{
		answer=10001;
		while(answer>10000)		//生成小于10000的一组加数 
		{
			num1=rand_num(0,10000);
			num2=rand_num(0,10000); 
			answer=num1+num2;
		} 
		printf("%d+%d=",num1,num2);	//打印题目	 
	}
	else if(c=1)	//10000以内减法 
	{
		num1=rand_num(0,10000);
		num2=rand_num(0,10000);		
		if(num1<num2)
			swap(&num1,&num2);
		answer=num1-num2;
		printf("%d-%d=",num1,num2);	//打印题目
	} 
	else if(c=2)	//两位数乘法 
	{
		num1=rand_num(0,100);
		num2=rand_num(0,100);		
		answer=num1*num2;
		printf("%dx%d=",num1,num2);	//打印题目
	} 	
	else	//两位数除一位数除法 
	{
		num1=rand_num(0,100);
		num2=rand_num(0,10);		
		answer=101;
		while(answer>100)		//生成小于100的积 
		{
			num1=rand_num(0,100);
			num2=rand_num(0,10); 
		} 
		printf("%d/%d=",answer,num2);	//打印题目
		answer=num1; 
	} 
	return answer; 
}


/**************生成四年级题目****************/ 
float program_4()
{
	system("cls");
	float num1,num2,num3,answer;	//从四年级开始都使用浮点数 
	char c=rand_num(0,3);
	if(c==0)	//10000以内带两位小数加法
	{
		answer=10001;
		while(answer>10000)		//生成小于10000的一组加数 
		{
			num1=(float)rand_num(0,10000);
			num2=(float)rand_num(0,10000); 
			answer=num1+num2;
		}
		num3=(float)rand_num(0,100)/100;	//生成两位以内小数 
		num1+=num3;							//加数1加上生成的小数 
		num3=(float)rand_num(0,100)/100;
		num2+=num3;
		answer=num1+num2;				//重新计算答案 
		printf("%.2f+%.2f=",num1,num2);		//打印题目	 
	}
	else if(c==1)	//10000以内带两位小数减法
	{
		int n1,n2;		 
		n1=rand_num(0,10000);
		n2=rand_num(0,10000); 
		if(n1<n2)
			swap(&n1,&n2);			
		num3=(float)rand_num(0,100)/100;	//生成两位以内小数 
		num1=n1+num3;							
		num3=(float)rand_num(0,100)/100;
		num2=n2+num3;
		answer=num1-num2;				//重新计算答案 
		printf("%.2f-%.2f=",num1,num2);	//减数和被减数保留两位小数		
	}	
	else if(c=2)	//两位数*三位数乘法 
	{
		num1=(float)rand_num(0,100);
		num2=(float)rand_num(0,1000);		
		answer=num1*num2;
		printf("%.0fx%.0f=",num1,num2);	//保留整数部分输出 
	} 
	else	//三位数除两位数除法 
	{
		num1=(float)rand_num(0,1000);
		num2=(float)rand_num(0,100);		
		answer=1001;
		while(answer>1000)		//生成小于1000的积 
		{
			num1=(float)rand_num(0,1000);
			num2=(float)rand_num(0,100); 
			answer=num1*num2;
		} 
		printf("%.0f/.0f=",answer,num2);//保留整数部分输出
		answer=num1; 
	} 	
	return answer; 
}


/***************生成五年级题目*****************/ 
float program_5()
{
	system("cls");
	float num1,num2,num3,answer;	//从四年级开始都使用浮点数 
	char c=rand_num(0,1);
	if(c==0)	//使用四年级题目 
	{
	 	answer=program_4();
	}
	else if(c==1)	//10以内小数乘法
	{
		num1=(float)rand_num(0,9);
		num2=(float)rand_num(0,9); 
		num3=(float)rand_num(0,100)/100;	//生成两位以内小数 
		num1+=num3;						 
		num3=(float)rand_num(0,100)/100;
		num2+=num3;
		answer=num1*num2;				//重新计算答案 
		printf("%.2fx%.2f=",num1,num2);		//打印题目			
	}	
	else	//20以内的小数除法，商保留两位小数的除法运算
	{
		num1=(float)rand_num(0,20);
		num2=(float)rand_num(0,20);		
		answer=21;
		while(answer>20)		//生成小于20的积 
		{
			num1=(float)rand_num(0,20);
			num2=(float)rand_num(0,20); 
			answer=num1*num2;
		} 
		num3=(float)rand_num(0,100)/100;	//生成两位以内小数 
		num1+=num3;						 
		num3=(float)rand_num(0,100)/100; 
		num2+=num3;
		answer=num1*num2;
		answer=(int)(answer*100)/100.0; //去掉多余的小数（保留两位小数） 
		printf("%.2f/.2f=",answer,num2);//保留两位小数输出
		answer/=num2;	//重新计算答案 
	} 
	return answer; 
}



/***************生成六年级题目****************/ 
float program_6()
{
	system("cls");
	float num1,num2,num3,answer;	//从四年级开始都使用浮点数 
	char c=rand_num(0,6);
	if(c==0) //百分数转小数 
	{
		num1=(float)rand_num(0,100);
		printf("%.0f\%转化为小数是：",num1);		//输出百分号要用\取消%的功能 
		answer=num1/100; 	 
	}
	else if(c==1)	//求圆的面积 
	{
		num1=(float)rand_num(0,20);
		printf("半径为%.0f的圆的面积是（pi=3.14）：",num1);	 
		answer=3.14*num1*num1; 
	} 
	else if(c==2)	//求圆的周长 
	{
		num1=(float)rand_num(0,20);
		printf("半径为%.0f的圆的周长是（pi=3.14）：",num1);	 
		answer=3.14*num1*2; 
	}	
	else if(c==3)	//求圆柱的体积 
	{
		num1=(float)rand_num(0,20);
		num2=(float)rand_num(0,20);
		printf("底面半径为%.0f，高为%.0f的圆柱的体积是（pi=3.14）：",num1,num2);	 
		answer=3.14*num1*num1*num2; 
	}
	else if(c==4)	//求圆锥的体积 
	{
		num1=(float)rand_num(0,20);
		num2=(float)rand_num(0,20);
		printf("底面半径为%.0f，高为%.0f的圆锥的体积是（pi=3.14）：",num1,num2);	 
		answer=3.14*num1*num1*num2/3; 
	}
	return answer;	
}
