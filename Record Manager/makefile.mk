record_mgr: test_record_operations.o dberror.o expr.o record_mgr.o rm_serializer.o storage_mgr.o buffer_mgr.o buffer_mgr_stat.o record_mgr_data_structures.o
	gcc -o record_mgr test_record_operations.o dberror.o expr.o record_mgr.o rm_serializer.o storage_mgr.o buffer_mgr.o buffer_mgr_stat.o record_mgr_data_structures.o -lm

test_expr: test_expr.o dberror.o expr.o record_mgr.o rm_serializer.o storage_mgr.o buffer_mgr.o buffer_mgr_stat.o
	gcc -o test_expr test_expr.o dberror.o expr.o record_mgr.o rm_serializer.o storage_mgr.o buffer_mgr.o -lm buffer_mgr_stat.o 

test_record_operations.o: test_record_operations.c dberror.h storage_mgr.h test_helper.h buffer_mgr.h buffer_mgr_stat.h expr.h tables.h record_mgr.h
	gcc -c test_record_operations.c

record_mgr.o: record_mgr.c record_mgr.h
	gcc -c record_mgr.c

record_mgr_data_structures.o: record_mgr_data_structures.c record_mgr_data_structures.h
	gcc -c record_mgr_data_structures.c

expr.o: expr.c expr.h
	gcc -c expr.c

rm_serializer.o: rm_serializer.c record_mgr.h
	gcc -c rm_serializer.c

buffer_mgr_stat.o: buffer_mgr_stat.c buffer_mgr_stat.h
	gcc -c buffer_mgr_stat.c

buffer_mgr.o: buffer_mgr.c buffer_mgr.h
	gcc -c buffer_mgr.c

storage_mgr.o: storage_mgr.c storage_mgr.h
	gcc -c storage_mgr.c

dberror.o: dberror.c dberror.h
	gcc -c dberror.c

clean:
	rm -f *.o record_mgr




