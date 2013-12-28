OBJ_TYPE_FLAG = -g
CC=gcc
TARGET=cmc
RM_TARGET=cmc 1.func 2.func 3.func 4.func 5.farray 6.farray 7.p_noparams 8.multifunc 9.multifunc 10.param 11.recurs 12.gcd 13.messy 14.bubble 15.bubblerecur
DIRS=parser util codegen 
LIBS=parser/libparser-g.a util/libutil-g.a codegen/libcodegen-g.a 
DOXYGEN_SRC=CminusCompilerDocumentation.Doxyfile
ARGS=input

TEST_CM=TEST_ONE_CM TEST_TWO_CM TEST_THREE_CM TEST_FOUR_CM TEST_FIVE_CM TEST_SIX_CM TEST_SEVEN_CM TEST_EIGHT_CM TEST_NINE_CM TEST_TEN_CM TEST_ELEVEN_CM TEST_TWELVE_CM TEST_THIRTEEN_CM TEST_FOURTEEN_CM TEST_FIFTEEN_CM
TEST_ONE_CM=1.func.cm
TEST_TWO_CM=2.func.cm
TEST_THREE_CM=3.func.cm
TEST_FOUR_CM=4.func.cm
TEST_FIVE_CM=5.farray.cm
TEST_SIX_CM=6.farray.cm
TEST_SEVEN_CM=7.p_noparams.cm
TEST_EIGHT_CM=8.multifunc.cm
TEST_NINE_CM=9.multifunc.cm
TEST_TEN_CM=10.param.cm
TEST_ELEVEN_CM=11.recurs.cm
TEST_TWELVE_CM=12.gcd.cm
TEST_THIRTEEN_CM=13.messy.cm
TEST_FOURTEEN_CM=14.bubble.cm
TEST_FIFTEEN_CM=15.bubblerecur.cm

TEST_ONE_S=1.func.s
TEST_TWO_S=2.func.s
TEST_THREE_S=3.func.s
TEST_FOUR_S=4.func.s
TEST_FIVE_S=5.farray.s
TEST_SIX_S=6.farray.s
TEST_SEVEN_S=7.p_noparams.s
TEST_EIGHT_S=8.multifunc.s
TEST_NINE_S=9.multifunc.s
TEST_TEN_S=10.param.s
TEST_ELEVEN_S=11.recurs.s
TEST_TWELVE_S=12.gcd.s
TEST_THIRTEEN_S=13.messy.s
TEST_FOURTEEN_S=14.bubble.s
TEST_FIFTEEN_S=15.bubblerecur.s

TEST_ONE_EXEC=1.func
TEST_TWO_EXEC=2.func
TEST_THREE_EXEC=3.func
TEST_FOUR_EXEC=4.func
TEST_FIVE_EXEC=5.farray
TEST_SIX_EXEC=6.farray
TEST_SEVEN_EXEC=7.p_noparams
TEST_EIGHT_EXEC=8.multifunc
TEST_NINE_EXEC=9.multifunc
TEST_TEN_EXEC=10.param
TEST_ELEVEN_EXEC=11.recurs
TEST_TWELVE_EXEC=12.gcd
TEST_THIRTEEN_EXEC=13.messy
TEST_FOURTEEN_EXEC=14.bubble
TEST_FIFTEEN_EXEC=15.bubblerecur

RM = /bin/rm -f

CFLAGS	= $(OBJ_TYPE_FLAG) 

.SILENT:

$(TARGET): $(LIBS)
	echo "Creating $@"
	$(CC) $(CFLAGS) -o $@ $(LIBS) 

.PHONY: $(LIBS) clean docs

$(LIBS): 
	echo "Making directory $(dir $@)"
	$(MAKE) -C $(dir $@)

test1:
	make
	./$(TARGET) $(ARGS)/$(TEST_ONE_CM)
	$(CC) -o $(TEST_ONE_EXEC) $(ARGS)/$(TEST_ONE_S)
	echo "Test 1"
	echo "Expected Results"
	echo "----------------"
	echo "inside function"
	echo "10"
	echo "----------------"
	./$(TEST_ONE_EXEC)

test2:
	make
	./$(TARGET) $(ARGS)/$(TEST_TWO_CM)
	$(CC) -o $(TEST_TWO_EXEC) $(ARGS)/$(TEST_TWO_S)
	echo "Test 2"
	echo "Expected Results"
	echo "----------------"
	echo "inside function"
	echo "15"
	echo "----------------"
	./$(TEST_TWO_EXEC)

test3:
	make
	./$(TARGET) $(ARGS)/$(TEST_THREE_CM)
	$(CC) -o $(TEST_THREE_EXEC) $(ARGS)/$(TEST_THREE_S)
	echo "Test 3"
	echo "Expected Results"
	echo "----------------"
	echo "2"
	echo "4"
	echo "----------------"
	./$(TEST_THREE_EXEC)

test4:
	make
	./$(TARGET) $(ARGS)/$(TEST_FOUR_CM)
	$(CC) -o $(TEST_FOUR_EXEC) $(ARGS)/$(TEST_FOUR_S)
	echo "Test 4"
	echo "Expected Results"
	echo "----------------"
	echo "2"
	echo "8"
	echo "----------------"
	./$(TEST_FOUR_EXEC)

test5:
	make
	./$(TARGET) $(ARGS)/$(TEST_FIVE_CM)
	$(CC) -o $(TEST_FIVE_EXEC) $(ARGS)/$(TEST_FIVE_S)
	echo "Test 5"
	echo "Expected Results"
	echo "----------------"
	echo "2"
	echo "8"
	echo "----------------"
	./$(TEST_FIVE_EXEC)

