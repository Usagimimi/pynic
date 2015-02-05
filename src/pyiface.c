#include "pyiface.h"

//TODO Create method to update tx/rx packets/bytes

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
        self->inet_addr = PyString_FromString("");
        if (self->inet_addr == NULL){
            Py_DECREF(self);
            return NULL;
        }
        self->inet6_addr = PyString_FromString("");
        if (self->inet6_addr == NULL){
            Py_DECREF(self);
            return NULL;
        }
        self->hw_addr = PyString_FromString("");
        if (self->hw_addr == NULL){
            Py_DECREF(self);
            return NULL;
        }
        self->broad_addr = PyString_FromString("");
        if (self->broad_addr == NULL){
            Py_DECREF(self);
            return NULL;
        }
        self->inet_mask = PyString_FromString("");
        if (self->inet_mask == NULL){
            Py_DECREF(self);
            return NULL;
        }
        self->inet6_mask = PyString_FromString("");
        if (self->inet6_mask == NULL){
            Py_DECREF(self);
            return NULL;
        }
        self->running = PyBool_FromLong(0);
        if (self->running == NULL){
            Py_DECREF(self);
            return NULL;
        }
        self->updown = PyBool_FromLong(0);
        if (self->updown == NULL){
            Py_DECREF(self);
            return NULL;
        }
        self->flags = 0;
        self->tx_bytes = 0;
        self->rx_bytes = 0;
        self->tx_packets = 0;
        self->rx_packets = 0;
    }

    return (PyObject *)self;
}

static int
Iface_init(Iface *self, PyObject *args, PyObject *kwds){
    PyObject *name=NULL, *inet_addr=NULL, *inet6_addr=NULL, *hw_addr=NULL, 
             *broad_addr=NULL, *inet_mask=NULL, *inet6_mask=NULL, 
             *running=NULL, *updown=NULL, *tmp;

    static char *kwlist[] = {"name", "inet_addr", "inet6_addr", "hw_addr", 
                             "broad_addr", "inet_mask", "inet6_mask", 
                             "running", "updown", "flags", "tx_bytes", 
                             "rx_bytes", "tx_packets", "rx_packets", 
                             NULL};

    if(!PyArg_ParseTupleAndKeywords(args, kwds, "|OOOOOOOiii", kwlist, 
                                     &name, &inet_addr, &inet6_addr, 
                                     &hw_addr, &broad_addr, &inet_mask, 
                                     &inet6_mask, &running, &updown, 
                                     &self->flags, &self->tx_bytes, 
                                     &self->rx_bytes, &self->tx_packets, 
                                     &self->rx_packets))
    {
        return -1;
    }

    if(name){
        tmp = self->name;
        Py_INCREF(name);
        self->name = name;
        Py_XDECREF(tmp);
    }
    
    if(inet_addr){
        tmp = self->inet_addr;
        Py_INCREF(inet_addr);
        self->inet_addr = inet_addr;
        Py_XDECREF(tmp);
    }
    
    if(inet6_addr){
        tmp = self->inet6_addr;
        Py_INCREF(inet6_addr);
        self->inet6_addr = inet6_addr;
        Py_XDECREF(tmp);
    }
    
    if(hw_addr){
        tmp = self->hw_addr;
        Py_INCREF(hw_addr);
        self->hw_addr = hw_addr;
        Py_XDECREF(tmp);
    }
    
    if(broad_addr){
        tmp = self->broad_addr;
        Py_INCREF(broad_addr);
        self->broad_addr = broad_addr;
        Py_XDECREF(tmp);
    }
    
    if(inet_mask){
        tmp = self->inet_mask;
        Py_INCREF(inet_mask);
        self->inet_mask = inet_mask;
        Py_XDECREF(tmp);
    }
    
    if(inet6_mask){
        tmp = self->inet6_mask;
        Py_INCREF(inet6_mask);
        self->inet6_mask = inet6_mask;
        Py_XDECREF(tmp);
    }
    
    if(running){
        tmp = self->running;
        Py_INCREF(running);
        self->running = running;
        Py_XDECREF(tmp);
    }
    
    if(updown){
        tmp = self->updown;
        Py_INCREF(updown);
        self->updown = updown;
        Py_XDECREF(tmp);
    }

    return 0;
}

