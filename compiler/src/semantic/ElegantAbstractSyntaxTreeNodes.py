from __future__ import annotations
from abc import ABC, abstractmethod
from compiler.src.semantic.ElegantSymbolTable import SymbolTable
from compiler.src.codegen.ElegantCodeGenerator import CodeGen, MAX_STR_SIZE


class ElegantNode(ABC):
    index = 0

    def __init__(self, value: str, children: list[ElegantNode]):
        self.value = value
        self.children = children
        self.index = ElegantNode.new_index()

    @abstractmethod
    def evaluate(self, symbol_table: SymbolTable, code_generator: CodeGen):
        pass

    @staticmethod
    def new_index():
        ElegantNode.index += 1
        return ElegantNode.index


class ElegantBinaryOperation(ElegantNode):
    def __init__(self, value: str, children: list[ElegantNode]):
        super().__init__(value, children)

    def evaluate(self, symbol_table: SymbolTable, code_generator: CodeGen):
        child_1_type = self.children[1].evaluate(symbol_table, code_generator)
        code_generator.write_main(f"PUSH EAX")
        child_0_type = self.children[0].evaluate(symbol_table, code_generator)
        code_generator.write_main(f"POP EBX")
        if child_0_type == "INT" and child_1_type == "INT":
            if self.value == "added to":
                code_generator.write_main(f"ADD EAX, EBX")
            elif self.value == "subtracted from":
                code_generator.write_main(f"SUB EBX, EAX")
            elif self.value == "multiplied by":
                code_generator.write_main(f"MUL EBX")
            elif self.value == "divided by":
                code_generator.write_main(f"DIV EBX")
            elif self.value == "or":
                code_generator.write_main(f"OR EAX, EBX")
            elif self.value == "and":
                code_generator.write_main(f"AND EAX, EBX")
            elif self.value == "equates to":
                code_generator.write_main(f"CMP EAX, EBX")
                code_generator.write_main(f"CALL binop_je")
            elif self.value == "differs from":
                code_generator.write_main(f"CMP EAX, EBX")
                code_generator.write_main(f"CALL binop_jne")
            elif self.value == "exceeds":
                code_generator.write_main(f"CMP EAX, EBX")
                code_generator.write_main(f"CALL binop_jg")
            elif self.value == "is less than":
                code_generator.write_main(f"CMP EAX, EBX")
                code_generator.write_main(f"CALL binop_jl")
            else:
                raise Exception(f"Gentle Reminder: The Operator {repr(self.value)} is not recognized as a valid operator for an interaction between types {child_0_type} and {child_1_type}. Kindly review the operator usage.")
            return "INT"
        elif child_0_type == "STRING" and child_1_type == "STRING":
            if self.value == "concatenated with":
                code_generator.write_main(f"; STRING OPERATIONS NOT IMPLEMENTED YET")
                return "STRING"
            elif self.value == "equates to":
                code_generator.write_main(f"; STRING OPERATIONS NOT IMPLEMENTED YET")
            elif self.value == "differs from":
                code_generator.write_main(f"; STRING OPERATIONS NOT IMPLEMENTED YET")
            else:
                raise Exception(f"Gentle Reminder: The Operator {repr(self.value)} is not recognized as a valid operator for an interaction between types {child_0_type} and {child_1_type}. Kindly review the operator usage.")
            return "INT"
        elif child_0_type == "STRING" or child_1_type == "STRING":
            if self.value == "concatenated with":
                code_generator.write_main(f"; STRING OPERATIONS NOT IMPLEMENTED YET")
            else:
                raise Exception(f"Gentle Reminder: The Operator {repr(self.value)} is not recognized as a valid operator for an interaction between types {child_0_type} and {child_1_type}. Kindly review the operator usage.")
            return "STRING"
        else:
            raise Exception(f"Operational Impasse: It appears that the types {child_0_type} and {child_1_type} are not amenable to operations in this context. I kindly suggest verifying the compatibility of the types in question.")


