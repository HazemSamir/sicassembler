.234567890123456789
SUM      START   0
        +STA     TOTAL
FIRST    LDX     #0
         LDA     #0
         BASE    TABLE2
        +LDB     #TABLE2
LOOP     ADD     TABLE,X
         ADD     TABLE2,X
         TIX     COUNT
         JLT     LOOP
         RSUB
COUNT    RESW    1
TABLE    RESW    2000
TABLE2   RESW    2000
TOTAL    RESW    1
         END
