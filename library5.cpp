#include <string.h>
#include <fstream>
#include<iomanip>
#include <iostream>
#include<string.h>
using namespace std;
class Reader							//存储读者信息的类
{
public: 
	char ReaderName[50];				//读者姓名
	char Password[50];					//密码
	char book1[30], book2[30];			//每人最多借两本书,可以根据需要增减限额,book储存ISBN号
	int y_n;							//记录借的书的数目,0 为没有借书,1 为借了一本,2 为借了二本
	Reader *next;						//指向下一节点的指针
};
/****读者类链表****/
class ReaderList {						//表明链表中的第几个节点
public:
	static Reader * point, *head_point;		//定义两个 Rreader 指针,head_point 为头指针,point 为活动指针
 	static int o;
	ReaderList()						//构造函数,使指针初始化
	{
		head_point = new Reader[sizeof(Reader)];
		 point = new Reader[sizeof(Reader)];
		strcpy(head_point->ReaderName,"0");
		head_point->next = NULL;
		point->next = NULL;
		o = 0;//读者数量
	} 
	static void save_readerfile()					//存储文件,存在链表里 
	{
		string r1,r2,r3,r4;
		fstream file;
		Reader *p;
		p=  new Reader[sizeof(Reader)];
		file.open("library//reader.csv",ios::in | ios::out);
		if(!file)
		{
			cout<<"reader.csv not open file"<<endl;
		}
		getline(file,r1,',');
		strcpy(p->ReaderName,&r1[0]);
		strcpy(head_point->ReaderName,&r1[0]);
		getline(file,r2,',');
		strcpy(p->Password,&r2[0]);
		strcpy(head_point->Password,&r2[0]);
		getline(file,r3,',');
		strcpy(p->book1,&r3[0]);
		strcpy(head_point->book1,&r3[0]);
		getline(file,r4,'\n');
		strcpy(p->book2,&r4[0]);
		strcpy(head_point->book2,&r4[0]);
		point =head_point; 
		while(!file.eof())
		{
			p=  new Reader[sizeof(Reader)];
			getline(file,r1,',');
			if(r1=="")//增强鲁棒性，如果文件被换行，最后一行为空，不加的话会最后一个节点错误
			{
				break;
			}
			strcpy(p->ReaderName,&r1[0]);
			getline(file,r2,',');
			strcpy(p->Password,&r2[0]);
			getline(file,r3,',');
			strcpy(p->book1,&r3[0]);
			getline(file,r4,'\n');
			strcpy(p->book2,&r4[0]);
			p->next=NULL;
			point->next = p;
			point = p;
			o++;
		} 
		file.close();
		delete p;
	}
	static void load_readerfile()					//上传文件
	{
		Reader *q;
		q = head_point;
		fstream file;
		file.open("library//reader.csv",ios::in | ios::out|ios::trunc);
		if(!file)
		{
			cout<<"reader.csv not open file"<<endl;
		}
		while(q!=NULL)
		{
			file<<q->ReaderName<<","<<q->Password<<","<<q->book1<<","<<q->book2<<endl;
			q = q->next ;
		} 
		file.close();
	}
	static Reader* reader_register()					//读者注册
	{
		string n1,n2;	
		Reader *nw; 
		nw = new Reader[sizeof(Reader)];
		cout<<"姓名(不能超过50个字符):"<<endl;
		cin >>setw(50)>>n1;
		//设置名字长度不能超过50
		cout<<"密码:"<<endl;
		cout<<"密码(不能超过50个字符):"<<endl;
		//设置密码长度不能超过50
		cin >> n2;
		strcpy(nw->ReaderName,&n1[0]);
		strcpy(nw->Password,&n2[0]);
		strcpy(nw->book1," ");
		strcpy(nw->book2," ");
		nw->next = NULL;
		return nw;
	}
	static void Add_Point(Reader * p)				//增加新结点到链表
	{
		save_readerfile();
		if(head_point==NULL)
		{
			head_point=p;
		}
		else
		{
			point=head_point;
			while(point->next!=NULL)
			{
				point=point->next;
			}
			point->next=p;
		}
		Reader *q;
		string r1,p1,b1,b2;
		q = head_point;
		fstream file;
		file.open("library//reader.csv",ios::in | ios::out);
		if(!file)
		{
			cout<<"reader.csv not open file"<<endl;
		}
		while(q!=NULL)
		{
			file<<q->ReaderName<<","<<q->Password<<","<<q->book1<<","<<q->book2<<endl;
			// cout<<q->ReaderName<<","<<q->Password<<","<<q->book1<<","<<q->book2<<endl;
			q = q->next ;
		} 
		file.close();
	}
	static Reader* reader_land()						//读者登录
	{
		string readername,readerpass;
		cout<<"请输入您的姓名:"<<endl;
		cin >> readername;
		point=head_point->next;
		while(point!=NULL)
		{
			if(strcmp(point->ReaderName,&readername[0])==0)//查找用户
			{
				cout<<"请输入您的密码:";
				cin>> readerpass;
				if(strcmp(point->Password,&readerpass[0])==0)//核验密码
				{
					cout<<"登录成功!"<<endl; 
					return point;//返回用户指针
				}
				else
				{
					cout<<"密码错误!"<<endl; 
					return NULL;//返回空
				} 
			}
			point=point->next;//下一个
		}
		if(point==NULL)
		{
			cout<<"该用户不存在!  您可以先注册，再试试^_^"<<endl; 
		}
		return NULL;
	}
	static void show_OneReader(Reader *p)		//显示某读者信息
	{
		if(p==NULL)
		{
			return;
		}
		cout << "***********************************************" << endl;
		cout <<"姓名"<<"\t"<<p->ReaderName <<endl;
		cout <<"第一本书的ISBN号:"<<"\t"<<p->book1 <<endl;
		cout <<"第二本书的ISBN号:"<<"\t"<<p->book2 <<endl;
	}
	static void show_all()
	{
		Reader *q;
		q = head_point;
		while(q!=NULL)
		{
			cout<<q->ReaderName<<","<<q->Password<<","<<q->book1<<","<<q->book2<<endl;
			q = q->next ;
		} 
	}
	static void change_password(Reader *p)					//修改密码
	{
		if(p==NULL)
		{
			return;
		}
		Reader *point;
		point = head_point;	
		while(strcmp(point->ReaderName ,p->ReaderName)!=0)
		{
			point=point->next;//在链表中找到登录用户
		}
		string n2;
		cout<<"请输入新的密码:"<<endl;
		cin>>n2;
		strcpy(point->Password,&n2[0]);
		load_readerfile();
		cout<<"更改成功!"<<endl; 
	}
		 
