INC_FLAGS = -I. -Iinclude -I$(BOOST_HOME)/include
LIB_FLAGS = -L/usr/lib64

CFLAGS = -std=c++14 -Wall

ifeq ($(OUTPUT_TARGET), -DSHARED_LIB)
    TARGETS = libpywrap.so
    CFLAGS += -fPIC -shared -fno-strict-aliasing
    ifeq ($(PY), -DSUPPORT_PYTHON3)
    INC_FLAGS += -I$(PYTHON3_INC)
    LIB_FLAGS += -lpython3.5
    else
      ifeq ($(PY), -DSUPPORT_PYTHON2)
    INC_FLAGS += -I$(PYTHON2_INC)
    LIB_FLAGS += -lpython2.7
      endif
    endif
else
    TARGETS = X 
endif

ifeq ($(DEBUG), ON)
CFLAGS += -g -O0
else
CFLAGS += -O2
endif

ifeq ($(OPENCV), -DWITH_OPENCV)
    ifeq ($(CV), -DSUPPORT_CV3)
    INC_FLAGS += -I$(OPENCV3_HOME)/include
    LIB_FLAGS += -L$(OPENCV3_HOME)/lib
    else
      ifeq ($(CV), -DSUPPORT_CV2)
    INC_FLAGS += -I$(OPENCV2_HOME)/include
    LIB_FLAGS += -L$(OPENCV2_HOME)/lib
    CFLAGS += -lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_video -lopencv_videostab
      endif
    endif
endif

ifeq ($(LOG4CXX), -DWITH_LOG4CXX)
INC_FLAGS += -I$(LOG4CXX_HOME)/include
LIB_FLAGS += -L$(LOG4CXX_HOME)/lib -llog4cxx
endif

ifeq ($(SUPPORT_SEETATECH), -DWITH_SEETATECH)
INC_FLAGS += -I$(SEETATECH_HOME)/include
LIB_FLAGS += -L$(SEETATECH_HOME)/lib -lVIPLFaceDetector500 -lVIPLPointDetector500
endif

ifeq ($(FILECONF), -DWITH_FILECONF)
INC_FLAGS += -I$(JSONCPP184_HOME)/include
LIB_FLAGS += -L$(JSONCPP184_HOME)/lib -ljsoncpp
endif

ifeq ($(MONGODB), -DWITH_MONGODB)
INC_FLAGS += -I/usr/local/include/libmongoc-1.0
INC_FLAGS += -I/usr/local/include/mongocxx/v_noabi
INC_FLAGS += -I/usr/local/include/bsoncxx/v_noabi
INC_FLAGS += -I/usr/local/include/libbson-1.0
LIB_FLAGS += -lbsoncxx -lmongocxx
endif

ifeq ($(MYSQL), -DWITH_MYSQL)
INC_FLAGS += -I$(MYSQLCPPCONN_HOME)/include
LIB_FLAGS += -L$(MYSQLCPPCONN_HOME)/lib -lmysqlcppconn
endif

ifeq ($(UUID), -DWITH_UUID)
CFLAGS += -luuid
endif

ifeq ($(os_type), Linux)
CFLAGS += -DOS_LINUX
endif

ifeq ($(os_arch), x86_64)
OSARCH = -m64
endif

CFLAGS += $(BOOST)
CFLAGS += $(OPENCV)
CFLAGS += $(LOG4CXX)
CFLAGS += $(FILECONF)
CFLAGS += $(MONGODB)
CFLAGS += $(MYSQL)
CFLAGS += $(OUTPUT_TARGET)
CFLAGS += $(PY)
CFLAGS += $(INC_FLAGS)
CFLAGS += $(LIB_FLAGS)

all:
	g++ src/*.cc $(CFLAGS) -lpthread -o $(TARGETS)
	mv $(TARGETS) release

clean:
	rm release/$(TARGETS) -f
