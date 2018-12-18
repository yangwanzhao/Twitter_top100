g++ server.cc \
	-std=c++14 \
	-lcpprest \
	-lboost_system \
	-lssl \
	-lcrypto \
  	-I/usr/local/lib/libmongodb/build/libmongocxx-install/include/bsoncxx/v_noabi/ \
  	-I/usr/local/lib/libmongodb/build/libmongocxx-install/include/mongocxx/v_noabi/ \
  	-L/usr/local/lib/libmongodb/build/libmongocxx-install/lib/ \
  	-lmongocxx \
  	-lbsoncxx \
  	-ljsoncpp \
  	-Wl,-rpath /usr/local/lib/libmongodb/build/libmongocxx-install/lib/ \
	-o server