	static void delete_reader(Reader *p)					//读者注销
	{
		if(p==NULL)
		{
			return;
		}
		Reader *q;//协助point指针，在p->next=point
		point = head_point;	
		q = point;
		point = point->next;
		while((strcmp(point->ReaderName ,p->ReaderName)!=0)&&point!=NULL)
		{
			q=point;
			point=point->next;
		}
		q->next=point->next;
		delete point;
		load_readerfile();
		cout<<"注销成功!"<<endl; 
		o=o-1;//读者人数减一
	}

	static void delete_readers()					//清空全部读者信息
	{
		cout<<"确定全部删除吗？ 请谨慎删除，确定请按1，否则请按其他键."<<endl;
		char h;
		cin>>h;
		if(h=='1')
		{
			Reader *p,*q;
			p = head_point->next;
			while(p!=NULL)
			{
				q=p;
				p=p->next ; 
				free(q);
			}
			head_point->next=NULL;
			load_readerfile();
			cout<<"已经成功清空全部读者信息!"<<endl;
		} 
		else
		{
			return;
		}
	}
	static void help()
	{
		cout<<"暂时没有帮助,BALABALABALA"<<endl; 
	 } 
	static void GoInto_ReaderInfo()				//读者信息菜单
	{
		char i;
		save_readerfile();
		do
		{
			cout << "***********************************************" << endl;
	 		cout << "*               读  者  功  能                *" << endl;
	 		cout << "*                                             *" << endl;
	 		cout << "*               1.登录查看                    *" << endl;
	 		cout << "*                                             *" << endl;
	 		cout << "*               2.注册                        *" << endl;
			cout << "*                                             *" << endl;
			cout << "*               3.注销                        *" << endl;
			cout << "*                                             *" << endl;
			cout << "*               4.修改密码                    *" << endl;
			cout << "*                                             *" << endl;
			cout << "*               5.查看全部读者信息#            *" << endl;
			cout << "*                                             *" << endl;
			cout << "*               6.清空全部读者信息#            *" << endl;
			cout << "*                                             *" << endl;
			cout << "*               7.帮助说明                    *" << endl;
			cout << "*                                             *" << endl;
			cout << "*               0.返回上一层                  *" << endl;
	 		cout << "*                                             *" << endl;
	 		cout << "***********************************************" << endl;
			cout<<"#号为管理员功能,需要登录管理员账号<(ˉ^ˉ)> "<<endl;
			cout <<"请输入相应功能代号:"<<endl; 
			
			cin >> i;
			Reader *p;
			
	  		switch (i)
	  		{
	  			case '1'://登录查看 
	  				p = reader_land();
				  	show_OneReader(p);
	   				break;
	  			case '2'://注册
	   				p = reader_register();
	   				Add_Point(p);
	   				cout<<"注册成功"<<endl; 
					break;
	   			case '3'://注销
				   	cout<<"先登录要注销的账号，以确定是本人"<<endl;
				    p = reader_land();
	   				delete_reader(p);
					break;
				case '4'://修改密码
					cout<<"先登录要修改密码的账号，以确定是本人"<<endl;
					p = reader_land();
					change_password(p);	
					break;
	  			case '5':
				  	cout<<"请先登录管理员的账号，再进行操作"<<endl;
					p = reader_land();
					if((p==NULL)||strcmp(p->ReaderName,"guanliyuan")!=0)//设置管理员为guanliyuan
					{
						cout<<"您不是管理员，无法进行此操作"<<endl;
						break;
					}
	  				show_all();
	  				break;
	  			case '6': 
				  	cout<<"请先登录管理员的账号，再进行操作"<<endl;
					p = reader_land();
					if((p==NULL)||strcmp(p->ReaderName,"guanliyuan")!=0)//设置管理员为guanliyuan
					{
						cout<<"您不是管理员，无法进行此操作"<<endl;
						break;
					}
	  				delete_readers();
					break; 
				case '7':
	  				help();
	  				break;
	  			case '0':
	  				break;
	  			default:cout << "输入错误，请重新输入。" << endl;
	  		}
	  	}while(i!='0');
	
	} 
};
Reader* ReaderList::head_point=new Reader[sizeof(Reader)];//读者头节点
Reader* ReaderList::point=new Reader[sizeof(Reader)];//临时读者节点
int ReaderList::o=1 ;

