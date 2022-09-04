//TURBO CODING SQUAD
//ECE-C

#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<dos.h>
#include<process.h>
#include<string.h>
#include"correct.h"
#define go(r,c) gotoxy(c,r)

//Structures
typedef struct{
	char user[51];
	char num[51];
	char pass[51];
	char name[51];
	
}Diary;
	Diary d;
	FILE *dir;

typedef struct{
	char usern[51];
	char id[51];
	char subj[51];
	char mynote[501];
	
}Notes;
Notes n;
FILE *note;

typedef struct{
	char star_name[51];
	char star[5];
}Reviews;
Reviews r;
FILE *star;


//Func
void sc01();
void message(char *message);
void title(char*title,int row,int color);
void ermessage(char *ermessage);
void login();
void signup();
void drawbox(int sr,int sc, int r,int c);
void loading();
void fullname();
void username();
void mobile_number();
void password();
void forgotpass();
int reset(char *username);
void otp();
void screen_in(char *username);
void bluebox(int size);
void otpscreen();
void screen_in();
void errormessage(char *ermessage);
void add(char *username);
void write(char *username);
void update(char *username);
void search(char *username);
void del(char *username);
void showall(char *username);
void editprofile();
void help();
void answer();
void box(int size);
void encdec(char *username);  
void note_enc(char *id);
void note_dec(char *id);
void privacy(char *usernam); 
void encrypt(char *username);
void decrypt(char *username);
void message_2(char *message);
void message_2_2(int message);

void feedback();
void review();
////////////////////////// 	MAIN	/////////////////////////////////////////

void main(){
	clrscr();
	dir= fopen("dir.dat","rb+");
		 if(dir==NULL)	dir=fopen("dir.dat","wb+");
	note=fopen("notes.dat","rb+");
		if (note==NULL) note=fopen("notes.dat","wb+");
	star=fopen("star.dat","rb+");
		if (star==NULL) note=fopen("star.dat","wb+");	

	sc01();//Entry Screen
}

/////////////////////////////////////////////////////////////////////////////


void sc01()
{
	char ch,x,j;
	clrscr();
	while(1){
		int sr=1,sc=1,r=22,c=78;

		title("     VIRTUAL NOTES ASSISTANT     ",4,WHITE);
		drawbox(sr,sc,r,c);
		drawbox(3,22,18,35);
		textbackground(BLACK);
		gotoxy(38,9);textcolor(YELLOW);cprintf("L");textcolor(LIGHTCYAN);cprintf("ogin");
		gotoxy(38,11);textcolor(YELLOW);cprintf("S");textcolor(LIGHTCYAN);cprintf("ignup");	
		gotoxy(38,13);textcolor(YELLOW);cprintf("R");textcolor(LIGHTCYAN);cprintf("eviews");	
		gotoxy(38,15);textcolor(YELLOW);cprintf("E");textcolor(LIGHTCYAN);cprintf("xit");
		textcolor(LIGHTCYAN);
		
		go(25,23);
		cprintf("  Developed By TURBO CODING SQUAD  ");
		gotoxy(23,18);
		cprintf("       Enter your choice:      ");
		gotoxy(50,18);
		ch=getchar();
		//getch();
		switch(ch){
			case 'e': case 'E':
			exit(0);

			case 'L': case 'l':	{	loading();login();
								break;	}
			
			case 'S': case 's':{	loading();signup();
								break;  }
			case 'R': case 'r':{	review();
								break;  }
			default:				
				ermessage("Invalid choice.. press [L/S/E]");
				break;
			}
		}
	//getch();
}
// Review Screen

void review(){
	//1st
	int i;
	clrscr();
	title("OUR REVIEWS",4,WHITE);
	
	rewind(star);
	gotoxy(1,8);
	while(fread(&r,sizeof(r),1,star)){
	textcolor(CYAN);
	printf("\t\t\t\t");
	cprintf("%-10s:",r.star_name);
	textcolor(RED);
	for(i=0;i<atoi(r.star);i++){
		cprintf(" %c",3);
	}
	printf("\n\n");
    }
    gotoxy(46,4);
	getch();
	

}

//Screen(Sign-Up)



void fullname()
{
	gotoxy(32,10);
	textbackground(WHITE);
	cprintf("                         ");fflush(stdin);
	gotoxy(32,10);
	for(;;){
		fflush(stdin);gets(d.name);
		if(corr_Name(d.name)) 
			break;
		else
			message("Sorry! Invalid Name... Please renter");
			getch();
			signup();
	}
	fseek(dir,0,SEEK_END);
	fwrite(&d,sizeof(d),1,dir);

}