static PyMemberDef Iface_members[] = {
    {"name", T_OBJECT_EX, offsetof(Iface, name), 
        0, "Interface's name"},
    {"inet_addr", T_OBJECT_EX, offsetof(Iface, inet_addr), 
        0, "Interface's IPv4 address"},
    {"inet6_addr", T_OBJECT_EX, offsetof(Iface, inet6_addr), 
        0, "Interface's IPv6 address"},
    {"hw_addr", T_OBJECT_EX, offsetof(Iface, hw_addr), 
        0, "Interface's MAC address"},
    {"broad_addr", T_OBJECT_EX, offsetof(Iface, broad_addr), 
        0, "Interface's Broadcast address"},
    {"inet_mask", T_OBJECT_EX, offsetof(Iface, inet_mask), 
        0, "Interface's Network Mask v4 address"},
    {"inet6_mask", T_OBJECT_EX, offsetof(Iface, inet6_mask), 
        0, "Interface's Network Mask v6 address"},
    {"running", T_OBJECT_EX, offsetof(Iface, running), 
        0, "Indicates if interface is running or not"},
    {"updown", T_OBJECT_EX, offsetof(Iface, updown), 
        0, "Indicates if interfaces is Up or Down"},
    {"flags", T_INT, offsetof(Iface, flags), 
        0, "Other Interface's flags"},
    {"tx_bytes", T_INT, offsetof(Iface, tx_bytes), 
        0, "Amount of bytes that the interface transmitted"},
    {"rx_bytes", T_INT, offsetof(Iface, rx_bytes), 
        0, "Amount of bytes that the interface received"},
    {"tx_packets", T_INT, offsetof(Iface, tx_packets), 
        0, "Amount of packets that the interface transmitted"},
    {"rx_packets", T_INT, offsetof(Iface, rx_packets), 
        0, "Amount of packets that the interface received"},
    {NULL}  /* Sentinel */
};

static PyMethodDef Iface_methods[] = {
    {"get_interface", (PyCFunction)Iface_get_interface, METH_VARARGS|METH_CLASS,
     "Return a Iface object with all its information."},
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
    Iface *self = (Iface*) Iface_new(&IfaceType, args, kwds);
    
    if (!PyArg_ParseTuple(args, "s", &iface_name))
        return NULL;
    
    get_info_interface(&ifa, iface_name);
    Iface_init(self, args, kwds);
    self->name = PyString_FromString(ifa.name);
    self->inet_addr = PyString_FromString(ifa.inet_addr);
    self->inet6_addr = PyString_FromString(ifa.inet6_addr);
    self->hw_addr = PyString_FromString(ifa.hw_addr);
    self->broad_addr = PyString_FromString(ifa.broad_addr);
    self->inet_mask = PyString_FromString(ifa.inet_mask);
    self->inet6_mask = PyString_FromString(ifa.inet6_mask);
    self->running = PyBool_FromLong(ifa.running);
    self->updown = PyBool_FromLong(ifa.updown);
    self->flags = ifa.flags;
    self->tx_bytes = ifa.tx_bytes;
    self->rx_bytes = ifa.rx_bytes;
    self->rx_packets = ifa.rx_packets;
    self->tx_packets = ifa.tx_packets;

    return self;
 }

//Module Methods
static PyObject *
pyiface_get_interfaces(PyObject *self, PyObject *args)
{
    char **list;
    int len_list;
    int i;
    len_list = get_list_interfaces(&list);
    PyObject *t;
    
    t = PyList_New(0);
    
    for(i=0; i < len_list; i++){
        PyList_Append(t, PyString_FromString(list[i]));
    }
    
    Py_INCREF(t);
    return t;
}

static PyMethodDef module_methods[] = {
    {"get_interfaces",  pyiface_get_interfaces, METH_VARARGS, "List all available Network Interface."},
    {NULL, NULL, 0, NULL}
};

//Init Module
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
