#�ڶ���
#�ַ������ַ���Ĳ鿴������
show character set;
show variables like 'character%';
show collation;
show variables like 'collation%';
set character_set_client = gbk;
set character_set_connection = gbk;
set character_set_database = gbk;
set character_set_results = gbk;
set character_set_server = gbk;
set collation_connection = gbk_chinese_ci ;
set collation_database = gbk_chinese_ci ;
set collation_server = gbk_chinese_ci ;
show variables like 'character%';
show variables like 'collation%';
#�������ݿ�
create database choose;
alter database choose character set gbk;
show variables like 'datadir';
show databases;
show create database choose;
use choose;
#�ֶ�����student���ݿ�Ŀ¼
#drop database student;
#�洢����
show engines;
set default_storage_engine=MyISAM;
show engines;
#�������ݿ��
use choose;
set default_storage_engine=InnoDB;
create table my_table(
today datetime,
name char(20)
);

alter table my_table engine=MyISAM;
show tables;
desc my_table;
show create table my_table;
#���¼�Ĺ���
use choose;
insert into my_table values(now(),'a');
insert into my_table values(now(),'a');
insert into my_table values(now(),NULL);
insert into my_table values(now(),'');
select * from my_table;

use choose;
alter table my_table engine=InnoDB;
use choose;
insert into my_table values(now(),'a');
insert into my_table values(now(),'a');
insert into my_table values(now(),NULL);
insert into my_table values(now(),'');
select * from my_table;
#InnoDB��ռ�
show variables like 'innodb_data_file_path';

show variables like 'innodb_file_per_table';
set @@global.innodb_file_per_table = ON;
show variables like 'innodb_file_per_table';

use choose;
alter table my_table engine=InnoDB;
create table second_table(
today datetime,
name char(20)
);
drop table second_table;
set @@global.innodb_file_per_table = OFF;
#ϵͳ����
#show global variables;
#show session variables;

show global variables like 'innodb_data_file_path';
show session variables like 'innodb_data_file_path';
show variables like 'innodb_data_file_path';

show session variables like 'pseudo_thread_id';
show variables like 'pseudo_thread_id';

show variables like 'character_set_client';
set character_set_client = latin1;
show session variables like 'character_set_client';
show variables like 'character_set_client';

show session variables like 'character_set_client';
show variables like 'character_set_client';

show global variables like 'character_set_client';

select @@global.innodb_data_file_path;
select @@innodb_data_file_path;

#select @@session.innodb_data_file_path;


set @@global.innodb_file_per_table = ON;
set global innodb_file_per_table = ON;


set @@session.pseudo_thread_id = 5;
set session pseudo_thread_id = 5;
set @@pseudo_thread_id = 5;
set pseudo_thread_id = 5;

select @@character_set_server;
#select @@character-set-server;

flush tables with read lock;
#insert into my_table values(now(),'a');
unlock tables;

set global innodb_file_per_table = OFF;
#������
#��������
show variables like 'time_zone';

use choose;
create table today(
t1 datetime,
t2 timestamp
);
insert into today values(now(),now());
insert into today values(now(),null);
select * from today;
set time_zone='+12:00';
select * from today;


update today set t1=now();
select * from today;

select now(6),curtime(6);
select now(6),now(),microsecond(now(6));

set character_set_client = gbk;

use choose;
create table person(
sex enum('��','Ů'),
interest set('������','����Ӱ','����','����','��Ӿ','��Ϸ')
);
insert into person values('��','����Ӱ,��Ӿ,������');
select * from person;

set sql_mode = 'strict_trans_tables';
#insert into person values('��','��Ӱ,��Ӿ,������');
set sql_mode = 'ansi';
insert into person values('��','��Ӱ,��Ӿ,������');
set sql_mode = 'strict_trans_tables';
#Լ��
use choose;
create table nowadays (
t1 datetime,
t2 timestamp,
primary key(t1, t2)
);

select constraint_name, constraint_type
from information_schema.table_constraints
where table_schema='choose' and table_name='nowadays';

show index from nowadays\G

create table test(
test_no char(10),
test_name char(10),
constraint test_pk primary key (test_no),
constraint name_unique unique (test_name)
);


select constraint_name, constraint_type
from information_schema.table_constraints
where table_schema='choose' and table_name='test';

show index from test\G

#ѡ��ϵͳ���ݿ��

