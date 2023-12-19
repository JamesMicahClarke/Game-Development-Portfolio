use example2207;

select users.userId, firstname, lastname, count(useraddresstypeId) from users
join userAddress on users.userId = useraddress.userId
group by userId;

select dvd.dvdId, count(dvd.dvdId), cast(sum(dvd.Price) as decimal(10,2)), dvd.Genre from dvd
join userdvd on dvd.dvdId = userdvd.dvdId
group by dvdId;

create table dvdNormal
(
dvdId int(11) not null,
dvdTitle varchar(255),
year varchar(255),
 publicRating decimal(4,2),
 dvdStudioId int,
 dvdStatusId int,
 dvdGenreId int,
 primary key(dvdId));
 
 create table dvdStudio 
 (
 dvdStudioId int auto_increment,
 dvdStudioName varchar(255),
 primary key(dvdStudioId));
 
 create table dvdStatus
 (
 dvdStatusId int auto_increment,
dvdStatusName varchar(255),
 primary key(dvdStatusId));
 
 create table dvdGenre
 (
dvdGenreId int auto_increment,
dvdGenreName varchar(255),
 primary key(dvdGenreId));
 
 alter table dvdnormal
add foreign key (dvdStatusId)
references dvdstatus(dvdStatusId) 
on delete cascade
on update cascade;

alter table dvdnormal
add foreign key (dvdStudioId)
references dvdstudio(dvdStudioId)
on delete cascade
on update cascade;

alter table dvdnormal
add foreign key (dvdGenreId)
references dvdgenre(dvdGenreId)
on delete cascade
on update cascade;

-- ALTER TABLE dvdnormal DROP foreign key dvdnormal_ibfk_1;

-- delete from dvdstatus; delete from dvdstudio; delete from dvdgenre;

insert into dvdstatus(dvdstatusName)
select distinct status from dvd;

insert into dvdstudio(dvdstudioName)
select distinct studio from dvd;

insert into dvdgenre(dvdgenreName)
select distinct genre from dvd;

create unique index dvdstatusIndexU on dvdstatus(dvdstatusName);
create unique index dvdstudioIndexU on dvdstudio(dvdstudioName); 
create unique index dvdGenreIndexU on dvdgenre(dvdgenreName);

create index dvdstudioIndex on dvd(studio);
create index dvdstatusIndex on dvd(status);
create index dvdgenreIndex on dvd(genre);

insert into dvdNormal(dvdgenreId, dvdstudioId, dvdstatusId, year, publicRating,dvdTitle, dvdId)
select dvdGenre.dvdgenreId, dvdStudio.dvdstudioId, dvdStatus.dvdstatusId, dvd.year, dvd.publicRating, dvd.dvd_Title, dvd.dvdId from dvd
join dvdgenre on dvdgenre.dvdGenreName = dvd.genre
join dvdstudio on dvdstudio.dvdStudioName = dvd.studio
join dvdstatus on dvdstatus.dvdstatusName = dvd.status;
 
SET FOREIGN_KEY_CHECKS = 0; 
set SQL_SAFE_UPDATES = 0;

create view dvdView as
select dvdId, dvdTitle, dvdstudioName, dvdstatusName, dvdgenreName from dvdnormal
join dvdstudio on dvdnormal.dvdStudioId = dvdstudio.dvdStudioId
join dvdstatus on dvdnormal.dvdStatusId = dvdstatus.dvdStatusId
join dvdgenre on dvdnormal.dvdGenreId = dvdgenre.dvdGenreId;

select inline.userId, users.firstname, users.lastname, users.gender, inline.dvdCount  
from (
select userdvd.userId, count(userdvd.userId) dvdCount
from users
join userdvd on users.userId = userdvd.userId
group by users.userId desc) inline
join users on  inline.userId = users.userId
where gender = 'F' && inline.userId > 0
group by inline.userid desc;

select userdvd.userId, firstname, lastname, gender,
(select count(userdvd.userId) dvdCount 
from users
where userdvd.userId = users.userId) subquery
from userdvd
join users on userdvd.userId = users.userId 
where gender = 'F' && userdvd.userId > 0
group by userId desc;


