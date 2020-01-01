CREATE USER hiprio IDENTIFIED BY '9d98c79733ca';
GRANT ALL PRIVILEGES ON biuro_podrozy.* TO 'hiprio'@'%';

CREATE USER miprio IDENTIFIED BY '2a282001ee39';
GRANT ALL PRIVILEGES ON biuro_podrozy.* TO 'miprio'@'%';

CREATE USER loprio IDENTIFIED BY '256486a77a3c';
GRANT SELECT ON biuro_podrozy.credentials TO 'loprio'@'%'; 

flush privileges;