use choose;
create table teacher(
teacher_no char(10) primary key,
teacher_name char(10) not null,			#��ʦ����������Ϊ��
teacher_contact char(20) not null			#��ʦ��ϵ��ʽ��������Ϊ��
)engine=InnoDB default charset=gbk;
create table classes(
class_no int auto_increment primary key,
class_name char(20) not null unique,		#�༶��������Ϊ�ա��Ҳ������ظ�
department_name char(20) not null		#Ժϵ��������Ϊ��
)engine=InnoDB default charset=gbk;
create table course(
course_no int auto_increment primary key,
course_name char(10) not null, 			#�γ��������ظ�
up_limit int default 60,					#�γ���������Ĭ��ֵΪ60
description text not null,					#�γ̵�������ϢΪ�ı��ַ���text���Ҳ���Ϊ��
status char(6) default 'δ���',			#�γ�״̬��Ĭ��ֵΪ��δ��ˡ�
teacher_no char(10) not null unique,		#Ψһ��Լ��ʵ�ֽ�ʦ��γ�֮��1:1��ϵ
constraint course_teacher_fk foreign key(teacher_no) references teacher(teacher_no)
)engine=InnoDB default charset=gbk;
create table student(
student_no char(11) primary key,			#ѧ�Ų������ظ�
student_name char(10) not null,			#ѧ������������Ϊ��
student_contact char(20) not null,			#ѧ����ϵ��ʽ������Ϊ��
class_no int ,							#ѧ���İ༶����Ϊ��
constraint student_class_fk foreign key (class_no) references classes(class_no)
)engine=InnoDB default charset=gbk;
create table choose(
choose_no int auto_increment primary key,
student_no char(11) not null,				#ѧ��ѧ�Ų�����Ϊ��
course_no int not null, 					#�γ̺Ų�����Ϊ��
score tinyint unsigned,
choose_time datetime not null,			#ѡ��ʱ�����now()�����Զ�����
constraint choose_student_fk foreign key(student_no) references student(student_no),
constraint choose_course_fk foreign key(course_no) references course(course_no)
)engine=InnoDB default charset=gbk;

use choose;
create table today1 like today;
show create table today1;
select * from today1;
use choose;
create table today2 select * from today;
show create table today2;
select * from today2;

#�޸ı�ṹ
alter table person drop interest;
alter table person add person_no int auto_increment primary key first;
alter table person add person_name char(10) not null after person_no;

alter table person change person_name name char(20);
alter table person modify name char(30);

#�޸�Լ������
delete from person;
alter table person add constraint name_unique unique (name);

select constraint_name, constraint_type
from information_schema.table_constraints
where table_schema='choose' and table_name='person';

show index from person\G


alter table person drop index name_unique;
alter table person engine=MyISAM;
alter table person default charset=gb2312;
alter table person auto_increment=8;
alter table person pack_keys=1;
alter table person rename human;


#����
create table book(
isbn char(20) primary key,
name char(100) not null,
brief_introduction text not null,
price decimal(6,2),
publish_time date not null,
unique index isbn_unique (isbn),
index name_index (name (20)),
fulltext index brief_fulltext (name,brief_introduction),
index complex_index (price,publish_time)
) engine=MyISAM default charset=gbk;
alter table course add fulltext index description_fulltext (description);
drop index complex_index on book;

#������
use choose;
insert into teacher values('001','����ʦ','11000000000');
insert into teacher values('002','����ʦ','12000000000');
insert into teacher values('003','����ʦ','13000000000');
select * from teacher;

use choose;
insert into classes(class_no,class_name,department_name) values(null,'2012�Զ���1��', '���繤��');
insert into classes(class_no,class_name,department_name) values(null,'2012�Զ���2��', '���繤��');
insert into classes(class_no,class_name,department_name) values(null,'2012�Զ���3��', '���繤��');
select * from classes;


use choose;
insert into course values(null,'java���Գ������',default,'����','�����','001');
insert into course values(null,'MySQL���ݿ�',150,'����','�����','002');
insert into course values(null,'c���Գ������',230,'����','�����','003');
select * from course;

#���������insert����������󣬵�id�ֶ�Ҳ������
insert into course values(null,'PHP��̻���',default,'����','�����','007');
insert into course values(null,'PHP��̻���',default,'����','�����','002');


use choose;
set character_set_client = latin1;
insert into classes values(null,'2012�����Ӧ��1��', '��Ϣ����');
select * from classes;

use choose;
set character_set_client = gbk;
select * from classes;


use choose;
delete from classes where class_no=4;
select * from classes;
insert into classes values(null,'2012�����Ӧ��1��', '��Ϣ����');
select * from classes;

show create table classes;

use choose;
insert into student values
('2012001','����','15000000000',1),
('2012002','����','16000000000',1),
('2012003','����','17000000000',3),
('2012004','����','18000000000',2),
('2012005','����','19000000000',2);
select * from student;



use choose;
create table new_student like student;
insert into new_student select * from student;
select * from new_student;

replace into student values ('2012001','������','15000000000',1);
replace into student values ('2012001','����','15000000000',1);

use choose;
update classes set department_name='���繤��ѧԺ' where class_no<=3;
select * from classes;

use choose;
delete from classes where class_name='2012�����Ӧ��1��';
select * from classes;

use choose;
#delete from classes;
select * from classes;

use choose;
create table new_class like classes;
insert into new_class select * from classes;
select * from new_class;

show create table new_class;

delete from new_class;
show create table new_class;

truncate table new_class;
show create table new_class;

insert into choose values
(null,'2012001',2,40,now()),
(null,'2012001',1,50,now()),
(null,'2012002',3,60,now()),
(null,'2012002',2,70,now()),
(null,'2012003',1,80,now()),
(null,'2012004',2,90,now()),
(null,'2012005',3,null,now()),
(null,'2012005',1,null,now());



use choose;
insert into new_student values('2012006','Mar_tin', 'mar\tin@gmail.com',3);
insert into new_student values('2012007','O\'Neil', 'o_\neil@gmail.com',3);
select * from new_student;


#������

