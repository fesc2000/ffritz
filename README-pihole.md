pi-hole service (experimental)
==============================

This is a snapshot of a pi-hole 5.0 installation.
Currently it is not started automatically with the fritzbox startup.

Installation (one-time)
-----------------------

- Configure buildroot so that it uses a copied installation:

  ffservice config buildroot

  Set BR_USER_COPY so that it points to a storage location where 
  the buildroot environment is copied to. Preferably this is on a
  USB (3.0) HDD!

- Restart buildroot:

	ffservice restart buildroot

- Install pihole into the br environment:

	pihole-install.sh


Startup
-------

Run

	pihole-start.sh

This will

- kill multid (DNS server)
- start pihole-FTP (dnsmasq daemon)
- restart multid without DNS server
- start lighttpd at port 85 (which is the pihole web GUI)

admin password is ffritz


Limitations/TODO
----------------

- No DHCP support for now, i.e. there will be issues with the fritz.box domain ..
- Only http ...
- Password fixed (copy it from another pihole installation to /var/pihole/setupVars ..)





