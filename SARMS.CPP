#include<io.h>
#include<dos.h>
#include<fstream.h>
#include<conio.h>
#include<process.h>
#include<stdio.h>
#include<string.h>


    /// File Streams ///
fstream f1, f2 ,f3 ,f4 ;
    /// Global Variables ///
int srchchoice , norecord = 0 ;
    /// Student data ///
struct sd
{
	int admno, class_rno ;
	char name[40], father_name[40], add[100] ;
	int  clas ;
	char section , ph[30], brgp[5], status[20] ;
} sd1 , forsrchsd[100] ;

void disp_sd (struct sd temp) ;

    /// Class Student Data ///
class studdata
{
	sd data ;
  public:
	studdata()
	{
	}
	void accept() ;
	void modify() ;
	void del() ;
	sd search(int) ;
	void display () ;
	void generate_admno() ;
	void studdata::display_all () ;

	~studdata()
	{
		cout << " BYE " ;
	}
} S, S1;
    /// Student Marks Data ///
struct marks
{
	int admno , term;
	int eng ,hindi , maths , science , sst ;

} ;
    /// Class Student Marks ///
class studmarks
{
	marks data ;
  public:
	studmarks()
	{
	   data.eng=data.maths=data.hindi=data.science=data.sst = -1 ;
	}
	void accept() ;
	void acceptmarksdata () ;
	void display_marks () ;
	void display_all () ;
	struct marks studmarks::search(int srchadmno, int term1) ;
	void studmarks::search_all_admno() ;

	void display (marks) ;

	~studmarks()
	{
		cout << " BYE " ;
	}
} M,M1;

    /// Validation of Marks ///
int valid_range (int x)
{
	if (x >=0 && x <= 100 )
	  return 1 ;
	else
	{
	  cout << "------ invalid Marks ------" ;
	  getch () ;
	  cin.clear () ;
	  cin.ignore () ;
	  return 0 ;
	}
}
    /// Functions of Class Student Data  ///
void studdata::generate_admno()
{
	if(access("Studinfo.dat", 0)== -1 )
		data.admno = 1 ;
	else
	 {
		::f1.open("Studinfo.dat",ios::in|ios::binary) ;
		::f1.seekg(- (int) (sizeof(sd)), ios::end) ;
		::f1.read((char*)&sd1 ,sizeof(sd)) ;
		data.admno = sd1.admno + 1 ;
		::f1.close() ;
	 }
}
void studdata::accept()
{
	clrscr() ;
	generate_admno() ;

	if( access("Studinfo.dat", 0) == -1)
	  ::f1.open("Studinfo.dat",ios::out|ios::binary) ;
	else
	  ::f1.open("Studinfo.dat",ios::app|ios::binary) ;

	cout << "******************NEW RECORD*************" ;
	cout << "\n\n\tAdmno issued :\t" << data.admno ;
	cout << "\n\n\tEnter name :\t" ;
	gets(data.name) ;
	do{
	  cout << "\n\tEnter class (1 to 10):\t" ;
	  cin >> data.clas ;
	} while (data.clas < 1 || data.clas > 10 ) ;

	cout << "\n\tEnter section :\t" ;
	data.section = getch () ;
	cout << data.section ;
	cout << "\n\n\tEnter class rno. :\t " ;
	cin >> data.class_rno ;
	cout << "\n\tEnter Father's name :\t" ;
	gets(data.father_name) ;
	cout << "\n\tEnter blood group :\t" ;
	gets(data.brgp) ;
	cout << "\n\tEnter Phone no.s(2) :\t" ;
	gets(data.ph) ;
	cout << "\n\tEnter address :\t" ;
	gets(data.add) ;
	strcpy(data.status,"IN SCHOOL") ;
	::f1.write((char*)&S,sizeof(S)) ;
	::f1.close() ;
}

