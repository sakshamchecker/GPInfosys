//Header files
#include<iostream>
#include<conio.h>
#include<fstream>
#include<stdio.h>
#include<iomanip>
#include<windows.h>

using namespace std;

void gotoxy(int x, int y)				//aligns components in x,y coordinates
{
    COORD cord;
    cord.X=x;
    cord.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),cord);
}

//FUNCTION PROTOTYPES
	void c_writefile();
	void c_readfile();
	void c_searchfile();
	void c_delfile();
	void c_modfile();
	void c_sort_rec();
	void s_writefile();
	void s_readfile();
	void s_searchfile();
	void s_delfile();
	void s_modfile();

// Courses
class courses
{
	int co_code;
	char co_name[25];
	int co_duration;
	char co_description[40];
	float fees;
	public:
		void input()
		{
			cout<<"\tEnter the course code:\t";
			cin>>co_code;
			cout<<"\tEnter the course name:\t";
			cin.ignore();
			gets(co_name); 
			cout<<"\tEnter course duration <in months>: ";
			cin>>co_duration;
			cout<<"\tEnter cource description: ";
			cin.ignore();
			gets(co_description);
			cout<<"\tEnter the fees:\t";
			cin>>fees;
		}
		void output()
		{
			cout<<setw(5)<<co_code<<setw(20)<<co_name<<setw(20)<<co_duration<<setw(20)<<co_description<<setw(20)<<fees<<'\n';
		}
		int ret_code(){return co_code;}
		char *ret_name(){return co_name;}
		int ret_duration(){return co_duration;}
		char *ret_description(){return co_description;}
		float ret_fees(){return fees;}
		void modify_course(courses d){}
};

int count_rec_courses()
{
		ifstream f;	
		f.open("courses.dat",ios::binary|ios::ate);
		int n;
		n=f.tellg()/sizeof(courses);
		cout<<"\nTotal number of records in the courses are:  "<<n;getch();
		return n;
}

void bubble_sort(courses A[],int n)
{
	courses t;
	ifstream f;
	f.open("courses.dat",ios::binary);
	int i, j;
	for(int i=0; i<n; i++)
	{
		for(int j=0;j<n-1-i; j++)
		{
			if(A[j].ret_code()>A[j+1].ret_code())
			{
				t=A[j];A[j]=A[j+1];A[j+1]=t;
			}
		}		
	}		
}

void c_writefile()//write file
{
	ofstream fout("courses.dat",ios::binary|ios::out|ios::app);
	courses c ;
	c.input();
	fout.write((char*)&c,sizeof(c));
	fout.close();
}

void c_readfile()  //readfile
{
	courses c;
	ifstream fin;
	fin.open("courses.dat",ios::binary);
	if(!fin)
	{
		cout<<"\tFILE DO NOT EXIST";
		getch(); return;
	}
	else
	{
		cout<<'\n'<<setw(5)<<"CODE"<<setw(20)<<"NAME"<<setw(20)<<"DURATION"<<setw(20)<<"DESCRIPTION"<<setw(20)<<"FEES"<<'\n';
		while(fin.read((char*)&c,sizeof(c)))
		{
			c.output();
		}
		getch();
		fin.close();
	}
}

void c_searchfile() //searchfile
{
	int code,k=0;
	courses c;
	cout<<"\tEnter the course  code you want to search for:";
	cin>>code;
	ifstream fin("courses.dat",ios::binary);
	if(!fin)
	cout<<"\tFile does not exist";
	else
	{	
		while((fin)&&(k==0))
		{
			fin.read((char*)&c,sizeof(courses));
			if(code==c.ret_code())
			{
				cout<<'\n'<<setw(5)<<"CODE"<<setw(15)<<"NAME"<<setw(15)<<"DURATION"<<setw(15)<<"DESCRIPTION"<<setw(15)<<"FEES"<<'\n';
				c.output();
				k++;
			}
		}
		fin.close();
		if(k==0)
		cout<<"\tRECORD DOESNOT EXIST";
	}	
}