select version(), now(),pi(),1+2,null=null,null!=null,null is null;
select version() �汾��, now() as ��������ǰʱ��, pi() PI��ֵ,1+2 ���;


select * from student;
select student_no,student_name, student_contact,class_no from student;
select student_no,student_name from student; 
select student.student_no, student.student_name from student; 
select distinct department_name from classes; 

select * from student limit 0,3; 
select * from student limit 3;

select * from choose limit 1,3;

insert into classes values(4,'2012�Զ���4��','���繤��ѧԺ');
insert into student values('2012006','������','20000000000',null);

select student_no,student_name,student_contact,student.class_no,class_name,department_name
from student join classes on student.class_no=classes.class_no;

select student_no,student_name,student_contact,student.class_no,class_name,department_name
from classes join student on student.class_no=classes.class_no;

select student_no,student_name,student_contact,s.class_no,class_name,department_name
from classes as c join student s on s.class_no=c.class_no;

select student_no,student_name,student_contact,s.class_no,class_name,department_name
from classes c join student s on s.class_no=c.class_no;

select student_no,student_name,student_contact,student.class_no,class_name,department_name
from student left join classes on student.class_no=classes.class_no;



select student_no,student_name,student_contact,student.class_no,class_name,department_name
from student left join classes on student.class_no=classes.class_no
where classes.class_no is null;


select classes.class_no,class_name,department_name,student_no,student_name,student_contact
from student right join classes on student.class_no=classes.class_no;


select student.student_no,student_name,choose.course_no,course_name,score
from classes left join student on classes.class_no=student.class_no
join choose on student.student_no=choose.student_no
join course on course.course_no=choose.course_no
where class_name='2012�Զ���2��';

select student_no,student_name,student_contact,student.class_no,class_name,department_name
from student , classes
where student.class_no=classes.class_no;

select student.student_no,student_name,choose.course_no,course_name,score
from student inner join choose on student.student_no=choose.student_no 
inner join course on choose.course_no=course.course_no
where score is NULL;

select 2 = 2,NULL = NULL, NULL != NULL, NULL is NULL, NULL is not NULL;

select * from course where up_limit=60;
set character_set_results = latin1;
select * from course where up_limit=60;

set character_set_results = gbk;
select * from course where course_name='java���Գ������';
set character_set_connection = latin1;
select * from course where course_name='java���Գ������';

set names latin1;
#select * from course where course_name='java���Գ������';
set names gbk;


select * from course where !(up_limit=60);

select student.student_no,student_name,student_contact,choose.course_no,course_name,score
from course join choose on course.course_no=choose.course_no
join student on choose.student_no=student.student_no
where course.course_name='MySQL���ݿ�' and score<60;

select student.student_no,student_name,choose.course_no,course_name,score
from student join choose on student.student_no=choose.student_no 
join course on choose.course_no=course.course_no
where score between 80 and 100;

select * 
from student
where substring(student_name,1,1)='��' or substring(student_name,1,1)='��';
select * from student where substring(student_name,1,1) in ('��' ,'��');
select * from student where student_name like '��_';
select * from student where student_name like '%��%';

select * from new_student where student_name like '%\_%';
select * from new_student where student_name like '%!_%' escape '!';
select * from choose order by score desc;

select student.student_no,student_name,course.course_no,course_name,score
from student inner join choose on student.student_no=choose.student_no 
inner join course on choose.course_no=course.course_no
order by student_no asc,course_no asc;

select count(*)  ѧ������ from student;
select count(choose_no) �μӿ��Ե�����, count(choose_no)-count(score) ȱ��ѧ������, 
(count(choose_no)-count(score))/count(choose_no)*100 ȱ���ٷֱ� from choose;

select sum(score) �ܳɼ� from choose;
select student.student_no,student_name ����,sum(score)  �ܳɼ� 
from student left join choose on choose.student_no=student.student_no
where student_name='������';
select student.student_no,student_name ����,avg(score)  ƽ���ɼ� 
from student left join choose on choose.student_no=student.student_no
where student_name='����';

select max(score) ��߷�,min(score) ��ͷ� from choose;

select * from student order by class_no;
select * from student group by class_no;

select class_name,count(student_no)
from classes left join student on student.class_no=classes.class_no
group by classes.class_no;

select student.student_no,student_name,count(course_no),max(score),min(score),sum(score), avg(score)
from student left join choose on student.student_no=choose.student_no 
group by student.student_no;

select choose.student_no,student_name,avg(score)
from choose join student on choose.student_no=student.student_no 
group by student.student_no 
having avg(score)>70;

select group_concat('java','����','���'),concat('java','����','���');

select class_name �༶��,group_concat(student_name) ѧ������, concat(student_name) ��������
from classes left join student on student.class_no=classes.class_no
group by classes.class_no;

select classes.class_no,count(classes.class_no)
from classes join student on student.class_no=classes.class_no
group by classes.class_no with rollup;

select student_no �˺�,student_name ����,student_contact ��ϵ��ʽ
from student
union all
select teacher_no,teacher_name,teacher_contact
from teacher;

select class_name,student.student_no, student_name,course_name,score
from classes join student on student.class_no=classes.class_no
join choose on choose.student_no=student.student_no
join course on choose.course_no=course.course_no
where score>(
select avg(score)
from student,choose
where student.student_no=choose.student_no and student_name='����'
);


