# PLY 分析

```python
# 0x02*0b011
# 0b011*1e2

# "aa"+0.1
# 0.1+"aa"
# "aa"-0.1
# "aa"*0.1
# 0.1*"aa"
# "aa"*2
# "aa"*0b011

# 0b0011+0.1
# 0b0011*0.1

# "aaa"+"aaa"

# 2^2^2
# 2^1.2

# a=b=c=1

# calc > a=b=c=4
# calc > a
# 4
# calc > b
# 4
# calc > c
# 4
# calc > d=a+b
# calc > d
# 8
# calc > e=b/c
# calc > e
# 1
# calc > f = a=d+e
# calc > f
# 13

# calc > a=b=c="aaa"
# calc > a
# "aaa"
```

```python
import sys

sys.path.insert(0, "../..")

if sys.version_info[0] >= 3:
    raw_input = input

tokens = (
    'NAME', 'NUMBER', 'EXPONENT', 'STRING'
)

literals = ['=', '+', '-', '*', '/', '(', ')']

# Tokens
t_NAME = r'[a-zA-Z_][a-zA-Z0-9_]*'
# t_STRING = r'\"[a-zA-Z0-9_]*\"'

def t_STRING(t):
    r'\".*?\"'
    t.value = str(t.value[1:-1])  # remove quotation marks
    return t

def t_NUMBER(t):
    r'0[bB][01]+|0[oO][0-7]+|0[xX][0-9a-fA-F]+|\d+\.\d*([eE][-+]?\d+)?|\d+([eE][-+]?\d+)?'
    try:
        t.value = int(t.value, 0)
    except ValueError:
        t.value = float(t.value)
    return t

t_EXPONENT = r'\^'
t_ignore = " \t"

def t_newline(t):
    r'\n+'
    t.lexer.lineno += t.value.count("\n")

def t_error(t):
    print("Illegal character '%s'" % t.value[0])
    t.lexer.skip(1)

# Build the lexer
import ply.lex as lex

lex.lex()

precedence = (
    ('right', 'UMINUS'),
    ('left', '+', '-'),
    ('left', '*', '/'),
    ('right', 'EXPONENT'),
)

names = {}

# ------------------------------------------------
# def p_statement_assign(p):
#     """statement : NAME "=" expression"""
#     names[p[1]] = p[3]
#     p[0] = p[3]
#     print("-------" + str(names))
#
# def p_statement_string(p):
#     """statement : NAME "=" STRING"""
#     names[p[1]] = p[3]
#     p[0] = p[3]
#     print("-------" + str(names))
#
# def p_statement_assignCon(p):
#     """statement : NAME "=" statement"""
#     names[p[1]] = p[3]
#     p[0] = p[3]
#     print("-------" + str(names))

# expression 数字
# statement 赋值
# string 字符
# ------------------------------------------------
def p_statement_assign(p):
    """statement : NAME "=" STRING
                 | NAME "=" statement
                 | NAME "=" expression"""
    names[p[1]] = p[3]
    p[0] = p[3]
    print("-------" + str(names))

def p_statement_expr(p):
    """statement : STRING
                 | expression"""
    print(p[1])

def p_expression_binop(p):
    '''expression : expression '+' expression
                  | expression '-' expression
                  | expression '*' expression
                  | expression '/' expression
                  | expression EXPONENT expression'''
    if isinstance(p[1], str) and isinstance(p[3], str) and p[2] == '+':
        p[0] = p[1] + p[3]
    elif isinstance(p[1], str) and isinstance(p[3], float) and p[2] == '+':
        print("Error: Cannot perform additive arithmetic operations on numbers and strings")
    elif isinstance(p[1], str) and isinstance(p[3], int) and p[2] == '+':
        print("Error: Cannot perform additive arithmetic operations on numbers and strings")
    elif isinstance(p[1], int) and isinstance(p[3], str) and p[2] == '+':
        print("Error: Cannot perform additive arithmetic operations on numbers and strings")
    elif isinstance(p[1], float) and isinstance(p[3], str) and p[2] == '+':
        print("Error: Cannot perform additive arithmetic operations on numbers and strings")

    elif isinstance(p[1], str) and isinstance(p[3], int) and p[2] == '*':
        p[0] = p[1] * p[3]
    elif isinstance(p[1], int) and isinstance(p[3], str) and p[2] == '*':
        p[0] = p[3] * p[1]
    elif isinstance(p[1], int) and isinstance(p[3], int) and p[2] == '*':
        p[0] = p[1] * p[3]
    elif isinstance(p[1], str) and isinstance(p[3], float) and p[2] == '*':
        print("Error: cannot perform arithmetic on float and string")
    elif isinstance(p[1], float) and isinstance(p[3], str) and p[2] == '*':
        print("Error: cannot perform arithmetic on float and string")

    elif (isinstance(p[1], str) or isinstance(p[3], str)) and p[2] == '/':
        print("Error: Cannot perform division operations on numbers and strings")
    elif (isinstance(p[1], str) or isinstance(p[3], str)) and p[2] == '-':
        print("Error: Cannot perform subtraction operations on numbers and strings")

    else:
        if p[2] == '+':
            p[0] = p[1] + p[3]
        elif p[2] == '-':
            p[0] = p[1] - p[3]
        elif p[2] == '*':
            p[0] = p[1] * p[3]
        elif p[2] == '/':
            p[0] = p[1] / p[3]
        elif p[2] == '^':
            p[0] = p[1] ** p[3]

def p_expression_uminus(p):
    "expression : '-' expression %prec UMINUS"
    p[0] = -p[2]

def p_expression_group(p):
    "expression : '(' expression ')'"
    p[0] = p[2]

def p_expression_number(p):
    "expression : NUMBER"
    p[0] = p[1]

def p_expression_string(p):
    "expression : STRING"
    p[0] = p[1]

def p_expression_name(p):
    "expression : NAME"
    try:
        p[0] = names[p[1]]
    except LookupError:
        print("Undefined name '%s'" % p[1])
        p[0] = 0

def p_error(p):
    if p:
        print("Syntax error at '%s'" % p.value)
    else:
        print("Syntax error at EOF")

import ply.yacc as yacc

yacc.yacc()

while True:
    try:
        s = raw_input('calc > ')
    except EOFError:
        break
    if not s:
        continue
    yacc.parse(s)
```