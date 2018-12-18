#include <cpprest/http_listener.h>
#include <cpprest/uri.h>
#include <dirent.h>
#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>
#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/json.hpp>
// #include <jsoncpp/json/json.h>

using namespace std;

// bsoncxx::stdx::optional<bsoncxx::document::value> query_from_mongo(string term){
web::json::value query_from_mongo(string term, auto collection){
  string out, res;
  web::json::value root_cpp, temp_cpp;
  ofstream fout;
  int i=0;

  mongocxx::cursor cursor = collection.find(
    bsoncxx::builder::stream::document{} << "term" << term << bsoncxx::builder::stream::finalize);
  for(auto doc : cursor) {
    // cout << bsoncxx::to_json(doc) << endl;
    res = bsoncxx::to_json(doc);
    temp_cpp = web::json::value::parse(res);
    root_cpp["term"] = temp_cpp["term"];
    root_cpp["histogram"][i]["date"] = temp_cpp["date"];
    root_cpp["histogram"][i++]["num"] = temp_cpp["num"];
  }
  root_cpp["num_date"] = i;
  
  if (root_cpp["num_date"] != 0)
  {
    fout.open(term + ".json");
    fout << root_cpp;
    fout.close();
  }

  return root_cpp;
}

void handle_GET(web::http::http_request request, auto collection){
  // relative_uri() return the request URI less the listener's path
  // listening to "http://localhost:34568/foo"
  // URL in browser is "http://localhost:34568/foo", then return '/'
  // URL in browser is "http://localhost:34568/foo/aa", then return '/aa'
  web::uri res = request.relative_uri(); 
  string res_str = res.to_string();
  web::json::value root, list_term;
  vector<string> files; 

  // If the browser is requesting a file 
  if (res_str == "/") 
  { 
    // If the request is "/", serve index.html  (homepage)
    string filename = "index.html";  
    ifstream file(filename);  
    stringstream buffer;  
    buffer << file.rdbuf();  
    // Serve the requested file  
    // "text/html" is the type of file, telling browser this is a html file, or browser will just show the source code as a string
    request.reply(web::http::status_codes::OK, buffer.str(), "text/html");  
  } 
  else if (res_str.find("/files/") == 0) 
  {  
    // Get the name of the requested file  
    string filename = res_str.substr(7)+".json";
    ifstream file(filename);  
    stringstream buffer;  
    buffer << file.rdbuf();  
    // Serve the requested file  
    request.reply(web::http::status_codes::OK, buffer.str(), "text/html"); 
  }
  // Get the search term 

  if (res_str.find("/data") == 0) 
  {  
    string term = res_str.substr(6);  
    cout << "get term from html: " << term << endl;

    root = query_from_mongo(term, collection);

    /**********************************************************************/

    struct dirent *ptr;
    vector<string> files;
    DIR *dir;
    string PATH = "./";
    string temp_json;
    dir = opendir(PATH.c_str());
    while((ptr=readdir(dir))!=NULL)
    {
      if(ptr->d_name[0] == '.')
        continue;
      if ( (temp_json = ptr->d_name).find(".json") != string::npos)
      {
        files.push_back(ptr->d_name);
      }
    }
    
    for (int i = 0; i < files.size(); ++i)
    {
      // cout << files[i] << endl;
      root["json"][i] = web::json::value(files[i]);
    }
    closedir(dir);

    /**********************************************************************/
    
    // cout << "here" << endl;
    // web::json::value root_cpp = web::json::value::parse(U("{ \"a\" : 10 }"));
    // cout << root_cpp << endl;

    request.reply(web::http::status_codes::OK, root);
    // request.reply(web::http::status_codes::OK, U("hello world!"));
  }

}

int main() {

  /**********************************************************************/
  string mongouser = "wanzhao";
  string mongopass = "1947chancellor";

  mongocxx::instance inst{};
  mongocxx::client conn{mongocxx::uri{"mongodb://" + mongouser + ":" + mongopass + "@ds157503.mlab.com:57503/wanzhao"}};

  auto collection = conn["wanzhao"]["twitter_top100"];

  /**********************************************************************/

  utility::string_t address = U("http://172.17.0.2:");
  address.append(U("34568"));

  web::uri_builder uri(address);
  // uri.append_path(U("wanzhao"));

  string addr = uri.to_uri().to_string();

  web::http::experimental::listener::http_listener listener(addr);

  listener.support(web::http::methods::GET, [&](web::http::http_request request) {
    handle_GET(request, collection);
  });

  // listener.support(web::http::methods::GET, handle_GET); // why not handle_GET(web::http::http_request request) ??

  listener
  .open()
  .then([]() {std::cout << "Listening on http://localhost:34568...\n";})
  .wait();

  string line;
  getline(std::cin, line);

  listener.close().wait();

  return 0;
}