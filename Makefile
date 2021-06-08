play:
	gcc single_thread.c -o single_thread -lpthread
	gcc multi_thread.c -o multi_thread -lpthread
	./single_thread
	./multi_thread