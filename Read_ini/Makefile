# https://seisman.github.io/how-to-write-makefile/introduction.html#id9
# 扩展通配符，搜索指定文件。在此我们使用src = $(wildcard ./*.cpp)，代表在当前目录下搜索所有的.cpp文件，并赋值给src
src = $(wildcard ./*.cpp)
include = $(wildcard ./*.h)  
# 替换通配符，按指定规则做替换。在此我们使用 代表将src里的每个文件都由.cpp替换成.o
obj = $(patsubst %.cpp, %.o, $(src))    
# 编译选项 c++使用CXX c使用CC  
CXXFLAGS += -std=c++11
CXXFLAGS += -g
# 目标文件 不可与*.o文件同名
target = Read_ini_test.out
CXX = g++
$(target): $(obj)  
	$(CXX) $(CXXFLAGS) $(obj) -o $(target) 
%.o: %.c  
	$(CXX) $@ $(CXXFLAGS) -c $< -o $(include)
.PHONY: clean  
clean:  
	rm -rf *.o


