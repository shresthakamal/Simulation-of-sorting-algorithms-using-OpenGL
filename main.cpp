#include<windows.h>
#ifdef __APPLE__
#else
#include <GL/glut.h>
#endif
#include <stdlib.h>
#include<stdio.h>
#include<string.h>
#include<iostream>


using namespace std;
#define win_height 700
#define win_width 1300

#define No_of_sorting_algos 3
#define MAX 75
#define width_bar 0.5
#define height_bars 4
#define start_pos_bars 10
#define SPEED 1500

int k=0;// Displaying the initial screen

//Sorting status check
int sorting=0;

//SORTING ALGORITHMS
char *name_of_algos[]={"Selection Sort","Bubble Sort","Insertion Sort"};
int sort_count=0;	// To cycle through the string

//BAR COLOURING
int pos=0;
int pos2=1;
int pos3=MAX-1;

//Variables for Bubble Sort
int bubble_green=MAX-1;
int count_bubble=0;

//Variables for selection sort
int s_temp;
int m=0;
int s_counter=0;
int select_j=1;

//Variables for insertion Sort
int flag=0;
int insert_counter=0;

int swapflag=0;
int a[MAX];
int i=0,j=0;

void int_str(int rad,char r[])
{
	itoa(rad,r,10);
}

void output_text(int x, int y, char *string, void *font)
{
	int len, i;

	glRasterPos2f(x, y);
	len = (int) strlen(string);
	for (i = 0; i < len; i++) {
		glutBitmapCharacter(font, string[i]);
	}
}

void screen_display()
{
	glColor3f(1,1,1);
	output_text(150, 550, "SIMULATIONS OF SORTING ALGORITHMS",GLUT_BITMAP_TIMES_ROMAN_24);
    glColor3f(1,1,1);

if (sorting!=1){
        output_text(10, 475, "Selected sort: ",GLUT_BITMAP_9_BY_15);
        output_text(150, 475, *(name_of_algos+sort_count),GLUT_BITMAP_9_BY_15);
}
 else if (sorting == 1)	// while sorting
	{
		glColor3f(1,1,1);

		output_text(10, 500, "Sorting in progress...",GLUT_BITMAP_9_BY_15);

		output_text(10, 480, "Press p to PAUSE",GLUT_BITMAP_9_BY_15);

	}
}

void front()
{
	glColor3f(1,1,1);

	output_text(150+20, 595-100, "****************************************************************",GLUT_BITMAP_9_BY_15);

	output_text(225+20, 565-100, "WELCOME TO ",GLUT_BITMAP_TIMES_ROMAN_24);

	output_text(170+20, 525-100, "SIMULATION OF SORTING ALGORITHMS",GLUT_BITMAP_TIMES_ROMAN_24);

	output_text(225+20, 485-100, "USING OPENGL",GLUT_BITMAP_TIMES_ROMAN_24);

	output_text(150+20, 470-100,"****************************************************************",GLUT_BITMAP_9_BY_15);

    output_text(95+20, 400-100, "We will be visualizing three sorting algorithms: Bubble Sort, Selection Sort, Insertion Sort",GLUT_BITMAP_9_BY_15);




        //Keyboards Shortcuts
    output_text(220+270, 385-20-150, "KEYBOARD CONTROLS",GLUT_BITMAP_9_BY_15);

    output_text(230+270, 370-20-150, "_ _ _ _ _ _ _ _ _ _",GLUT_BITMAP_9_BY_15);

    output_text(220+270, 355-20-150, "Press Space to SORT",GLUT_BITMAP_9_BY_15);

    output_text(220+270, 515-200-20-150, "Press r to RANDOMISE",GLUT_BITMAP_9_BY_15);

    output_text(220+270, 495-200-20-150, "BackSpace to QUIT",GLUT_BITMAP_9_BY_15);

    output_text(220+270, 535-200-20-150, "Press s to Select Algorithm",GLUT_BITMAP_9_BY_15);


    //Developer Details

    output_text(20, 100, "Developed By:",GLUT_BITMAP_9_BY_15);

    output_text(20, 95, "_ _ _ _ _ _ _",GLUT_BITMAP_9_BY_15);

    output_text(20, 75, "Kamal Shrestha",GLUT_BITMAP_9_BY_15);

    output_text(20, 55, "CE(III), Roll No:49",GLUT_BITMAP_9_BY_15);

    output_text(20, 35, "Department of Computer Science and Engineering (DoCSE)",GLUT_BITMAP_9_BY_15);

    output_text(20, 15, "Mini Project Computer Graphics (COMP:342)",GLUT_BITMAP_9_BY_15);




	glColor3f(1.0,0.0,0.0);
	glBegin(GL_QUADS);
		glVertex2f(445,120-80);
		glVertex2f(445,155-80);
		glVertex2f(565,155-80);
		glVertex2f(565,120-80);
	glEnd();

	glColor3f(1.0,1.0,1.0);
	output_text(450, 135-80, "Press Enter to continue.......",GLUT_BITMAP_HELVETICA_18);

	glFlush();
}

