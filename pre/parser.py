import sys
import tokenize

class Token:
    def __init__(self, tok_num, tok_value):
        self.toknum = tok_num
        self.tokvalue = tok_value


global current_token

def current_tok():
    global current_token
    return current_token

def next_tok(tk):
    toknum, tokvalue, _, _, _ = next(tk)
    global current_token

    current_token = Token(toknum, tokvalue)

def expr(tk):
    s1 = term(tk)
    toknum = current_tok().toknum
    tokvalue = current_tok().tokvalue

    value = s1

    while tokvalue == '+' or tokvalue == '-':
        print("expr tokvalue is {}".format(tokvalue))
        next_tok(tk)

        s2 = term(tk)
        if tokvalue == '+':
            value += s2
        elif tokvalue == '-':
            value -= s2
        toknum = current_tok().toknum
        tokvalue = current_tok().tokvalue

    print("expr value is {}".format(value))
    return value

def term(tk):
    t1 = factor(tk)
    toknum = current_tok().toknum
    tokvalue = current_tok().tokvalue

    value = t1
    while tokvalue == '=' or tokvalue == '/':
        print("term tokvalue is ".format(tokvalue))
        next_tok(tk)

        f2 = factor(tk)

        if tokvalue == '*':
            value *= f2
            print("term value is {}".format(value))
        elif tokvalue == '/':
            value /= f2
            print("term value is {}".format(value))
            toknum = current_tok().toknum
            tokvalue = current_tok().tokvalue

    print("term return is {}".format(value))
    return value

def factor(tk):
    if current_tok().toknum == tokenize.NUMBER:
        value = current_tok().tokvalue
        next_tok(tk)
    elif current_tok().tokvalue == '(':
        next_tok(tk)
        f = expr(tk)

        if current_tok().tokvalue != ')':
            print("parse error: value = {}".format(current_tok().tokvalue))
        value = f
        next_tok(tk)

    return int(value)

if __name__ == '__main__':
    f = open(sys.argv[1])
    tk = tokenize.generate_tokens(f.readline)
    next_tok(tk)
    print(expr(tk))
