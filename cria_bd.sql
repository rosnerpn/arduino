create database banco_arduino collate = utf8_general_ci;



use banco_arduino;



create table registrotemp (
id int(11) AUTO_INCREMENT PRIMARY KEY,
	
temperatura double,
	
data timestamp default current_timestamp);