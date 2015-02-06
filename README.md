# pyIface
A Python interface to get Network Interface Cards(NIC) on Linux.

## Installation

    sudo python setup.py install

## Usage

    import pyiface

You can see some examples in examples directory.

## Methods

    get_list_interfaces()                    -   It lists all available interfaces

## Iface class

This class store all necessary information about the interfaces.

### Attributes

    String  name                        -   Interface's name
    String  inet_addr                   -   Interface's IPv4 address
    String  inet6_addr                  -   Interface's IPv6 address
    String  hw_addr                     -   Interface's MAC address
    String  broad_addr                  -   Interface's Broadcast address
    String  inet_mask                   -   Interface's Network Mask v4 address
    String  inet6_mask                  -   Interface's Network Mask v6 address
    Boolean running                     -   Indicates if interface is running or not
    Boolean updown                      -   Indicates if interfaces is Up or Down
    Integer flags                       -   Other Interface's flags
    Integer tx_bytes                    -   Amount of bytes that the interface transmitted
    Integer rx_bytes                    -   Amount of bytes that the interface received
    Integer tx_packets                  -   Amount of packets that the interface transmitted
    Integer rx_packets                  -   Amount of packets that the interface received

### Methods

    update_tx_rx()                      -   Update NIC's TX/RX information (bytes and packets)

### Class Methods

    Iface.get_interface(iface_name)     -   It return an Iface object with all information about it
