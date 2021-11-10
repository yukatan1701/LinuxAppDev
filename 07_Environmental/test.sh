STATUS=0
for STR in "meow" "Some string to test." "Another one!" "That\`s all."; do
  echo -n "Test string: '$STR'... "
  RES1=$(echo -n "MD5 \"$STR\"" | ./rhasher | tail -n1)
  EX1=$(echo -n "$STR" | md5sum | tail -n1 | tr -d ' ' | tr -d '-')
  RES2=$(echo -n "SHA1 \"$STR\"" | ./rhasher | tail -n1)
  EX2=$(echo -n "$STR" | sha1sum | tail -n1 | tr -d ' ' | tr -d '-')
  if [ "$RES1" != "$EX1" ]; then
    echo "MD5 failed."
    STATUS=1
    break
  elif [ "$RES2" != "$EX2" ]; then
    echo "SHA1 failed."
    STATUS=1
  else
    echo "OK."
  fi
done
if [ $STATUS -ne 0 ]; then
  exit $STATUS
fi
for FILE in "rhasher.c" "rhasher" "$0"; do
  echo -n "Test file '$FILE'... "
  RES1=$(echo -n "MD5 $FILE" | ./rhasher | tail -n1)
  EX1=$(md5sum $FILE | cut -d " " -f1)
  RES2=$(echo -n "SHA1 $FILE" | ./rhasher | tail -n1)
  EX2=$(sha1sum $FILE | cut -d " " -f1)
  if [ "$RES1" != "$EX1" ]; then
    echo "MD5 failed."
    STATUS=1
    break
  elif [ "$RES2" != "$EX2" ]; then
    echo "SHA1 failed."
    STATUS=1
  else
    echo "OK."
  fi  
done


