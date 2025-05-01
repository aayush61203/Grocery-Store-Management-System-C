#include <stdio.h>
#include <iostream.h>
#include <conio.h>
#include <fstream.h>
#include <iomanip.h>
#include <stdlib.h>
#include <string.h>


class Mall                   //Parent Class
{
	int pno;
	char name[30];
	float price,dis;

	public:
		Mall()      //Default Constructor
		{
			pno=0;
			strcmp(name,"");
			price=0;
			dis=0;
		}
		void getdata()        //get detail of product
		{
			char ch;

			cout<<"\n\tEnter the details of the product...";
			cout<<"\n\tProduct No: ";
			cin>>pno;
			cin.get(ch);   //use of get (manipulator)
			cout<<"\n\tProduct Name: ";
			cin>>name;
			cout<<"\n\tProduct Price: ";
			cin>>price;
			cout<<"\n\tProduct Discount(%): ";
			cin>>dis;
		}

	   friend void showdata(Mall &); //friend function declare

		int retpno()
		{
			return pno;  //return product no
		}

		float retprice()
		{
			return price;     //return price
		}

		char* retname()
		{
			return name;  //return product name
		}

		int retdis()
		{
			return dis;  //return discount
		}
};


void showdata(Mall & obj) //definition of friend function
{
  cout<<setw(4)<<obj.pno<<setw(20)<<obj.name<<setw(8)<<obj.price<<setw(10)<<obj.dis<<"%"<<"\n\t";
}       //use of setw(manipulator)


fstream f; //fstream declare as f object
Mall m;   //class Mall is declare as m object


class Fun : public Mall    // child function is inherit from fun
{
	public :

	void menu()    // function of menu
	{
	   cout<<"\n\t";
	   cout<<setw(4)<<"P No"<<setw(20)<<"Product Name"<<setw(8)<<"Price"<<setw(10)<<"Discount";
	   cout<<"\n\t--------------------------------------------\n\t";
	}

	void enter()  //function of getdata of product
	{
	  clrscr();
	  f.open("mall.txt",ios::out|ios::app);//file open in output and append
	  m.getdata();
	  f.write((char*)&m,sizeof(Mall));//object write in file
	  f.close();
	  cout<<"\n\n\tProduct has been created...!!! ";
	  getch();
	}


	void display() //display of product
	{
	  clrscr();
	  cout<<"\n\n\t\tDISPLAYING ALL RECORDS !!!\n\n";

	  f.open("mall.txt",ios::in);//file open in input mode
	  menu();

	  while(f.peek() != EOF) //condition read till end of file
		{
		  f.read((char*)&m,sizeof(Mall));//file read
		  showdata(m);
		}
	 f.close();
	 getch();
	}

	void search() //function for search data of product
	{
	   int no,flag=0;
	   clrscr();

	   cout<<"\n\n\tEnter the Product No. of the Product to be searched: ";
	   cin>>no;

	   f.open("mall.txt",ios::in);//file open in input
	   menu();

	   while(f.read((char*)&m,sizeof(Mall)))
		{
			if(m.retpno()==no)
			{
				showdata(m);
				flag=1;
			}
		}
	   f.close();

		if(flag==0)
		cout<<"\n\n\tRecord does not exist...!!!";
		getch();
	}

	void update()  //function of update product
	{
		int no,found=0;
		clrscr();

		cout<<"\n\n\tTo Update...Enter The Product No: ";
		cin>>no;

		f.open("mall.txt",ios::in|ios::out);
		menu();

		while(f.read((char*)&m,sizeof(Mall)) && found==0)
		{
			if(m.retpno()==no)
			{
			   showdata(m);
			   m.getdata();

			   int pos=-1*sizeof(m);
			   f.seekp(pos,ios::cur);
			   f.write((char*)&m,sizeof(Mall));

			   cout<<"\n\n\t Record has been Updated...!!!";
			   found=1;
			}
		}
		f.close();

		if(found==0)
		cout<<"\n\n\tRecord Not Found ";
		getch();
	}