void c_delfile()	//Delete file
{
	int code, k=0;
	courses c1;
	ifstream fin("courses.dat",ios::binary);
	ofstream fout("temp.dat",ios::binary);
	if(!fin)
	{
		cout<<"file does not exist"; 
		getch(); 
		return;
	}
	cout<<"\tEnter the code of the course you want to delete:";
	cin>>code;
	while(fin.read((char*)&c1,sizeof(c1)) )
	{
	//	cout<<c1.ret_code(); getch();
		if(code!=c1.ret_code())
		{
			fout.write((char*)&c1,sizeof(courses));
	//		cout<<c1.ret_code();
		}
		else k++;
	}
	fout.close();
	fin.close(); 
	remove("courses.dat");
	rename("temp.dat","courses.dat");
	if(k==0)
	{
		cout<<"\tRecord does not exist";
		getch(); 
		return;
	}
	else
	{
		cout<<"\tRecord deleted";
	}
}
 
void c_modfile()		//Modify file
{
	courses c1;
	int code,f=0;
	ifstream fin("courses.dat",ios::binary);
	ofstream fout("temp.dat",ios::binary);
	if(!fin)
	{
		cout<<"\tFile does not exist";
		getch(); 
		return;
	}
	else
	{
		cout<<"\tEnter any course code:";
		cin>>code;
		while(fin.read((char*)&c1,sizeof(c1)))
		{
			if (c1.ret_code()==code)
			{
				c1.input();
				f=1;
			}
			fout.write((char*)&c1,sizeof(courses));
		}
		if(f==0)
		{
			cout<<"\tRecord does not exist";
			getch(); 
			return;
		}
		else
		{
			fout.close();
			fin.close();
			remove("courses.dat");
			rename("temp.dat","courses.dat");
		}
	}
}

void c_sort_rec()
{
	int i=0;
	cout<<"Total records are\t";
	int r=count_rec_courses();
	cout<<r;
	courses *c;
	c= new courses[r];
	ifstream f;	
	f.open("courses.dat",ios::binary);
	while(f.read((char*)&c[i++],sizeof(courses)));
	for(i=0;i<r;i++)
	{
	cout<<"\n";
	c[i].output();
	}
	f.close();
	bubble_sort(c,r);
	cout<<"The topmost course is";
	for(i=0;i<r;i++)
	{
	cout<<"\n";
	c[i].output();
	}
	getch();
}


// Student
class student
{
	int co_code;
	int admno;
	char name[25];
	char adrs[40];
	char phno[10];
	public:
		void input()
		{
			cout<<"\tEnter student code: ";
			cin>>co_code;
			cout<<"\tEnter the admno: ";
			cin>>admno;
			cout<<"\tEnter name: ";
			cin.ignore();
			gets(name);
			cout<<"\tEnter the address: ";
			gets(adrs);
			cout<<"\tEnter the phone no.: ";
			cin>>phno;
		}
		void output()
		{
			cout<<setw(5)<<co_code<<setw(20)<<admno<<setw(20)<<name<<setw(20)<<adrs<<setw(20)<<phno<<"\n";
		}
		int ret_code(){return co_code;}
		int ret_admno(){return admno;}
		char *ret_name(){return name;}
		char *ret_adrs(){return adrs;}
		char *ret_phno(){return phno;}
		void modify_rec(student s){}
};

// WRITE FUNCTION
void s_writefile()
{
 	ofstream fout("student.dat",ios::binary|ios::app);
 	student c ;
 	c.input();
 	fout.write((char*)&c,sizeof(c));
	fout.close();
}

//READ FILE
void s_readfile()
{
	student s;
	ifstream fin;
	fin.open("student.dat",ios::binary|ios::app);
	if(!fin)
	cout<<"\tFile does not exist";
	else
	{
		fin.read((char*)&s,sizeof(s));
		cout<<"\n"<<setw(5)<<"CODE"<<setw(20)<<"  ADMISSION NO."<<setw(20)<<"NAME"<<setw(20)<<"ADDRESS"<<setw(20)<<"PHONE NO."<<"\n";
		while(fin)
		{
			s.output();
			fin.read((char*)&s,sizeof(s));
		}
		fin.close();
	}	
}