void username()
{	char str1[51];int check=0;
	gotoxy(32,12);
	textbackground(WHITE);
	cprintf("                         ");fflush(stdin);
	gotoxy(32,12);
	for(;;){
	    fflush(stdin);gets(str1);
 		if((corr_username(str1))&&(strlen(str1)<11))
		 {
 			rewind(dir);
 			while(fread(&d,sizeof(d),1,dir))
 			{
 				if(strcmp(str1,d.user)==0)	//already exists
 				{
				check++;break;}
			 }
			 if(check==0){
			 		strcpy(d.user,str1);
					break;
			 }
			 else	{
			 message("Username Already Exists Reenter");
			 getch();
			 signup();
		}

			}
			else{
				message("Invalid Username: ");
				getch();
				signup();
			}
}
	fseek(dir,0,SEEK_END);
	fwrite(&d,sizeof(d),1,dir);
}
void mobile_number()
{	char str3[51];int check=0;
	gotoxy(32,14);
	textbackground(WHITE);
	cprintf("                         ");fflush(stdin);
	gotoxy(32,14);
		for(;;){	
	    fflush(stdin);
		scanf("%s",&str3);
		if((corr_num(str3))&&(strlen(str3)==10)){
			strcpy(d.num,str3);
			break;
			}
			else{
				message("\nNumber must be of 10 characters.Renter");
				getch();
				signup();
				
			}
}
	fseek(dir,0,SEEK_END);
	fwrite(&d,sizeof(d),1,dir);
	//system("pause");

}

void password()
{       char str2[51],st;int check=0,ct;
	gotoxy(32,16);
	textbackground(WHITE);
	cprintf("                         ");fflush(stdin);
	gotoxy(32,16);
	for(;;){
		fflush(stdin);
	    scanf("%s",&str2);
 		if((corr_username(str2))&&(strlen(str2)<9)){
			strcpy(d.pass,str2);
			break;
			}
			else{
				message("Sorry! Invalid Password... Please renter the password : ");
				getch();
				gotoxy(32,16);
	}
}
	fseek(dir,0,SEEK_END);
	fwrite(&d,sizeof(d),1,dir);

}
void signup()
{
    int x;char choice;
    system("cls");


    title("Sign Up",6,WHITE);
    textcolor(CYAN);
    textbackground(BLACK);
    gotoxy(16,10);
    cprintf("Fullname");
    textcolor(CYAN);
    textbackground(BLACK);
    gotoxy(16,12);
    cprintf("Username");
    textcolor(CYAN);
    textbackground(BLACK);
    gotoxy(16,14);
    cprintf("Mobile Number");
    textcolor(CYAN);
    textbackground(BLACK);
    gotoxy(16,16);
    cprintf("Password");
    textcolor(CYAN);
    textbackground(BLACK);
    gotoxy(16,18);
    //cprintf("Confirm Password");
    textcolor(BLACK);
	drawbox(3,10,19,60);
    fullname();
    username();
    mobile_number();
    password();

    textcolor(YELLOW);
    textbackground(BLACK);
    gotoxy(20,20);
    cprintf("Press S to Submit");
    textcolor(BLACK);
    textbackground(WHITE);
    gotoxy(40,20);
    cprintf("                      ");
    for(x=0;x<=5;x++)
    {
	 gotoxy(40,20);
	 scanf("%c",&choice);
	 switch(choice)
	 {
		case 's': {
			
			//login();
			otpscreen();
			break;
		}
		default: break;
	 }
    }
     //return 0;
}


//Screen (Login)

void login()
{	int i=0,mychoice,p=0;
	int a,b;
	char username[51];char pass[51];
    char choice;int x;
    system("cls");
//    drawbox(4,15,16,50);
    textcolor(WHITE+BLINK);
    textbackground(RED);
    //gotoxy(38,6);
    title("Login",6,WHITE);
    textcolor(CYAN);
    textbackground(BLACK);
    gotoxy(24,10);
    cprintf("Username");
    textcolor(CYAN);
    textbackground(BLACK);
    gotoxy(24,12);
    cprintf("Password");
    textcolor(LIGHTBLUE);
    drawbox(4,15,16,50);
    //usern
    gotoxy(35,10);
	textbackground(WHITE);
	cprintf("                         ");fflush(stdin);
	gotoxy(35,10);
	scanf("%s",&username);
	//pass
	gotoxy(35,12);
	textbackground(WHITE);
	cprintf("                         ");fflush(stdin);
	gotoxy(35,12);
    do{
        pass[p]=getch();
        if(pass[p]!='\r'){
            printf("*");
        }
        p++;
    }while(pass[p-1]!='\r');
    pass[p-1]='\0';
    //getch();


	//checking
	rewind(dir);
	while(fread(&d,sizeof(d),1,dir))
	{	a=strcmp(d.user,username);
		b=strcmp(d.pass,pass);
		if((a==0)&&(b==0))
		{
			i=1;break;

		}
	}
	if(i)
	{
		printf("Welcome %s\n",username);
		screen_in(username);
	}
	else
	{	gotoxy(32,15);
		printf("Wrong Credentials");
		gotoxy(32,16);
		printf("1. Try again");
		gotoxy(32,17);
		printf("2. Forgot Password");
		gotoxy(32,18);
		printf("Enter your Choice: ");scanf("%d",&mychoice);
		switch(mychoice){
			case 1: login();break;
			case 2: forgotpass();break;
			default: login();
		}
		}

		system("pause");

}