select class_name,student.student_no, student_name,course_name,score
from classes join student on student.class_no=classes.class_no
join choose on choose.student_no=student.student_no
join course on choose.course_no=course.course_no
where score>(
select avg(score)
from choose
where student.student_no=choose.student_no and student_name='����'
);

select class_name,student.student_no,student_name,course_name,avg(score)
from classes join student on student.class_no=classes.class_no
join choose on choose.student_no=student.student_no
join course on choose.course_no=course.course_no
group by student.student_no
having avg(score)>(
select avg(score)
from choose join student on student.student_no=choose.student_no
where student_name='����'
);

select student.student_no,student_name,course_name,score
from course join choose on choose.course_no=course.course_no
join student on choose.student_no=student.student_no
where student.student_no in (
select student_no
from student join classes on student.class_no=classes.class_no
where classes.class_name='2012�Զ���1��'
);

select * from teacher where teacher_no
not in (
select teacher.teacher_no from course where course.teacher_no=teacher.teacher_no
);
insert into teacher values('004','����ʦ','10000000000');
select * from teacher
where not exists (
select * from course where course.teacher_no=teacher.teacher_no
);
select * from course
where not exists (
select * from choose where course.course_no=choose.course_no
);
insert into course values(null,'PHP�������',60,'����','�����','004');
select student.student_no,student_name,class_name
from student join classes on student.class_no=classes.class_no
join choose on choose.student_no=student.student_no
where class_name='2012�Զ���2��' and score>any(
select score
from choose join student on student.student_no=choose.student_no
join classes on classes.class_no=student.class_no
where class_name='2012�Զ���1��'
);
#�˴�PHP������Ƶ�idΪ6
insert into course values(null,'PHP�������',60,'����','�����','004');

select student.student_no,student_name,class_name
from student join classes on student.class_no=classes.class_no
join choose on choose.student_no=student.student_no
where class_name='2012�Զ���2��' and score>all(
select score
from choose join student on student.student_no=choose.student_no
join classes on classes.class_no=student.class_no
where class_name='2012�Զ���1��'
);


#ѡ��ϵͳ�ۺϲ�ѯ
select student_no,count(*) course_num
from choose
where student_no='2012001';

select choose.course_no, course_name,teacher_name,teacher_contact,description
from choose join course on course.course_no=choose.course_no
join teacher on teacher.teacher_no=course.teacher_no
where student_no='2012001';

select department_name,class_name,student.student_no,student_name,student_contact
from student join classes on student.class_no=classes.class_no
join choose on student.student_no=choose.student_no
where course_no=1
order by department_name,class_name,student_no;

select course.course_no,course_name,teacher_name,up_limit,description
from choose join course on choose.course_no=course.course_no
join teacher on teacher.teacher_no=course.teacher_no
group by course_no
having up_limit=count(*);


select course.course_no,course_name,teacher_name,teacher_contact,count(*) as student_num
from choose join course on choose.course_no=course.course_no
join teacher on teacher.teacher_no=course.teacher_no
group by course_no
having count(*)<30
union all
select course.course_no, course_name,teacher_name,teacher_contact,0
from course join teacher on teacher.teacher_no=course.teacher_no
where not exists (
select * from choose where course.course_no=choose.course_no
);




select course.course_no,course_name,teacher_name,
up_limit,count(*) as student_num,up_limit-count(*) available
from choose join course on choose.course_no=course.course_no
join teacher on teacher.teacher_no=course.teacher_no
group by course_no
union all
select course.course_no,course_name,teacher_name,up_limit,0,up_limit
from course join teacher on teacher.teacher_no=course.teacher_no
where not exists (
select * from choose where course.course_no=choose.course_no
);

select * from course where course_name regexp 'java';
select * from course where course_name like '%java%';
select * from course where course_name regexp '�������$';
select * from course where course_name regexp '^j.*�������$';
select * from student where student_contact regexp '^1[58][0-9]{9}';


insert into book(isbn,name,brief_introduction,price,publish_time) values
('978-7-115-25626-3','PHP Fundamentals & Practices','Web Database Applications MySQL offers web developers a mixture of theoretical and practical information on creating web database applications. ','42.0','2012-7-1'),
 ('978-7-115-25626-4','MySQL COOKBOOK','The MySQL database management system has become quite popular in recent years.','128.0','2008-1-1'),
 ('978-7-115-25626-5','Beginning MySQL',' MySQL is especially heavily used in combination with a web server for constructing database-backed web sites that involve dynamic content generation.','98.0','2008-1-1');

select * from book where match (name,brief_introduction) against ('practices')\G
select * from book where match (name,brief_introduction) against ('practices cookbook')\G

select isbn,name, match(name,brief_introduction) against ('practices cookbook') ������
from book;
select * from book where match (name,brief_introduction) against ('mysql')\G

select * from book where match (name,brief_introduction) against ('mysql' in boolean mode)\G

select * from book where match (name,brief_introduction) against ('php' in boolean mode)\G
show variables like 'ft_min_word_len';
show variables like 'ft_max_word_len';
repair table book quick;
select * from book where match (name,brief_introduction) against ('that' in boolean mode)\G

