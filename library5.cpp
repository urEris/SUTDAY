#include <string.h>
#include <fstream>
#include<iomanip>
#include <iostream>
#include<string.h>
using namespace std;
class Reader							//�洢������Ϣ����
{
public: 
	char ReaderName[50];				//��������
	char Password[50];					//����
	char book1[30], book2[30];			//ÿ������������,���Ը�����Ҫ�����޶�,book����ISBN��
	int y_n;							//��¼��������Ŀ,0 Ϊû�н���,1 Ϊ����һ��,2 Ϊ���˶���
	Reader *next;						//ָ����һ�ڵ��ָ��
};
/****����������****/
class ReaderList {						//���������еĵڼ����ڵ�
public:
	static Reader * point, *head_point;		//�������� Rreader ָ��,head_point Ϊͷָ��,point Ϊ�ָ��
 	static int o;
	ReaderList()						//���캯��,ʹָ���ʼ��
	{
		head_point = new Reader[sizeof(Reader)];
		 point = new Reader[sizeof(Reader)];
		strcpy(head_point->ReaderName,"0");
		head_point->next = NULL;
		point->next = NULL;
		o = 0;//��������
	} 
	static void save_readerfile()					//�洢�ļ�,���������� 
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
			if(r1=="")//��ǿ³���ԣ�����ļ������У����һ��Ϊ�գ����ӵĻ������һ���ڵ����
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
	static void load_readerfile()					//�ϴ��ļ�
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
	static Reader* reader_register()					//����ע��
	{
		string n1,n2;	
		Reader *nw; 
		nw = new Reader[sizeof(Reader)];
		cout<<"����(���ܳ���50���ַ�):"<<endl;
		cin >>setw(50)>>n1;
		//�������ֳ��Ȳ��ܳ���50
		cout<<"����:"<<endl;
		cout<<"����(���ܳ���50���ַ�):"<<endl;
		//�������볤�Ȳ��ܳ���50
		cin >> n2;
		strcpy(nw->ReaderName,&n1[0]);
		strcpy(nw->Password,&n2[0]);
		strcpy(nw->book1," ");
		strcpy(nw->book2," ");
		nw->next = NULL;
		return nw;
	}
	static void Add_Point(Reader * p)				//�����½�㵽����
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
	static Reader* reader_land()						//���ߵ�¼
	{
		string readername,readerpass;
		cout<<"��������������:"<<endl;
		cin >> readername;
		point=head_point->next;
		while(point!=NULL)
		{
			if(strcmp(point->ReaderName,&readername[0])==0)//�����û�
			{
				cout<<"��������������:";
				cin>> readerpass;
				if(strcmp(point->Password,&readerpass[0])==0)//��������
				{
					cout<<"��¼�ɹ�!"<<endl; 
					return point;//�����û�ָ��
				}
				else
				{
					cout<<"�������!"<<endl; 
					return NULL;//���ؿ�
				} 
			}
			point=point->next;//��һ��
		}
		if(point==NULL)
		{
			cout<<"���û�������!  ��������ע�ᣬ������^_^"<<endl; 
		}
		return NULL;
	}
	static void show_OneReader(Reader *p)		//��ʾĳ������Ϣ
	{
		if(p==NULL)
		{
			return;
		}
		cout << "***********************************************" << endl;
		cout <<"����"<<"\t"<<p->ReaderName <<endl;
		cout <<"��һ�����ISBN��:"<<"\t"<<p->book1 <<endl;
		cout <<"�ڶ������ISBN��:"<<"\t"<<p->book2 <<endl;
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
	static void change_password(Reader *p)					//�޸�����
	{
		if(p==NULL)
		{
			return;
		}
		Reader *point;
		point = head_point;	
		while(strcmp(point->ReaderName ,p->ReaderName)!=0)
		{
			point=point->next;//���������ҵ���¼�û�
		}
		string n2;
		cout<<"�������µ�����:"<<endl;
		cin>>n2;
		strcpy(point->Password,&n2[0]);
		load_readerfile();
		cout<<"���ĳɹ�!"<<endl; 
	}
		 
	static void delete_reader(Reader *p)					//����ע��
	{
		if(p==NULL)
		{
			return;
		}
		Reader *q;//Э��pointָ�룬��p->next=point
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
		cout<<"ע���ɹ�!"<<endl; 
		o=o-1;//����������һ
	}

	static void delete_readers()					//���ȫ��������Ϣ
	{
		cout<<"ȷ��ȫ��ɾ���� �����ɾ����ȷ���밴1�������밴������."<<endl;
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
			cout<<"�Ѿ��ɹ����ȫ��������Ϣ!"<<endl;
		} 
		else
		{
			return;
		}
	}
	static void help()
	{
		cout<<"��ʱû�а���,BALABALABALA"<<endl; 
	 } 
	static void GoInto_ReaderInfo()				//������Ϣ�˵�
	{
		char i;
		save_readerfile();
		do
		{
			cout << "***********************************************" << endl;
	 		cout << "*               ��  ��  ��  ��                *" << endl;
	 		cout << "*                                             *" << endl;
	 		cout << "*               1.��¼�鿴                    *" << endl;
	 		cout << "*                                             *" << endl;
	 		cout << "*               2.ע��                        *" << endl;
			cout << "*                                             *" << endl;
			cout << "*               3.ע��                        *" << endl;
			cout << "*                                             *" << endl;
			cout << "*               4.�޸�����                    *" << endl;
			cout << "*                                             *" << endl;
			cout << "*               5.�鿴ȫ��������Ϣ#            *" << endl;
			cout << "*                                             *" << endl;
			cout << "*               6.���ȫ��������Ϣ#            *" << endl;
			cout << "*                                             *" << endl;
			cout << "*               7.����˵��                    *" << endl;
			cout << "*                                             *" << endl;
			cout << "*               0.������һ��                  *" << endl;
	 		cout << "*                                             *" << endl;
	 		cout << "***********************************************" << endl;
			cout<<"#��Ϊ����Ա����,��Ҫ��¼����Ա�˺�<(��^��)> "<<endl;
			cout <<"��������Ӧ���ܴ���:"<<endl; 
			
			cin >> i;
			Reader *p;
			
	  		switch (i)
	  		{
	  			case '1'://��¼�鿴 
	  				p = reader_land();
				  	show_OneReader(p);
	   				break;
	  			case '2'://ע��
	   				p = reader_register();
	   				Add_Point(p);
	   				cout<<"ע��ɹ�"<<endl; 
					break;
	   			case '3'://ע��
				   	cout<<"�ȵ�¼Ҫע�����˺ţ���ȷ���Ǳ���"<<endl;
				    p = reader_land();
	   				delete_reader(p);
					break;
				case '4'://�޸�����
					cout<<"�ȵ�¼Ҫ�޸�������˺ţ���ȷ���Ǳ���"<<endl;
					p = reader_land();
					change_password(p);	
					break;
	  			case '5':
				  	cout<<"���ȵ�¼����Ա���˺ţ��ٽ��в���"<<endl;
					p = reader_land();
					if((p==NULL)||strcmp(p->ReaderName,"guanliyuan")!=0)//���ù���ԱΪguanliyuan
					{
						cout<<"�����ǹ���Ա���޷����д˲���"<<endl;
						break;
					}
	  				show_all();
	  				break;
	  			case '6': 
				  	cout<<"���ȵ�¼����Ա���˺ţ��ٽ��в���"<<endl;
					p = reader_land();
					if((p==NULL)||strcmp(p->ReaderName,"guanliyuan")!=0)//���ù���ԱΪguanliyuan
					{
						cout<<"�����ǹ���Ա���޷����д˲���"<<endl;
						break;
					}
	  				delete_readers();
					break; 
				case '7':
	  				help();
	  				break;
	  			case '0':
	  				break;
	  			default:cout << "����������������롣" << endl;
	  		}
	  	}while(i!='0');
	
	} 
};
Reader* ReaderList::head_point=new Reader[sizeof(Reader)];//����ͷ�ڵ�
Reader* ReaderList::point=new Reader[sizeof(Reader)];//��ʱ���߽ڵ�
int ReaderList::o=1 ;

