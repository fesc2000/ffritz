##########################################################################################
## Betriebsstundenzaehler & Watchdog
##########################################################################################
/bin/run_clock -c /dev/tffs -d
echo init-done >/dev/watchdog
#########################################################################
## Damit auch Oops zum Reboot fuehren
#########################################################################
echo 1 > /proc/sys/kernel/panic_on_oops
#########################################################################
## Damit auch OOM zum Panic/Reboot fuehrt
#########################################################################
echo 2 > /proc/sys/vm/panic_on_oom
## spaeter wenn die tests vorbei sind
## rm -f /var/env
#########################################################################
## lade Powerinfo-Tabelle (fuer Energiemonitor)
#########################################################################
if [ -f /lib/modules/pm_info.in ]; then
cat /lib/modules/pm_info.in >/dev/avm_power
fi
#########################################################################
## set printk level to KERN_ERR
#########################################################################
echo "4" > /proc/sysrq-trigger
if test -x /usr/bin/ethnator ; then
/usr/bin/ethnator -d /etc/init.d/linkdown.sh -u etc/init.d/linkup.sh
fi
#########################################################################
## cleanup - if running, stop debug (0 normal, 1 flush buffer)
#########################################################################
if `ps | grep -v grep | grep -q "cat /dev/debug"` ; then
echo Info: have to stop 'cat /dev/debug'.
echo AVMDBG_EOF 1 >/dev/debug
fi;
#########################################################################
## PTEST: warten, bis der laufenende WLAN-Lifetest beendet ist
#########################################################################
if [ -n "$PTEST_WAIT_PID" ] ; then
wait $PTEST_WAIT_PID
fi
#########################################################################
## modulemem: mit 'fork' <set_m_sleep> Minuten warten, bis alle module gestartet sind.
#########################################################################
if [ -x "/bin/set_modulemem" ] ; then
set_m_sleep=$((10*60))
nohup sh -c "echo \"\$0[\$\$]: ++++fork set_modulemen, sleep ${set_m_sleep}++++\" > /dev/console ; sleep ${set_m_sleep}; echo \"\$0[\$\$]: ++++do set_modulemen++++\" > /dev/console; /bin/set_modulemem;" &
fi
#########################################################################
# MOD: Make sure telnetd is started
#########################################################################
/usr/sbin/telnetd -l /sbin/ar7login

#########################################################################
# MOD: Start a SSH daemon (dropbear)
#   - We want to be able to store root password persistently:
#	- Create a copy for /etc/shadow to /nvram/shadow (if not yet done)
#	- Link /etc/shadow to /nvram/shadow
#   - Same for the certificates:
#	- Create /var/media/ftp/.dropbear (if it does not yet exist)
#	- Link /var/tmp/dropbear to /var/media/ftp/.dropbear
#   - Start the daemon. -R will create certificates on demand
#
#   TODO: use box password for root, or add GUI to edit ssh pwd
#   
#########################################################################
if [ -x /usr/local/sbin/dropbear ]; then
    if [ ! -f /nvram/shadow ]; then
	cp /etc/shadow /nvram/shadow
    fi
    rm -f /var/tmp/shadow
    ln -sf /nvram/shadow /var/tmp/shadow

    if [ ! -d /var/media/ftp/.dropbear ]; then
	mkdir /var/media/ftp/.dropbear
	chmod 700 /var/media/ftp/.dropbear
    fi

    rm -rf /var/tmp/dropbear
    ln -sf /var/media/ftp/.dropbear /var/tmp/dropbear

    /usr/local/sbin/dropbear -R
fi

#########################################################################
# MOD: telnetd also on atom core
#########################################################################
/usr/sbin/start_atom_telnetd

#########################################################################
# MOD: call debug.cfg, if present
#########################################################################
. /var/flash/debug.cfg

exit 0