void Initialize() {
	int temp1;

	// Reset the array
	for(temp1=0;temp1<MAX;temp1++){
		a[temp1]=rand()%100+1;//MAX-temp1;
	}


	// Reset all values
	i=j=0;
	count_bubble=0;
	pos=0;
	pos2=1;
	pos3=MAX-1;
	bubble_green=MAX-1;


    m=0;
    s_counter=0;
    select_j=1;



	glClearColor( 0, 0, 0, 0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 610,0,680);
}

// Return 1 if not sorted
int notsorted(){
	int q;
	for(q=0;q<MAX-1;q++)
	{
		if(a[q]>a[q+1])
			return 1;
	}
	return 0;
}

// Main function for display
void display()
{
	int x;
	glClear(GL_COLOR_BUFFER_BIT);

	if(k==0)
		front();
	else{

		char text[10];

		screen_display();


		//Displaying the Bars based on values of a[i]
		for(x=0;x<MAX;x++)
		{

			glColor3f(1,1,1);
			glBegin(GL_POLYGON);
				glVertex2f(start_pos_bars+(600/(MAX))*x,25);
				glVertex2f(start_pos_bars+(600/(MAX))*(x+width_bar),25);
				glVertex2f(start_pos_bars+(600/(MAX))*(x+width_bar),25+a[x]*height_bars);
				glVertex2f(start_pos_bars+(600/(MAX))*x,25+a[x]*height_bars);
			glEnd();


			//LABELLING
			int_str(a[x],text);
			glColor3f(1,1,1);
			output_text(start_pos_bars+(600/(MAX))*x, 15, text,GLUT_BITMAP_TIMES_ROMAN_10);
			//char label[10];
			//int_str(x,label);
			//output_text(start_pos_bars+(600/(MAX))*x, 20, label,GLUT_BITMAP_TIMES_ROMAN_10);
		}

        //Coloured Polygons
		if(swapflag)
		{
            glColor3f(1,0,0);
			glBegin(GL_POLYGON);
				glVertex2f(start_pos_bars+(600/(MAX))*pos,25);
				glVertex2f(start_pos_bars+(600/(MAX))*(pos+width_bar),25);
				glVertex2f(start_pos_bars+(600/(MAX))*(pos+width_bar),25+a[pos]*height_bars);
				glVertex2f(start_pos_bars+(600/(MAX))*pos,25+a[pos]*height_bars);
			glEnd();

			glColor3f(0,0,1);
			glBegin(GL_POLYGON);
				glVertex2f(start_pos_bars+(600/(MAX))*pos2,25);
				glVertex2f(start_pos_bars+(600/(MAX))*(pos2+width_bar),25);
				glVertex2f(start_pos_bars+(600/(MAX))*(pos2+width_bar),25+a[pos2]*height_bars);
				glVertex2f(start_pos_bars+(600/(MAX))*pos2,25+a[pos2]*height_bars);
			glEnd();

            glColor3f(0,1,0);
			glBegin(GL_POLYGON);
				glVertex2f(start_pos_bars+(600/(MAX))*pos3,25);
				glVertex2f(start_pos_bars+(600/(MAX))*(pos3+width_bar),25);
				glVertex2f(start_pos_bars+(600/(MAX))*(pos3+width_bar),25+a[pos3]*height_bars);
				glVertex2f(start_pos_bars+(600/(MAX))*pos3,25+a[pos3]*height_bars);
			glEnd();
	}
	glFlush();
 }
}

