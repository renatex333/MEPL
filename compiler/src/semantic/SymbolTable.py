class SymbolTable:
    def __init__(self):
        self.table = dict()
    
    def get(self, identifier: str):
        try:
            return self.table[identifier]
        except KeyError:
            raise Exception(f"Identifier Error: Identifier '{identifier}' not declared.")
    
    def set(self, identifier: str, value: tuple):
        self.table[identifier] = value

    def create(self, identifier: str, var_type: str):
        if identifier in self.table.keys():
            raise Exception(f"Identifier Error: Identifier '{self.children[0].value}' already declared.")
        self.table[identifier] = (var_type, (len(self.table) + 1) * 4)