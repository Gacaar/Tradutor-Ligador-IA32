                 SECTION TEXT
INPUT OLD_DATA
LOAD OLD_DATA





L1: DIV DOIS
STORE  NEW_DATA; asdasdasdasdasda
MULT DOIS
STORE TMP_DATA
LOAD OLD_DATA


ADD DOIS



SUB TMP_DATA
STORE TMP_DATA
OUTPUT TMP_DATA
      COPY NEW_DATA, OLD_DATA





LOAD OLD_DATA
JMPP L1
STOP
SECTION DATA
DOIS: CONST 2
OLD_DATA: SPACE
NEW_DATA: SPACE
TMP_DATA: SPACE