class Book						//�洢ͼ����Ϣ����
{
public:
	char *BookName;			    //����,���ڲ���	
	char *Writer;			    //������,���ڲ���
	char PublishDate[20];		//��������,���ڲ���
	char ISBN[30];				//ISBN ��,���ڲ���
	char ebook[2];				//������ 
	char paperbook[2];			//ֽ����  
	char *Publisher;		    //������,���ڲ���
	char *BriefIntroduction;    //�������ݼ��
	int i_o;					//�ж����Ƿ���,0 Ϊ�ڼ�,1 Ϊ���
	Book *next;					//ָ����һ���ڵ��ָ��
};
/****���������****/
class BookList {
public:
	static Book * node;
	static Book *head_ptr ;//�������� Book ָ��,head_ptr Ϊͷָ��,node\p Ϊ�ָ��
	static int n;	
	BookList() 
	{								 //���캯����ʹָ���ʼ��
		node = new Book[sizeof(Book)];    //��������Ϣ
		head_ptr = new Book[sizeof(Book)];
		head_ptr->next = NULL;
		node->next = NULL;
	}
	static void save_file()					//�洢�ļ�
	{
		Book *p;           //��ʱ�ڵ�
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
			if(s1=="")//��ǿ³���ԣ�����ļ������У����һ��Ϊ�գ����ӵĻ������һ���ڵ����
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
			n++;//�������
			//  cout<<"�������: "<<n<<endl;
		}
		file.close();
		delete p;
	}
	static void load_file()					//�ϴ��ļ�
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
	static Book* AddNewBook()					//����Ǽ�,�� node ָ��������ֵ
	{
		string n1,n2,n3,n4,n5,n6,n7,n8;	
		Book *nw; 
		nw = new Book[sizeof(Book)];
		cout<<"�����������������Ϣ:"<<endl;
		cout<<"����:"<<endl;
		cin>>n1;
		cout<<"������:"<<endl;
		cin>>n2;
		cout<<"��������:"<<endl;
		cin>>n3;
		cout<<"ISBN ��:"<<endl;	
		cin>>n4;
		cout<<"������(0 Ϊ�ڼ�,1 Ϊ���):"<<endl;
		cin>>n5;
		cout<<"ֽ����(0 Ϊ�ڼ�,1 Ϊ���):"<<endl;
		cin>>n6;
		cout<<"������:"<<endl;
		cin>>n7;
		cout<<"���ݼ��:"<<endl;
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
	static  void Add_list(Book * p)			//���ӽ�㵽 Book ������,�����������ʱ
	{ 		
		node = head_ptr;
		while(node->next!=NULL)//�ҵ�β�ڵ�
		{
			node=node->next;
		}
		node->next = p;//��β�������½ڵ�
		node = p;
		p->next=NULL;//����ÿ�
		load_file();//�����ļ�
	}
	static void borrow_book(Reader *p)				//��������
	{
		Book *n;
		if (strcmp(p->book1," ")!=0 &&strcmp(p->book2 ," ")!=0)           //����
	 	{
	 		cout<<"���Ѿ����2���ˣ����ܽ�����,�����Ȼ����ٽ��顣"<<endl;
	 	}
	 	else if(strcmp(p->book1," ")==0)
	 	{
			//����
			n = search_ISBN(); 
			//���������裬ֽ����ֻ�ܽ�����
			cout<<"ֻ��¼ֽ������ļ�¼����ֽ�鲻ռ�ý���������������ز鿴!"<<endl;
			if(strcmp(n->paperbook,"0")==0)
			{
				cout<<"��"<<n->BookName<<"��ֽ����ɽ���"<<endl;
				cout<<"ȷ�Ͻ��ġ�"<<n->BookName<<"��ֽ�����𣿣�ȷ���밴1�����������������"<<endl;
				char temp;
				cin>>temp;
				if(temp=='1')
				{
					strcpy(p->book1,n->ISBN);//��¼������ISBN��
					strcpy(n->paperbook,"1");//����ȥ��0->1,˵�����ڼ���
					ReaderList::load_readerfile();//�����û���Ϣ
					BookList::load_file();//���������Ϣ
					cout<<"����ɹ�!!"<<endl;
				}
			}
			else
			{
				cout<<"�ޡ�"<<n->BookName<<"����ֽ����"<<endl;
			}//���Ҫ��20���飬���԰�book���������е��鷳
		}
		else if(strcmp(p->book2," ")==0)
	 	{
			//����
			n = search_ISBN();
			//���������裬ֽ����ֻ�ܽ�����
			cout<<"ֻ��¼ֽ������ļ�¼����ֽ�鲻ռ�ý���������������ز鿴!"<<endl;
			if(strcmp(n->paperbook,"0")==0)
			{
				cout<<"��"<<n->BookName<<"��ֽ����ɽ���"<<endl;
				cout<<"ȷ�Ͻ��ġ�"<<n->BookName<<"��ֽ�����𣿣�ȷ���밴1�����������������"<<endl;
				char temp;
				cin>>temp;
				if(temp=='1')
				{
					strcpy(p->book2,n->ISBN);//��¼������ISBN��
					strcpy(n->paperbook,"1");//����ȥ��0->1,˵�����ڼ���
					ReaderList::load_readerfile();//�����û���Ϣ
					BookList::load_file();//���������Ϣ
					cout<<"����ɹ�!!"<<endl;
				}
			}
			else
			{
				cout<<"�ޡ�"<<n->BookName<<"����ֽ����"<<endl;
			}
		}
		else
		{
			cout<<"����ʧ��"<<endl;
		}
	}
	static void return_book(Reader *p)				//��������
	{
		cout << "***********************************************" << endl;
		cout <<"����"<<"\t"<<p->ReaderName <<endl;
		cout <<"book1"<<"\t"<<p->book1 <<endl;
		cout <<"book2"<<"\t"<<p->book2 <<endl;
  		cout<<"����book1����1��������book2����2����"<<endl;
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
					strcpy(u->paperbook,"0");//�ڼ�Ϊ0
					strcpy(p->book1 ," ");//����֮��Ϊ��
					ReaderList::load_readerfile();//�����û���Ϣ
					BookList::load_file();//���������Ϣ
					cout<<"����ɹ�"<<endl; 
					break;
				}u=u->next ;
			}
			if(u==NULL)
			{
				cout<<"û���Ȿ��!����ʧ�ܣ�����ISBN��"<<endl; 
			}
		}
		else if(hua=='2'&&p->book2!=" ")
		{
			u=BookList::head_ptr;
			while(u!=NULL)
			{
				
				if(strcmp(u->ISBN  ,p->book2)==0)
				{
					strcpy(u->paperbook,"0");//�ڼ�Ϊ0
					strcpy(p->book2 ," ");//����֮��Ϊ��
					ReaderList::load_readerfile();//�����û���Ϣ
					BookList::load_file();//���������Ϣ
					cout<<"����ɹ�"<<endl; 
					break;
				}u=u->next ;
			}
			if(u==NULL)
			{
				cout<<"û���Ȿ��!����ʧ�ܣ�����ISBN��"<<endl; 
			}
		}
		else
		{
			cout<<"�������!"<<endl;
		}
	}
	static void show_book(Book *p)
	{
		cout << "***********************************************" << endl; 
		cout<<"��    ��"<<"\t"<<p->BookName<<endl;
		cout<<"��    ��"<<"\t"<<p->Writer<<endl;
		cout<<"��������"<<"\t"<<p ->PublishDate<<endl;
		cout<<"ISBN  ��"<<"\t"<<p->ISBN<<endl;
		if(strcmp(p->ebook ,"0")==0)
		{
			cout<<"���� ��"<<"\t"<<"�ڼ�"<<endl;
		} 				
		if(strcmp(p->paperbook,"0")==0)
		{
			cout<<"ֽ�� ��"<<"\t"<<"�ڼ�"<<endl;
		} 
		cout<<"����  ��"<<"\t"<<p->Publisher<<endl;
		cout<<"ͼ����"<<"\t"<<p->BriefIntroduction<<endl;
		cout << "***********************************************" << endl;
	}
	static	Book* search_ISBN()			//�� ISBN �Ų���ͼ��
	{
		string cs;
		cout<<"������ͼ���ISBN ��:"<<endl;
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
			cout<<"û���ҵ��Ȿ�飬���Բ����������"<<endl;
		}
		return p;
	}
	static void search_BookName()		//����������ͼ��
	{
		string cs;
		cout<<"������ͼ�������:"<<endl;
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
		cout<<"���ҵ�"<<i<<"����Ϊ��"<<cs<<"������"<<endl;
	}
	static	void search_Writer()			//������������ͼ��
	{
		string cs;
		cout<<"������ͼ���������:"<<endl;
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
		cout<<"���ҵ�"<<i<<"��"<<cs<<"����"<<endl;
	}
	static	void search_Publisher()		//�������̲���ͼ��
	{
		string cs;
		cout<<"������ͼ��ĳ�����:"<<endl;
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
		cout<<"���ҵ�"<<i<<"��"<<cs<<"����"<<endl;
	}
	static	void search_PublishDate() 	//���������ڲ���ͼ��
	{
		string cs;
		cout<<"������ͼ��ĳ�������:"<<endl;
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
		cout<<"���ҵ�"<<i<<"��"<<cs<<"����"<<endl;
	}
	static void search()						//������Ҳ˵�
	{	
		char r;
		do
		{
			cout << "***********************************************" << endl;
	 		cout << "*               ͼ �� �� ��                   *" << endl;
	 		cout << "*                                             *" << endl;
	 		cout << "*               1.�� ISBN �Ų���ͼ��          *" << endl;
	 		cout << "*                                             *" << endl;
	 		cout << "*               2.����������ͼ��              *" << endl;
			cout << "*                                             *" << endl;
			cout << "*               3.������������ͼ��            *" << endl;
			cout << "*                                             *" << endl;
			cout << "*               4.�������̲���ͼ��            *" << endl;
			cout << "*                                             *" << endl;
			cout << "*               5.���������ڲ���ͼ��          *" << endl;
			cout << "*                                             *" << endl;
			cout << "*               0.������һ��                  *" << endl;
			cout << "*                                             *" << endl;
			cout << "***********************************************" << endl;
	   		cout <<"��������Ӧ���ܴ���:"<<endl; 
	   		
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
	  			default:cout << "���������������롣" << endl;
	   					
			}
		}
		while(r!='0');
	}
	static	void show_all()					//��ʾ���п���δ�������ͼ��
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
		cout<<"���ҵ�"<<i<<"���ڼ���"<<endl;
	}
	static	void delete_onebook()				//ɾ��ĳ����
	{
		string ss;
		cout<<"������Ҫɾ����ͼ���ISBN��:"<<endl;
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
			cout<<"û����Ҫɾ����ͼ��ļ�¼"<<endl;
		}
		else
		{
			q->next=p->next;
			p->next=NULL;
			delete p;
			load_file();
			cout<<"ɾ���ɹ�!"<<endl; 
			n=n-1;
		} 
	}
    static	void delete_allbook()				//ɾ������ͼ��
	{
		cout<<"ȷ��ȫ��ɾ���𣿣������ɾ����ȷ���밴1�������밴������."<<endl;
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
			cout<<"ȫ��ͼ��ɾ���ɹ�!"<<endl;
		}
	} 
	static	void change_content()				//����ĳ�������Ϣ
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
	 		cout << "*              �� �� ͼ �� �� Ϣ               *" << endl;
	 		cout << "*                                             *" << endl;
	 		cout << "*               1.�޸�����                     *" << endl;
	 		cout << "*                                             *" << endl;
	 		cout << "*               2.�޸�������                   *" << endl;
			cout << "*                                             *" << endl;
			cout << "*               3.�޸ĳ�������                 *" << endl;
			cout << "*                                             *" << endl;
			cout << "*               4.�޸ĵ�����(0 Ϊ�ڼ�,1 Ϊ���) *" << endl;
			cout << "*                                             *" << endl;
			cout << "*               5.�޸�ֽ����(0 Ϊ�ڼ�,1 Ϊ���) *" << endl;
			cout << "*                                             *" << endl;
			cout << "*               6.�޸ĳ�����                   *" << endl;
	 		cout << "*                                             *" << endl;
			cout << "*               7.�޸����ݼ��                 *" << endl;
	 		cout << "*                                             *" << endl;
			cout << "*               0.������һ��                   *" << endl;
			cout << "*                                             *" << endl;
	 		cout << "***********************************************" << endl;
			cout<<endl<<endl;
			cout <<"��������Ӧ���ܴ���:"<<endl; 
			
			cin >> i;
	  		switch (i)
	  		{
	  			case '1':
	  				cout<<"�µ�����:"<<endl;
					cin>>n1;
					strcpy(p->BookName,&n1[0]);//ֱ�����������޸�
	   				break;
	  			case '2':
	   				cout<<"�µ�������:"<<endl;
					cin>>n2;
					strcpy(p->Writer,&n2[0]);
					break;
	   			case '3':
	   				cout<<"�µĳ�������:"<<endl;
					cin>>n3;
					strcpy(p->PublishDate,&n4[0]);
					break;
				case '4':
					cout<<"������(0 Ϊ�ڼ�,1 Ϊ���):"<<endl;
					cin>>n4;
					strcpy(p->ebook,&n4[0]);
					break;
	  			case '5':
	  				cout<<"�޸�ֽ����(0 Ϊ�ڼ�,1 Ϊ���):"<<endl;
					cin>>n5;
					strcpy(p->paperbook,&n5[0]);
	  				break;
	  			case '6':
	  				cout<<"�µĳ�����:"<<endl;
					cin>>n6;
					strcpy(p->Publisher,&n6[0]);
					break;
	  			case '7': 
	  				cout<<"�µ����ݼ��:"<<endl;
					cin>>n7;
					strcpy(p->BriefIntroduction,&n7[0]);
					break; 
				case '0': 
					break; 
	  			default:cout << "���������������롣" << endl;
	  		}
	  	}while(i!='0');
		cout<<"�޸ĺ����"<<endl;
		show_book(p);
		load_file();
	}
	static	void GoInto_BookInfo(ReaderList rel)				//���������Ϣ�˵�
	{
		Book *p;
		Reader *r;
		save_file();
		rel.save_readerfile();//���ض�����Ϣ
		char i=' ';
		do
		{
			cout << "***********************************************" << endl;
	 		cout << "*               ͼ �� �� Ϣ �� ��             *" << endl;
	 		cout << "*                                             *" << endl;
	 		cout << "*               1.�������#                    *" << endl;
	 		cout << "*                                             *" << endl;
	 		cout << "*               2.����                        *" << endl;
			cout << "*                                             *" << endl;
			cout << "*               3.ɾ��#                        *" << endl;
			cout << "*                                             *" << endl;
			cout << "*               4.�޸�#                        *" << endl;
			cout << "*                                             *" << endl;
			cout << "*               5.��ʾȫ���ڼ���              *" << endl;
			cout << "*                                             *" << endl;
			cout << "*               6.���ȫ��ͼ������#            *" << endl;
			cout << "*                                             *" << endl;
			cout << "*               0.������һ��                  *" << endl;
	 		cout << "*                                             *" << endl;
	 		cout << "***********************************************" << endl;
			cout<<"#��Ϊ����Ա����,��Ҫ��¼����Ա�˺�<(��^��)> "<<endl;
			cout <<"��������Ӧ���ܴ���:"<<endl; 
			
			cin >> i;
	  		switch (i)
	  		{
	  			case '1':
				  	cout<<"���ȵ�¼����Ա���˺ţ��ٽ��в���"<<endl;
					r = rel.reader_land();//����Ա��¼
					if((r==NULL)||strcmp(r->ReaderName,"guanliyuan")!=0)//���ù���ԱΪguanliyuan
					{
						cout<<"�����ǹ���Ա���޷����д˲���"<<endl;
						break;
					}
	  				p =  AddNewBook();
	  	 			Add_list(p);
					cout<<"�������ɹ�"<<endl;
	   				break;
	  			case '2':
	   				search();
					break;
	   			case '3':
				   	cout<<"���ȵ�¼����Ա���˺ţ��ٽ��в���"<<endl;
					r = rel.reader_land();//����Ա��¼
					if((r==NULL)||strcmp(r->ReaderName,"guanliyuan")!=0)//���ù���ԱΪguanliyuan
					{
						cout<<"�����ǹ���Ա���޷����д˲���"<<endl;
						break;
					}
	   				delete_onebook();
					break;
				case '4':
					cout<<"���ȵ�¼����Ա���˺ţ��ٽ��в���"<<endl;
					r = rel.reader_land();//����Ա��¼
					if((r==NULL)||strcmp(r->ReaderName,"guanliyuan")!=0)//���ù���ԱΪguanliyuan
					{
						cout<<"�����ǹ���Ա���޷����д˲���"<<endl;
						break;
					}
					change_content();	
					break;
	  			case '5':
	  				show_all();
	  				break;
	  			case '6': 
				    cout<<"���ȵ�¼����Ա���˺ţ��ٽ��в���"<<endl;
					r = rel.reader_land();//����Ա��¼
					if((r==NULL)||strcmp(r->ReaderName,"guanliyuan")!=0)//���ù���ԱΪguanliyuan
					{
						cout<<"�����ǹ���Ա���޷����д˲���"<<endl;
						break;
					}
	  				delete_allbook();
					break; 
	  			case '0':
	  				break;
	  			default:cout << "���������������롣" << endl;
	  		}
	  	}while(i!='0');
	
	}
};
int BookList::n ;
Book* BookList::head_ptr=new Book[sizeof(Book)];
Book* BookList::node=new Book[sizeof(Book)];

