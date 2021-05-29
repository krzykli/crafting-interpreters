# Interpolation

## What token types would you define to implement a scanner for string interpolation?
TOKEN_STRING_INTERPOLATION

```
print "${drink} will be ready in ${steep + cool} minutes.";
```

## What sequence of tokens would you emit for the above string literal?
TOKEN_STRING
TOKEN_STRING_INTERPOLATION
TOKEN_STRING_INTERPOLATION


## What tokens would you emit for:

```
"Nested ${                                        }"
           "interpolation?! Are you ${         }"  
                                       "mad?!"
```


Recursion:

TOKEN_STRING
TOKEN_STRING_INTERPOLATION
    TOKEN_STRING
    TOKEN_STRING_INTERPOLATION
        TOKEN_STRING


# Generics with >>
TODO
Guess: Multi character lookahead?? Recursion?


# Contextual Keywords
## Name a few contextual keywords from other languages, and the context where they are meaningful

### Java

module

### C++
final (C++11)
override (C++11)
transaction_safe (TM TS)
transaction_safe_dynamic (TM TS)
import (C++20)
module (C++20)

### C#
add	alias	ascending	descending	dynamic	from	get
global	group	into	join	let	orderby	partial (type)
partial(method)	remove	select	set	


## What are the pros and cons of having contextual keywords?
### Pros
- Slightly more expressive language

### Cons
- Higher chance of shadowing keywords by identifiers -> bugs?


## How would you implement them in your language’s front end if you needed to?
Extend Scanner to be aware of the current context and deal with it accordingly.

