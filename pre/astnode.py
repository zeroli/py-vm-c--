class BinOpNode(object):
    def __init__(self, op, left, right):
        self.op = op
        self.left = left
        self.right = right

    def accept(self, visitor):
        visitor.visitBinOpNode(self)

class ConstNode(object):
    def __init__(self, value):
        self.value = value

    def accept(self, visitor):
        visitor.visitConstNode(self)