///Forgot Password

void forgotpass(){

	char username[51],num[51];int i=0;
	system("cls");
	printf("\n\n\t\t\t***************************\n");
    printf("\t\t\t* RESET PASSWORD *");
	printf("\n\tEnter your username: ");scanf("%s",&username);
	printf("\n\tEnter your Phone Number: ");scanf("%s",&num);
	rewind(dir);
	while(fread(&d,sizeof(d),1,dir))
	{
		if((strcmp(username,d.user)==0)&&(strcmp(num,d.num)==0))
		{	i=1;break;
			}
	}
	if(i)
		reset(username);
	else
		printf("Wrong Number!");
		
sc01();
}

int reset(char *username)
{

	char pass[51];
	system("cls");
	printf("Enter your new Password: ");
		for(;;){
	    scanf("%s",&pass);
 		if((corr_username(pass))&&(strlen(pass)<9)){
			strcpy(d.pass,pass);
			fseek(dir,-sizeof(d),SEEK_CUR);
			fwrite(&d,sizeof(d),1,dir);
			break;
			}
			else{
				printf("\nInvalid Password \nRules:-\nPassword must be less than 9 characters.\n");
				printf("No space or special character allowed.\nUse only number and alphabets.\n");
				printf("Renter Password: ");
			}
}
	login();
	system("pause");
}


//Screen (Human Verification)

void otpscreen(){
	int otp,a,s=0,i,num;
	char ch;
	clrscr();
	while(1){
		//clrscr();
		
		title("Human Verification",4,WHITE);
		gotoxy(30,21);
		message_2("Captcha");
		num=((rand()%10000)+1);
		//printf("%d",num);
		message_2_2(num);
		gotoxy(30,12);
		textcolor(LIGHTCYAN);
		cprintf("  Enter Code-");textcolor(LIGHTCYAN);drawbox(3,22,18,35);
		gotoxy(45,12);
		scanf("%d",&otp);gotoxy(47,12);
		
		if(num!=otp){
			message("Invalid otp");
			getch();
			otpscreen();
		}
		else{
			gotoxy(30,15);
			textcolor(LIGHTCYAN);
			printf("Loading");
			for(i=0;i<15;i++){
				textbackground(WHITE);
				cprintf(" ");
				delay(10);
				textbackground(BLACK);
			}

			message("   VERIFIED!!!!   ");
			gotoxy(50,23);
			getch();
			login();
		}
	}
}


//Screen (Main Interface)