show variables like 'ft_stopword_file';
repair table book quick;
select * from book where match (name,brief_introduction) against ('that' in boolean mode)\G



select * from book where match (name,brief_introduction) against ('+mysql -php' in boolean mode)\G
select isbn,name,match(name,brief_introduction) against('+mysql +(cookbook php)' in boolean mode) ������
from book;
select isbn,name,match(name,brief_introduction) against('+mysql +(>cookbook <php)' in boolean mode) ������
from book;
select * from book where match (name,brief_introduction) against (' "Database Applications" popu*' in boolean mode)\G

select * from book where match (name,brief_introduction) against ('mysql')\G
alter table book engine=InnoDB;
select * from book where match (name,brief_introduction) against ('mysql')\G



#������
select 'I\'m a \teacher' as col1, "you're a stude\nt" as col2;
select X'41', x'4D7953514C';
select 0x41, 0x4D7953514C ;
select b'111101',b'1', b'11';
select true, false;

set @user_name = '����';
select @user_name;
set @user_name = b'11', @age = 18;
select @user_name,@age;
set @age = @age+1;
select @user_name,@age;

select @a := 'a';
select @a='a';
select @user_name:='����';
select 19 into @age;
select @user_name,@age;
set @student_count = (select count(*) from student);
select @student_count;
select @student_count := (select count(*) from student);
select @student_count:= count(*) from student;
select count(*) into @student_count from student;
select count(*) from student into @student_count;
set @student_no='2012001';
select * from student where student_no=@student_no;
set @num = 15;
select @num+2, @num-2, @num *2, @num/2, @num%3,@num div 3;
select '2013-01-31' + interval '22' day, '2013-01-31' - interval '22' day;
select 'ab '='ab', ' ab'='ab', 'b'>'a',NULL=NULL,NULL<=>NULL,NULL is NULL;
select 1 and 2, 2 and 0,2 and true,0 or true,not 2,not false;
select null and 2, 2 and 0.0,2 and 'true', 1 xor 2, 1 xor false;
select b'101' & b'010',5&2,5|2, ~5,5 ^2,5>>2,5<<2;

delimiter $$
select * from student where student_name like '��_'$$
delimiter ;
select * from student where student_name like '��_';


#�Զ��庯��
delimiter $$
create function row_no_fn() returns int
no sql
begin
	set @row_no = @row_no + 1;
	return @row_no;
end;
$$
delimiter ;


delimiter $$
create function get_name_fn(student_no1 int) returns char(20)
reads sql data
begin
	declare student_name1 char(20);
	select student_name into student_name1 from student where student_no=student_no1;
	return student_name1;
end;
$$
delimiter ;


delimiter $$
create function get_choose_number_fn(student_no1 int) returns int
reads sql data
begin
	declare choose_number int;
	select count(*) into choose_number from choose where student_no=student_no1;
	return choose_number;
end;
$$
delimiter ;


select name from mysql.proc where db = 'choose' and type = 'function' ;
show create function get_name_fn\G
select * from information_schema.routines where routine_name='get_name_fn'\G


drop function get_name_fn;

delimiter $$
create function get_name_fn (no int,role char(20)) returns char(20)
reads sql data
begin
	declare name char(20);
	if('student'=role) then
		select student_name into name from student where student_no=no;
	elseif('teacher'=role) then
		select teacher_name into name from teacher where teacher_no=no;
	else set name='��������';
	end if;
	return name;
end;
$$
delimiter ;


delimiter $$
create function get_week_fn(week_no int) returns char(20)
no sql
begin
	declare week char(20);
	case week_no
	when 0 then set week = '����һ';
	when 1 then set week = '���ڶ�';
	when 2 then set week = '������';
	when 3 then set week = '������';
	when 4 then set week = '������';
	else set week = '������Ϣ';
	end case;
	return week;
end
$$
delimiter ;


delimiter $$
create function get_sum_fn(n int) returns int
no sql
begin
	declare sum char(20) default 0;
	declare start int default 0;
	while start<n do
		set start = start + 1;
		set sum = sum + start;
	end while;
	return sum;
end;
$$
delimiter ;

delimiter $$
create function get_sum1_fn(n int) returns int
no sql
begin
	declare sum char(20) default 0;
	declare start int default 0;
	add_num : while true do
		set start = start + 1;
		set sum = sum + start;
		if(start=n) then 
leave add_num; 
end if;
	end while add_num;
	return sum;
end;
$$
delimiter ;


delimiter $$
create function get_sum2_fn (n int) returns int
no sql
begin
	declare sum char(20) default 0;
	declare start int default 0;
	add_num: while true do
		set start = start + 1;
		if(start%2=0) then 
set sum = sum + start; 
else 
iterate add_num; 
end if;
		if(start=n) then 
leave add_num; 
end if;
	end while add_num;
	return sum;
end;
$$
delimiter ;


delimiter $$
create function get_sum3_fn(n int) returns int
no sql
begin
	declare sum char(20) default 0;
	declare start int default 0;
	repeat
		set start = start + 1;
		set sum = sum + start;
		until start=n
	end repeat;
	return sum;
end;
$$
delimiter ;


