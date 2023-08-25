class Visitor(object):
    def visit(self, node):
        node.accept(self)

class PrintVisitor(Visitor):
    def visitConstNode(self, node):
        print("{}".format(node.value), end='')

    def visitBinOpNode(self, node):
        print('({}'.format(node.op), end='')
        print(' ', end='')
        self.visit(node.left)
        print(' ', end='')
        self.visit(node.right)
        print(')', end='')

class EmitVisitor(Visitor):
    def visitConstNode(self, node):
        pass

    def visitBinOpNode(self, node):
        pass
