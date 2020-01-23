drop database if exists biuro_podrozy;
create database if not exists biuro_podrozy
  character set = 'utf8'
  collate = 'utf8_polish_ci';
set character_set_server = 'utf8';
set collation_server = 'utf8_polish_ci';

use biuro_podrozy;
set names utf8;

create table biuro_podrozy.tour (
  id               int(10) not null auto_increment,
  debt             int(10) not null,
  insurance        int(1),
  extra_meals      int(1),
  state            int(1) not null,
  reserved_tickets int(10) not null,
  customerid       int(10),
  employeeid       int(10),
  offerid          int(10),
  primary key (id));

create table biuro_podrozy.credentials (
  id           int(10)     not null auto_increment,
  login        varchar(50) not null,
  pass_hash    varchar(64) not null,
  privilege    int(1)      not null,
  employeeid   int(10)     not null,
  unique (employeeid),
  primary key (id));

create table biuro_podrozy.employees (
  id           int(10) not null auto_increment,
  name         varchar(50) not null,
  surname      varchar(50) not null,
  hire_date    date not null,
  salary       int(10) not null,
  email        varchar(50) not null,
  phone_number varchar(12) not null,
  primary key (id));

create table biuro_podrozy.customers (
  id      int(10) not null auto_increment,
  pesel   bigint(12) not null,
  name    varchar(50) not null,
  surname varchar(50) not null,
  email   varchar(50) not null,
  primary key (id));

create table biuro_podrozy.category (
  id   int(10) not null auto_increment,
  name varchar(50) not null,
  primary key (id));

