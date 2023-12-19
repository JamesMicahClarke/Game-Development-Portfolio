use example2207;

ALTER TABLE item
add column quantityInStock int;

update item
set quantityInStock = 10;

delimiter $$
create trigger orderQuantity
after insert on orderItem
for each row
begin
update item
set quantityInStock = quantityInStock - new.quantity
where item.itemId = new.itemId;
end $$
delimiter ;

select itemId, itemName, quantityInStock
from item
where itemId = 15 or itemId = 23;
-- They were 10.

insert into orderItem (orderId, itemId, quantity)
values (1, 15, 3);

insert into orderItem (orderId, itemId, quantity)
values (2, 23, 5);

select itemId, itemName, quantityInStock
from item
where itemId = 15 or itemId = 23;

delimiter $$
create trigger UserStatusChange
after update on users
for each row
begin
if (new.userStatusId != old.userStatusId)
then insert into activityLog (userStatusId) values ( now(),'User Status Changed', 
new.userId);
end if;
end $$
delimiter ;

delimiter $$
create trigger UserStatusChange
after update on users
for each row
begin
if (old.userStatusId != new.userStatusId)
then insert into activityLog (userStatusId) values ( now(),'User Status Changed', 
new.userId);
end if;
end $$
delimiter ;

select n Dvdprice, (
select count(*) Dvdcount from Dvd where Dvd.price > (numbers.n - 1) and 
Dvd.price <= numbers.n
) Count
from numbers;

select n as CylinderCount, 
Case when vehicleCount is null then 0 else vehicleCount end as vehicleCount
from numbers
left join
(
select count(*) vehicleCount, cylinders from vehicle
 where year = 1985
 group by cylinders
) as inline
on numbers.n = cylinders
where n >= 1 and n <= 16;

