CREATE USER 'loprio'@'localhost' IDENTIFIED BY 'bazydanych19';
GRANT USAGE ON *.* TO 'loprio'@'localhost';
REVOKE SELECT, ALTER, CREATE, DELETE, DROP, INSERT, INDEX, REFERENCES, UPDATE  ON TABLE *.* FROM 'loprio'@'localhost';
GRANT SELECT, SHOW VIEW  ON TABLE `biuro_podrozy`.`creditionals` TO 'loprio'@'localhost';
FLUSH PRIVILEGES;

CREATE USER 'miprio'@'localhost' IDENTIFIED BY 'bazydanych19';
GRANT USAGE ON *.* TO 'miprio'@'localhost';
REVOKE SELECT, ALTER, CREATE, DELETE, DROP, INSERT, INDEX, REFERENCES, UPDATE  ON TABLE *.* FROM 'miprio'@'localhost';
GRANT ALL PRIVILEGES  ON TABLE `biuro_podrozy`.`annual_income` TO 'miprio'@'localhost';
GRANT ALL PRIVILEGES  ON TABLE  `biuro_podrozy`.`category` TO 'miprio'@'localhost';
GRANT ALL PRIVILEGES  ON TABLE  `biuro_podrozy`.`customers` TO 'miprio'@'localhost';
GRANT ALL PRIVILEGES  ON TABLE  `biuro_podrozy`.`offers` TO 'miprio'@'localhost';
GRANT ALL PRIVILEGES  ON TABLE  `biuro_podrozy`.`tour` TO 'miprio'@'localhost';
FLUSH PRIVILEGES;

CREATE USER 'hiprio'@'localhost' IDENTIFIED BY 'bazydanych19';
GRANT USAGE ON *.* TO 'hiprio'@'localhost';
GRANT ALL PRIVILEGES  ON TABLE `biuro_podrozy`.* TO 'hiprio'@'localhost';
FLUSH PRIVILEGES;