void borrowtoreturn(BookList b,ReaderList r)
//���黹�麯��.�ж���"����"����"����".1Ϊ"����",2Ϊ"����"
{
	int k= 0;
 	int rsuffix, bsuffix;
 	string readername,readerpass;//�ݴ�������֡�����
	cout<<"��������������:"<<endl;;
	cin >> readername;
	Reader *p;
	p=r.head_point;
	while(p!=NULL)
	{
		if(strcmp(p->ReaderName,&readername[0])==0)
		{
			cout<<"��������������:";
			cin>> readerpass;
			if(strcmp(p->Password,&readerpass[0])==0)
			{
				cout<<"��¼�ɹ�!"<<endl; 
				k=1;break;
			}
			else
			{
				cout<<"�������!"<<endl; 
				k=0;return;
			} 
		}
		p=p->next;
	}
	if(k=0)
	{
		cout<<"�������"<<endl; return;
	}	
	char br=' ';
	do
	{
		cout << "***********************************************" << endl;
		cout << "*               �� �� / �� ��                 *" << endl;
		cout << "*                                             *" << endl;
		cout << "*               1. �� ��                      *" << endl;
		cout << "*                                             *" << endl;
		cout << "*               2. �� ��                      *" << endl;
		cout << "*                                             *" << endl;
		cout << "*               0. �� ��                      *" << endl;
		cout << "*                                             *" << endl;
		cout << "***********************************************" << endl;
		cout<<endl<<endl;
		cout <<"��������Ӧ���ܴ���:"<<endl; 

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
			cout<<"�������!"<<endl;
			break;
		}
	} while (br!='0');
	
}


