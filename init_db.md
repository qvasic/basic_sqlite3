# init db

create table odometer (id PRIMARY KEY, odometer_cm INTEGER);
insert into odometer (id, odometer_cm) values (0, 0);
update odometer set odometer_cm = 666 where id = 0;
