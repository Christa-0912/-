#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define TRUE 1
#define FALSE 0
#define MAX 3

//����ʱ��ṹ�� 
typedef struct time
{
	int hour;
	int min;
}Time;

//���峵���ṹ�壬���������ƺš�����ʱ�䡢�뿪ʱ�� 
typedef struct car
{
	char num[10];
	Time intime;
	Time outtime;
}CarData;


//����ͣ������˳��ջ�� 
typedef struct Park
{
	CarData data[MAX+1];//������ų�����Ϣ����СΪMAX+1����Ϊ��1��ʼ��¼���� 
	int top;//��¼ջ��  
}Stack;

//�����㣬���������������ݺ�һ��ָ�룬ָ��ָ����һ���� 
typedef struct node
{
	CarData cardata;
	node *next;
}QueueNode;

//����������ջ��
typedef struct SideWalk
{
	QueueNode *front;//���е�ͷָ�룬ָ���� 
	QueueNode *rear;//���е�βָ�� ��ָ���� 
}Queue;

//��ʼ��ջ����ΪҪ�ı�ջ�����ݣ���������Ĳ���Ӧ���ǵ�ַ
void InitStack(Stack *S)
{
	S->top=0;//��ʾջ�� 
}

//��ʼ��ջ
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

//���㳵����ͣ����ͣ����ʱ�䣬��ͣ���ķ��� 
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
	printf("\n�ó�����ͣ�����й�ͣ��%d���ӣ�������%dԪ��\n\n",sum,cost);
 }
 
 //��������������Ϊջ,����
 //��ͣ����û��ͣ����������ջ����ͣ����ͣ���������������ȴ� 
void Arrive(Stack *S,Queue *Q)
{
	CarData x;
	QueueNode *p;//����һ�����p
	p=(QueueNode *)malloc(sizeof(QueueNode));
	printf("������ó����ĳ��ƺţ�");
	scanf("%s",x.num);//��ȡ���ƺţ�����num�����飬����Ҫ��ַ�� 
	p->cardata=x;//��x��ֵ����p�������� 
	if(S->top==MAX)//ͣ��������
	{
		if(p!=NULL)
		{
			p->cardata=x;
			p->next=NULL;
			Q->rear->next=p;
			Q->rear=p;
			printf("\nͣ���������������������ȴ���\n\n");
		}
	}
	else
	{
		printf("\n�����복������ͣ������ʱ�䣺");
		scanf("%d%d",&x.intime.hour,&x.intime.min);//����hour��min��int�ԣ���Ҫ��ַ�������������޷����� 
		printf("\nʱ���¼�ɹ���\n");
		S->top++;//ջ����¼��һ 
		S->data[S->top]=x;//��������Ϣ�ŵ�ͣ����������������
		printf("\n�����ɹ�����ͣ������\n");
		printf("\n�ó�����λ���ǣ�%d��\n\n",S->top);
		
	}
}

//����뿪�ĳ�������Ϣ 
void Print(Stack *S)
{
	printf("\n�����복���뿪��ʱ�䣺");
	scanf("%d%d",&S->data[S->top].outtime.hour,&S->data[S->top].outtime.min);
	TimeLong(S->data[S->top]);
}

