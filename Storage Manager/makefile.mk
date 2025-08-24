assign1:test_storage_basic.o dberror.o storage_mgr.o
	gcc test_storage_basic.o dberror.o storage_mgr.o -o assign1

test_storage_basic.o :test_storage_basic.c test_helper.h dberror.h storage_mgr.h
	gcc -c test_storage_basic.c

dberror.o: dberror.c dberror.h
	gcc -c dberror.c

storage_mgr.o: storage_mgr.c storage_mgr.h
	gcc -c storage_mgr.c

clean:
	rm -f *.o assign1
