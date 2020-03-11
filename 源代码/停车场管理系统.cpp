#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define TRUE 1
#define FALSE 0
#define MAX 3

//定义时间结构体 
typedef struct time
{
	int hour;
	int min;
}Time;

//定义车辆结构体，包括：车牌号、到达时间、离开时间 
typedef struct car
{
	char num[10];
	Time intime;
	Time outtime;
}CarData;


//定义停车场（顺序栈） 
typedef struct Park
{
	CarData data[MAX+1];//用来存放车辆信息，大小为MAX+1，因为从1开始记录车辆 
	int top;//记录栈顶  
}Stack;

//定义结点，包括：车辆的数据和一个指针，指针指向下一辆车 
typedef struct node
{
	CarData cardata;
	node *next;
}QueueNode;

//定义便道（链栈）
typedef struct SideWalk
{
	QueueNode *front;//队列的头指针，指向结点 
	QueueNode *rear;//队列的尾指针 ，指向结点 
}Queue;

//初始化栈，因为要改变栈的内容，所以这里的参数应该是地址
void InitStack(Stack *S)
{
	S->top=0;//表示栈空 
}

//初始化栈
int InitQueue(Queue *Q)
{
	Q->front=(QueueNode *)malloc(sizeof(QueueNode));
	if(Q->front!=NULL)
	{
		Q->rear=Q->front;
		Q->front->next=NULL;
		return(TRUE);
	}
	else
	{
		return(FALSE);
	}
}

//计算车辆在停车场停留的时间，及停车的费用 
void TimeLong(CarData x)
 {
 	int hour,min,sum,cost;
 	if(x.intime.hour<=x.outtime.hour)
 	{
 		hour=x.outtime.hour-x.intime.hour;
	}
	else
	{
		hour=24-x.intime.hour+x.outtime.hour;
	}
	if(x.intime.min<=x.outtime.min)
	{
		min=x.outtime.min-x.intime.min;
	}
	else
	{
		min=60-x.intime.min+x.outtime.min;
	}
	sum=hour*60+min;
	cost=sum*0.05;
	printf("\n该车辆在停车场中共停留%d分钟，共花费%d元。\n\n",sum,cost);
 }
 
 //车辆到达，这里参数为栈,队列
 //若停车场没有停满，则车辆进栈；若停车场停满，则车辆进入便道等待 
void Arrive(Stack *S,Queue *Q)
{
	CarData x;
	QueueNode *p;//定义一个结点p
	p=(QueueNode *)malloc(sizeof(QueueNode));
	printf("请输入该车辆的车牌号：");
	scanf("%s",x.num);//获取车牌号，这里num是数组，不需要地址符 
	p->cardata=x;//将x的值赋给p的数据域 
	if(S->top==MAX)//停车场已满
	{
		if(p!=NULL)
		{
			p->cardata=x;
			p->next=NULL;
			Q->rear->next=p;
			Q->rear=p;
			printf("\n停车场已满！车辆进入便道等待。\n\n");
		}
	}
	else
	{
		printf("\n请输入车辆进入停车场的时间：");
		scanf("%d%d",&x.intime.hour,&x.intime.min);//这里hour和min是int性，需要地址符，否则数据无法输入 
		printf("\n时间记录成功！\n");
		S->top++;//栈顶记录加一 
		S->data[S->top]=x;//将车辆信息放到停车场的数据数组中
		printf("\n车辆成功进入停车场！\n");
		printf("\n该车辆的位置是：%d。\n\n",S->top);
		
	}
}

//输出离开的车辆的信息 
void Print(Stack *S)
{
	printf("\n请输入车辆离开的时间：");
	scanf("%d%d",&S->data[S->top].outtime.hour,&S->data[S->top].outtime.min);
	TimeLong(S->data[S->top]);
}