void screen_in(char *username){
	char choice;
		 
	//clrscr();
	system("cls");
//	drawbox(2,10,22,58);
	textbackground(BLACK);
	for(;;){
		system("cls");
		title("Main Menu",4,WHITE);
		textcolor(YELLOW);
		gotoxy(34,6);cprintf("C");textcolor(LIGHTCYAN);cprintf("reate a note");
		textcolor(YELLOW);gotoxy(35,8);cprintf("O");textcolor(LIGHTCYAN);cprintf("pen a note");
		textcolor(YELLOW);gotoxy(35,10);cprintf("E");textcolor(LIGHTCYAN);cprintf("dit a note");
		textcolor(YELLOW);gotoxy(34,12);cprintf("S");textcolor(LIGHTCYAN);cprintf("how all notes");
		textcolor(YELLOW);gotoxy(34,14);cprintf("D");textcolor(LIGHTCYAN);cprintf("elete a note");
		textcolor(YELLOW);gotoxy(35,16);cprintf("P");textcolor(LIGHTCYAN);cprintf("rivate safe");
		textcolor(YELLOW);gotoxy(33,18);cprintf("H");textcolor(LIGHTCYAN);cprintf("elp / ");textcolor(YELLOW);cprintf("F");textcolor(LIGHTCYAN);cprintf("eedback");
		textcolor(YELLOW);gotoxy(37,20);cprintf("L");textcolor(LIGHTCYAN);cprintf("og out");
		
		textcolor(BLACK);
		drawbox(2,10,22,58);
		//message("Select a choice");
		textcolor(BLACK);
		gotoxy(32,22);
		printf("Enter choice : ");
		gotoxy(45,22);
		bluebox(10);
		gotoxy(45,22);
		choice=getchar();
//		scanf("%c",&choice);

		switch(choice){
			case 'o':case 'O':	search(username);break;
			case 'c':case 'C':	add(username);break;
			case 'e':case 'E':	update(username);break;
			case 's':case 'S':	showall(username);break;
			case 'd':case 'D':	del(username);break;
			case 'p':case 'P':	privacy(username);break;
			case 'h':case 'H':	help();break;
			case 'l': case 'L': sc01();break;
			case 'f': case 'F': feedback();break;
			default:
				errormessage("Invalid Choice..");//getch();
		}
	}
}

////Feedback
void feedback(){
	char for_star[5],a[]="5";system("cls");			
	while(1){	
	printf("\n\n\t\t\t**************************\n");
    printf("\t\t\t * RATE YOUR EXPERIENCE *");	
    drawbox(1,1,22,78);
    gotoxy(19,8);
		printf("Rate our Product(_\\5): ");fflush(stdin);gets(for_star);
		
		if(atoi(for_star)>5){

			message_2("Thank You for the Extra Stars, but we'll keep only 5 with us :)");
			strcpy(r.star,a);
			break;
		}	
		else	
			{
			strcpy(r.star,for_star);
			break;
		}	
	}
	
	gotoxy(19,10);
	printf("Enter a display Name that we can use: ");fflush(stdin);gets(r.star_name);
	
	fseek(star,0,SEEK_END);
	fwrite(&r,sizeof(r),1,star);
	
	gotoxy(26,13);
	textcolor(RED+BLINK);
	cprintf("Thanks for the Feedback!!!"); 
	fflush(stdin);
	printf("\n\n");gotoxy(37,14);getch();
	//system("pause");
}

////Notes
	         //////////////////////////////////////_ADD_ENTRY_////////////////////////////////////

void add(char *username){

	char id1[51],id2[51];
	system("cls");
	
	strcpy(id1, username);
	
	printf("\n\n\t\t\t***************************\n");
    printf("\t\t\t* WELCOME TO THE ADD MENU *");
    
	printf("\n\n\nAssign an ID to your Note:\t%s-",id1);
	
	fflush(stdin);gets(id2);
	strcat(id1,id2);
	strcpy(n.id,id1);
	
	textcolor(LIGHTGRAY+BLINK);
	cprintf("\n\nYour ID is: %s",n.id);
	textcolor(WHITE);
	
	printf("\n\n\n\nName/Subject of Note: ");
	fflush(stdin);gets(n.subj);
	printf("\n\nYour Note: \n\n=> ");
	fflush(stdin);gets(n.mynote);

	fseek(note,0,SEEK_END);
	fwrite(&n,sizeof(n),1,note);
	
	textcolor(RED+BLINK);
	cprintf("\nRecord Saved..."); 
	fflush(stdin);
	printf("\n\n");
	system("pause");	
}

 			///////////////////////////////////_UPDATE_ENTRIES_////////////////////////////////////
void update(char *username){
	FILE * temp = fopen("temp", "wb");
	
	
	int i=0,a,choice;
	char id[51],subj[51],mynote[501];
	system("cls");
	
	printf("\n\n\t\t\t******************************\n");
    printf("\t\t\t* WELCOME TO THE UPDATE MENU *");
	
	printf("\n\n\nEnter your Note ID that needs to be updated: ");scanf("%s",&id);
	rewind(note);
	while(fread(&n,sizeof(n),1,note)){
		a=strcmp(n.id,id);
		if(a==0)
			{
			i=1;break;}
	}
	if(i)
	{	
	
		printf("\n\nOld Subject:\t\t%s\nEnter New Subject:\t",n.subj);fflush(stdin);gets(subj);
		printf("\n\nOld Note:\t\t%s\nEnter New Note:\n=> ",n.mynote);fflush(stdin);gets(mynote);
		
		//1-Delete Record
		
	    rewind(note);
	    while (fread( &n, sizeof(n), 1, note)) {
	    	a=strcmp(n.id,id);
	      if (a != 0) {
	        fwrite( &n, sizeof(n), 1, temp);
	      }
	    }
	    fclose(note);
	    fclose(temp);
	    remove("notes.dat");
	    rename("temp", "notes.dat");
	    note = fopen("notes.dat", "rb+");
		//
		
		//2-Add that record with updated details		
		strcpy(n.id,id);
		strcpy(n.subj,subj);
		strcpy(n.mynote,mynote);
	
		fseek(note,0,SEEK_END);
		fwrite(&n,sizeof(n),1,note);
		//
		textcolor(RED+BLINK);
		cprintf("\nRecord Updated...");printf("\n");
	}
	else{
		textcolor(RED+BLINK);
		cprintf("\nID not found.");printf("\n\n");
	}
system("pause");
}
/////////////SHOW ALL///////////////////////////////////////////