class Book						//存储图书信息的类
{
public:
	char *BookName;			    //书名,用于查找	
	char *Writer;			    //作者名,用于查找
	char PublishDate[20];		//出版日期,用于查找
	char ISBN[30];				//ISBN 号,用于查找
	char ebook[2];				//电子书 
	char paperbook[2];			//纸质书  
	char *Publisher;		    //出版商,用于查找
	char *BriefIntroduction;    //该书内容简介
	int i_o;					//判断书是否借出,0 为在架,1 为借出
	Book *next;					//指向下一个节点的指针
};
/****书库类链表****/
class BookList {
public:
	static Book * node;
	static Book *head_ptr ;//定义两个 Book 指针,head_ptr 为头指针,node\p 为活动指针
	static int n;	
	BookList() 
	{								 //构造函数，使指针初始化
		node = new Book[sizeof(Book)];    //存放书的信息
		head_ptr = new Book[sizeof(Book)];
		head_ptr->next = NULL;
		node->next = NULL;
	}
	static void save_file()					//存储文件
	{
		Book *p;           //临时节点
	    fstream file;
		string s1,s2,s3,s4,s5,s6,s7,s8,s9;
		char a1[1000];
		file.open("library//book.csv",ios::in | ios::out);
		if(!file)
		{
			cout<<"[save_file] book.csv not open file"<<endl;
			return;
		}
		getline(file,s1,',');
		head_ptr->BookName=new char[strlen(s1.c_str())+1];
		strcpy(head_ptr->BookName,s1.c_str());
		getline(file,s2,',');
		head_ptr->Writer=new char[strlen(s2.c_str())+1];
		strcpy(head_ptr->Writer,s2.c_str());
		getline(file,s3,',');
		strcpy(head_ptr->PublishDate,&s3[0]);
		getline(file,s4,',');
		strcpy(head_ptr->ISBN,&s4[0]);
		getline(file,s5,',');
		strcpy(head_ptr->ebook,&s5[0]);
		getline(file,s6,',');
		strcpy(head_ptr->paperbook,&s6[0]);
		getline(file,s7,',');
		head_ptr->Publisher=new char[strlen(s7.c_str())+1];
		strcpy(head_ptr->Publisher,s7.c_str());
		getline(file,s8);
		head_ptr->BriefIntroduction=new char[strlen(s8.c_str())+1];
		strcpy(head_ptr->BriefIntroduction,s8.c_str());
		node = head_ptr;
		while(!file.eof())
		{
			p = new Book[sizeof(Book)];
			getline(file,s1,',');
			if(s1=="")//增强鲁棒性，如果文件被换行，最后一行为空，不加的话会最后一个节点错误
			{
				break;
			}
			p->BookName=new char[strlen(s1.c_str())+1];
			strcpy(p->BookName,s1.c_str());
			getline(file,s2,',');
			p->Writer=new char[strlen(s2.c_str())+1];
			strcpy(p->Writer,&s2[0]);
			getline(file,s3,',');
			strcpy(p->PublishDate,&s3[0]);
			getline(file,s4,',');
			strcpy(p->ISBN,&s4[0]);
			getline(file,s5,',');
			strcpy(p->ebook,&s5[0]);
			getline(file,s6,',');
			strcpy(p->paperbook,&s6[0]);
			getline(file,s7,',');
			p->Publisher=new char[strlen(s7.c_str())+1];
			strcpy(p->Publisher,&s7[0]);
			getline(file,s8,'\n');
			p->BriefIntroduction=new char[strlen(s8.c_str())+1];
			strcpy(p->BriefIntroduction,&s8[0]);
			p->next=NULL;
			node -> next= p; 
			node = p;
			// j++;
			n++;//书的数量
			//  cout<<"书的数量: "<<n<<endl;
		}
		file.close();
		delete p;
	}
	static void load_file()					//上传文件
	{
		Book *q;
		q = head_ptr;
		fstream file;
		file.open("library//book.csv",ios::in | ios::out|ios::trunc);
		if(!file)
		{
			cout<<"[load_file] book.csv not open file"<<endl;
		}
		while(q!=NULL)
		{
			file<<q->BookName<<","<<q->Writer<<","<<q->PublishDate<<","<<q->ISBN<<","<<q->ebook<<","<<q->paperbook<<","<<q->Publisher<<","<<q->BriefIntroduction<<endl;
			q = q->next ;
		} 
		file.close();
	}
	static Book* AddNewBook()					//新书登记,对 node 指向的类对象赋值
	{
		string n1,n2,n3,n4,n5,n6,n7,n8;	
		Book *nw; 
		nw = new Book[sizeof(Book)];
		cout<<"请输入新书的以下信息:"<<endl;
		cout<<"书名:"<<endl;
		cin>>n1;
		cout<<"作者名:"<<endl;
		cin>>n2;
		cout<<"出版日期:"<<endl;
		cin>>n3;
		cout<<"ISBN 号:"<<endl;	
		cin>>n4;
		cout<<"电子书(0 为在架,1 为借出):"<<endl;
		cin>>n5;
		cout<<"纸质书(0 为在架,1 为借出):"<<endl;
		cin>>n6;
		cout<<"出版商:"<<endl;
		cin>>n7;
		cout<<"内容简介:"<<endl;
		cin>>n8;
		nw->BookName=new char[strlen(n1.c_str())+1];
		nw->Writer=new char[strlen(n2.c_str())+1];
		nw->Publisher=new char[strlen(n7.c_str())+1];
		nw->BriefIntroduction=new char[strlen(n8.c_str())+1];
		strcpy(nw->BookName,n1.c_str());
		strcpy(nw->Writer,&n2[0]);
		strcpy(nw->PublishDate,&n3[0]);
		strcpy(nw->ISBN,&n4[0]);
		strcpy(nw->ebook,&n5[0]);
		strcpy(nw->paperbook,&n6[0]);
		strcpy(nw->Publisher,&n7[0]);
		strcpy(nw->BriefIntroduction,&n8[0]);
		nw->next = NULL;
		n=n+1;
		return nw;
	}
	static  void Add_list(Book * p)			//增加结点到 Book 链表中,用于添加新书时
	{ 		
		node = head_ptr;
		while(node->next!=NULL)//找到尾节点
		{
			node=node->next;
		}
		node->next = p;//从尾部接上新节点
		node = p;
		p->next=NULL;//最后置空
		load_file();//更新文件
	}
	static void borrow_book(Reader *p)				//借书手续
	{
		Book *n;
		if (strcmp(p->book1," ")!=0 &&strcmp(p->book2 ," ")!=0)           //借书
	 	{
	 		cout<<"您已经借过2本了，不能借书了,可以先还书再借书。"<<endl;
	 	}
	 	else if(strcmp(p->book1," ")==0)
	 	{
			//找书
			n = search_ISBN(); 
			//电子书随便借，纸质书只能借两本
			cout<<"只记录纸质书借阅记录，电纸书不占用借书名额，请自行下载查看!"<<endl;
			if(strcmp(n->paperbook,"0")==0)
			{
				cout<<"《"<<n->BookName<<"》纸质书可借阅"<<endl;
				cout<<"确认借阅《"<<n->BookName<<"》纸质书吗？（确认请按1，否则按其他任意键）"<<endl;
				char temp;
				cin>>temp;
				if(temp=='1')
				{
					strcpy(p->book1,n->ISBN);//记录借的书的ISBN号
					strcpy(n->paperbook,"1");//书借出去，0->1,说明不在架了
					ReaderList::load_readerfile();//更新用户信息
					BookList::load_file();//更新书库信息
					cout<<"借书成功!!"<<endl;
				}
			}
			else
			{
				cout<<"无《"<<n->BookName<<"》的纸质书"<<endl;
			}//如果要借20本书，可以把book串成链表，有点麻烦
		}
		else if(strcmp(p->book2," ")==0)
	 	{
			//找书
			n = search_ISBN();
			//电子书随便借，纸质书只能借两本
			cout<<"只记录纸质书借阅记录，电纸书不占用借书名额，请自行下载查看!"<<endl;
			if(strcmp(n->paperbook,"0")==0)
			{
				cout<<"《"<<n->BookName<<"》纸质书可借阅"<<endl;
				cout<<"确认借阅《"<<n->BookName<<"》纸质书吗？（确认请按1，否则按其他任意键）"<<endl;
				char temp;
				cin>>temp;
				if(temp=='1')
				{
					strcpy(p->book2,n->ISBN);//记录借的书的ISBN号
					strcpy(n->paperbook,"1");//书借出去，0->1,说明不在架了
					ReaderList::load_readerfile();//更新用户信息
					BookList::load_file();//更新书库信息
					cout<<"借书成功!!"<<endl;
				}
			}
			else
			{
				cout<<"无《"<<n->BookName<<"》的纸质书"<<endl;
			}
		}
		else
		{
			cout<<"借书失败"<<endl;
		}
	}
	static void return_book(Reader *p)				//还书手续
	{
		cout << "***********************************************" << endl;
		cout <<"姓名"<<"\t"<<p->ReaderName <<endl;
		cout <<"book1"<<"\t"<<p->book1 <<endl;
		cout <<"book2"<<"\t"<<p->book2 <<endl;
  		cout<<"还书book1（按1），还书book2（按2），"<<endl;
  		char hua;
  		cin>>hua;
		Book *u; 
  		if(hua=='1'&&p->book1!=" ")
  		{	
			u=BookList::head_ptr;
			while(u!=NULL)
			{
				
				if(strcmp(u->ISBN,p->book1)==0)
				{
					strcpy(u->paperbook,"0");//在架为0
					strcpy(p->book1 ," ");//还书之后为空
					ReaderList::load_readerfile();//更新用户信息
					BookList::load_file();//更新书库信息
					cout<<"还书成功"<<endl; 
					break;
				}u=u->next ;
			}
			if(u==NULL)
			{
				cout<<"没有这本书!还书失败，请检查ISBN号"<<endl; 
			}
		}
		else if(hua=='2'&&p->book2!=" ")
		{
			u=BookList::head_ptr;
			while(u!=NULL)
			{
				
				if(strcmp(u->ISBN  ,p->book2)==0)
				{
					strcpy(u->paperbook,"0");//在架为0
					strcpy(p->book2 ," ");//还书之后为空
					ReaderList::load_readerfile();//更新用户信息
					BookList::load_file();//更新书库信息
					cout<<"还书成功"<<endl; 
					break;
				}u=u->next ;
			}
			if(u==NULL)
			{
				cout<<"没有这本书!还书失败，请检查ISBN号"<<endl; 
			}
		}
		else
		{
			cout<<"输入错误!"<<endl;
		}
	}
	static void show_book(Book *p)
	{
		cout << "***********************************************" << endl; 
		cout<<"书    名"<<"\t"<<p->BookName<<endl;
		cout<<"作    者"<<"\t"<<p->Writer<<endl;
		cout<<"出版日期"<<"\t"<<p ->PublishDate<<endl;
		cout<<"ISBN  号"<<"\t"<<p->ISBN<<endl;
		if(strcmp(p->ebook ,"0")==0)
		{
			cout<<"电子 书"<<"\t"<<"在架"<<endl;
		} 				
		if(strcmp(p->paperbook,"0")==0)
		{
			cout<<"纸质 书"<<"\t"<<"在架"<<endl;
		} 
		cout<<"出版  商"<<"\t"<<p->Publisher<<endl;
		cout<<"图书简介"<<"\t"<<p->BriefIntroduction<<endl;
		cout << "***********************************************" << endl;
	}
	static	Book* search_ISBN()			//按 ISBN 号查找图书
	{
		string cs;
		cout<<"请输入图书的ISBN 号:"<<endl;
		cin>>cs;
		Book *p;
		p=head_ptr;
		while(p!=NULL)
		{
			if(strcmp(p->ISBN  ,&cs[0])==0)
			{
				show_book(p);
				break;
			}
			p=p->next;
		}	
		if(p==NULL)
		{
			cout<<"没有找到这本书，试试查找其他书吧"<<endl;
		}
		return p;
	}
	static void search_BookName()		//按书名查找图书
	{
		string cs;
		cout<<"请输入图书的书名:"<<endl;
		cin>>cs;
		Book *p;
		int i=0;
		p=head_ptr;
		while(p!=NULL)
		{
			if(strcmp(p->BookName,&cs[0])==0)
			{
				show_book(p);
				i++;
			}
			p=p->next;
		}	
		cout<<"共找到"<<i<<"本名为《"<<cs<<"》的书"<<endl;
	}
	static	void search_Writer()			//按作者名查找图书
	{
		string cs;
		cout<<"请输入图书的作者名:"<<endl;
		cin>>cs;
		Book *p;
		int i=0;
		p=head_ptr;
		while(p!=NULL)
		{
			if(strcmp(p->Writer,&cs[0])==0)
			{
				show_book(p);
				i++;
			}
			p=p->next;
		}	
		cout<<"共找到"<<i<<"本"<<cs<<"的书"<<endl;
	}
	static	void search_Publisher()		//按出版商查找图书
	{
		string cs;
		cout<<"请输入图书的出版商:"<<endl;
		cin>>cs;
		Book *p;
		int i=0;
		p=head_ptr;
		while(p!=NULL)
		{
			if(strcmp(p->Publisher,&cs[0])==0)
			{
				show_book(p);
				i++;
			}
			p=p->next;
		}	
		cout<<"共找到"<<i<<"本"<<cs<<"的书"<<endl;
	}
	static	void search_PublishDate() 	//按出版日期查找图书
	{
		string cs;
		cout<<"请输入图书的出版日期:"<<endl;
		cin>>cs;
		int i=0;
		Book *p;
		p=head_ptr;
		while(p!=NULL)
		{
			if(strcmp(p->PublishDate,&cs[0])==0)
			{
				show_book(p);
				i++;
			}
			p=p->next;
		}	
		cout<<"共找到"<<i<<"本"<<cs<<"的书"<<endl;
	}
	static void search()						//进入查找菜单
	{	
		char r;
		do
		{
			cout << "***********************************************" << endl;
	 		cout << "*               图 书 查 找                   *" << endl;
	 		cout << "*                                             *" << endl;
	 		cout << "*               1.按 ISBN 号查找图书          *" << endl;
	 		cout << "*                                             *" << endl;
	 		cout << "*               2.按书名查找图书              *" << endl;
			cout << "*                                             *" << endl;
			cout << "*               3.按作者名查找图书            *" << endl;
			cout << "*                                             *" << endl;
			cout << "*               4.按出版商查找图书            *" << endl;
			cout << "*                                             *" << endl;
			cout << "*               5.按出版日期查找图书          *" << endl;
			cout << "*                                             *" << endl;
			cout << "*               0.返回上一层                  *" << endl;
			cout << "*                                             *" << endl;
			cout << "***********************************************" << endl;
	   		cout <<"请输入相应功能代号:"<<endl; 
	   		
	   		cin>>r;
	   		switch(r)
	   		{
	   			case '1':
	  	 			search_ISBN();
	   				break;
	  			case '2':
	   				search_BookName();
	 				break;
	   			case '3':
	   				search_Writer();
					break;
				case '4':
					search_Publisher();	
					break;
	  			case '5':
	  				search_PublishDate();
	  				break;
	  			case '0':	
					break;
	  			default:cout << "输入错误，请从新输入。" << endl;
	   					
			}
		}
		while(r!='0');
	}
	static	void show_all()					//显示所有库存的未被借出的图书
	{
		int i=0;
		Book *p;
		p=head_ptr->next;
		while(p!=NULL)
		{
			if(strcmp(p->ebook,"0")==0||strcmp(p->paperbook,"0")==0)
			{
				show_book(p);
				i++;
			}
			p=p->next;
		}	
		cout<<"共找到"<<i<<"本在架书"<<endl;
	}
	static	void delete_onebook()				//删除某本书
	{
		string ss;
		cout<<"请输入要删除的图书的ISBN号:"<<endl;
		cin>>ss;
		Book *p,*q;
		p = head_ptr;
		q=p;
		p = p->next ;
		while(strcmp(p->ISBN ,&ss[0])!=0)
		{
			q=p;
			p=p->next;
		}
		if(p==NULL)
		{
			cout<<"没有你要删除的图书的记录"<<endl;
		}
		else
		{
			q->next=p->next;
			p->next=NULL;
			delete p;
			load_file();
			cout<<"删除成功!"<<endl; 
			n=n-1;
		} 
	}
    static	void delete_allbook()				//删除所有图书
	{
		cout<<"确定全部删除吗？，请谨慎删除，确定请按1，否则请按其他键."<<endl;
		char h;
		cin>>h;
		if(h!='1')
		{
			return;
		} 
		else
		{
			Book *p,*q;
			p = head_ptr->next;
			while(p!=NULL)
			{
				q=p;
				p=p->next ; 
				free(q);
			}
			head_ptr->next=NULL;
			load_file();
			cout<<"全部图书删除成功!"<<endl;
		}
	} 
	static	void change_content()				//更改某本书的信息
	{
		Book *p; 
		p = search_ISBN();
		if(p==NULL)
		{
			return;
		}
		string n1,n2,n3,n4,n5,n6,n7;	
		char i=' ';
		do
		{
			cout << "***********************************************" << endl;
	 		cout << "*              修 改 图 书 信 息               *" << endl;
	 		cout << "*                                             *" << endl;
	 		cout << "*               1.修改书名                     *" << endl;
	 		cout << "*                                             *" << endl;
	 		cout << "*               2.修改作者名                   *" << endl;
			cout << "*                                             *" << endl;
			cout << "*               3.修改出版日期                 *" << endl;
			cout << "*                                             *" << endl;
			cout << "*               4.修改电子书(0 为在架,1 为借出) *" << endl;
			cout << "*                                             *" << endl;
			cout << "*               5.修改纸质书(0 为在架,1 为借出) *" << endl;
			cout << "*                                             *" << endl;
			cout << "*               6.修改出版商                   *" << endl;
	 		cout << "*                                             *" << endl;
			cout << "*               7.修改内容简介                 *" << endl;
	 		cout << "*                                             *" << endl;
			cout << "*               0.返回上一层                   *" << endl;
			cout << "*                                             *" << endl;
	 		cout << "***********************************************" << endl;
			cout<<endl<<endl;
			cout <<"请输入相应功能代号:"<<endl; 
			
			cin >> i;
	  		switch (i)
	  		{
	  			case '1':
	  				cout<<"新的书名:"<<endl;
					cin>>n1;
					strcpy(p->BookName,&n1[0]);//直接在链表中修改
	   				break;
	  			case '2':
	   				cout<<"新的作者名:"<<endl;
					cin>>n2;
					strcpy(p->Writer,&n2[0]);
					break;
	   			case '3':
	   				cout<<"新的出版日期:"<<endl;
					cin>>n3;
					strcpy(p->PublishDate,&n4[0]);
					break;
				case '4':
					cout<<"电子书(0 为在架,1 为借出):"<<endl;
					cin>>n4;
					strcpy(p->ebook,&n4[0]);
					break;
	  			case '5':
	  				cout<<"修改纸质书(0 为在架,1 为借出):"<<endl;
					cin>>n5;
					strcpy(p->paperbook,&n5[0]);
	  				break;
	  			case '6':
	  				cout<<"新的出版商:"<<endl;
					cin>>n6;
					strcpy(p->Publisher,&n6[0]);
					break;
	  			case '7': 
	  				cout<<"新的内容简介:"<<endl;
					cin>>n7;
					strcpy(p->BriefIntroduction,&n7[0]);
					break; 
				case '0': 
					break; 
	  			default:cout << "输入错误，请从新输入。" << endl;
	  		}
	  	}while(i!='0');
		cout<<"修改后的书"<<endl;
		show_book(p);
		load_file();
	}
	static	void GoInto_BookInfo(ReaderList rel)				//进入书库信息菜单
	{
		Book *p;
		Reader *r;
		save_file();
		rel.save_readerfile();//下载读者信息
		char i=' ';
		do
		{
			cout << "***********************************************" << endl;
	 		cout << "*               图 书 信 息 管 理             *" << endl;
	 		cout << "*                                             *" << endl;
	 		cout << "*               1.新书入库#                    *" << endl;
	 		cout << "*                                             *" << endl;
	 		cout << "*               2.查找                        *" << endl;
			cout << "*                                             *" << endl;
			cout << "*               3.删除#                        *" << endl;
			cout << "*                                             *" << endl;
			cout << "*               4.修改#                        *" << endl;
			cout << "*                                             *" << endl;
			cout << "*               5.显示全部在架书              *" << endl;
			cout << "*                                             *" << endl;
			cout << "*               6.清空全部图书内容#            *" << endl;
			cout << "*                                             *" << endl;
			cout << "*               0.返回上一层                  *" << endl;
	 		cout << "*                                             *" << endl;
	 		cout << "***********************************************" << endl;
			cout<<"#号为管理员功能,需要登录管理员账号<(ˉ^ˉ)> "<<endl;
			cout <<"请输入相应功能代号:"<<endl; 
			
			cin >> i;
	  		switch (i)
	  		{
	  			case '1':
				  	cout<<"请先登录管理员的账号，再进行操作"<<endl;
					r = rel.reader_land();//管理员登录
					if((r==NULL)||strcmp(r->ReaderName,"guanliyuan")!=0)//设置管理员为guanliyuan
					{
						cout<<"您不是管理员，无法进行此操作"<<endl;
						break;
					}
	  				p =  AddNewBook();
	  	 			Add_list(p);
					cout<<"新书插入成功"<<endl;
	   				break;
	  			case '2':
	   				search();
					break;
	   			case '3':
				   	cout<<"请先登录管理员的账号，再进行操作"<<endl;
					r = rel.reader_land();//管理员登录
					if((r==NULL)||strcmp(r->ReaderName,"guanliyuan")!=0)//设置管理员为guanliyuan
					{
						cout<<"您不是管理员，无法进行此操作"<<endl;
						break;
					}
	   				delete_onebook();
					break;
				case '4':
					cout<<"请先登录管理员的账号，再进行操作"<<endl;
					r = rel.reader_land();//管理员登录
					if((r==NULL)||strcmp(r->ReaderName,"guanliyuan")!=0)//设置管理员为guanliyuan
					{
						cout<<"您不是管理员，无法进行此操作"<<endl;
						break;
					}
					change_content();	
					break;
	  			case '5':
	  				show_all();
	  				break;
	  			case '6': 
				    cout<<"请先登录管理员的账号，再进行操作"<<endl;
					r = rel.reader_land();//管理员登录
					if((r==NULL)||strcmp(r->ReaderName,"guanliyuan")!=0)//设置管理员为guanliyuan
					{
						cout<<"您不是管理员，无法进行此操作"<<endl;
						break;
					}
	  				delete_allbook();
					break; 
	  			case '0':
	  				break;
	  			default:cout << "输入错误，请从新输入。" << endl;
	  		}
	  	}while(i!='0');
	
	}
};
int BookList::n ;
Book* BookList::head_ptr=new Book[sizeof(Book)];
Book* BookList::node=new Book[sizeof(Book)];

