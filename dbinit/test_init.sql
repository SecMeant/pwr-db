DROP TABLE IF EXISTS tour;
DROP TABLE IF EXISTS credentials;
DROP TABLE IF EXISTS employees;
DROP TABLE IF EXISTS customers;
DROP TABLE IF EXISTS category;
DROP TABLE IF EXISTS offers;
DROP TABLE IF EXISTS annual_income;

CREATE TABLE biuro_podrozy_test.tour (
  Id               int(10) NOT NULL AUTO_INCREMENT,
  Debt             int(10) NOT NULL,
  Insurance        int(1),
  Extra_meals      int(1),
  Finished         int(1) NOT NULL,
  Reserved_tickets int(10) NOT NULL,
  CustomerId       int(10),
  EmployeeId       int(10),
  OfferId          int(10),
  PRIMARY KEY (Id));

CREATE TABLE biuro_podrozy_test.credentials (
  login      varchar(50) NOT NULL,
  pass_hash varchar(64) NOT NULL,
  account_type   INT(1) NOT NULL,
  PRIMARY KEY (login));

CREATE TABLE biuro_podrozy_test.employees (
  Id           int(10) NOT NULL AUTO_INCREMENT,
  Name         varchar(50) NOT NULL,
  Surname      varchar(50) NOT NULL,
  Hire_date    date NOT NULL,
  Salary       int(10) NOT NULL,
  Email        varchar(50) NOT NULL,
  Phone_number varchar(12) NOT NULL,
  PRIMARY KEY (Id));

CREATE TABLE biuro_podrozy_test.customers (
  Id      int(10) NOT NULL AUTO_INCREMENT,
  Pesel   bigint(12) NOT NULL,
  Name    varchar(50) NOT NULL,
  Surname varchar(50) NOT NULL,
  Email   varchar(50) NOT NULL,
  PRIMARY KEY (Id));

CREATE TABLE biuro_podrozy_test.category (
  Id   int(10) NOT NULL AUTO_INCREMENT,
  Name varchar(50) NOT NULL,
  PRIMARY KEY (Id));

CREATE TABLE biuro_podrozy_test.offers (
  Id               int(10) NOT NULL AUTO_INCREMENT,
  Name             varchar(50) NOT NULL,
  Country          varchar(50) CHARACTER SET utf8 COLLATE utf8_polish_ci NOT NULL,
  City             varchar(40) NOT NULL,
  Tickets_count    int(10)     NOT NULL,
  Date_begin       date        NOT NULL,
  Date_end         date        NOT NULL,
  Price            int(10)     NOT NULL,
  CategoryId       int(10)     NOT NULL,
  Insurance_cost   int(10),
  Extra_meals_cost int(10),
  PRIMARY KEY (Id));

CREATE TABLE biuro_podrozy_test.annual_income (
  Id int(10) NOT NULL AUTO_INCREMENT,
  Year int(4) NOT NULL,
  Balance int(13) NOT NULL,
  PRIMARY KEY (Id));

ALTER TABLE biuro_podrozy_test.tour ADD CONSTRAINT FKtour997364 FOREIGN KEY (CustomerId) REFERENCES biuro_podrozy_test.customers (Id);
ALTER TABLE biuro_podrozy_test.tour ADD CONSTRAINT FKtour557083 FOREIGN KEY (EmployeeId) REFERENCES biuro_podrozy_test.employees (Id);
ALTER TABLE biuro_podrozy_test.tour ADD CONSTRAINT FKtour774357 FOREIGN KEY (OfferId) REFERENCES biuro_podrozy_test.offers (Id);
ALTER TABLE biuro_podrozy_test.offers ADD CONSTRAINT FKoffers229222 FOREIGN KEY (CategoryId) REFERENCES biuro_podrozy_test.category (Id);