// Set GPIO pin 4 to output
#include <Python.h>
#include <time.h>

//
//  How to access GPIO registers from C-code on the Raspberry-Pi
//  Example program
//  15-January-2012
//  Dom and Gert
//  Revised: 15-Feb-2013
 
 
// Access from ARM Running Linux
 
#define BCM2708_PERI_BASE        0x3F000000
#define GPIO_BASE                (BCM2708_PERI_BASE + 0x200000) /* GPIO controller */
 
 
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
 
#define PAGE_SIZE (4*1024)
#define BLOCK_SIZE (4*1024)
 
int  mem_fd;
void *gpio_map;
 
// I/O access
volatile unsigned *gpio;
 
 
// GPIO setup macros. Always use INP_GPIO(x) before using OUT_GPIO(x) or SET_GPIO_ALT(x,y)
#define INP_GPIO(g) *(gpio+((g)/10)) &= ~(7<<(((g)%10)*3))
#define OUT_GPIO(g) *(gpio+((g)/10)) |=  (1<<(((g)%10)*3))
#define SET_GPIO_ALT(g,a) *(gpio+(((g)/10))) |= (((a)<=3?(a)+4:(a)==4?3:2)<<(((g)%10)*3))
 
#define GPIO_SET *(gpio+7)  // sets   bits which are 1 ignores bits which are 0
#define GPIO_CLR *(gpio+10) // clears bits which are 1 ignores bits which are 0
 
#define GET_GPIO(g) (*(gpio+13)&(1<<g)) // 0 if LOW, (1<<g) if HIGH
 
#define GPIO_PULL *(gpio+37) // Pull up/pull down
#define GPIO_PULLCLK0 *(gpio+38) // Pull up/pull down clock

//
// Set up a memory regions to access GPIO
//
void setup_io()
{
   /* open /dev/mem */
   if ((mem_fd = open("/dev/mem", O_RDWR|O_SYNC) ) < 0) {
      printf("can't open /dev/mem \n");
      exit(-1);
   }
 
   /* mmap GPIO */
   gpio_map = mmap(
      NULL,             //Any adddress in our space will do
      BLOCK_SIZE,       //Map length
      PROT_READ|PROT_WRITE,// Enable reading & writting to mapped memory
      MAP_SHARED,       //Shared with other processes
      mem_fd,           //File to map
      GPIO_BASE         //Offset to GPIO peripheral
   );
 
   close(mem_fd); //No need to keep mem_fd open after mmap
 
   if (gpio_map == MAP_FAILED) {
      printf("mmap error %d\n", (int)gpio_map);//errno also set!
      exit(-1);
   }
 
   // Always use volatile pointer!
   gpio = (volatile unsigned *)gpio_map;
 
 
} // setup_io

static void send(PyObject* self, PyObject* pList){
	int g;
 
	// Set up gpi pointer for direct register access
	setup_io();
	 
	// Switch GPIO 7..11 to output mode
	 
	/************************************************************************\
	 * You are about to change the GPIO settings of your computer.          *
	 * Mess this up and it will stop working!                               *
	 * It might be a good idea to 'sync' before running this program        *
	 * so at least you still have your code changes written to the SD-card! *
	\************************************************************************/
	 
	// Set GPIO pins 7-11 to output
	for (g=27; g<=27; g++)
	{
		INP_GPIO(g); // must use INP_GPIO before we can use OUT_GPIO
		OUT_GPIO(g);
	}

    //int numLines;       /* how many lines we passed for parsing */
	char * line;		/* pointer to the line as a string */
	
    PyObject * strObj;  /* one string in the list */
	
	 /* Half a second in nano's */
	
	/* get the number of lines passed to us */
	//numLines = PyList_Size(pList);
	//fprintf(stdout, "NUMLINES was: %zd\n", numLines);

    /* should raise an error here. */
    //if (numLines < 0)   return; /* Not a list */

    /* iterate over items of the list, grabbing strings, and parsing
       for numbers */
	int j;//i,j;
    //for (i=0; i<numLines; i++){
        /* grab the string object from the next element of the list */
    strObj = PyList_GetItem(pList, 0); /* Can't fail */
		
	//	fprintf(stdout, "I was: %zd\n", i);
		
        /* make it a string */
    line = PyString_AsString(strObj);
	
	int stringlength;
	stringlength = strlen(line);
		
	//	fprintf(stdout, "STROBJECT REF count was: %zd\n", strObj->ob_refcnt);

    for(j=0; j < stringlength; j++){
        if(line[j] == '1'){
            GPIO_SET = 1<<27;
        }
	//		fprintf(stdout, "LINE was: %s\n", line);
	//		fprintf(stdout, "LINE[J] was: %c\n", line[j]);
        else{
            GPIO_CLR = 1<<27;
        }
			//usleep(1);
			//nanosleep(&delay, NULL);
		int k;
		for(k=0;k<1000;k++){
			asm("nop");
		}
    }
    //}
	fprintf(stdout, "SEGFAULT? was: %zd\n", 0);
	return;
}

static void writetofile(){
	FILE *fp;
	int c;
  
	fp = fopen("file.txt","w");
	while(1)
	{
		fprintf("%zd", GET_GPIO(17));
		//fprintf(fp,"%zd",GET_GPIO(17));
	}
	fclose(fp);
   
	return;
}

static PyObject *readArduino(PyObject *module){
		int g;
 
	// Set up gpi pointer for direct register access
	setup_io();
	 
	// Switch GPIO 7..11 to output mode
	 
	/************************************************************************\
	 * You are about to change the GPIO settings of your computer.          *
	 * Mess this up and it will stop working!                               *
	 * It might be a good idea to 'sync' before running this program        *
	 * so at least you still have your code changes written to the SD-card! *
	\************************************************************************/
	 
	// Set GPIO pins 7-11 to output
	for (g=17; g<=17; g++)
	{
		INP_GPIO(g); // must use INP_GPIO before we can use OUT_GPIO
	}

	PyObject *ret = NULL;
	PyObject *bit = NULL;
	
	writetofile();
	
	//char ch;
	//int output;
	
	//while(1){
	//	ch = getchar();
	//	if(ch=='~'){break;}
	//	bit = PyString_FromFormat("%zd", GET_GPIO(17));
	//	output = PyList_Append(ret,); 
	//	fprintf("PRINT %d", output);
	//}
	
	//assert(! PyErr_Occurred());
    return ret;
}




static PyMethodDef fastgpio_methods[] = {
    {"send"		  , send	   , METH_O		},
	{"readArduino", readArduino, METH_NOARGS},
    {NULL,NULL}
};

void initfastgpio(){
    (void) Py_InitModule("fastgpio",fastgpio_methods);
}