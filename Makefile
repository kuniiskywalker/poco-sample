
build:
	docker run --rm -it -v ${PWD}:/usr/src kuniiskywalker/docker-poco g++ -o main.o main.cpp -lPocoNetSSL -lPocoUtil -lPocoXML -lPocoJSON -lPocoNet -lPocoFoundation
.PHONY: build

run:
	docker run --rm -it -v ${PWD}:/usr/src kuniiskywalker/docker-poco ./main.o
.PHONY: run
