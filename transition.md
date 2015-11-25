

#### Start State
StartState = 1

#### NiL State
NilState = 0

#### NFA to DFA Algorithm *Subset Construction*: 
```
{
    Add EpsClosure(s0) into DStates.
    Initialize states in DStates to unmarked.
    WHILE there's an unmarked states T in DStates {
        Mark T.
        FOR EACH input symbol a {
            U = EpsClosure(move(T, a))
            if(U is not in DStates) {
                Add U as an unmarked state to DStates.
            }
            DStates[T, a] = U.
        }
    }
}
```

#### Epsilon Closure (A set of NFA states T)
```
{
    Stack S.
    Push all states of T onto S.
    WHILE S is not empty {
        Pop top element v from S.
        FOR EACH state v with an edge from u to v labeled epsilon {
            IF v is not in EpsClosure(T) {
                Add v to EpsClosure(T)
                push v onto S.
            }
        }
    }
}
```