// SEARCH FILE
void s_searchfile()
{
	int ano,k=0;
	student s;
	cout<<"\tEnter any admission no. ";
	cin>>ano;
	ifstream fin("student.dat",ios::binary);
	if(!fin)
		cout<<"\tFiledoesnot exist";
	else
	{
		fin.read((char*)&s,sizeof(s));
		while((fin)&&(k==0))
		{
			if(ano==s.ret_admno())
			{
				cout<<"\n"<<setw(10)<<"CODE"<<setw(20)<<"ADMISSION NO."<<setw(15)<<"NAME"<<setw(20)<<"ADDRESS"<<setw(15)<<"PHONE NO."<<"\n";
				s.output();
				k++;
			}
			fin.read((char*)&s,sizeof(s));
		}
		fin.close();
		if(k==0)
		cout<<"\tRecorddoesnot exist";
	}
}

// DELETE FILE
void s_delfile()
{
	int admno,k=0;
	student s1;
	ifstream fin("student.dat",ios::binary);
	ofstream fout("temp1.dat",ios::binary);
	if(!fin)
	{
		cout<<"file does not exist"; 
		getch(); 
		return;
	}
	cout<<"\tEnter admission number you want to delete:";
	cin>>admno;
	while(fin.read((char*)&s1,sizeof(s1)) )
	{
		 getch();
		if(admno!=s1.ret_admno())
		{
			fout.write((char*)&s1,sizeof(student));
		//	cout<<s1.ret_admno();
		}
		else k++;
	}
	fout.close();
	fin.close(); 
	remove("student.dat");
	rename("temp1.dat","student.dat");
	if(k==0)
	{
		cout<<"\tRecord does not exist";
		getch(); 
		return;
	}
	else
	{
		cout<<"\tRecord deleted";
	}
}

//MODIFY FILE
void s_modfile()
{
	student s;
	int ad,f=0;
	ifstream fin("student.dat",ios::binary);
	ofstream fout("temp2.dat",ios::binary);
	if(!fin)
	{
		cout<<"\tFile does not exist";
		getch(); 
		return;
	}
	else
	{
		cout<<"\tEnter any admission number";
		cin>>ad;
		while(fin.read((char*)&s,sizeof(s)))
		{
			if (s.ret_admno()==ad)
			{
				s.input();
				f=1;
			}
			fout.write((char*)&s,sizeof(student));
		}
		if(f==0)
		{
			cout<<"\tRecord does not exist";
			getch(); 
			return;
		}
		else
		{
			fout.close();
			fin.close();
			remove("student.dat");
			rename("temp2.dat","student.dat");
		}
	}
}

//START FUNCTION
void startup()
{
	cout<<setw(74)<<" ______________________________________ \n";
	cout<<setw(74)<<"|  __________________________________  |\n";
	cout<<setw(74)<<"| |                                  | |\n";
	cout<<setw(74)<<"| |                                  | |\n";
	cout<<setw(25)<<"___________ "<<setw(49)<<"| |                                  | |\n";
	cout<<setw(25)<<"|  _____    |"<<setw(49)<<"| |                                  | |\n";
	cout<<setw(25)<<"| |_____|   |"<<setw(49)<<"| |                                  | |\n";
	cout<<setw(25)<<"|           |"<<setw(49)<<"| |                                  | |\n";
	cout<<setw(25)<<"|GP  InFoSyS|"<<setw(49)<<"| |                                  | |\n";
	cout<<setw(25)<<"|_____  __  |"<<setw(49)<<"| |                                  | |\n";
	cout<<setw(25)<<"|_____ /  \\ |"<<setw(49)<<"| |                                  | |\n";
	cout<<setw(25)<<"|_____ |  | |"<<setw(49)<<"| |                                  | |\n";
	cout<<setw(25)<<"|_____ |  | |"<<setw(49)<<"| |                                  | |\n";
	cout<<setw(25)<<"|_____ |  | |"<<setw(49)<<"| |                                  | |\n";
	cout<<setw(25)<<"|      \\__/ |"<<setw(49)<<"| |                                  | |\n";
	cout<<setw(25)<<"|___________|"<<setw(49)<<"| |                                  | |\n";
	cout<<setw(74)<<"| |__________________________________| |\n";
	cout<<setw(74)<<"|______________________________________|\n"<<endl;
	cout<<"\t\t\t            ___________________________________"<<setw(18)<<"/_|_\\\n";
	cout<<"\t\t\t           /  _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _  \\	   |   |\n";
	cout<<"\t\t\t          / _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ \\          \\___/\n";
	cout<<"\t\t\t         / _ _ _ _____ _ _ _ _ _ _ _ _ _ _ _ _ _ \\\n";
	cout<<"\t\t\t        /_________________________________________\\";
}

