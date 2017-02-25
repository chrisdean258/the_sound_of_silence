#!/bin/sh
HOST='whereischris.net'
USER='cdean16'
PASSWD='Chipper528!'
FILE=$1

ftp -n $HOST <<END_SCRIPT
quote USER $USER
quote PASS $PASSWD
put $FILE /public_html/SilentCity/index.html
quit
END_SCRIPT
exit 0