class ElegantUnaryOperation(ElegantNode):
    def __init__(self, value: str, children: list[ElegantNode]):
        super().__init__(value, children)

    def evaluate(self, symbol_table: SymbolTable, code_generator: CodeGen):
        child_0_type = self.children[0].evaluate(symbol_table, code_generator)
        if child_0_type == "INT":
            if self.value == "positively":
                pass
            elif self.value == "negatively":
                code_generator.write_main(f"NEG EAX")
            elif self.value == "not":
                code_generator.write_main(f"TEST EAX, EAX")
                code_generator.write_main(f"SETZ AL")
            else:
                raise Exception(f"Gentle Reminder: The Operator {repr(self.value)} is not recognized as a valid unary operator for an interaction with type {child_0_type}.")
            return "INT"
        else:
            raise Exception(f"Operational Impasse: It appears that the type {child_0_type} is not amenable to unary operations in this context. I kindly suggest verifying the compatibility of the type in question.")


class ElegantIntegerValue(ElegantNode):
    def __init__(self, value: str, children: list[ElegantNode]):
        super().__init__(value, children)

    def evaluate(self, symbol_table: SymbolTable, code_generator: CodeGen):
        code_generator.write_main(f"MOV EAX, {int(self.value)}")
        return "INT"


class ElegantStringValue(ElegantNode):
    def __init__(self, value: str, children: list[ElegantNode]):
        super().__init__(value, children)

    def evaluate(self, symbol_table: SymbolTable, code_generator: CodeGen):
        for i in range(MAX_STR_SIZE):
            code_generator.write_main(f"MOV byte [string_buffer + {i}], 0")
        for i, c in enumerate(self.value):
            code_generator.write_main(f"MOV byte [string_buffer + {i}], {ord(c)}")
        return "STRING"


class ElegantIdentifier(ElegantNode):
    def __init__(self, value: str, children: list[ElegantNode]):
        super().__init__(value, children)

    def evaluate(self, symbol_table: SymbolTable, code_generator: CodeGen):
        identifier_type, identifier_stack_location = symbol_table.get(self.value)
        if identifier_type == "INT":
            code_generator.write_main(f"MOV EAX, [EBP - {identifier_stack_location}]")
        elif identifier_type == "STRING":
            code_generator.write_main(f"MOV EAX, {self.value}")
        return identifier_type


class ElegantVariableDeclaration(ElegantNode):
    def __init__(self, value: str, children: list[ElegantNode]):
        super().__init__(value, children)
    
    def evaluate(self, symbol_table: SymbolTable, code_generator: CodeGen):
        symbol_table.create(self.children[0].value, self.value)
        if self.value == "INT":
            code_generator.write_main(f"PUSH DWORD 0")
        elif self.value == "STRING":
            code_generator.write_bss(f"{self.children[0].value} RESB {MAX_STR_SIZE}")
        if len(self.children) > 1:
            child_1_type = self.children[1].evaluate(symbol_table, code_generator)
            if child_1_type != self.value:
                raise Exception(f"Elegant Misalignment: The type {child_1_type} does not harmonize with a variable of the distinguished type {self.value}. May I suggest a review of the variable's type specification?")

            identifier_type, identifier_stack_location = symbol_table.get(self.children[0].value)
            symbol_table.set(identifier=self.children[0].value, value=(child_1_type, identifier_stack_location))
            if self.value == "INT":
                code_generator.write_main(f"MOV [EBP - {identifier_stack_location}], EAX")
            elif self.value == "STRING":
                for i in range(MAX_STR_SIZE):
                    code_generator.write_main(f"MOV AL, byte [string_buffer + {i}]")
                    code_generator.write_main(f"MOV byte [{self.children[0].value} + {i}], AL")


class ElegantAssignment(ElegantNode):
    def __init__(self, value: str, children: list[ElegantNode]):
        super().__init__(value, children)

    def evaluate(self, symbol_table: SymbolTable, code_generator: CodeGen):
        child_1_type = self.children[1].evaluate(symbol_table, code_generator)
        identifier_type, identifier_stack_location = symbol_table.get(
            self.children[0].value)
        if identifier_type != child_1_type:
            raise Exception(f"Elegant Misalignment: The type {child_1_type} does not harmonize with a variable of the distinguished type {identifier_type}. May I suggest a review of the variable's type specification?")
        symbol_table.set(self.children[0].value,
                         (child_1_type, identifier_stack_location))
        code_generator.write_main(
            f"MOV [EBP - {identifier_stack_location}], EAX")


