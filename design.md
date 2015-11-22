
#### Input Format

```
definitions
%%
rules
%% //user code section can be skipped.
user code //
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

#### Comments

Anything between '/*' and '*/' is considered a comment.

#### Scanner

+ Scanning Routine
yylex()
 
+ Tables 
A number of tables for matching tokens.

+ Auxiliary
A number of auxiliary routines and macros.

