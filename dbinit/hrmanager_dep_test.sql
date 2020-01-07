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
  -- hash of password : passwd1
  ("manager_1", '2C69A0416BB8AA4A03F12734987F34D154E3964E',2,1),
  -- hash of password : passwd2
  ("employee_1", '96E7C231A54050DFA9571101979A6201CA3C2A18',1,2),
  -- hash of password : passwd3
  ("employee_2", '4B6BB75317F7D15EB8926F76DF7ABCDE276E80DA',1,3),
  -- hash of password : passwd4
  ("employee_3", '072774747BD9E7D0E2EE9DBCAFAECD74D1620816',1,4),
  -- hash of password : passwd5
  ("employee_4", '1B1C08CEC0008453C416CD44C9F2F26620A32BAD',1,5),
  -- hash of password : passwd6
  ("employee_5", '2659E3433796E0C2CAAD12AC757C4025A3CA0F57',1,6),
  -- hash of password : passwd7
  ("employee_6", 'C366F6925EF642C978AC952C0FB3B39B75DA8807',1,7);