void wire1()
{
	gotoxy(25,14);
	cout<<"____\n";
	for(int i=15; i<=17; i++)
	{
	gotoxy(28,i);
	cout<<" |";
	}
	gotoxy(28,18);
	cout<<" |________________________";
	gotoxy(53,19);
	cout<<"|";
}
	
void wire2()
{
	gotoxy(25,13);
	cout<<"________\n";
	gotoxy(73,13);
	cout<<"____________\n";
	for(int i=14; i<=17; i++)
	{
		gotoxy(85,i);
		cout<<"|";
	}
	gotoxy(84,18);
		cout<<"_|_";
}

void display()
{
gotoxy(46,3);
cout<<"W";Sleep(100); cout<<"E";Sleep(100); cout<<"L";Sleep(100); cout<<"C";Sleep(100); cout<<"O";Sleep(100); cout<<"M";Sleep(100); cout<<"E";Sleep(100); cout<<" ";Sleep(100); cout<<"T";Sleep(100); cout<<"O";Sleep(100); cout<<" ";Sleep(100); cout<<"C";Sleep(100); cout<<"+";Sleep(100); cout<<"+";
gotoxy(45,5);
cout<<"C";Sleep(100); cout<<"O";Sleep(100); cout<<"M";Sleep(100); cout<<"P";Sleep(100); cout<<"U";Sleep(100); cout<<"T";Sleep(100);cout<<"E";Sleep(100); cout<<"R";Sleep(100); cout<<" ";Sleep(100); cout<<"P";Sleep(100); cout<<"R";Sleep(100); cout<<"O";Sleep(100); cout<<"J";Sleep(100); cout<<"E";Sleep(100); cout<<"C";Sleep(100); cout<<"T";
gotoxy(52,7);
cout<<"O";Sleep(100); cout<<"N";
gotoxy(46,9);
cout<<"G";Sleep(100); cout<<"P";Sleep(100); cout<<" ";Sleep(100); cout<<"I";Sleep(100);cout<<"N";Sleep(100); cout<<"F";Sleep(100); cout<<"O";Sleep(100); cout<<"R";Sleep(100); cout<<"M";Sleep(100); cout<<"A";Sleep(100); cout<<"T";Sleep(100); cout<<"I";Sleep(100); cout<<"O";Sleep(100); cout<<"N";
gotoxy(50,11);
cout<<"S";Sleep(100); cout<<"Y"; Sleep(100); cout<<"S";Sleep(100); cout<<"T";Sleep(100);cout<<"E";Sleep(100); cout<<"M";
gotoxy(37,15);
Sleep(500);cout<<"Press any key to continue...";
}

