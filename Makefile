mock:
	json-server db.json
.PHONY: mock

build:
	docker run --rm -it -v ${PWD}:/usr/src kuniiskywalker/docker-poco g++ -o get.o get.cpp -lPocoNetSSL -lPocoUtil -lPocoXML -lPocoJSON -lPocoNet -lPocoFoundation
	docker run --rm -it -v ${PWD}:/usr/src kuniiskywalker/docker-poco g++ -o post.o post.cpp -lPocoNetSSL -lPocoUtil -lPocoXML -lPocoJSON -lPocoNet -lPocoFoundation
.PHONY: build

run:
	docker run --rm -it -v ${PWD}:/usr/src kuniiskywalker/docker-poco ${ARG}
.PHONY: run
