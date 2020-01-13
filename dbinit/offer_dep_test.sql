DROP TRIGGER IF EXISTS biuro_podrozy_test.on_new_tour_appear;
insert into biuro_podrozy_test.category
  (name)
values
  ('last minute'),
  ('sightseeing tour'),
  ('cruise'),
  ('facultative trips');
insert into biuro_podrozy_test.employees
  (name,surname, hire_date, salary,email,phone_number)
  values
('gerhardine','loghan',str_to_date('30.07.09','%d.%m.%y'),4156,'gloghan0@china.com.cn','765-578-4612'),
('aubree','sturr',str_to_date('12.06.19','%d.%m.%y'),3598,'asturr1@linkedin.com','249-754-0474'),
('faustina','glusby',str_to_date('01.05.15','%d.%m.%y'),2072,'fglusby2@acquirethisname.com','369-671-0886'),
('dorelle','ong',str_to_date('08.03.09','%d.%m.%y'),3937,'dong3@myspace.com','166-542-3734');
insert into biuro_podrozy_test.customers
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
 (88080188937,'josi','bottomer','jbottomerd@youtu.be');
insert into biuro_podrozy_test.offers
  ( name, city, country, date_begin, date_end, price, categoryid, insurance_cost, extra_meals_cost, tickets_count)
values
  ('wycieczka 1','tokio','japonia',str_to_date('14.01.19','%d.%m.%y'),str_to_date('20.01.19','%d.%m.%y'),6412,1,830,393,55),
  ('wycieczka 2','meksyk-city','meksyk',str_to_date('15.01.19','%d.%m.%y'),str_to_date('21.01.19','%d.%m.%y'),4298,4,614,538,55),
  ('wycieczka 3','nowy jork','usa',str_to_date('16.01.19','%d.%m.%y'),str_to_date('22.01.19','%d.%m.%y'),6990,2,795,385,46),
  ('wycieczka 4','kair','egipt',str_to_date('17.01.19','%d.%m.%y'),str_to_date('23.01.19','%d.%m.%y'),5040,4,793,608,52),
  ('wycieczka 5','sao paulo','brazylia',str_to_date('18.01.19','%d.%m.%y'),str_to_date('24.01.19','%d.%m.%y'),4909,2,1320,751,42);
insert into biuro_podrozy_test.credentials
  (login,  pass_hash,  privilege, employeeid)
values
  ("mamanger_1", 'F578F4A1136DB20EC96B6D29FB890283F123F459',2,1),
  ("employee_1", 'F578F4A1136DB20EC96B6D29FB890283F123F459',1,2),
  ("employee_2", 'F578F4A1136DB20EC96B6D29FB890283F123F459',1,3),
  ("employee_3", 'F578F4A1136DB20EC96B6D29FB890283F123F459',1,4);

insert into biuro_podrozy_test.tour
  (offerid, customerid, employeeid, insurance, extra_meals, debt, state, reserved_tickets)
values
  (1 ,1, 1, 1, 0, 1379 ,0 ,4),
  (2, 2, 1, 1, 1, 1062 ,0 ,5),
  (3, 3, 1, 1, 1, 2509 ,0 ,3),
  (4, 4, 1, 0, 0, 1122 ,0 ,2);