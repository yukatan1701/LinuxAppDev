#!/bin/sh
DELAY=$1
TEXT=""
EMPTY_TEXT=""
while IFS= read -r line; do
	LEN=$(/bin/echo -e -n "$line" | wc -c)
	EMPTY_TEXT=$EMPTY_TEXT$(printf %${LEN}s | tr " " " ")'\r'
	TEXT=$TEXT$line'\n'
done

#/bin/echo -e -n "$TEXT"
#/bin/echo -e -n "$EMPTY_TEXT"

EMPTY_LEN=$(/bin/echo -e -n "$EMPTY_TEXT" | wc -c)
#echo $EMPTY_LEN

SEQ=$(seq $EMPTY_LEN | shuf)
#echo $SEQ

for ch in $SEQ; do
	#echo "SEQ: ${ch}"
	CUR_CHAR="$(/bin/echo -e "$TEXT" | cut -z -c${ch})"
	
	if [ "${CUR_CHAR}" = '' ] ; then
		continue
	fi

	#echo "beep"
	CH_MIN="$((ch-1))"
	BEGIN=""
	if [ ${ch} -gt 1 ] ; then
		BEGIN="$(/bin/echo -e "$EMPTY_TEXT" | cut -z -c1-${CH_MIN})"
	fi
	END=""
	CH_PLUS="$((ch+1))"
	if [ ${ch} -lt ${EMPTY_LEN} ] ; then
		END="$(/bin/echo -e "$EMPTY_TEXT" | cut -z -c${CH_PLUS}-${EMPTY_LEN})"
	fi
	EMPTY_TEXT="${BEGIN}${CUR_CHAR}${END}"
	tput clear
	tput cup 0 0
	/bin/echo -n -e "${EMPTY_TEXT}" | tr '\r' '\n'
	sleep ${DELAY}
done