sd studdata::search(int srchadmno = -1)
{
	char srchname[50] ;
	clrscr() ;
	srchchoice = 1 ;
	::f1.open("Studinfo.dat", ios::in|ios::binary) ;

	if (srchadmno == -1)
	{
	   norecord = 0 ;
	   cout << " Enter by which method you want to search the student :\n" ;
	   cout << " \t1.Admno. \n\t2.Name \n\t-->" ;
	   cin >> srchchoice ;
	}
	if(srchchoice==1)
	{
	  if (srchadmno == -1 )
	  {
	    cout << " Enter the Admno you want to search :\t" ;
	    cin >> srchadmno ;
	  }
	  while(::f1.read((char*)&S.data,sizeof(S.data)))
	  {
	   if( srchadmno == data.admno )
	   {
	      norecord = 1 ;
	      break ;
	   }
	  }
	  ::f1.close() ;
	}
	else if(srchchoice==2)
	{
	  cout << " Enter the name you want to search :\t" ;
	  cin >> srchname ;
	  int i = 0 ;
	  while(::f1.read( (char *)&S,sizeof(S)))
	  {
	    if(strspn(data.name,srchname)==(strlen(srchname)))
	    {
	      norecord++ ;
	      forsrchsd[i]=S.data ;
	      i++ ;
	    }
	  }
	  cout << " The of records found by the name you entered :\t" << norecord ;
	  getch () ;
	}
	if ( norecord  == 0 )
	   S.data.admno = 0 ;
	::f1.close() ;
	return S.data ;
}

void studdata::display_all ()
{
	int count = 0 ;
	::f1.open("Studinfo.dat", ios::in|ios::binary) ;
	void disp_heading () ;

	clrscr () ;
	disp_heading () ;
	while(::f1.read( (char *)&S,sizeof(S)))
	{
	  if ( count > 6)
	  {
	     getch () ;
	     clrscr () ;
	     count = 0 ;
	     disp_heading () ;
	  }
	  disp_sd (S.data) ;
	  count++ ;
	}
	::f1.close () ;
	getch () ;
}

void studdata::display()
{
	void disp_heading ();
	clrscr() ;
	search() ;
	disp_heading () ;
	if(srchchoice==1)
	{
	  disp_sd (data) ;
	  getch () ;
	}
	else if(srchchoice==2)
	{
	  char ans='a' ;
	  for(int i=0; i<norecord; i++)
	  {
	    disp_sd (forsrchsd[i] ) ;
	    cout << "\n\tIs this is the record ?(y/n) : " ;
	    cin >> ans ;
	    if(ans=='y' || ans=='Y')
	    {
	      getch() ;
	      break ;
	    }
	    else if(ans=='n' || ans=='N')
	    {
	      delay(150) ;
	      if (i==(norecord-1))
	      {
		cout << "\n\t\t No more records found...." ;
	      }
	    }
	    else
	      cout << "Wrong choice....Enter again " ;
	  }
	 }
}

void disp_heading ()
{
	cout << "Admno Status     Name                Class sec R.No. Bld grp Phone" << endl ;
	cout << "                 FATHER's Name           Address\n" ;
	cout << "---------------------------------------------------------------------\n" ;
}

void disp_sd (struct sd temp)
{
	printf ("%-5d %-10s %-20s %-5d %-3c %3d %5s %10s\n\t\t Sh.%-20s %-30s\n",
		 temp.admno, temp.status, temp.name ,temp.clas,
		 temp.section, temp.class_rno ,temp.brgp, temp.ph ,
		 temp.father_name , temp.add );
}

void studdata::del()
{
	int admnodel, reason , flag = 0;
	clrscr () ;
	cout << "\nEnter the admno you want to delete the record of :\t" ;
	cin >> admnodel ;
	cout << " Enter 1 for Pass Out, enter 2 for TC ISSUED :\t " ;
	cin >> reason ;
	::f1.open("Studinfo.dat",ios::in|ios::binary) ;
	::f2.open("Temp.dat",ios::out|ios::binary) ;
	while(::f1.read((char*)&S,sizeof(S)))
	 {
	  if(admnodel==data.admno && reason==1)
	  {
	    S1 = S ;
	    cout << "\nRecord Found and updated\n" ;
	    cout << "NAME :\t" << S.data.name ;
	    strcpy(S1.data.status," PASS OUT ") ;
	    ::f2.write((char*)&S1,sizeof(S1)) ;
	    flag = 1 ;
	  }
	  else if(admnodel==data.admno && reason==2)
	  {
	    S1 = S ;
	    cout << "\nRecord Found and updated\n" ;
	    cout << "NAME :\t" << S.data.name ;
	    strcpy(S1.data.status," TC ISSUED ") ;
	    ::f2.write((char*)&S1,sizeof(S1)) ;
	    flag = 1 ;
	  }
	  else
	    ::f2.write((char*)&S,sizeof(S)) ;
	 }
	::f1.close() ;
	::f2.close() ;
	if (flag == 0)
	   cout << "\nNo record found\n" ;
	getch () ;
	remove("Studinfo.dat") ;
	rename("Temp.dat","Studinfo.dat") ;
}


