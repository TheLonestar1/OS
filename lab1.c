#!/bin/bash
maskwifi=$(sudo ifconfig en0 | awk '/netmask/{print$4}')
ipwifi=$(ifconfig en0 | awk '/inet 1/{print $2}')
gatewifi=$(route -n get default | awk '/gateway/{print$2}')
speedwifi=$(ifconfig en0 | awk '/media/{print $2}')
macwifi=$(ifconfig en0 | awk '/ether/{print $2}')
maskblu=$(sudo ifconfig en3 | awk '/netmask/{print$4}')
ipblu=$(ifconfig en3 | awk '/inet 1/{print $2}')
gateblu=$(sudo netstat -nr | grep default | awk '/en3/{print$2}')
speedblu=$(ifconfig en3 | awk '/media/{print $2}')
macblu=$(ifconfig en3 | awk '/ether/{print $2}')
echo
while [ -n "$1" ]
do
case "$1" in
-h)
    echo "Author: Yuriev Yuriy,Ilya Karchev,Ilya Pahomov"
    echo "Availible arguments are:"
    echo " -h to read help; (example ./lab1 -h)"
    echo " -l to list all network connections; (example ./lab1 -l)"
    echo " -k to kill network connection; (example ./lab1 -k)"
    echo " -r to revive network connection; (example ./lab1 -r)"
    echo " -sip to set ip (example ./lab1 -sip 192.168.1.43)"
    echo " -sm to set mask (example ./lab1 -sm 255.255.255)"
    echo " -sg to set gateway (example ./lab1 -sg 192.168.1.1)"
;;
-l)
    echo " Network interfaces:"
    echo "    Wi-Fi"
    echo "      MAC address: $macwifi"
    echo "      IP: $ipwifi"
    echo "      Connection speed: $speedwifi"
    echo "      Mask: $maskwifi"
    echo "      Gateway: $gatewifi"
    echo "    Bluetooth tethering"
    echo "      MAC address: $macblu"
    echo "      IP: $ipblu"
    echo "      Connection speed: $speedblu"
    echo "      Mask: $maskblu"
    echo "      Gateway: $gateblu"
;;
-k)
    sudo ifconfig en3 down
    echo "Tethering is disabled"
;;
-r)
    sudo ifconfig en3 up
    echo "Tethering is enabled"
;;
-sip)
    sudo ifconfig en3 $2
    echo "IP changed to $2"
;;
-sm)
        sudo ifconfig en3 $ipblu netmask $2
        echo "Mask changed to $2"
;;
-sg)
        sudo route delete default
        sudo route add default $2
        echo "Gateway changed to $2"
;;
esac
shift
done
