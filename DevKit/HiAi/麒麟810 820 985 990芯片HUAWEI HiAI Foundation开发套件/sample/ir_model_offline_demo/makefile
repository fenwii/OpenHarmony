##########################################################################################################################
#                                               Compile Descriptions                                                     #
#Before you do the below operations,you should make sure you have installed the make and g++ tools on your environment.  # 
#1. IR compile depends on the libcxx and libcxxabi head files.                                                           #
#2. Please download the head files from the below link :                                                                 #
#    libcxx: https://android.googlesource.com/platform/external/libcxx/+/refs/heads/sdk-release/include/                 #
#    libcxxabi: https://android.googlesource.com/platform/external/libcxxabi/+/refs/heads/sdk-release/include/           #
#3. Create the dir like as mkdir -p external/libcxx/include and mkdir -p external/libcxxabi/include on the current dir.  #
#4. Decompress the head files packages to the dir which created in step 3.                                               #
#5. Compile the source code like : make squeezenet                                                                       #
#6. Link and execute :                                                                                                   #
#   export LD_LIBRARY_PATH=./../../tools/tools_omg/master/lib64                                                          #
#   ./squeezenet                                                                                                         #
##########################################################################################################################
WORK_PATH := .
LIB_C_INCLUDE_PATH := ./external
GRAPH_INCLUDE_PATH := ./../../ddk/ai_ddk_lib/include/
OMG_LIB_PATH := ./../../tools/tools_omg/master/lib64
all:$(TARGET)
squeezenet:squeezenet.o
	g++ $(WORK_PATH)/squeezenet.o -Wl,--whole-archive  -Wl,--no-whole-archive $(OMG_LIB_PATH)/libc++.so -Wl,-rpath-link=$(OMG_LIB_PATH)  -Wl,-z,noexecstack -Wl,-z,relro -Wl,-z,now -Wl,--no-undefined-version -m64 -B$(OMG_LIB_PATH)/lib64 -pie -nodefaultlibs -Wl,--no-undefined $(OMG_LIB_PATH)/libgraph_host.so $(OMG_LIB_PATH)/libhiai_ir_build.so  -o squeezenet -ldl -ldl -lpthread -lm -lrt -s -lgcc_s -lgcc -lc -lgcc_s -lgcc
squeezenet.o:squeezenet.cpp
	g++ -I$(GRAPH_INCLUDE_PATH) -I$(LIB_C_INCLUDE_PATH)/libcxx/include -I$(LIB_C_INCLUDE_PATH)/libcxxabi/include -c  -Wa,--noexecstack -fPIC -U_FORTIFY_SOURCE -D_FORTIFY_SOURCE=2 -fstack-protector -fstack-protector-strong -ftrapv -m64 -fmessage-length=0 -W -Wall -Wno-unused -Winit-self -Wpointer-arith -no-canonical-prefixes -fno-exceptions -Wno-multichar -O2 -g -fno-strict-aliasing -Wformat -Werror=int-conversion -Wno-zero-as-null-pointer-constant -B$(OMG_LIB_PATH)  -Wsign-promo -std=gnu++14  -Wall -Wextra -Werror -Wl,-rpath-link=$(OMG_LIB_PATH) -L $(OMG_LIB_PATH) -Wall -Wno-unused-parameter -fPIE -D_USING_LIBCXX -std=c++11 -fexceptions -nostdinc++ -Werror=int-to-pointer-cast -Werror=pointer-to-int-cast -Werror=return-type -Wno-uninitialized   -MD -MF $(WORK_PATH)/squeezenet.d -o $(WORK_PATH)/squeezenet.o squeezenet.cpp
clean:
	rm -f squeezenet ./*.o ./*.d
