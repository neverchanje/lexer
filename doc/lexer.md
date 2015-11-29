
# Design of lexer for lexer

Firstly, we must assure that there's no string can be accepted by two different
NFAs.

### Design 1: One Pattern One NFA

```
Algorithm OnePatternOneNFA() {
    // Traverse all NFAs to find if there's an NFA that matches the
    // given string.
}
```

### Design 2: One Pattern One Accept State

```
Algorithm OnePatternOneAccept() {
    // We can use only one NFA which shares states with all patterns.
    // It has much fewer number of states and transitions than Design 1,
    // IF WE DO SOME OPTIMIZATIONS.
}
```


### Definition Section

The ‘name’ is a word beginning with a letter or an underscore (‘_’)
followed by zero or more letters, digits, ‘_’, or ‘-’ (dash).

NAME <= [_a-zA-Z][[a-z][A-Z][0-9]_-]*
