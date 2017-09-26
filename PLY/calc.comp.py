
# -----------------------------------------------------------------------------
# calc.py
#
# A simple calculator with variables -- all in one file.
# -----------------------------------------------------------------------------

reserved = {
    'struct': 'STRUCT'
}

tokens = [
    'NAME','NUMBER',
    'PLUS','MINUS','TIMES','DIVIDE','EQUALS',
    'LPAREN','RPAREN', 'LBRACE', 'RBRACE', 'COMA'

] + list(reserved.values())

# Tokens

t_PLUS    = r'\+'
t_MINUS   = r'-'
t_TIMES   = r'\*'
t_DIVIDE  = r'/'
t_EQUALS  = r'='
t_LPAREN  = r'\('
t_RPAREN  = r'\)'
#t_NAME    = r'[a-zA-Z_][a-zA-Z0-9_]*'
t_NUMBER  = r'\d+'
t_LBRACE  = r'\{'
t_RBRACE  = r'\}'
t_COMA    = r','

'''def t_NUMBER(t):
    r'\d+'
    try:
        t.value = int(t.value)
    except ValueError:
        print("Integer value too large %d", t.value)
        t.value = 0
    return t'''

# Ignored characters
t_ignore = " \t"

def t_NAME(t):
    r'[a-zA-Z_][a-zA-Z0-9_]*'
    t.type = reserved.get(t.value, 'NAME') # Check for reserved words
    return t

def t_newline(t):
    r'\n+'
    t.lexer.lineno += t.value.count("\n")
    
def t_error(t):
    print("Illegal character '%s'" % t.value[0])
    t.lexer.skip(1)
    
# Build the lexer
import ply.lex as lex
lexer = lex.lex()

# Parsing rules

precedence = (
    ('left','PLUS','MINUS'),
    ('left','TIMES','DIVIDE'),
    ('right','UMINUS'),
    )

names = []
f = open('output.py', 'w')

def p_statement_assign(t):
    'statement : NAME EQUALS expression'
    if t[1] not in names:
        names.append(t[1])
    t[0] = '{0} = {1}\n'.format(t[1], t[3])

def p_statement_expr(t):
    'statement : expression'
    if t[1] != None:
        t[0] = '{0}\n'.format(t[1])

def p_statement_struct(t):
    'statement : struct'
    if t[1] != None:
        t[0] = '{0}\n'.format(t[1])

def p_struct(t):
    '''struct : STRUCT NAME LBRACE assignmentlst RBRACE
              | STRUCT NAME LBRACE RBRACE'''
    if t[4] == '}':
        t[0] = '{0} = {{}}'.format(t[2])
    else:
        t[0] = '{0} = {{\n  {1}\n}}'.format(t[2],
            t[4].replace(', ', ',\n  ', t[4].count(',')))

def p_assignmentlst(t):
    '''assignmentlst : assignmentlst COMA NAME EQUALS expression
                     | NAME EQUALS expression'''
    if t[2] == ',':
        t[0] = '{0}, {1}: {2}'.format(t[1], t[3], t[5])
    else:
        t[0] = '{0}: {1}'.format(t[1], t[3])

def p_expression_binop(t):
    '''expression : expression PLUS expression
                  | expression MINUS expression
                  | expression TIMES expression
                  | expression DIVIDE expression'''
    t[0] = '{0} {1} {2}'.format(*t[1:])
    '''if t[2] == '+'  : t[0] = t[1] + t[3]
    elif t[2] == '-': t[0] = t[1] - t[3]
    elif t[2] == '*': t[0] = t[1] * t[3]
    elif t[2] == '/': t[0] = t[1] / t[3]'''

def p_expression_uminus(t):
    'expression : MINUS expression %prec UMINUS'
    t[0] = '-{0}'.format(t[2])

def p_expression_simple(t):
    '''expression : LPAREN expression RPAREN
                  | NUMBER'''
    if t[1] == '(':
        t[0] = '({0})'.format(t[2])
    else:
        t[0] = t[1]

def p_expression_name(t):
    'expression : NAME'
    if t[1] not in names:
        print('Undefined reference: %s'%t[1])
        return
    t[0] = t[1]

def p_error(t):
    print("Syntax error at '%s'" % t.value)

import ply.yacc as yacc

if __name__ == '__main__':
    parser = yacc.yacc()
    output = open('output.py', 'w')

    while True:
        try:
            s = input('calc > ')   # Use raw_input on Python 2
        except EOFError:
            break
        result = parser.parse(s)
        # write to file
        if result is not None:
            output.write(result)