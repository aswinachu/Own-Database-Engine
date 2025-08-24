buffermgr: test_buffer_fifo.o storage_mgr.o dberror.o buffer_mgr.o buffer_mgr_stat.o
	gcc -o buffermgr test_buffer_fifo.o storage_mgr.o dberror.o buffer_mgr.o buffer_mgr_stat.o -lm

storage_mgr.o: storage_mgr.c storage_mgr.h
	gcc -c storage_mgr.c

dberror.o: dberror.c dberror.h
	gcc -c dberror.c

test_buffer_fifo.o: test_buffer_fifo.c dberror.h storage_mgr.h test_helper.h buffer_mgr.h buffer_mgr_stat.h
	gcc -c test_buffer_fifo.c

buffer_mgr.o: buffer_mgr.c buffer_mgr.h
	gcc -c buffer_mgr.c

buffer_mgr_stat.o: buffer_mgr_stat.c buffer_mgr_stat.h
	gcc -c buffer_mgr_stat.c

clean:
	rm -f *.o buffermgr


