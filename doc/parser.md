# Design of the parser for lexer

+ token: CHAR OR 

+ reductions:
 
LEXER -> DEF_SECT RULE_SECT USER_CODE_SECT

WS -> WS+ | '\t' | ' '

DEF_SECT -> DEF_NAME WS DEF_DEF SECTEND

SECTEND -> %%

CCL -> [CCL] | [NO_BRACKET_CCL]

NO_BRACKET_CCL -> CHAR NO_BRACKET_CCL | ^ NO_BRACKET_CCL | CHAR

+ semantic value && semantic action 

| Semantic Value | Semantic Action |
| ------------- | ----------- |
|       | |
------------