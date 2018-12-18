#include <string>
#include <iostream>
#include <sstream>
#include <Poco/URI.h>
#include <Poco/Net/HTTPSClientSession.h>
#include <Poco/Net/HTTPRequest.h>
#include <Poco/Net/HTTPResponse.h>
#include <Poco/Dynamic/Var.h>
#include <Poco/JSON/Parser.h>
#include <Poco/StreamCopier.h>
// #include "Poco/Net/Context.h"
// #include "Poco/Net/SSLManager.h"
// #include "Poco/Net/AcceptCertificateHandler.h"
using namespace std;

int main(int argc, char **argv)
{

    // SSL接続情報 初期化
    // Poco::Net::initializeSSL();
    // Poco::Net::SSLManager::InvalidCertificateHandlerPtr ptrHandler ( new Poco::Net::AcceptCertificateHandler(false) );
    // Poco::Net::Context::Ptr ptrContext ( new Poco::Net::Context(Poco::Net::Context::CLIENT_USE, "") );
    // Poco::Net::SSLManager::instance().initializeClient(0, ptrHandler, ptrContext);

	try {
		// Poco::URI uri("http://www.yahoo.co.jp/");
		// Poco::Net::HTTPSClientSession session(uri.getHost(), uri.getPort());
		// Poco::Net::HTTPRequest req("GET", uri.getPath(), Poco::Net::HTTPMessage::HTTP_1_1);
		Poco::URI uri("http://host.docker.internal:3000/movies");
		Poco::Net::HTTPClientSession session(uri.getHost(), uri.getPort());
		Poco::Net::HTTPRequest req("GET", uri.getPath(), Poco::Net::HTTPMessage::HTTP_1_1);

		// リクエスト送信
		ostream& ss = session.sendRequest(req);

		// レスポンス受信
		Poco::Net::HTTPResponse res;
		istream& rs = session.receiveResponse(res);

		stringstream sstr;
		Poco::StreamCopier::copyStream(rs, sstr);

		// [
        //   {
        //     "id": 1,
        //     "name": "The Godfather",
        //     "director": "Francis Ford Coppola",
        //     "rating": 9.1
        //   },
        //   {
        //     "id": 2,
        //     "name": "Casablanca",
        //     "director": "Michael Curtiz",
        //     "rating": 8.8
        //   }
        // ]
		string json = sstr.str();
		// string json = "{ \"test\" : { \"property\" : \"value\" } }";

		Poco::JSON::Parser parser;
		Poco::Dynamic::Var result = parser.parse(json);

		Poco::JSON::Array::Ptr arr = result.extract<Poco::JSON::Array::Ptr>();
        Poco::JSON::Object::Ptr object = arr->getObject(0);

        int id = object->get("id");
        string name = object->get("name");
        string director = object->get("director");
        float rating = object->get("rating");

		cout << string("response:") << id << name << director << rating << endl;
	}
	catch ( Poco::Exception& ex )
	{
		string msg = string("Poco Exception : ") + ex.what() + ", message: " + ex.message();
		cout << msg << endl;
	}

	return 0;
}