	void erase() // delete of product
	{
		int no;
		clrscr();

		cout<<"\n\n\n\tTo Delete...Enter The product No: ";
		cin>>no;

		f.open("mall.txt",ios::in|ios::out);
		fstream ft;
		ft.open("temp.txt",ios::out);
		f.seekg(0,ios::beg);

		while(f.read((char*)&m,sizeof(Mall)))
		{
			if(m.retpno()!=no)
			{
				ft.write((char *)&m,sizeof(Mall));
			}
		}
		ft.close();
		f.close();
		remove("mall.txt");
		rename("temp.txt","mall.txt");
			cout<<"\n\n\tRecord  has been Deleted...!!!";
			display();
		getch();
	}

	void place_order()//function of place order
	{
		int  order[30],quan[30],i=0;
		float amt,damt,total=0;
		char ch='Y';

		clrscr();
		display();

		cout<<"\n\n\t============================";
		cout<<"\n\t      PLACE YOUR ORDER";
		cout<<"\n\t============================\n";

		do
		{
			cout<<"\n\n\tEnter The Product No: ";
			cin>>order[i];
			cout<<"\tQuantity: ";
			cin>>quan[i];

			i++;
			cout<<"\n\tDo you want to order another product ?(y/n): ";
			cin>>ch;
		}while(ch=='y'||ch=='Y');


		clrscr();           //generate bill
		cout<<"\n\n\t\t************************BILL************************\n\n\t\t";
		cout<<setw(4)<<"P No"<<setw(20)<<"Product Name"<<setw(10)<<"Quantity"<<setw(8)<<"Price"<<setw(8)<<"Amount"<<setw(10)<<"Discount"<<endl;
		cout<<"\t\t------------------------------------------------------------\n\t\t";

		for(int x=0;x<=i;x++)
		{
			f.open("mall.txt",ios::in);
			f.read((char*)&m,sizeof(Mall));

			while(f)
			{
				if(m.retpno()!=order[x])
				{
					amt=0;
					damt=0;
				}
				else
				{
				    amt=m.retprice()*quan[x];
				    amt=amt-(amt*m.retdis()/100);

				    cout<<setw(4)<<order[x]<<setw(20)<<m.retname()<<setw(10)<<quan[x]<<setw(8)<<m.retprice()<<setw(8)<<amt<<setw(10)<<damt<<"\n\t\t";
				    total+=damt;
				}
				f.read((char*)&m,sizeof(Mall));
			}
			f.close();
		}

		cout<<"\n\t\t--------------------------------------------------------------";
		cout<<"\n\t\tThank You...Visit Once Again...............TOTAL = "<<"Rs."<<total;
		cout<<"\n\t\t--------------------------------------------------------------";
		getch();
	}
};


int main()
{
	clrscr();
	cout<<"\n\n\n\n\n\n\n\n\n\t\t\tGROCERY STORE MANAGEMENT SYSTEM\n\t\t\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
	cout<<"\n\n\t\t\t\tMade By: AAYUSH SHAH\n\t\t\t\t---------------------";
	getch();
	int ch;
	Fun f1;   //class function object is f1
	do
	{
		clrscr();
		cout<<"\n\n\t1.Create Products";
		cout<<"\n\n\t2.Display Products";
		cout<<"\n\n\t3.Search Products ";
		cout<<"\n\n\t4.Modify Products";
		cout<<"\n\n\t5.Delete Products";
		cout<<"\n\n\t6.Place an Order";
		cout<<"\n\n\t7.EXIT";
		cout<<"\n\n\tEnter Your Choice: ";
		cin>>ch;

		switch(ch)
		{
			case 1: f1.enter();
					break;
			case 2: f1.display();
					break;
			case 3: f1.search();
					break;
			case 4: f1.update();
					break;
			case 5: f1.erase();
					break;
			case 6: f1.place_order();
					break;
			case 7 : exit(0);
			default : cout<<"Invalid Choice";
		}
	}while(ch!='7');

	getch();
	return 0;
}

