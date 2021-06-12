
Q1
====================
parsePrecedence - PREC_ASSIGNMENT
    grouping
parsePrecedence - PREC_ASSIGNMENT
    unary - TOKEN_MINUS
parsePrecedence - PREC_UNARY
    binary TOKEN_PLUS
parsePrecedence - PREC_FACTOR
    binary TOKEN_STAR
parsePrecedence - PREC_UNARY
    binary TOKEN_MINUS
parsePrecedence - PREC_FACTOR
    binary TOKEN_MINUS
parsePrecedence - PREC_UNARY

Q2
====================
In C:
* TOKEN_STAR - unary dereference, binary multiplication

& TOKEN_AMPERSAND - unary address of, binary bitwise and

