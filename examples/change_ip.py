#!/usr/bin/python

# Author: Alfredo Miranda
# E-mail: alfredocdmiranda@gmail.com
# Date: 04/24/2015
#
# This is a sample code to pyNIC, which lists NICs on computer and 
# ask a new IPv4 Address to be set. You must have root permission.

import pynic

list_interfaces = pynic.get_list_interfaces()

for pos, i in enumerate(list_interfaces):
    print("{0} - {1}".format(pos, i))

opt = int(input("Choose the interface: "))
iface = pynic.Iface.get_interface(list_interfaces[opt])

new_addr = input("New IPv4  Address: ")
print("Last IPv4: {0}".format(iface.inet_addr))
iface.set_inet_addr(new_addr)
print("New IPv4: {0}".format(iface.inet_addr))
