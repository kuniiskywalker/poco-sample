mock:
	json-server db.json
.PHONY: mock

build:
	docker run --rm -it -v ${PWD}:/usr/src kuniiskywalker/docker-poco g++ -o main.o main.cpp movie.cpp -lPocoNetSSL -lPocoUtil -lPocoXML -lPocoJSON -lPocoNet -lPocoFoundation
.PHONY: build

run:
	docker run --rm -it -v ${PWD}:/usr/src kuniiskywalker/docker-poco ./main.o ${ARG}
.PHONY: run
