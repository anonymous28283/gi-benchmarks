grammar g_mathexpr;
start: expr EOF;
expr: funccall exprp | VAR exprp | FLOAT exprp | INTEGER exprp | CONSTANT exprp | '(' expr ')' exprp;
exprp: SPACE op SPACE expr |;
funccall: FUNC '(' arglist ')';
arglist: expr | expr ',' SPACE arglist;
op : '+' | '-' | '*' | '/';
FUNC : 'abs'
    | 'acos'
    | 'asin'
    | 'atan2'
    | 'atan'
    | 'ceil'
    | 'cosh'
    | 'cos'
    | 'degrees'
    | 'exp'
    | 'fabs'
    | 'floor'
    | 'fmod'
    | 'frexp'
    | 'hypot'
    | 'ldexp'
    | 'log10'
    | 'log'
    | 'modf'
    | 'pow'
    | 'radians'
    | 'sinh'
    | 'sin'
    | 'sqrt'
    | 'tanh'
    | 'tan';
CONSTANT: 'pi' | 'phi' | 'e';
VAR: ('a'..'z')+ (('a'..'z'|'0'..'9'|'_')+ ('a'..'z'))?;
FLOAT: ('-')? ('0'| '1'..'9' ('0'..'9')*) '.' ('0'..'9')+;
INTEGER: '0' | ('-')?('1'..'9' ('0'..'9')*);
SPACE: ' ';