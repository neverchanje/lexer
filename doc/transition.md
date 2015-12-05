
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

***Design 1***
```
//----------- data structure ----------
vector< set<State> > unmarked;
map< set<State>, State > DStates
State maxID
//----------- algorithm ---------------
unmarked.push(EpsClosure(s0))
DStates[EpsClosure(s0)] = maxID++
while(!unmarked.empty()) 
{
    T = unmarked.pop() // mark
    vector<Sym> symlist = GetAllSymFromT(T)
    set<State> U
    for(Sym a in symlist)
    {
        for(State t in T)
        {
            U.insert(nfa.GetTrans(t, a))
        }
        U = nfa.GetEpsClosure(U)
        if(!DStates.find(U)) // U is not in DStates
        {   
            unmarked.push(U)
            DStates[U] = maxID++
        }
        trans[DStates[T], a] = DStates[U]
    }
}
```
Complexity:
Time: O(E)
E is the number of edges in nfa.

***Design 2***
```
//----------- data structure ----------
vector< State > unmarked
vector< set<State> > DStates
State maxID
//----------- algorithm --------------- 
DStates.push(EpsClosure[s0]) // maxID == DStates.size
unmarked.push(maxID++)
while(!unmarked.empty()) 
{
    Tid = unmarked.pop() // mark
    vector<Sym> symlist = GetAllSymFromT(T)
    set<State> U
    for(Sym a in symlist)
    {
        for(State t in T)
        {
            U.insert(nfa.GetTrans(t, a))
        }
        U = nfa.GetEpsClosure(U)
        Uid = DStates.find(U)
        if(!Uid) 
        {
            DStates.push(U)
            Uid = maxID
            unmarked.push(maxID++)
        }
        trans[Tid, a] = Uid
    }
}
```
Time Complexity: O(unmarked.size() ^ 2)
Apparently, this algorithm consumes less memory, but whose time 
consumption is not acceptable.

***Design 3***
```
//----------- data structure ----------
vector< State > unmarked
map< set<State>, State > DStates
State maxID
//----------- algorithm ---------------
table[EpsClosure(s0)] = maxID
unmarked.push(maxID++)
while(!unmarked.empty()) 
{
    Tid = unmarked.pop() // mark
    T = DStates.find(Tid) // O(epsilon.size)
    vector<Sym> symlist = GetAllSymFromT(T)
    set<State> U
    for(Sym a in symlist)
    {
        for(State t in T)
        {
            U.insert(nfa.GetTrans(t, a))
        }
        U = nfa.GetEpsClosure(U)
        if(!DStates.find(U)) {
            DStates[U] = maxID
            unmarked.push(maxID++)
        }
        trans[T, a] = U
    }
}
```
It consumes the same memory as Design 2 and costs the same time
as Design 1. So it seems to be an acceptable choice for our 
implementation.

***Design 4***
Maybe we can have a try on boost::bimap.

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
