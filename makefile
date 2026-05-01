CXX      = x86_64-w64-mingw32-g++
CXXFLAGS = -I./include -Wall
LDFLAGS  = -lws2_32 -lmswsock
SRCS     = $(wildcard src/*.cpp)
OBJS     = $(SRCS:.cpp=.o)
TARGET   = myapp.exe

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)