delimiter $$
create function get_sum4_fn(n int) returns int
no sql
begin
	declare sum char(20) default 0;
	declare start int default 0;
	add_sum : loop
		set start = start + 1;
		set sum = sum + start;
		if (start=n) then 
leave add_sum; 
end if;
	end loop;
	return sum;
end;
$$
delimiter ;



insert into new_class values
(null,'2012�������1��','���ѧԺ'),
(null,'2012�������2��','���ѧԺ');
select last_insert_id(),@@last_insert_id;


delimiter $$
create function to_english_fn(s varchar(32760)) returns varchar(32760)
no sql
begin
declare start int;
declare string_length int;
declare new_string varchar(32760);
declare temp_string varchar(32760);
set start = 1;
set string_length = char_length(s);
set new_string = '';
while start<=string_length do	
		set temp_string = hex(substring(s,start,1));
		set start = start + 1;
		set new_string = concat(new_string,' H',temp_string);
end while;
return trim(new_string);
end;
$$
delimiter ;

update course set description=to_english_fn('Java��һ�ֿ���׫д��ƽ̨Ӧ��������������ĳ���������ԡ�') where course_name='java���Գ������';
update course set description=to_english_fn('MySQL��һ�����͹�ϵ�����ݿ����ϵͳ�������MySQL AB��˾������Ŀǰ����Oracle��˾��') where course_name='MySQL���ݿ�';
update course set description=to_english_fn('C������һ�ּ��������������ԣ����Ⱦ��и߼����Ե��ص㣬�־��л�����Ե��ص㡣') where course_name='c���Գ������';
update course set description=to_english_fn('PHP����ѧ�ҹ���ǿ���ǿ���WEBӦ�ó�������Ľű����ԡ�') where course_name='PHP�������';


delimiter $$
create function to_chinese_fn(s varchar(32760)) returns varchar(32760)
no sql
begin
declare new_string varchar(32760);
declare temp_string varchar(32760);
set temp_string = replace(s, ' H','');
set temp_string = replace(temp_string,'H','');
set temp_string = unhex(temp_string);
return temp_string;
end
$$
delimiter ;


#��������ͼ�봥����

use choose;
create view available_course_view
as
select course.course_no,course_name,teacher_name,teacher_contact,count(*) as student_num
from choose join course on choose.course_no=course.course_no
join teacher on teacher.teacher_no=course.teacher_no
group by course_no
having count(*)<30
union all
select course.course_no, course_name,teacher_name,teacher_contact,0
from course join teacher on teacher.teacher_no=course.teacher_no
where not exists (
select * from choose where course.course_no=choose.course_no
);

alter table course add available int default 0;

select course_no,course_name,up_limit,available from course;

update course set available=up_limit-(select student_num from available_course_view where available_course_view.course_no=course.course_no);

drop view available_course_view;
create view choose_1_view as select * from choose where score<60;

insert into choose_1_view values (null,'2012003',2,100,now());
select * from choose;
delete from choose where student_no='2012003' and course_no=2;

create view choose_2_view as select * from choose where score<60 with local check option;
#�����insert���ִ��ʱ��������
insert into choose_2_view values (null,'2012004',2,100,now());

#������
delimiter $$
create trigger course_insert_before_trigger before insert on course for each row
begin
if(new.up_limit=60 || new.up_limit=150 || new.up_limit=230) then
set new.up_limit = new.up_limit;
else insert into mytable values(0);
end if;
end;
$$
delimiter ;


insert into teacher values('005','����ʦ','00000000000');
#�����insert���ִ��ʱ��������
insert into course values(null,'�ߵ���ѧ',20,'����','�����','005',20);

delimiter $$
create trigger course_update_before_trigger before update on course for each row
begin
if(new.up_limit!=60 || new.up_limit!=150 || new.up_limit!=230) then
set new.up_limit = old.up_limit;
end if;
end;
$$
delimiter ;



delimiter $$
create trigger choose_insert_before_trigger before insert on choose for each row
begin
update course set available=available-1 where course_no=new.course_no;
end;
$$
delimiter ;

delimiter $$
create trigger choose_delete_before_trigger before delete on choose for each row
begin
update course set available=available+1 where course_no=old.course_no;
end;
$$
delimiter ;


#InnoDB�洢����ļ���ɾ��

alter table choose drop foreign key choose_course_fk;
alter table choose add constraint choose_course_fk foreign key (course_no) references course(course_no) on delete cascade;


create table organization(
o_no int not null auto_increment,
o_name varchar(32) default '',
primary key (o_no)
) engine=innodb;
create table member(
m_no int not null auto_increment,
m_name varchar(32) default '',
o_no int,
primary key (m_no),
constraint organization_member_fk foreign key (o_no) references organization(o_no)
) engine=innodb;

insert into organization(o_no, o_name) values
(null, 'o1'),
(null, 'o2');
insert into member(m_no,m_name,o_no) values
(null, 'm1',1),
(null, 'm2',1),
(null, 'm3',1),
(null, 'm4',2),
(null, 'm5',2);


delimiter $$
create trigger organization_delete_before_trigger before delete on organization for each row
begin
delete from member where o_no=old.o_no;
end;
$$
delimiter ;

select * from member;
delete from organization where o_no=1;
select * from member;

drop trigger organization_delete_before_trigger;