void showall(char *username){
	
	char str[80], search[10];
    int count1 = 0, count2 = 0, i, j, flag;
    system("cls");
    printf("\n\n\t\t\t*******************************\n");
    printf("\t\t\t\t* YOUR NOTES *");
    rewind(note);
	while(fread(&n,sizeof(n),1,note)){
		strcpy(search,username);
		strcpy(str,n.id);
    while (str[count1] != '\0')
        count1++;
    while (search[count2] != '\0')
        count2++;
    for (i = 0; i <= count1 - count2; i++)
    {
        for (j = i; j < i + count2; j++)
        {
            flag = 1;
            if (str[j] != search[j - i])
            {
                flag = 0;
                break;
            }
        }
        if (flag == 1)
            break;
    }
    if (flag == 1){
    	textcolor(RED+BLINK);
    	printf("\n\n");
		cprintf("Your Note:\n");
		printf("\nID: \t\t%s\nSUBJECT: \t%s\nNOTE: \t\t%s\n\n\n",n.id,n.subj,n.mynote);
		//break;
	}

        
}
	system("pause");
}



 				///////////////////////////////////_SEARCH_ENTRIES_////////////////////////////////////

void search(char *username){
	int i=0,a;
	char id[51];
	clrscr();system("cls");
	printf("\n\n\t\t\t*******************************\n");
    printf("\t\t\t* WELCOME TO THE SEARCH MENU *");
    
	printf("\n\n\nEnter your Note ID that needs to be shown: ");fflush(stdin);gets(id);
	rewind(note);
	while(fread(&n,sizeof(n),1,note)){
		a=strcmp(n.id,id);
		if(a==0)
			{
			i++;break;}
	}
	if(i)
	{
		textcolor(RED+BLINK);
		cprintf("\nYour Note:\n",id);
		printf("\nID: \t\t%s\nSUBJECT: \t%s\nNOTE: \t\t%s\n\n\n",n.id,n.subj,n.mynote);

		}
		else{
		textcolor(RED+BLINK);
		cprintf("\nID not found.");printf("\n\n");
	}
		system("pause");
}

void del(char *username) {
  int found = 0,a;
  char idno[51];
  system("cls");
  printf("\n\n\t\t\t******************************\n");
    printf("\t\t\t* WELCOME TO THE DELETE MENU *");
  printf("\n\n\nEnter Note ID to delete : ");
  fflush(stdin);gets(idno);
  rewind(note);
  while (fread( &n, sizeof(n), 1, note)) {
  	a=strcmp(n.id,idno);
    if (a == 0) {
      found = 1;
      break;
    }
  }
  if (found) {
    FILE * temp = fopen("temp", "wb");
    rewind(note);
    while (fread( &n, sizeof(n), 1, note)) {
    	a=strcmp(n.id,idno);
      if (a != 0) {
        fwrite( &n, sizeof(n), 1, temp);
      }
    }
    fclose(note);
    fclose(temp);
    remove("notes.dat");
    rename("temp", "notes.dat");
    note = fopen("notes.dat", "rb+");
    textcolor(RED+BLINK);
    cprintf("\nRecord Deleted...");printf("\n\n");
  } 
  else {
  	textcolor(RED+BLINK);
  	cprintf("\nRecord not found");printf("\n\n");
  }
  system("pause");
}
//////////////////////////////////////////////////Help//////////////////////////////////////////////////

