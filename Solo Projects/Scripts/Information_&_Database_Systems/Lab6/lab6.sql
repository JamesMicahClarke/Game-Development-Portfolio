use example2207;

select fuelType, avg(mpgHighway) as MpgHighwayAvg, avg(fuelCostAnnual) as AnnualFuelCost
from vehicle
group by fuelType
order by MpgHighwayAvg desc;



delete from userVehicle where userVehicleid in(select vehicleId
from vehicle  where cylinders = 4);
delete from vehicle where cylinders = 4;


delimiter $$
create function itemCount(inputItemid int)
returns int
begin
 declare result int;
 select quantityinstock into result
 from item
 where itemId = inputItemId;
 return result;
end $$
delimiter ;

delimiter $$
create function itemCount(inputItemid int)
returns int
begin
 declare result int;
 select quantityinstock into result
 from item
 where itemId = inputItemId;
 return result;
end $$
delimiter ;

delimiter $$
create procedure userInfo (
in inputUserId int,
out fullname varchar(255),
out occupation varchar(255),
out numOrders int,
out numDvds int,
out numVehicles int)
begin
 select fullname, occupation into fullname, occupation
 from users, occupation
 where users.occupationId = occupation.occupationId
 and userId = inputUserId;
 select count(*) into numOrders
 from orders
 where userId = inputUserId;
 select count(*) into numDvds
 from userDvd
 where userId = inputUserId;
 select count(*) into numVehicles
from userVehicle
 where userId = inputuserId;
end $$
delimiter ;

