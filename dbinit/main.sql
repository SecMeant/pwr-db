drop database biuro_podrozy;
create database biuro_podrozy
	character set = 'utf8'
	COLLATE = 'utf8_polish_ci';
SET character_set_server = 'utf8';
SET collation_server = 'utf8_polish_ci';

USE biuro_podrozy;
SET NAMES utf8;

CREATE TABLE biuro_podrozy.tour (
  Id               int(10) NOT NULL AUTO_INCREMENT, 
  Debt             int(10) NOT NULL, 
  Insurance        int(1),
  Extra_meals      int(1), 
  Finished         int(1) NOT NULL, 
  Reserved_tickets int(10) NOT NULL, 
  CustomerPesel    bigint(12), 
  EmployeeId       int(10), 
  OfferId          int(10), 
  PRIMARY KEY (Id));

CREATE TABLE biuro_podrozy.creditionals (
  login      varchar(50) NOT NULL,
  pass_hash varchar(64) NOT NULL,
  account_type   INT(1) NOT NULL,
  PRIMARY KEY (login));

CREATE TABLE biuro_podrozy.employees (
  Id           int(10) NOT NULL AUTO_INCREMENT, 
  Name         varchar(50) NOT NULL, 
  Surname      varchar(50) NOT NULL, 
  Hire_date    date NOT NULL, 
  Salary       int(10) NOT NULL, 
  Email        varchar(50) NOT NULL, 
  Phone_number varchar(12) NOT NULL, 
  PRIMARY KEY (Id));

CREATE TABLE biuro_podrozy.customers (
  Pesel   bigint(12) NOT NULL, 
  Name    varchar(50) NOT NULL, 
  Surname varchar(50) NOT NULL, 
  Email   varchar(50) NOT NULL, 
  PRIMARY KEY (Pesel));

CREATE TABLE biuro_podrozy.category (
  Id   int(10) NOT NULL AUTO_INCREMENT, 
  Name varchar(50) NOT NULL, 
  PRIMARY KEY (Id));

