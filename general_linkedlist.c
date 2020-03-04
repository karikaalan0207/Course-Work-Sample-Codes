#include<stdio.h>
#include<stdlib.h>
#include<string.h>


struct gll
{
	int dsize;
	int dt;
	int (*compareFn)(void *,void *,int);
	struct node *list;
	struct student *st;

};
struct student {
       char fname[20]; /* stores the 1st name of the student */

       char surname[20]; /* stores the surname of the student */

       int roll; /* stores the roll number of the student */

       struct student *next; /* points to the next node in the liked-list */

};
struct node
{
	void *data;
	struct node *next;
			
};

int compare(void *a,void *b,int dt)
{
	if(dt==1)
	{
		if((*(int *)a)>(*(int *)b))
			return 1;
		else if((*(int *)a)==(*(int *)b))
			return 0;
		else if ((*(int *)a)<(*(int *)b))
			return -1;
	}
	if(dt==2)
	{
		if((*(char *)a)>(*(char *)b))
			return 1;
		else if((*(char *)a)==(*(char *)b))
			return 0;
		else if ((*(char *)a)<(*(char *)b))
			return -1;
	}
	if(dt==3)
	{
		if((*(float *)a)>(*(float *)b))
			return 1;
		else if((*(float *)a)==(*(float *)b))
			return 0;
		else if ((*(float *)a)<(*(float *)b))
			return -1;
	}

}

struct gll *creategll(int dsize,int(*cfunction)(void *,void *,int),int dty)
{
	struct gll *new=(struct gll *)malloc(sizeof(struct gll));
	new->dsize=dsize;
	new->compareFn=cfunction;
	new->list==NULL;
	new->st==NULL;
	new->dt=dty;
	return new;
}

void addnodesorted(struct gll *g,void *d,struct student s)
{
	if(g->dt!=4)
	{
	struct node *new=(struct node *)malloc(sizeof(struct node));
	struct node *t;
	(new->data)=malloc(g->dsize);
	new->next=NULL;
	int i;
	//copying
	if(g->dt==1)
	{
		for (int i = 0; i < g->dsize; ++i)
		{
			*(int *)(new->data+i)=*(int *)(d+i);
		}
		
	}
	if(g->dt==3)
	{
		for (int i = 0; i < g->dsize; ++i)
		{
			*(float *)(new->data+i)=*(float *)(d+i);
		}
	}
	if(g->dt==2)
	{
		
		for (int i = 0; i < g->dsize; ++i)
		{
			*(char *)(new->data+i)=*(char *)(d+i);
		}
	};

	if(g->list==NULL)
	{
		g->list=new;

	}
	else{
		struct node *tempx=g->list;
		if(g->compareFn(tempx->data,new->data,g->dt)==1)
		{
			new->next=g->list;
			g->list=new;
		}
		else
		{	
			while(tempx!=NULL && (g->compareFn)(tempx->data,new->data,g->dt)== -1)
			{
			
				t=tempx;
				tempx=tempx->next;
			}
			
			t->next=new;
			new->next=tempx;
			
			
		}
	}
	}
	else
	{
	struct student *new=(struct student *)malloc(sizeof(struct student));
	strcpy(new->fname,s.fname);
	strcpy(new->surname,s.surname);
	
	new->roll=s.roll;
	new->next=NULL;


	if(g->st==NULL)
	{
		g->st=new;
		
	}
	else
	{	struct student *reg,*x=g->st;
		if((g->st)->roll>s.roll)
		{
			new->next=g->st;
			g->st=new;
			
		}
		else
		{
			while(x!=NULL && x->roll<s.roll)
			{
				reg=x;
				x=x->next;
			}

			reg->next=new;
			new->next=x;
			
		}
	}

	}
}	

void addnodelast(struct gll *g,void *d,struct student s)
{		

	if(g->dt!=4)
	{
	struct node *new=(struct node *)malloc(sizeof(struct node));
	(new->data)=malloc(g->dsize);
	new->next=NULL;
	int i=0;
	//copying
	if(g->dt==1)
	{
		for (int i = 0; i <g->dsize; ++i)
		{
			*(int *)(new->data+i)=*(int *)(d+i);
		}
		
	}
	if(g->dt==3)
	{
		for (int i = 0; i < g->dsize; ++i)
		{
			*(float *)(new->data+i)=*(float *)(d+i);
		}
	}
	if(g->dt==2)
	{
		
		for (int i = 0; i <g->dsize; ++i)
		{
			*(char *)(new->data+i)=*(char *)(d+i);
		}
	};

	if(g->list==NULL)
	{
		g->list=new;
	}
	else{
			struct node *reg,*tempx=g->list;
			while(tempx!=NULL)
			{
				reg=tempx;
				tempx=tempx->next;
			}

			reg->next=new;
			new->next=tempx;

		}
	}
	else
	{
	struct student *new=(struct student *)malloc(sizeof(struct student));
	strcpy(new->fname,s.fname);
	strcpy(new->surname,s.surname);
	struct student *reg;
	new->roll=s.roll;
	new->next=NULL;


	if(g->st==NULL)
	{
		g->st=new;
	}
	else{
			struct student *reg,*tempx=g->st;
			while(tempx!=NULL)
			{
				reg=tempx;
				tempx=tempx->next;
			}

			reg->next=new;
			new->next=tempx;

		}
	}
}