#��ʱ��

alter table student add password char(32) not null after student_no;
alter table teacher add password char(32) not null after teacher_no;

create temporary table password_temp select student_no s_no, md5(student_no) pwd from student;

update student set password=(
select pwd
from password_temp
where student_no=s_no
);



update teacher s set s.password =(
select md5(u.teacher_no) 
from 
(select teacher_no from teacher) u
where s.teacher_no=u.teacher_no
);


#�洢����

delimiter $$
create procedure get_choose_number_proc(in student_no1 int,out choose_number int)
reads sql data
begin
	select count(*) into choose_number from choose where student_no=student_no1;
end
$$
delimiter ;

delimiter $$
create procedure get_choose_number1_proc(inout number int)
reads sql data
begin
	select count(*) into number from choose where student_no=number ;
end
$$
delimiter ;


delimiter $$
create procedure get_student_course_proc(in s_no char(11))
reads sql data
begin
select choose.course_no,course_name,teacher_name,teacher_contact,to_chinese_fn(description) description
from choose join course on course.course_no=choose.course_no
join teacher on teacher.teacher_no=course.teacher_no
where student_no=s_no;
end
$$
delimiter ;


delimiter $$
create procedure get_teacher_course_proc(in t_no char(11))
reads sql data
begin
select course_no,course_name,teacher_name,teacher_contact,status,to_chinese_fn(description) description
from teacher join course on course.teacher_no=teacher.teacher_no
where teacher.teacher_no=t_no;
end
$$
delimiter ;


delimiter $$
create procedure get_course_student_proc(in c_no int)
reads sql data
begin
select department_name,class_name,student.student_no,student_name,student_contact
from student join classes on student.class_no=classes.class_no
join choose on student.student_no=choose.student_no
where course_no=c_no
order by department_name,class_name,student_no;
end
$$
delimiter ;


delimiter $$
create procedure choose_proc(in s_no char(11),in c_no int,out state int)
modifies sql data
begin
	declare s1 int;
	declare s2 int;
	declare s3 int;
	declare status char(8);
	set state= 0;
	set status='δ���';
	select count(*) into s1 from choose where student_no=s_no and course_no=c_no ;
	if(s1>=1) then 
		set state = -1; 
	else
		select count(*) into s2 from choose where student_no=s_no;
		if(s2>=2) then 
			set state = -2;
		else
			select state into status from course where course_no=c_no;
			select available into s3 from course where course_no=c_no;
			if(s3=0 || status='δ���') then 
				set state = -3;
			else
				insert into choose values(null,s_no,c_no,null,now());
				set state = last_insert_id();
			end if;
		end if;
	end if;
end
$$
delimiter ;

set @state = 0;
call choose_proc('2012003',1,@state);
select @state;
call choose_proc('2012003',2,@state);
select @state;
call choose_proc('2012003',3,@state);
select @state;

drop procedure get_choose_number_proc;

delimiter $$
create procedure choose1_proc(in s_no char(11),in c_no int,out state int)
modifies sql data
begin
	declare s1 int;
	declare s2 int;
	declare s3 int;
	declare status char(8);
	declare continue handler for 1452
		begin
		set @error1 = '���Լ������!';
		end;
	set state= 0;
	set status='δ���';
	select count(*) into s1 from choose where student_no=s_no and course_no=c_no ;
	if(s1>=1) then 
		set state = -1; 
	else
		select count(*) into s2 from choose where student_no=s_no;
		if(s2>=2) then 
			set state = -2;
		else
			select state into status from course where course_no=c_no;
			select available into s3 from course where course_no=c_no;
			if(s3=0 || status='δ���') then 
				set state = -3;
			else
				insert into choose values(null,s_no,c_no,null,now());
				set state = last_insert_id();
set @error2 = '������Ȼ������������Ȼ��������!';
			end if;
		end if;
	end if;
end
$$
delimiter ;


delimiter $$
create procedure update_course_score_proc(in c_no int)
modifies sql data
begin
declare s_no int;
declare grade int;
declare state char(20);
declare score_cursor cursor for select student_no,score from choose where course_no=c_no;
declare continue handler for 1329 set state = 'error';
open score_cursor;
repeat
fetch score_cursor into s_no,grade;
set grade = grade + 5;
if(grade>100) then set grade = 100; end if;
if(grade>=55 && grade<=59) then set grade = 60; end if;
update choose set score=grade where student_no=s_no and course_no=c_no;
until state = 'error'
end repeat; 
close score_cursor;
end
$$
delimiter ;

delimiter $$
create procedure get_class_proc(in class_no int)
reads sql data
begin
set @class_no = class_no;
prepare class_pre from 'select * from classes where class_no=?';
execute class_pre using @class_no;
deallocate prepare class_pre;
end
$$
delimiter ;



#������������

create table account(
account_no int auto_increment primary key,
account_name char(10) not null,
balance int unsigned
) engine=innodb;
insert into account values(null,'��',1000);
insert into account values(null,'��',1000);
delimiter $$
create procedure transfer_proc(in from_account int,in to_account int,in money int)
modifies sql data
begin
update account set balance=balance+money where account_no=to_account;
update account set balance=balance-money where account_no=from_account;
end
$$
delimiter ;

