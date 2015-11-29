
#### NFA to DFA Algorithm *Subset Construction*: 
```
{
    Add EpsClosure(s0) into DStates.
    Initialize states in DStates to unmarked.
    WHILE there's an unmarked states T in DStates {
        Mark T.
        FOR EACH input_ symbol a {
            U = EpsClosure(move(T, a))
            IF U is not in DStates {
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
        Pop top element u off S.
        FOR EACH state v with an edge from u to v labeled epsilon {
            IF v is not in EpsClosure(T) {
                Add v to EpsClosure(T)
                Push v onto S.
            }
        }
    }
}
```

#### Beginning States
 
The beginning states are the epsilon closure of the first state.

#### Positive Closure / Kleene Closure

zero or more

#### Data structure of an NFA

Transition tuple (State from, State to, int symbol)

We assume that retrieving an element by a given key costs O(1).

+ **Design 1**
```
unordered_map<State, unordered_map<State, int> > trans_;
```

Find an edge (from, sym, to): O(1)

Get all epsilon-transition out from a state : no exactly

+ **Design 2**
```
unordered_map<State, unordered_map<int, vector<State> > > trans_;
```

Find an edge (from, sym, to): >O(1)

Get all epsilon-transition out from a state : exactly

+ **Design 3**

```
unordered_map<State, unordered_map<int, State> > trans_;
unordered_map<State, vector<State> > eps_trans_;
// Add epsilon transition to eps_trans.
// Create a new state `s` when there's an existed transition labelled `sym`.
// Then add transition(from, SYM_EPSILON, s), and add transition(s, sym, to).
```

Find an edge (from, sym, to) (non-epsilon-symbol sym): O(1)

Find an edge (from, SYM_EPSILON, to) : >O(1)

Get all epsilon-transition out from a state : exactly

+ **Design 4**

```
unordered_map<State, unordered_map<int, vector<State> > > trans1_;
unordered_map<State, unordered_map<State, int> > trans2_;
```

Find an edge (from, sym, to): O(1)

Get all epsilon-transition out from a state : exactly

#### Construction of an NFA from regular expression

+ `r = s | t`

+ `r = st `

+ `r = s*`

+ `r = s+`

+ `r = (s)`
