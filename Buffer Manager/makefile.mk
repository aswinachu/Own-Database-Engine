buffer_mgr: test_buffer_lru.o storage_mgr.o dberror.o buffer_mgr.o buffer_mgr_stat.o
	gcc -o buffer_mgr test_buffer_lru.o storage_mgr.o dberror.o buffer_mgr.o buffer_mgr_stat.o -lm

storage_mgr.o: storage_mgr.c storage_mgr.h
	gcc -c storage_mgr.c

dberror.o: dberror.c dberror.h
	gcc -c dberror.c

test_buffer_lru.o: test_buffer_lru.c dberror.h storage_mgr.h test_helper.h buffer_mgr.h buffer_mgr_stat.h
	gcc -c test_buffer_lru.c

buffer_mgr.o: buffer_mgr.c buffer_mgr.h
	gcc -c buffer_mgr.c

buffer_mgr_stat.o: buffer_mgr_stat.c buffer_mgr_stat.h
	gcc -c buffer_mgr_stat.c

clean:
	rm -f *.o buffer_mgr

