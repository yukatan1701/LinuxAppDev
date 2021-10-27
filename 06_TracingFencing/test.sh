#!/bin/sh

INPUT_FILE="from.txt"
HEADER="[TEST]"
FAILED_TEXT="Test failed."

echo "$HEADER Test for ERR_BAD_OPEN_INPUT (Permission denied) at line 53.";
strace -eopenat -e fault=openat:error=EACCES:when=3 ./move from.txt to.txt
if [ $? -ne 4 ] || [ ! -f "$INPUT_FILE" ]; then
  echo $FAILED_TEXT
  exit $?
fi

echo ""
echo "$HEADER Test for ERR_BAD_OPEN_INPUT (Operation not permitted) at line 53.";
strace -eopenat -e fault=openat:error=EPERM:when=3 ./move from.txt to.txt
if [ $? -ne 4 ] || [ ! -f "$INPUT_FILE" ]; then
  echo $FAILED_TEXT
  exit $?
fi

echo ""
echo "$HEADER Test for ERR_BAD_OPEN_INPUT (No such file or directory) at line 53.";
strace -eopenat -e fault=openat:error=ENOENT:when=3 ./move from.txt to.txt
if [ $? -ne 4 ]; then
  echo $FAILED_TEXT
  exit $?
fi

echo ""
echo "$HEADER Test for ERR_BAD_OPEN_OUTPUT (Permission denied) at line 59.";
strace -eopenat -e fault=openat:error=EACCES:when=4 ./move from.txt to.txt
if [ $? -ne 5 ] || [ ! -f "$INPUT_FILE" ]; then
  echo $FAILED_TEXT
  exit $?
fi

echo ""
echo "$HEADER Test for ERR_BAD_OPEN_OUTPUT (Operation not permitted) at line 59.";
strace -eopenat -e fault=openat:error=EPERM:when=4 ./move from.txt to.txt
if [ $? -ne 5 ] || [ ! -f "$INPUT_FILE" ]; then
  echo $FAILED_TEXT
  exit $?
fi

echo "Tested succesfully."