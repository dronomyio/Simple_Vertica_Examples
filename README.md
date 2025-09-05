# Examples from
/opt/vertica/sdk/examples

# Build the clean version:

```
make -f Makefile_vertica_clean clean
make -f Makefile_vertica_clean
```


# Deploy and test:

cp libAdd2Ints_vertica_clean.so /home/dbadmin/microstructure_query/

```
1. su - dbadmin
password: dbadmin
```


2. start the database first the tesdb
```
vsql -d testdb -f test_add2ints_vertica_clean.sql
password: testdb


Initial error:

vsql -d testdb -f test_add2ints_symbol_fixed.sql
Password: 
vsql:test_add2ints_symbol_fixed.sql:4: ROLLBACK 3399:  Failure in UDx RPC call InvokeGetLibraryInfo(): Error calling setupExecContext() in User Defined Object [] at [/data/jenkins/workspace/RE-ReleaseBuilds/RE-Miner/server/vertica/OSS/UDxFence/vertica-udx-C++.cpp:243], error code: 0, message: Error happened in dlopen(): [/home/dbadmin/microstructure_query/libAdd2Ints_fixed.so: undefined symbol: _ZNK7Vertica12VerticaBlock24checkStringUserBlockInfoEm]

FIX:

Error because of:

The Solution (from Vertica Support):
Add /opt/vertica/sdk/include/Vertica.cpp to the compilation command
Before (Failed):
Bash
g++ -I /opt/vertica/sdk/include -shared -fPIC -std=c++11 -o libAdd2Ints.so Add2Ints.cpp

Result: undefined symbol: vt_throw_exception


and FIX add /opt/vertica/sdk/include/Vertica.cpp

make fix:
g++ -I /opt/vertica/sdk/include -shared -fPIC -std=c++11 -o libAdd2Ints.so Add2Ints.cpp /opt/vertica/sdk/include/Vertica.cpp

sql fix:

Use correct SQL syntax - CREATE FUNCTION name AS LANGUAGE 'C++' NAME 'FactoryName' LIBRARY LibName

 Use lowercase function names - add2ints not Add2Ints




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


```