test6:
	make
	./$(TARGET) $(ARGS)/$(TEST_SIX_CM)
	$(CC) -o $(TEST_SIX_EXEC) $(ARGS)/$(TEST_SIX_S)
	echo "Test 6"
	echo "Expected Results"
	echo "----------------"
	echo "4"
	echo "----------------"
	./$(TEST_SIX_EXEC)

test7:
	make
	./$(TARGET) $(ARGS)/$(TEST_SEVEN_CM)
	$(CC) -o $(TEST_SEVEN_EXEC) $(ARGS)/$(TEST_SEVEN_S)
	echo "Test 7"
	echo "Expected Results"
	echo "----------------"
	echo "1"
	echo "1"
	echo "2"
	echo "1"
	echo "1"
	echo "2"
	echo "3"
	echo "1"
	echo "1"
	echo "2"
	echo "1"
	echo "1"
	echo "2"
	echo "3"
	echo "4"
	echo "----------------"
	./$(TEST_SEVEN_EXEC)

test8:
	make
	./$(TARGET) $(ARGS)/$(TEST_EIGHT_CM)
	$(CC) -o $(TEST_EIGHT_EXEC) $(ARGS)/$(TEST_EIGHT_S)
	echo "Test 8"
	echo "Expected Results"
	echo "----------------"
	echo "1"
	echo "2"
	echo "1"
	echo "2"
	echo "----------------"
	./$(TEST_EIGHT_EXEC)

test9:
	make
	./$(TARGET) $(ARGS)/$(TEST_NINE_CM)
	$(CC) -o $(TEST_NINE_EXEC) $(ARGS)/$(TEST_NINE_S)
	echo "Test 9"
	echo "Expected Results"
	echo "----------------"
	echo "1"
	echo "2"
	echo "1"
	echo "4"
	echo "1"
	echo "2"
	echo "1"
	echo "4"
	echo "1"
	echo "2"
	echo "1"
	echo "4"
	echo "1"
	echo "2"
	echo "1"
	echo "8"
	echo "----------------"
	./$(TEST_NINE_EXEC)

test10:
	make
	./$(TARGET) $(ARGS)/$(TEST_TEN_CM)
	$(CC) -o $(TEST_TEN_EXEC) $(ARGS)/$(TEST_TEN_S)
	echo "Test 10"
	echo "Expected Results"
	echo "----------------"
	echo "4"
	echo "3"
	echo "3"
	echo "2"
	echo "400"
	echo "3"
	echo "4"
	echo "2"
	echo "2"
	echo "1"
	echo "2"
	echo "400"
	echo "3"
	echo "4"
	echo "6"
	echo "3"
	echo "400"
	echo "6"
	echo "4"
	echo "400"
	echo "4"
	echo "2"
	echo "2"
	echo "----------------"
	./$(TEST_TEN_EXEC)

test11:
	make
	./$(TARGET) $(ARGS)/$(TEST_ELEVEN_CM)
	$(CC) -o $(TEST_ELEVEN_EXEC) $(ARGS)/$(TEST_ELEVEN_S)
	echo "Test 11"
	echo "Expected Results (for 4)"
	echo "----------------"
	echo "Enter a:"
	echo "4"
	echo "4"
	echo "3"
	echo "2"
	echo "1"
	echo "0"
	echo "0"
	echo "----------------"
	./$(TEST_ELEVEN_EXEC)

test12:
	make
	./$(TARGET) $(ARGS)/$(TEST_TWELVE_CM)
	$(CC) -o $(TEST_TWELVE_EXEC) $(ARGS)/$(TEST_TWELVE_S)
	echo "Test 12"
	echo "Expected Results for (12, 8)"
	echo "----------------"
	echo "4"
	echo "----------------"
	./$(TEST_TWELVE_EXEC)

test13:
	make
	./$(TARGET) $(ARGS)/$(TEST_THIRTEEN_CM)
	$(CC) -o $(TEST_THIRTEEN_EXEC) $(ARGS)/$(TEST_THIRTEEN_S)
	echo "Test 13"
	echo "Expected Results"
	echo "----------------"
	echo "24"
	echo "10"
	echo "1"
	echo "10"
	echo "80"
	echo "----------------"
	./$(TEST_THIRTEEN_EXEC)

test14:
	make
	./$(TARGET) $(ARGS)/$(TEST_FOURTEEN_CM)
	$(CC) -o $(TEST_FOURTEEN_EXEC) $(ARGS)/$(TEST_FOURTEEN_S)
	echo "Test 14"
	echo "Expected Results"
	echo "----------------"
	echo "After initialization"
	echo "20 0's"
	echo "Enter a[3:7]"
	echo "After input"
	echo "20 nums replace 3-7 with entered"
	echo "After sorting"
	echo "Sorted List"
	echo "----------------"
	./$(TEST_FOURTEEN_EXEC)

test15:
	make
	./$(TARGET) $(ARGS)/$(TEST_FIFTEEN_CM)
	$(CC) -o $(TEST_FIFTEEN_EXEC) $(ARGS)/$(TEST_FIFTEEN_S)
	echo "Test 15"
	echo "Expected Results"
	echo "----------------"
	echo "Enter a[0:9]"
	echo "After input"
	echo "10 nums replace 0-9 with entered"
	echo "After sorting"
	echo "Sorted List"
	echo "----------------"
	./$(TEST_FIFTEEN_EXEC)

clean:
	for dir in $(DIRS); do \
		echo "Cleaning directory $$dir"; \
		$(MAKE) -C $$dir clean; \
	done
	$(RM) $(RM_TARGET)

docs:
	doxygen $(DOXYGEN_SRC)
