from __future__ import annotations
from abc import ABC, abstractmethod
from compiler.src.semantic.SymbolTable import SymbolTable
from compiler.src.codegen.CodeGenerator import CodeGen


class Node(ABC):
    index = 0

    def __init__(self, value: str, children: list[Node]):
        self.value = value
        self.children = children
        self.index = Node.new_index()

    @abstractmethod
    def evaluate(self, symbol_table: SymbolTable, code_generator: CodeGen):
        pass

    @staticmethod
    def new_index():
        Node.index += 1
        return Node.index


class ElegantBinaryOperation(Node):
    def __init__(self, value: str, children: list[Node]):
        super().__init__(value, children)

    def evaluate(self, symbol_table: SymbolTable, code_generator: CodeGen):
        child_1_type = self.children[1].evaluate(symbol_table, code_generator)
        code_generator.write_line(f"PUSH EAX")
        child_0_type = self.children[0].evaluate(symbol_table, code_generator)
        code_generator.write_line(f"POP EBX")
        if child_0_type == "INT" and child_1_type == "INT":
            if self.value == "added to":
                code_generator.write_line(f"ADD EAX, EBX")
            elif self.value == "subtracted from":
                code_generator.write_line(f"SUB EBX, EAX")
            elif self.value == "multiplied by":
                code_generator.write_line(f"MUL EBX")
            elif self.value == "divided by":
                code_generator.write_line(f"DIV EBX")
            elif self.value == "or":
                code_generator.write_line(f"OR EAX, EBX")
            elif self.value == "and":
                code_generator.write_line(f"AND EAX, EBX")
            elif self.value == "equates to":
                code_generator.write_line(f"CMP EAX, EBX")
                code_generator.write_line(f"CALL binop_je")
            elif self.value == "differs from":
                code_generator.write_line(f"CMP EAX, EBX")
                code_generator.write_line(f"CALL binop_jne")
            elif self.value == "exceeds":
                code_generator.write_line(f"CMP EAX, EBX")
                code_generator.write_line(f"CALL binop_jg")
            elif self.value == "is less than":
                code_generator.write_line(f"CMP EAX, EBX")
                code_generator.write_line(f"CALL binop_jl")
            else:
                raise Exception(
                    f"Gentle Reminder: The Operator {repr(self.value)} is not recognized as a valid operator for an interaction between types {child_0_type} and {child_1_type}. Kindly review the operator usage.")
            return "INT"
        elif child_0_type == "STRING" and child_1_type == "STRING":
            if self.value == "concatenated with":
                code_generator.write_line(
                    f"; STRING OPERATIONS NOT IMPLEMENTED YET")
                return "STRING"
            elif self.value == "equates to":
                code_generator.write_line(
                    f"; STRING OPERATIONS NOT IMPLEMENTED YET")
                code_generator.write_line(
                    f"; STRING OPERATIONS NOT IMPLEMENTED YET -> CALL binop_je")
            elif self.value == "differs from":
                code_generator.write_line(
                    f"; STRING OPERATIONS NOT IMPLEMENTED YET")
                code_generator.write_line(
                    f"; STRING OPERATIONS NOT IMPLEMENTED YET -> CALL binop_jne")
            else:
                raise Exception(
                    f"Gentle Reminder: The Operator {repr(self.value)} is not recognized as a valid operator for an interaction between types {child_0_type} and {child_1_type}. Kindly review the operator usage.")
            return "INT"
        elif child_0_type == "STRING" or child_1_type == "STRING":
            if self.value == "concatenated with":
                code_generator.write_line(
                    f"; STRING OPERATIONS NOT IMPLEMENTED YET")
            else:
                raise Exception(
                    f"Gentle Reminder: The Operator {repr(self.value)} is not recognized as a valid operator for an interaction between types {child_0_type} and {child_1_type}. Kindly review the operator usage.")
            return "STRING"
        else:
            raise Exception(
                f"Operational Impasse: It appears that the types {child_0_type} and {child_1_type} are not amenable to operations in this context. I kindly suggest verifying the compatibility of the types in question.")


class ElegantUnaryOperation(Node):
    def __init__(self, value: str, children: list[Node]):
        super().__init__(value, children)

    def evaluate(self, symbol_table: SymbolTable, code_generator: CodeGen):
        child_0_type = self.children[0].evaluate(symbol_table, code_generator)
        if child_0_type == "INT":
            if self.value == "positively":
                pass
            elif self.value == "negatively":
                code_generator.write_line(f"NEG EAX")
            elif self.value == "not":
                code_generator.write_line(f"TEST EAX, EAX")
                code_generator.write_line(f"SETZ AL")
            else:
                raise Exception(
                    f"Gentle Reminder: The Operator {repr(self.value)} is not recognized as a valid unary operator for an interaction with type {child_0_type}.")
            return "INT"
        else:
            raise Exception(
                f"Operational Impasse: It appears that the type {child_0_type} is not amenable to unary operations in this context. I kindly suggest verifying the compatibility of the type in question.")


class ElegantIntegerValue(Node):
    def __init__(self, value: str, children: list[Node]):
        super().__init__(value, children)

    def evaluate(self, symbol_table: SymbolTable, code_generator: CodeGen):
        code_generator.write_line(f"MOV EAX, {int(self.value)}")
        return "INT"


class ElegantStringValue(Node):
    def __init__(self, value: str, children: list[Node]):
        super().__init__(value, children)

    def evaluate(self, symbol_table: SymbolTable, code_generator: CodeGen):
        code_generator.write_line(f"; STRING OPERATIONS NOT IMPLEMENTED YET")
        return "STRING"