void studdata::modify()
{
	sd sd_temp ;
	int srchadmno = 0 ,admno_temp;
	clrscr () ;
	cout << " Enter the Admno you want to Modify :\t" ;
	cin >> srchadmno ;

	sd_temp=search (srchadmno) ;
	if (sd_temp.admno == 0 )
	{
	   cout << "Record Not Found." ;
	   getch () ;
	   return ;
	}

	admno_temp = sd_temp.admno ;
	::f1.open("Studinfo.dat",ios::in|ios::binary) ;
	::f2.open("Temp.dat",ios::out|ios::binary) ;
	while(::f1.read((char*)&sd_temp,sizeof(sd_temp)))
	{
	   if(sd_temp.admno==admno_temp)
	   {
	     cout << "\n\n\tAdmno issueed :\t" << S.data.admno ;
	     cout << "\nExisting data (Press Enter for no changes)\n\n" ;
	     cout << S.data.name << "\tEnter name :\t" ;
	     gets(sd_temp.name) ;
	     if ( strlen(sd_temp.name) == 0)
		strcpy (sd_temp.name,S.data.name) ;
	     cout << endl << S.data.clas <<"\tEnter class :\t" ;
	     cin >> sd_temp.clas ;
	     if (sd_temp.clas == 0)
		sd_temp.clas = S.data.clas ;
	     cout << endl << S.data.section <<"\tEnter Section :\t" ;
	     cin >> sd_temp.section ;
	     if (sd_temp.section == ' ')
		sd_temp.section = S.data.section ;
	     cout << endl<< S.data.class_rno << "\tEnter class rno. :\t " ;
	     cin >> sd_temp.class_rno ;
	     if (sd_temp.class_rno == 0)
		sd_temp.class_rno = S.data.class_rno ;
	     cout << endl<< S.data.father_name << "\tEnter Father's name :\t" ;
	     gets(sd_temp.father_name) ;
	     if (strlen(sd_temp.father_name) == 0)
		strcpy (sd_temp.father_name,S.data.father_name) ;
	     cout << endl<< S.data.brgp << "\tEnter blood group :\t" ;
	     gets(sd_temp.brgp) ;
	     if (strlen(sd_temp.brgp) == 0)
		strcpy (sd_temp.brgp,S.data.brgp) ;
	     cout << endl<< S.data.ph << "\tEnter Phone no.s(2) :\t" ;
	     gets(sd_temp.ph) ;
	     if (strlen(sd_temp.ph) == 0)
		strcpy (sd_temp.ph,S.data.ph) ;
		cout << endl<< S.data.add << "\tEnter address :\t" ;
		gets(sd_temp.add) ;
	     if (strlen(sd_temp.add) == 0)
		strcpy (sd_temp.add,S.data.add) ;
	     strcpy(sd_temp.status,"IN SCHOOL") ;
	     ::f2.write((char*)&sd_temp,sizeof(sd_temp)) ;
	   }
	   else
	     ::f2.write((char*)&sd_temp,sizeof(sd_temp)) ;
	}
	::f1.close() ;
	::f2.close() ;
	remove("Studinfo.dat") ;
	rename("Temp.dat","Studinfo.dat") ;
}


  //// FUNCTIONS of the CLASS STUDMARKS  ////