call transfer_proc(1,2,800);
select * from account;

call transfer_proc(1,2,800);
select * from account;

set autocommit=0;
update account set balance=balance+800 where account_no=2;
select * from account;
commit;
set autocommit=1;

drop procedure transfer_proc;
delimiter $$
create procedure transfer_proc (in from_account int,in to_account int,in money int)
modifies sql data
begin
declare continue handler for 1690
begin
rollback;
end;
start transaction;
update account set balance=balance+money where account_no=to_account;
update account set balance=balance-money where account_no=from_account;
commit;
end
$$
delimiter ;


delimiter $$
create procedure save_point1_proc()
modifies sql data
begin
declare continue handler for 1062
begin
rollback to B;
rollback;
end;
start transaction;
insert into account values(null,'��',1000);
savepoint B;
insert into account values(last_insert_id(),'��',1000);
commit;
end
$$
delimiter ;

call save_point1_proc();
select * from account;


delimiter $$
create procedure save_point2_proc()
modifies sql data
begin
declare continue handler for 1062
begin
rollback to B;
commit;
end;
start transaction;
insert into account values(null,'��',1000);
savepoint B;
insert into account values(last_insert_id(),'��',1000);
commit;
end
$$
delimiter ;

call save_point2_proc();
select * from account;


#���δ洢����

delimiter $$
create procedure replace_course_proc(in s_no char(11),in c_before int,in c_after int,out state int)
modifies sql data
begin
	declare s int;
	declare status char(8);
	set state = 0;
	set status='δ���';
	if(c_before=c_after) then 
		set state = -1; 
	else
		start transaction;
		select state into status from course where course_no=c_after;
		select available into s from course where course_no=c_after;
		if(s=0 || status='δ���') then
			set state = -2;
		elseif(state=0) then
			update choose set course_no=c_after,choose_time=now() where student_no=s_no and course_no=c_before;
			update course set available=available+1 where course_no=c_before;
			update course set available=available-1 where course_no=c_after;
			set state = c_after;
		end if;
		commit;
	end if;
end
$$
delimiter ;


set @s_no = '2012002';
set @c_before = 3;
set @c_after = 1;
set @state = 0;
call replace_course_proc(@s_no,@c_before,@c_after,@state);
select @state;


#������


alter table account engine=MyISAM;
lock tables account as a read,account as b write;
select * from account as a;
select * from account as b;
select * from account;
unlock tables;

insert into account values(null,'��',1000);


#�ؽ����δ洢����
drop procedure replace_course_proc;
delimiter $$
create procedure replace_course_proc(in s_no char(11),in c_before int,in c_after int,out state int)
modifies sql data
begin
	declare s int;
	declare status char(8);
	set state = 0;
	set status='δ���';
	if(c_before=c_after) then 
		set state = -1; 
	else
		start transaction;
		select state into status from course where course_no=c_after;
		select available into s from course where course_no=c_after for update;
		if(s=0 || status='δ���') then
			set state = -2;
		elseif(state=0) then
			update choose set course_no=c_after,choose_time=now() where student_no=s_no and course_no=c_before;
			update course set available=available+1 where course_no=c_before;
			update course set available=available-1 where course_no=c_after;
			set state = c_after;
		end if;
		commit;
	end if;
end
$$
delimiter ;

#�ؽ�ѡ�δ洢����
drop procedure choose_proc;
delimiter $$
create procedure choose_proc(in s_no char(11),in c_no int,out state int)
modifies sql data
begin
	declare s1 int;
	declare s2 int;
	declare s3 int;
	declare status char(8);
	set state= 0;
	set status='δ���';
	select count(*) into s1 from choose where student_no=s_no and course_no=c_no ;
	if(s1>=1) then 
		set state = -1; 
	else
		select count(*) into s2 from choose where student_no=s_no;
		if(s2>=2) then 
			set state = -2;
		else
			start transaction;
			select state into status from course where course_no=c_no;
			select available into s3 from course where course_no=c_no for update;
			if(s3=0 || status='δ���') then 
				set state = -3;
			else
				insert into choose values(null,s_no,c_no,null,now());
				set state = last_insert_id();
			end if;
			commit;
		end if;
	end if;
end
$$
delimiter ;

#�м������޸�account��Ĵ洢����
alter table account engine=InnoDB;
insert into account values(20,'��',5000);

drop procedure transfer_proc;
delimiter $$
create procedure transfer_proc(in from_account int,in to_account int,in money int)
modifies sql data
begin
declare continue handler for 1690
begin
rollback;
end;
declare continue handler for 1213
begin
rollback;
end;
start transaction;
update account set balance=balance+money where account_no=to_account;
update account set balance=balance-money where account_no=from_account;
commit;
end
$$
delimiter ;

insert into account values(100,'��',5000);

insert into account values(200,'��',5000);

#��ʮ��
create table admin(
admin_no char(10) primary key,
password char(32) not null,
admin_name char(10)
);
insert into admin values('admin',md5('admin'),'����Ա');


create view course_teacher_view as
select course_no,course_name,up_limit,to_chinese_fn(description) description,teacher.teacher_no,teacher_name,teacher_contact,available,status
from course join teacher on course.teacher_no=teacher.teacher_no;