CREATE TABLE biuro_podrozy.offers (
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

CREATE TABLE biuro_podrozy.annual_income (
  Id int(10) NOT NULL AUTO_INCREMENT, 
  Year int(4) NOT NULL, 
  Balance int(13) NOT NULL, 
  PRIMARY KEY (Id));

ALTER TABLE biuro_podrozy.tour ADD CONSTRAINT FKtour997364 FOREIGN KEY (CustomerPesel) REFERENCES biuro_podrozy.customers (Pesel);
ALTER TABLE biuro_podrozy.tour ADD CONSTRAINT FKtour557083 FOREIGN KEY (EmployeeId) REFERENCES biuro_podrozy.employees (Id);
ALTER TABLE biuro_podrozy.tour ADD CONSTRAINT FKtour774357 FOREIGN KEY (OfferId) REFERENCES biuro_podrozy.offers (Id);
ALTER TABLE biuro_podrozy.offers ADD CONSTRAINT FKoffers229222 FOREIGN KEY (CategoryId) REFERENCES biuro_podrozy.category (Id);

INSERT INTO
biuro_podrozy.category 
  (NAME) 
VALUES 
  ('Last minute'),
  ('Sightseeing tour'),
  ('Cruise'),
  ('Facultative trips');

INSERT INTO
biuro_podrozy.creditionals  
  (LOGIN,  PASS_HASH,  ACCOUNT_TYPE) 
VALUES 
  ("mamanger_1", '5FD924625F6AB16A19CC9807C7C506AE1813490E4BA675F843D5A10E0BAACDB8',1),
  ("employee_1", 'A63AB36162A4F4EE6622CCD787B0A048C26B93ACFC05C6B1843659B253C3C00B',0),
  ("employee_2", 'C1B5F0EAC826B829526F13B182808F34515826D4F1F2F9DB4173568718A995E1',0),
  ("employee_3", 'F64AEEF4AE2075114506128EE0E944353022AD959F3E69E5738D13DC560E351B',0);


INSERT INTO biuro_podrozy.annual_income 
  (YEAR,BALANCE) 
VALUES 
  ( STR_TO_DATE('1978', '%Y'),  -5675),
  ( STR_TO_DATE('1979', '%Y'),  -7952),
  ( STR_TO_DATE('1980', '%Y'),  -3478),
  ( STR_TO_DATE('1981', '%Y'),  -2547),
  ( STR_TO_DATE('1982', '%Y'),  350),
  ( STR_TO_DATE('1983', '%Y'),  12457),
  ( STR_TO_DATE('1984', '%Y'),  65254),
  ( STR_TO_DATE('1985', '%Y'),  95789),
  ( STR_TO_DATE('1986', '%Y'),  125900),
  (  STR_TO_DATE('1987', '%Y'),  96376),
  (  STR_TO_DATE('1988', '%Y'),  134924),
  (  STR_TO_DATE('1989', '%Y'),  129829),
  (  STR_TO_DATE('1990', '%Y'),  105551),
  (  STR_TO_DATE('1991', '%Y'),  138482),
  (  STR_TO_DATE('1992', '%Y'),  118980),
  (  STR_TO_DATE('1993', '%Y'),  96416),
  (  STR_TO_DATE('1994', '%Y'),  82463),
  (  STR_TO_DATE('1995', '%Y'),  118606),
  (  STR_TO_DATE('1996', '%Y'),  81183),
  (  STR_TO_DATE('1997', '%Y'),  130009),
  (  STR_TO_DATE('1998', '%Y'),  97520),
  (  STR_TO_DATE('1999', '%Y'),  99880),
  (  STR_TO_DATE('2000', '%Y'),  95796),
  (  STR_TO_DATE('2001', '%Y'),  111848),
  (  STR_TO_DATE('2002', '%Y'),  111733),
  (  STR_TO_DATE('2003', '%Y'),  91428),
  (  STR_TO_DATE('2004', '%Y'),  116649),
  (  STR_TO_DATE('2005', '%Y'),  92682),
  (  STR_TO_DATE('2006', '%Y'),  115525),
  (  STR_TO_DATE('2007', '%Y'),  139747),
  (  STR_TO_DATE('2008', '%Y'),  91046),
  (  STR_TO_DATE('2009', '%Y'),  88344),
  (  STR_TO_DATE('2010', '%Y'),  85589),
  (  STR_TO_DATE('2011', '%Y'),  87658),
  (  STR_TO_DATE('2012', '%Y'),  123593),
  (  STR_TO_DATE('2013', '%Y'),  109855),
  (  STR_TO_DATE('2014', '%Y'),  124706),
  (  STR_TO_DATE('2015', '%Y'),  138409),
  (  STR_TO_DATE('2016', '%Y'),  95149),
  (  STR_TO_DATE('2017', '%Y'),  105841),
  (  STR_TO_DATE('2018', '%Y'),  102893),
  (  STR_TO_DATE('2019', '%Y'),  0);


INSERT INTO biuro_podrozy.employees 
  (NAME,SURNAME, HIRE_DATE, SALARY,EMAIL,PHONE_NUMBER) 
  VALUES
('Gerhardine','Loghan',STR_TO_DATE('30.07.09','%d.%m.%y'),4156,'gloghan0@china.com.cn','765-578-4612'),
('Aubree','Sturr',STR_TO_DATE('12.06.19','%d.%m.%y'),3598,'asturr1@linkedin.com','249-754-0474'),
('Faustina','Glusby',STR_TO_DATE('01.05.15','%d.%m.%y'),2072,'fglusby2@acquirethisname.com','369-671-0886'),
('Dorelle','Ong',STR_TO_DATE('08.03.09','%d.%m.%y'),3937,'dong3@myspace.com','166-542-3734'),
('Brok','Segebrecht',STR_TO_DATE('09.02.19','%d.%m.%y'),4033,'bsegebrecht4@dion.ne.jp','770-888-4001'),
('Nikolas','Twigg',STR_TO_DATE('09.01.19','%d.%m.%y'),2623,'ntwigg5@ask.com','765-515-7208'),
('Lil','Abbate',STR_TO_DATE('17.07.03','%d.%m.%y'),3668,'labbate6@theguardian.com','821-543-1231'),
('Benita','Mallan',STR_TO_DATE('13.09.12','%d.%m.%y'),3213,'bmallan7@moonfruit.com','185-925-0579'),
('Shawna','McGarry',STR_TO_DATE('25.05.11','%d.%m.%y'),4563,'smcgarry8@naver.com','114-376-7016'),
('Martha','Schulz',STR_TO_DATE('20.08.08','%d.%m.%y'),4591,'mschulz9@wisc.edu','685-622-3523'),
('Rurik','Demelt',STR_TO_DATE('04.05.17','%d.%m.%y'),3818,'rdemelta@issuu.com','121-911-7876'),
('Marianne','Ambrosoni',STR_TO_DATE('09.07.17','%d.%m.%y'),4205,'mambrosonib@paginegialle.it','761-511-5349'),
('Bonita','Hubber',STR_TO_DATE('01.08.05','%d.%m.%y'),2188,'bhubberc@goodreads.com','239-597-0796'),
('Tara','Delves',STR_TO_DATE('28.07.14','%d.%m.%y'),2631,'tdelvesd@apple.com','654-487-8278'),
('Quent','Marke',STR_TO_DATE('20.10.19','%d.%m.%y'),2274,'qmarkee@tripadvisor.com','409-493-8714'),
('Loralie','Matic',STR_TO_DATE('10.01.12','%d.%m.%y'),3804,'lmaticf@cam.ac.uk','413-644-1319'),
('Monty','Chipps',STR_TO_DATE('11.07.05','%d.%m.%y'),4153,'mchippsg@theguardian.com','733-610-6835'),
('Jeanie','Ringham',STR_TO_DATE('16.04.03','%d.%m.%y'),4392,'jringhamh@tuttocitta.it','664-215-4663'),
('Vera','Escott',STR_TO_DATE('10.10.06','%d.%m.%y'),4075,'vescotti@alibaba.com','575-157-6374'),
('Boonie','Passo',STR_TO_DATE('14.04.06','%d.%m.%y'),2583,'bpassoj@cafepress.com','747-255-8859'),
('Constantina','Barten',STR_TO_DATE('13.01.17','%d.%m.%y'),2675,'cbartenk@dyndns.org','725-646-7503'),
('Sig','Dunbobin',STR_TO_DATE('21.05.17','%d.%m.%y'),3190,'sdunbobinl@zdnet.com','388-108-6413'),
('Cash','Guerner',STR_TO_DATE('24.01.06','%d.%m.%y'),4776,'cguernerm@hud.gov','409-329-8491'),
('Justina','Filipiak',STR_TO_DATE('11.11.10','%d.%m.%y'),4315,'jfilipiakn@pinterest.com','989-345-9952'),
('Marilee','Dunan',STR_TO_DATE('20.01.06','%d.%m.%y'),2643,'mdunano@squidoo.com','859-443-0772'),
('Maridel','Linge',STR_TO_DATE('21.05.18','%d.%m.%y'),4171,'mlingep@rediff.com','868-139-6890'),
('Flss','Doughtery',STR_TO_DATE('14.02.03','%d.%m.%y'),2125,'fdoughteryq@gov.uk','121-825-9778'),
('Cicely','Oliphant',STR_TO_DATE('12.08.06','%d.%m.%y'),2655,'coliphantr@mit.edu','222-958-7074'),
('Urbain','Tantum',STR_TO_DATE('27.07.08','%d.%m.%y'),2443,'utantums@arizona.edu','794-637-0104'),
('Joice','Crocroft',STR_TO_DATE('09.04.09','%d.%m.%y'),3468,'jcrocroftt@sciencedaily.com','283-199-4958'),
('Roseann','Bryning',STR_TO_DATE('05.11.13','%d.%m.%y'),3272,'rbryningu@indiatimes.com','750-819-7384'),
('Peterus','Wheatland',STR_TO_DATE('31.03.16','%d.%m.%y'),3739,'pwheatlandv@sina.com.cn','711-518-3187'),
('Aldo','Vincent',STR_TO_DATE('06.11.07','%d.%m.%y'),2692,'avincentw@bbb.org','759-389-0456'),
('Dion','Tomkinson',STR_TO_DATE('06.03.14','%d.%m.%y'),2997,'dtomkinsonx@miitbeian.gov.cn','366-846-6977'),
('Julina','Cathenod',STR_TO_DATE('30.03.15','%d.%m.%y'),2568,'jcathenody@sakura.ne.jp','136-288-7007'),
('Glennie','Lashford',STR_TO_DATE('06.01.07','%d.%m.%y'),2863,'glashfordz@prnewswire.com','721-270-4709'),
('Fransisco','Aleksic',STR_TO_DATE('23.09.06','%d.%m.%y'),3924,'faleksic10@google.ru','159-432-1825'),
('Giraud','Pulsford',STR_TO_DATE('12.08.19','%d.%m.%y'),4807,'gpulsford11@cpanel.net','142-406-3823'),
('Willard','Clear',STR_TO_DATE('26.10.03','%d.%m.%y'),4817,'wclear12@japanpost.jp','731-169-2731'),
('Ewen','Beevors',STR_TO_DATE('05.08.15','%d.%m.%y'),4608,'ebeevors13@spotify.com','763-312-0866'),
('Ezekiel','Jacks',STR_TO_DATE('22.07.07','%d.%m.%y'),3310,'ejacks14@toplist.cz','211-153-5185'),
('Zacharie','Minelli',STR_TO_DATE('05.03.06','%d.%m.%y'),4735,'zminelli15@alibaba.com','161-682-0722'),
('Heddie','Bruna',STR_TO_DATE('11.11.19','%d.%m.%y'),2580,'hbruna16@bizjournals.com','559-177-5410'),
('Regine','Heritege',STR_TO_DATE('25.07.18','%d.%m.%y'),3512,'rheritege17@pen.io','837-755-0897'),
('Etty','Figurski',STR_TO_DATE('03.09.11','%d.%m.%y'),3320,'efigurski18@reference.com','465-671-3174'),
('Sanders','Spellar',STR_TO_DATE('29.09.15','%d.%m.%y'),4258,'sspellar19@eventbrite.com','437-551-3838'),
('Sharon','Cockle',STR_TO_DATE('16.02.14','%d.%m.%y'),4196,'scockle1a@berkeley.edu','783-739-7551'),
('Carlo','Legges',STR_TO_DATE('01.06.19','%d.%m.%y'),4570,'clegges1b@admin.ch','329-400-1414'),
('Raina','Deinhard',STR_TO_DATE('20.04.10','%d.%m.%y'),2004,'rdeinhard1c@dedecms.com','522-620-5448'),
('Cass','Pennick',STR_TO_DATE('30.12.11','%d.%m.%y'),2110,'cpennick1d@boston.com','586-581-5361'),
('Sidnee','Vallow',STR_TO_DATE('19.07.13','%d.%m.%y'),3742,'svallow1e@exblog.jp','798-914-8430'),
('Claudetta','Oland',STR_TO_DATE('05.05.05','%d.%m.%y'),3406,'coland1f@census.gov','320-456-8633'),
('Antoni','Oxley',STR_TO_DATE('11.05.08','%d.%m.%y'),3209,'aoxley1g@intel.com','578-251-2599'),
('Cristine','Barmadier',STR_TO_DATE('29.05.16','%d.%m.%y'),4434,'cbarmadier1h@opera.com','623-602-3858'),
('Erek','Jirus',STR_TO_DATE('01.08.04','%d.%m.%y'),4042,'ejirus1i@qq.com','858-542-7889'),
('Willetta','Hukins',STR_TO_DATE('29.09.18','%d.%m.%y'),4640,'whukins1j@360.cn','775-436-6035'),
('Vinni','Battista',STR_TO_DATE('31.03.05','%d.%m.%y'),4775,'vbattista1k@epa.gov','875-104-6715'),
('Elnora','Blooman',STR_TO_DATE('06.04.19','%d.%m.%y'),3893,'eblooman1l@marketwatch.com','107-745-1287'),
('Etheline','Emig',STR_TO_DATE('12.01.05','%d.%m.%y'),2089,'eemig1m@nationalgeographic.com','911-265-6821'),
('Avigdor','Gouthier',STR_TO_DATE('21.07.11','%d.%m.%y'),3552,'agouthier1n@cloudflare.com','187-395-1855'),
('Fredra','Bonnar',STR_TO_DATE('08.01.13','%d.%m.%y'),2026,'fbonnar1o@ihg.com','140-856-3098'),
('Ansel','Davison',STR_TO_DATE('14.04.15','%d.%m.%y'),2631,'adavison1p@imageshack.us','261-924-1705'),
('Jasun','Madge',STR_TO_DATE('03.04.19','%d.%m.%y'),4366,'jmadge1q@census.gov','259-377-3203'),
('Rutter','Thorsby',STR_TO_DATE('02.10.18','%d.%m.%y'),3214,'rthorsby1r@wix.com','983-843-5198'),
('Willyt','Rowland',STR_TO_DATE('27.03.16','%d.%m.%y'),2495,'wrowland1s@accuweather.com','210-163-9653'),
('Ynes','Addington',STR_TO_DATE('30.08.08','%d.%m.%y'),4773,'yaddington1t@hc360.com','837-131-6377'),
('Franzen','Mullenger',STR_TO_DATE('09.06.10','%d.%m.%y'),4434,'fmullenger1u@sakura.ne.jp','548-299-7084'),
('Thibaud','Biscomb',STR_TO_DATE('22.02.04','%d.%m.%y'),4612,'tbiscomb1v@miitbeian.gov.cn','454-287-4246'),
('Meredeth','Sumpton',STR_TO_DATE('01.12.06','%d.%m.%y'),4824,'msumpton1w@bizjournals.com','189-231-1629'),
('Yuma','Lavin',STR_TO_DATE('25.09.10','%d.%m.%y'),3468,'ylavin1x@instagram.com','740-107-9058'),
('Kynthia','Ropartz',STR_TO_DATE('06.02.11','%d.%m.%y'),3825,'kropartz1y@issuu.com','208-921-1717'),
('Pierce','Percy',STR_TO_DATE('02.05.03','%d.%m.%y'),4099,'ppercy1z@wikispaces.com','657-200-8810'),
('Germaine','Fedorski',STR_TO_DATE('21.02.06','%d.%m.%y'),3850,'gfedorski20@angelfire.com','625-222-7704'),
('Ezechiel','McCullouch',STR_TO_DATE('27.04.07','%d.%m.%y'),4657,'emccullouch21@bloomberg.com','120-588-3960'),
('Annabelle','Bowerman',STR_TO_DATE('06.01.09','%d.%m.%y'),3044,'abowerman22@berkeley.edu','470-128-0597'),
('Milly','Hoodlass',STR_TO_DATE('28.08.16','%d.%m.%y'),3684,'mhoodlass23@ning.com','512-890-2292'),
('Rosalind','Kuhnhardt',STR_TO_DATE('14.02.06','%d.%m.%y'),3329,'rkuhnhardt24@dmoz.org','167-783-5678'),
('Carce','Francesc',STR_TO_DATE('27.12.15','%d.%m.%y'),4920,'cfrancesc25@dedecms.com','343-277-5040'),
('Agatha','Ottery',STR_TO_DATE('22.06.16','%d.%m.%y'),4370,'aottery26@howstuffworks.com','411-705-4407'),
('Garrick','Terris',STR_TO_DATE('02.02.06','%d.%m.%y'),3413,'gterris27@mail.ru','785-119-7876'),
('Marj','Bushen',STR_TO_DATE('13.05.15','%d.%m.%y'),3446,'mbushen28@cnn.com','310-287-9319'),
('Tyne','Hansana',STR_TO_DATE('24.01.10','%d.%m.%y'),3801,'thansana29@princeton.edu','122-170-4637'),
('Tiffany','Dods',STR_TO_DATE('19.02.03','%d.%m.%y'),3650,'tdods2a@scientificamerican.com','130-281-6451'),
('Giana','Going',STR_TO_DATE('09.01.13','%d.%m.%y'),4455,'ggoing2b@engadget.com','528-911-5297'),
('Sophia','Dilleston',STR_TO_DATE('21.10.16','%d.%m.%y'),2045,'sdilleston2c@admin.ch','785-759-9052'),
('Magda','Cranson',STR_TO_DATE('08.11.09','%d.%m.%y'),2865,'mcranson2d@weebly.com','834-580-2237'),
('Bartel','Leale',STR_TO_DATE('30.01.08','%d.%m.%y'),4946,'bleale2e@uiuc.edu','350-770-9162'),
('Wiatt','Abella',STR_TO_DATE('17.07.05','%d.%m.%y'),3376,'wabella2f@chronoengine.com','130-789-9513'),
('Monte','Hassewell',STR_TO_DATE('17.02.14','%d.%m.%y'),4115,'mhassewell2g@huffingtonpost.com','164-677-4772'),
('Raviv','Hunt',STR_TO_DATE('25.09.06','%d.%m.%y'),3127,'rhunt2h@gmpg.org','162-608-6145'),
('Sephira','Lovel',STR_TO_DATE('19.06.09','%d.%m.%y'),4870,'slovel2i@goodreads.com','435-452-1786'),
('Daffi','Willingham',STR_TO_DATE('23.11.16','%d.%m.%y'),4665,'dwillingham2j@slate.com','313-820-7613'),
('Jo ann','Cardenas',STR_TO_DATE('22.07.12','%d.%m.%y'),4771,'jcardenas2k@wikia.com','223-662-7057'),
('Ginni','Wayvill',STR_TO_DATE('29.01.08','%d.%m.%y'),4600,'gwayvill2l@europa.eu','946-770-4080'),
('Sheppard','Bernth',STR_TO_DATE('14.07.14','%d.%m.%y'),3839,'sbernth2m@pcworld.com','684-362-1870'),
('Hesther','Stanborough',STR_TO_DATE('31.12.12','%d.%m.%y'),2046,'hstanborough2n@army.mil','916-392-7072'),
('Anne','Spellar',STR_TO_DATE('30.06.13','%d.%m.%y'),4023,'aspellar2o@behance.net','660-953-4237'),
('Mayne','MacCardle',STR_TO_DATE('03.07.07','%d.%m.%y'),4121,'mmaccardle2p@go.com','885-231-9642'),
('Saunder','Leward',STR_TO_DATE('01.08.03','%d.%m.%y'),3352,'sleward2q@usgs.gov','476-555-2648'),
('Libbie','Vines',STR_TO_DATE('27.07.05','%d.%m.%y'),3578,'lvines2r@issuu.com','600-733-4718'),
('Gracie','Prestner',STR_TO_DATE('21.09.19','%d.%m.%y'),4999,'gprestner2s@youtu.be','306-761-2549'),
('Fredek','Monteath',STR_TO_DATE('28.04.11','%d.%m.%y'),2196,'fmonteath2t@spiegel.de','661-620-4314'),
('Frants','Caughan',STR_TO_DATE('12.03.18','%d.%m.%y'),2896,'fcaughan2u@arizona.edu','213-141-2766'),
('Glennis','Gath',STR_TO_DATE('16.08.03','%d.%m.%y'),2050,'ggath2v@free.fr','211-586-8272'),
('Brand','Kuhnwald',STR_TO_DATE('29.07.11','%d.%m.%y'),3757,'bkuhnwald2w@ifeng.com','962-102-8682'),
('Mab','Tuckerman',STR_TO_DATE('15.09.03','%d.%m.%y'),2225,'mtuckerman2x@people.com.cn','552-865-8375'),
('Tobie','Worsell',STR_TO_DATE('01.03.04','%d.%m.%y'),3341,'tworsell2y@dot.gov','717-940-5661'),
('Amby','Prall',STR_TO_DATE('10.05.17','%d.%m.%y'),3770,'aprall2z@buzzfeed.com','577-631-9468'),
('Deonne','Bail',STR_TO_DATE('26.05.06','%d.%m.%y'),4783,'dbail30@rediff.com','336-873-7952'),
('Donny','Burless',STR_TO_DATE('17.05.15','%d.%m.%y'),4537,'dburless31@posterous.com','904-614-8736'),
('Silas','Cordeau]',STR_TO_DATE('07.08.10','%d.%m.%y'),4832,'scordeau32@drupal.org','772-728-8904'),
('Billy','Iskow',STR_TO_DATE('09.04.06','%d.%m.%y'),2661,'biskow33@webnode.com','156-655-3848'),
('Jaymee','Birtley',STR_TO_DATE('24.05.09','%d.%m.%y'),4653,'jbirtley34@qq.com','131-814-3367'),
('Chloris','Rosenthal',STR_TO_DATE('06.02.16','%d.%m.%y'),3575,'crosenthal35@meetup.com','374-569-5752'),
('Prue','Kynd',STR_TO_DATE('26.05.03','%d.%m.%y'),2877,'pkynd36@elegantthemes.com','273-263-4203'),
('Hatty','Ducaen',STR_TO_DATE('30.12.18','%d.%m.%y'),3007,'hducaen37@yellowpages.com','933-135-9280'),
('Ricky','Joule',STR_TO_DATE('11.01.06','%d.%m.%y'),3094,'rjoule38@123-reg.co.uk','756-902-7269'),
('Willette','Allden',STR_TO_DATE('09.09.10','%d.%m.%y'),3856,'wallden39@livejournal.com','298-606-7372'),
('Ede','Ruane',STR_TO_DATE('31.08.07','%d.%m.%y'),3199,'eruane3a@posterous.com','281-552-2027'),
('Jobi','Stockell',STR_TO_DATE('17.04.15','%d.%m.%y'),3009,'jstockell3b@google.ca','920-916-2449'),
('Sallyann','Kaley',STR_TO_DATE('09.03.14','%d.%m.%y'),3704,'skaley3c@sakura.ne.jp','610-493-5781'),
('Bayard','MacGilmartin',STR_TO_DATE('15.01.07','%d.%m.%y'),4030,'bmacgilmartin3d@loc.gov','909-381-0220'),
('Joanne','Littlefair',STR_TO_DATE('26.10.14','%d.%m.%y'),3678,'jlittlefair3e@gizmodo.com','125-748-4008'),
('Parry','Werner',STR_TO_DATE('10.08.12','%d.%m.%y'),3345,'pwerner3f@tumblr.com','523-602-5639'),
('Avigdor','Dohr',STR_TO_DATE('13.12.05','%d.%m.%y'),2889,'adohr3g@feedburner.com','312-252-7918'),
('Meghan','Hanhardt',STR_TO_DATE('20.12.14','%d.%m.%y'),2192,'mhanhardt3h@microsoft.com','315-955-1257'),
('Duffy','Lownie',STR_TO_DATE('26.03.07','%d.%m.%y'),2508,'dlownie3i@godaddy.com','422-735-3998'),
('Osborne','Issacoff',STR_TO_DATE('19.07.07','%d.%m.%y'),3825,'oissacoff3j@sfgate.com','776-522-0261'),
('Rahal','Dewhirst',STR_TO_DATE('09.04.15','%d.%m.%y'),3651,'rdewhirst3k@bravesites.com','143-597-9189'),
('Marylynne','Gentzsch',STR_TO_DATE('03.08.05','%d.%m.%y'),2997,'mgentzsch3l@sitemeter.com','790-341-9184'),
('Raff','Ridgley',STR_TO_DATE('23.10.12','%d.%m.%y'),3011,'rridgley3m@photobucket.com','221-830-9063'),
('Sammy','Labram',STR_TO_DATE('19.03.09','%d.%m.%y'),4517,'slabram3n@ycombinator.com','450-705-8316'),
('Wallache','Thistleton',STR_TO_DATE('22.07.08','%d.%m.%y'),3858,'wthistleton3o@phpbb.com','482-434-1896'),
('Mallorie','Showell',STR_TO_DATE('22.02.10','%d.%m.%y'),4133,'mshowell3p@toplist.cz','580-569-6120'),
('Scottie','Prestland',STR_TO_DATE('03.11.05','%d.%m.%y'),2950,'sprestland3q@123-reg.co.uk','290-468-1062'),
('Cordi','Pickworth',STR_TO_DATE('09.11.10','%d.%m.%y'),3499,'cpickworth3r@theatlantic.com','367-318-4014'),
('Merv','Zavattari',STR_TO_DATE('15.04.03','%d.%m.%y'),2874,'mzavattari3s@chronoengine.com','469-752-1191'),
('Abner','Gaucher',STR_TO_DATE('09.08.13','%d.%m.%y'),4744,'agaucher3t@msu.edu','625-964-1654'),
('Conroy','Dutson',STR_TO_DATE('06.09.15','%d.%m.%y'),3561,'cdutson3u@creativecommons.org','431-929-4448'),
('Timothee','Bastable',STR_TO_DATE('01.04.11','%d.%m.%y'),2350,'tbastable3v@biglobe.ne.jp','375-297-4511'),
('Schuyler','Landman',STR_TO_DATE('16.06.09','%d.%m.%y'),3902,'slandman3w@sakura.ne.jp','692-982-6129'),
('Humberto','Devons',STR_TO_DATE('13.03.08','%d.%m.%y'),4270,'hdevons3x@chronoengine.com','190-300-0030'),
('Caspar','Corriea',STR_TO_DATE('17.02.04','%d.%m.%y'),3620,'ccorriea3y@tripadvisor.com','918-359-5015'),
('Lowell','McDonnell',STR_TO_DATE('15.09.16','%d.%m.%y'),2928,'lmcdonnell3z@trellian.com','321-375-6597'),
('Henrieta','Shirley',STR_TO_DATE('03.07.13','%d.%m.%y'),2470,'hshirley40@weebly.com','995-606-1329'),
('Dene','Foystone',STR_TO_DATE('06.12.09','%d.%m.%y'),3238,'dfoystone41@ed.gov','402-134-2499'),
('Janie','Vanlint',STR_TO_DATE('27.03.06','%d.%m.%y'),3351,'jvanlint42@foxnews.com','619-937-8795'),
('Hatti','Kingdon',STR_TO_DATE('18.11.10','%d.%m.%y'),4305,'hkingdon43@walmart.com','467-663-5017'),
('Agosto','Wolver',STR_TO_DATE('28.09.08','%d.%m.%y'),2888,'awolver44@wufoo.com','584-208-9249') ,
('Delainey','Cloke',STR_TO_DATE('25.08.17','%d.%m.%y'),4342,'dcloke45@microsoft.com','688-270-2546'),
('Ignacius','Hewins',STR_TO_DATE('07.10.11','%d.%m.%y'),3158,'ihewins46@tinyurl.com','712-270-1241'),
('Kirsteni','Gittens',STR_TO_DATE('15.01.17','%d.%m.%y'),4800,'kgittens47@ning.com','361-908-2267'),
('York','Martinet',STR_TO_DATE('13.09.09','%d.%m.%y'),3354,'ymartinet48@liveinternet.ru','275-101-6539'),
('Lothario','Osipenko',STR_TO_DATE('26.11.19','%d.%m.%y'),4702,'losipenko49@nytimes.com','443-462-1248'),
('Jeremy','Northley',STR_TO_DATE('08.12.04','%d.%m.%y'),4151,'jnorthley4a@adobe.com','937-723-5400'),
('Karalee','Winspire',STR_TO_DATE('27.10.11','%d.%m.%y'),2818,'kwinspire4b@mapy.cz','298-144-1876'),
('Delphine','Yesinov',STR_TO_DATE('11.06.16','%d.%m.%y'),4089,'dyesinov4c@free.fr','243-768-4524'),
('Rodney','Darnell',STR_TO_DATE('16.08.05','%d.%m.%y'),2817,'rdarnell4d@google.com.hk','519-698-9991'),
('Leslie','Blaylock',STR_TO_DATE('16.03.08','%d.%m.%y'),3255,'lblaylock4e@biglobe.ne.jp','376-681-1107'),
('Tomasine','Blunsom',STR_TO_DATE('12.11.12','%d.%m.%y'),4775,'tblunsom4f@va.gov','354-117-9754'),
('Trix','Otson',STR_TO_DATE('09.04.08','%d.%m.%y'),4554,'totson4g@oracle.com','591-776-8884'),
('Devin','Tacker',STR_TO_DATE('27.04.15','%d.%m.%y'),3104,'dtacker4h@abc.net.au','642-366-4356'),
('Ree','Verrechia',STR_TO_DATE('18.10.19','%d.%m.%y'),4753,'rverrechia4i@vistaprint.com','519-868-2482'),
('Cynde','Alabaster',STR_TO_DATE('22.08.04','%d.%m.%y'),3735,'calabaster4j@wsj.com','904-740-8031'),
('Benni','MacCurley',STR_TO_DATE('23.09.15','%d.%m.%y'),4167,'bmaccurley4k@ibm.com','317-812-9803'),
('Mattie','Huikerby',STR_TO_DATE('22.05.17','%d.%m.%y'),4900,'mhuikerby4l@dropbox.com','748-991-3646'),
('Carmon','Lowey',STR_TO_DATE('27.10.05','%d.%m.%y'),2530,'clowey4m@is.gd','133-405-4671'),
('Sullivan','Godthaab',STR_TO_DATE('01.10.08','%d.%m.%y'),3667,'sgodthaab4n@deliciousdays.com','975-311-4606'),
('Raye','Patek',STR_TO_DATE('31.12.05','%d.%m.%y'),3112,'rpatek4o@shop-pro.jp','627-657-9173'),
('Hyacinthe','Pulster',STR_TO_DATE('13.03.16','%d.%m.%y'),2864,'hpulster4p@domainmarket.com','778-506-5834'),
('Gallagher','McCorkell',STR_TO_DATE('17.03.03','%d.%m.%y'),4036,'gmccorkell4q@census.gov','921-144-3744'),
('Bettina','Scaife',STR_TO_DATE('28.10.05','%d.%m.%y'),2149,'bscaife4r@squarespace.com','779-935-8804'),
('Broddie','Stean',STR_TO_DATE('11.03.03','%d.%m.%y'),3304,'bstean4s@pbs.org','352-925-2055'),
('Alvera','Brill',STR_TO_DATE('20.02.10','%d.%m.%y'),3799,'abrill4t@blogs.com','394-270-7143'),
('Laney','Dwelley',STR_TO_DATE('06.03.14','%d.%m.%y'),2972,'ldwelley4u@livejournal.com','892-640-0855'),
('Daisie','Kewley',STR_TO_DATE('03.08.13','%d.%m.%y'),2536,'dkewley4v@google.co.uk','572-250-3698'),
('Hildy','Tomaszek',STR_TO_DATE('21.10.04','%d.%m.%y'),2086,'htomaszek4w@bravesites.com','414-416-9334'),
('Cliff','Amos',STR_TO_DATE('09.08.14','%d.%m.%y'),4065,'camos4x@smh.com.au','655-724-1382'),
('Ellissa','Guly',STR_TO_DATE('30.08.16','%d.%m.%y'),3555,'eguly4y@biblegateway.com','479-366-3091'),
('Jourdan','Groundwator',STR_TO_DATE('06.12.12','%d.%m.%y'),3059,'jgroundwator4z@loc.gov','119-292-5355'),
('Emogene','Feldharker',STR_TO_DATE('12.12.03','%d.%m.%y'),4243,'efeldharker50@utexas.edu','127-280-5468'),
('Ulla','Rennebeck',STR_TO_DATE('14.07.11','%d.%m.%y'),3971,'urennebeck51@telegraph.co.uk','747-426-5301'),
('Mable','Airth',STR_TO_DATE('27.03.06','%d.%m.%y'),2488,'mairth52@cpanel.net','910-451-0240'),
('Port','Diviny',STR_TO_DATE('27.12.04','%d.%m.%y'),2892,'pdiviny53@salon.com','685-487-3669'),
('Vivia','McCathy',STR_TO_DATE('21.08.11','%d.%m.%y'),3539,'vmccathy54@narod.ru','536-360-6119'),
('Desiri','Claffey',STR_TO_DATE('02.09.16','%d.%m.%y'),4175,'dclaffey55@clickbank.net','946-562-0616'),
('Frances','Rous',STR_TO_DATE('02.08.07','%d.%m.%y'),2816,'frous56@wordpress.org','251-176-5196'),
('Malvin','Neary',STR_TO_DATE('07.09.18','%d.%m.%y'),2486,'mneary57@google.fr','465-960-7256'),
('Carolyn','Cutmare',STR_TO_DATE('28.08.07','%d.%m.%y'),3183,'ccutmare58@freewebs.com','921-540-7182'),
('Tamarra','Cosbey',STR_TO_DATE('25.11.14','%d.%m.%y'),2630,'tcosbey59@microsoft.com','614-317-5375'),
('Cammy','Fellon',STR_TO_DATE('16.11.19','%d.%m.%y'),3163,'cfellon5a@booking.com','879-641-1921'),
('Elane','Ditt',STR_TO_DATE('24.12.06','%d.%m.%y'),3714,'editt5b@tiny.cc','343-294-6880'),
('Smitty','Polly',STR_TO_DATE('24.02.08','%d.%m.%y'),4975,'spolly5c@indiegogo.com','214-250-0969'),
('Normie','Bracknall',STR_TO_DATE('21.08.10','%d.%m.%y'),3136,'nbracknall5d@archive.org','729-946-7555'),
('Theodosia','Sheilds',STR_TO_DATE('07.07.14','%d.%m.%y'),3336,'tosheilds5e@netvibes.com','300-492-7679'),
('Addie','Scimonelli',STR_TO_DATE('07.05.14','%d.%m.%y'),3383,'ascimonelli5f@mapy.cz','710-172-9069'),
('Garwood','Kielt',STR_TO_DATE('18.05.10','%d.%m.%y'),2407,'gkielt5g@furl.net','820-398-3195'),
('Tabatha','Alyonov',STR_TO_DATE('26.11.06','%d.%m.%y'),3853,'talyonov5h@parallels.com','333-184-2713'),
('Dallas','Trussell',STR_TO_DATE('06.09.09','%d.%m.%y'),2914,'dtrussell5i@cmu.edu','603-804-3688'),
('Rory','Entreis',STR_TO_DATE('01.10.06','%d.%m.%y'),4020,'rentreis5j@nationalgeographic.com','804-907-7189'),
('Niel','Jacobowits',STR_TO_DATE('05.12.17','%d.%m.%y'),3018,'njacobowits5k@un.org','643-974-3826'),
('June','Lambertson',STR_TO_DATE('14.04.04','%d.%m.%y'),2772,'jlambertson5l@liveinternet.ru','306-766-1090'),
('Kylie','Reekie',STR_TO_DATE('20.08.08','%d.%m.%y'),3170,'kreekie5m@wordpress.org','704-166-2789'),
('Arly','Santarelli',STR_TO_DATE('13.01.07','%d.%m.%y'),3253,'asantarelli5n@de.vu','697-447-0523'),
('Camella','Blazeby',STR_TO_DATE('22.04.06','%d.%m.%y'),3302,'cblazeby5o@symantec.com','827-252-4512'),
('Joel','Crookall',STR_TO_DATE('09.02.15','%d.%m.%y'),4860,'jcrookall5p@altervista.org','146-223-0789'),
('Lowe','Robbins',STR_TO_DATE('03.04.11','%d.%m.%y'),2678,'lrobbins5q@ibm.com','991-629-8606'),
('Hyacinthe','Parry',STR_TO_DATE('19.03.11','%d.%m.%y'),4332,'hparry5r@sitemeter.com','101-887-5579'),
('Teirtza','Bohman',STR_TO_DATE('26.06.11','%d.%m.%y'),2498,'tbohman5s@gnu.org','951-804-4591'),
('Cybill','Redborn',STR_TO_DATE('26.03.04','%d.%m.%y'),2722,'credborn5t@technorati.com','131-415-4937'),
('Vinnie','Mates',STR_TO_DATE('03.02.08','%d.%m.%y'),3029,'vmates5u@state.tx.us','164-909-2338'),
('Cathyleen','Cumberledge',STR_TO_DATE('26.09.10','%d.%m.%y'),2165,'ccumberledge5v@technorati.com','665-735-9249'),
('Suellen','Brandli',STR_TO_DATE('22.07.06','%d.%m.%y'),3710,'sbrandli5w@about.com','813-271-6116'),
('Judd','Boor',STR_TO_DATE('02.06.18','%d.%m.%y'),4686,'jboor5x@eepurl.com','209-112-7313'),
('Lorrie','MacKaile',STR_TO_DATE('17.07.16','%d.%m.%y'),2910,'lmackaile5y@ocn.ne.jp','260-715-9819'),
('Augie','Gulk',STR_TO_DATE('12.09.10','%d.%m.%y'),4637,'agulk5z@cmu.edu','125-242-4038'),
('Sorcha','Hallward',STR_TO_DATE('13.12.10','%d.%m.%y'),2855,'shallward60@yellowpages.com','545-437-2690'),
('Gavrielle','Deluze',STR_TO_DATE('16.06.07','%d.%m.%y'),3927,'gdeluze61@twitter.com','583-425-5633'),
('Burnaby','Aldritt',STR_TO_DATE('02.11.03','%d.%m.%y'),2905,'baldritt62@odnoklassniki.ru','577-375-1569'),
('Ernestus','Dempsey',STR_TO_DATE('18.05.17','%d.%m.%y'),2796,'edempsey63@theguardian.com','736-380-4868'),
('Hannah','Almeida',STR_TO_DATE('16.06.03','%d.%m.%y'),2073,'hdalmeida64@multiply.com','647-356-6439'),
('Skipp','Danigel',STR_TO_DATE('31.07.14','%d.%m.%y'),2288,'sdanigel65@nasa.gov','374-279-7943'),
('Briant','Gregr',STR_TO_DATE('13.02.05','%d.%m.%y'),3769,'bgregr66@flavors.me','448-532-0415'),
('Delora','Dayley',STR_TO_DATE('10.03.19','%d.%m.%y'),3197,'ddayley67@domainmarket.com','518-834-8198'),
('Kipp','Otterwell',STR_TO_DATE('08.08.14','%d.%m.%y'),4385,'kotterwell68@photobucket.com','485-951-3559'),
('Rianon','Pigdon',STR_TO_DATE('28.11.08','%d.%m.%y'),3398,'rpigdon69@techcrunch.com','879-270-3876'),
('Mehetabel','Clawley',STR_TO_DATE('31.10.10','%d.%m.%y'),3232,'mclawley6a@icio.us','827-932-1227'),
('Mab','Annand',STR_TO_DATE('15.01.10','%d.%m.%y'),3675,'mannand6b@yandex.ru','799-902-9692'),
('Sutton','Bothen',STR_TO_DATE('27.06.19','%d.%m.%y'),4017,'sbothen6c@webeden.co.uk','204-941-8449'),
('Georgine','Woodyatt',STR_TO_DATE('06.12.17','%d.%m.%y'),4215,'gwoodyatt6d@fda.gov','907-295-2537'),
('Daveta','Drew-Clifton',STR_TO_DATE('30.08.11','%d.%m.%y'),4937,'ddrewclifton6e@google.com.hk','835-952-0943'),
('Arny','Mutimer',STR_TO_DATE('18.06.07','%d.%m.%y'),2150,'amutimer6f@nymag.com','487-797-9108'),
('Barr','Carn',STR_TO_DATE('08.02.17','%d.%m.%y'),2088,'bcarn6g@microsoft.com','658-918-8538'),
('Lucinda','Huntington',STR_TO_DATE('23.08.08','%d.%m.%y'),3910,'lhuntington6h@blogspot.com','704-554-3374'),
('Enrichetta','Fitzroy',STR_TO_DATE('04.08.14','%d.%m.%y'),4880,'efitzroy6i@gravatar.com','599-279-4051'),
('Orelle',' Timony',STR_TO_DATE('29.11.12','%d.%m.%y'),4955,'ootimony6j@sitemeter.com','439-334-3671'),
('Zelig','Braddock',STR_TO_DATE('26.05.05','%d.%m.%y'),2664,'zbraddock6k@creativecommons.org','695-996-9348'),
('Moritz','Heinsius',STR_TO_DATE('12.11.15','%d.%m.%y'),3001,'mheinsius6l@blogtalkradio.com','282-917-0188'),
('Lenna','Marte',STR_TO_DATE('04.03.11','%d.%m.%y'),2503,'lmarte6m@home.pl','126-272-5423'),
('Sidoney','Kimbley',STR_TO_DATE('13.04.14','%d.%m.%y'),3701,'skimbley6n@yale.edu','368-451-4626'),
('Spence','Wardhaugh',STR_TO_DATE('24.03.07','%d.%m.%y'),4697,'swardhaugh6o@sbwire.com','389-620-2921'),
('Griff','Torrisi',STR_TO_DATE('08.01.06','%d.%m.%y'),4095,'gtorrisi6p@merriam-webster.com','733-879-5226'),
('Mada','Papaminas',STR_TO_DATE('26.12.16','%d.%m.%y'),4633,'mpapaminas6q@imageshack.us','312-150-9375'),
('Trudi','Farn',STR_TO_DATE('04.01.08','%d.%m.%y'),3045,'tfarn6r@xrea.com','219-710-9457'),
('Misti','Ranklin',STR_TO_DATE('24.06.12','%d.%m.%y'),2462,'mranklin6s@storify.com','450-569-3261'),
('Janeen','Farland',STR_TO_DATE('02.06.14','%d.%m.%y'),3897,'jfarland6t@trellian.com','738-594-1639'),
('Talya','Challinor',STR_TO_DATE('20.09.10','%d.%m.%y'),4972,'tchallinor6u@prlog.org','501-986-8988'),
('Frankie','Warmisham',STR_TO_DATE('31.05.05','%d.%m.%y'),2507,'fwarmisham6v@cafepress.com','537-835-7567'),
('Erinna','Newlin',STR_TO_DATE('20.01.16','%d.%m.%y'),3571,'enewlin6w@foxnews.com','701-725-6831'),
('Arte','Courvert',STR_TO_DATE('19.06.13','%d.%m.%y'),4476,'acourvert6x@liveinternet.ru','789-102-4232'),
('Drew','Kelso',STR_TO_DATE('26.02.18','%d.%m.%y'),2153,'dkelso6y@pen.io','951-631-6053'),
('Derrek','Halliwell',STR_TO_DATE('20.07.09','%d.%m.%y'),4684,'dhalliwell6z@admin.ch','455-246-5603'),
('Dalila','Rosenwasser',STR_TO_DATE('19.06.07','%d.%m.%y'),3916,'drosenwasser70@wikia.com','588-630-5409'),
('Xerxes','Atton',STR_TO_DATE('21.02.06','%d.%m.%y'),4601,'xatton71@businesswire.com','947-596-9022'),
('Bettina','Birchill',STR_TO_DATE('26.12.06','%d.%m.%y'),3351,'bbirchill72@oracle.com','206-578-8043'),
('Cammy','McFall',STR_TO_DATE('20.07.13','%d.%m.%y'),4011,'cmcfall73@typepad.com','860-370-2463'),
('Caralie','Manwell',STR_TO_DATE('16.03.13','%d.%m.%y'),3540,'cmanwell74@godaddy.com','705-433-0746'),
('Candis','Kennermann',STR_TO_DATE('07.10.09','%d.%m.%y'),3157,'ckennermann75@wikimedia.org','376-144-5098'),
('Amy','Ells',STR_TO_DATE('01.05.07','%d.%m.%y'),4563,'aells76@umich.edu','366-720-4884'),
('Orly','Baguley',STR_TO_DATE('03.11.12','%d.%m.%y'),3931,'obaguley77@huffingtonpost.com','907-866-3301'),
('Maire','Pringle',STR_TO_DATE('22.03.15','%d.%m.%y'),2824,'mpringle78@cloudflare.com','445-411-8478'),
('Edgardo','Thomen',STR_TO_DATE('12.11.19','%d.%m.%y'),4594,'ethomen79@163.com','367-903-9452'),
('Brander','Serle',STR_TO_DATE('24.07.13','%d.%m.%y'),2280,'bserle7a@jimdo.com','879-521-8922'),
('Vaughan','Simnel',STR_TO_DATE('26.03.12','%d.%m.%y'),2068,'vsimnel7b@jalbum.net','630-359-8617'),
('Luca','Joseland',STR_TO_DATE('25.04.03','%d.%m.%y'),4058,'ljoseland7c@sohu.com','251-603-3011'),
('Alvin','Tobias',STR_TO_DATE('02.12.18','%d.%m.%y'),4234,'atobias7d@vistaprint.com','789-193-5138'),
('Dannel','Coopland',STR_TO_DATE('26.02.15','%d.%m.%y'),2295,'dcoopland7e@prlog.org','957-827-6899'),
('Dave','Extal',STR_TO_DATE('22.05.12','%d.%m.%y'),3319,'dextal7f@prnewswire.com','558-385-0339'),
('Pall','Witton',STR_TO_DATE('24.01.10','%d.%m.%y'),2037,'pwitton7g@psu.edu','957-831-2478'),
('Jamison','Yokel',STR_TO_DATE('03.07.13','%d.%m.%y'),3898,'jyokel7h@yellowpages.com','924-511-4641'),
('Dougy','Lardge',STR_TO_DATE('04.02.15','%d.%m.%y'),3425,'dlardge7i@google.it','408-472-6961'),
('Troy','Hacket',STR_TO_DATE('27.03.03','%d.%m.%y'),3133,'thacket7j@reuters.com','613-975-7268'),
('Ladonna','Jeckells',STR_TO_DATE('09.09.08','%d.%m.%y'),3803,'ljeckells7k@netscape.com','755-265-7507'),
('Currey','Eckh',STR_TO_DATE('10.11.08','%d.%m.%y'),2278,'ceckh7l@symantec.com','243-769-0577'),
('Phedra','Archell',STR_TO_DATE('10.07.07','%d.%m.%y'),2515,'parchell7m@hatena.ne.jp','187-808-8577'),
('Leda','Ghioni',STR_TO_DATE('15.04.17','%d.%m.%y'),4771,'lghioni7n@icio.us','851-433-6915'),
('Clarice','Graham',STR_TO_DATE('23.05.17','%d.%m.%y'),4258,'cgraham7o@tripadvisor.com','564-338-1801'),
('Juli','Sheriff',STR_TO_DATE('19.01.05','%d.%m.%y'),4429,'jsheriff7p@usa.gov','298-305-2056'),
('Deeann','Sayburn',STR_TO_DATE('17.05.06','%d.%m.%y'),4509,'dsayburn7q@ucoz.ru','359-524-3554'),
('Meryl','Pickavant',STR_TO_DATE('06.03.17','%d.%m.%y'),2111,'mpickavant7r@multiply.com','342-985-0943'),
('Steve','Bonder',STR_TO_DATE('19.04.09','%d.%m.%y'),4870,'sbonder7s@weather.com','874-767-1075'),
('Cal','Creelman',STR_TO_DATE('14.07.07','%d.%m.%y'),2503,'ccreelman7t@cnn.com','780-100-5024'),
('Marice','Butterley',STR_TO_DATE('03.06.08','%d.%m.%y'),3640,'mbutterley7u@wordpress.org','967-833-6443'),
('Sansone','Alves',STR_TO_DATE('07.02.06','%d.%m.%y'),2939,'salves7v@t.co','897-414-2448'),
('Bartlett','Devonald',STR_TO_DATE('12.12.11','%d.%m.%y'),2685,'bdevonald7w@seattletimes.com','316-141-2668'),
('Cobb','Ivins',STR_TO_DATE('22.02.05','%d.%m.%y'),3929,'civins7x@seattletimes.com','528-508-7562'),
('Marillin','Soppit',STR_TO_DATE('03.04.03','%d.%m.%y'),2702,'msoppit7y@nydailynews.com','266-523-7958'),
('Merilee','Seeger',STR_TO_DATE('28.04.17','%d.%m.%y'),3113,'mseeger7z@amazon.com','388-939-9366'),
('Troy','Hacket',STR_TO_DATE('27.03.03','%d.%m.%y'),3133,'thacket7j@reuters.com','613-975-7268'),
('Ladonna','Jeckells',STR_TO_DATE('09.09.08','%d.%m.%y'),3803,'ljeckells7k@netscape.com','755-265-7507'),
('Currey','Eckh',STR_TO_DATE('10.11.08','%d.%m.%y'),2278,'ceckh7l@symantec.com','243-769-0577'),
('Phedra','Archell',STR_TO_DATE('10.07.07','%d.%m.%y'),2515,'parchell7m@hatena.ne.jp','187-808-8577'),
('Leda','Ghioni',STR_TO_DATE('15.04.17','%d.%m.%y'),4771,'lghioni7n@icio.us','851-433-6915'),
('Clarice','Graham',STR_TO_DATE('23.05.17','%d.%m.%y'),4258,'cgraham7o@tripadvisor.com','564-338-1801'),
('Juli','Sheriff',STR_TO_DATE('19.01.05','%d.%m.%y'),4429,'jsheriff7p@usa.gov','298-305-2056'),
('Deeann','Sayburn',STR_TO_DATE('17.05.06','%d.%m.%y'),4509,'dsayburn7q@ucoz.ru','359-524-3554'),
('Meryl','Pickavant',STR_TO_DATE('06.03.17','%d.%m.%y'),2111,'mpickavant7r@multiply.com','342-985-0943'),
('Steve','Bonder',STR_TO_DATE('19.04.09','%d.%m.%y'),4870,'sbonder7s@weather.com','874-767-1075'),
('Cal','Creelman',STR_TO_DATE('14.07.07','%d.%m.%y'),2503,'ccreelman7t@cnn.com','780-100-5024'),
('Marice','Butterley',STR_TO_DATE('03.06.08','%d.%m.%y'),3640,'mbutterley7u@wordpress.org','967-833-6443');

INSERT INTO biuro_podrozy.customers 
  (PESEL,NAME,SURNAME,EMAIL) 
VALUES 
 (92121963645,'Dannie','Blockey','dblockey0@paginegialle.it'),
 (91102158153,'Philippine','Bosson','pbosson1@cdc.gov'),
 (98050322889,'York','Penwarden','ypenwarden2@360.cn'),
 (95052933721,'Gene','Trouel','gtrouel3@hexun.com'),
 (99022565682,'Martainn','Arman','marman4@posterous.com'),
 (92020595486,'Larry','Winterborne','lwinterborne5@arizona.edu'),
 (90050252168,'Homere','Garlette','hgarlette6@qq.com'),
 (97011076793,'Ardella','Reilly','areilly7@icio.us'),
 (94080542457,'Rudyard','Wackley','rwackley8@mtv.com'),
 (98030772446,'Normand','McKiernan','nmckiernan9@opensource.org'),
 (89101558418,'Lani','Stather','lstathera@nydailynews.com'),
 (89101417784,'Marya','Tissington','mtissingtonb@blog.com'),
 (94030687722,'Tally','Elgram','telgramc@aol.com'),
 (88080188937,'Josi','Bottomer','jbottomerd@youtu.be'),
 (97121452733,'Garwood','Rainsbury','grainsburye@nbcnews.com'),
 (98102239284,'Odey','Alanbrooke','oalanbrookef@state.tx.us'),
 (97062677264,'Bobette','Babalola','bbabalolag@etsy.com'),
 (90010258184,'Monty','Choffin','mchoffinh@zdnet.com'),
 (98011073223,'Mechelle','Redsall','mredsalli@technorati.com'),
 (96030416843,'Margaretta','Revening','mreveningj@nsw.gov.au'),
 (89080529461,'Godiva','Flaverty','goflavertyk@e-recht24.de'),
 (97080435826,'Elene','Storcke','estorckel@yolasite.com'),
 (94050161963,'Mischa','Spearman','mspearmanm@cdc.gov'),
 (94010862686,'Dee','de Courcey','ddecourceyn@tiny.cc'),
 (89122078342,'Roma','Dickens','rdickenso@java.com'),
 (98021051271,'Ermentrude','Benedettini','ebenedettinip@domainmarket.com'),
 (89092288664,'Galvin','Gowler','ggowlerq@bloglines.com'),
 (96110822636,'Deb','MacMenamie','dmacmenamier@scribd.com'),
 (91090545573,'Goldina','Giurio','ggiurios@dailymotion.com'),
 (95021446881,'Miltie','Clair','mclairt@adobe.com'),
 (93062845924,'Gabriel','Van Geffen','gvangeffenu@privacy.gov.au'),
 (92060171444,'Mordecai','Alster','malsterv@wired.com'),
 (95072238873,'Vasilis','Kobisch','vkobischw@scribd.com'),
 (97021033294,'Vita','Malley','vomalleyx@seesaa.net'),
 (89121966686,'Gradey','Baylie','gbayliey@intel.com'),
 (95020152279,'Stormi','Wolton','swoltonz@newsvine.com'),
 (89102474993,'Esmaria','Gerold','egerold10@rakuten.co.jp'),
 (91092712931,'Cheston','Bartolacci','cbartolacci11@house.gov'),
 (94050388922,'Diandra','Bickerstaff','dbickerstaff12@about.com'),
 (94110773815,'Tuckie','Colbert','tcolbert13@nps.gov'),
 (88110752572,'Andria','Pantone','apantone14@huffingtonpost.com'),
 (98081599852,'Georas','Clayworth','gclayworth15@berkeley.edu'),
 (98032861881,'Alwin','Munnings','amunnings16@topsy.com'),
 (93011253936,'Ame','Kramer','akramer17@cbslocal.com'),
 (92122481674,'Hildegaard','South','hsouth18@rediff.com'),
 (92070353698,'Doralia','Ommundsen','dommundsen19@moonfruit.com'),
 (96111617442,'Davin','Smeeton','dsmeeton1a@yandex.ru'),
 (93032626724,'Viv','MacGillacolm','vmacgillacolm1b@stumbleupon.com'),
 (95093018812,'Matthias','Gaudon','mgaudon1c@census.gov'),
 (99051769721,'Dietrich','Prettejohns','dprettejohns1d@howstuffworks.com'),
 (92022381742,'Filippo','Bonsey','fbonsey1e@huffingtonpost.com'),
 (91010366974,'Farand','Degoey','fdegoey1f@bandcamp.com'),
 (93120288294,'Christine','Giordano','cgiordano1g@engadget.com'),
 (90080238994,'Chelsae','Yoell','cyoell1h@vimeo.com'),
 (96010124414,'Gaultiero','Gores','ggores1i@uiuc.edu'),
 (92040717664,'Vannie','Zamorano','vzamorano1j@wikispaces.com'),
 (96053062227,'Krispin','Barck','kbarck1k@naver.com'),
 (90102518817,'Bar','Cheeney','bcheeney1l@cpanel.net'),
 (96111151337,'Hedda','Drewitt','hdrewitt1m@fc2.com'),
 (95052716281,'Guthrie','Arthur','garthur1n@npr.org'),
 (88031717924,'Karla','Flatley','kflatley1o@clickbank.net'),
 (94051299829,'Kissiah','Chasson','kchasson1p@slate.com'),
 (94022889442,'Ernestine','Peacham','epeacham1q@dailymail.co.uk'),
 (89092878335,'Cecil','Swinglehurst','cswinglehurst1r@slate.com'),
 (88101013969,'Bessy','Moneti','bmoneti1s@51.la'),
 (90082565487,'Nikki','Delahunt','ndelahunt1t@soup.io'),
 (96112415988,'Minna','Schuh','mschuh1u@goo.ne.jp'),
 (90041339737,'Magdalena','Haugen','mhaugen1v@sohu.com'),
 (95011284558,'Kippie','Ebbin','kebbin1w@canalblog.com'),
 (89121982398,'Grace','Trill','gtrill1x@usgs.gov'),
 (96110523889,'Shirlee','Crippes','scrippes1y@sciencedaily.com'),
 (99040828213,'Boyce','Osborn','bosborn1z@cloudflare.com'),
 (94080785982,'Ives','Arkill','iarkill20@odnoklassniki.ru'),
 (93082042873,'Jakie','Samsonsen','jsamsonsen21@aol.com'),
 (93010952539,'Lionello','Gynne','lgynne22@bigcartel.com'),
 (96070319577,'Mandel','Baggaley','mbaggaley23@cafepress.com'),
 (96110912388,'Koressa','Kiley','kkiley24@hp.com'),
 (88072715277,'Frederique','Sooley','fsooley25@cnn.com'),
 (94031112911,'Rosmunda','Flips','rflips26@ifeng.com'),
 (91020669542,'Sissy','Geraldo','sgeraldo27@slideshare.net'),
 (91031084343,'Dene','Mullinder','dmullinder28@salon.com'),
 (93100583168,'Gonzales','Well','gwell29@tinypic.com'),
 (97032158377,'Elston','Deble','edeble2a@shinystat.com'),
 (92111724694,'Murray','Cheel','mcheel2b@time.com'),
 (92070832788,'Melly','Wabey','mwabey2c@thetimes.co.uk'),
 (90091663682,'Isa','Yesinov','iyesinov2d@narod.ru'),
 (89022347913,'Sonja','Cullnean','scullnean2e@simplemachines.org'),
 (88092971499,'Claire','Bullingham','cbullingham2f@discuz.net'),
 (96052056632,'Sondra','Bossom','sbossom2g@quantcast.com'),
 (88110573339,'Carlina','Jacson','cjacson2h@prlog.org'),
 (89050866413,'Wiatt','Goodwins','wgoodwins2i@hexun.com'),
 (88062157261,'Deane','Paoletto','dpaoletto2j@networksolutions.com'),
 (92081091123,'Eirena','Attew','eattew2k@webnode.com'),
 (94120276876,'Susie','Bristo','sbristo2l@engadget.com'),
 (98062088515,'Fae','Cleaver','fcleaver2m@yahoo.co.jp'),
 (90092897749,'Scottie','Carek','scarek2n@prlog.org'),
 (95110376817,'Maryrose','Tytherton','mtytherton2o@latimes.com'),
 (97021364769,'Teri','Crooke','tcrooke2p@sitemeter.com'),
 (91102375471,'Steve','De la Perrelle','sdelaperrelle2q@ask.com'),
 (95063061817,'Sayre','Brookwell','sbrookwell2r@1688.com'),
 (98030957579,'Orran','Lulham','olulham2s@skyrock.com'),
 (89071641358,'Raoul','Brasseur','rbrasseur2t@sohu.com'),
 (92022093562,'Stillmann','Ducker','sducker2u@discovery.com'),
 (89120732161,'Pall','Chattell','pchattell2v@vkontakte.ru'),
 (95030526679,'Chaunce','Baus','cbaus2w@flickr.com'),
 (99052792333,'Jason','Just','jjust2x@whitehouse.gov'),
 (98110724321,'Alon','McCamish','amccamish2y@tmall.com'),
 (91120618334,'Marylynne','Smalridge','msmalridge2z@example.com'),
 (89041298274,'Jenifer','Vockings','jvockings30@altervista.org'),
 (97053192916,'Iorgos','Littleton','ilittleton31@comcast.net'),
 (92081442486,'Orran','Titford','otitford32@mapquest.com'),
 (90032457187,'Arlie','Benion','abenion33@arizona.edu'),
 (91042667465,'Emile','Fleg','efleg34@hhs.gov'),
 (98121826511,'Enrica','McDuff','emcduff35@yellowbook.com'),
 (88081381162,'Ninnetta','Grimes','ngrimes36@github.com'),
 (96031978946,'Guthry','Pursglove','gpursglove37@fastcompany.com'),
 (88060613316,'Guillemette','Byng','gbyng38@mit.edu'),
 (97020941749,'Sloane','Hampshaw','shampshaw39@people.com.cn'),
 (98051227824,'Errol','Gredden','egredden3a@mapy.cz'),
 (92041851949,'Billie','Vogeller','bvogeller3b@fotki.com'),
 (89062388491,'Birgit','Swiffin','bswiffin3c@tripadvisor.com'),
 (88040223487,'Annmarie','Gosson','agosson3d@vistaprint.com'),
 (89021882879,'Gardener','Hurdman','ghurdman3e@barnesandnoble.com'),
 (94052984669,'Scotti','Teaser','steaser3f@shareasale.com'),
 (88111569249,'Keely','Sotham','ksotham3g@dedecms.com'),
 (92010846345,'Conrado','Brazer','cbrazer3h@vk.com'),
 (91111734348,'Joshuah','Jakubiak','jjakubiak3i@yahoo.co.jp'),
 (99022882167,'Jake','McAulay','jmcaulay3j@bizjournals.com'),
 (96062519875,'Regine','Hovee','rhovee3k@diigo.com'),
 (95012424577,'Court','Sommer','csommer3l@blogtalkradio.com'),
 (96061026659,'Ericka','Lygoe','elygoe3m@globo.com'),
 (90020698741,'Galina','Amiranda','gamiranda3n@reference.com'),
 (98082688779,'Davida','Merfin','dmerfin3o@tmall.com'),
 (88122752885,'Lennard','Schuchmacher','lschuchmacher3p@mysql.com'),
 (93090724918,'Alie','Gianullo','agianullo3q@ask.com'),
 (97020386812,'Coletta','Crozier','ccrozier3r@flickr.com'),
 (95120239867,'Johnny','Entissle','jentissle3s@forbes.com'),
 (91100289442,'Sonya','Drabble','sdrabble3t@vk.com'),
 (98123132113,'Tibold','McSporon','tmcsporon3u@jigsy.com'),
 (88061119842,'Edie','Stallion','estallion3v@kickstarter.com'),
 (98061914453,'Jacinthe','Bohlens','jbohlens3w@va.gov'),
 (94020757545,'Dulcine','Knoller','dknoller3x@loc.gov'),
 (94071691227,'Karalynn','Maith','kmaith3y@imdb.com'),
 (94060451313,'Kitty','Lesek','klesek3z@geocities.com'),
 (98100163954,'Starla','McAlister','smcalister40@nps.gov'),
 (99012347164,'Berke','Sindle','bsindle41@goodreads.com'),
 (95070125278,'Fanchette','Maylott','fmaylott42@storify.com'),
 (96042843594,'Jilly','Menendez','jmenendez43@nsw.gov.au'),
 (90050328773,'Shayna','Moreman','smoreman44@webs.com'),
 (90040597868,'Daryle','Scarffe','dscarffe45@cdbaby.com'),
 (97092089321,'Raina','Hyde-Chambers','rhydechambers46@canalblog.com'),
 (91040175579,'Rowan','Kiltie','rkiltie47@typepad.com'),
 (97102756834,'Lemar','Kruschov','lkruschov48@mashable.com'),
 (89011339486,'Yvette','Petriello','ypetriello49@usgs.gov'),
 (95010488793,'Alric','Burril','aburril4a@census.gov'),
 (93110112398,'Donnajean','Danilowicz','ddanilowicz4b@zdnet.com'),
 (88072115855,'Abbey','Areles','aareles4c@usatoday.com'),
 (94122342281,'Marielle','Selkirk','mselkirk4d@digg.com'),
 (90060157754,'Maddy','Scardifield','mscardifield4e@tamu.edu'),
 (97021866322,'Paten','Lax','plax4f@t.co'),
 (97082456364,'Paulo','Misken','pmisken4g@paginegialle.it'),
 (96022941665,'Saudra','Roskam','sroskam4h@pagesperso-orange.fr'),
 (93121511548,'Tully','Pendell','tpendell4i@a8.net'),
 (92093038565,'Gibbie','Voysey','gvoysey4j@ucoz.ru'),
 (93092634882,'Trudi','Giacobilio','tgiacobilio4k@hibu.com'),
 (95021767933,'Janie','Dunstall','jdunstall4l@pagesperso-orange.fr'),
 (88060624372,'Kaitlynn','Spendley','kspendley4m@ftc.gov'),
 (89052599788,'Gratiana','Shepcutt','gshepcutt4n@ucla.edu'),
 (92021166441,'Sergio','Bellord','sbellord4o@jigsy.com'),
 (96011875319,'Trisha','Charke','tcharke4p@yahoo.com'),
 (94070241935,'Adria','Bramhill','abramhill4q@tmall.com'),
 (96072535274,'Rollins','Poulsen','rpoulsen4r@1688.com'),
 (92010784539,'Jecho','Barniss','jbarniss4s@yahoo.co.jp'),
 (98120124245,'Armand','Trenouth','atrenouth4t@cargocollective.com'),
 (93081277438,'Heath','Iredale','hiredale4u@ehow.com'),
 (98081173432,'Dorena','Reach','dreach4v@nsw.gov.au'),
 (90070777159,'Wynn','Ibbs','wibbs4w@europa.eu'),
 (93010471478,'Prescott','Bollon','pbollon4x@tuttocitta.it'),
 (95100929786,'Grantham','Lorain','glorain4y@studiopress.com'),
 (92120824648,'Emelen','Garham','egarham4z@ca.gov'),
 (92111374745,'Sean','Taverner','staverner50@nsw.gov.au'),
 (93020953227,'Carolus','Crannach','ccrannach51@discuz.net'),
 (98041819367,'Tabina','Lackmann','tlackmann52@usa.gov'),
 (98031332827,'Teodora','De la Perrelle','tdelaperrelle53@mtv.com'),
 (95062156695,'Marena','Navein','mnavein54@weebly.com'),
 (90021293853,'Hannah','Caulton','hcaulton55@freewebs.com'),
 (90102979333,'Doy','Allabush','dallabush56@furl.net'),
 (93062376967,'Halie','Gridley','hgridley57@google.com.br'),
 (98091694794,'Jess','Evennett','jevennett58@webeden.co.uk'),
 (91042197452,'Kelcy','Lorenzo','klorenzo59@is.gd'),
 (90010893794,'Judie','Bentote','jbentote5a@blogtalkradio.com'),
 (98043099851,'Ellen','Shillan','eshillan5b@example.com'),
 (88010887617,'Harwell','Burcher','hburcher5c@utexas.edu'),
 (98062331927,'Jaquenette','Brownill','jbrownill5d@amazon.co.jp'),
 (92030965127,'Biddie','Durrand','bdurrand5e@whitehouse.gov'),
 (96120763633,'Brandtr','Straffon','bstraffon5f@cbslocal.com'),
 (94101486849,'Elspeth','Nashe','enashe5g@wunderground.com'),
 (94061192413,'Bridgette','Clingoe','bclingoe5h@harvard.edu'),
 (94120487454,'Bertram','Kislingbury','bkislingbury5i@pbs.org'),
 (97013129369,'Teodoro','Ansty','tansty5j@unesco.org'),
 (93082697646,'Deeann','Arnopp','darnopp5k@hibu.com'),
 (92091845693,'Tori','Dauney','tdauney5l@time.com'),
 (97042131856,'Giraud','Crosgrove','gcrosgrove5m@tinyurl.com'),
 (88091996477,'Ive','Rubinsztein','irubinsztein5n@seattletimes.com'),
 (97030623691,'Hamilton','Grigoriev','hgrigoriev5o@multiply.com'),
 (91091447836,'Murry','Frill','mfrill5p@flickr.com'),
 (97071999418,'Milton','Cadman','mcadman5q@xinhuanet.com'),
 (88080287667,'Julita','Catterell','jcatterell5r@dedecms.com'),
 (90052681353,'Arden','Laimable','alaimable5s@ow.ly'),
 (96072213794,'Merlina','Valek','mvalek5t@ocn.ne.jp'),
 (89053086564,'Penny','Neeson','pneeson5u@1688.com'),
 (97030577327,'Mack','Renshaw','mrenshaw5v@mapy.cz'),
 (94122889582,'Rena','McKay','rmckay5w@telegraph.co.uk'),
 (97082064497,'Spike','Syder','ssyder5x@homestead.com'),
 (88121923653,'Sephira','McGilmartin','smcgilmartin5y@sciencedirect.com'),
 (97040214623,'Tillie','Lettice','tlettice5z@gnu.org'),
 (91061125513,'Larisa','Stickney','lstickney60@amazon.co.jp'),
 (91020239712,'Sheffie','Hardaker','shardaker61@technorati.com'),
 (97012838842,'Cris','Brend','cbrend62@bigcartel.com'),
 (97070963339,'Henka','Martinez','hmartinez63@opensource.org'),
 (93081045495,'Gaven','Giblett','ggiblett64@google.com.au'),
 (96060336289,'Derrek','Cosgry','dcosgry65@issuu.com'),
 (96050355863,'Crystal','McGillreich','cmcgillreich66@nhs.uk'),
 (90061736659,'Terri','Yarnall','tyarnall67@squidoo.com'),
 (89052272937,'Shae','Jennison','sjennison68@vkontakte.ru'),
 (89052945862,'Parry','Postans','ppostans69@businesswire.com'),
 (92020668425,'Bill','Lowings','blowings6a@naver.com'),
 (92072886266,'Willie','Ricardin','wricardin6b@fotki.com'),
 (94080824812,'Lennard','Beiderbeck','lbeiderbeck6c@shop-pro.jp'),
 (88123176936,'Henderson','Askell','haskell6d@spiegel.de'),
 (92111587417,'Lia','Goldthorp','lgoldthorp6e@stumbleupon.com'),
 (92090158943,'Osbourne','Chasmoor','ochasmoor6f@163.com'),
 (88092228843,'Luelle','Mandre','lmandre6g@example.com'),
 (97122877717,'Caleb','Redihalgh','credihalgh6h@google.com.au'),
 (89031266654,'Nanine','Mardlin','nmardlin6i@godaddy.com'),
 (97030335336,'Filberto','Foxhall','ffoxhall6j@odnoklassniki.ru'),
 (95020723693,'Kippy','Figin','kfigin6k@photobucket.com'),
 (95010196939,'Clemmie','Enever','cenever6l@icio.us'),
 (89061993638,'Mathe','Campe','mcampe6m@newsvine.com'),
 (94041049683,'Kassie','Smale','ksmale6n@npr.org'),
 (88123136378,'Agnola','Woodwind','awoodwind6o@about.me'),
 (88013066475,'Magdalena','McKeighan','mmckeighan6p@tinypic.com'),
 (96012869395,'Sybil','Lakey','slakey6q@delicious.com'),
 (88080547826,'Alice','Woolard','awoolard6r@acquirethisname.com'),
 (99040684725,'Ilise','Grundle','igrundle6s@hubpages.com'),
 (99050161586,'Cati','Toone','ctoone6t@reuters.com'),
 (94071424232,'Hendrika','Pidon','hpidon6u@google.co.jp'),
 (88082136419,'Inglebert','Ensor','iensor6v@icio.us'),
 (96043086868,'Shawnee','Praill','spraill6w@is.gd'),
 (94112897278,'Simonne','Endricci','sendricci6x@youtu.be'),
 (98060146237,'Terra','Fishwick','tfishwick6y@360.cn'),
 (89110735279,'Waylan','Spaven','wspaven6z@un.org'),
 (98070663878,'Tymon','Jakeman','tjakeman70@senate.gov'),
 (98082039346,'Arvin','Martinolli','amartinolli71@tmall.com'),
 (95062326935,'Early','Elix','eelix72@theatlantic.com'),
 (96111326641,'Tomlin','Pockey','tpockey73@mit.edu'),
 (88032782899,'Marji','Eskriett','meskriett74@people.com.cn'),
 (97101714565,'Giraldo','Ancell','gancell75@bbb.org'),
 (89101181597,'Ferne','Hacquoil','fhacquoil76@multiply.com'),
 (94051131192,'Osborn','Valentine','ovalentine77@fda.gov'),
 (88012244854,'Mateo','Alison','malison78@360.cn'),
 (92101383357,'Abey','Gwyther','agwyther79@quantcast.com'),
 (97041337369,'Page','Marthen','pmarthen7a@elpais.com'),
 (97040189141,'Clim','Babbidge','cbabbidge7b@yale.edu'),
 (89020522857,'Nichole','Godart','ngodart7c@nps.gov'),
 (89051623499,'Morris','Ragot','mragot7d@moonfruit.com'),
 (89102773788,'Marmaduke','Wims','mwims7e@posterous.com'),
 (96082438394,'Tammi','Falconbridge','tfalconbridge7f@mediafire.com'),
 (98021191874,'Otto','Melmeth','omelmeth7g@skype.com'),
 (95010397996,'Sergeant','Ruckledge','sruckledge7h@indiatimes.com'),
 (89110743621,'Albertine','Paddick','apaddick7i@cocolog-nifty.com'),
 (94102058843,'Kipper','Denyagin','kdenyagin7j@t-online.de'),
 (96101799826,'Eric','Feighney','efeighney7k@unicef.org'),
 (94110397664,'Edgar','Peirpoint','epeirpoint7l@oaic.gov.au'),
 (90022897957,'Davidde','Darlaston','ddarlaston7m@blog.com'),
 (93012314894,'Morgan','Sherel','msherel7n@discovery.com'),
 (92072698557,'Marcellina','Clout','mclout7o@umn.edu'),
 (95082589628,'Verena','Reding','vreding7p@dot.gov'),
 (94082851953,'Dill','Davley','ddavley7q@umn.edu'),
 (98063061597,'Packston','Wrixon','pwrixon7r@salon.com'),
 (91030869431,'Huey','Brockington','hbrockington7s@amazon.de'),
 (88052931653,'Sascha','Hatherley','shatherley7t@imageshack.us'),
 (91081024388,'Xymenes','Cowx','xcowx7u@squarespace.com'),
 (95122476943,'Jean','Cartwight','jcartwight7v@discovery.com'),
 (93091313625,'Tyne','Bortoloni','tbortoloni7w@biglobe.ne.jp'),
 (93090614635,'Salaidh','Mozzi','smozzi7x@cnbc.com'),
 (96100493813,'Ulrica','Stoakley','ustoakley7y@ftc.gov'),
 (98052064941,'Marla','Undrell','mundrell7z@ezinearticles.com'),
 (97121395236,'Layla','Darell','ldarell80@bigcartel.com'),
 (93082589211,'Melvin','Durrett','mdurrett81@wsj.com'),
 (94092094144,'Cammy','Kobel','ckobel82@instagram.com'),
 (98121081198,'Kara-lynn','Foulstone','kfoulstone83@forbes.com'),
 (98112873641,'Karena','Lamberto','klamberto84@imgur.com'),
 (96092892838,'Rayshell','Rodliff','rrodliff85@google.com.hk'),
 (94072986441,'Reuben','Orton','rorton86@macromedia.com'),
 (93102742822,'Jordon','Juliano','jjuliano87@sun.com'),
 (91051099435,'Stefan','Plan','splan88@eepurl.com'),
 (90090699329,'Vanny','Hinksen','vhinksen89@amazon.de'),
 (98032532578,'Sunshine','Kapelhoff','skapelhoff8a@ameblo.jp'),
 (88120797419,'Tabby','Tedahl','ttedahl8b@skype.com'),
 (92030474339,'Robbin','Feria','rferia8c@yale.edu'),
 (92020291849,'Matty','Etherington','metherington8d@topsy.com'),
 (96083154622,'Lazarus','Wheway','lwheway8e@jigsy.com'),
 (94051488768,'Bernadine','Lillicrop','blillicrop8f@bloglines.com'),
 (92052927134,'Darb','Vanderson','dvanderson8g@cdc.gov'),
 (92082287747,'Barton','Kenworthy','bkenworthy8h@seesaa.net'),
 (89111833792,'Bev','Symon','bsymon8i@go.com'),
 (89061987844,'Rakel','Keizman','rkeizman8j@example.com'),
 (98051299421,'Anna-maria','Attard','aattard8k@chron.com'),
 (96041567518,'Laina','Deuss','ldeuss8l@parallels.com'),
 (96110386626,'Latrena','Billett','lbillett8m@go.com'),
 (92052114958,'Ronni','Benyon','rbenyon8n@hhs.gov'),
 (94062794454,'Sonni','Gilloran','sgilloran8o@wikispaces.com'),
 (92101448227,'Jermayne','Holleran','jholleran8p@biglobe.ne.jp'),
 (89042637838,'Nikolaos','Croix','ncroix8q@psu.edu'),
 (99032767467,'Brena','Piser','bpiser8r@canalblog.com'),
 (89110213887,'Dewey','Fynes','dfynes8s@washingtonpost.com'),
 (93042895699,'Maison','Lilleman','mlilleman8t@cornell.edu'),
 (95043076349,'Nestor','McQuillin','nmcquillin8u@parallels.com'),
 (93062394121,'Antonio','Kensett','akensett8v@acquirethisname.com'),
 (93022595931,'Charley','Gini','cgini8w@mediafire.com'),
 (89043093181,'Krystal','Johannesson','kjohannesson8x@hhs.gov'),
 (90051487943,'Ryon','Sember','rsember8y@1688.com'),
 (92090875471,'Shelden','Arnli','sarnli8z@cisco.com'),
 (93081069976,'Ingemar','Ziemke','iziemke90@independent.co.uk'),
 (93081624964,'Gabie','Buy','gbuy91@printfriendly.com'),
 (88031242534,'Hamlen','Janousek','hjanousek92@weibo.com'),
 (89031372131,'Margi','Leaburn','mleaburn93@cbc.ca'),
 (96020437849,'Annabal','Bixley','abixley94@cdc.gov'),
 (98070271123,'Codi','Cordrey','ccordrey95@exblog.jp'),
 (89122249775,'Brice','Hastwell','bhastwell96@usnews.com'),
 (99062025887,'Guinevere','Heskey','gheskey97@icio.us'),
 (99011573638,'Melitta','Orrice','morrice98@woothemes.com'),
 (88080865555,'Nan','Van Daalen','nvandaalen99@cdbaby.com'),
 (93030221259,'Tiphani','Mapes','tmapes9a@nyu.edu'),
 (97030636475,'Clotilda','Jeste','cjeste9b@vinaora.com'),
 (93062777836,'Stevie','Gilpillan','sgilpillan9c@icq.com'),
 (95101384694,'Christiano','Enrrico','cenrrico9d@fastcompany.com'),
 (96012522272,'Robbert','Drysdall','rdrysdall9e@vistaprint.com'),
 (90070164311,'Trixy','Heaffey','theaffey9f@paypal.com'),
 (93042221487,'Devland','Remmers','dremmers9g@xrea.com'),
 (91021343722,'Hortensia','Manlow','hmanlow9h@walmart.com'),
 (96121469866,'Alick','Chitter','achitter9i@dyndns.org'),
 (96021464219,'Annalee','Boult','aboult9j@wiley.com'),
 (96122161132,'Cullin','Kirstein','ckirstein9k@ifeng.com'),
 (94120727327,'Georgina','MacSharry','gmacsharry9l@fc2.com'),
 (95061842971,'Mick','Loeber','mloeber9m@washington.edu'),
 (98100438784,'Florian','Conaghan','fconaghan9n@bloglines.com'),
 (97062617952,'Ty','Haggus','thaggus9o@rambler.ru'),
 (91012944358,'Tobin','Gunningham','tgunningham9p@sphinn.com'),
 (93042424941,'Irena','Mowsley','imowsley9q@scientificamerican.com'),
 (95102423998,'Rosie','Grzegorek','rgrzegorek9r@theatlantic.com'),
 (88072115329,'Theobald','Godfree','tgodfree9s@ibm.com'),
 (98010734918,'Melisent','Zanetello','mzanetello9t@youtu.be'),
 (95122137675,'Susy','Torvey','storvey9u@house.gov'),
 (97012223576,'Emalee','McGing','emcging9v@bizjournals.com'),
 (88090947634,'Desi','Connor','dconnor9w@jigsy.com'),
 (99061582895,'Abelard','Mateja','amateja9x@slashdot.org'),
 (94090266693,'Petronille','Heino','pheino9y@usa.gov'),
 (96041031136,'Penn','Magenny','pmagenny9z@sun.com'),
 (89051651267,'Christan','Strodder','cstroddera0@cornell.edu'),
 (95112577513,'Antonie','Faughey','afaugheya1@bing.com'),
 (97100174616,'Devora','Yanov','dyanova2@wix.com'),
 (98121232839,'Niels','Extal','nextala3@macromedia.com'),
 (99021659834,'Riccardo','Bolino','rbolinoa4@ehow.com'),
 (89082217555,'Hester','Aveling','havelinga5@is.gd'),
 (93050295782,'Colette','Grafom','cgrafoma6@dagondesign.com'),
 (94031597758,'Kendricks','Salvidge','ksalvidgea7@dot.gov'),
 (89122429858,'Alfy','Pietsma','apietsmaa8@newyorker.com'),
 (90012357157,'Constantine','Ligerton','cligertona9@nasa.gov'),
 (94072923273,'Mersey','Ketchell','mketchellaa@boston.com'),
 (96032275448,'Merle','Delamar','mdelamarab@blogspot.com'),
 (98092687434,'Alicea','While','awhileac@pagesperso-orange.fr'),
 (99041888685,'Laurella','Moine','lmoinead@issuu.com'),
 (91122444241,'Tannie','Ridler','tridlerae@theatlantic.com'),
 (92111991955,'Phyllis','Byrch','pbyrchaf@wisc.edu'),
 (94101615919,'Emlyn','Silversmidt','esilversmidtag@reuters.com'),
 (98020922994,'Melina','Vanshin','mvanshinah@scientificamerican.com'),
 (99021919352,'Gauthier','Dran','gdranai@mashable.com'),
 (92071991514,'Cathleen','Jarry','cjarryaj@independent.co.uk'),
 (98121781289,'Corella','Ould','couldak@123-reg.co.uk'),
 (96091036785,'Asia','Offill','aoffillal@eepurl.com'),
 (95092332258,'Lynnea','Josey','ljoseyam@surveymonkey.com'),
 (94050826699,'Brucie','Grogan','bgroganan@comcast.net'),
 (92103062753,'Cory','MacCart','cmaccartao@ask.com'),
 (93020659246,'Corilla','Johl','cjohlap@studiopress.com'),
 (88102914467,'Cindi','Harbor','charboraq@scientificamerican.com'),
 (88032237962,'Randell','Jencken','rjenckenar@youku.com'),
 (98122657684,'Deva','Cranmer','dcranmeras@mayoclinic.com'),
 (98110192441,'Lisha','Lefort','llefortat@eepurl.com'),
 (97080453356,'Freeland','Weins','fweinsau@about.com'),
 (94040892466,'Kendal','Baleine','kbaleineav@qq.com'),
 (95012242614,'Haze','Nozzolii','hnozzoliiaw@globo.com'),
 (92101034666,'Benoit','Titcom','btitcomax@howstuffworks.com'),
 (98061864864,'Konrad','Risbrough','krisbroughay@nature.com'),
 (90092198215,'Wildon','Lenormand','wlenormandaz@twitter.com'),
 (94081576633,'Dwight','Tomowicz','dtomowiczb0@uol.com.br'),
 (98101749498,'Griff','Jayes','gjayesb1@goodreads.com'),
 (95011747653,'Josh','Wheeliker','jwheelikerb2@ft.com'),
 (99020873112,'Morse','Hickinbottom','mhickinbottomb3@state.gov'),
 (96092571434,'Francesco','Rhydderch','frhydderchb4@sakura.ne.jp'),
 (99040885393,'Gusty','Tincey','gtinceyb5@irs.gov'),
 (97052945874,'Keeley','Dunbobbin','kdunbobbinb6@craigslist.org'),
 (89100782157,'Edeline','Viegas','eviegasb7@arstechnica.com'),
 (90062755639,'Bunni','Mitchel','bmitchelb8@so-net.ne.jp'),
 (88103048961,'Austine','Siddons','asiddonsb9@ebay.co.uk'),
 (98080295681,'Malena','Bartelot','mbartelotba@sitemeter.com'),
 (98010152637,'Jerri','Colquite','jcolquitebb@cpanel.net'),
 (94012196787,'Maiga','Dinan','mdinanbc@globo.com'),
 (89020679863,'Josiah','Robinson','jrobinsonbd@comcast.net'),
 (89050479824,'Fritz','Wenzel','fwenzelbe@admin.ch'),
 (89102632573,'Silva','Joinson','sjoinsonbf@narod.ru'),
 (94012095765,'Ali','Ship','ashipbg@state.tx.us'),
 (92082424436,'Chad','Coppens','ccoppensbh@washingtonpost.com'),
 (96020853191,'Sallyanne','Jaggli','sjagglibi@hibu.com'),
 (89030888297,'Bendicty','Neville','bnevillebj@moonfruit.com'),
 (97050412213,'Tobe','Joblin','tjoblinbk@wikipedia.org'),
 (94121025936,'Fredek','Foli','ffolibl@symantec.com'),
 (99060271976,'Danika','Bromage','dbromagebm@kickstarter.com'),
 (95092797778,'Jolyn','Sidey','jsideybn@bluehost.com'),
 (88101169875,'Nevsa','Ducker','nduckerbo@t-online.de'),
 (95040928939,'Fara','Hebborn','fhebbornbp@blogs.com'),
 (89012865225,'Celestine','Houten','choutenbq@ask.com'),
 (95050188598,'Marianne','Shrimplin','mshrimplinbr@desdev.cn'),
 (96060318391,'Stephani','Chislett','schislettbs@ucoz.ru'),
 (95020556714,'Susana','Ebbens','sebbensbt@squidoo.com'),
 (97101285715,'Hayden','Bucksey','hbuckseybu@edublogs.org'),
 (89081045443,'Hildagard','Traher','htraherbv@vistaprint.com'),
 (88100596856,'Lorita','Gallafant','lgallafantbw@oaic.gov.au'),
 (90091886951,'Gaspar','Dominy','gdominybx@e-recht24.de'),
 (99011655839,'Sharai','Kunisch','skunischby@yahoo.co.jp'),
 (94010522775,'Lamont','Crofthwaite','lcrofthwaitebz@cargocollective.com'),
 (93020736718,'Christy','Becraft','cbecraftc0@pagesperso-orange.fr'),
 (94063083382,'Jacinthe','Gouny','jgounyc1@wix.com'),
 (96052494241,'Bell','Ahearne','bahearnec2@springer.com'),
 (90030198891,'Nedi','Crosson','ncrossonc3@ameblo.jp'),
 (91012288188,'Mignon','Troyes','mtroyesc4@blog.com'),
 (93070413256,'Guinevere','Feaveer','gfeaveerc5@biblegateway.com'),
 (92082644498,'Bonita','Guare','bguarec6@topsy.com'),
 (88093011145,'Mordy','Dalinder','mdalinderc7@ezinearticles.com'),
 (98032251114,'Bondon','Klosa','bklosac8@apache.org'),
 (95060894696,'Annis','Blacksell','ablacksellc9@paginegialle.it'),
 (91083023989,'Truman','Brecon','tbreconca@google.it'),
 (88041978331,'Lexis','Jagoe','ljagoecb@free.fr'),
 (90070533166,'Stevana','Learoyde','slearoydecc@about.me'),
 (95051378727,'Morgen','Alliott','malliottcd@twitpic.com'),
 (90072532927,'Silvester','Gow','sgowce@163.com'),
 (91122293784,'Aguie','Longhurst','alonghurstcf@ask.com'),
 (89020214879,'Deane','Ledwich','dledwichcg@wsj.com'),
 (92112036941,'Fey','Wintersgill','fwintersgillch@csmonitor.com'),
 (96101439896,'Minni','Avrahm','mavrahmci@nhs.uk'),
 (96082272624,'Staci','Filppetti','sfilppetticj@google.ru'),
 (95050923393,'Finlay','Tibbs','ftibbsck@wordpress.com'),
 (88110865643,'Aloysia','Longland','alonglandcl@youku.com'),
 (95121712462,'Laurena','McVanamy','lmcvanamycm@bloomberg.com'),
 (96103126842,'Nanny','Zavittieri','nzavittiericn@delicious.com'),
 (94012176316,'Inga','Norrington','inorringtonco@ft.com'),
 (89092878496,'Kelby','Addekin','kaddekincp@shop-pro.jp'),
 (89081083764,'Lynea','Shrive','lshrivecq@skype.com'),
 (88090679146,'Neale','Ghion','nghioncr@reverbnation.com'),
 (97080112369,'Rowe','Skidmore','rskidmorecs@rakuten.co.jp'),
 (97011227328,'Eal','Shrawley','eshrawleyct@chronoengine.com'),
 (94050837631,'Valentijn','Gillbe','vgillbecu@rakuten.co.jp'),
 (92040343456,'Dorree','Phillpot','dphillpotcv@uiuc.edu'),
 (99052322273,'Wyn','McAlinion','wmcalinioncw@dyndns.org'),
 (95100173819,'Jeffie','Costa','jdcostacx@google.ca'),
 (91021971998,'Marys','Haime','mhaimecy@is.gd'),
 (89042542716,'Tiena','Cowin','tcowincz@technorati.com'),
 (97080122119,'Omero','McKeady','omckeadyd0@berkeley.edu'),
 (88011579898,'Elvin','Allenby','eallenbyd1@macromedia.com'),
 (94021346634,'Eloise','Fabri','efabrid2@sphinn.com'),
 (95041156571,'Starlene','Caygill','scaygilld3@yahoo.com'),
 (92061291453,'Reggie','Greenough','rgreenoughd4@technorati.com'),
 (97031685447,'Nisse','Kroger','nkrogerd5@admin.ch'),
 (99012585885,'Danella','Waple','dwapled6@statcounter.com'),
 (97071124232,'Mechelle','Jaffray','mjaffrayd7@altervista.org'),
 (97040295628,'Jourdain','Baine','jbained8@eepurl.com'),
 (95022318817,'Georgy','Ecclestone','gecclestoned9@fc2.com'),
 (97082656719,'Thain','Pinnock','tpinnockda@washingtonpost.com'),
 (94050934369,'Terence','Boylin','tboylindb@state.tx.us'),
 (90050148935,'Calli','Rawsthorn','crawsthorndc@quantcast.com'),
 (93012153655,'Ingeborg','Jon','ijondd@zdnet.com'),
 (91082695169,'Drusi','Handling','dhandlingde@cbslocal.com'),
 (93062834661,'Vinnie','Twinberrow','vtwinberrowdf@w3.org'),
 (92052327682,'Frayda','Boscher','fboscherdg@uol.com.br'),
 (91071885528,'Harry','Gerrey','hgerreydh@marriott.com'),
 (96122929851,'Freemon','Bracknall','fbracknalldi@reuters.com'),
 (90051796281,'Emmanuel','Duro','edurodj@ihg.com'),
 (98031524691,'Beaufort','Gronow','bgronowdk@ezinearticles.com'),
 (95110541862,'Faye','MacDirmid','fmacdirmiddl@booking.com'),
 (97060912769,'Marion','Strafford','mstrafforddm@storify.com'),
 (96080134414,'Tomasina','Treasure','ttreasuredn@edublogs.org'),
 (97050697124,'Maridel','Rogez','mrogezdo@weibo.com'),
 (96042293542,'Corette','Chant','cchantdp@google.nl'),
 (91042228589,'Tye','Bollum','tbollumdq@java.com'),
 (94112129713,'Candra','Eam','ceamdr@nhs.uk'),
 (98062026911,'Rosie','Hazell','rhazellds@chronoengine.com'),
 (89062314489,'Korie','Ropking','kropkingdt@google.ru'),
 (88101744371,'Petra','MacConnel','pmacconneldu@scientificamerican.com'),
 (92030866787,'Clementius','Eliassen','celiassendv@va.gov'),
 (92073088513,'Zitella','Bedburrow','zbedburrowdw@nifty.com'),
 (92072167842,'Gigi','Gorke','ggorkedx@japanpost.jp'),
 (95060118871,'Andra','Leal','alealdy@istockphoto.com'),
 (90031585748,'Edwina','Mogridge','emogridgedz@hibu.com'),
 (96101693656,'Antone','Bees','abeese0@ted.com'),
 (95011824576,'Blanca','Jiricka','bjirickae1@theglobeandmail.com'),
 (95102543861,'Cilka','Ladlow','cladlowe2@bandcamp.com'),
 (96013116274,'Eadie','Dabs','edabse3@yellowpages.com'),
 (94102129453,'Benson','Braidley','bbraidleye4@sakura.ne.jp'),
 (89042018251,'Lyman','Bough','lboughe5@sbwire.com'),
 (93032696688,'Van','Mattia','vmattiae6@omniture.com'),
 (96092462497,'Inness','Apfel','iapfele7@dagondesign.com'),
 (96100242752,'Jacobo','Feldmann','jfeldmanne8@mail.ru'),
 (91061061613,'Nat','Blaxill','nblaxille9@illinois.edu'),
 (98052113157,'Isaak','Wearne','iwearneea@tmall.com'),
 (98102614526,'Grier','Zanelli','gzanellieb@studiopress.com'),
 (90090775425,'Shaughn','Lohmeyer','slohmeyerec@plala.or.jp'),
 (90062311871,'Dorian','Gheeraert','dgheeraerted@myspace.com'),
 (96012812638,'Trenton','Dovidian','tdovidianee@ameblo.jp'),
 (91012955338,'Consalve','Gisborne','cgisborneef@wisc.edu'),
 (98101566381,'Karalynn','Petkovic','kpetkoviceg@facebook.com'),
 (98052258588,'Brennen','Sabatier','bsabatiereh@ca.gov'),
 (96031563421,'Rodd','Offa','roffaei@harvard.edu'),
 (94092579643,'Sutherlan','Lorenzetto','slorenzettoej@exblog.jp'),
 (90071445781,'Ethelind','Haacker','ehaackerek@twitter.com'),
 (91030562853,'Carlotta','Van Rembrandt','cvanrembrandtel@abc.net.au'),
 (91072118414,'Glennis','Gulk','ggulkem@dmoz.org'),
 (97092396926,'Alfreda','Conachie','aconachieen@sakura.ne.jp'),
 (93121247375,'Liv','Grigg','lgriggeo@smugmug.com'),
 (89081284769,'Brynn','Houselee','bhouseleeep@about.me'),
 (92070941442,'Ingmar','Penquet','ipenqueteq@google.com'),
 (97041561922,'Monica','Cleverley','mcleverleyer@51.la'),
 (90013113996,'Falito','Haddy','fhaddyes@wp.com'),
 (91080533775,'Dud','Jessopp','djessoppet@php.net'),
 (89090831178,'Danell','Oselton','doseltoneu@i2i.jp'),
 (92010465557,'Rand','Mattingson','rmattingsonev@tamu.edu'),
 (91032092114,'Danielle','Smellie','dsmellieew@wp.com'),
 (97043024247,'Roderick','Crocken','rcrockenex@acquirethisname.com'),
 (95050425666,'Lynnette','Pellamonuten','lpellamonuteney@goo.gl'),
 (96071274954,'Chalmers','Necolds','cnecoldsez@intel.com'),
 (96012924166,'Karlie','Aldwinckle','kaldwincklef0@nydailynews.com'),
 (93100131415,'Legra','McGray','lmcgrayf1@vkontakte.ru'),
 (97101896629,'Sheeree','Thomassen','sthomassenf2@blogs.com'),
 (94030158811,'Mozes','Arkcoll','markcollf3@craigslist.org'),
 (89100157656,'Zora','Benard','zbenardf4@mysql.com'),
 (93090534634,'Eda','Huburn','ehuburnf5@furl.net'),
 (92022185698,'Perren','Berford','pberfordf6@hao123.com'),
 (92052245474,'Virginie','Bradfield','vbradfieldf7@guardian.co.uk'),
 (91111812934,'Moshe','Roscoe','mroscoef8@bizjournals.com'),
 (96072472122,'Mike','Samuel','msamuelf9@sciencedirect.com'),
 (97070297524,'Hedvig','McMeekin','hmcmeekinfa@instagram.com'),
 (96090789189,'Aeriela','Pittham','apitthamfb@alexa.com'),
 (89052393399,'Estele','Cornillot','ecornillotfc@indiegogo.com'),
 (96052217543,'Rosalynd','Skehan','rskehanfd@twitter.com'),
 (98031572779,'Sanderson','Fauguel','sfauguelfe@plala.or.jp'),
 (95090644539,'Chiquita','Presdie','cpresdieff@typepad.com'),
 (97072743887,'Ethyl','Gare','egarefg@nifty.com'),
 (98121561678,'Carlee','Fawdry','cfawdryfh@virginia.edu'),
 (98032262637,'Othello','Print','oprintfi@oaic.gov.au'),
 (94052259468,'Ada','Kitchinham','akitchinhamfj@weebly.com'),
 (93022285685,'Arin','MacKean','amackeanfk@telegraph.co.uk'),
 (98122936312,'Robinet','Cockran','rcockranfl@ucoz.ru'),
 (91051498586,'Georgianna','Lemmen','glemmenfm@adobe.com'),
 (94010955898,'Kristo','Baltzar','kbaltzarfn@icq.com'),
 (90112456354,'Barr','Suatt','bsuattfo@umn.edu'),
 (97050873777,'Morlee','Crocumbe','mcrocumbefp@examiner.com'),
 (96092257761,'Alverta','Sheeryne','aosheerynefq@admin.ch'),
 (94123051878,'Anjela','Thomsen','athomsenfr@cbc.ca'),
 (93030555284,'Vittoria','Doogood','vdoogoodfs@uol.com.br'),
 (96080626838,'Gabrila','Shearn','gshearnft@who.int'),
 (92100265784,'Chevalier','Dyte','cdytefu@walmart.com'),
 (88091761974,'Guinevere','Palfery','gpalferyfv@trellian.com'),
 (92102789688,'Clemence','Geale','cgealefw@blogtalkradio.com'),
 (99012749775,'Don','Parncutt','dparncuttfx@smugmug.com'),
 (93030863439,'Cathlene','Linsley','clinsleyfy@spotify.com'),
 (91062619518,'Pris','Frain','pfrainfz@wiley.com'),
 (94082971772,'Doralynn','Evequot','devequotg0@omniture.com'),
 (90032979838,'Harp','Gee','hgeeg1@taobao.com'),
 (95120293555,'Lorie','Parkyn','lparkyng2@cargocollective.com'),
 (90060996782,'Billy','Bashford','bbashfordg3@sfgate.com'),
 (96060523614,'Henrie','Capewell','hcapewellg4@posterous.com'),
 (92031834471,'Giuseppe','Exley','gexleyg5@cpanel.net'),
 (98102241159,'Bron','Semarke','bsemarkeg6@opera.com'),
 (94031522486,'Denna','Brambill','dbrambillg7@theatlantic.com'),
 (96042131996,'Lyndsay','Pargetter','lpargetterg8@businessinsider.com'),
 (97033177272,'Willie','Mustin','wmusting9@hexun.com'),
 (92121312241,'Yoshiko','Jarry','yjarryga@elpais.com'),
 (93120584567,'Mickie','Garza','mgarzagb@ed.gov'),
 (98011585179,'Dina','Lycett','dlycettgc@reference.com'),
 (92120124243,'Massimiliano','Brouncker','mbrounckergd@mozilla.org'),
 (96040518652,'Marlon','Andersen','mandersenge@umich.edu'),
 (96120869674,'Bowie','McDonnell','bmcdonnellgf@wikimedia.org'),
 (88071443977,'Robinet','Forrington','rforringtongg@chron.com'),
 (91070799642,'Dallas','Pye','dpyegh@nba.com'),
 (99053182733,'Thebault','Marzello','tmarzellogi@google.es'),
 (99050787597,'Giovanna','Jenne','gjennegj@histats.com'),
 (88103094955,'Pierre','Nardoni','pnardonigk@google.co.jp'),
 (95112163815,'Elayne','Driffe','edriffegl@craigslist.org'),
 (95090219674,'Gerladina','Getcliff','ggetcliffgm@home.pl'),
 (89010119272,'Ninette','Snowdon','nsnowdongn@thetimes.co.uk'),
 (94033132472,'Walton','Ollander','wollandergo@wikia.com'),
 (99050487398,'Sabina','Doherty','sodohertygp@accuweather.com'),
 (90120251198,'Darleen','Woollett','dwoollettgq@nyu.edu'),
 (89032878735,'Malinde','Runcieman','mrunciemangr@google.co.uk'),
 (89110776838,'Kittie','Bisp','kbispgs@nba.com'),
 (95073019675,'Floria','Bock','fbockgt@google.com'),
 (96032029238,'Angus','Crame','acramegu@ucsd.edu'),
 (97052587429,'Cazzie','Arkley','carkleygv@newyorker.com'),
 (94021989679,'Randi','Todd','rtoddgw@engadget.com'),
 (95042428215,'Shantee','Marcoolyn','smarcoolyngx@istockphoto.com'),
 (96101593161,'Christiane','Frain','cfraingy@netvibes.com'),
 (99021652899,'Correna','Matkovic','cmatkovicgz@answers.com'),
 (95012069545,'Adoree','Himsworth','ahimsworthh0@hubpages.com'),
 (89053133174,'Rhiamon','Heggie','rheggieh1@hud.gov'),
 (92042936937,'Maddalena','Pude','mpudeh2@dell.com'),
 (91041599828,'Torrance','Rowbottom','trowbottomh3@discuz.net'),
 (90062719723,'Elisabetta','touret','etoureth4@opensource.org'),
 (90121676189,'Trudey','Dami','tdamih5@icio.us'),
 (97042423153,'Rosella','Andresser','randresserh6@zdnet.com'),
 (95012757617,'Egor','Licciardi','elicciardih7@flavors.me'),
 (90090463122,'Terencio','Boumphrey','tboumphreyh8@timesonline.co.uk'),
 (94080257942,'Sergeant','Dufer','sduferh9@myspace.com'),
 (88082036665,'Jeremie','De Caville','jdecavilleha@paypal.com'),
 (96092118343,'Binni','Brookesbie','bbrookesbiehb@opera.com'),
 (93040767321,'Cynthy','Munning','cmunninghc@wikispaces.com'),
 (98101285989,'Claudine','Hoolahan','cohoolahanhd@chronoengine.com'),
 (91061793934,'Chickie','Twinbourne','ctwinbournehe@technorati.com'),
 (97071681775,'Courtnay','Crathorne','ccrathornehf@nyu.edu'),
 (93032341328,'Felicity',' Lone','folonehg@bbc.co.uk'),
 (97043097531,'Merla','Sidey','msideyhh@sciencedirect.com');


INSERT INTO biuro_podrozy.offers 
  ( NAME, CITY, COUNTRY, DATE_BEGIN, DATE_END, PRICE, CATEGORYID, INSURANCE_COST, EXTRA_MEALS_COST, TICKETS_COUNT) 
VALUES 
  ('Wycieczka 1','Tokio','Japonia',STR_TO_DATE('14.01.19','%d.%m.%y'),STR_TO_DATE('20.01.19','%d.%m.%y'),6412,1,830,393,55),
  ('Wycieczka 2','Meksyk-City','Meksyk',STR_TO_DATE('15.01.19','%d.%m.%y'),STR_TO_DATE('21.01.19','%d.%m.%y'),4298,4,614,538,55),
  ('Wycieczka 3','Nowy Jork','USA',STR_TO_DATE('16.01.19','%d.%m.%y'),STR_TO_DATE('22.01.19','%d.%m.%y'),6990,2,795,385,46),
  ('Wycieczka 4','Kair','Egipt',STR_TO_DATE('17.01.19','%d.%m.%y'),STR_TO_DATE('23.01.19','%d.%m.%y'),5040,4,793,608,52),
  ('Wycieczka 5','Sao Paulo','Brazylia',STR_TO_DATE('18.01.19','%d.%m.%y'),STR_TO_DATE('24.01.19','%d.%m.%y'),4909,2,1320,751,42),
  ('Wycieczka 6','Seul','Korea południowa',STR_TO_DATE('19.01.19','%d.%m.%y'),STR_TO_DATE('25.01.19','%d.%m.%y'),3101,3,1241,514,45),
  ('Wycieczka 7','Osaka','Japonia',STR_TO_DATE('20.01.19','%d.%m.%y'),STR_TO_DATE('26.01.19','%d.%m.%y'),4848,3,1079,566,53),
  ('Wycieczka 8','Los Angeles','USA',STR_TO_DATE('21.01.19','%d.%m.%y'),STR_TO_DATE('27.01.19','%d.%m.%y'),9264,1,1311,461,48),
  ('Wycieczka 9','Szanghaj','Chiny',STR_TO_DATE('22.01.19','%d.%m.%y'),STR_TO_DATE('28.01.19','%d.%m.%y'),6609,2,1502,563,53),
  ('Wycieczka 10','Bombaj','Indie',STR_TO_DATE('14.02.19','%d.%m.%y'),STR_TO_DATE('20.02.19','%d.%m.%y'),2584,1,1336,443,57),
  ('Wycieczka 11','Kalkuta','Indie',STR_TO_DATE('15.02.19','%d.%m.%y'),STR_TO_DATE('21.02.19','%d.%m.%y'),1262,1,596,323,49),
  ('Wycieczka 12','Czungcing','Chiny',STR_TO_DATE('16.02.19','%d.%m.%y'),STR_TO_DATE('22.02.19','%d.%m.%y'),8596,2,683,312,42),
  ('Wycieczka 13','Rio de Janeiro','Brazylia',STR_TO_DATE('17.02.19','%d.%m.%y'),STR_TO_DATE('23.02.19','%d.%m.%y'),8930,4,1698,325,60),
  ('Wycieczka 14','Pekin','Chiny',STR_TO_DATE('18.02.19','%d.%m.%y'),STR_TO_DATE('24.02.19','%d.%m.%y'),7771,4,692,750,41),
  ('Wycieczka 15','Londyn','Anglia',STR_TO_DATE('19.02.19','%d.%m.%y'),STR_TO_DATE('25.02.19','%d.%m.%y'),1086,4,1277,344,58),
  ('Wycieczka 16','Buenos Aires','Argentyna',STR_TO_DATE('20.02.19','%d.%m.%y'),STR_TO_DATE('26.02.19','%d.%m.%y'),7337,3,1664,598,52),
  ('Wycieczka 17','Bangkok','Tajlandia',STR_TO_DATE('21.02.19','%d.%m.%y'),STR_TO_DATE('27.02.19','%d.%m.%y'),1060,2,699,602,47),
  ('Wycieczka 18','Stambu','Turcja',STR_TO_DATE('22.02.19','%d.%m.%y'),STR_TO_DATE('28.02.19','%d.%m.%y'),2889,4,677,437,54),
  ('Wycieczka 19','Teheran','Iran',STR_TO_DATE('14.05.19','%d.%m.%y'),STR_TO_DATE('20.05.19','%d.%m.%y'),7928,2,1434,535,44),
  ('Wycieczka 20','Djakarta','Indonezja',STR_TO_DATE('15.05.19','%d.%m.%y'),STR_TO_DATE('21.05.19','%d.%m.%y'),3982,2,554,413,58),
  ('Wycieczka 21','Karaczi','Pakistan',STR_TO_DATE('16.05.19','%d.%m.%y'),STR_TO_DATE('22.05.19','%d.%m.%y'),3691,3,1804,449,52),
  ('Wycieczka 22','Paryz','Francja',STR_TO_DATE('17.05.19','%d.%m.%y'),STR_TO_DATE('23.05.19','%d.%m.%y'),2584,3,1541,475,49),
  ('Wycieczka 23','Tiencin','Chiny',STR_TO_DATE('18.05.19','%d.%m.%y'),STR_TO_DATE('24.05.19','%d.%m.%y'),1255,3,1078,434,49),
  ('Wycieczka 24','Lagos','Portugalja',STR_TO_DATE('19.05.19','%d.%m.%y'),STR_TO_DATE('25.05.19','%d.%m.%y'),9742,1,1706,511,49),
  ('Wycieczka 25','Delhi','Indie',STR_TO_DATE('20.05.19','%d.%m.%y'),STR_TO_DATE('26.05.19','%d.%m.%y'),1175,2,1961,538,48),
  ('Wycieczka 26','Chicago','USA',STR_TO_DATE('21.05.19','%d.%m.%y'),STR_TO_DATE('27.05.19','%d.%m.%y'),3980,2,854,388,50),
  ('Wycieczka 27','Manila','Filipiny',STR_TO_DATE('22.05.19','%d.%m.%y'),STR_TO_DATE('28.05.19','%d.%m.%y'),7734,3,1890,682,53),
  ('Wycieczka 28','Moskwa','Rosja',STR_TO_DATE('14.07.19','%d.%m.%y'),STR_TO_DATE('20.07.19','%d.%m.%y'),3356,2,1446,582,42),
  ('Wycieczka 29','Dhaka','Bangladesz',STR_TO_DATE('15.07.19','%d.%m.%y'),STR_TO_DATE('21.07.19','%d.%m.%y'),7068,3,1055,720,43),
  ('Wycieczka 30','Czengtu','Chiny',STR_TO_DATE('16.07.19','%d.%m.%y'),STR_TO_DATE('22.07.19','%d.%m.%y'),2745,1,1355,677,58),
  ('Wycieczka 31','Konurbacja Zagłębia Ruhry','Niemcy',STR_TO_DATE('17.07.19','%d.%m.%y'),STR_TO_DATE('23.07.19','%d.%m.%y'),8687,2,1229,484,49),
  ('Wycieczka 32','Shantou','Chiny',STR_TO_DATE('18.07.19','%d.%m.%y'),STR_TO_DATE('24.07.19','%d.%m.%y'),7825,2,1645,357,50),
  ('Wycieczka 33','Lima - Callao','Cypr',STR_TO_DATE('19.07.19','%d.%m.%y'),STR_TO_DATE('25.07.19','%d.%m.%y'),5991,3,1301,563,52),
  ('Wycieczka 34','Nantong','Chiny',STR_TO_DATE('20.07.19','%d.%m.%y'),STR_TO_DATE('26.07.19','%d.%m.%y'),1411,3,1344,555,59),
  ('Wycieczka 35','Kanton','Chiny',STR_TO_DATE('21.07.19','%d.%m.%y'),STR_TO_DATE('27.07.19','%d.%m.%y'),2340,3,1682,459,44),
  ('Wycieczka 36','Waszyngton','USA',STR_TO_DATE('22.07.19','%d.%m.%y'),STR_TO_DATE('28.07.19','%d.%m.%y'),3009,2,1791,353,44),
  ('Wycieczka 37','Wuhan','Chiny',STR_TO_DATE('19.08.19','%d.%m.%y'),STR_TO_DATE('25.08.19','%d.%m.%y'),4474,3,1808,387,47),
  ('Wycieczka 38','Nagoja','Japonia',STR_TO_DATE('20.08.19','%d.%m.%y'),STR_TO_DATE('26.08.19','%d.%m.%y'),5046,4,618,657,51),
  ('Wycieczka 39','Ibadan','Nigeria',STR_TO_DATE('21.08.19','%d.%m.%y'),STR_TO_DATE('27.08.19','%d.%m.%y'),8616,2,1603,306,45),
  ('Wycieczka 40','Brasilia','Brazylia',STR_TO_DATE('22.08.19','%d.%m.%y'),STR_TO_DATE('28.08.19','%d.%m.%y'),3363,1,1493,329,50);

CREATE TRIGGER on_new_tour_appear
AFTER INSERT ON biuro_podrozy.tour  
FOR EACH ROW 
UPDATE biuro_podrozy.offers
  SET offers.Tickets_count = offers.Tickets_count - NEW.Reserved_tickets
  WHERE offers.Id = NEW.OfferId;


INSERT INTO biuro_podrozy.tour 
  (OFFERID, CustomerPesel, EMPLOYEEID, Insurance, Extra_meals, DEBT, FINISHED, RESERVED_TICKETS) 
VALUES 
  (28,92121963645,41,1,0,1379,1,2),
  (3,91102158153,8,1,1,1062,0,2),
  (5,98050322889,263,1,1,2509,0,3),
  (27,95052933721,286,0,0,1122,0,1),
  (38,99022565682,36,0,0,2381,0,3),
  (4,92020595486,219,0,0,2020,1,4),
  (35,90050252168,235,1,1,1446,0,4);


CREATE TRIGGER on_employee_remove
AFTER DELETE ON biuro_podrozy.employees 
FOR EACH ROW 
UPDATE biuro_podrozy.tour
  SET tour.EmployeeId = NULL WHERE tour.EmployeeId = OLD.Id;



delimiter //

CREATE PROCEDURE reserve_tour (
  IN offerid INT,
  IN ticket_count INT,
  IN customerid BIGINT,
  IN employeeid INT,
  IN Insurance INT(1),
  IN extra_meals INT(1)
)
proc_begin:BEGIN
  DECLARE offer_ticket_count INT DEFAULT 0;
  DECLARE offer_Insurance_cost INT;
  DECLARE offer_extra_meals_cost INT;
  DECLARE offer_price INT;
  
  SELECT Tickets_count, price, Insurance_cost, Extra_meals_cost
  INTO offer_ticket_count, offer_price, offer_Insurance_cost, offer_extra_meals_cost
  FROM offers WHERE offers.Id = offerid;
  
  IF offer_ticket_count < ticket_count THEN
    LEAVE proc_begin;
  END IF;
  
  SET offer_price = offer_price*ticket_count;
  
  IF offer_Insurance_cost IS NOT NULL AND Insurance <> 0 THEN
    SET offer_price = offer_price + offer_Insurance_cost*ticket_count;
  END IF;
  
  IF offer_extra_meals_cost IS NOT NULL AND extra_meals <> 0 THEN
    SET offer_price = offer_price + offer_extra_meals_cost*ticket_count;
  END IF;
  
  INSERT INTO biuro_podrozy.tour 
  (OfferId, CustomerPesel, EMPLOYEEID, Insurance, Extra_meals, DEBT, FINISHED, RESERVED_TICKETS) 
VALUES 
  (offerid,customerid,employeeid,Insurance,extra_meals,offer_price,0,ticket_count);

END//

CREATE PROCEDURE change_employee_tours (
  IN from_employee INT,
  IN to_employee INT
)
proc_begin:BEGIN
  IF from_employee IS NULL THEN
      UPDATE biuro_podrozy.tour
      SET tour.EmployeeId = to_employee WHERE tour.EmployeeId IS NULL;
    LEAVE proc_begin;
  END IF;
  
  UPDATE biuro_podrozy.tour
     SET tour.EmployeeId = to_employee WHERE tour.EmployeeId = from_employee;
END//


CREATE PROCEDURE resign_from_insurance (
  IN tourid INT 
)
proc_begin:BEGIN
  DECLARE withInsurance INT(1);
  DECLARE tour_finished INT(1);
  DECLARE tour_Debt INT;
  DECLARE tour_reserved_tickets INT;
  DECLARE tour_offerid INT;
  DECLARE offer_insurance_cost INT;

  SELECT Insurance, Debt, Reserved_tickets, Finished, offerid
  INTO withInsurance, tour_Debt, tour_reserved_tickets, tour_finished, tour_offerid
  FROM tour WHERE  tour.id = tourid;

  IF withInsurance IS NULL OR withInsurance = 0 OR tour_finished = 1 THEN
    LEAVE proc_begin;
  END IF;

  SELECT Insurance_cost
  INTO offer_insurance_cost
  FROM offers WHERE  offers.id = tour_offerid;

  SET tour_Debt = tour_Debt -  offer_insurance_cost*tour_reserved_tickets;

  UPDATE biuro_podrozy.tour
     SET 
        tour.Debt = tour_Debt,
        tour.Insurance =0 
     WHERE tour.id = tourid;
END//


CREATE PROCEDURE resign_from_extra_meals (
  IN tourid INT 
)
proc_begin:BEGIN
  DECLARE with_extra_meals INT(1);
  DECLARE tour_finished INT(1);
  DECLARE tour_Debt INT;
  DECLARE tour_reserved_tickets INT;
  DECLARE tour_offerid INT;
  DECLARE offer_extra_meals_cost INT;

  SELECT Extra_meals, Debt, Reserved_tickets, Finished, offerid
  INTO with_extra_meals, tour_Debt, tour_reserved_tickets, tour_finished, tour_offerid
  FROM tour WHERE  tour.id = tourid;

  IF with_extra_meals IS NULL OR with_extra_meals = 0 OR tour_finished = 1 THEN
    LEAVE proc_begin;
  END IF;

  SELECT Extra_meals_cost
  INTO offer_extra_meals_cost
  FROM offers WHERE  offers.id = tour_offerid;

  SET tour_Debt = tour_Debt -  offer_extra_meals_cost*tour_reserved_tickets;

  UPDATE biuro_podrozy.tour
     SET 
     tour.Debt = tour_Debt,
     tour.Extra_meals =0
    WHERE tour.id = tourid;
END//

CREATE PROCEDURE forget_customer (
  IN customerId INT,
  OUT return_value INT
)
proc_begin:BEGIN

  DECLARE tours_count INT;
  SET return_value = 0; 
  SELECT COUNT(*) 
  INTO tours_count 
  FROM tour WHERE tour.customerid = customerId AND tour.finished = 0;
  IF tours_count <> 0 THEN
    SET return_value = -1;
    LEAVE proc_begin;
  END IF;
  DELETE FROM customers WHERE  customers.id = customerId;
END//

CREATE PROCEDURE forget_offer (
  IN offerId INT,
  OUT return_value INT
)
proc_begin:BEGIN

  DECLARE tours_count INT;
  SET return_value = 0; 
  SELECT COUNT(*) 
  INTO tours_count 
  FROM tour WHERE tour.offerid = offerId AND tour.finished = 0;
  IF tours_count <> 0 THEN
    SET return_value = -1;
    LEAVE proc_begin;
  END IF;
  DELETE FROM offers WHERE  offers.id = offerId;
END//


CREATE PROCEDURE modify_offer(
  IN OfferId INT,
  IN OffName VARCHAR(50), 
  IN Country VARCHAR(50), 
  IN City VARCHAR(40),  
  IN Date_begin DATE, 
  IN Date_end DATE, 
  IN Price INT,
  IN Insurance_cost INT,
  IN Extra_meals_cost INT,
  IN CategoryId INT
)
proc_begin:BEGIN
  DECLARE tour_id INT;
  DECLARE cost_diff INT;
  DECLARE tour_debt INT;
  DECLARE tour_insurance INT;
  DECLARE tour_extra_meals INT;
  DECLARE tour_reserved_count INT;
  DECLARE current_insurance_cost INT;
  DECLARE current_extra_melas_cost INT;
  DECLARE affected_tours_count INT;
  DECLARE tour_cursor
    CURSOR FOR  
   SELECT id, Debt, Insurance, Extra_meals, Reserved_tickets FROM tour 
  WHERE  tour.OfferId = OfferId;

  SELECT offers.Insurance_cost, offers.Extra_meals_cost
  INTO current_insurance_cost, current_extra_melas_cost
  FROM offers WHERE offers.id = OfferId;
  
  OPEN tour_cursor;
  select FOUND_ROWS() into affected_tours_count;
  IF affected_tours_count <> 0 THEN
    tour_update: LOOP
      FETCH tour_cursor INTO tour_id, tour_debt, tour_insurance, tour_extra_meals, tour_reserved_count;
      SET cost_diff =0;
      IF tour_insurance = 0 THEN
         SET  cost_diff = (Insurance_cost -current_insurance_cost);
      END IF;

      IF tour_insurance = 0 THEN
         SET cost_diff = cost_diff + (Extra_meals_cost - current_extra_melas_cost);
      END IF;
      SET cost_diff = cost_diff * tour_reserved_count;
      
     UPDATE biuro_podrozy.tour
      SET
        tour.Debt = tour_debt + cost_diff
      WHERE  tour.id = tour_id;
      
    END LOOP tour_update;
  END IF;
  CLOSE tour_cursor;

  UPDATE biuro_podrozy.offers
     SET 
      offers.Name = OffName,
      offers.Country = Country,
      offers.City = City,
      offers.Date_begin = Date_begin,
      offers.Date_end = Date_end,
      offers.Price = Price,
      offers.Insurance_cost = Insurance_cost,
      offers.Extra_meals_cost = Extra_meals_cost,
      offers.CategoryId = CategoryId
     WHERE offers.id = OfferId;
END//

delimiter ;
-- procedura delete client must check if client has any tours and not finished 
CALL reserve_tour(1,4,92100265784,1,1,1);
CALL resign_from_insurance(2);
CALL resign_from_extra_meals(2);
CALL resign_from_insurance(2);
CALL resign_from_extra_meals(2);
CALL resign_from_insurance(8);
CALL resign_from_extra_meals(8);
CALL modify_offer(2,'Wycieczka 2','USA','NEW YORK',STR_TO_DATE('15.01.19','%d.%m.%y'),STR_TO_DATE('21.01.19','%d.%m.%y'),4298,614,538,4);

-- pokazanie funkcjionalnosci tirgera
SET FOREIGN_KEY_CHECKS=0;
DELETE FROM biuro_podrozy.employees WHERE biuro_podrozy.employees.Id =1;
SET FOREIGN_KEY_CHECKS=1;
CALL change_employee_tours(NULL, 2);
-- pokazanie naruszania kluczy w kazdej z tabel

-- INSERT INTO
-- biuro_podrozy.category (ID,  NAME) VALUES (1, 'Last minute');


-- INSERT INTO
-- biuro_podrozy.creditionals (LOGIN,  PASS_HASH,  ACCOUNT_TYPE) VALUES ("mamanger_1", 'Last minute',1);


-- INSERT INTO 
-- biuro_podrozy.annual_income  (ID,YEAR,BALANCE) VALUES (1, STR_TO_DATE('1978', '%Y'),  -5675);


-- INSERT INTO 
-- biuro_podrozy.employees  (ID,NAME,SURNAME, HIRE_DATE, SALARY,EMAIL,PHONE_NUMBER) VALUES (1,'Gerhardine','Loghan',STR_TO_DATE('30.07.09','%d.%m.%y'),4156,'gloghan0@china.com.cn','765-578-4612');


-- INSERT INTO 
-- biuro_podrozy.customers  (PESEL,NAME,SURNAME,EMAIL) VALUES (92121963645,'Dannie','Blockey','dblockey0@paginegialle.it');


-- INSERT INTO biuro_podrozy.offers 
--   (ID, NAME, CITY, COUNTRY, DATE_BEGIN, DATE_END, PRICE, CATEGORYID, INSURANCE_COST, EXTRA_MEALS_COST, TICKETS_COUNT) 
-- VALUES 
--   (1,'Wycieczka 1','Tokio','Japonia',STR_TO_DATE('14.01.19','%d.%m.%y'),STR_TO_DATE('20.01.19','%d.%m.%y'),6412,1,830,393,55);


-- INSERT INTO biuro_podrozy.tour 
--   (ID,  OFFERID, CustomerPesel, EMPLOYEEID, Insurance, Extra_meals, DEBT, FINISHED, RESERVED_TICKETS) 
-- VALUES 
--   (1,28,92121963645,41,1,0,1379,1,2);
