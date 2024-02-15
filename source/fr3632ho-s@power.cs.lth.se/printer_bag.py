import gdb


class NodePrinter:
    "Print a Node structure"

    def __init__(self, val):
        self.val = val

    def to_string(self):
        return "Node value: {}".format(self.val)

    def display_hint(self):
        return 'string'

# Register the pretty printer for Node structure
def register_printers(obj):
    obj.printer.pretty_printers.append(NodePrinter)

register_printers(gdb.current_objfile())