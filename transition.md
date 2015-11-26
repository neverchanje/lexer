
#### NFA to DFA Algorithm *Subset Construction*: 
```
{
    Add EpsClosure(s0) into DStates.
    Initialize states in DStates to unmarked.
    WHILE there's an unmarked states T in DStates {
        Mark T.
        FOR EACH input symbol a {
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

#### Data structure of a Finite Automata

Transition tuple (State from, State to, int symbol)

We assume that retrieving an element by a given key costs O(1).

+ Design 1
```
std::unordered_map<State, std::unordered_map<State, int> > machine_;
```
Traverse all edges out from `from`: exactly
Traverse all edges out from `from` labeled `sym`: no exactly
Traverse all edges out from `from` to `to`: exactly

+ Design 2
```
std::unordered_map<State, std::unordered_map<int, std::vector<State> > > machine_;
```
Traverse all edges out from `from`: exactly
Traverse all edges out from `from` labeled `sym`: exactly
Traverse all edges out from `from` to `to`: no exactly

+ Design 3
```
struct Edge {
    std::unordered_map<int, State> transTo.
    State s;
}
std::unordered_map<State, Edge> machine_;
```
Each Node stores the edges trans out from it.

Traverse all edges out from `from`: exactly
Traverse all edges out from `from` labeled `sym`: exactly
Traverse all edges out from `from` to `to`: no exactly