void studmarks::accept()
{
	char term1 , choice= 'Y' , conf ;
	marks m_temp ;
	sd sd_temp ;

	clrscr() ;
	cout << "\nSELECT EXAM TERM " ;
	cout << "\n1 for 1st TERM " ;
	cout << "\n2 for 2nd TERM " ;
	cout << "\n3 for FINALS " ;

	do
	{
		term1 = getch () ;
	}
	while ( ! (term1 == '1' || term1 == '2' || term1 == '3')) ;

	M.data.term = (int) (term1-48) ;

	do
	{
	 cout << "\nEnter student adminsion Number : " ;
	 cin  >> data.admno ;
	 if ( data.admno == 0 )
	    break ;

	 // SEARCH FOR DUPLICATE DATA //

	 m_temp = search (data.admno , data.term );
	 if (m_temp.admno != 0)
	 {
	    cout << "\nduplicate data" ;
	    continue ;
	 }

	// SEARCH ADMNO IN STUDENT.DAT FILE AND DISPLAY STUDENT DATA

	 sd_temp = S.search (M.data.admno) ;
	 if (sd_temp.admno == 0)
	 {
	   cout << "\nAdmission Number not found " ;
	   continue ;
	 }
	 cout << "\nSTUDENT NAME : " << sd_temp.name << "\tCLASS : " << sd_temp.class_rno ;
	 do{
	     cout << "\nConfirm student (Y/N) : " ;
	     cin  >> conf ;
	 }
	 while ( ! ( conf == 'y' || conf=='Y' || conf=='n' || conf =='N')) ;

	 if (! (conf == 'y' || conf == 'Y' ))
	     continue ;

	 acceptmarksdata () ;
	 ::f4.open("marks.dat",ios::app|ios::binary) ;
	 ::f4.write ((char *)&M.data , sizeof (M.data) ) ;
	 ::f4.close () ;

	 cout << "\nAdd More data (Y/N)..." ;
	 cin >> choice ;
	} while (choice == 'Y' || choice == 'y' ) ;


}

void studmarks::acceptmarksdata()
{
	clrscr () ;
	cout << "\nEnter Marks : " ;
	do
	{
	  cout << "\nENGLISH : " ;

	/* Check if only numbers are entered */
	  while ( ! (cin >>  data.eng) )
	  {  cout << "\nEnter numbers only\n" ;
	     cin.clear ();
	     cin.ignore (10000,'\n');
	  }

	} while (! valid_range (data.eng)) ;
	do
	{
	  cout << "\nHINDI : " ;
	  while ( ! (cin >>  data.hindi) )
	  {  cout << "\nEnter numbers only\n" ;
	     cin.clear ();
	     cin.ignore (10000,'\n');
	  }

	} while (! valid_range (data.hindi)) ;
	do
	{
	  cout << "\nMATHS : " ;
	  while ( ! (cin >>  data.maths) )
	  {  cout << "\nEnter numbers only\n" ;
	     cin.clear ();
	     cin.ignore (10000,'\n');
	  }

	} while (! valid_range (data.maths)) ;
	do
	{
	  cout << "\nSCIENCE : " ;
	  while ( ! (cin >>  data.science) )
	  {  cout << "\nEnter numbers only\n" ;
	     cin.clear ();
	     cin.ignore (10000,'\n');
	  }

	} while (! valid_range (data.science)) ;
	do
	{
	  cout << "\nSOCIAL STUDIES : " ;
	  while ( ! (cin >>  data.sst) )
	  {  cout << "\nEnter numbers only\n" ;
	     cin.clear ();
	     cin.ignore (10000,'\n');
	  }
	} while (! valid_range (data.sst)) ;
}

void display_marks_heading ()
{
	cout << "\nADMN NO\tTERM\tENGLISH\tHINDI\tMATHS\tSCIENCE\tS.ST\t" ;
}

void studmarks::search_all_admno()
{
	int norecord = 0 ;
	sd sd_temp ;
	marks m_temp = {0,0,0,0,0,0} ;
	clrscr() ;
	::f3.open("marks.dat", ios::in|ios::binary) ;
	int srchadmno ;

	cout << "\nEnter the Admno you want to search :\t" ;
	cin >> srchadmno ;

	sd_temp = S.search (srchadmno) ;
	cout << endl << "NAME : " << sd_temp.name << '\t' << sd_temp.class_rno ;

	display_marks_heading () ;
	while(::f3.read( (char *)&m_temp,sizeof(m_temp)))
	{
	  if (srchadmno == m_temp.admno )
	  {
	    norecord++ ;
	    M.display (m_temp) ;
	  }
	}
	cout << "\nThe of records found by the name you entered :\t" << norecord ;
	getch () ;
	::f3.close() ;
}

