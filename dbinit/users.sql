create user 'loprio'@'localhost' identified by 'bazydanych19';
grant usage on *.* to 'loprio'@'localhost';
revoke select, alter, create, delete, drop, insert, index, references, update  on table *.* from 'loprio'@'localhost';
grant select, show view  on table `biuro_podrozy`.`credentials` to 'loprio'@'localhost';
flush privileges;

create user 'miprio'@'localhost' identified by 'bazydanych19';
grant usage on *.* to 'miprio'@'localhost';
revoke select, alter, create, delete, drop, insert, index, references, update  on table *.* from 'miprio'@'localhost';
grant all privileges  on table `biuro_podrozy`.`annual_income` to 'miprio'@'localhost';
grant all privileges  on table  `biuro_podrozy`.`category` to 'miprio'@'localhost';
grant all privileges  on table  `biuro_podrozy`.`customers` to 'miprio'@'localhost';
grant all privileges  on table  `biuro_podrozy`.`offers` to 'miprio'@'localhost';
grant all privileges  on table  `biuro_podrozy`.`tour` to 'miprio'@'localhost';
flush privileges;

create user 'hiprio'@'localhost' identified by 'bazydanych19';
grant usage on *.* to 'hiprio'@'localhost';
grant all privileges  on table `biuro_podrozy`.* to 'hiprio'@'localhost';
flush privileges;