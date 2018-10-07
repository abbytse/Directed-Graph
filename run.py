import sqlite3
import pandas as pd

# connecting to the database  
connection = sqlite3.connect("directed_graph.db") 

# cursor  
crsr = connection.cursor()

#create database called directed_graph
#create table called my_graph (Nodes: source, destination; Links: link)
#schema- my_graph(link_id: int, source_id: int, destination_id: int)
#sqlite3 directed_graph.db
Q1 = """create table my_graph(
    link_id int,
    source_id int,
    destination_id int,
    primary key (link_id)
);"""

# execute the statement 
crsr.execute(Q1)

print ("Q1")
print (pd.read_sql_query("select * from my_graph", connection))

#insert values into the table
Q2 = """insert into my_graph values (1,5,11), (2,11,2), (3,11,9), (4,11,10), (5,7,11), (6,7,8), (7,8,9),(8,3,8), (9,3,10);
"""
# execute the statement 
crsr.execute(Q2)

print ("Q2")
print (pd.read_sql_query("select * from my_graph", connection))

#returns all distinct source ids 
Q3 = """select distinct source_id 
     from my_graph;"""
# execute the statement 
crsr.execute(Q3)

print ("Q3")
print (pd.read_sql_query("select * from my_graph", connection))

#returns all link_ids where the source id is larger than destination id 
Q4 = """select link_id
     from my_graph
     where (source_id > destination_id);
"""
# execute the statement 
crsr.execute(Q4)

print ("Q4")
print (pd.read_sql_query("select * from my_graph", connection))

#add weight column to each link_id
Q5 = """alter table my_graph
     add weight int;
"""
# execute the statement 
crsr.execute(Q5)

print ("Q5")
print (pd.read_sql_query("select * from my_graph", connection))

#randomly assign weight
Q6 = """update my_graph
     set weight = abs(random() % 11);
"""
# execute the statement 
crsr.execute(Q6)

print ("Q6")
print (pd.read_sql_query("select * from my_graph", connection))

#return the link with largest value of weight
Q7 = """select link_id
     from my_graph
     where (weight in (select max(weight) from my_graph));
"""
# execute the statement 
crsr.execute(Q7)

print ("Q7")
print (pd.read_sql_query("select * from my_graph", connection))

#drop table
Q8 = """drop table if exists my_graph;"""
crsr.execute(Q8)

# To save the changes in the files. 
# If we skip this, nothing will be saved in the database. 
connection.commit() 
  
# close the connection 
connection.close() 