struct marks studmarks::search(int srchadmno, int term1)
{
	int found = 0 ;
	marks m_temp = {0,0,0,0,0,0 } ;
	::f3.open("marks.dat", ios::in|ios::binary) ;

	norecord = 0 ;
	int i = 0 ;

	while(::f3.read( (char *)&m_temp,sizeof(m_temp)))
	{
	  if (srchadmno == m_temp.admno && term1 == m_temp.term)
	  {
	     found = 1;
	     break ;
	  }
	}
	if (found == 0)
	   m_temp.admno = 0 ;
	::f3.close() ;
	return m_temp ;
}

void studmarks::display_all ()
{
	marks m_temp ;
	int count = 0 ;
	::f4.open ("marks.dat",ios::in|ios::binary) ;
	clrscr () ;
	display_marks_heading () ;

	while(::f4.read( (char *)&m_temp,sizeof(m_temp)))
	{
	   if (count > 10 )
	   {
		getch () ;
		clrscr () ;
		display_marks_heading () ;
		count = 0 ;
	   }
	    M.display (m_temp) ;
	    count ++ ;
	}
	::f4.close () ;
	getch ();
}

void studmarks::display(marks m_temp)
{
	cout <<  '\n' << m_temp.admno  << '\t';
	cout <<  m_temp.term   << '\t';
	cout <<  m_temp.eng    << '\t';
	cout <<  m_temp.hindi  << '\t';
	cout <<  m_temp.maths  << '\t';
	cout <<  m_temp.science<< '\t';
	cout <<  m_temp.sst    << '\t';
}

void MenuDisplay()
{
	cout << "\n\n\t\t\t Enter the choice " ;
	cout << "\n\t\t        ------------------------------- " ;
	cout << "\n\n\t\t\t a) Add Student Record " ;
	cout << "\n\n\t\t\t b) Display Student record " ;
	cout << "\n\n\t\t\t c) Display All Student Records " ;
	cout << "\n\n\t\t\t d) Delete Student Record " ;
	cout << "\n\n\t\t\t f) Modify Student Record " ;
	cout << "\n\n\t\t\t g) Add Marks " ;
	cout << "\n\n\t\t\t h) Display marks for Admission \n\t\t\t    Number " ;
	cout << "\n\n\t\t\t i) Display All Marks Record " ;
	cout << "\n\n\t\t        ------------------------------- " ;
	cout << "\n\t\t\t    Enter e to EXIT program. " ;
}

void main()
{
	clrscr() ;
	int loop=1 ;
	char choice ;

	cout << "\n\n\n\n\n\n\n\t\t\t STUDENT ACADMIC RECORD MANAGEMENT SYSTEM \n" ;
	     getch () ;
	clrscr();
	while(loop)
	{
	  clrscr() ;
	  MenuDisplay() ;
	  choice=getch() ;
	  switch (choice)
	  {
	    case 'a' :
	    case 'A':
		S.accept() ;
		break ;
	    case 'b' :
	    case 'B' :
		S.display() ;
		break ;
	    case 'c' :
	    case 'C' :
		S.display_all () ;
		break ;
	    case 'd' :
	    case 'D' :
		S.del() ;
		break ;
	    case 'f' :
	    case 'F' :
		S.modify() ;
		break ;
	    case 'g' :
	    case 'G' :
		M.accept () ;
		break ;
	    case 'h' :
	    case 'H' :
		M.search_all_admno () ;
		break ;
	    case 'i' :
	    case 'I' :
		M.display_all () ;
		break ;
	    case 'e' :
	    case 'E' :
		exit(0) ;
	    default :
		cout << "\n\n\n\t\t\tWRONG CHOICE : Please enter again " ;
		delay(1000) ;
		clreol() ;
	   }
	 }
}