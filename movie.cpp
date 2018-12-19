#include "movie.h"

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

using namespace Poco::Net;
using namespace Poco;

Poco::JSON::Object::Ptr Movie::get(string endpoint)
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
    	Poco::URI uri(endpoint);
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
        //     "name": "Godfather"
        //   },
        //   {
        //     "id": 2,
        //     "name": "Casablanca"
        //   }
        // ]
    	string json = sstr.str();
    	// string json = "[ { \"id\": 2, \"name\": \"Koichi\" } ]";

    	Poco::JSON::Parser parser;
    	Poco::Dynamic::Var result = parser.parse(json);

    	Poco::JSON::Array::Ptr arr = result.extract<Poco::JSON::Array::Ptr>();
        Poco::JSON::Object::Ptr object = arr->getObject(0);

        return object;
    }
    catch ( Poco::Exception& ex )
    {
    	string msg = string("Poco Exception : ") + ex.what() + ", message: " + ex.message();
    	cout << msg << endl;
    }
}

std::string Movie::post(string url, string body, std::map<string,string> headers) {
    try
    {
        // prepare session
        URI uri(url);
        HTTPClientSession session(uri.getHost(), uri.getPort());

        // prepare path
        string path(uri.getPathAndQuery());
        if (path.empty()) path = "/";

        // send request
        HTTPRequest req(HTTPRequest::HTTP_POST, path, HTTPMessage::HTTP_1_1);
        req.setContentType("application/x-www-form-urlencoded");

        // Set headers here
        for(map<string,string>::iterator it = headers.begin();
            it != headers.end(); it++) {
            req.set(it->first, it->second);
        }

        // Set the request body
        req.setContentLength( body.length() );

        // sends request, returns open stream
        std::ostream& os = session.sendRequest(req);
        os << body;  // sends the body
        //req.write(std::cout); // print out request

        // get response
        HTTPResponse res;
        cout << res.getStatus() << " " << res.getReason() << endl;

        istream &is = session.receiveResponse(res);
        stringstream ss;
        StreamCopier::copyStream(is, ss);

        return ss.str();
    }
    catch (Exception &ex)
    {
        cerr << ex.displayText() << endl;
        return "";
    }
}