void help(){
	int k;
	system("cls");
	for(;;){
		clrscr();
		drawbox(1,1,22,78);
		gotoxy(35,4);
		textcolor(YELLOW);
		cprintf("QUESTIONS");
		gotoxy(6,6);
		cprintf("1. About me");
		gotoxy(6,8);
		cprintf("2. Is notes assistance safe?");
		gotoxy(6,10);
		cprintf("3. How our notes assistance is better then others note maker?");
		gotoxy(6,12);
		cprintf("4. Developers of this notes assistant?");
		gotoxy(6,14);
		cprintf("5. What are its additional features?");
		gotoxy(6,16);
		cprintf("6. What are the language and tools used?");
		gotoxy(6,18);
		cprintf("=> Press 0 or 9 to return ");
		gotoxy(10,21);
		cprintf("Press any given Query number: ");gotoxy(40,21);
		scanf("%d",&k);
		switch(k){
			case 1:
				clrscr();
				answer();
				gotoxy(3,10);
				textcolor(LIGHTCYAN);
				cprintf("It is utility based application.A simple note keeper that can be accessed easily.User can perform CRUD operations.After users enter their details to create an account, we’ll verify their identity by sending an OTP to their provided email address.");
				getch();
				break;
			case 2:
				clrscr();
				answer();
				gotoxy(3,10);
				textcolor(LIGHTCYAN);
				cprintf("Yes, absolutely safe!! it has two layer authentication protection that are OTP verification and login credentials.");
				getch();
				break;
            case 3:
				clrscr();
				answer();
				gotoxy(6,10);
				textcolor(LIGHTCYAN);
				cprintf("It is flexible tool can be used by any age group to maintain notes.");
				getch();
				break;
            case 4:
				clrscr();
				answer();
				gotoxy(10,10);
				textcolor(LIGHTCYAN);
				cprintf("1.Sakshi Gupta\n2.Ujjawal Tripathi\n3.Utkarsh Goel\n 4.Yati Jaiswal");
				getch();
				break;
            case 5:
				clrscr();
				answer();
				gotoxy(3,10);
				textcolor(LIGHTCYAN);
				cprintf("It has some additional features are checking privacy through encrypting and decrypting the notes. ");
				getch();
				break;
            case 6:
				clrscr();
				answer();
				gotoxy(6,10);
				textcolor(LIGHTCYAN);
				cprintf("Languages used are-ANSI C,C language.Tools are-Turbo C++, Code Blocks");
				getch();
				break;
			case 0:
				clrscr();
				sc01();
			case 9:
				return;
		}
	}
}
void answer(){
	clrscr();
	drawbox(1,1,22,78);
}

////////////////////////////////////Private Safe///////////////////////////////////

////Private Safe Main Screen//////
void privacy(char *username){
char pass[51];
int p=0;


title("PRIVACY SAFE",5,WHITE+BLINK);

textcolor(CYAN);
textbackground(BLACK);
gotoxy(12,8);
cprintf("You can add an extra layer of security to your notes by");
gotoxy(12,9);
cprintf("encrypting or decrypting your files using your password.");
gotoxy(12,11);
cprintf("After you've encrypted your note, you'll need to remember");
gotoxy(12,12);
cprintf("a code that will be provided to you.");
gotoxy(12,14);
cprintf("To decrypt your file, you'll need to enter that code.");
textcolor(YELLOW);
drawbox(2,8,20,65);
gotoxy(20,18);
cprintf("Enter Password: ");
textcolor(BLACK);
gotoxy(40,18);box(20);gotoxy(41,18);

 do{
        pass[p]=getch();
        if(pass[p]!='\r'){
            printf("*");
        }
        p++;
    }while(pass[p-1]!='\r');
    pass[p-1]='\0';

if(strcmp(d.pass,pass)==0){
encdec(username);
getch();
}
else{

message("Incorrect Password...");
getch();
privacy(username);
}

}



