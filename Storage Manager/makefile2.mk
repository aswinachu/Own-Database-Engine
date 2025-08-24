assign2:test_storage_advanced.o dberror.o storage_mgr.o
	gcc test_storage_advanced.o dberror.o storage_mgr.o -o assign2

test_storage_advanced.o :test_storage_advanced.c test_helper.h dberror.h storage_mgr.h
	gcc -c test_storage_advanced.c

dberror.o: dberror.c dberror.h
	gcc -c dberror.c

storage_mgr.o: storage_mgr.c storage_mgr.h
	gcc -c storage_mgr.c

clean:
	rm -f *.o assign2
