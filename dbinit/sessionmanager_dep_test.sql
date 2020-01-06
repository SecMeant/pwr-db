insert into biuro_podrozy_test.employees
  (name,surname, hire_date, salary,email,phone_number)
  values
('gerhardine','loghan',str_to_date('30.07.09','%d.%m.%y'),4156,'gloghan0@china.com.cn','765-578-4612'),
('aubree','sturr',str_to_date('12.06.19','%d.%m.%y'),3598,'asturr1@linkedin.com','249-754-0474'),
('faustina','glusby',str_to_date('01.05.15','%d.%m.%y'),2072,'fglusby2@acquirethisname.com','369-671-0886'),
('dorelle','ong',str_to_date('08.03.09','%d.%m.%y'),3937,'dong3@myspace.com','166-542-3734'),
('brok','segebrecht',str_to_date('09.02.19','%d.%m.%y'),4033,'bsegebrecht4@dion.ne.jp','770-888-4001'),
('nikolas','twigg',str_to_date('09.01.19','%d.%m.%y'),2623,'ntwigg5@ask.com','765-515-7208'),
('lil','abbate',str_to_date('17.07.03','%d.%m.%y'),3668,'labbate6@theguardian.com','821-543-1231');

insert into
biuro_podrozy_test.credentials
  (login,  pass_hash,  privilege, employeeid)
values
  ("mamanger_1", '5fd924625f6ab16a19cc9807c7c506ae1813490e4ba675f843d5a10e0baacdb8',2,1),
  ("employee_1", 'a63ab36162a4f4ee6622ccd787b0a048c26b93acfc05c6b1843659b253c3c00b',1,2),
  ("employee_2", 'c1b5f0eac826b829526f13b182808f34515826d4f1f2f9db4173568718a995e1',1,3),
  ("employee_3", 'f64aeef4ae2075114506128ee0e944353022ad959f3e69e5738d13dc560e351b',1,4);