int ispresent(struct gll g,void *dss,struct student s)
{
	if(g.dt!=4)
 {
	int c=0,d=1;
	struct node *temp=g.list;
	while(temp!=NULL&&d==1)
	{
		if((*g.compareFn)(temp->data,dss,g.dt)==0)
		{
			d=0;
		}
		else
		{
			temp=temp->next;
			++c;
		}
	}

	if(d==1)
	{
		return 0;
	}
	else
		return c+1;
 }
	
	else
	{
		int c=0;
		struct student *head=g.st;
	while(head!=NULL)
	{	
		if((head->roll==s.roll) && !(strcmp(head->fname,s.fname)) && !(strcmp(head->surname,s.surname)))
		{
			return c+1;
		}
		++c;
		head=head->next;
	}
	return 0;
	}
}

int delete(struct gll *g,void *d,struct student s)
{
	if(g->dt!=4)
	{struct node *t1,*temp=g->list;
	int c=0,x=0;
	while(temp!=NULL)
	{
		if((g->compareFn)(d,temp->data,g->dt)==0)
		{
			if(x>0)
			{t1->next=temp->next;
			free(temp);
			return c+1;}
			else
			{
				g->list=temp->next;
				free(temp);
				return c+1;
			}
		}
		else
		{
			t1=temp;
			temp=temp->next;
			++c;
			++x;
		}
	}
	}

	else{
		struct student *head=g->st;
	
	struct student *tem;
	int c=0;
	while(head!=NULL && strcmp(head->fname,s.fname) && strcmp(head->surname,s.surname) && head->roll!=s.roll)
	{
		tem=head;
		head=head->next;
		++c;
	}

	tem->next=head->next;
	free(head);
	return c;
	}
	
}

int getnodedata(struct gll g,int i,void *d)
{
	
	int c=0;
	struct node *temp=g.list;
	while(c<i)
	{
		temp=temp->next;
		++c;
	}

	if(g.dt==1)
	{
		for(i=0;i<g.dsize;++i)
			*(int *)(d+i)=*(int *)(temp->data+i);
	}
	if(g.dt==3)
	{
		for(i=0;i<g.dsize;++i)
		*(float *)(d+i)=*(float *)(temp->data+i);
	}
	if(g.dt==2)
	{
		for(i=0;i<g.dsize;++i)
		*(char *)(d+i)=*(char *)(temp->data+i);
	}

	return 1;
	
	
	
}

void printall(struct gll g)
{
	if(g.dt!=4)
	{struct node *temp=g.list;
	int a,i;char b[g.dsize];float c[g.dsize];
	while(temp!=NULL)
	{
		if(g.dt==1)
		{	
			for(i=0;i<g.dsize;++i)
			{	
				a=*(int *)(temp->data+i);
				printf("%d ",a);
			}
			printf("\n");
			temp=temp->next;

		}
		if(g.dt==2)
		{
			for(i=0;i<g.dsize;++i)
			{	
				b[i]=*(char *)(temp->data+i);
				printf("%c ",b[i]);
			}
			printf("\n");
			temp=temp->next;
		}
		if(g.dt==3)
		{
			for(i=0;i<g.dsize;++i)
			{	
				c[i]=*(float *)(temp->data+i);
				printf("%f ",c[i]);
			}
			printf("\n");
			temp=temp->next;
		}
	}
	}
	else{
			struct student *head=g.st;
	while(head!=NULL)
	{
		printf("NAME   ROLL\n");
		printf(" %s %s  %d \n",head->fname,head->surname,head->roll);
		head=head->next;
	}
	

	}
}



