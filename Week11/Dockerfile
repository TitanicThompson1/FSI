FROM handsonsecurity/seed-server:apache-php

ARG WWWDIR=/var/www/fsi

COPY ./index.html ./index_red.html $WWWDIR/
COPY ./fsi_apache_ssl.conf /etc/apache2/sites-available
COPY ./certs/fsi.crt ./certs/fsi.key  /certs/

RUN  chmod 400 /certs/fsi.key \
     && chmod 644 $WWWDIR/index.html \
     && chmod 644 $WWWDIR/index_red.html \
     && a2ensite fsi_apache_ssl   

CMD  tail -f /dev/null