//车辆离开，这里参数为栈、临时栈、队列
//车辆离开时，其后面的车辆进入临时栈，该车辆出栈，临时栈车辆进入停车场，若停车场未满，便道车辆进入停车场 
void Leave(Stack *S,Stack *T,Queue *Q)
{
	int seat;//记要离开的车辆的位置 
	int x=1;
	CarData s,t;
	QueueNode *q;
	printf("请输入要离开的车辆的位置：");
	scanf("%d",&seat);
	while(x)//若输入错误则重新输入，直到输入正确为止
	{
		if(seat<=0||seat>MAX||seat>S->top)
		{
			printf("\n输入错误或该位置没有车！请重新输入。\n");//输出提示信息 
		}
		else  //输入位置合理 
		{
			x=0;//输入正确，循环只执行一次 
			while(seat<S->top)//seat位置后面的车先出栈，进入临时栈 
			{
				//车辆出栈 
				t=S->data[S->top];//把栈顶元素的值赋给x
				S->top--;//栈顶位置减一 
				//车辆进入临时栈 
				T->top++;//临时栈栈顶记录加一 
				T->data[T->top]=t;//将车辆信息放到停车场的数据数组中
			}
			//这里要输出提示信息
			Print(S);
			//seat位置车辆出栈 
			s=S->data[S->top];//把栈顶元素的值赋给x
			S->top--;//栈顶位置减一 
			
			//临时栈中的元素全部进入到停车场中
			while(T->top>0) 
			{
				t=T->data[T->top];//把临时栈的栈顶元素的值赋给x
				T->top--;//栈顶位置减一 
				S->top++;
				S->data[S->top]=t;//车辆进入停车场 
			}
			//临时栈中的车全部进入停车场后，便道的车进入停车场，直到停车场满为止 
			//先判断便道是否有车
			if(Q->rear!=Q->front)//如果队列不为空 
			{
				//便道中的第一辆车出队 
				q=Q->front->next;//p结点指向便道中的第一辆车，储存信息 
				Q->front->next=q->next;//队头元素出队
				if(Q->rear==q)//如果队伍中只有一个元素p，则p出队后成为空队 
				{
					Q->rear=Q->front;
				}	
				s=q->cardata;
				//该车辆进入停车场 
				S->top++;
				S->data[S->top]=s; 
				free(q);
				printf("\n请输入%s车辆进入停车场的时间：",S->data[S->top].num);
				scanf("%d%d",&S->data[S->top].intime.hour,&S->data[S->top].intime.min); 
				printf("\n车牌号为%s的车辆进入停车场的%d位置。\n\n",S->data[S->top].num,S->top);
			}
		}
	}
}

void menu_List()
{
	printf("**************************************************\n");
	printf("*                    显示菜单                    *\n");
	printf("**************************************************\n");
	printf("*                1.显示停车场信息                *\n");
	printf("*                2.显示便道信息                  *\n");
	printf("*                3.退出                          *\n");
	printf("**************************************************\n");
}

//显示停车场车辆情况
void StackList(Stack S)
{
	int i=1;
	if(S.top==0)//停车场中没有车
	{
		printf("\n停车场中没有车！\n\n");
	}
	else
	{
		printf("\n停车场的情况为：\n");
		while(i<=S.top)
		{
			printf("车牌号：%s\t到达时间：%d：%d\t位置：%d\n",S.data[i].num,S.data[i].intime.hour,S.data[i].intime.min,i);
			i++;
		}
		printf("\n");
	}
}

//显示便道的情况
void QueueList(Queue *Q)
{
	QueueNode *p;
	p=Q->front->next;
	if(Q->front!=Q->rear)//便道上有车
	{
		printf("\n等待的车辆的车牌号为：\n");
		while(p!=NULL)
		{
			printf("%s\n",p->cardata.num);
			p=p->next;
		}
		printf("\n");
	}
	else//便道上没有车
	{
		printf("\n便道上没有车！\n\n");
	}
}

void List(Stack S,Queue Q)
{
	int x=1,n;
	while(x)
	{
		system("cls");
		menu_List();
		printf("请输入您的选择：");
		scanf("%d",&n);
		switch(n)
		{
			case 1:system("cls");
				   StackList(S);
				   system("pause");
				   break;
			case 2:system("cls");
				   QueueList(&Q);
				   system("pause");
				   break;
			case 3:x=0;break;
			default:printf("\n指令错误！请重新输入。\n\n");
		}
	}
}

void menu_main()
{
	printf("**************************************************\n");
	printf("*                      菜单                      *\n");
	printf("**************************************************\n");
	printf("*                 1.车辆到达                     *\n");
	printf("*                 2.车辆离开                     *\n");
	printf("*                 3.显示车场现状                 *\n");
	printf("*                 4.退出                         *\n");
	printf("**************************************************\n");
}

int main()
{
  	Stack S,T;
  	Queue Q;
  	int x=1,n;
  	InitStack(&S);  //初始化停车场 
  	InitStack(&T);   //初始化临时栈
  	InitQueue(&Q);   //初始化便道
  	while(x)
  	{
  		system("cls");
    	menu_main();
    	printf("请输入您的选择：");
    	while(1)
    	{
    		scanf("%d",&n);
      		if(x>=1&&x<=4)
      		{
      			break;
			}
        	else
        	{
        		printf("\n输入错误！请输入正确的指令。\n");
			}
    	}
    	switch(n)
    	{
    		case 1:system("cls");
				   Arrive(&S,&Q);
				   system("pause");
      			   break;
    		case 2:system("cls");
				   Leave(&S,&T,&Q);
				   system("pause");
      			   break;
    		case 3:system("cls");
				   List(S,Q);
				   system("pause");
      			   break;
    		case 4:x=0;break;  //退出程序
    		default:printf("\n请输入正确指令！\n");
    	}
  	}
  	printf("\n感谢您的使用！\n");
  	return 0;
}

