#!/bin/bash

#sudo composer install --no-dev --optimize-autoloader
#start services
sudo cp /etc/nginx/sites-available/SP_vaja01 ./nginx_SP_vaja01
sudo service php8.1-fpm start
sudo service mysql start
mysqldump -uschool -pschool school > vaja01.sql
sudo rm /etc/nginx/sites-enabled/SP_vaja01
sudo unlink /etc/nginx/sites-enabled/default
sudo ln -s /etc/nginx/sites-available/SP_vaja01 /etc/nginx/sites-enabled/SP_vaja01
sudo nginx -t && service nginx start
