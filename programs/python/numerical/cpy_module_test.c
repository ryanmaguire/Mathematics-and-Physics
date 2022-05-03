#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION
#include <math.h>
#include <Python.h>
#include <numpy/ndarraytypes.h>
#include <numpy/ufuncobject.h>

// Declare constants used throughout module.
#define FIBO_A -0.6180339887498948482045870
#define FIBO_B  1.6180339887498948482045870
#define FIBO_C  0.7236067977499789696409170
#define FIBO_D  0.2763932022500210303590826
#define RECIP_2_34 17179869184

unsigned mod25a(unsigned x)
{
    /* 25 * (all powers of 2 <= INT_MAX), descending */
    if (x >= 1677721600) x -= 1677721600;
    if (x >=  838860800) x -=  838860800;
    if (x >=  419430400) x -=  419430400;
    if (x >=  209715200) x -=  209715200;
    if (x >=  104857600) x -=  104857600;
    if (x >=   52428800) x -=   52428800;
    if (x >=   26214400) x -=   26214400;
    if (x >=   13107200) x -=   13107200;
    if (x >=    6553600) x -=    6553600;
    if (x >=    3276800) x -=    3276800;
    if (x >=    1638400) x -=    1638400;
    if (x >=     819200) x -=     819200;
    if (x >=     409600) x -=     409600;
    if (x >=     204800) x -=     204800;
    if (x >=     102400) x -=     102400;
    if (x >=      51200) x -=      51200;
    if (x >=      25600) x -=      25600;
    if (x >=      12800) x -=      12800;
    if (x >=       6400) x -=       6400;
    if (x >=       3200) x -=       3200;
    if (x >=       1600) x -=       1600;
    if (x >=        800) x -=        800;
    if (x >=        400) x -=        400;
    if (x >=        200) x -=        200;
    if (x >=        100) x -=        100;
    if (x >=         50) x -=         50;
    if (x >=         25) x -=         25;
    return x;
}

unsigned char mod25(unsigned int n)
{
    unsigned int div25 = ((unsigned long long)n * 2748779069) >> 36;
    return n - div25 * 25;
}

unsigned char mod4(unsigned int n)
{
    unsigned div4 = ((unsigned long long)n * RECIP_2_34) >> 36;
    return n - div4 * 4;
}

unsigned long long _fiba(int n){
    int i = 0;
    unsigned long long fibo;
    long double fibo_a = FIBO_A;
    long double fibo_b = FIBO_B;
    if (n < 2){
        return n;
    }
    else{
        while (i < n){
            fibo_a *= FIBO_A;
            fibo_b *= FIBO_B;
            i += 1;
        }
        fibo_a = fibo_a*FIBO_C + fibo_b*FIBO_D;
        fibo = (unsigned long long)fibo_a;
        if (fibo_a - 0.5 > fibo){
            fibo += 1;
        }
        return fibo;
    }
}

//  Python function for running the _fib C function.
static PyObject* fiba(PyObject* self, PyObject* args)
{
    int n;

    if (!PyArg_ParseTuple(args, "i", &n))
        return NULL;

    return Py_BuildValue("K", _fiba(n));
}

/*  define functions in module */
static PyMethodDef LogitMethods[] =
{
    {
        "fiba",
        fiba,
        METH_VARARGS,
        "Calculate the Fibonacci numbers the fast way."
    },
    {NULL, NULL, 0, NULL}
};

/* The loop definition must precede the PyMODINIT_FUNC. */
static void double_logitprod(char **args, npy_intp *dimensions,
                             npy_intp* steps, void* data)
{
    npy_intp i;
    npy_intp n = dimensions[0];
    char *in1 = args[0];
    char *out1 = args[1];
    npy_intp in1_step = steps[0];
    npy_intp out1_step = steps[1];

    double tmp;

    for (i = 0; i < n; i++) {
        /*BEGIN main ufunc computation*/
        tmp = *(double *)in1;
        *((double *)out1) = log(tmp/(1-tmp));
        /*END main ufunc computation*/

        in1 += in1_step;
        out1 += out1_step;
    }
}

/*This a pointer to the above function*/
PyUFuncGenericFunction funcs[1] = {&double_logitprod};

/* These are the input and return dtypes of logit.*/
static char types[4] = {NPY_DOUBLE, NPY_DOUBLE};
static void *data[1] = {NULL};

#if PY_VERSION_HEX >= 0x03000000
static struct PyModuleDef moduledef = {
    PyModuleDef_HEAD_INIT,
    "__ufuncs",
    NULL,
    -1,
    LogitMethods,
    NULL,
    NULL,
    NULL,
    NULL
};

PyMODINIT_FUNC PyInit___ufuncs(void)
{
    PyObject *m, *logit, *d;
    m = PyModule_Create(&moduledef);
    if (!m) {
        return NULL;
    }

    import_array();
    import_umath();

    logit = PyUFunc_FromFuncAndData(funcs, data, types, 1, 1, 1,
                                    PyUFunc_None, "logit",
                                    "logit_docstring", 0);

    d = PyModule_GetDict(m);

    PyDict_SetItemString(d, "logit", logit);
    Py_DECREF(logit);

    return m;
}
#else
PyMODINIT_FUNC init__funcs(void)
{
    PyObject *m, *logit, *d;


    m = Py_InitModule("__funcs", LogitMethods);
    if (m == NULL) {
        return;
    }

    import_array();
    import_umath();

    logit = PyUFunc_FromFuncAndData(funcs, data, types, 1, 1, 1,
                                    PyUFunc_None, "logit",
                                    "logit_docstring", 0);

    d = PyModule_GetDict(m);

    PyDict_SetItemString(d, "logit", logit);
    Py_DECREF(logit);
}
#endif

