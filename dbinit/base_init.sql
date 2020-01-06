drop table if exists tour;
drop table if exists customers;
drop table if exists credentials;
drop table if exists employees;
drop table if exists offers;
drop table if exists annual_income;
drop table if exists category;

create table biuro_podrozy_test.tour (
  id               int(10) not null auto_increment,
  debt             int(10) not null,
  insurance        int(1),
  extra_meals      int(1),
  state         int(1) not null,
  reserved_tickets int(10) not null,
  customerid       int(10),
  employeeid       int(10),
  offerid          int(10),
  primary key (id));

create table biuro_podrozy_test.credentials (
  id           int(10)     not null auto_increment,
  login        varchar(50) not null,
  pass_hash    varchar(64) not null,
  privilege    int(1)      not null,
  employeeid   int(10)     not null,
  unique (employeeid),
  primary key (id));

create table biuro_podrozy_test.employees (
  id           int(10) not null auto_increment,
  name         varchar(50) not null,
  surname      varchar(50) not null,
  hire_date    date not null,
  salary       int(10) not null,
  email        varchar(50) not null,
  phone_number varchar(12) not null,
  primary key (id));

create table biuro_podrozy_test.customers (
  id      int(10) not null auto_increment,
  pesel   bigint(12) not null,
  name    varchar(50) not null,
  surname varchar(50) not null,
  email   varchar(50) not null,
  primary key (id));

create table biuro_podrozy_test.category (
  id   int(10) not null auto_increment,
  name varchar(50) not null,
  primary key (id));

create table biuro_podrozy_test.offers (
  id               int(10) not null auto_increment,
  name             varchar(50) not null,
  country          varchar(50) character set utf8 collate utf8_polish_ci not null,
  city             varchar(40) not null,
  tickets_count    int(10)     not null,
  date_begin       date        not null,
  date_end         date        not null,
  price            int(10)     not null,
  categoryid       int(10)     not null,
  insurance_cost   int(10),
  extra_meals_cost int(10),
  primary key (id));

create table biuro_podrozy_test.annual_income (
  id int(10) not null auto_increment,
  year int(4) not null,
  balance int(13) not null,
  primary key (id));

alter table biuro_podrozy_test.tour add constraint fktour997364 foreign key (customerid) references biuro_podrozy_test.customers (id);
alter table biuro_podrozy_test.tour add constraint fktour557083 foreign key (employeeid) references biuro_podrozy_test.employees (id);
alter table biuro_podrozy_test.tour add constraint fktour774357 foreign key (offerid) references biuro_podrozy_test.offers (id);
alter table biuro_podrozy_test.offers add constraint fkoffers229222 foreign key (categoryid) references biuro_podrozy_test.category (id);
alter table biuro_podrozy_test.credentials
  add constraint fk_credentials_employees foreign key (`employeeid`) references biuro_podrozy_test.employees (`id`);