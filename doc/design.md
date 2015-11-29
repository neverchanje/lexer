
#### Input Format

```
definitions
%%
rules
%%
user code
```

#### Definitions 

The definitions section contains declarations of simple name definitions 
to simplify the scanner specification.

Name definitions have the form:

```
name definition
```

#### Rules

(regular expressions, C codes)

The rules section of the flex input_ contains a series of rules of the form:

```
pattern   action
```

+ default rules

If no match is found, then the default rule is executed: the next character
in the input_ is considered matched and copied to the standard output.

+ default actions 

If the action is empty, then when the pattern is matched the input_ token is 
simply discarded.

+ special directives which can be included within an action

    - ECHO
    
    Copies the matched token to the lexer's output.
    
    - TODO: BEGIN
    
    - TODO: REJECT
    
    - An action consisting solely of a vertical bar (‘|’)
    
    Same as the action for the next rule.
    
    - If the action contains a ‘{’, then the action spans till the balancing ‘}’
     is found, and the action may cross multiple lines.

#### Comments

Anything between '/*' and '*/' is considered a comment.

#### Scanner

+ Scanning Routine
Scan()
 
+ Tables 
A number of tables for matching tokens.

+ Auxiliary
A number of auxiliary routines and macros.

#### TODO(MUST): Multiple Input Buffers
Used in 'include'

#### `<<EOF>>` End-of-FileInput Rules

#### Start Condition
<STRING> means any rules whose pattern is prefixed with "STRING" will be activated.

+ TODO(NOT): inclusive start condition
```
%s
```
rules with no start condition will also be active.

+ exclusive start condition
```
%x
```
only rules qualified with the start condition will be active.

#### Character Class / CCL
```
[abc] // a character class 
```

+ Character Class Expression / CCE
```
         [:alnum:] [:alpha:] [:blank:]
         [:cntrl:] [:digit:] [:graph:]
         [:lower:] [:print:] [:punct:]
         [:space:] [:upper:] [:xdigit:]
```

#### Repeat operator {}

POSIX and AT&T lex place the
precedence of the repeat operator, {}, below that of concatenation.
Thus, ab{3} is ababab.  Most other POSIX utilities use an Extended
Regular Expression (ERE) precedence that has the repeat operator
higher than concatenation.  This causes ab{3} to yield abbb.

