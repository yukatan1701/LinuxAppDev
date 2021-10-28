#!/bin/sh

INPUT_FILE="from.txt"
OUTPUT_FILE="to.txt"
HEADER="[TEST]"
FAILED_TEXT="Test failed."

cp $INPUT_FILE.orig $INPUT_FILE
echo "$HEADER Test for ERR_BAD_OPEN_INPUT (Permission denied) at line 53.";
strace -eopenat -e fault=openat:error=EACCES:when=3 ./move $INPUT_FILE $OUTPUT_FILE
RET_CODE=$?
if [ $RET_CODE -ne 4 ] || [ ! -f "$INPUT_FILE" ]; then
  echo $FAILED_TEXT
  exit $RET_CODE
fi

cp $INPUT_FILE.orig $INPUT_FILE
echo ""
echo "$HEADER Test for ERR_BAD_OPEN_INPUT (Operation not permitted) at line 53.";
strace -eopenat -e fault=openat:error=EPERM:when=3 ./move $INPUT_FILE $OUTPUT_FILE
RET_CODE=$?
if [ $RET_CODE -ne 4 ] || [ ! -f "$INPUT_FILE" ]; then
  echo $FAILED_TEXT
  exit $RET_CODE
fi

cp $INPUT_FILE.orig $INPUT_FILE
echo ""
echo "$HEADER Test for ERR_BAD_OPEN_INPUT (No such file or directory) at line 53.";
strace -eopenat -e fault=openat:error=ENOENT:when=3 ./move $INPUT_FILE $OUTPUT_FILE
RET_CODE=$?
if [ $RET_CODE -ne 4 ]; then
  echo $FAILED_TEXT
  exit $RET_CODE
fi

cp $INPUT_FILE.orig $INPUT_FILE
echo ""
echo "$HEADER Test for ERR_BAD_OPEN_OUTPUT (Permission denied) at line 59.";
strace -eopenat -e fault=openat:error=EACCES:when=4 ./move $INPUT_FILE $OUTPUT_FILE
RET_CODE=$?
if [ $RET_CODE -ne 5 ] || [ ! -f "$INPUT_FILE" ]; then
  echo $FAILED_TEXT
  exit $RET_CODE
fi

cp $INPUT_FILE.orig $INPUT_FILE
echo ""
echo "$HEADER Test for ERR_BAD_OPEN_OUTPUT (Operation not permitted) at line 59.";
strace -eopenat -e fault=openat:error=EPERM:when=4 ./move $INPUT_FILE $OUTPUT_FILE
RET_CODE=$?
if [ $RET_CODE -ne 5 ] || [ ! -f "$INPUT_FILE" ]; then
  echo $FAILED_TEXT
  exit $RET_CODE
fi

cp $INPUT_FILE.orig $INPUT_FILE
rm -f $OUTPUT_FILE
echo ""
echo "$HEADER Test for ERR_BAD_READ_INPUT (Bad file descriptor) at line 78.";
strace -eread -e fault=read:error=EBADF:when=2 ./move $INPUT_FILE $OUTPUT_FILE
RET_CODE=$?
if [ $RET_CODE -ne 9 ] || [ ! -f "$INPUT_FILE" ] || [ -f "$OUTPUT_FILE" ]; then
  echo $FAILED_TEXT
  exit $RET_CODE
fi

cp $INPUT_FILE.orig $INPUT_FILE
rm -f $OUTPUT_FILE
echo ""
echo "$HEADER Test for ERR_BAD_WRITE_OUTPUT (Bad file descriptor) at line 73.";
strace -ewrite -e fault=write:error=EPERM:when=1 ./move $INPUT_FILE $OUTPUT_FILE
RET_CODE=$?
if [ $RET_CODE -ne 3 ] || [ ! -f "$INPUT_FILE" ] ; then
  echo $FAILED_TEXT
  exit $RET_CODE
fi

cp $INPUT_FILE.orig $INPUT_FILE
rm -f $OUTPUT_FILE
echo ""
echo "$HEADER Test for ERR_BAD_DELETE_INPUT (Permission denied) at line 95.";
strace -eunlink -e fault=unlink:error=EACCES:when=1 ./move $INPUT_FILE $OUTPUT_FILE
RET_CODE=$?
if [ $RET_CODE -ne 6 ] || [ ! -f "$INPUT_FILE" ] || [ -f "$OUTPUT_FILE" ]; then
  echo $FAILED_TEXT
  exit $RET_CODE
fi

cp $INPUT_FILE.orig $INPUT_FILE
rm -f $OUTPUT_FILE
echo ""
echo "$HEADER Test for ERR_BAD_DELETE_OUTPUT (Permission denied) at line 97.";
strace -eunlink -e fault=unlink:error=EACCES ./move $INPUT_FILE $OUTPUT_FILE
RET_CODE=$?
if [ $RET_CODE -ne 7 ] || [ ! -f "$INPUT_FILE" ] || [ ! -f "$OUTPUT_FILE" ]; then
  echo $FAILED_TEXT
  exit $RET_CODE
fi

cp $INPUT_FILE.orig $INPUT_FILE
rm -f $OUTPUT_FILE
echo ""
echo "$HEADER Test for ERR_BAD_CLOSE_INPUT (Permission denied) at line 93.";
strace -eclose -e fault=close:error=EACCES:when=4 ./move $INPUT_FILE $OUTPUT_FILE
RET_CODE=$?
if [ $RET_CODE -ne 2 ] || [ ! -f "$INPUT_FILE" ] || [ -f "$OUTPUT_FILE" ]; then
  echo $FAILED_TEXT
  exit $RET_CODE
fi

cp $INPUT_FILE.orig $INPUT_FILE
rm -f $OUTPUT_FILE
echo ""
echo "$HEADER Test for ERR_BAD_CLOSE_OUTPUT (Permission denied) at line 87.";
strace -eclose -e fault=close:error=EACCES:when=3 ./move $INPUT_FILE $OUTPUT_FILE
RET_CODE=$?
if [ $RET_CODE -ne 3 ] || [ ! -f "$INPUT_FILE" ] || [ ! -f "$OUTPUT_FILE" ]; then
  echo $FAILED_TEXT
  exit $RET_CODE
fi

cp $INPUT_FILE.orig PROTECT_$INPUT_FILE
rm -f $OUTPUT_FILE
echo ""
echo "$HEADER Test for LD_PRELOAD."
LD_PRELOAD=`pwd`/fake_unlink.so ./move PROTECT_$INPUT_FILE $OUTPUT_FILE
RET_CODE=$?
if [ $RET_CODE -ne 0 ] || [ ! -f "$INPUT_FILE" ] || [ ! -f "$OUTPUT_FILE" ]; then
  echo $FAILED_TEXT
  exit $RET_CODE
fi

echo "Tested successfully."