use arduino;

create table DHT22 (id int(11) AUTO_INCREMENT PRIMARY KEY,
	temp float,
	umid float,
	data timestamp default current_timestamp);