// MAIN FUCTION
	int  main()
	{
	startup();
	wire1();
	wire2();
	display();
	getch();
	int choice, c1,c2;
	courses c;
	student s;
	char ch;
	l:
	do
	 {
	system("CLS");
	gotoxy(2,0);
	for(int i=0; i<90; i++)
	{
		cout<<"_";
	}
	for(int i=0; i<22; i++)
	{
		gotoxy(1,i+1);
		cout<<"|\n";
	}
	gotoxy(2,22);
	for(int i=0; i<90; i++)
	{
		cout<<"_";
	}
	for(int i=0; i<22; i++)
	{
		gotoxy(92,i+1);
		cout<<"|\n";
	}
	gotoxy(48,26);
	cout<<"GP InFoSyS ~ Copyright (c) 2019",
	gotoxy(10,2);
	cout<<"                    ------------------------";
	gotoxy(32,4);
	cout<<"GP COMPUTER CENTRE";
	gotoxy(10,6);
	cout<<"                    ------------------------";
	gotoxy(20,8);
	cout<<"1.FOR COURSES DETAILS";
	gotoxy(20,10);
	cout<<"2.FOR STUDENT DETAILS";
	gotoxy(20,12);
	cout<<"0.TO EXIT\n\n";
	gotoxy(20,14);
	cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
	gotoxy(20,16);
	cout<<"Enter your choice:";
	cin>>choice;
	switch(choice)
	{
		case 1:
		do
		{
			system("CLS");
			cout<<"\t\t\t_________________________\n\n";
			cout<<"\t\t\t     COURSE DETAILS\n";
			cout<<"\t\t\t_________________________\n\n";
			cout<<"\t!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";
			cout<<"\n\t1.TO WRITE INTO THE COURSE FILE";
			cout<<"\n\n\t2.TO READ FROM THE COURSE FILE";
			cout<<"\n\n\t3.TO SEARCH ANY EXISTING ENTRY FROM THE COURSE FILE";
			cout<<"\n\n\t4.TO DELETE AN EXISTING ENTRY FROM THE COURSE FILE";
			cout<<"\n\n\t5.TO MODIFY AN ENTRY IN THE COURSE FILE";
			cout<<"\n\n\t6.TO DISPLAY THE SORTED LIST";
			cout<<"\n\n\t0.TO EXIT\n\n";
			cout<<"\t!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";
			cout<<"\n\tEnter your choice:";
			for(int i=0; i<27; i++)
			{
				gotoxy(100,i);
				cout<<"|\n";
			}
			for(int i=0; i<100; i++)
			{
				gotoxy(i,25);
				cout<<"_";
			}
			gotoxy(101,25);
			cout<<"__";
			gotoxy(68,26);
			cout<<"GP InFoSyS ~ Copyright (c) 2019",
			gotoxy(27,23);
			cin>>c1;
			system("cls");
			switch(c1)
			{
				case 1:
				c_writefile();
				system("pause");
				getch();
				break;
				case 2:
				c_readfile();
				system("pause");
				getch();
				break;
				case 3:
				c_searchfile();
				system("pause");
				getch();
				break;
				case 4:
				c_delfile();
				system("pause");
				getch();
				break;
				case 5:
				c_modfile();
				system("pause");
				getch();
				break;
				case 6:
				c_sort_rec();
				system("pause");
				getch();
				break;
				case 0:
				goto l;
				break;
			}
		}
		while((c1!=5));
		break;
		case 2:
		do
		{
		system("cls");
		cout<<"\t\t\t_________________________\n\n";
		cout<<"\t\t\t     STUDENT DETAILS\n";
		cout<<"\t\t\t_________________________\n\n";
		cout<<"\t!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";
		cout<<"\n\t1.TO WRITE INTO THE STUDENT FILE";
		cout<<"\n\n\t2.TO READ FROM THE STUDENT FILE";
		cout<<"\n\n\t3.TO SEARCH ANY EXISTING ENTRY FROM THE STUDENT FILE";
		cout<<"\n\n\t4.TO DELETE AN EXISTING ENTRY FROM THE STUDENT FILE";
		cout<<"\n\n\t5.TO MODIFY ANY ENTRY IN THE STUDENT FILE";
		cout<<"\n\n\t0.TO EXIT\n\n";
		cout<<"\t!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";
		cout<<"\n\tEnter your choice:";
		for(int i=0; i<27; i++)
		{
			gotoxy(100,i);
			cout<<"|\n";
		}
		for(int i=0; i<100; i++)
		{
			gotoxy(i,25);
			cout<<"_";
		}
		gotoxy(101,25);
		cout<<"__";
		gotoxy(68,26);
		cout<<"GP InFoSyS ~ Copyright (c) 2019",
		gotoxy(27,21);
		cin>>c2;
		system("cls");
		switch(c2)
		 {
		case 1:
		s_writefile();
		getch();
		break;
		case 2:
		s_readfile();
		getch();
		break;
		case 3:
		s_searchfile();
		getch();
		break;
		case 4:
		s_delfile();
		getch();
		break;
		case 5:
		s_modfile();
		getch();
		break;
		case 0:
		goto l;
		 }
		}while(c2!=6);
		case 0:
		exit(0);
		}
}
	while(choice!=2);
	getch();
	return 0;
 }
