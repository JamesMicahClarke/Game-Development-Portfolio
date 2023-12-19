use example2207;

select vehicle.vehicleId, vehicle.make, 
vehicle.model, vehicle.year, vehicle.drive, vehicle.fuelType
from vehicle
order by vehicle.vehicleId;

select vehicle.make, vehicle.model, count(vehicle.model), avg(vehicle.mpgHighway)
from vehicle where vehicle.year = 1986
group by vehicle.make, vehicle.model
having count( vehicle.model) > 2
order by vehicle.make, vehicle.model, avg(vehicle.mpgHighway);

create table vMake(
vMakeId int(11) not null auto_increment, 
vMake varchar(255),
Primary key(vMakeId));

create table vModel(
vModelId int(11) not null auto_increment, 
vModel varchar(255),
Primary key(vModelId));

create table vDrive(
vDriveId int(11) not null auto_increment, 
vDrive varchar(255),
Primary key(vDriveId));

create table vFuelType(
vFuelTypeId int(11) not null auto_increment, 
vFuelType varchar(255),
Primary key(vFuelTypeId));

insert into vMake (vmake)
select distinct make from vehicle;

insert into vModel (vModel)
select distinct model from vehicle;

insert into vDrive (vDrive)
select distinct make from vehicle;

insert into vFuelType (vFuelType)
select distinct fueltype from vehicle;

create unique index vMakeName on vMake (vMake);
 
 create unique index vModelName on vModel (vModel);
 
 create unique index vDriveName on vDrive (vDrive);
 
 create unique index vFuelTypeName on vFuelType (vFuelType);
 
 create table vNormal(
vehicleId int(11) not null, 
makeId int(11) not null,
modelId int(11) not null,
driveId int(11) not null,
fuelTypeId int(11) not null,
year int(11) not null,
cylinders int (11) not null,
mpgCity dec(10,2) not null,
mpgHighway dec(10,2) not null,
Primary key(vehicleId));

 create index makeIndex on vehicle (make);
 create index modelIndex on vehicle (model);
 create index driveIndex on vehicle (drive);
 create index fuelTypeIndex on vehicle (fuelType);
 
 
insert into vnormal(vehicleId, makeId, modelId, driveId, year, cylinders, mpgCity, mpgHighway, fuelTypeId)
select vehicleId, vmakeId, vmodelId, vdriveId, year, cylinders, mpgCity, mpgHighway, vfuelTypeId from vehicle 
join vMake on vehicle.make = vMake.vMake
join vModel on vehicle.model = vModel.vModel
join vDrive on vehicle.drive = vDrive.vDrive
join vfueltype on vehicle.fuelType = vfueltype.vfueltype;

select vNormal.vehicleId, vmake.vmake, vmodel.vmodel , vdrive.vdrive, year, vfueltype.vfuelType from vNormal
join vMake on vNormal.vehicleId = vMake.vMakeId
join vModel on vNormal.modelId = vModel.vModelId
join vDrive on vNormal.driveId = vDrive.vDriveId
join vfueltype on vNormal.fuelTypeId = vfueltype.vfueltypeId
order by vNormal.vehicleId;

select vehicle.vehicleId, vmake.vmake, vmodel.vmodel , vdrive.vdrive, year, vfueltype.vfuelType 
from vehicle
join vMake on vehicle.make = vMake.vMake
join vModel on vehicle.model = vModel.vModel
join vDrive on vehicle.drive = vDrive.vDrive
join vfueltype on vehicle.fuelType = vfueltype.vfueltype
order by vehicle.vehicleId;


 
 

