#include <Python.h>

// Function 1: A simple 'hello world' function
static PyObject* helloworld(PyObject* self, PyObject* args)
{
    printf("Hello World\n");
    return Py_None;
}


int Cfib(int n)
{
    if (n < 2)
        return n;
    else
        return Cfib(n-1)+Cfib(n-2);
}
// Our Python binding to our C function
// This will take one and only one non-keyword argument
static PyObject* fib(PyObject* self, PyObject* args)
{
    // instantiate our `n` value
    int n;
    // if our `n` value
    if(!PyArg_ParseTuple(args, "i", &n))
        return NULL;
    // return our computed fib number
    return Py_BuildValue("i", Cfib(n));
}


// Our Module's Function Definition struct
// We require this `NULL` to signal the end of our method
// definition
static PyMethodDef myMethods[] = {
     { "fib", fib, METH_VARARGS, "returns fibonnaci" },
    {
        "helloworld", // name exposed to Python
        helloworld, // C wrapper function
        METH_NOARGS, // received no args (but really just 1)
        "  returns hello world" // documentation
    },
    { NULL, NULL, 0, NULL } //sentinel return 
    
};

// Our Module Definition struct
static struct PyModuleDef myModule = {
    PyModuleDef_HEAD_INIT,
    "myModule",
    "Test Module",
    -1,
    myMethods
};

// Initializes our module using our above struct
PyMODINIT_FUNC PyInit_myModule(void)
{
    return PyModule_Create(&myModule);
}