void borrowtoreturn(BookList b,ReaderList r)
//借书还书函数.判断是"借书"还是"还书".1为"借书",2为"还书"
{
	int k= 0;
 	int rsuffix, bsuffix;
 	string readername,readerpass;//暂存读者名字、密码
	cout<<"请输入您的姓名:"<<endl;;
	cin >> readername;
	Reader *p;
	p=r.head_point;
	while(p!=NULL)
	{
		if(strcmp(p->ReaderName,&readername[0])==0)
		{
			cout<<"请输入您的密码:";
			cin>> readerpass;
			if(strcmp(p->Password,&readerpass[0])==0)
			{
				cout<<"登录成功!"<<endl; 
				k=1;break;
			}
			else
			{
				cout<<"密码错误!"<<endl; 
				k=0;return;
			} 
		}
		p=p->next;
	}
	if(k=0)
	{
		cout<<"输入错误"<<endl; return;
	}	
	char br=' ';
	do
	{
		cout << "***********************************************" << endl;
		cout << "*               借 书 / 还 书                 *" << endl;
		cout << "*                                             *" << endl;
		cout << "*               1. 借 书                      *" << endl;
		cout << "*                                             *" << endl;
		cout << "*               2. 还 书                      *" << endl;
		cout << "*                                             *" << endl;
		cout << "*               0. 退 出                      *" << endl;
		cout << "*                                             *" << endl;
		cout << "***********************************************" << endl;
		cout<<endl<<endl;
		cout <<"请输入相应功能代号:"<<endl; 

		cin>>br;
		switch (br)
		{
		case '1':
			b.borrow_book(p);
			break;
		case '2':
			b.return_book(p);
			break;
		case '0':
			break;
		default:
			cout<<"输入错误!"<<endl;
			break;
		}
	} while (br!='0');
	
}


