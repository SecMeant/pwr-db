CREATE USER 'superuser'@'localhost' IDENTIFIED BY 'alamakota';
GRANT ALL PRIVILEGES ON *.* TO 'superuser'@'localhost';
FLUSH PRIVILEGES;

drop database IF EXISTS biuro_podrozy_test;
create database IF NOT EXISTS biuro_podrozy_test;