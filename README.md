# Examples from
/opt/vertica/sdk/examples

# Build the clean version:

make -f Makefile_vertica_clean clean
make -f Makefile_vertica_clean


# Deploy and test:

cp libAdd2Ints_vertica_clean.so /home/dbadmin/microstructure_query/

1. su - dbadmin
password: dbadmin


2. start the database first the tesdb

vsql -d testdb -f test_add2ints_vertica_clean.sql
password: testdb


vsql -d testdb -f test_add2ints_vertica_clean.sql
Password: 


Result:

CREATE LIBRARY
                       status                        
-----------------------------------------------------
 Add2Ints Vertica clean library created successfully
(1 row)

CREATE FUNCTION
                        status                        
------------------------------------------------------
 Add2Ints Vertica clean function created successfully
(1 row)

                 status                  
-----------------------------------------
 Testing add2ints_vertica_clean function
(1 row)

 result 
--------
      8
(1 row)

CREATE TABLE
TRUNCATE TABLE
 OUTPUT 
--------
      4
(1 row)

 a  | b  | sum_result 
----+----+------------
  1 |  2 |          3
  3 |  4 |          7
  5 |  6 |         11
 10 | 20 |         30
(4 rows)

                    final_status                     
-----------------------------------------------------
 Add2Ints Vertica clean test completed successfully!
(1 row)



