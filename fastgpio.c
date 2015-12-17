// Set GPIO pin 4 to output
#include <Python.h>

INP_GPIO(27); // must use INP_GPIO before we can use OUT_GPIO
OUT_GPIO(27);

static void send(PyObject* self, PyObject* args){
    //Liberally copied from http://code.activestate.com/lists/python-list/31841/

    char * tok;         /* delimiter tokens for strtok */
    int cols;           /* number of cols to parse, from the left */

    int numLines;       /* how many lines we passed for parsing */
    char * line;        /* pointer to the line as a string */
    char * token;       /* token parsed by strtok */

    PyObject * listObj; /* the list of strings */
    PyObject * strObj;  /* one string in the list */

    /* the O! parses for a Python object (listObj) checked
       to be of type PyList_Type */
    if (! PyArg_ParseTuple( args, "O!is", &PyList_Type, &listObj, 
               &cols, &tok )) return NULL;

    /* get the number of lines passed to us */
    numLines = PyList_Size(listObj);

    /* should raise an error here. */
    if (numLines < 0)   return NULL; /* Not a list */

    /* iterate over items of the list, grabbing strings, and parsing
       for numbers */
    for (i=0; i<numLines; i++){
        /* grab the string object from the next element of the list */
        strObj = PyList_GetItem(listObj, i); /* Can't fail */

        /* make it a string */
        line = PyString_AsString( strObj );

        for(int j = 0; j < strlen(line); j++){
    //        if(line[j] == '1'){
                GPIO_SET = 1<<27;
    //        }
    //        else if(line[j] == '0'){
                GPIO_CLR = 1<<27;
    //        }
        }
    }
}

static PyMethodDef fastgpio_methods[] = {
    {"send", py_myFunction, METH_VARARGS},
    {NULL}
};

void initmyModule(){
    (void) Py_InitModule("fastgpio",fastgpio_methods);
}