create table biuro_podrozy.offers (
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

create table biuro_podrozy.annual_income (
  id int(10) not null auto_increment,
  year date not null,
  balance int(13) not null,
  primary key (id));

alter table biuro_podrozy.tour add constraint fktour997364 foreign key (customerid) references biuro_podrozy.customers (id);
alter table biuro_podrozy.tour add constraint fktour557083 foreign key (employeeid) references biuro_podrozy.employees (id);
alter table biuro_podrozy.tour add constraint fktour774357 foreign key (offerid) references biuro_podrozy.offers (id);
alter table biuro_podrozy.offers add constraint fkoffers229222 foreign key (categoryid) references biuro_podrozy.category (id);
alter table biuro_podrozy.credentials
  add constraint fk_credentials_employees foreign key (`employeeid`) references biuro_podrozy.employees (`id`);


insert into
biuro_podrozy.category
  (name)
values
  ('last minute'),
  ('sightseeing tour'),
  ('cruise'),
  ('facultative trips');


insert into biuro_podrozy.annual_income
  (year,balance)
values
  ( str_to_date('1978', '%Y'),  -5675),
  ( str_to_date('1979', '%Y'),  -7952),
  ( str_to_date('1980', '%Y'),  -3478),
  ( str_to_date('1981', '%Y'),  -2547),
  ( str_to_date('1982', '%Y'),  350),
  ( str_to_date('1983', '%Y'),  12457),
  ( str_to_date('1984', '%Y'),  65254),
  ( str_to_date('1985', '%Y'),  95789),
  ( str_to_date('1986', '%Y'),  125900),
  (  str_to_date('1987', '%Y'),  96376),
  (  str_to_date('1988', '%Y'),  134924),
  (  str_to_date('1989', '%Y'),  129829),
  (  str_to_date('1990', '%Y'),  105551),
  (  str_to_date('1991', '%Y'),  138482),
  (  str_to_date('1992', '%Y'),  118980),
  (  str_to_date('1993', '%Y'),  96416),
  (  str_to_date('1994', '%Y'),  82463),
  (  str_to_date('1995', '%Y'),  118606),
  (  str_to_date('1996', '%Y'),  81183),
  (  str_to_date('1997', '%Y'),  130009),
  (  str_to_date('1998', '%Y'),  97520),
  (  str_to_date('1999', '%Y'),  99880),
  (  str_to_date('2000', '%Y'),  95796),
  (  str_to_date('2001', '%Y'),  111848),
  (  str_to_date('2002', '%Y'),  111733),
  (  str_to_date('2003', '%Y'),  91428),
  (  str_to_date('2004', '%Y'),  116649),
  (  str_to_date('2005', '%Y'),  92682),
  (  str_to_date('2006', '%Y'),  115525),
  (  str_to_date('2007', '%Y'),  139747),
  (  str_to_date('2008', '%Y'),  91046),
  (  str_to_date('2009', '%Y'),  88344),
  (  str_to_date('2010', '%Y'),  85589),
  (  str_to_date('2011', '%Y'),  87658),
  (  str_to_date('2012', '%Y'),  123593),
  (  str_to_date('2013', '%Y'),  109855),
  (  str_to_date('2014', '%Y'),  124706),
  (  str_to_date('2015', '%Y'),  138409),
  (  str_to_date('2016', '%Y'),  95149),
  (  str_to_date('2017', '%Y'),  105841),
  (  str_to_date('2018', '%Y'),  102893),
  (  str_to_date('2019', '%Y'),  0);


insert into biuro_podrozy.employees
  (name,surname, hire_date, salary,email,phone_number)
  values
('gerhardine','loghan',str_to_date('30.07.09','%d.%m.%y'),4156,'gloghan0@china.com.cn','765-578-4612'),
('aubree','sturr',str_to_date('12.06.19','%d.%m.%y'),3598,'asturr1@linkedin.com','249-754-0474'),
('faustina','glusby',str_to_date('01.05.15','%d.%m.%y'),2072,'fglusby2@acquirethisname.com','369-671-0886'),
('dorelle','ong',str_to_date('08.03.09','%d.%m.%y'),3937,'dong3@myspace.com','166-542-3734'),
('brok','segebrecht',str_to_date('09.02.19','%d.%m.%y'),4033,'bsegebrecht4@dion.ne.jp','770-888-4001'),
('nikolas','twigg',str_to_date('09.01.19','%d.%m.%y'),2623,'ntwigg5@ask.com','765-515-7208'),
('lil','abbate',str_to_date('17.07.03','%d.%m.%y'),3668,'labbate6@theguardian.com','821-543-1231'),
('benita','mallan',str_to_date('13.09.12','%d.%m.%y'),3213,'bmallan7@moonfruit.com','185-925-0579'),
('shawna','mcgarry',str_to_date('25.05.11','%d.%m.%y'),4563,'smcgarry8@naver.com','114-376-7016'),
('martha','schulz',str_to_date('20.08.08','%d.%m.%y'),4591,'mschulz9@wisc.edu','685-622-3523'),
('rurik','demelt',str_to_date('04.05.17','%d.%m.%y'),3818,'rdemelta@issuu.com','121-911-7876'),
('marianne','ambrosoni',str_to_date('09.07.17','%d.%m.%y'),4205,'mambrosonib@paginegialle.it','761-511-5349'),
('bonita','hubber',str_to_date('01.08.05','%d.%m.%y'),2188,'bhubberc@goodreads.com','239-597-0796'),
('tara','delves',str_to_date('28.07.14','%d.%m.%y'),2631,'tdelvesd@apple.com','654-487-8278'),
('quent','marke',str_to_date('20.10.19','%d.%m.%y'),2274,'qmarkee@tripadvisor.com','409-493-8714'),
('loralie','matic',str_to_date('10.01.12','%d.%m.%y'),3804,'lmaticf@cam.ac.uk','413-644-1319'),
('monty','chipps',str_to_date('11.07.05','%d.%m.%y'),4153,'mchippsg@theguardian.com','733-610-6835'),
('jeanie','ringham',str_to_date('16.04.03','%d.%m.%y'),4392,'jringhamh@tuttocitta.it','664-215-4663'),
('vera','escott',str_to_date('10.10.06','%d.%m.%y'),4075,'vescotti@alibaba.com','575-157-6374'),
('boonie','passo',str_to_date('14.04.06','%d.%m.%y'),2583,'bpassoj@cafepress.com','747-255-8859'),
('constantina','barten',str_to_date('13.01.17','%d.%m.%y'),2675,'cbartenk@dyndns.org','725-646-7503'),
('sig','dunbobin',str_to_date('21.05.17','%d.%m.%y'),3190,'sdunbobinl@zdnet.com','388-108-6413'),
('cash','guerner',str_to_date('24.01.06','%d.%m.%y'),4776,'cguernerm@hud.gov','409-329-8491'),
('justina','filipiak',str_to_date('11.11.10','%d.%m.%y'),4315,'jfilipiakn@pinterest.com','989-345-9952'),
('marilee','dunan',str_to_date('20.01.06','%d.%m.%y'),2643,'mdunano@squidoo.com','859-443-0772'),
('maridel','linge',str_to_date('21.05.18','%d.%m.%y'),4171,'mlingep@rediff.com','868-139-6890'),
('flss','doughtery',str_to_date('14.02.03','%d.%m.%y'),2125,'fdoughteryq@gov.uk','121-825-9778'),
('cicely','oliphant',str_to_date('12.08.06','%d.%m.%y'),2655,'coliphantr@mit.edu','222-958-7074'),
('urbain','tantum',str_to_date('27.07.08','%d.%m.%y'),2443,'utantums@arizona.edu','794-637-0104'),
('joice','crocroft',str_to_date('09.04.09','%d.%m.%y'),3468,'jcrocroftt@sciencedaily.com','283-199-4958'),
('roseann','bryning',str_to_date('05.11.13','%d.%m.%y'),3272,'rbryningu@indiatimes.com','750-819-7384'),
('peterus','wheatland',str_to_date('31.03.16','%d.%m.%y'),3739,'pwheatlandv@sina.com.cn','711-518-3187'),
('aldo','vincent',str_to_date('06.11.07','%d.%m.%y'),2692,'avincentw@bbb.org','759-389-0456'),
('dion','tomkinson',str_to_date('06.03.14','%d.%m.%y'),2997,'dtomkinsonx@miitbeian.gov.cn','366-846-6977'),
('julina','cathenod',str_to_date('30.03.15','%d.%m.%y'),2568,'jcathenody@sakura.ne.jp','136-288-7007'),
('glennie','lashford',str_to_date('06.01.07','%d.%m.%y'),2863,'glashfordz@prnewswire.com','721-270-4709'),
('fransisco','aleksic',str_to_date('23.09.06','%d.%m.%y'),3924,'faleksic10@google.ru','159-432-1825'),
('giraud','pulsford',str_to_date('12.08.19','%d.%m.%y'),4807,'gpulsford11@cpanel.net','142-406-3823'),
('willard','clear',str_to_date('26.10.03','%d.%m.%y'),4817,'wclear12@japanpost.jp','731-169-2731'),
('ewen','beevors',str_to_date('05.08.15','%d.%m.%y'),4608,'ebeevors13@spotify.com','763-312-0866'),
('ezekiel','jacks',str_to_date('22.07.07','%d.%m.%y'),3310,'ejacks14@toplist.cz','211-153-5185'),
('zacharie','minelli',str_to_date('05.03.06','%d.%m.%y'),4735,'zminelli15@alibaba.com','161-682-0722'),
('heddie','bruna',str_to_date('11.11.19','%d.%m.%y'),2580,'hbruna16@bizjournals.com','559-177-5410'),
('regine','heritege',str_to_date('25.07.18','%d.%m.%y'),3512,'rheritege17@pen.io','837-755-0897'),
('etty','figurski',str_to_date('03.09.11','%d.%m.%y'),3320,'efigurski18@reference.com','465-671-3174'),
('sanders','spellar',str_to_date('29.09.15','%d.%m.%y'),4258,'sspellar19@eventbrite.com','437-551-3838'),
('sharon','cockle',str_to_date('16.02.14','%d.%m.%y'),4196,'scockle1a@berkeley.edu','783-739-7551'),
('carlo','legges',str_to_date('01.06.19','%d.%m.%y'),4570,'clegges1b@admin.ch','329-400-1414'),
('raina','deinhard',str_to_date('20.04.10','%d.%m.%y'),2004,'rdeinhard1c@dedecms.com','522-620-5448'),
('cass','pennick',str_to_date('30.12.11','%d.%m.%y'),2110,'cpennick1d@boston.com','586-581-5361'),
('sidnee','vallow',str_to_date('19.07.13','%d.%m.%y'),3742,'svallow1e@exblog.jp','798-914-8430'),
('claudetta','oland',str_to_date('05.05.05','%d.%m.%y'),3406,'coland1f@census.gov','320-456-8633'),
('antoni','oxley',str_to_date('11.05.08','%d.%m.%y'),3209,'aoxley1g@intel.com','578-251-2599'),
('cristine','barmadier',str_to_date('29.05.16','%d.%m.%y'),4434,'cbarmadier1h@opera.com','623-602-3858'),
('erek','jirus',str_to_date('01.08.04','%d.%m.%y'),4042,'ejirus1i@qq.com','858-542-7889'),
('willetta','hukins',str_to_date('29.09.18','%d.%m.%y'),4640,'whukins1j@360.cn','775-436-6035'),
('vinni','battista',str_to_date('31.03.05','%d.%m.%y'),4775,'vbattista1k@epa.gov','875-104-6715'),
('elnora','blooman',str_to_date('06.04.19','%d.%m.%y'),3893,'eblooman1l@marketwatch.com','107-745-1287'),
('etheline','emig',str_to_date('12.01.05','%d.%m.%y'),2089,'eemig1m@nationalgeographic.com','911-265-6821'),
('avigdor','gouthier',str_to_date('21.07.11','%d.%m.%y'),3552,'agouthier1n@cloudflare.com','187-395-1855'),
('fredra','bonnar',str_to_date('08.01.13','%d.%m.%y'),2026,'fbonnar1o@ihg.com','140-856-3098'),
('ansel','davison',str_to_date('14.04.15','%d.%m.%y'),2631,'adavison1p@imageshack.us','261-924-1705'),
('jasun','madge',str_to_date('03.04.19','%d.%m.%y'),4366,'jmadge1q@census.gov','259-377-3203'),
('rutter','thorsby',str_to_date('02.10.18','%d.%m.%y'),3214,'rthorsby1r@wix.com','983-843-5198'),
('willyt','rowland',str_to_date('27.03.16','%d.%m.%y'),2495,'wrowland1s@accuweather.com','210-163-9653'),
('ynes','addington',str_to_date('30.08.08','%d.%m.%y'),4773,'yaddington1t@hc360.com','837-131-6377'),
('franzen','mullenger',str_to_date('09.06.10','%d.%m.%y'),4434,'fmullenger1u@sakura.ne.jp','548-299-7084'),
('thibaud','biscomb',str_to_date('22.02.04','%d.%m.%y'),4612,'tbiscomb1v@miitbeian.gov.cn','454-287-4246'),
('meredeth','sumpton',str_to_date('01.12.06','%d.%m.%y'),4824,'msumpton1w@bizjournals.com','189-231-1629'),
('yuma','lavin',str_to_date('25.09.10','%d.%m.%y'),3468,'ylavin1x@instagram.com','740-107-9058'),
('kynthia','ropartz',str_to_date('06.02.11','%d.%m.%y'),3825,'kropartz1y@issuu.com','208-921-1717'),
('pierce','percy',str_to_date('02.05.03','%d.%m.%y'),4099,'ppercy1z@wikispaces.com','657-200-8810'),
('germaine','fedorski',str_to_date('21.02.06','%d.%m.%y'),3850,'gfedorski20@angelfire.com','625-222-7704'),
('ezechiel','mccullouch',str_to_date('27.04.07','%d.%m.%y'),4657,'emccullouch21@bloomberg.com','120-588-3960'),
('annabelle','bowerman',str_to_date('06.01.09','%d.%m.%y'),3044,'abowerman22@berkeley.edu','470-128-0597'),
('milly','hoodlass',str_to_date('28.08.16','%d.%m.%y'),3684,'mhoodlass23@ning.com','512-890-2292'),
('rosalind','kuhnhardt',str_to_date('14.02.06','%d.%m.%y'),3329,'rkuhnhardt24@dmoz.org','167-783-5678'),
('carce','francesc',str_to_date('27.12.15','%d.%m.%y'),4920,'cfrancesc25@dedecms.com','343-277-5040'),
('agatha','ottery',str_to_date('22.06.16','%d.%m.%y'),4370,'aottery26@howstuffworks.com','411-705-4407'),
('garrick','terris',str_to_date('02.02.06','%d.%m.%y'),3413,'gterris27@mail.ru','785-119-7876'),
('marj','bushen',str_to_date('13.05.15','%d.%m.%y'),3446,'mbushen28@cnn.com','310-287-9319'),
('tyne','hansana',str_to_date('24.01.10','%d.%m.%y'),3801,'thansana29@princeton.edu','122-170-4637'),
('tiffany','dods',str_to_date('19.02.03','%d.%m.%y'),3650,'tdods2a@scientificamerican.com','130-281-6451'),
('giana','going',str_to_date('09.01.13','%d.%m.%y'),4455,'ggoing2b@engadget.com','528-911-5297'),
('sophia','dilleston',str_to_date('21.10.16','%d.%m.%y'),2045,'sdilleston2c@admin.ch','785-759-9052'),
('magda','cranson',str_to_date('08.11.09','%d.%m.%y'),2865,'mcranson2d@weebly.com','834-580-2237'),
('bartel','leale',str_to_date('30.01.08','%d.%m.%y'),4946,'bleale2e@uiuc.edu','350-770-9162'),
('wiatt','abella',str_to_date('17.07.05','%d.%m.%y'),3376,'wabella2f@chronoengine.com','130-789-9513'),
('monte','hassewell',str_to_date('17.02.14','%d.%m.%y'),4115,'mhassewell2g@huffingtonpost.com','164-677-4772'),
('raviv','hunt',str_to_date('25.09.06','%d.%m.%y'),3127,'rhunt2h@gmpg.org','162-608-6145'),
('sephira','lovel',str_to_date('19.06.09','%d.%m.%y'),4870,'slovel2i@goodreads.com','435-452-1786'),
('daffi','willingham',str_to_date('23.11.16','%d.%m.%y'),4665,'dwillingham2j@slate.com','313-820-7613'),
('jo ann','cardenas',str_to_date('22.07.12','%d.%m.%y'),4771,'jcardenas2k@wikia.com','223-662-7057'),
('ginni','wayvill',str_to_date('29.01.08','%d.%m.%y'),4600,'gwayvill2l@europa.eu','946-770-4080'),
('sheppard','bernth',str_to_date('14.07.14','%d.%m.%y'),3839,'sbernth2m@pcworld.com','684-362-1870'),
('hesther','stanborough',str_to_date('31.12.12','%d.%m.%y'),2046,'hstanborough2n@army.mil','916-392-7072'),
('anne','spellar',str_to_date('30.06.13','%d.%m.%y'),4023,'aspellar2o@behance.net','660-953-4237'),
('mayne','maccardle',str_to_date('03.07.07','%d.%m.%y'),4121,'mmaccardle2p@go.com','885-231-9642'),
('saunder','leward',str_to_date('01.08.03','%d.%m.%y'),3352,'sleward2q@usgs.gov','476-555-2648'),
('libbie','vines',str_to_date('27.07.05','%d.%m.%y'),3578,'lvines2r@issuu.com','600-733-4718'),
('gracie','prestner',str_to_date('21.09.19','%d.%m.%y'),4999,'gprestner2s@youtu.be','306-761-2549'),
('fredek','monteath',str_to_date('28.04.11','%d.%m.%y'),2196,'fmonteath2t@spiegel.de','661-620-4314'),
('frants','caughan',str_to_date('12.03.18','%d.%m.%y'),2896,'fcaughan2u@arizona.edu','213-141-2766'),
('glennis','gath',str_to_date('16.08.03','%d.%m.%y'),2050,'ggath2v@free.fr','211-586-8272'),
('brand','kuhnwald',str_to_date('29.07.11','%d.%m.%y'),3757,'bkuhnwald2w@ifeng.com','962-102-8682'),
('mab','tuckerman',str_to_date('15.09.03','%d.%m.%y'),2225,'mtuckerman2x@people.com.cn','552-865-8375'),
('tobie','worsell',str_to_date('01.03.04','%d.%m.%y'),3341,'tworsell2y@dot.gov','717-940-5661'),
('amby','prall',str_to_date('10.05.17','%d.%m.%y'),3770,'aprall2z@buzzfeed.com','577-631-9468'),
('deonne','bail',str_to_date('26.05.06','%d.%m.%y'),4783,'dbail30@rediff.com','336-873-7952'),
('donny','burless',str_to_date('17.05.15','%d.%m.%y'),4537,'dburless31@posterous.com','904-614-8736'),
('silas','cordeau]',str_to_date('07.08.10','%d.%m.%y'),4832,'scordeau32@drupal.org','772-728-8904'),
('billy','iskow',str_to_date('09.04.06','%d.%m.%y'),2661,'biskow33@webnode.com','156-655-3848'),
('jaymee','birtley',str_to_date('24.05.09','%d.%m.%y'),4653,'jbirtley34@qq.com','131-814-3367'),
('chloris','rosenthal',str_to_date('06.02.16','%d.%m.%y'),3575,'crosenthal35@meetup.com','374-569-5752'),
('prue','kynd',str_to_date('26.05.03','%d.%m.%y'),2877,'pkynd36@elegantthemes.com','273-263-4203'),
('hatty','ducaen',str_to_date('30.12.18','%d.%m.%y'),3007,'hducaen37@yellowpages.com','933-135-9280'),
('ricky','joule',str_to_date('11.01.06','%d.%m.%y'),3094,'rjoule38@123-reg.co.uk','756-902-7269'),
('willette','allden',str_to_date('09.09.10','%d.%m.%y'),3856,'wallden39@livejournal.com','298-606-7372'),
('ede','ruane',str_to_date('31.08.07','%d.%m.%y'),3199,'eruane3a@posterous.com','281-552-2027'),
('jobi','stockell',str_to_date('17.04.15','%d.%m.%y'),3009,'jstockell3b@google.ca','920-916-2449'),
('sallyann','kaley',str_to_date('09.03.14','%d.%m.%y'),3704,'skaley3c@sakura.ne.jp','610-493-5781'),
('bayard','macgilmartin',str_to_date('15.01.07','%d.%m.%y'),4030,'bmacgilmartin3d@loc.gov','909-381-0220'),
('joanne','littlefair',str_to_date('26.10.14','%d.%m.%y'),3678,'jlittlefair3e@gizmodo.com','125-748-4008'),
('parry','werner',str_to_date('10.08.12','%d.%m.%y'),3345,'pwerner3f@tumblr.com','523-602-5639'),
('avigdor','dohr',str_to_date('13.12.05','%d.%m.%y'),2889,'adohr3g@feedburner.com','312-252-7918'),
('meghan','hanhardt',str_to_date('20.12.14','%d.%m.%y'),2192,'mhanhardt3h@microsoft.com','315-955-1257'),
('duffy','lownie',str_to_date('26.03.07','%d.%m.%y'),2508,'dlownie3i@godaddy.com','422-735-3998'),
('osborne','issacoff',str_to_date('19.07.07','%d.%m.%y'),3825,'oissacoff3j@sfgate.com','776-522-0261'),
('rahal','dewhirst',str_to_date('09.04.15','%d.%m.%y'),3651,'rdewhirst3k@bravesites.com','143-597-9189'),
('marylynne','gentzsch',str_to_date('03.08.05','%d.%m.%y'),2997,'mgentzsch3l@sitemeter.com','790-341-9184'),
('raff','ridgley',str_to_date('23.10.12','%d.%m.%y'),3011,'rridgley3m@photobucket.com','221-830-9063'),
('sammy','labram',str_to_date('19.03.09','%d.%m.%y'),4517,'slabram3n@ycombinator.com','450-705-8316'),
('wallache','thistleton',str_to_date('22.07.08','%d.%m.%y'),3858,'wthistleton3o@phpbb.com','482-434-1896'),
('mallorie','showell',str_to_date('22.02.10','%d.%m.%y'),4133,'mshowell3p@toplist.cz','580-569-6120'),
('scottie','prestland',str_to_date('03.11.05','%d.%m.%y'),2950,'sprestland3q@123-reg.co.uk','290-468-1062'),
('cordi','pickworth',str_to_date('09.11.10','%d.%m.%y'),3499,'cpickworth3r@theatlantic.com','367-318-4014'),
('merv','zavattari',str_to_date('15.04.03','%d.%m.%y'),2874,'mzavattari3s@chronoengine.com','469-752-1191'),
('abner','gaucher',str_to_date('09.08.13','%d.%m.%y'),4744,'agaucher3t@msu.edu','625-964-1654'),
('conroy','dutson',str_to_date('06.09.15','%d.%m.%y'),3561,'cdutson3u@creativecommons.org','431-929-4448'),
('timothee','bastable',str_to_date('01.04.11','%d.%m.%y'),2350,'tbastable3v@biglobe.ne.jp','375-297-4511'),
('schuyler','landman',str_to_date('16.06.09','%d.%m.%y'),3902,'slandman3w@sakura.ne.jp','692-982-6129'),
('humberto','devons',str_to_date('13.03.08','%d.%m.%y'),4270,'hdevons3x@chronoengine.com','190-300-0030'),
('caspar','corriea',str_to_date('17.02.04','%d.%m.%y'),3620,'ccorriea3y@tripadvisor.com','918-359-5015'),
('lowell','mcdonnell',str_to_date('15.09.16','%d.%m.%y'),2928,'lmcdonnell3z@trellian.com','321-375-6597'),
('henrieta','shirley',str_to_date('03.07.13','%d.%m.%y'),2470,'hshirley40@weebly.com','995-606-1329'),
('dene','foystone',str_to_date('06.12.09','%d.%m.%y'),3238,'dfoystone41@ed.gov','402-134-2499'),
('janie','vanlint',str_to_date('27.03.06','%d.%m.%y'),3351,'jvanlint42@foxnews.com','619-937-8795'),
('hatti','kingdon',str_to_date('18.11.10','%d.%m.%y'),4305,'hkingdon43@walmart.com','467-663-5017'),
('agosto','wolver',str_to_date('28.09.08','%d.%m.%y'),2888,'awolver44@wufoo.com','584-208-9249') ,
('delainey','cloke',str_to_date('25.08.17','%d.%m.%y'),4342,'dcloke45@microsoft.com','688-270-2546'),
('ignacius','hewins',str_to_date('07.10.11','%d.%m.%y'),3158,'ihewins46@tinyurl.com','712-270-1241'),
('kirsteni','gittens',str_to_date('15.01.17','%d.%m.%y'),4800,'kgittens47@ning.com','361-908-2267'),
('york','martinet',str_to_date('13.09.09','%d.%m.%y'),3354,'ymartinet48@liveinternet.ru','275-101-6539'),
('lothario','osipenko',str_to_date('26.11.19','%d.%m.%y'),4702,'losipenko49@nytimes.com','443-462-1248'),
('jeremy','northley',str_to_date('08.12.04','%d.%m.%y'),4151,'jnorthley4a@adobe.com','937-723-5400'),
('karalee','winspire',str_to_date('27.10.11','%d.%m.%y'),2818,'kwinspire4b@mapy.cz','298-144-1876'),
('delphine','yesinov',str_to_date('11.06.16','%d.%m.%y'),4089,'dyesinov4c@free.fr','243-768-4524'),
('rodney','darnell',str_to_date('16.08.05','%d.%m.%y'),2817,'rdarnell4d@google.com.hk','519-698-9991'),
('leslie','blaylock',str_to_date('16.03.08','%d.%m.%y'),3255,'lblaylock4e@biglobe.ne.jp','376-681-1107'),
('tomasine','blunsom',str_to_date('12.11.12','%d.%m.%y'),4775,'tblunsom4f@va.gov','354-117-9754'),
('trix','otson',str_to_date('09.04.08','%d.%m.%y'),4554,'totson4g@oracle.com','591-776-8884'),
('devin','tacker',str_to_date('27.04.15','%d.%m.%y'),3104,'dtacker4h@abc.net.au','642-366-4356'),
('ree','verrechia',str_to_date('18.10.19','%d.%m.%y'),4753,'rverrechia4i@vistaprint.com','519-868-2482'),
('cynde','alabaster',str_to_date('22.08.04','%d.%m.%y'),3735,'calabaster4j@wsj.com','904-740-8031'),
('benni','maccurley',str_to_date('23.09.15','%d.%m.%y'),4167,'bmaccurley4k@ibm.com','317-812-9803'),
('mattie','huikerby',str_to_date('22.05.17','%d.%m.%y'),4900,'mhuikerby4l@dropbox.com','748-991-3646'),
('carmon','lowey',str_to_date('27.10.05','%d.%m.%y'),2530,'clowey4m@is.gd','133-405-4671'),
('sullivan','godthaab',str_to_date('01.10.08','%d.%m.%y'),3667,'sgodthaab4n@deliciousdays.com','975-311-4606'),
('raye','patek',str_to_date('31.12.05','%d.%m.%y'),3112,'rpatek4o@shop-pro.jp','627-657-9173'),
('hyacinthe','pulster',str_to_date('13.03.16','%d.%m.%y'),2864,'hpulster4p@domainmarket.com','778-506-5834'),
('gallagher','mccorkell',str_to_date('17.03.03','%d.%m.%y'),4036,'gmccorkell4q@census.gov','921-144-3744'),
('bettina','scaife',str_to_date('28.10.05','%d.%m.%y'),2149,'bscaife4r@squarespace.com','779-935-8804'),
('broddie','stean',str_to_date('11.03.03','%d.%m.%y'),3304,'bstean4s@pbs.org','352-925-2055'),
('alvera','brill',str_to_date('20.02.10','%d.%m.%y'),3799,'abrill4t@blogs.com','394-270-7143'),
('laney','dwelley',str_to_date('06.03.14','%d.%m.%y'),2972,'ldwelley4u@livejournal.com','892-640-0855'),
('daisie','kewley',str_to_date('03.08.13','%d.%m.%y'),2536,'dkewley4v@google.co.uk','572-250-3698'),
('hildy','tomaszek',str_to_date('21.10.04','%d.%m.%y'),2086,'htomaszek4w@bravesites.com','414-416-9334'),
('cliff','amos',str_to_date('09.08.14','%d.%m.%y'),4065,'camos4x@smh.com.au','655-724-1382'),
('ellissa','guly',str_to_date('30.08.16','%d.%m.%y'),3555,'eguly4y@biblegateway.com','479-366-3091'),
('jourdan','groundwator',str_to_date('06.12.12','%d.%m.%y'),3059,'jgroundwator4z@loc.gov','119-292-5355'),
('emogene','feldharker',str_to_date('12.12.03','%d.%m.%y'),4243,'efeldharker50@utexas.edu','127-280-5468'),
('ulla','rennebeck',str_to_date('14.07.11','%d.%m.%y'),3971,'urennebeck51@telegraph.co.uk','747-426-5301'),
('mable','airth',str_to_date('27.03.06','%d.%m.%y'),2488,'mairth52@cpanel.net','910-451-0240'),
('port','diviny',str_to_date('27.12.04','%d.%m.%y'),2892,'pdiviny53@salon.com','685-487-3669'),
('vivia','mccathy',str_to_date('21.08.11','%d.%m.%y'),3539,'vmccathy54@narod.ru','536-360-6119'),
('desiri','claffey',str_to_date('02.09.16','%d.%m.%y'),4175,'dclaffey55@clickbank.net','946-562-0616'),
('frances','rous',str_to_date('02.08.07','%d.%m.%y'),2816,'frous56@wordpress.org','251-176-5196'),
('malvin','neary',str_to_date('07.09.18','%d.%m.%y'),2486,'mneary57@google.fr','465-960-7256'),
('carolyn','cutmare',str_to_date('28.08.07','%d.%m.%y'),3183,'ccutmare58@freewebs.com','921-540-7182'),
('tamarra','cosbey',str_to_date('25.11.14','%d.%m.%y'),2630,'tcosbey59@microsoft.com','614-317-5375'),
('cammy','fellon',str_to_date('16.11.19','%d.%m.%y'),3163,'cfellon5a@booking.com','879-641-1921'),
('elane','ditt',str_to_date('24.12.06','%d.%m.%y'),3714,'editt5b@tiny.cc','343-294-6880'),
('smitty','polly',str_to_date('24.02.08','%d.%m.%y'),4975,'spolly5c@indiegogo.com','214-250-0969'),
('normie','bracknall',str_to_date('21.08.10','%d.%m.%y'),3136,'nbracknall5d@archive.org','729-946-7555'),
('theodosia','sheilds',str_to_date('07.07.14','%d.%m.%y'),3336,'tosheilds5e@netvibes.com','300-492-7679'),
('addie','scimonelli',str_to_date('07.05.14','%d.%m.%y'),3383,'ascimonelli5f@mapy.cz','710-172-9069'),
('garwood','kielt',str_to_date('18.05.10','%d.%m.%y'),2407,'gkielt5g@furl.net','820-398-3195'),
('tabatha','alyonov',str_to_date('26.11.06','%d.%m.%y'),3853,'talyonov5h@parallels.com','333-184-2713'),
('dallas','trussell',str_to_date('06.09.09','%d.%m.%y'),2914,'dtrussell5i@cmu.edu','603-804-3688'),
('rory','entreis',str_to_date('01.10.06','%d.%m.%y'),4020,'rentreis5j@nationalgeographic.com','804-907-7189'),
('niel','jacobowits',str_to_date('05.12.17','%d.%m.%y'),3018,'njacobowits5k@un.org','643-974-3826'),
('june','lambertson',str_to_date('14.04.04','%d.%m.%y'),2772,'jlambertson5l@liveinternet.ru','306-766-1090'),
('kylie','reekie',str_to_date('20.08.08','%d.%m.%y'),3170,'kreekie5m@wordpress.org','704-166-2789'),
('arly','santarelli',str_to_date('13.01.07','%d.%m.%y'),3253,'asantarelli5n@de.vu','697-447-0523'),
('camella','blazeby',str_to_date('22.04.06','%d.%m.%y'),3302,'cblazeby5o@symantec.com','827-252-4512'),
('joel','crookall',str_to_date('09.02.15','%d.%m.%y'),4860,'jcrookall5p@altervista.org','146-223-0789'),
('lowe','robbins',str_to_date('03.04.11','%d.%m.%y'),2678,'lrobbins5q@ibm.com','991-629-8606'),
('hyacinthe','parry',str_to_date('19.03.11','%d.%m.%y'),4332,'hparry5r@sitemeter.com','101-887-5579'),
('teirtza','bohman',str_to_date('26.06.11','%d.%m.%y'),2498,'tbohman5s@gnu.org','951-804-4591'),
('cybill','redborn',str_to_date('26.03.04','%d.%m.%y'),2722,'credborn5t@technorati.com','131-415-4937'),
('vinnie','mates',str_to_date('03.02.08','%d.%m.%y'),3029,'vmates5u@state.tx.us','164-909-2338'),
('cathyleen','cumberledge',str_to_date('26.09.10','%d.%m.%y'),2165,'ccumberledge5v@technorati.com','665-735-9249'),
('suellen','brandli',str_to_date('22.07.06','%d.%m.%y'),3710,'sbrandli5w@about.com','813-271-6116'),
('judd','boor',str_to_date('02.06.18','%d.%m.%y'),4686,'jboor5x@eepurl.com','209-112-7313'),
('lorrie','mackaile',str_to_date('17.07.16','%d.%m.%y'),2910,'lmackaile5y@ocn.ne.jp','260-715-9819'),
('augie','gulk',str_to_date('12.09.10','%d.%m.%y'),4637,'agulk5z@cmu.edu','125-242-4038'),
('sorcha','hallward',str_to_date('13.12.10','%d.%m.%y'),2855,'shallward60@yellowpages.com','545-437-2690'),
('gavrielle','deluze',str_to_date('16.06.07','%d.%m.%y'),3927,'gdeluze61@twitter.com','583-425-5633'),
('burnaby','aldritt',str_to_date('02.11.03','%d.%m.%y'),2905,'baldritt62@odnoklassniki.ru','577-375-1569'),
('ernestus','dempsey',str_to_date('18.05.17','%d.%m.%y'),2796,'edempsey63@theguardian.com','736-380-4868'),
('hannah','almeida',str_to_date('16.06.03','%d.%m.%y'),2073,'hdalmeida64@multiply.com','647-356-6439'),
('skipp','danigel',str_to_date('31.07.14','%d.%m.%y'),2288,'sdanigel65@nasa.gov','374-279-7943'),
('briant','gregr',str_to_date('13.02.05','%d.%m.%y'),3769,'bgregr66@flavors.me','448-532-0415'),
('delora','dayley',str_to_date('10.03.19','%d.%m.%y'),3197,'ddayley67@domainmarket.com','518-834-8198'),
('kipp','otterwell',str_to_date('08.08.14','%d.%m.%y'),4385,'kotterwell68@photobucket.com','485-951-3559'),
('rianon','pigdon',str_to_date('28.11.08','%d.%m.%y'),3398,'rpigdon69@techcrunch.com','879-270-3876'),
('mehetabel','clawley',str_to_date('31.10.10','%d.%m.%y'),3232,'mclawley6a@icio.us','827-932-1227'),
('mab','annand',str_to_date('15.01.10','%d.%m.%y'),3675,'mannand6b@yandex.ru','799-902-9692'),
('sutton','bothen',str_to_date('27.06.19','%d.%m.%y'),4017,'sbothen6c@webeden.co.uk','204-941-8449'),
('georgine','woodyatt',str_to_date('06.12.17','%d.%m.%y'),4215,'gwoodyatt6d@fda.gov','907-295-2537'),
('daveta','drew-clifton',str_to_date('30.08.11','%d.%m.%y'),4937,'ddrewclifton6e@google.com.hk','835-952-0943'),
('arny','mutimer',str_to_date('18.06.07','%d.%m.%y'),2150,'amutimer6f@nymag.com','487-797-9108'),
('barr','carn',str_to_date('08.02.17','%d.%m.%y'),2088,'bcarn6g@microsoft.com','658-918-8538'),
('lucinda','huntington',str_to_date('23.08.08','%d.%m.%y'),3910,'lhuntington6h@blogspot.com','704-554-3374'),
('enrichetta','fitzroy',str_to_date('04.08.14','%d.%m.%y'),4880,'efitzroy6i@gravatar.com','599-279-4051'),
('orelle',' timony',str_to_date('29.11.12','%d.%m.%y'),4955,'ootimony6j@sitemeter.com','439-334-3671'),
('zelig','braddock',str_to_date('26.05.05','%d.%m.%y'),2664,'zbraddock6k@creativecommons.org','695-996-9348'),
('moritz','heinsius',str_to_date('12.11.15','%d.%m.%y'),3001,'mheinsius6l@blogtalkradio.com','282-917-0188'),
('lenna','marte',str_to_date('04.03.11','%d.%m.%y'),2503,'lmarte6m@home.pl','126-272-5423'),
('sidoney','kimbley',str_to_date('13.04.14','%d.%m.%y'),3701,'skimbley6n@yale.edu','368-451-4626'),
('spence','wardhaugh',str_to_date('24.03.07','%d.%m.%y'),4697,'swardhaugh6o@sbwire.com','389-620-2921'),
('griff','torrisi',str_to_date('08.01.06','%d.%m.%y'),4095,'gtorrisi6p@merriam-webster.com','733-879-5226'),
('mada','papaminas',str_to_date('26.12.16','%d.%m.%y'),4633,'mpapaminas6q@imageshack.us','312-150-9375'),
('trudi','farn',str_to_date('04.01.08','%d.%m.%y'),3045,'tfarn6r@xrea.com','219-710-9457'),
('misti','ranklin',str_to_date('24.06.12','%d.%m.%y'),2462,'mranklin6s@storify.com','450-569-3261'),
('janeen','farland',str_to_date('02.06.14','%d.%m.%y'),3897,'jfarland6t@trellian.com','738-594-1639'),
('talya','challinor',str_to_date('20.09.10','%d.%m.%y'),4972,'tchallinor6u@prlog.org','501-986-8988'),
('frankie','warmisham',str_to_date('31.05.05','%d.%m.%y'),2507,'fwarmisham6v@cafepress.com','537-835-7567'),
('erinna','newlin',str_to_date('20.01.16','%d.%m.%y'),3571,'enewlin6w@foxnews.com','701-725-6831'),
('arte','courvert',str_to_date('19.06.13','%d.%m.%y'),4476,'acourvert6x@liveinternet.ru','789-102-4232'),
('drew','kelso',str_to_date('26.02.18','%d.%m.%y'),2153,'dkelso6y@pen.io','951-631-6053'),
('derrek','halliwell',str_to_date('20.07.09','%d.%m.%y'),4684,'dhalliwell6z@admin.ch','455-246-5603'),
('dalila','rosenwasser',str_to_date('19.06.07','%d.%m.%y'),3916,'drosenwasser70@wikia.com','588-630-5409'),
('xerxes','atton',str_to_date('21.02.06','%d.%m.%y'),4601,'xatton71@businesswire.com','947-596-9022'),
('bettina','birchill',str_to_date('26.12.06','%d.%m.%y'),3351,'bbirchill72@oracle.com','206-578-8043'),
('cammy','mcfall',str_to_date('20.07.13','%d.%m.%y'),4011,'cmcfall73@typepad.com','860-370-2463'),
('caralie','manwell',str_to_date('16.03.13','%d.%m.%y'),3540,'cmanwell74@godaddy.com','705-433-0746'),
('candis','kennermann',str_to_date('07.10.09','%d.%m.%y'),3157,'ckennermann75@wikimedia.org','376-144-5098'),
('amy','ells',str_to_date('01.05.07','%d.%m.%y'),4563,'aells76@umich.edu','366-720-4884'),
('orly','baguley',str_to_date('03.11.12','%d.%m.%y'),3931,'obaguley77@huffingtonpost.com','907-866-3301'),
('maire','pringle',str_to_date('22.03.15','%d.%m.%y'),2824,'mpringle78@cloudflare.com','445-411-8478'),
('edgardo','thomen',str_to_date('12.11.19','%d.%m.%y'),4594,'ethomen79@163.com','367-903-9452'),
('brander','serle',str_to_date('24.07.13','%d.%m.%y'),2280,'bserle7a@jimdo.com','879-521-8922'),
('vaughan','simnel',str_to_date('26.03.12','%d.%m.%y'),2068,'vsimnel7b@jalbum.net','630-359-8617'),
('luca','joseland',str_to_date('25.04.03','%d.%m.%y'),4058,'ljoseland7c@sohu.com','251-603-3011'),
('alvin','tobias',str_to_date('02.12.18','%d.%m.%y'),4234,'atobias7d@vistaprint.com','789-193-5138'),
('dannel','coopland',str_to_date('26.02.15','%d.%m.%y'),2295,'dcoopland7e@prlog.org','957-827-6899'),
('dave','extal',str_to_date('22.05.12','%d.%m.%y'),3319,'dextal7f@prnewswire.com','558-385-0339'),
('pall','witton',str_to_date('24.01.10','%d.%m.%y'),2037,'pwitton7g@psu.edu','957-831-2478'),
('jamison','yokel',str_to_date('03.07.13','%d.%m.%y'),3898,'jyokel7h@yellowpages.com','924-511-4641'),
('dougy','lardge',str_to_date('04.02.15','%d.%m.%y'),3425,'dlardge7i@google.it','408-472-6961'),
('troy','hacket',str_to_date('27.03.03','%d.%m.%y'),3133,'thacket7j@reuters.com','613-975-7268'),
('ladonna','jeckells',str_to_date('09.09.08','%d.%m.%y'),3803,'ljeckells7k@netscape.com','755-265-7507'),
('currey','eckh',str_to_date('10.11.08','%d.%m.%y'),2278,'ceckh7l@symantec.com','243-769-0577'),
('phedra','archell',str_to_date('10.07.07','%d.%m.%y'),2515,'parchell7m@hatena.ne.jp','187-808-8577'),
('leda','ghioni',str_to_date('15.04.17','%d.%m.%y'),4771,'lghioni7n@icio.us','851-433-6915'),
('clarice','graham',str_to_date('23.05.17','%d.%m.%y'),4258,'cgraham7o@tripadvisor.com','564-338-1801'),
('juli','sheriff',str_to_date('19.01.05','%d.%m.%y'),4429,'jsheriff7p@usa.gov','298-305-2056'),
('deeann','sayburn',str_to_date('17.05.06','%d.%m.%y'),4509,'dsayburn7q@ucoz.ru','359-524-3554'),
('meryl','pickavant',str_to_date('06.03.17','%d.%m.%y'),2111,'mpickavant7r@multiply.com','342-985-0943'),
('steve','bonder',str_to_date('19.04.09','%d.%m.%y'),4870,'sbonder7s@weather.com','874-767-1075'),
('cal','creelman',str_to_date('14.07.07','%d.%m.%y'),2503,'ccreelman7t@cnn.com','780-100-5024'),
('marice','butterley',str_to_date('03.06.08','%d.%m.%y'),3640,'mbutterley7u@wordpress.org','967-833-6443'),
('sansone','alves',str_to_date('07.02.06','%d.%m.%y'),2939,'salves7v@t.co','897-414-2448'),
('bartlett','devonald',str_to_date('12.12.11','%d.%m.%y'),2685,'bdevonald7w@seattletimes.com','316-141-2668'),
('cobb','ivins',str_to_date('22.02.05','%d.%m.%y'),3929,'civins7x@seattletimes.com','528-508-7562'),
('marillin','soppit',str_to_date('03.04.03','%d.%m.%y'),2702,'msoppit7y@nydailynews.com','266-523-7958'),
('merilee','seeger',str_to_date('28.04.17','%d.%m.%y'),3113,'mseeger7z@amazon.com','388-939-9366'),
('troy','hacket',str_to_date('27.03.03','%d.%m.%y'),3133,'thacket7j@reuters.com','613-975-7268'),
('ladonna','jeckells',str_to_date('09.09.08','%d.%m.%y'),3803,'ljeckells7k@netscape.com','755-265-7507'),
('currey','eckh',str_to_date('10.11.08','%d.%m.%y'),2278,'ceckh7l@symantec.com','243-769-0577'),
('phedra','archell',str_to_date('10.07.07','%d.%m.%y'),2515,'parchell7m@hatena.ne.jp','187-808-8577'),
('leda','ghioni',str_to_date('15.04.17','%d.%m.%y'),4771,'lghioni7n@icio.us','851-433-6915'),
('clarice','graham',str_to_date('23.05.17','%d.%m.%y'),4258,'cgraham7o@tripadvisor.com','564-338-1801'),
('juli','sheriff',str_to_date('19.01.05','%d.%m.%y'),4429,'jsheriff7p@usa.gov','298-305-2056'),
('deeann','sayburn',str_to_date('17.05.06','%d.%m.%y'),4509,'dsayburn7q@ucoz.ru','359-524-3554'),
('meryl','pickavant',str_to_date('06.03.17','%d.%m.%y'),2111,'mpickavant7r@multiply.com','342-985-0943'),
('steve','bonder',str_to_date('19.04.09','%d.%m.%y'),4870,'sbonder7s@weather.com','874-767-1075'),
('cal','creelman',str_to_date('14.07.07','%d.%m.%y'),2503,'ccreelman7t@cnn.com','780-100-5024'),
('marice','butterley',str_to_date('03.06.08','%d.%m.%y'),3640,'mbutterley7u@wordpress.org','967-833-6443');


insert into
biuro_podrozy.credentials
  (login,  pass_hash,  privilege, employeeid)
values
  -- hash of password : passwd1
  ("manager_1", '2C69A0416BB8AA4A03F12734987F34D154E3964E',2,1),
  -- hash of password : passwd2
  ("employee_1", '96E7C231A54050DFA9571101979A6201CA3C2A18',1,2),
  -- hash of password : passwd3
  ("employee_2", '4B6BB75317F7D15EB8926F76DF7ABCDE276E80DA',1,3),
  -- hash of password : passwd4
  ("employee_3", '072774747BD9E7D0E2EE9DBCAFAECD74D1620816',1,4);


insert into biuro_podrozy.customers
  (pesel,name,surname,email)
values
 (92121963645,'dannie','blockey','dblockey0@paginegialle.it'),
 (91102158153,'philippine','bosson','pbosson1@cdc.gov'),
 (98050322889,'york','penwarden','ypenwarden2@360.cn'),
 (95052933721,'gene','trouel','gtrouel3@hexun.com'),
 (99022565682,'martainn','arman','marman4@posterous.com'),
 (92020595486,'larry','winterborne','lwinterborne5@arizona.edu'),
 (90050252168,'homere','garlette','hgarlette6@qq.com'),
 (97011076793,'ardella','reilly','areilly7@icio.us'),
 (94080542457,'rudyard','wackley','rwackley8@mtv.com'),
 (98030772446,'normand','mckiernan','nmckiernan9@opensource.org'),
 (89101558418,'lani','stather','lstathera@nydailynews.com'),
 (89101417784,'marya','tissington','mtissingtonb@blog.com'),
 (94030687722,'tally','elgram','telgramc@aol.com'),
 (88080188937,'josi','bottomer','jbottomerd@youtu.be'),
 (97121452733,'garwood','rainsbury','grainsburye@nbcnews.com'),
 (98102239284,'odey','alanbrooke','oalanbrookef@state.tx.us'),
 (97062677264,'bobette','babalola','bbabalolag@etsy.com'),
 (90010258184,'monty','choffin','mchoffinh@zdnet.com'),
 (98011073223,'mechelle','redsall','mredsalli@technorati.com'),
 (96030416843,'margaretta','revening','mreveningj@nsw.gov.au'),
 (89080529461,'godiva','flaverty','goflavertyk@e-recht24.de'),
 (97080435826,'elene','storcke','estorckel@yolasite.com'),
 (94050161963,'mischa','spearman','mspearmanm@cdc.gov'),
 (94010862686,'dee','de courcey','ddecourceyn@tiny.cc'),
 (89122078342,'roma','dickens','rdickenso@java.com'),
 (98021051271,'ermentrude','benedettini','ebenedettinip@domainmarket.com'),
 (89092288664,'galvin','gowler','ggowlerq@bloglines.com'),
 (96110822636,'deb','macmenamie','dmacmenamier@scribd.com'),
 (91090545573,'goldina','giurio','ggiurios@dailymotion.com'),
 (95021446881,'miltie','clair','mclairt@adobe.com'),
 (93062845924,'gabriel','van geffen','gvangeffenu@privacy.gov.au'),
 (92060171444,'mordecai','alster','malsterv@wired.com'),
 (95072238873,'vasilis','kobisch','vkobischw@scribd.com'),
 (97021033294,'vita','malley','vomalleyx@seesaa.net'),
 (89121966686,'gradey','baylie','gbayliey@intel.com'),
 (95020152279,'stormi','wolton','swoltonz@newsvine.com'),
 (89102474993,'esmaria','gerold','egerold10@rakuten.co.jp'),
 (91092712931,'cheston','bartolacci','cbartolacci11@house.gov'),
 (94050388922,'diandra','bickerstaff','dbickerstaff12@about.com'),
 (94110773815,'tuckie','colbert','tcolbert13@nps.gov'),
 (88110752572,'andria','pantone','apantone14@huffingtonpost.com'),
 (98081599852,'georas','clayworth','gclayworth15@berkeley.edu'),
 (98032861881,'alwin','munnings','amunnings16@topsy.com'),
 (93011253936,'ame','kramer','akramer17@cbslocal.com'),
 (92122481674,'hildegaard','south','hsouth18@rediff.com'),
 (92070353698,'doralia','ommundsen','dommundsen19@moonfruit.com'),
 (96111617442,'davin','smeeton','dsmeeton1a@yandex.ru'),
 (93032626724,'viv','macgillacolm','vmacgillacolm1b@stumbleupon.com'),
 (95093018812,'matthias','gaudon','mgaudon1c@census.gov'),
 (99051769721,'dietrich','prettejohns','dprettejohns1d@howstuffworks.com'),
 (92022381742,'filippo','bonsey','fbonsey1e@huffingtonpost.com'),
 (91010366974,'farand','degoey','fdegoey1f@bandcamp.com'),
 (93120288294,'christine','giordano','cgiordano1g@engadget.com'),
 (90080238994,'chelsae','yoell','cyoell1h@vimeo.com'),
 (96010124414,'gaultiero','gores','ggores1i@uiuc.edu'),
 (92040717664,'vannie','zamorano','vzamorano1j@wikispaces.com'),
 (96053062227,'krispin','barck','kbarck1k@naver.com'),
 (90102518817,'bar','cheeney','bcheeney1l@cpanel.net'),
 (96111151337,'hedda','drewitt','hdrewitt1m@fc2.com'),
 (95052716281,'guthrie','arthur','garthur1n@npr.org'),
 (88031717924,'karla','flatley','kflatley1o@clickbank.net'),
 (94051299829,'kissiah','chasson','kchasson1p@slate.com'),
 (94022889442,'ernestine','peacham','epeacham1q@dailymail.co.uk'),
 (89092878335,'cecil','swinglehurst','cswinglehurst1r@slate.com'),
 (88101013969,'bessy','moneti','bmoneti1s@51.la'),
 (90082565487,'nikki','delahunt','ndelahunt1t@soup.io'),
 (96112415988,'minna','schuh','mschuh1u@goo.ne.jp'),
 (90041339737,'magdalena','haugen','mhaugen1v@sohu.com'),
 (95011284558,'kippie','ebbin','kebbin1w@canalblog.com'),
 (89121982398,'grace','trill','gtrill1x@usgs.gov'),
 (96110523889,'shirlee','crippes','scrippes1y@sciencedaily.com'),
 (99040828213,'boyce','osborn','bosborn1z@cloudflare.com'),
 (94080785982,'ives','arkill','iarkill20@odnoklassniki.ru'),
 (93082042873,'jakie','samsonsen','jsamsonsen21@aol.com'),
 (93010952539,'lionello','gynne','lgynne22@bigcartel.com'),
 (96070319577,'mandel','baggaley','mbaggaley23@cafepress.com'),
 (96110912388,'koressa','kiley','kkiley24@hp.com'),
 (88072715277,'frederique','sooley','fsooley25@cnn.com'),
 (94031112911,'rosmunda','flips','rflips26@ifeng.com'),
 (91020669542,'sissy','geraldo','sgeraldo27@slideshare.net'),
 (91031084343,'dene','mullinder','dmullinder28@salon.com'),
 (93100583168,'gonzales','well','gwell29@tinypic.com'),
 (97032158377,'elston','deble','edeble2a@shinystat.com'),
 (92111724694,'murray','cheel','mcheel2b@time.com'),
 (92070832788,'melly','wabey','mwabey2c@thetimes.co.uk'),
 (90091663682,'isa','yesinov','iyesinov2d@narod.ru'),
 (89022347913,'sonja','cullnean','scullnean2e@simplemachines.org'),
 (88092971499,'claire','bullingham','cbullingham2f@discuz.net'),
 (96052056632,'sondra','bossom','sbossom2g@quantcast.com'),
 (88110573339,'carlina','jacson','cjacson2h@prlog.org'),
 (89050866413,'wiatt','goodwins','wgoodwins2i@hexun.com'),
 (88062157261,'deane','paoletto','dpaoletto2j@networksolutions.com'),
 (92081091123,'eirena','attew','eattew2k@webnode.com'),
 (94120276876,'susie','bristo','sbristo2l@engadget.com'),
 (98062088515,'fae','cleaver','fcleaver2m@yahoo.co.jp'),
 (90092897749,'scottie','carek','scarek2n@prlog.org'),
 (95110376817,'maryrose','tytherton','mtytherton2o@latimes.com'),
 (97021364769,'teri','crooke','tcrooke2p@sitemeter.com'),
 (91102375471,'steve','de la perrelle','sdelaperrelle2q@ask.com'),
 (95063061817,'sayre','brookwell','sbrookwell2r@1688.com'),
 (98030957579,'orran','lulham','olulham2s@skyrock.com'),
 (89071641358,'raoul','brasseur','rbrasseur2t@sohu.com'),
 (92022093562,'stillmann','ducker','sducker2u@discovery.com'),
 (89120732161,'pall','chattell','pchattell2v@vkontakte.ru'),
 (95030526679,'chaunce','baus','cbaus2w@flickr.com'),
 (99052792333,'jason','just','jjust2x@whitehouse.gov'),
 (98110724321,'alon','mccamish','amccamish2y@tmall.com'),
 (91120618334,'marylynne','smalridge','msmalridge2z@example.com'),
 (89041298274,'jenifer','vockings','jvockings30@altervista.org'),
 (97053192916,'iorgos','littleton','ilittleton31@comcast.net'),
 (92081442486,'orran','titford','otitford32@mapquest.com'),
 (90032457187,'arlie','benion','abenion33@arizona.edu'),
 (91042667465,'emile','fleg','efleg34@hhs.gov'),
 (98121826511,'enrica','mcduff','emcduff35@yellowbook.com'),
 (88081381162,'ninnetta','grimes','ngrimes36@github.com'),
 (96031978946,'guthry','pursglove','gpursglove37@fastcompany.com'),
 (88060613316,'guillemette','byng','gbyng38@mit.edu'),
 (97020941749,'sloane','hampshaw','shampshaw39@people.com.cn'),
 (98051227824,'errol','gredden','egredden3a@mapy.cz'),
 (92041851949,'billie','vogeller','bvogeller3b@fotki.com'),
 (89062388491,'birgit','swiffin','bswiffin3c@tripadvisor.com'),
 (88040223487,'annmarie','gosson','agosson3d@vistaprint.com'),
 (89021882879,'gardener','hurdman','ghurdman3e@barnesandnoble.com'),
 (94052984669,'scotti','teaser','steaser3f@shareasale.com'),
 (88111569249,'keely','sotham','ksotham3g@dedecms.com'),
 (92010846345,'conrado','brazer','cbrazer3h@vk.com'),
 (91111734348,'joshuah','jakubiak','jjakubiak3i@yahoo.co.jp'),
 (99022882167,'jake','mcaulay','jmcaulay3j@bizjournals.com'),
 (96062519875,'regine','hovee','rhovee3k@diigo.com'),
 (95012424577,'court','sommer','csommer3l@blogtalkradio.com'),
 (96061026659,'ericka','lygoe','elygoe3m@globo.com'),
 (90020698741,'galina','amiranda','gamiranda3n@reference.com'),
 (98082688779,'davida','merfin','dmerfin3o@tmall.com'),
 (88122752885,'lennard','schuchmacher','lschuchmacher3p@mysql.com'),
 (93090724918,'alie','gianullo','agianullo3q@ask.com'),
 (97020386812,'coletta','crozier','ccrozier3r@flickr.com'),
 (95120239867,'johnny','entissle','jentissle3s@forbes.com'),
 (91100289442,'sonya','drabble','sdrabble3t@vk.com'),
 (98123132113,'tibold','mcsporon','tmcsporon3u@jigsy.com'),
 (88061119842,'edie','stallion','estallion3v@kickstarter.com'),
 (98061914453,'jacinthe','bohlens','jbohlens3w@va.gov'),
 (94020757545,'dulcine','knoller','dknoller3x@loc.gov'),
 (94071691227,'karalynn','maith','kmaith3y@imdb.com'),
 (94060451313,'kitty','lesek','klesek3z@geocities.com'),
 (98100163954,'starla','mcalister','smcalister40@nps.gov'),
 (99012347164,'berke','sindle','bsindle41@goodreads.com'),
 (95070125278,'fanchette','maylott','fmaylott42@storify.com'),
 (96042843594,'jilly','menendez','jmenendez43@nsw.gov.au'),
 (90050328773,'shayna','moreman','smoreman44@webs.com'),
 (90040597868,'daryle','scarffe','dscarffe45@cdbaby.com'),
 (97092089321,'raina','hyde-chambers','rhydechambers46@canalblog.com'),
 (91040175579,'rowan','kiltie','rkiltie47@typepad.com'),
 (97102756834,'lemar','kruschov','lkruschov48@mashable.com'),
 (89011339486,'yvette','petriello','ypetriello49@usgs.gov'),
 (95010488793,'alric','burril','aburril4a@census.gov'),
 (93110112398,'donnajean','danilowicz','ddanilowicz4b@zdnet.com'),
 (88072115855,'abbey','areles','aareles4c@usatoday.com'),
 (94122342281,'marielle','selkirk','mselkirk4d@digg.com'),
 (90060157754,'maddy','scardifield','mscardifield4e@tamu.edu'),
 (97021866322,'paten','lax','plax4f@t.co'),
 (97082456364,'paulo','misken','pmisken4g@paginegialle.it'),
 (96022941665,'saudra','roskam','sroskam4h@pagesperso-orange.fr'),
 (93121511548,'tully','pendell','tpendell4i@a8.net'),
 (92093038565,'gibbie','voysey','gvoysey4j@ucoz.ru'),
 (93092634882,'trudi','giacobilio','tgiacobilio4k@hibu.com'),
 (95021767933,'janie','dunstall','jdunstall4l@pagesperso-orange.fr'),
 (88060624372,'kaitlynn','spendley','kspendley4m@ftc.gov'),
 (89052599788,'gratiana','shepcutt','gshepcutt4n@ucla.edu'),
 (92021166441,'sergio','bellord','sbellord4o@jigsy.com'),
 (96011875319,'trisha','charke','tcharke4p@yahoo.com'),
 (94070241935,'adria','bramhill','abramhill4q@tmall.com'),
 (96072535274,'rollins','poulsen','rpoulsen4r@1688.com'),
 (92010784539,'jecho','barniss','jbarniss4s@yahoo.co.jp'),
 (98120124245,'armand','trenouth','atrenouth4t@cargocollective.com'),
 (93081277438,'heath','iredale','hiredale4u@ehow.com'),
 (98081173432,'dorena','reach','dreach4v@nsw.gov.au'),
 (90070777159,'wynn','ibbs','wibbs4w@europa.eu'),
 (93010471478,'prescott','bollon','pbollon4x@tuttocitta.it'),
 (95100929786,'grantham','lorain','glorain4y@studiopress.com'),
 (92120824648,'emelen','garham','egarham4z@ca.gov'),
 (92111374745,'sean','taverner','staverner50@nsw.gov.au'),
 (93020953227,'carolus','crannach','ccrannach51@discuz.net'),
 (98041819367,'tabina','lackmann','tlackmann52@usa.gov'),
 (98031332827,'teodora','de la perrelle','tdelaperrelle53@mtv.com'),
 (95062156695,'marena','navein','mnavein54@weebly.com'),
 (90021293853,'hannah','caulton','hcaulton55@freewebs.com'),
 (90102979333,'doy','allabush','dallabush56@furl.net'),
 (93062376967,'halie','gridley','hgridley57@google.com.br'),
 (98091694794,'jess','evennett','jevennett58@webeden.co.uk'),
 (91042197452,'kelcy','lorenzo','klorenzo59@is.gd'),
 (90010893794,'judie','bentote','jbentote5a@blogtalkradio.com'),
 (98043099851,'ellen','shillan','eshillan5b@example.com'),
 (88010887617,'harwell','burcher','hburcher5c@utexas.edu'),
 (98062331927,'jaquenette','brownill','jbrownill5d@amazon.co.jp'),
 (92030965127,'biddie','durrand','bdurrand5e@whitehouse.gov'),
 (96120763633,'brandtr','straffon','bstraffon5f@cbslocal.com'),
 (94101486849,'elspeth','nashe','enashe5g@wunderground.com'),
 (94061192413,'bridgette','clingoe','bclingoe5h@harvard.edu'),
 (94120487454,'bertram','kislingbury','bkislingbury5i@pbs.org'),
 (97013129369,'teodoro','ansty','tansty5j@unesco.org'),
 (93082697646,'deeann','arnopp','darnopp5k@hibu.com'),
 (92091845693,'tori','dauney','tdauney5l@time.com'),
 (97042131856,'giraud','crosgrove','gcrosgrove5m@tinyurl.com'),
 (88091996477,'ive','rubinsztein','irubinsztein5n@seattletimes.com'),
 (97030623691,'hamilton','grigoriev','hgrigoriev5o@multiply.com'),
 (91091447836,'murry','frill','mfrill5p@flickr.com'),
 (97071999418,'milton','cadman','mcadman5q@xinhuanet.com'),
 (88080287667,'julita','catterell','jcatterell5r@dedecms.com'),
 (90052681353,'arden','laimable','alaimable5s@ow.ly'),
 (96072213794,'merlina','valek','mvalek5t@ocn.ne.jp'),
 (89053086564,'penny','neeson','pneeson5u@1688.com'),
 (97030577327,'mack','renshaw','mrenshaw5v@mapy.cz'),
 (94122889582,'rena','mckay','rmckay5w@telegraph.co.uk'),
 (97082064497,'spike','syder','ssyder5x@homestead.com'),
 (88121923653,'sephira','mcgilmartin','smcgilmartin5y@sciencedirect.com'),
 (97040214623,'tillie','lettice','tlettice5z@gnu.org'),
 (91061125513,'larisa','stickney','lstickney60@amazon.co.jp'),
 (91020239712,'sheffie','hardaker','shardaker61@technorati.com'),
 (97012838842,'cris','brend','cbrend62@bigcartel.com'),
 (97070963339,'henka','martinez','hmartinez63@opensource.org'),
 (93081045495,'gaven','giblett','ggiblett64@google.com.au'),
 (96060336289,'derrek','cosgry','dcosgry65@issuu.com'),
 (96050355863,'crystal','mcgillreich','cmcgillreich66@nhs.uk'),
 (90061736659,'terri','yarnall','tyarnall67@squidoo.com'),
 (89052272937,'shae','jennison','sjennison68@vkontakte.ru'),
 (89052945862,'parry','postans','ppostans69@businesswire.com'),
 (92020668425,'bill','lowings','blowings6a@naver.com'),
 (92072886266,'willie','ricardin','wricardin6b@fotki.com'),
 (94080824812,'lennard','beiderbeck','lbeiderbeck6c@shop-pro.jp'),
 (88123176936,'henderson','askell','haskell6d@spiegel.de'),
 (92111587417,'lia','goldthorp','lgoldthorp6e@stumbleupon.com'),
 (92090158943,'osbourne','chasmoor','ochasmoor6f@163.com'),
 (88092228843,'luelle','mandre','lmandre6g@example.com'),
 (97122877717,'caleb','redihalgh','credihalgh6h@google.com.au'),
 (89031266654,'nanine','mardlin','nmardlin6i@godaddy.com'),
 (97030335336,'filberto','foxhall','ffoxhall6j@odnoklassniki.ru'),
 (95020723693,'kippy','figin','kfigin6k@photobucket.com'),
 (95010196939,'clemmie','enever','cenever6l@icio.us'),
 (89061993638,'mathe','campe','mcampe6m@newsvine.com'),
 (94041049683,'kassie','smale','ksmale6n@npr.org'),
 (88123136378,'agnola','woodwind','awoodwind6o@about.me'),
 (88013066475,'magdalena','mckeighan','mmckeighan6p@tinypic.com'),
 (96012869395,'sybil','lakey','slakey6q@delicious.com'),
 (88080547826,'alice','woolard','awoolard6r@acquirethisname.com'),
 (99040684725,'ilise','grundle','igrundle6s@hubpages.com'),
 (99050161586,'cati','toone','ctoone6t@reuters.com'),
 (94071424232,'hendrika','pidon','hpidon6u@google.co.jp'),
 (88082136419,'inglebert','ensor','iensor6v@icio.us'),
 (96043086868,'shawnee','praill','spraill6w@is.gd'),
 (94112897278,'simonne','endricci','sendricci6x@youtu.be'),
 (98060146237,'terra','fishwick','tfishwick6y@360.cn'),
 (89110735279,'waylan','spaven','wspaven6z@un.org'),
 (98070663878,'tymon','jakeman','tjakeman70@senate.gov'),
 (98082039346,'arvin','martinolli','amartinolli71@tmall.com'),
 (95062326935,'early','elix','eelix72@theatlantic.com'),
 (96111326641,'tomlin','pockey','tpockey73@mit.edu'),
 (88032782899,'marji','eskriett','meskriett74@people.com.cn'),
 (97101714565,'giraldo','ancell','gancell75@bbb.org'),
 (89101181597,'ferne','hacquoil','fhacquoil76@multiply.com'),
 (94051131192,'osborn','valentine','ovalentine77@fda.gov'),
 (88012244854,'mateo','alison','malison78@360.cn'),
 (92101383357,'abey','gwyther','agwyther79@quantcast.com'),
 (97041337369,'page','marthen','pmarthen7a@elpais.com'),
 (97040189141,'clim','babbidge','cbabbidge7b@yale.edu'),
 (89020522857,'nichole','godart','ngodart7c@nps.gov'),
 (89051623499,'morris','ragot','mragot7d@moonfruit.com'),
 (89102773788,'marmaduke','wims','mwims7e@posterous.com'),
 (96082438394,'tammi','falconbridge','tfalconbridge7f@mediafire.com'),
 (98021191874,'otto','melmeth','omelmeth7g@skype.com'),
 (95010397996,'sergeant','ruckledge','sruckledge7h@indiatimes.com'),
 (89110743621,'albertine','paddick','apaddick7i@cocolog-nifty.com'),
 (94102058843,'kipper','denyagin','kdenyagin7j@t-online.de'),
 (96101799826,'eric','feighney','efeighney7k@unicef.org'),
 (94110397664,'edgar','peirpoint','epeirpoint7l@oaic.gov.au'),
 (90022897957,'davidde','darlaston','ddarlaston7m@blog.com'),
 (93012314894,'morgan','sherel','msherel7n@discovery.com'),
 (92072698557,'marcellina','clout','mclout7o@umn.edu'),
 (95082589628,'verena','reding','vreding7p@dot.gov'),
 (94082851953,'dill','davley','ddavley7q@umn.edu'),
 (98063061597,'packston','wrixon','pwrixon7r@salon.com'),
 (91030869431,'huey','brockington','hbrockington7s@amazon.de'),
 (88052931653,'sascha','hatherley','shatherley7t@imageshack.us'),
 (91081024388,'xymenes','cowx','xcowx7u@squarespace.com'),
 (95122476943,'jean','cartwight','jcartwight7v@discovery.com'),
 (93091313625,'tyne','bortoloni','tbortoloni7w@biglobe.ne.jp'),
 (93090614635,'salaidh','mozzi','smozzi7x@cnbc.com'),
 (96100493813,'ulrica','stoakley','ustoakley7y@ftc.gov'),
 (98052064941,'marla','undrell','mundrell7z@ezinearticles.com'),
 (97121395236,'layla','darell','ldarell80@bigcartel.com'),
 (93082589211,'melvin','durrett','mdurrett81@wsj.com'),
 (94092094144,'cammy','kobel','ckobel82@instagram.com'),
 (98121081198,'kara-lynn','foulstone','kfoulstone83@forbes.com'),
 (98112873641,'karena','lamberto','klamberto84@imgur.com'),
 (96092892838,'rayshell','rodliff','rrodliff85@google.com.hk'),
 (94072986441,'reuben','orton','rorton86@macromedia.com'),
 (93102742822,'jordon','juliano','jjuliano87@sun.com'),
 (91051099435,'stefan','plan','splan88@eepurl.com'),
 (90090699329,'vanny','hinksen','vhinksen89@amazon.de'),
 (98032532578,'sunshine','kapelhoff','skapelhoff8a@ameblo.jp'),
 (88120797419,'tabby','tedahl','ttedahl8b@skype.com'),
 (92030474339,'robbin','feria','rferia8c@yale.edu'),
 (92020291849,'matty','etherington','metherington8d@topsy.com'),
 (96083154622,'lazarus','wheway','lwheway8e@jigsy.com'),
 (94051488768,'bernadine','lillicrop','blillicrop8f@bloglines.com'),
 (92052927134,'darb','vanderson','dvanderson8g@cdc.gov'),
 (92082287747,'barton','kenworthy','bkenworthy8h@seesaa.net'),
 (89111833792,'bev','symon','bsymon8i@go.com'),
 (89061987844,'rakel','keizman','rkeizman8j@example.com'),
 (98051299421,'anna-maria','attard','aattard8k@chron.com'),
 (96041567518,'laina','deuss','ldeuss8l@parallels.com'),
 (96110386626,'latrena','billett','lbillett8m@go.com'),
 (92052114958,'ronni','benyon','rbenyon8n@hhs.gov'),
 (94062794454,'sonni','gilloran','sgilloran8o@wikispaces.com'),
 (92101448227,'jermayne','holleran','jholleran8p@biglobe.ne.jp'),
 (89042637838,'nikolaos','croix','ncroix8q@psu.edu'),
 (99032767467,'brena','piser','bpiser8r@canalblog.com'),
 (89110213887,'dewey','fynes','dfynes8s@washingtonpost.com'),
 (93042895699,'maison','lilleman','mlilleman8t@cornell.edu'),
 (95043076349,'nestor','mcquillin','nmcquillin8u@parallels.com'),
 (93062394121,'antonio','kensett','akensett8v@acquirethisname.com'),
 (93022595931,'charley','gini','cgini8w@mediafire.com'),
 (89043093181,'krystal','johannesson','kjohannesson8x@hhs.gov'),
 (90051487943,'ryon','sember','rsember8y@1688.com'),
 (92090875471,'shelden','arnli','sarnli8z@cisco.com'),
 (93081069976,'ingemar','ziemke','iziemke90@independent.co.uk'),
 (93081624964,'gabie','buy','gbuy91@printfriendly.com'),
 (88031242534,'hamlen','janousek','hjanousek92@weibo.com'),
 (89031372131,'margi','leaburn','mleaburn93@cbc.ca'),
 (96020437849,'annabal','bixley','abixley94@cdc.gov'),
 (98070271123,'codi','cordrey','ccordrey95@exblog.jp'),
 (89122249775,'brice','hastwell','bhastwell96@usnews.com'),
 (99062025887,'guinevere','heskey','gheskey97@icio.us'),
 (99011573638,'melitta','orrice','morrice98@woothemes.com'),
 (88080865555,'nan','van daalen','nvandaalen99@cdbaby.com'),
 (93030221259,'tiphani','mapes','tmapes9a@nyu.edu'),
 (97030636475,'clotilda','jeste','cjeste9b@vinaora.com'),
 (93062777836,'stevie','gilpillan','sgilpillan9c@icq.com'),
 (95101384694,'christiano','enrrico','cenrrico9d@fastcompany.com'),
 (96012522272,'robbert','drysdall','rdrysdall9e@vistaprint.com'),
 (90070164311,'trixy','heaffey','theaffey9f@paypal.com'),
 (93042221487,'devland','remmers','dremmers9g@xrea.com'),
 (91021343722,'hortensia','manlow','hmanlow9h@walmart.com'),
 (96121469866,'alick','chitter','achitter9i@dyndns.org'),
 (96021464219,'annalee','boult','aboult9j@wiley.com'),
 (96122161132,'cullin','kirstein','ckirstein9k@ifeng.com'),
 (94120727327,'georgina','macsharry','gmacsharry9l@fc2.com'),
 (95061842971,'mick','loeber','mloeber9m@washington.edu'),
 (98100438784,'florian','conaghan','fconaghan9n@bloglines.com'),
 (97062617952,'ty','haggus','thaggus9o@rambler.ru'),
 (91012944358,'tobin','gunningham','tgunningham9p@sphinn.com'),
 (93042424941,'irena','mowsley','imowsley9q@scientificamerican.com'),
 (95102423998,'rosie','grzegorek','rgrzegorek9r@theatlantic.com'),
 (88072115329,'theobald','godfree','tgodfree9s@ibm.com'),
 (98010734918,'melisent','zanetello','mzanetello9t@youtu.be'),
 (95122137675,'susy','torvey','storvey9u@house.gov'),
 (97012223576,'emalee','mcging','emcging9v@bizjournals.com'),
 (88090947634,'desi','connor','dconnor9w@jigsy.com'),
 (99061582895,'abelard','mateja','amateja9x@slashdot.org'),
 (94090266693,'petronille','heino','pheino9y@usa.gov'),
 (96041031136,'penn','magenny','pmagenny9z@sun.com'),
 (89051651267,'christan','strodder','cstroddera0@cornell.edu'),
 (95112577513,'antonie','faughey','afaugheya1@bing.com'),
 (97100174616,'devora','yanov','dyanova2@wix.com'),
 (98121232839,'niels','extal','nextala3@macromedia.com'),
 (99021659834,'riccardo','bolino','rbolinoa4@ehow.com'),
 (89082217555,'hester','aveling','havelinga5@is.gd'),
 (93050295782,'colette','grafom','cgrafoma6@dagondesign.com'),
 (94031597758,'kendricks','salvidge','ksalvidgea7@dot.gov'),
 (89122429858,'alfy','pietsma','apietsmaa8@newyorker.com'),
 (90012357157,'constantine','ligerton','cligertona9@nasa.gov'),
 (94072923273,'mersey','ketchell','mketchellaa@boston.com'),
 (96032275448,'merle','delamar','mdelamarab@blogspot.com'),
 (98092687434,'alicea','while','awhileac@pagesperso-orange.fr'),
 (99041888685,'laurella','moine','lmoinead@issuu.com'),
 (91122444241,'tannie','ridler','tridlerae@theatlantic.com'),
 (92111991955,'phyllis','byrch','pbyrchaf@wisc.edu'),
 (94101615919,'emlyn','silversmidt','esilversmidtag@reuters.com'),
 (98020922994,'melina','vanshin','mvanshinah@scientificamerican.com'),
 (99021919352,'gauthier','dran','gdranai@mashable.com'),
 (92071991514,'cathleen','jarry','cjarryaj@independent.co.uk'),
 (98121781289,'corella','ould','couldak@123-reg.co.uk'),
 (96091036785,'asia','offill','aoffillal@eepurl.com'),
 (95092332258,'lynnea','josey','ljoseyam@surveymonkey.com'),
 (94050826699,'brucie','grogan','bgroganan@comcast.net'),
 (92103062753,'cory','maccart','cmaccartao@ask.com'),
 (93020659246,'corilla','johl','cjohlap@studiopress.com'),
 (88102914467,'cindi','harbor','charboraq@scientificamerican.com'),
 (88032237962,'randell','jencken','rjenckenar@youku.com'),
 (98122657684,'deva','cranmer','dcranmeras@mayoclinic.com'),
 (98110192441,'lisha','lefort','llefortat@eepurl.com'),
 (97080453356,'freeland','weins','fweinsau@about.com'),
 (94040892466,'kendal','baleine','kbaleineav@qq.com'),
 (95012242614,'haze','nozzolii','hnozzoliiaw@globo.com'),
 (92101034666,'benoit','titcom','btitcomax@howstuffworks.com'),
 (98061864864,'konrad','risbrough','krisbroughay@nature.com'),
 (90092198215,'wildon','lenormand','wlenormandaz@twitter.com'),
 (94081576633,'dwight','tomowicz','dtomowiczb0@uol.com.br'),
 (98101749498,'griff','jayes','gjayesb1@goodreads.com'),
 (95011747653,'josh','wheeliker','jwheelikerb2@ft.com'),
 (99020873112,'morse','hickinbottom','mhickinbottomb3@state.gov'),
 (96092571434,'francesco','rhydderch','frhydderchb4@sakura.ne.jp'),
 (99040885393,'gusty','tincey','gtinceyb5@irs.gov'),
 (97052945874,'keeley','dunbobbin','kdunbobbinb6@craigslist.org'),
 (89100782157,'edeline','viegas','eviegasb7@arstechnica.com'),
 (90062755639,'bunni','mitchel','bmitchelb8@so-net.ne.jp'),
 (88103048961,'austine','siddons','asiddonsb9@ebay.co.uk'),
 (98080295681,'malena','bartelot','mbartelotba@sitemeter.com'),
 (98010152637,'jerri','colquite','jcolquitebb@cpanel.net'),
 (94012196787,'maiga','dinan','mdinanbc@globo.com'),
 (89020679863,'josiah','robinson','jrobinsonbd@comcast.net'),
 (89050479824,'fritz','wenzel','fwenzelbe@admin.ch'),
 (89102632573,'silva','joinson','sjoinsonbf@narod.ru'),
 (94012095765,'ali','ship','ashipbg@state.tx.us'),
 (92082424436,'chad','coppens','ccoppensbh@washingtonpost.com'),
 (96020853191,'sallyanne','jaggli','sjagglibi@hibu.com'),
 (89030888297,'bendicty','neville','bnevillebj@moonfruit.com'),
 (97050412213,'tobe','joblin','tjoblinbk@wikipedia.org'),
 (94121025936,'fredek','foli','ffolibl@symantec.com'),
 (99060271976,'danika','bromage','dbromagebm@kickstarter.com'),
 (95092797778,'jolyn','sidey','jsideybn@bluehost.com'),
 (88101169875,'nevsa','ducker','nduckerbo@t-online.de'),
 (95040928939,'fara','hebborn','fhebbornbp@blogs.com'),
 (89012865225,'celestine','houten','choutenbq@ask.com'),
 (95050188598,'marianne','shrimplin','mshrimplinbr@desdev.cn'),
 (96060318391,'stephani','chislett','schislettbs@ucoz.ru'),
 (95020556714,'susana','ebbens','sebbensbt@squidoo.com'),
 (97101285715,'hayden','bucksey','hbuckseybu@edublogs.org'),
 (89081045443,'hildagard','traher','htraherbv@vistaprint.com'),
 (88100596856,'lorita','gallafant','lgallafantbw@oaic.gov.au'),
 (90091886951,'gaspar','dominy','gdominybx@e-recht24.de'),
 (99011655839,'sharai','kunisch','skunischby@yahoo.co.jp'),
 (94010522775,'lamont','crofthwaite','lcrofthwaitebz@cargocollective.com'),
 (93020736718,'christy','becraft','cbecraftc0@pagesperso-orange.fr'),
 (94063083382,'jacinthe','gouny','jgounyc1@wix.com'),
 (96052494241,'bell','ahearne','bahearnec2@springer.com'),
 (90030198891,'nedi','crosson','ncrossonc3@ameblo.jp'),
 (91012288188,'mignon','troyes','mtroyesc4@blog.com'),
 (93070413256,'guinevere','feaveer','gfeaveerc5@biblegateway.com'),
 (92082644498,'bonita','guare','bguarec6@topsy.com'),
 (88093011145,'mordy','dalinder','mdalinderc7@ezinearticles.com'),
 (98032251114,'bondon','klosa','bklosac8@apache.org'),
 (95060894696,'annis','blacksell','ablacksellc9@paginegialle.it'),
 (91083023989,'truman','brecon','tbreconca@google.it'),
 (88041978331,'lexis','jagoe','ljagoecb@free.fr'),
 (90070533166,'stevana','learoyde','slearoydecc@about.me'),
 (95051378727,'morgen','alliott','malliottcd@twitpic.com'),
 (90072532927,'silvester','gow','sgowce@163.com'),
 (91122293784,'aguie','longhurst','alonghurstcf@ask.com'),
 (89020214879,'deane','ledwich','dledwichcg@wsj.com'),
 (92112036941,'fey','wintersgill','fwintersgillch@csmonitor.com'),
 (96101439896,'minni','avrahm','mavrahmci@nhs.uk'),
 (96082272624,'staci','filppetti','sfilppetticj@google.ru'),
 (95050923393,'finlay','tibbs','ftibbsck@wordpress.com'),
 (88110865643,'aloysia','longland','alonglandcl@youku.com'),
 (95121712462,'laurena','mcvanamy','lmcvanamycm@bloomberg.com'),
 (96103126842,'nanny','zavittieri','nzavittiericn@delicious.com'),
 (94012176316,'inga','norrington','inorringtonco@ft.com'),
 (89092878496,'kelby','addekin','kaddekincp@shop-pro.jp'),
 (89081083764,'lynea','shrive','lshrivecq@skype.com'),
 (88090679146,'neale','ghion','nghioncr@reverbnation.com'),
 (97080112369,'rowe','skidmore','rskidmorecs@rakuten.co.jp'),
 (97011227328,'eal','shrawley','eshrawleyct@chronoengine.com'),
 (94050837631,'valentijn','gillbe','vgillbecu@rakuten.co.jp'),
 (92040343456,'dorree','phillpot','dphillpotcv@uiuc.edu'),
 (99052322273,'wyn','mcalinion','wmcalinioncw@dyndns.org'),
 (95100173819,'jeffie','costa','jdcostacx@google.ca'),
 (91021971998,'marys','haime','mhaimecy@is.gd'),
 (89042542716,'tiena','cowin','tcowincz@technorati.com'),
 (97080122119,'omero','mckeady','omckeadyd0@berkeley.edu'),
 (88011579898,'elvin','allenby','eallenbyd1@macromedia.com'),
 (94021346634,'eloise','fabri','efabrid2@sphinn.com'),
 (95041156571,'starlene','caygill','scaygilld3@yahoo.com'),
 (92061291453,'reggie','greenough','rgreenoughd4@technorati.com'),
 (97031685447,'nisse','kroger','nkrogerd5@admin.ch'),
 (99012585885,'danella','waple','dwapled6@statcounter.com'),
 (97071124232,'mechelle','jaffray','mjaffrayd7@altervista.org'),
 (97040295628,'jourdain','baine','jbained8@eepurl.com'),
 (95022318817,'georgy','ecclestone','gecclestoned9@fc2.com'),
 (97082656719,'thain','pinnock','tpinnockda@washingtonpost.com'),
 (94050934369,'terence','boylin','tboylindb@state.tx.us'),
 (90050148935,'calli','rawsthorn','crawsthorndc@quantcast.com'),
 (93012153655,'ingeborg','jon','ijondd@zdnet.com'),
 (91082695169,'drusi','handling','dhandlingde@cbslocal.com'),
 (93062834661,'vinnie','twinberrow','vtwinberrowdf@w3.org'),
 (92052327682,'frayda','boscher','fboscherdg@uol.com.br'),
 (91071885528,'harry','gerrey','hgerreydh@marriott.com'),
 (96122929851,'freemon','bracknall','fbracknalldi@reuters.com'),
 (90051796281,'emmanuel','duro','edurodj@ihg.com'),
 (98031524691,'beaufort','gronow','bgronowdk@ezinearticles.com'),
 (95110541862,'faye','macdirmid','fmacdirmiddl@booking.com'),
 (97060912769,'marion','strafford','mstrafforddm@storify.com'),
 (96080134414,'tomasina','treasure','ttreasuredn@edublogs.org'),
 (97050697124,'maridel','rogez','mrogezdo@weibo.com'),
 (96042293542,'corette','chant','cchantdp@google.nl'),
 (91042228589,'tye','bollum','tbollumdq@java.com'),
 (94112129713,'candra','eam','ceamdr@nhs.uk'),
 (98062026911,'rosie','hazell','rhazellds@chronoengine.com'),
 (89062314489,'korie','ropking','kropkingdt@google.ru'),
 (88101744371,'petra','macconnel','pmacconneldu@scientificamerican.com'),
 (92030866787,'clementius','eliassen','celiassendv@va.gov'),
 (92073088513,'zitella','bedburrow','zbedburrowdw@nifty.com'),
 (92072167842,'gigi','gorke','ggorkedx@japanpost.jp'),
 (95060118871,'andra','leal','alealdy@istockphoto.com'),
 (90031585748,'edwina','mogridge','emogridgedz@hibu.com'),
 (96101693656,'antone','bees','abeese0@ted.com'),
 (95011824576,'blanca','jiricka','bjirickae1@theglobeandmail.com'),
 (95102543861,'cilka','ladlow','cladlowe2@bandcamp.com'),
 (96013116274,'eadie','dabs','edabse3@yellowpages.com'),
 (94102129453,'benson','braidley','bbraidleye4@sakura.ne.jp'),
 (89042018251,'lyman','bough','lboughe5@sbwire.com'),
 (93032696688,'van','mattia','vmattiae6@omniture.com'),
 (96092462497,'inness','apfel','iapfele7@dagondesign.com'),
 (96100242752,'jacobo','feldmann','jfeldmanne8@mail.ru'),
 (91061061613,'nat','blaxill','nblaxille9@illinois.edu'),
 (98052113157,'isaak','wearne','iwearneea@tmall.com'),
 (98102614526,'grier','zanelli','gzanellieb@studiopress.com'),
 (90090775425,'shaughn','lohmeyer','slohmeyerec@plala.or.jp'),
 (90062311871,'dorian','gheeraert','dgheeraerted@myspace.com'),
 (96012812638,'trenton','dovidian','tdovidianee@ameblo.jp'),
 (91012955338,'consalve','gisborne','cgisborneef@wisc.edu'),
 (98101566381,'karalynn','petkovic','kpetkoviceg@facebook.com'),
 (98052258588,'brennen','sabatier','bsabatiereh@ca.gov'),
 (96031563421,'rodd','offa','roffaei@harvard.edu'),
 (94092579643,'sutherlan','lorenzetto','slorenzettoej@exblog.jp'),
 (90071445781,'ethelind','haacker','ehaackerek@twitter.com'),
 (91030562853,'carlotta','van rembrandt','cvanrembrandtel@abc.net.au'),
 (91072118414,'glennis','gulk','ggulkem@dmoz.org'),
 (97092396926,'alfreda','conachie','aconachieen@sakura.ne.jp'),
 (93121247375,'liv','grigg','lgriggeo@smugmug.com'),
 (89081284769,'brynn','houselee','bhouseleeep@about.me'),
 (92070941442,'ingmar','penquet','ipenqueteq@google.com'),
 (97041561922,'monica','cleverley','mcleverleyer@51.la'),
 (90013113996,'falito','haddy','fhaddyes@wp.com'),
 (91080533775,'dud','jessopp','djessoppet@php.net'),
 (89090831178,'danell','oselton','doseltoneu@i2i.jp'),
 (92010465557,'rand','mattingson','rmattingsonev@tamu.edu'),
 (91032092114,'danielle','smellie','dsmellieew@wp.com'),
 (97043024247,'roderick','crocken','rcrockenex@acquirethisname.com'),
 (95050425666,'lynnette','pellamonuten','lpellamonuteney@goo.gl'),
 (96071274954,'chalmers','necolds','cnecoldsez@intel.com'),
 (96012924166,'karlie','aldwinckle','kaldwincklef0@nydailynews.com'),
 (93100131415,'legra','mcgray','lmcgrayf1@vkontakte.ru'),
 (97101896629,'sheeree','thomassen','sthomassenf2@blogs.com'),
 (94030158811,'mozes','arkcoll','markcollf3@craigslist.org'),
 (89100157656,'zora','benard','zbenardf4@mysql.com'),
 (93090534634,'eda','huburn','ehuburnf5@furl.net'),
 (92022185698,'perren','berford','pberfordf6@hao123.com'),
 (92052245474,'virginie','bradfield','vbradfieldf7@guardian.co.uk'),
 (91111812934,'moshe','roscoe','mroscoef8@bizjournals.com'),
 (96072472122,'mike','samuel','msamuelf9@sciencedirect.com'),
 (97070297524,'hedvig','mcmeekin','hmcmeekinfa@instagram.com'),
 (96090789189,'aeriela','pittham','apitthamfb@alexa.com'),
 (89052393399,'estele','cornillot','ecornillotfc@indiegogo.com'),
 (96052217543,'rosalynd','skehan','rskehanfd@twitter.com'),
 (98031572779,'sanderson','fauguel','sfauguelfe@plala.or.jp'),
 (95090644539,'chiquita','presdie','cpresdieff@typepad.com'),
 (97072743887,'ethyl','gare','egarefg@nifty.com'),
 (98121561678,'carlee','fawdry','cfawdryfh@virginia.edu'),
 (98032262637,'othello','print','oprintfi@oaic.gov.au'),
 (94052259468,'ada','kitchinham','akitchinhamfj@weebly.com'),
 (93022285685,'arin','mackean','amackeanfk@telegraph.co.uk'),
 (98122936312,'robinet','cockran','rcockranfl@ucoz.ru'),
 (91051498586,'georgianna','lemmen','glemmenfm@adobe.com'),
 (94010955898,'kristo','baltzar','kbaltzarfn@icq.com'),
 (90112456354,'barr','suatt','bsuattfo@umn.edu'),
 (97050873777,'morlee','crocumbe','mcrocumbefp@examiner.com'),
 (96092257761,'alverta','sheeryne','aosheerynefq@admin.ch'),
 (94123051878,'anjela','thomsen','athomsenfr@cbc.ca'),
 (93030555284,'vittoria','doogood','vdoogoodfs@uol.com.br'),
 (96080626838,'gabrila','shearn','gshearnft@who.int'),
 (92100265784,'chevalier','dyte','cdytefu@walmart.com'),
 (88091761974,'guinevere','palfery','gpalferyfv@trellian.com'),
 (92102789688,'clemence','geale','cgealefw@blogtalkradio.com'),
 (99012749775,'don','parncutt','dparncuttfx@smugmug.com'),
 (93030863439,'cathlene','linsley','clinsleyfy@spotify.com'),
 (91062619518,'pris','frain','pfrainfz@wiley.com'),
 (94082971772,'doralynn','evequot','devequotg0@omniture.com'),
 (90032979838,'harp','gee','hgeeg1@taobao.com'),
 (95120293555,'lorie','parkyn','lparkyng2@cargocollective.com'),
 (90060996782,'billy','bashford','bbashfordg3@sfgate.com'),
 (96060523614,'henrie','capewell','hcapewellg4@posterous.com'),
 (92031834471,'giuseppe','exley','gexleyg5@cpanel.net'),
 (98102241159,'bron','semarke','bsemarkeg6@opera.com'),
 (94031522486,'denna','brambill','dbrambillg7@theatlantic.com'),
 (96042131996,'lyndsay','pargetter','lpargetterg8@businessinsider.com'),
 (97033177272,'willie','mustin','wmusting9@hexun.com'),
 (92121312241,'yoshiko','jarry','yjarryga@elpais.com'),
 (93120584567,'mickie','garza','mgarzagb@ed.gov'),
 (98011585179,'dina','lycett','dlycettgc@reference.com'),
 (92120124243,'massimiliano','brouncker','mbrounckergd@mozilla.org'),
 (96040518652,'marlon','andersen','mandersenge@umich.edu'),
 (96120869674,'bowie','mcdonnell','bmcdonnellgf@wikimedia.org'),
 (88071443977,'robinet','forrington','rforringtongg@chron.com'),
 (91070799642,'dallas','pye','dpyegh@nba.com'),
 (99053182733,'thebault','marzello','tmarzellogi@google.es'),
 (99050787597,'giovanna','jenne','gjennegj@histats.com'),
 (88103094955,'pierre','nardoni','pnardonigk@google.co.jp'),
 (95112163815,'elayne','driffe','edriffegl@craigslist.org'),
 (95090219674,'gerladina','getcliff','ggetcliffgm@home.pl'),
 (89010119272,'ninette','snowdon','nsnowdongn@thetimes.co.uk'),
 (94033132472,'walton','ollander','wollandergo@wikia.com'),
 (99050487398,'sabina','doherty','sodohertygp@accuweather.com'),
 (90120251198,'darleen','woollett','dwoollettgq@nyu.edu'),
 (89032878735,'malinde','runcieman','mrunciemangr@google.co.uk'),
 (89110776838,'kittie','bisp','kbispgs@nba.com'),
 (95073019675,'floria','bock','fbockgt@google.com'),
 (96032029238,'angus','crame','acramegu@ucsd.edu'),
 (97052587429,'cazzie','arkley','carkleygv@newyorker.com'),
 (94021989679,'randi','todd','rtoddgw@engadget.com'),
 (95042428215,'shantee','marcoolyn','smarcoolyngx@istockphoto.com'),
 (96101593161,'christiane','frain','cfraingy@netvibes.com'),
 (99021652899,'correna','matkovic','cmatkovicgz@answers.com'),
 (95012069545,'adoree','himsworth','ahimsworthh0@hubpages.com'),
 (89053133174,'rhiamon','heggie','rheggieh1@hud.gov'),
 (92042936937,'maddalena','pude','mpudeh2@dell.com'),
 (91041599828,'torrance','rowbottom','trowbottomh3@discuz.net'),
 (90062719723,'elisabetta','touret','etoureth4@opensource.org'),
 (90121676189,'trudey','dami','tdamih5@icio.us'),
 (97042423153,'rosella','andresser','randresserh6@zdnet.com'),
 (95012757617,'egor','licciardi','elicciardih7@flavors.me'),
 (90090463122,'terencio','boumphrey','tboumphreyh8@timesonline.co.uk'),
 (94080257942,'sergeant','dufer','sduferh9@myspace.com'),
 (88082036665,'jeremie','de caville','jdecavilleha@paypal.com'),
 (96092118343,'binni','brookesbie','bbrookesbiehb@opera.com'),
 (93040767321,'cynthy','munning','cmunninghc@wikispaces.com'),
 (98101285989,'claudine','hoolahan','cohoolahanhd@chronoengine.com'),
 (91061793934,'chickie','twinbourne','ctwinbournehe@technorati.com'),
 (97071681775,'courtnay','crathorne','ccrathornehf@nyu.edu'),
 (93032341328,'felicity',' lone','folonehg@bbc.co.uk'),
 (97043097531,'merla','sidey','msideyhh@sciencedirect.com');


insert into biuro_podrozy.offers
  ( name, city, country, date_begin, date_end, price, categoryid, insurance_cost, extra_meals_cost, tickets_count)
values
  ('wycieczka 1','tokio','japonia',str_to_date('14.01.19','%d.%m.%y'),str_to_date('20.01.19','%d.%m.%y'),6412,1,830,393,55),
  ('wycieczka 2','meksyk-city','meksyk',str_to_date('15.01.19','%d.%m.%y'),str_to_date('21.01.19','%d.%m.%y'),4298,4,614,538,55),
  ('wycieczka 3','nowy jork','usa',str_to_date('16.01.19','%d.%m.%y'),str_to_date('22.01.19','%d.%m.%y'),6990,2,795,385,46),
  ('wycieczka 4','kair','egipt',str_to_date('17.01.19','%d.%m.%y'),str_to_date('23.01.19','%d.%m.%y'),5040,4,793,608,52),
  ('wycieczka 5','sao paulo','brazylia',str_to_date('18.01.19','%d.%m.%y'),str_to_date('24.01.19','%d.%m.%y'),4909,2,1320,751,42),
  ('wycieczka 6','seul','korea południowa',str_to_date('19.01.19','%d.%m.%y'),str_to_date('25.01.19','%d.%m.%y'),3101,3,1241,514,45),
  ('wycieczka 7','osaka','japonia',str_to_date('20.01.19','%d.%m.%y'),str_to_date('26.01.19','%d.%m.%y'),4848,3,1079,566,53),
  ('wycieczka 8','los angeles','usa',str_to_date('21.01.19','%d.%m.%y'),str_to_date('27.01.19','%d.%m.%y'),9264,1,1311,461,48),
  ('wycieczka 9','szanghaj','chiny',str_to_date('22.01.19','%d.%m.%y'),str_to_date('28.01.19','%d.%m.%y'),6609,2,1502,563,53),
  ('wycieczka 10','bombaj','indie',str_to_date('14.02.19','%d.%m.%y'),str_to_date('20.02.19','%d.%m.%y'),2584,1,1336,443,57),
  ('wycieczka 11','kalkuta','indie',str_to_date('15.02.19','%d.%m.%y'),str_to_date('21.02.19','%d.%m.%y'),1262,1,596,323,49),
  ('wycieczka 12','czungcing','chiny',str_to_date('16.02.19','%d.%m.%y'),str_to_date('22.02.19','%d.%m.%y'),8596,2,683,312,42),
  ('wycieczka 13','rio de janeiro','brazylia',str_to_date('17.02.19','%d.%m.%y'),str_to_date('23.02.19','%d.%m.%y'),8930,4,1698,325,60),
  ('wycieczka 14','pekin','chiny',str_to_date('18.02.19','%d.%m.%y'),str_to_date('24.02.19','%d.%m.%y'),7771,4,692,750,41),
  ('wycieczka 15','londyn','anglia',str_to_date('19.02.19','%d.%m.%y'),str_to_date('25.02.19','%d.%m.%y'),1086,4,1277,344,58),
  ('wycieczka 16','buenos aires','argentyna',str_to_date('20.02.19','%d.%m.%y'),str_to_date('26.02.19','%d.%m.%y'),7337,3,1664,598,52),
  ('wycieczka 17','bangkok','tajlandia',str_to_date('21.02.19','%d.%m.%y'),str_to_date('27.02.19','%d.%m.%y'),1060,2,699,602,47),
  ('wycieczka 18','stambu','turcja',str_to_date('22.02.19','%d.%m.%y'),str_to_date('28.02.19','%d.%m.%y'),2889,4,677,437,54),
  ('wycieczka 19','teheran','iran',str_to_date('14.05.19','%d.%m.%y'),str_to_date('20.05.19','%d.%m.%y'),7928,2,1434,535,44),
  ('wycieczka 20','djakarta','indonezja',str_to_date('15.05.19','%d.%m.%y'),str_to_date('21.05.19','%d.%m.%y'),3982,2,554,413,58),
  ('wycieczka 21','karaczi','pakistan',str_to_date('16.05.19','%d.%m.%y'),str_to_date('22.05.19','%d.%m.%y'),3691,3,1804,449,52),
  ('wycieczka 22','paryz','francja',str_to_date('17.05.19','%d.%m.%y'),str_to_date('23.05.19','%d.%m.%y'),2584,3,1541,475,49),
  ('wycieczka 23','tiencin','chiny',str_to_date('18.05.19','%d.%m.%y'),str_to_date('24.05.19','%d.%m.%y'),1255,3,1078,434,49),
  ('wycieczka 24','lagos','portugalja',str_to_date('19.05.19','%d.%m.%y'),str_to_date('25.05.19','%d.%m.%y'),9742,1,1706,511,49),
  ('wycieczka 25','delhi','indie',str_to_date('20.05.19','%d.%m.%y'),str_to_date('26.05.19','%d.%m.%y'),1175,2,1961,538,48),
  ('wycieczka 26','chicago','usa',str_to_date('21.05.19','%d.%m.%y'),str_to_date('27.05.19','%d.%m.%y'),3980,2,854,388,50),
  ('wycieczka 27','manila','filipiny',str_to_date('22.05.19','%d.%m.%y'),str_to_date('28.05.19','%d.%m.%y'),7734,3,1890,682,53),
  ('wycieczka 28','moskwa','rosja',str_to_date('14.07.19','%d.%m.%y'),str_to_date('20.07.19','%d.%m.%y'),3356,2,1446,582,42),
  ('wycieczka 29','dhaka','bangladesz',str_to_date('15.07.19','%d.%m.%y'),str_to_date('21.07.19','%d.%m.%y'),7068,3,1055,720,43),
  ('wycieczka 30','czengtu','chiny',str_to_date('16.07.19','%d.%m.%y'),str_to_date('22.07.19','%d.%m.%y'),2745,1,1355,677,58),
  ('wycieczka 31','konurbacja zagłębia ruhry','niemcy',str_to_date('17.07.19','%d.%m.%y'),str_to_date('23.07.19','%d.%m.%y'),8687,2,1229,484,49),
  ('wycieczka 32','shantou','chiny',str_to_date('18.07.19','%d.%m.%y'),str_to_date('24.07.19','%d.%m.%y'),7825,2,1645,357,50),
  ('wycieczka 33','lima - callao','cypr',str_to_date('19.07.19','%d.%m.%y'),str_to_date('25.07.19','%d.%m.%y'),5991,3,1301,563,52),
  ('wycieczka 34','nantong','chiny',str_to_date('20.07.19','%d.%m.%y'),str_to_date('26.07.19','%d.%m.%y'),1411,3,1344,555,59),
  ('wycieczka 35','kanton','chiny',str_to_date('21.07.19','%d.%m.%y'),str_to_date('27.07.19','%d.%m.%y'),2340,3,1682,459,44),
  ('wycieczka 36','waszyngton','usa',str_to_date('22.07.19','%d.%m.%y'),str_to_date('28.07.19','%d.%m.%y'),3009,2,1791,353,44),
  ('wycieczka 37','wuhan','chiny',str_to_date('19.08.19','%d.%m.%y'),str_to_date('25.08.19','%d.%m.%y'),4474,3,1808,387,47),
  ('wycieczka 38','nagoja','japonia',str_to_date('20.08.19','%d.%m.%y'),str_to_date('26.08.19','%d.%m.%y'),5046,4,618,657,51),
  ('wycieczka 39','ibadan','nigeria',str_to_date('21.08.19','%d.%m.%y'),str_to_date('27.08.19','%d.%m.%y'),8616,2,1603,306,45),
  ('wycieczka 40','brasilia','brazylia',str_to_date('22.08.19','%d.%m.%y'),str_to_date('28.08.19','%d.%m.%y'),3363,1,1493,329,50);

create trigger on_new_tour_appear
after insert on biuro_podrozy.tour
for each row
update biuro_podrozy.offers
  set offers.tickets_count = offers.tickets_count - new.reserved_tickets
  where offers.id = new.offerid;


insert into biuro_podrozy.tour
  (offerid, customerid, employeeid, insurance, extra_meals, debt, state, reserved_tickets)
values
  (28,1,41,1,0,1379,1,2),
  (3,2,8,1,1,1062,0,2),
  (5,3,263,1,1,2509,0,3),
  (27,4,286,0,0,1122,0,1),
  (38,5,36,0,0,2381,0,3),
  (4,6,219,0,0,2020,1,4),
  (35,7,235,1,1,1446,0,4);


create trigger on_employee_remove
after delete on biuro_podrozy.employees
for each row
update biuro_podrozy.tour
  set tour.employeeid = null where tour.employeeid = old.id;



delimiter //

create procedure reserve_tour (
  in offerid int,
  in ticket_count int,
  in customerid bigint,
  in employeeid int,
  in insurance int(1),
  in extra_meals int(1)
)
proc_begin:begin
  declare offer_ticket_count int default 0;
  declare offer_insurance_cost int;
  declare offer_extra_meals_cost int;
  declare offer_price int;

  select tickets_count, price, insurance_cost, extra_meals_cost
  into offer_ticket_count, offer_price, offer_insurance_cost, offer_extra_meals_cost
  from offers where offers.id = offerid;

  if offer_ticket_count < ticket_count then
    leave proc_begin;
  end if;

  set offer_price = offer_price*ticket_count;

  if offer_insurance_cost is not null and insurance <> 0 then
    set offer_price = offer_price + offer_insurance_cost*ticket_count;
  end if;

  if offer_extra_meals_cost is not null and extra_meals <> 0 then
    set offer_price = offer_price + offer_extra_meals_cost*ticket_count;
  end if;

  insert into biuro_podrozy.tour
  (offerid, customerid, employeeid, insurance, extra_meals, debt, state, reserved_tickets)
values
  (offerid,customerid,employeeid,insurance,extra_meals,offer_price,0,ticket_count);

end//

create procedure change_employee_tours (
  in from_employee int,
  in to_employee int
)
proc_begin:begin
  if from_employee is null then
      update biuro_podrozy.tour
      set tour.employeeid = to_employee where tour.employeeid is null;
    leave proc_begin;
  end if;

  update biuro_podrozy.tour
     set tour.employeeid = to_employee where tour.employeeid = from_employee;
end//


create procedure resign_from_insurance (
  in tourid int
)
proc_begin:begin
  declare withinsurance int(1);
  declare tour_state int(1);
  declare tour_debt int;
  declare tour_reserved_tickets int;
  declare tour_offerid int;
  declare offer_insurance_cost int;

  select insurance, debt, reserved_tickets, state, offerid
  into withinsurance, tour_debt, tour_reserved_tickets, tour_state, tour_offerid
  from tour where  tour.id = tourid;

  if withinsurance is null or withinsurance = 0 or tour_state = 1 then
    leave proc_begin;
  end if;

  select insurance_cost
  into offer_insurance_cost
  from offers where  offers.id = tour_offerid;

  set tour_debt = tour_debt -  offer_insurance_cost*tour_reserved_tickets;

  update biuro_podrozy.tour
     set
        tour.debt = tour_debt,
        tour.insurance =0
     where tour.id = tourid;
end//


create procedure resign_from_extra_meals (
  in tourid int
)
proc_begin:begin
  declare with_extra_meals int(1);
  declare tour_state int(1);
  declare tour_debt int;
  declare tour_reserved_tickets int;
  declare tour_offerid int;
  declare offer_extra_meals_cost int;

  select extra_meals, debt, reserved_tickets, state, offerid
  into with_extra_meals, tour_debt, tour_reserved_tickets, tour_state, tour_offerid
  from tour where  tour.id = tourid;

  if with_extra_meals is null or with_extra_meals = 0 or tour_state = 1 then
    leave proc_begin;
  end if;

  select extra_meals_cost
  into offer_extra_meals_cost
  from offers where  offers.id = tour_offerid;

  set tour_debt = tour_debt -  offer_extra_meals_cost*tour_reserved_tickets;

  update biuro_podrozy.tour
     set
     tour.debt = tour_debt,
     tour.extra_meals =0
    where tour.id = tourid;
end//

create procedure forget_customer (
  in customerid int,
  out return_value int
)
proc_begin:begin

  declare tours_count int;
  set return_value = 0;
  select count(*)
  into tours_count
  from tour where tour.customerid = customerid and tour.state = 0;
  if tours_count <> 0 then
    set return_value = -1;
    leave proc_begin;
  end if;
  delete from customers where  customers.id = customerid;
end//

create procedure forget_offer (
  in offerid int,
  out return_value int
)
proc_begin:begin

  declare tours_count int;
  set return_value = 0;
  select count(*)
  into tours_count
  from tour where tour.offerid = offerid and tour.state = 0;
  if tours_count <> 0 then
    set return_value = -1;
    leave proc_begin;
  end if;
  delete from offers where  offers.id = offerid;
end//


create procedure modify_offer(
  in offerid int,
  in offname varchar(50),
  in country varchar(50),
  in city varchar(40),
  in date_begin date,
  in date_end date,
  in price int,
  in insurance_cost int,
  in extra_meals_cost int,
  in categoryid int
)
proc_begin:begin
  declare tour_id int;
  declare cost_diff int;
  declare tour_debt int;
  declare tour_insurance int;
  declare tour_extra_meals int;
  declare tour_reserved_count int;
  declare current_insurance_cost int;
  declare current_extra_melas_cost int;
  declare affected_tours_count int;
  declare tour_cursor
    cursor for
   select id, debt, insurance, extra_meals, reserved_tickets from tour
  where  tour.offerid = offerid;

  select offers.insurance_cost, offers.extra_meals_cost
  into current_insurance_cost, current_extra_melas_cost
  from offers where offers.id = offerid;

  open tour_cursor;
  select found_rows() into affected_tours_count;
  if affected_tours_count <> 0 then
    tour_update: loop
      fetch tour_cursor into tour_id, tour_debt, tour_insurance, tour_extra_meals, tour_reserved_count;
      set cost_diff =0;
      if tour_insurance = 0 then
         set  cost_diff = (insurance_cost -current_insurance_cost);
      end if;

      if tour_insurance = 0 then
         set cost_diff = cost_diff + (extra_meals_cost - current_extra_melas_cost);
      end if;
      set cost_diff = cost_diff * tour_reserved_count;

     update biuro_podrozy.tour
      set
        tour.debt = tour_debt + cost_diff
      where  tour.id = tour_id;

    end loop tour_update;
  end if;
  close tour_cursor;

  update biuro_podrozy.offers
     set
      offers.name = offname,
      offers.country = country,
      offers.city = city,
      offers.date_begin = date_begin,
      offers.date_end = date_end,
      offers.price = price,
      offers.insurance_cost = insurance_cost,
      offers.extra_meals_cost = extra_meals_cost,
      offers.categoryid = categoryid
     where offers.id = offerid;
end//

delimiter ;
-- procedura delete client must check if client has any tours and not state
call reserve_tour(1,4,5,1,1,1);
call resign_from_insurance(2);
call resign_from_extra_meals(2);
call resign_from_insurance(2);
call resign_from_extra_meals(2);
call resign_from_insurance(8);
call resign_from_extra_meals(8);
call modify_offer(2,'wycieczka 2','usa','new york',str_to_date('15.01.19','%d.%m.%y'),str_to_date('21.01.19','%d.%m.%y'),4298,614,538,4);

-- pokazanie funkcjionalnosci tirgera
set foreign_key_checks=0;
delete from biuro_podrozy.employees where biuro_podrozy.employees.id =1;
set foreign_key_checks=1;
call change_employee_tours(null, 2);
-- pokazanie naruszania kluczy w kazdej z tabel

-- insert into
-- biuro_podrozy.category (id,  name) values (1, 'last minute');


-- insert into
-- biuro_podrozy.credentials (login,  pass_hash,  account_type) values ("mamanger_1", 'last minute',1);


-- insert into
-- biuro_podrozy.annual_income  (id,year,balance) values (1, str_to_date('1978', '%y'),  -5675);


-- insert into
-- biuro_podrozy.employees  (id,name,surname, hire_date, salary,email,phone_number) values (1,'gerhardine','loghan',str_to_date('30.07.09','%d.%m.%y'),4156,'gloghan0@china.com.cn','765-578-4612');


-- insert into
-- biuro_podrozy.customers  (pesel,name,surname,email) values (92121963645,'dannie','blockey','dblockey0@paginegialle.it');


-- insert into biuro_podrozy.offers
--   (id, name, city, country, date_begin, date_end, price, categoryid, insurance_cost, extra_meals_cost, tickets_count)
-- values
--   (1,'wycieczka 1','tokio','japonia',str_to_date('14.01.19','%d.%m.%y'),str_to_date('20.01.19','%d.%m.%y'),6412,1,830,393,55);


-- insert into biuro_podrozy.tour
--   (id,  offerid, customerpesel, employeeid, insurance, extra_meals, debt, state, reserved_tickets)
-- values
--   (1,28,92121963645,41,1,0,1379,1,2);
