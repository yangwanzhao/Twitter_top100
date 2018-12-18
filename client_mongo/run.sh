c++ --std=c++11 mongotest.cc -o test \
    -I/usr/local/lib/libmongoDB/build/libmongocxx-install/include/mongocxx/v_noabi \
    -I/usr/local/lib/libmongoDB/build/libmongocxx-install/include/bsoncxx/v_noabi \
    -L/usr/local/lib/libmongoDB/build/libmongocxx-install/lib -lmongocxx -lbsoncxx \
    -Wl,-rpath,/usr/local/lib/libmongoDB/build/libmongocxx-install/lib/