int main()
{

	int c=-1,i,j,n,d1,ds,r,f;
	char x;
	struct gll g[5],*nx;
	struct student s,*head=NULL;
	do
	{

		printf("Enter 1) Create GLL 2) Insert Node 3) Is Present 4) Delete 5) Get Data 6) Print All 0) exit\n");
		scanf("%d",&c);

		switch(c)
		{
			case 1:	{
						printf("Enter the nth GLL\n");
						scanf("%d",&n);
						printf("Enter 1-INT 2-CHAR 3-FLOAT 4-STRUCT STUDENT\n");
						scanf("%d",&j);
						nx=creategll(1,compare,j);
						g[n]=*nx;
						break;
					}
			case 2: {	if(g[n].dt!=4)
						{printf("Enter the nth GLL\n");
						scanf("%d",&n);
						printf("1 for sorted 2 for last add\n");
						scanf("%d",&j);
						printf("Enter data\n");
						int h[g[n].dsize];
						char v;
						float  f1[g[n].dsize];
						if(g[n].dt==1)
						{
							
							for(f=0;f<g[n].dsize;++f)
								scanf("%d",&h[f]);
							if(j==1)	
								addnodesorted(&g[n],h,s);	
							else
								addnodelast(&g[n],h,s);
						}						
						if(g[n].dt==2)
						{
							scanf("%c",&x);
							scanf("%c",&v);							
							if(j==1)	
								addnodesorted(&g[n],&v,s);	
							else
								addnodelast(&g[n],&v,s);
						}
						if(g[n].dt==3)
						{
							
							for(f=0;f<g[n].dsize;++f)
								scanf("%f",&f1[f]);
							
							if(j==1)	
								addnodesorted(&g[n],f1,s);	
							else
								addnodelast(&g[n],f1,s);
						}
					}
					else
					{	float f1;
						printf("Enter Fname Sname Roll\n");
						scanf("%s",s.fname);
						scanf("%s",s.surname);
						scanf("%d",&s.roll);
						printf("1 for sorted 2 for last add\n");
						scanf("%d",&j);
						if(j==1)	
								addnodesorted(&g[n],&f1,s);	
							else
								addnodelast(&g[n],&f1,s);
						
					}
					break;
					}
			case 3:
					{
						if(g[n].dt!=4)
							{printf("Enter the gll no & character to be checked \n");
						int h[g[n].dsize];
						char v;
						float  f1[g[n].dsize];
						scanf("%d",&n);
						if(g[n].dt==1)
						{
							
							for(f=0;f<g[n].dsize;++f)
								scanf("%d",&h[f]);
							r=ispresent(g[n],h,s);
							printf("%d\n",r );
						}						
						if(g[n].dt==2)
						{
							scanf("%c",&x);
							v=getchar();
							r=ispresent(g[n],&v,s);
							printf("%d\n",r );
						}
						if(g[n].dt==3)
						{
							
							for(f=0;f<g[n].dsize;++f)
								scanf("%f",&f1[f]);
							r=ispresent(g[n],f1,s);
							printf("%d\n",r );
						}
					}
					else{
							float f1;
							printf("Enter Fname Sname Roll\n");
						scanf("%s",s.fname);
						scanf("%s",s.surname);
						scanf("%d",&s.roll);
						i=ispresent(g[n],&f1,s);
						if(i==0)
							{printf("%d Not present\n",i);}
						else
							{printf("present at %d \n",i);}

					}
						break;

					}
			case 4: 
					{
						if(g[n].dt!=4)
						{
							printf("Enter the gll no & character to be deleted\n");
						
						scanf("%d",&n);
						int h[g[n].dsize];
						char v;
						float  f1[g[n].dsize];
						if(g[n].dt==1)
						{
							
							for(f=0;f<g[n].dsize;++f)
								scanf("%d",&h[f]);
							r=delete(&g[n],h,s);
							printf("%d\n",r );
						}						
						if(g[n].dt==2)
						{
							scanf("%c",&x);
							v=getchar();
							r=delete(&g[n],&v,s);
							printf("%d\n",r );
						}
						if(g[n].dt==3)
						{
							
							for(f=0;f<g[n].dsize;++f)
								scanf("%f",&f1[f]);
							r=delete(&g[n],f1,s);
							printf("%d\n",r );
						}
						}
						else
						{	float f1;
							printf("Enter Fname Sname Roll\n");
						scanf("%s",s.fname);
						scanf("%s",s.surname);
						scanf("%d",&s.roll);
						r=delete(&g[n],&f1,s);
						printf("node deleted\n");
						}
						break;
					}
			case 5:
					{
						printf("Enter the gll no & pos. to get\n");
						
						scanf("%d",&n);
						int pos;
						scanf("%d",&pos);
						if(g[n].dt==1)
						{
							int h;
							r=getnodedata(g[n],pos-1,&h);
							printf("%d %d\n",h,r);
						}						
						if(g[n].dt==2)
						{
							char v;
							r=getnodedata(g[n],pos-1,&v);
							printf("%c %d\n",v,r );
						}
						if(g[n].dt==3)
						{	float f;
							r=getnodedata(g[n],pos-1,&f);
							printf("%f %d\n",f,r );
						}
						break;
					}	
			case 6:
					{
						printf("Enter the gll no to print \n");
						scanf("%d",&n);
						printall(g[n]);
					}						
		}
		
	}while(c!=0);
		return 0;
}
