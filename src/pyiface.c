#include "pyiface.h"

//Iface Object Definition
static void
Iface_dealloc(Iface* self){
    Py_XDECREF(self->name);
    self->ob_type->tp_free((PyObject*)self);
}

static PyObject *
Iface_new(PyTypeObject *type, PyObject *args, PyObject *kwds){
    Iface *self;

    self = (Iface *)type->tp_alloc(type, 0);
    if(self != NULL){
        self->name = PyString_FromString("");
        if (self->name == NULL){
            Py_DECREF(self);
            return NULL;
        }
    }

    return (PyObject *)self;
}

static int
Iface_init(Iface *self, PyObject *args, PyObject *kwds){
    PyObject *name=NULL, *tmp;

    static char *kwlist[] = {"name", NULL};

    if(!PyArg_ParseTupleAndKeywords(args, kwds, "|O", kwlist, 
                                     &name))
        return -1; 

    if(name){
        tmp = self->name;
        Py_INCREF(name);
        self->name = name;
        Py_XDECREF(tmp);
    }

    return 0;
}

static PyMemberDef Iface_members[] = {
    {"name", T_OBJECT_EX, offsetof(Iface, name), 0, "Interface's name"},
    {NULL}  /* Sentinel */
};

static PyMethodDef Iface_methods[] = {
    {"get_interface", (PyCFunction)Iface_get_interface, METH_VARARGS|METH_CLASS,
     "Return the name, combining the first and last name"
    },
    {NULL}  /* Sentinel */
};

static PyTypeObject IfaceType = {
    PyObject_HEAD_INIT(NULL)
    0,                         /*ob_size*/
    "pyiface.Iface",             /*tp_name*/
    sizeof(Iface),             /*tp_basicsize*/
    0,                         /*tp_itemsize*/
    (destructor)Iface_dealloc, /*tp_dealloc*/
    0,                         /*tp_print*/
    0,                         /*tp_getattr*/
    0,                         /*tp_setattr*/
    0,                         /*tp_compare*/
    0,                         /*tp_repr*/
    0,                         /*tp_as_number*/
    0,                         /*tp_as_sequence*/
    0,                         /*tp_as_mapping*/
    0,                         /*tp_hash */
    0,                         /*tp_call*/
    0,                         /*tp_str*/
    0,                         /*tp_getattro*/
    0,                         /*tp_setattro*/
    0,                         /*tp_as_buffer*/
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE, /*tp_flags*/
    "Iface objects",           /* tp_doc */
    0,		               /* tp_traverse */
    0,		               /* tp_clear */
    0,		               /* tp_richcompare */
    0,		               /* tp_weaklistoffset */
    0,		               /* tp_iter */
    0,		               /* tp_iternext */
    Iface_methods,             /* tp_methods */
    Iface_members,             /* tp_members */
    0,                         /* tp_getset */
    0,                         /* tp_base */
    0,                         /* tp_dict */
    0,                         /* tp_descr_get */
    0,                         /* tp_descr_set */
    0,                         /* tp_dictoffset */
    (initproc)Iface_init,      /* tp_init */
    0,                         /* tp_alloc */
    Iface_new,                 /* tp_new */
};

static PyObject * Iface_get_interface(PyObject *cls, PyObject *args, PyObject *kwds){
    const char *iface_name;
    struct iface ifa;
    Iface *v = (Iface*) Iface_new(&IfaceType, args, kwds);
    
    if (!PyArg_ParseTuple(args, "s", &iface_name))
        return NULL;
    
    get_info_interface(&ifa, iface_name);
    //Iface_init(v, args, kwds);
    v->name = PyString_FromString(ifa.name);
    return v;
 }

//Module Methods
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

static PyMethodDef module_methods[] = {
    {"get_interfaces",  pyiface_get_interfaces, METH_VARARGS, "List all available Network Interface."},
    {NULL, NULL, 0, NULL}
};

#ifndef PyMODINIT_FUNC	/* declarations for DLL import/export */
#define PyMODINIT_FUNC void
#endif
PyMODINIT_FUNC
initpyiface(void) 
{
    PyObject* m;

    if (PyType_Ready(&IfaceType) < 0)
        return;

    m = Py_InitModule3("pyiface", module_methods,
                       "Example module that creates an extension type.");

    if (m == NULL)
      return;

    Py_INCREF(&IfaceType);
    PyModule_AddObject(m, "Iface", (PyObject *)&IfaceType);
}
