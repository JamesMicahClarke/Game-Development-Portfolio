use example2207;
-- delete from orders
-- where orders.userId = ' yyyyy ';

insert into orders
(userId, orderDate, shippingDate)
values ( ' yyyyy ', Now(), Now());

select * from orders
where orders.orderId = 21279;

-- delete from orderitem
-- where orderitem.orderId = 89;

insert into orderitem
(orderId, itemId, quantity)
 values(89, 45, 1);
 
 insert into orderitem
(orderId, itemId, quantity)
 values(90, 10, 1);
 
 select * from orderitem
 where orderitem.orderId = 90 and orderitem.itemId = 10
 || orderitem.orderId = 89 and orderitem.itemId = 45;
 
 select * from dvd
 where dvd.dvdId = 12466 ||  dvd.dvdId = 26925;
 
 insert into userdvd (userId, dvdId) 
 values (' yyyyy ',12466 );
 
 insert into userdvd (userId, dvdId) 
 values (' yyyyy ',26925 );
 
 select * from vehicle
 where vehicleId = 5159 || vehicleId =  4546;
 
 insert into userVehicle (userId, vehicleId) values(' yyyyy', 5159 );
 
 insert into userVehicle (userId, vehicleId) values(' yyyyy', 4546 );
 
-- delete from userVehicle where userVehicleId = 250002;

select users.userId, users.firstname, users.lastname, orders.orderId
from users
join orders
on users.userId = orders.userId;

select users.userId, users.firstname, users.lastname, orders.orderId
from users left join orders
on users.userId = orders.userId
where orders.orderId is null;

select orders.orderId, orders.orderDate, users.userId, 
users.firstname, users.lastname, item.itemName, orderitem.quantity
from users join orders
on users.userId = orders.userId
join orderitem
on orders.orderId = orderitem.orderId
join item
on orderitem.itemId = item.itemId;

alter table orders
add destinationState varchar(2);

update orders
set destinationState  = 'WY'
where orders.destinationState is null;

alter table orders
add foreign key (destinationState)
references state(state);

select firstName, lastname, concat(firstName, lastName) fullName 
from users 
where firstName = 'Austin';

Alter table users
Add index (firstname);

select firstName, lastname, concat(firstName, lastName) fullName 
from users 
where firstName = 'Austin';

select firstname, lastname from users
where lastname >= 'gggg' && lastname like '%ing';

select firstname, lastname from users
where firstname like 'j%r' and
users.occupationId >= 0;









 
 