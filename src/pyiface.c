/*
 * Author:  Alfredo Miranda
 * Email:   alfredocdmiranda@gmail.com
 * Version: 0.1
 */

#include <Python.h>
#include "iface.h"
 
static PyObject *
pyiface_get_interfaces(PyObject *self, PyObject *args)
{
    char **list;
    int i;
    list = get_list_interfaces();
    PyObject *t;
    
    t = PyList_New(0);
    
    for(i=0; i < MAX_IFACE; i++){
        if(list[i] == '\0'){
            break;
        }
        PyList_Append(t, PyString_FromString(list[i]));
    }
    
    Py_INCREF(t);
    return t;
}

static PyMethodDef PyIfaceMethods[] = {
    {"get_interfaces",  pyiface_get_interfaces, METH_VARARGS, "List all available Network Interface."},
    {NULL, NULL, 0, NULL}
};

PyMODINIT_FUNC
initpyiface(void)
{
    (void) Py_InitModule("pyiface", PyIfaceMethods);
}
