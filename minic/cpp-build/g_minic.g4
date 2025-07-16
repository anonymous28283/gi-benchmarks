// $antlr-format alignTrailingComments true, columnLimit 150, minEmptyLines 1, maxEmptyLinesToKeep 1, reflowComments false, useTab false
// $antlr-format allowShortRulesOnASingleLine false, allowShortBlocksOnASingleLine true, alignSemicolons hanging, alignColons hanging

grammar g_minic;
program
    : decl* EOF
    ;
decl
    : var_decl
    | func_decl
    ;
var_decl
    : type idents ';'
    ;
type
    : 'int'
    | 'float'
    | 'bool'
    | 'char'
    ;
idents
    : id_ ',' idents
    | id_
    ;
func_decl
    : rtype id_ '(' args? ')' '{' statement* '}'
    ;
rtype
    : type
    | 'void'
    ;
args
    :  type id_ ',' args
    | type id_
    ;
statement
    : 'if' paren_expr statement
    | 'if' paren_expr statement 'else' statement
    | 'while' paren_expr statement
    | 'do' statement 'while' paren_expr ';'
    | '{' statement* '}'
    | expr ';'
    | ';'
    | var_decl
    ;
params
    : expr ',' params
    | expr
    ;
paren_expr
    : '(' expr ')'
    ;

expr
    : test
    | id_ '=' expr
    ;

test
    : sum_
    | sum_ '<' sum_
    ;

sum_
    : term
    | sum_ '+' term
    | sum_ '-' term
    ;

term
    : id_
    | integer
    | paren_expr
    | id_ '(' params? ')'
    ;

id_
    : STRING
    ;

integer
    : INT
    ;

STRING
    : [a-z]+
    ;

INT
    : [0-9]+
    ;

WS
    : [ \r\n\t] -> skip
    ;