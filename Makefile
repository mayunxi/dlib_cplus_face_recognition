#######################
# Makefile
#######################

# compile and lib parameter
CC      := g++ -std=c++11
TARGET	:= libstfz_facematch.so
#############################################################
#############################################################
LDFLAGS :=
DEFINES :=
INCLUDE := -I.
CFLAGS  := 
CXXFLAGS:= 

#link
$(TARGET):stfz_facematch.o
	$(CC) $< -shared -fPIC -o $@
#compile
stfz_facematch.o:stfz_facematch.cpp
	$(CC) -c -fPIC $^ -o $@

# clean
clean:
	rm -fr *.o
	rm -fr $(TARGET)
