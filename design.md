
#### Input Format

```
definitions
%%
rules
%% //user code section can be skipped.
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

The rules section of the flex input contains a series of rules of the form:

```
pattern   action
```

+ default rules

If no match is found, then the default rule is executed: the next character
in the input is considered matched and copied to the standard output.

+ default actions 

If the action is empty, then when the pattern is matched the input token is 
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

#### `<<EOF>>` End-of-File Rules

#### Start Condition
<STRING> means any rules whose pattern is prefixed with "STRING" will be activated.

+ TODO: inclusive start condition
```
%s
```
rules with no start condition will also be active.

+ exclusive start condition
```
%x
```
only rules qualified with the start condition will be active.

