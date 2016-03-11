record_mgr: test_assign3_1.o dberror.o expr.o record_mgr.o rm_serializer.o storage_mgr.o buffer_mgr.o buffer_mgr_stat.o record_mgr_data_structures.o
	gcc -o record_mgr test_assign3_1.o dberror.o expr.o record_mgr.o rm_serializer.o storage_mgr.o buffer_mgr.o buffer_mgr_stat.o record_mgr_data_structures.o -lm

test_expr: test_expr.o dberror.o expr.o record_mgr.o rm_serializer.o storage_mgr.o buffer_mgr.o buffer_mgr_stat.o
	gcc -o test_expr test_expr.o dberror.o expr.o record_mgr.o rm_serializer.o storage_mgr.o buffer_mgr.o -lm buffer_mgr_stat.o 

test_assign3_1.o: test_assign3_1.c dberror.h storage_mgr.h test_helper.h buffer_mgr.h buffer_mgr_stat.h
	gcc -c test_assign3_1.c -lm

test_expr.o: test_expr.c dberror.h expr.h record_mgr.h tables.h test_helper.h
	gcc -c test_expr.c -lm

record_mgr.o: record_mgr.c record_mgr.h buffer_mgr.h storage_mgr.h record_mgr_data_structures.h
	gcc -c  record_mgr.c

record_mgr_data_structures.o: record_mgr_data_structures.c record_mgr_data_structures.h
	gcc -c record_mgr_data_structures.c

expr.o: expr.c dberror.h record_mgr.h expr.h tables.h
	gcc -c expr.c

rm_serializer.o: rm_serializer.c dberror.h tables.h record_mgr.h
	gcc -c rm_serializer.c

buffer_mgr_stat.o: buffer_mgr_stat.c buffer_mgr_stat.h buffer_mgr.h
	gcc -c buffer_mgr_stat.c

buffer_mgr.o: buffer_mgr.c buffer_mgr.h dt.h storage_mgr.h record_mgr_data_structures.h
	gcc -c buffer_mgr.c

storage_mgr.o: storage_mgr.c storage_mgr.h 
	gcc -c storage_mgr.c -lm

dberror.o: dberror.c dberror.h 
	gcc -c dberror.c