////Private safe Menu with Options////
void encdec(char *username){
char ch;
for(;;){
clrscr();
drawbox(4,4,10,10);
title("You have entered the Private Safe",5,WHITE+BLINK);
textbackground(BLACK);
gotoxy(36,9);


textcolor(YELLOW);cprintf("E");textcolor(LIGHTCYAN);cprintf("ncrypt");
gotoxy(36,11);
textcolor(YELLOW);cprintf("D");textcolor(LIGHTCYAN);cprintf("ecrypt");
gotoxy(37,13);
textcolor(LIGHTCYAN);cprintf("e");textcolor(YELLOW);cprintf("X");textcolor(LIGHTCYAN);cprintf("it");
gotoxy(20,18);
textcolor(YELLOW);cprintf("Enter your Choice");textcolor(WHITE);cprintf("[E/D/X]: ");textcolor(BLACK);
drawbox(2,8,20,65);
gotoxy(46,18);box(10);gotoxy(47,18);
textcolor(BLACK);
scanf("%c",&ch);

switch(ch){

	case 'E': case 'e':
			encrypt(username);
			break;


	case 'D':case 'd':
			decrypt(username);
			break;


	case 'x':case 'X':
			screen_in(username);
			break;


	default:
			
			message("Incorrect Choice");
			getch();
			encdec(username);


}

}
//getch();
}
//////////Encryption/////////////
void encrypt(char *username){
int x;char ch;
char id[51];
clrscr();
title("Encryption",5,WHITE+BLINK);
textbackground(BLACK);
gotoxy(15,11);
textcolor(YELLOW);cprintf("E");textcolor(LIGHTCYAN);cprintf("nter the Note ID you need to encrypt: ");
gotoxy(15,13);
textcolor(YELLOW);cprintf("R");textcolor(LIGHTCYAN);cprintf("eturn to Main Menu");
gotoxy(20,16);
textcolor(LIGHTCYAN);
cprintf("Enter your choice");
textcolor(YELLOW);
cprintf("[E/R]: ");
textcolor(BLACK);
			gotoxy(45,16);
			for(x=0;x<15;x++){
				textbackground(WHITE);
				cprintf(" ");
				textcolor(WHITE);
				textbackground(BLACK);
			}
textcolor(BLACK);
gotoxy(45,16);
textcolor(BLACK);
scanf("%s",&ch);textcolor(BLACK);

switch(ch){
 case 'e':case 'E':{
	gotoxy(57,11);
	box(10);
	gotoxy(58,11);fflush(stdin);gets(id);
	note_enc(id);
	break;
 }
 case 'r':case 'R':{
	screen_in(username);
	break;
 }
 default: {
 	//gotoxy(25,20);
 		message("Incorrect Choice");
		getch();
	  	encrypt(username);
	  }
}
getch();
}
void note_enc(char *id){
	int a,i,found=0;
	char mynote[501],subj[51];
	FILE * temp = fopen("temp", "wb");
	rewind(note);
	while(fread(&n,sizeof(n),1,note)){
		a=strcmp(n.id,id);
		if(a==0)
			{found++;break;}
	}
	if(found)
	{	strcpy(mynote,n.mynote);
		strcpy(subj,n.subj);
		for(i = 0; (i < 501 && mynote[i] != '\0'); i++)
        	mynote[i] = mynote[i] + 3;       	
//		printf("Your key is 3");
					
		//1-Delete Record
		
	    rewind(note);
	    while (fread( &n, sizeof(n), 1, note)) {
	    	a=strcmp(n.id,id);
	      if (a != 0) {
	        fwrite( &n, sizeof(n), 1, temp);
	      }
	    }
	    fclose(note);
	    fclose(temp);
	    remove("notes.dat");
	    rename("temp", "notes.dat");
	    note = fopen("notes.dat", "rb+");
		//
		
		//2-Add that record with updated details		
		strcpy(n.id,id);
		strcpy(n.subj,subj);
		strcpy(n.mynote,mynote);
	
		fseek(note,0,SEEK_END);
		fwrite(&n,sizeof(n),1,note);
		//
		
		message("Record Encrypted: Your KEY is 3");
		getch();
		screen_in(username);
		
	}
		
		
	else{
		message("ID not found");
		getch();
		encrypt(username);
	}
system("pause");
}
//////////Decryption/////////////
void decrypt(char *username){

int x;
char ch,id[51];
clrscr();
title("Decryption",5,WHITE+BLINK);
textbackground(BLACK);
gotoxy(15,11);
textcolor(YELLOW);cprintf("E");textcolor(LIGHTCYAN);cprintf("nter the Note ID you need to decrypt: ");
gotoxy(15,13);
textcolor(YELLOW);cprintf("R");textcolor(LIGHTCYAN);cprintf("eturn to Main Menu");
gotoxy(20,16);
textcolor(LIGHTCYAN);
cprintf("Enter your choice");
textcolor(YELLOW);cprintf("[E/R]: ");
textcolor(BLACK);
			gotoxy(45,16);
			for(x=0;x<25;x++){
				textbackground(WHITE);
				cprintf(" ");
				textcolor(WHITE);
				textbackground(BLACK);
			}
			textcolor(BLACK);
gotoxy(45,16);textcolor(BLACK);
scanf("%s",&ch);

switch(ch){
 case 'e':case 'E':{
	gotoxy(57,11);
	box(10);
	gotoxy(58,11);
	fflush(stdin);gets(id);
	note_dec(id);
	break;
 }
 case 'r':case 'R':{
	screen_in(username);
	break;
 }
 default: {
 message("Incorrect Choice");
		getch();
	  decrypt(username);
	  }
}
getch();
}