class ElegantDisplay(ElegantNode):
    def __init__(self, value: str, children: list[ElegantNode]):
        super().__init__(value, children)

    def evaluate(self, symbol_table: SymbolTable, code_generator: CodeGen):
        child_0_type = self.children[0].evaluate(symbol_table, code_generator)
        if child_0_type == "INT":
            code_generator.write_main(f"PUSH EAX")
            code_generator.write_main(f"PUSH formatout")
        elif child_0_type == "STRING":
            code_generator.write_main(f"PUSH string_buffer")
            code_generator.write_main(f"PUSH formatoutstr")
        code_generator.write_main(f"CALL printf")
        code_generator.write_main(f"ADD ESP, 8")


class ElegantSolicitation(ElegantNode):
    def __init__(self, value: str, children: list[ElegantNode]):
        super().__init__(value, children)

    def evaluate(self, symbol_table: SymbolTable, code_generator: CodeGen):
        identifier_type, identifier_stack_location = symbol_table.get(self.children[0].value)
        if identifier_type == "INT":
            code_generator.write_main(f"PUSH scanint")
            code_generator.write_main(f"PUSH formatin")
            code_generator.write_main(f"CALL scanf")
            code_generator.write_main(f"ADD ESP, 8")
            code_generator.write_main(f"MOV EAX, DWORD [scanint]")
            code_generator.write_main(f"MOV [EBP - {identifier_stack_location}], EAX")
        elif identifier_type == "STRING":
            code_generator.write_main(f"PUSH string_buffer")
            code_generator.write_main(f"PUSH formatinstr")
            code_generator.write_main(f"CALL scanf")
            code_generator.write_main(f"ADD ESP, 8")
            for i in range(MAX_STR_SIZE):
                code_generator.write_main(f"MOV AL, byte [string_buffer + {i}]")
                code_generator.write_main(f"MOV byte [{self.children[0].value} + {i}], AL")


class ElegantConditional(ElegantNode):
    def __init__(self, value: str, children: list[ElegantNode]):
        super().__init__(value, children)

    def evaluate(self, symbol_table: SymbolTable, code_generator: CodeGen):
        child_0_type = self.children[0].evaluate(symbol_table, code_generator)
        if child_0_type != "INT":
            raise Exception(f"Refined Type Discordance: The esteemed condition destined for 'In the event that' gracefully accommodates integers alone. However, a variable of the notably distinct type {child_0_type} has been discerned. May I courteously suggest a reevaluation of the type used in the condition?")
        code_generator.write_main(f"CMP EAX, False")
        code_generator.write_main(f"JE EXIT_{self.index}")
        self.children[1].evaluate(symbol_table, code_generator)
        code_generator.write_main(f"JMP COND_EXIT_{self.index}")
        code_generator.write_main(f"EXIT_{self.index}:")
        if len(self.children) > 2:
            self.children[2].evaluate(symbol_table, code_generator)
        code_generator.write_main(f"COND_EXIT_{self.index}:")


class ElegantLoop(ElegantNode):
    def __init__(self, value: str, children: list[ElegantNode]):
        super().__init__(value, children)

    def evaluate(self, symbol_table: SymbolTable, code_generator: CodeGen):
        code_generator.write_main(f"LOOP_{self.index}:")
        code_generator.indent_up()
        self.children[0].evaluate(symbol_table, code_generator)
        code_generator.write_main(f"CMP EAX, False")
        code_generator.write_main(f"JE EXIT_{self.index}")
        self.children[1].evaluate(symbol_table, code_generator)
        code_generator.write_main(f"JMP LOOP_{self.index}")
        code_generator.indent_down()
        code_generator.write_main(f"EXIT_{self.index}:")


class ElegantBlock(ElegantNode):
    def __init__(self, value: str, children: list[ElegantNode]):
        super().__init__(value, children)

    def evaluate(self, symbol_table: SymbolTable, code_generator: CodeGen):
        for child in self.children:
            child.evaluate(symbol_table, code_generator)


class ElegantConversation(ElegantNode):
    def __init__(self, value: str, children: list[ElegantNode]):
        super().__init__(value, children)

    def evaluate(self, symbol_table: SymbolTable, code_generator: CodeGen):
        for child in self.children:
            child.evaluate(symbol_table, code_generator)


class AbsolutelyNoOperation(ElegantNode):
    def __init__(self, value: str, children: list[ElegantNode]):
        super().__init__(value, children)

    def evaluate(self, symbol_table: SymbolTable, code_generator: CodeGen):
        code_generator.write_main(f"NOP")