void mainjiemian()    //������                                                           //������
{
 	cout << "***********************************************" << endl;
 	cout << "*               ͼ �� �� �� ϵ ͳ              *" << endl;
 	cout << "*                                             *" << endl;
 	cout << "*               1.�� �� �� Ϣ                 *" << endl;
 	cout << "*                                             *" << endl;
 	cout << "*               2.�� �� �� Ϣ                  *" << endl;
	cout << "*                                             *" << endl;
	cout << "*               3.����/����                   *" << endl;
	cout << "*                                             *" << endl;
	cout << "*               4.�� ��                       *" << endl;
	cout << "*                                             *" << endl;
	cout << "*               5.�йظ�ϵͳ��һЩ˵��         *" << endl;
	cout << "*                                             *" << endl;
 	cout << "*               0.�˳�ϵͳ                     *" << endl;
 	cout << "*                                             *" << endl;
	cout << "***********************************************" << endl;
	cout <<"��������Ӧ���ܴ���"<<endl; 
}

void help()
{
	cout<<"����ע�ᡢ��¼�����顢����"<<endl; 
}
void notes()
{
	cout<<"=================����ϵͳ��һЩ˵��=================="<<endl; 
	cout<<"THIS FILE IS PART OF Library lending system PROJECT"<<endl;
	cout<<"THIS FILE CAN ONLY BE USED FOR LEARNING , NOT FOR COMMERCIAL PROFIT."<<endl;
	cout<<"Copyright (c) 2020-2022 ����JDD "<<endl;
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
			    b.save_file();//���������Ϣ������
   				r.save_readerfile();//���ض�����Ϣ������
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
  			default:cout << "����������������롣" << endl;
  		}
 	} 
	while (in != '0');
	system("pause");
 	return 0;
}