class ElegantIdentifier(Node):
    def __init__(self, value: str, children: list[Node]):
        super().__init__(value, children)

    def evaluate(self, symbol_table: SymbolTable, code_generator: CodeGen):
        identifier_type, identifier_stack_location = symbol_table.get(
            self.value)
        code_generator.write_line(
            f"MOV EAX, [EBP - {identifier_stack_location}]")
        return identifier_type


class ElegantVariableDeclaration(Node):
    def __init__(self, value: str, children: list[Node]):
        super().__init__(value, children)
    
    def evaluate(self, symbol_table: SymbolTable, code_generator: CodeGen):
        symbol_table.create(self.children[0].value, self.value)
        code_generator.write_line(f"PUSH DWORD 0")
        if len(self.children) > 1:
            child_1_type = self.children[1].evaluate(symbol_table, code_generator)
            if child_1_type != self.value:
                raise Exception(f"Invalid Type Error: Type {child_1_type} is not a valid type for a variable of type {self.value}.")
            identifier_type, identifier_stack_location = symbol_table.get(self.children[0].value)
            symbol_table.set(identifier=self.children[0].value, value=(child_1_type, identifier_stack_location))
            code_generator.write_line(f"MOV [EBP - {identifier_stack_location}], EAX")


class ElegantAssignment(Node):
    def __init__(self, value: str, children: list[Node]):
        super().__init__(value, children)

    def evaluate(self, symbol_table: SymbolTable, code_generator: CodeGen):
        child_1_type = self.children[1].evaluate(symbol_table, code_generator)
        identifier_type, identifier_stack_location = symbol_table.get(
            self.children[0].value)
        if identifier_type != child_1_type:
            raise Exception(
                f"Elegant Misalignment: The type {child_1_type} does not harmonize with a variable of the distinguished type {identifier_type}. May I suggest a review of the variable's type specification?")
        symbol_table.set(self.children[0].value,
                         (child_1_type, identifier_stack_location))
        code_generator.write_line(
            f"MOV [EBP - {identifier_stack_location}], EAX")


class ElegantDisplay(Node):
    def __init__(self, value: str, children: list[Node]):
        super().__init__(value, children)

    def evaluate(self, symbol_table: SymbolTable, code_generator: CodeGen):
        self.children[0].evaluate(symbol_table, code_generator)
        code_generator.write_line(f"PUSH EAX")
        code_generator.write_line(f"PUSH formatout")
        code_generator.write_line(f"CALL printf")
        code_generator.write_line(f"ADD ESP, 8")


class ElegantSolicitation(Node):
    def __init__(self, value: str, children: list[Node]):
        super().__init__(value, children)

    def evaluate(self, symbol_table: SymbolTable, code_generator: CodeGen):
        code_generator.write_line(f"PUSH scanint")
        code_generator.write_line(f"PUSH formatin")
        code_generator.write_line(f"CALL scanf")
        code_generator.write_line(f"ADD ESP, 8")
        code_generator.write_line(f"MOV EAX, DWORD [scanint]")
        identifier_type, identifier_stack_location = symbol_table.get(
            self.children[0].value)
        if identifier_type != "INT":
            raise Exception(
                f"Refined Type Discordance: The esteemed solicitation process is tailored exclusively for integers, yet it appears a variable of the distinguished type {identifier_type} was presented. Might I propose a gracious reconsideration of the variable's type?")
        symbol_table.set(self.children[0].value,
                         ("INT", identifier_stack_location))
        code_generator.write_line(
            f"MOV [EBP - {identifier_stack_location}], EAX")


class ElegantConditional(Node):
    def __init__(self, value: str, children: list[Node]):
        super().__init__(value, children)

    def evaluate(self, symbol_table: SymbolTable, code_generator: CodeGen):
        child_0_type = self.children[0].evaluate(symbol_table, code_generator)
        if child_0_type != "INT":
            raise Exception(
                f"Refined Type Discordance: The esteemed condition destined for 'In the event that' gracefully accommodates integers alone. However, a variable of the notably distinct type {child_0_type} has been discerned. May I courteously suggest a reevaluation of the type used in the condition?")
        code_generator.write_line(f"CMP EAX, False")
        code_generator.write_line(f"JE EXIT_{self.index}")
        self.children[1].evaluate(symbol_table, code_generator)
        code_generator.write_line(f"EXIT_{self.index}:")
        if len(self.children) > 2:
            self.children[2].evaluate(symbol_table, code_generator)


class ElegantLoop(Node):
    def __init__(self, value: str, children: list[Node]):
        super().__init__(value, children)

    def evaluate(self, symbol_table: SymbolTable, code_generator: CodeGen):
        code_generator.write_line(f"LOOP_{self.index}:")
        code_generator.indent_up()
        self.children[0].evaluate(symbol_table, code_generator)
        code_generator.write_line(f"CMP EAX, False")
        code_generator.write_line(f"JE EXIT_{self.index}")
        self.children[1].evaluate(symbol_table, code_generator)
        code_generator.write_line(f"JMP LOOP_{self.index}")
        code_generator.indent_down()
        code_generator.write_line(f"EXIT_{self.index}:")


class ElegantBlock(Node):
    def __init__(self, value: str, children: list[Node]):
        super().__init__(value, children)

    def evaluate(self, symbol_table: SymbolTable, code_generator: CodeGen):
        for child in self.children:
            child.evaluate(symbol_table, code_generator)


class ElegantConversation(Node):
    def __init__(self, value: str, children: list[Node]):
        super().__init__(value, children)

    def evaluate(self, symbol_table: SymbolTable, code_generator: CodeGen):
        for child in self.children:
            child.evaluate(symbol_table, code_generator)


class AbsolutelyNoOperation(Node):
    def __init__(self, value: str, children: list[Node]):
        super().__init__(value, children)

    def evaluate(self, symbol_table: SymbolTable, code_generator: CodeGen):
        code_generator.write_line(f"NOP")