// Insertion Sort
void insertionsort()
{

pos2=insert_counter;
insert_counter++;

if(insert_counter==MAX-1){insert_counter=0;}

    int temp;
	while(i<MAX)
	{
        if(flag==0){j=i; flag=1;}
		while(j<MAX-1)
		{
			if(a[j]>a[j+1])
			{
			    swapflag=1;
				temp=a[j];
				a[j]=a[j+1];
				a[j+1]=temp;

				goto A;
			}
			pos=j;
			j++;

			if(j==MAX-1){flag=0;}
		}
		i++;
	}
	sorting=0;
	PlaySound(NULL, 0, 0);
	A:

    pos3=j;
    i=j=0;
	printf("");
}
// Selection Sort
void selectionsort()
{

            while(select_j<MAX){
                    pos2=select_j;
                    if(a[s_counter]>a[select_j]){
                            swapflag=1;
                        s_temp=a[select_j];
                        a[select_j]=a[s_counter];
                        a[s_counter]=s_temp;
                        pos3=select_j;

                    }

                select_j++;

                if(select_j==MAX){

                    pos=s_counter+1;
                    s_counter++;
                    select_j=s_counter;
                }


                if(s_counter==MAX){sorting=0;PlaySound(NULL, 0, 0);pos=MAX-1;}
                goto A;
            }

    A:
    printf("");


}

//Bubble Sort
void bubblesort()
{
    int temp;

		while(j<(MAX-1) && count_bubble<MAX-1)
        {

            pos=j;
            pos2=j+1;
            pos3=bubble_green;

            if(a[j]>a[j+1])
                {
                    swapflag=1;
                    temp=a[j];
                    a[j]=a[j+1];
                    a[j+1]=temp;

                }

            j++;
            if(j==(MAX-1)){j=0;count_bubble++;bubble_green--;}
            if(count_bubble==MAX-1){sorting=0;PlaySound(NULL, 0, 0);}



            goto A;
        }
        A:
        printf("");
}
// Timer Function, takes care of sort selection
void makedelay(int)
{
	if(sorting)
	{
		switch(sort_count)
		{
			case 0:		selectionsort();	break;
			case 1:		bubblesort(); break;
			case 2: insertionsort();	break;
		}
	}
	glutPostRedisplay();
	glutTimerFunc(SPEED/MAX,makedelay,1);
}

// Keyboard Function
void keyboard (unsigned char key, int x, int y)
{
	if(key==13)
		k=1;
    if(key==8){k=0;PlaySound(NULL, 0, 0);Initialize();}

	if (k==1 && sorting!=1)
	{
		switch (key)
		{
			case 27	 :	exit (0); // 27 is the ascii code for the ESC key
			case 32 :	sorting = 1;PlaySound("C:/Users/pc/Desktop/sos-morse-code_daniel-simion-[AudioTrimmer.com]-[AudioTrimmer.com] (2).wav", NULL, SND_ASYNC|SND_FILENAME|SND_LOOP);break;
			case 'r' :	Initialize(); break;
			case 's' :	sort_count=(sort_count+1)%No_of_sorting_algos;	break;
		}
	}
	if(k==1 && sorting==1)
		if(key=='p')
        {sorting=0;
PlaySound(NULL, 0, 0);
        }
}

int main(int argc, char *argv[])
{

	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowSize(win_width,win_height);
	glutInitWindowPosition(20,20);
	glutCreateWindow("Sorting Visualization");
	Initialize();
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutTimerFunc(1000,makedelay,1);// Initial glutTimer Function is to Transition between the pages.
	glutMainLoop();
	return 0;
}