//�����뿪���������Ϊջ����ʱջ������
//�����뿪ʱ�������ĳ���������ʱջ���ó�����ջ����ʱջ��������ͣ��������ͣ����δ���������������ͣ���� 
void Leave(Stack *S,Stack *T,Queue *Q)
{
	int seat;//��Ҫ�뿪�ĳ�����λ�� 
	int x=1;
	CarData s,t;
	QueueNode *q;
	printf("������Ҫ�뿪�ĳ�����λ�ã�");
	scanf("%d",&seat);
	while(x)//������������������룬ֱ��������ȷΪֹ
	{
		if(seat<=0||seat>MAX||seat>S->top)
		{
			printf("\n���������λ��û�г������������롣\n");//�����ʾ��Ϣ 
		}
		else  //����λ�ú��� 
		{
			x=0;//������ȷ��ѭ��ִֻ��һ�� 
			while(seat<S->top)//seatλ�ú���ĳ��ȳ�ջ��������ʱջ 
			{
				//������ջ 
				t=S->data[S->top];//��ջ��Ԫ�ص�ֵ����x
				S->top--;//ջ��λ�ü�һ 
				//����������ʱջ 
				T->top++;//��ʱջջ����¼��һ 
				T->data[T->top]=t;//��������Ϣ�ŵ�ͣ����������������
			}
			//����Ҫ�����ʾ��Ϣ
			Print(S);
			//seatλ�ó�����ջ 
			s=S->data[S->top];//��ջ��Ԫ�ص�ֵ����x
			S->top--;//ջ��λ�ü�һ 
			
			//��ʱջ�е�Ԫ��ȫ�����뵽ͣ������
			while(T->top>0) 
			{
				t=T->data[T->top];//����ʱջ��ջ��Ԫ�ص�ֵ����x
				T->top--;//ջ��λ�ü�һ 
				S->top++;
				S->data[S->top]=t;//��������ͣ���� 
			}
			//��ʱջ�еĳ�ȫ������ͣ�����󣬱���ĳ�����ͣ������ֱ��ͣ������Ϊֹ 
			//���жϱ���Ƿ��г�
			if(Q->rear!=Q->front)//������в�Ϊ�� 
			{
				//����еĵ�һ�������� 
				q=Q->front->next;//p���ָ�����еĵ�һ������������Ϣ 
				Q->front->next=q->next;//��ͷԪ�س���
				if(Q->rear==q)//���������ֻ��һ��Ԫ��p����p���Ӻ��Ϊ�ն� 
				{
					Q->rear=Q->front;
				}	
				s=q->cardata;
				//�ó�������ͣ���� 
				S->top++;
				S->data[S->top]=s; 
				free(q);
				printf("\n������%s��������ͣ������ʱ�䣺",S->data[S->top].num);
				scanf("%d%d",&S->data[S->top].intime.hour,&S->data[S->top].intime.min); 
				printf("\n���ƺ�Ϊ%s�ĳ�������ͣ������%dλ�á�\n\n",S->data[S->top].num,S->top);
			}
		}
	}
}

void menu_List()
{
	printf("**************************************************\n");
	printf("*                    ��ʾ�˵�                    *\n");
	printf("**************************************************\n");
	printf("*                1.��ʾͣ������Ϣ                *\n");
	printf("*                2.��ʾ�����Ϣ                  *\n");
	printf("*                3.�˳�                          *\n");
	printf("**************************************************\n");
}

//��ʾͣ�����������
void StackList(Stack S)
{
	int i=1;
	if(S.top==0)//ͣ������û�г�
	{
		printf("\nͣ������û�г���\n\n");
	}
	else
	{
		printf("\nͣ���������Ϊ��\n");
		while(i<=S.top)
		{
			printf("���ƺţ�%s\t����ʱ�䣺%d��%d\tλ�ã�%d\n",S.data[i].num,S.data[i].intime.hour,S.data[i].intime.min,i);
			i++;
		}
		printf("\n");
	}
}

//��ʾ��������
void QueueList(Queue *Q)
{
	QueueNode *p;
	p=Q->front->next;
	if(Q->front!=Q->rear)//������г�
	{
		printf("\n�ȴ��ĳ����ĳ��ƺ�Ϊ��\n");
		while(p!=NULL)
		{
			printf("%s\n",p->cardata.num);
			p=p->next;
		}
		printf("\n");
	}
	else//�����û�г�
	{
		printf("\n�����û�г���\n\n");
	}
}

void List(Stack S,Queue Q)
{
	int x=1,n;
	while(x)
	{
		system("cls");
		menu_List();
		printf("����������ѡ��");
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
			default:printf("\nָ��������������롣\n\n");
		}
	}
}

void menu_main()
{
	printf("**************************************************\n");
	printf("*                      �˵�                      *\n");
	printf("**************************************************\n");
	printf("*                 1.��������                     *\n");
	printf("*                 2.�����뿪                     *\n");
	printf("*                 3.��ʾ������״                 *\n");
	printf("*                 4.�˳�                         *\n");
	printf("**************************************************\n");
}

int main()
{
  	Stack S,T;
  	Queue Q;
  	int x=1,n;
  	InitStack(&S);  //��ʼ��ͣ���� 
  	InitStack(&T);   //��ʼ����ʱջ
  	InitQueue(&Q);   //��ʼ�����
  	while(x)
  	{
  		system("cls");
    	menu_main();
    	printf("����������ѡ��");
    	while(1)
    	{
    		scanf("%d",&n);
      		if(x>=1&&x<=4)
      		{
      			break;
			}
        	else
        	{
        		printf("\n���������������ȷ��ָ�\n");
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
    		case 4:x=0;break;  //�˳�����
    		default:printf("\n��������ȷָ�\n");
    	}
  	}
  	printf("\n��л����ʹ�ã�\n");
  	return 0;
}

