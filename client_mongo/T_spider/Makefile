CC=g++

MONGOLIB   = /usr/local/lib/libmongodb/build/libmongocxx-install/lib/
MONGOINCL1  = /usr/local/lib/libmongodb/build/libmongocxx-install/include/bsoncxx/v_noabi/
MONGOINCL2  = /usr/local/lib/libmongodb/build/libmongocxx-install/include/mongocxx/v_noabi/
TWILIB = /usr/local/lib/
TWIINCL = ./include/
MONGOLIBFLAGS = -I$(MONGOINCL1) -I$(MONGOINCL2) -L$(MONGOLIB) -lmongocxx -lbsoncxx
TWILIBFLAGS = -I$(TWIINCL) -L$(TWILIB) -ltwitcurl -ljsoncpp

# CXXFLAGS = -std=c++17 $(LIBFLAGS) -mavx

all : twitterClient

libcurl : 
		cd ../libtwitcurl && make install 
		cd ../T_spider
	

twitterClient : libcurl twitterClient.cc
	$(CC) twitterClient.cc $(TWILIBFLAGS) $(MONGOLIBFLAGS) -o twitterClient -Wl,-rpath $(MONGOLIB)

clean : 
		rm twitterClient
		cd ../libtwitcurl && make clean
		cd ../T_spider