void note_dec(char *id){
	int a,i,found=0,code;
	char mynote[501],subj[51];
	FILE * temp = fopen("temp", "wb");
	rewind(note);
	while(fread(&n,sizeof(n),1,note)){
		a=strcmp(n.id,id);
		if(a==0)
			{found++;break;}
	}
	if(found)
	{	
		message("Enter decipher code:");
		//getch();
		scanf("%d",&code);
		
		if(code==3){
			strcpy(mynote,n.mynote);
			strcpy(subj,n.subj);
			for(i = 0; (i < 501 && mynote[i] != '\0'); i++)
	        	mynote[i] = mynote[i] - 3;       	
			//printf("Your key is 3");
			
			//1-Delete Record
			
		    rewind(note);
		    while (fread( &n, sizeof(n), 1, note)) {
		    	a=strcmp(n.id,id);
		      if (a != 0) {
		        fwrite( &n, sizeof(n), 1, temp);
		      }
		    }
		    fclose(note);
		    fclose(temp);
		    remove("notes.dat");
		    rename("temp", "notes.dat");
		    note = fopen("notes.dat", "rb+");
			//
			
			//2-Add that record with updated details		
			strcpy(n.id,id);
			strcpy(n.subj,subj);
			strcpy(n.mynote,mynote);
		
			fseek(note,0,SEEK_END);
			fwrite(&n,sizeof(n),1,note);
			//
			//decrypt(username);
			message_2("Record Decrypted");	
			getch();
			screen_in(username);
		}
		else{
		message("Incorrect decipher code");
		getch();
		decrypt(username);
	}
	}
		
		
	else{
	message("ID not found");
		getch();
	decrypt(username);
	}
system("pause");
}

/////////////////////////////////////////Extra Func/////////////////////////////////////

void bluebox(int size){
	int i;
	textbackground(WHITE);
	for(i=1;i<=size;i++)
	  cprintf(" ");
	textbackground(BLACK);
}


void errormessage(char *ermessage){
	int col=40-strlen(ermessage)/2;
	gotoxy(15,24);bluebox(50);
	gotoxy(col,24);
	textcolor(RED);
	printf("%s",ermessage);
	textcolor(WHITE);
	textbackground(BLACK);
}
void ermessage(char *ermessage){
	int col=40-strlen(ermessage)/2;
	gotoxy(col,20);
	textcolor(RED);
	cprintf("%s",ermessage);
	textbackground(BLACK);
}
void loading(){                 int i;
				clrscr();
				go(10,20);
				textbackground(WHITE);
				textcolor(WHITE);
				printf("Loading ");
				for(i=0;i<20;i++){
					cprintf(" ");
					delay(40);
				}
				textbackground(BLACK);
}
void message(char *message){
	int col=40-strlen(message)/2;
	gotoxy(col,23);
	textcolor(LIGHTCYAN);
	textbackground(RED);
	cprintf("%s",message);
	textbackground(BLACK);
	}
void message_2(char *message){
	int col=40-strlen(message)/2;
	gotoxy(col,21);
	textcolor(LIGHTCYAN);
	textbackground(RED);
	cprintf("%s",message);
	textbackground(BLACK);
	}
void message_2_2(int message){
	char snum[11];int col;
	itoa(message,snum,10);
	col=40-strlen(snum)/2;
	gotoxy(col,20);
	textcolor(YELLOW);
	cprintf("%s",snum);
	textbackground(BLACK);
	}
void title(char*title,int row,int color){
	int col=40-strlen(title)/2;
	system("cls");
	gotoxy(col,row);
	textcolor(color+BLINK);
	textbackground(RED);
	cprintf("%s",title);
	textcolor(WHITE);
	textbackground(BLACK);
}

void drawbox(int sr,int sc, int r,int c){
	int i,j;
	gotoxy(sc,sr);
	printf("%c",201);
	for(i=1;i<=c;i++)
	printf("%c",205);
	printf("%c",187);
	for(i=1;i<=r;i++){
		gotoxy(sc,sr+i);
		printf("%c",186);
		gotoxy(sc+c+1,sr+i);
		printf("%c",186);
	}
	gotoxy(sc,sr+i);
	printf("%c",200);
	for(i=0;i<c;i++){
		printf("%c",205);
	}
	printf("%c",188);

}

void box(int size){
	int i;
	textbackground(WHITE);
	for(i=1;i<=size;i++)
	  cprintf(" ");
	textbackground(BLACK);
}
