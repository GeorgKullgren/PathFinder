# SYNOPSIS:
#
#   make [all]  - makes unit tests
#   make clean  - removes all files generated by make.

# Name of test executable
TESTS = myTest

# File containing application main implementation
SRC_MAIN = src/main.cpp

# Choose compiler. g++ or clang++ ?
CXX = clang++

# Flags passed to the C++ compiler.
CXXFLAGS += -g -Wall -Wextra -std=c++14

LDFLAGS = -lpthread

# Choose if gtest or gmock main implementation should be used
GMAIN = gtest

######################################################################
# Where to find user code.
USER_DIR = .
TEST_DIR = test
OBJ_DIR = $(USER_DIR)/obj

######################################################################
# Points to the root of Google Test, relative to where this file is.
# Remember to tweak this if you move this file, or if you want to use
# a copy of Google Test at a different location.
GOOGLE_ROOT = /usr/src/googletest

######################################################################
# Points to the mock and test directories in Google Test.
GTEST_DIR = $(GOOGLE_ROOT)/googletest
GMOCK_DIR = $(GOOGLE_ROOT)/googlemock

######################################################################
# Creating lists of src files and test files
TEST_FILES = $(wildcard test/*.cpp)
TEST_OBJS = $(TEST_FILES:%.cpp=%.o)
TEST_OBJ_FILES = $(addprefix $(OBJ_DIR)/,$(notdir $(TEST_OBJS)))

SRC_FILES = $(filter-out $(SRC_MAIN), $(wildcard src/*.cpp))
OBJS = $(SRC_FILES:%.cpp=%.o)
OBJ_FILES = $(addprefix $(OBJ_DIR)/,$(notdir $(OBJS)))
OBJ_MAIN = $(OBJ_DIR)/main.o

#####################################################################
# All Google Test headers.  Usually you shouldn't change this
# definition.
GTEST_HEADERS = $(GTEST_DIR)/include/gtest/*.h \
                $(GTEST_DIR)/include/gtest/internal/*.h

#####################################################################
# All Google Mock headers. Note that all Google Test headers are
# included here too, as they are #included by Google Mock headers.
# Usually you shouldn't change this definition.	
GMOCK_HEADERS = $(GMOCK_DIR)/include/gmock/*.h \
                $(GMOCK_DIR)/include/gmock/internal/*.h \
                $(GTEST_HEADERS)

# House-keeping build targets.

all : $(OBJ_DIR) $(TESTS)

clean :
	rm -f $(TESTS) $(OBJ_DIR)/*

$(OBJ_DIR) :
	mkdir $(OBJ_DIR)

######################################################################
# Builds gmock.a and gmock_main.a.  These libraries contain both
# Google Mock and Google Test.  A test should link with either gmock.a
# or gmock_main.a, depending on whether it defines its own main()
# function.  It's fine if your test only uses features from Google
# Test (and not Google Mock).

# Usually you shouldn't tweak such internal variables, indicated by a
# trailing _.
GTEST_SRCS_ = $(GTEST_DIR)/src/*.cc $(GTEST_DIR)/src/*.h $(GTEST_HEADERS)
GMOCK_SRCS_ = $(GMOCK_DIR)/src/*.cc $(GMOCK_HEADERS)

# For simplicity and to avoid depending on implementation details of
# Google Mock and Google Test, the dependencies specified below are
# conservative and not optimized.  This is fine as Google Mock and
# Google Test compile fast and for ordinary users their source rarely
# changes.
$(OBJ_DIR)/gtest-all.o : $(GTEST_SRCS_)
	$(CXX) -I$(GTEST_DIR) -I$(GMOCK_DIR) \
            -c $(GTEST_DIR)/src/gtest-all.cc -o $@

$(OBJ_DIR)/gmock-all.o : $(GMOCK_SRCS_)
	$(CXX) -I$(GTEST_DIR) -I$(GMOCK_DIR) \
            -c $(GMOCK_DIR)/src/gmock-all.cc -o $@

$(OBJ_DIR)/gmock_main.o : $(GMOCK_SRCS_)
	$(CXX) -I$(GTEST_DIR) -I$(GMOCK_DIR) \
            -c $(GMOCK_DIR)/src/gmock_main.cc -o $@

$(OBJ_DIR)/gtest_main.o : $(GTEST_SRCS_)
	$(CXX) -I$(GTEST_DIR) -c \
	    $(GTEST_DIR)/src/gtest_main.cc -o $@

$(OBJ_DIR)/gmock.a : $(OBJ_DIR)/gmock-all.o $(OBJ_DIR)/gtest-all.o
	$(AR) $(ARFLAGS) $@ $^

$(OBJ_DIR)/gmock_main.a : $(OBJ_DIR)/gmock-all.o $(OBJ_DIR)/gtest-all.o $(OBJ_DIR)/gmock_main.o
	$(AR) $(ARFLAGS) $@ $^

$(OBJ_DIR)/gtest_main.a : $(OBJ_DIR)/gtest-all.o $(OBJ_DIR)/gtest_main.o
	$(AR) $(ARFLAGS) $@ $^

#######################################################################
# Build rules for test executable

$(OBJ_DIR)/%.o : $(TEST_DIR)/%.cpp $(GMOCK_HEADERS)
	$(CXX) $(CXXFLAGS) -I$(USER_DIR)/src -c $< -o $@

$(TESTS) : $(OBJ_DIR)/$(GMAIN)_main.a $(TEST_OBJ_FILES) $(OBJ_FILES)
	$(CXX) $(LDFLAGS) $^ -o $@

$(OBJ_DIR)/%.o:	src/%.cpp 
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_MAIN):	$(SRC_MAIN) 
	$(CXX) $(CXXFLAGS) -c $< -o $@

#-include $(OBJ_DIR)/*.d