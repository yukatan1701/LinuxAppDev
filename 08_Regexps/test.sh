#!/bin/bash

function fcheck {
  S=$1
  REGEX=$2
  SUBST=$3
  if [ ${#S} -eq 0 ] || [ ${#REGEX} -eq 0 ]; then
    echo "Not enough arguments"
    return
  fi
  echo "Test string: '$S'"
  SAMPLE=$(echo "$S" | sed -E "s/$REGEX/$SUBST/")
  echo "sed output: '$SAMPLE'"
  RES=$(./esub "$REGEX" "$SUBST" "$S")
  echo "esub output: '$RES'"
  test "$SAMPLE" == "$RES"
  if [ $? -ne 0 ]; then
    echo "Invalid result on string: '$S'"
    exit 1
  else
    echo "OK."
  fi
}

fcheck "aaabbbCDFGllBRRRt" "([A-Z]+)" "[str: \1]"
fcheck "\\aaaa\\\bgfbgfgb" "(bg)" ""
fcheck "lll MMM mm Op12112 kek151" "([[:digit:]]+)" "br"
fcheck "Op121212" "([[:digit:]]{3})" "{\1}"
fcheck "\\\\\\\\????brrr" "([\\]{3})" "0\1"
fcheck "\\\\\\\\????brrr" "(\\{3})" "0\1"