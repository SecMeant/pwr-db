CREATE USER manager IDENTIFIED BY 'classified';
CREATE USER worker IDENTIFIED BY 'classified_2';
GRANT ALL PRIVILEGES ON biuro_podrozy.* TO manager;
flush privileges;
