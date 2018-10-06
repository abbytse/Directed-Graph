import sqlite3

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

#insert values into the table
Q2 = """insert into my_graph values (1,5,11), (2,11,2), (3,11,9), (4,11,10), (5,7,11), (6,7,8), (7,8,9),(8,3,8), (9,3,10);
"""

#returns all distinct source ids 
Q3 = """select distinct source_id 
     from my_graph;"""

#returns all link_ids where the source id is larger than destination id 
Q4 = """select link_id
     from my_graph
     where (source_id > destination_id);
"""

#add weight column to each link_id
Q5 = """alter table my_graph
     add weight int;
"""

#randomly assign weight
Q6 = """update my_graph
     set weight = abs(random() % 11);
"""

#return the link with largest value of weight
Q7 = """select link_id
     from my_graph
     where (weight in (select max(weight) from my_graph));
"""

# open a database connection to our local flights database
def connect_database(database_path):
    global conn
    conn = sqlite3.connect(database_path)

def get_all_query_results(debug_print = True):
    all_results = []
    for q, idx in zip([Q1, Q2, Q3, Q4, Q5, Q6, Q7], range(1, 8)):
        result_strings = ("The result for Q%d was:\n%s\n\n" % (idx, from_db_cursor(conn.execute(q)))).splitlines()
        all_results.append(result_strings)
        if debug_print:
            for string in result_strings:
                print (string)
    return all_results

if __name__ == "__main__":
    connect_database('directed_graph.db')
    query_results = get_all_query_results()