void mainjiemian()    //主界面                                                           //主界面
{
 	cout << "***********************************************" << endl;
 	cout << "*               图 书 借 阅 系 统              *" << endl;
 	cout << "*                                             *" << endl;
 	cout << "*               1.读 者 信 息                 *" << endl;
 	cout << "*                                             *" << endl;
 	cout << "*               2.书 库 信 息                  *" << endl;
	cout << "*                                             *" << endl;
	cout << "*               3.借书/还书                   *" << endl;
	cout << "*                                             *" << endl;
	cout << "*               4.帮 助                       *" << endl;
	cout << "*                                             *" << endl;
	cout << "*               5.有关该系统的一些说明         *" << endl;
	cout << "*                                             *" << endl;
 	cout << "*               0.退出系统                     *" << endl;
 	cout << "*                                             *" << endl;
	cout << "***********************************************" << endl;
	cout <<"请输入相应功能代号"<<endl; 
}

void help()
{
	cout<<"可以注册、登录、借书、还书"<<endl; 
}
void notes()
{
	cout<<"=================关于系统的一些说明=================="<<endl; 
	cout<<"THIS FILE IS PART OF Library lending system PROJECT"<<endl;
	cout<<"THIS FILE CAN ONLY BE USED FOR LEARNING , NOT FOR COMMERCIAL PROFIT."<<endl;
	cout<<"Copyright (c) 2020-2022 子衿JDD "<<endl;
}

int main()
{
	BookList b;
	ReaderList r;
	char in=' ';
 	do
	{
  		mainjiemian();
  		cin >> in;
  		switch (in)
  		{
  			case '1':
  	 			r.GoInto_ReaderInfo();
   				break;
  			case '2':
   				b.GoInto_BookInfo(r);
   				break;
   			case '3':
			    b.save_file();//下载书库信息到链表
   				r.save_readerfile();//下载读者信息到链表
   				borrowtoreturn(b,r);
				break;
			case '4':
				help();	
				break;
  			case '5':
  				notes();
  				break;
  			case '0':
  				return 0;
  			default:cout << "输入错误，请重新输入。" << endl;
  		}
 	} 
	while (in != '0');
	system("pause");
 	return 0;
}