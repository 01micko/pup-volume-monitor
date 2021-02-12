This is pup-volume-monitor, a lightweight drive and volume management backend. 

It is this kind of software responsible for displaying drives in file managers
and file open/save dialogs in many linux distributions.

# How to install

To generate configure, etc.. run:

- ./autogen.sh

Install:

- ./configure --prefix=/usr --sysconfdir=/etc
- make && make install

To install PVM to a specific directory, so you can package it:

- make DESTDIR=/path/to/dir install

The build system installs a generic 'service' script in /etc/init.d
that will automatically start it on each boot. Take that into account
if already using the gvfs volume monitor.. it might cause glib/gio errors.

