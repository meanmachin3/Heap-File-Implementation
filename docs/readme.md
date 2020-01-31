# Knowledge Repository

## Record.cc

* It contains all the functions required to process one record. For example **toBinary** and **fromBinary** functions convert data to and from binary format to store them in .bin file.
* **composeRecord** makes the record with given schema and the source file name.

## File.cc

* It is the higher abstraction to Record in Db. File object contains number of records based on block size.
* The default block size we used as in most of the database engines ins 4 Kb.
  
## Schema.cc, Catalog.cc

* They contain implemtation fuctions for schema of any table in the database. Schema of the database is stored in catalog file.

## AbstractDbFile.cc, DBFile.cc, Heap.cc, Sort.cc

* They implement heap data structure and sort data structure. DBFile objects abstracts the heap or sort data structure.
  
## BigQ.cc , Pipe.cc, ComparisionEngine.cc and Comparsion.cc

* BigQ uses priorty queues to sort the records with order made by ordermaker.
* It maintains two pipes inputPipe and outputPipe. Data is fed into the input pipe which is sorted based on **External Merge Sort Technique**
BigQs are used not only in the sorted data structure but also to perform Join and Group By operations
