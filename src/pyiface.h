#ifndef PYIFACE_H
#define PYIFACE_H

#include <Python.h>
#include "structmember.h"

#include "iface.h"

typedef struct{
    PyObject_HEAD
    PyObject *name; /* first name */
}Iface;

static void Iface_dealloc(Iface* self);
static int Iface_init(Iface *self, PyObject *args, PyObject *kwds);
static PyObject * Iface_new(PyTypeObject *type, PyObject *args, PyObject *kwds);
static PyObject * Iface_get_interface(PyObject *cls, PyObject *args, PyObject *kwds);

static PyObject * Iface_get_interfaces(Iface* self);

#endif
