#!/bin/sh
DELAY=$1
TEXT=""
EMPTY_TEXT=""
while IFS= read -r line; do
	LEN=$(/bin/echo -e -n "$line" | wc -c)
	TAIL=$(printf %${LEN}s | tr " " "=")
	EMPTY_TEXT=$EMPTY_TEXT$TAIL'\t'
	TEXT=$TEXT$line'\n'
done

EMPTY_LEN=$(/bin/echo -e -n "$EMPTY_TEXT" | wc -c)

SEQ=$(seq $EMPTY_LEN | shuf)
#SEQ="2 9 3 10 6 12 11 4 7 14 5 8 15 13 1"

tput clear

HEIGHT=$(tput lines)
WIDTH=$(tput cols)

for ch in $SEQ; do
	#echo "SEQ: ${ch}"
	CUR_CHAR="$(/bin/echo -e "$TEXT" | cut -z -c${ch})"
	if [ "${CUR_CHAR}" = '' ] || [ "${CUR_CHAR}" = ' ' ] ; then
		continue
	fi
	ROW=0
	COL=0
	CH_MIN="$((ch-1))"
	BEGIN=""
	if [ ${ch} -gt 1 ] ; then
		BEGIN="$(/bin/echo -e "$EMPTY_TEXT" | cut -z -c1-${CH_MIN})"
	fi
	ROW=$(/bin/echo -n -e "${BEGIN}" | tr -d -c '\t' | wc -c)
	RES=$(/bin/echo -e "\t")
	TAIL=$(/bin/echo "$BEGIN" | rev | cut -d '	' -f1)
	COL=${#TAIL}
	if [ $ROW -ge $HEIGHT ] || [ $COL -ge $WIDTH ]; then
		continue
	fi

	tput cup $ROW $COL
	/bin/echo -n -e "$CUR_CHAR\b"
	sleep ${DELAY}
done

tput cup $((HEIGHT-1)) 0
