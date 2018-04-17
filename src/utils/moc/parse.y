%{

#include <stdio.h>
#include <string.h>
#include "moc_actions.h"

#define EMPTY strdup("");
#define YYDEBUG 1
#define YYPRINT(file, type, value)   yyprint (file, type, value)

%}

// Symbols. //
%union
{        
        char	*sval;
};

%token MOC_PROPERTY MOC_OBJECT_PARAMETERS
%type <sval> MOC_monk_seq_opt MOC_monk



%token <sval> IDENTIFIER
%token <sval> INTEGER FLOATING CHARACTER STRING
%token <sval> TYPEDEF_NAME NAMESPACE_NAME CLASS_NAME ENUM_NAME TEMPLATE_NAME

%token <sval> COLONCOLON
%token <sval> ELLIPSIS DOTSTAR ADDEQ SUBEQ MULEQ DIVEQ MODEQ
%token <sval> XOREQ ANDEQ OREQ SL SR SREQ SLEQ EQ NOTEQ LTEQ GTEQ ANDAND OROR
%token <sval> PLUSPLUS MINUSMINUS ARROWSTAR ARROW


%token <sval> ASM AUTO BOOL BREAK CASE CATCH CHAR CLASS CONST CONST_CAST CONTINUE
%token <sval> DEFAULT DELETE DO DOUBLE DYNAMIC_CAST ELSE ENUM EXPLICIT EXPORT EXTERN
%token <sval> FALSE FLOAT FOR FRIEND GOTO IF INLINE INT LONG MUTABLE NAMESPACE NEW
%token <sval> OPERATOR PRIVATE PROTECTED PUBLIC REGISTER REINTERPRET_CAST RETURN
%token <sval> SHORT SIGNED SIZEOF STATIC STATIC_CAST STRUCT SWITCH TEMPLATE THIS
%token <sval> THROW TRUE TRY TYPEDEF TYPEID TYPENAME UNION UNSIGNED USING VIRTUAL
%token <sval> VOID VOLATILE WCHAR_T WHILE




%type <sval> type_name class_name enum_name typedef_name

%type <sval> simple_type_specifier
%type <sval> decl_specifier_seq decl_specifier
%type <sval> simple_declaration block_declaration

%type <sval> init_declarator_list init_declarator
%type <sval> initializer initializer_clause
%type <sval> declarator direct_declarator ptr_operator declarator_id
%type <sval> type_specifier type_specifier_seq elaborated_type_specifier class_key nested_name_specifier template_argument_list
%type <sval> enum_specifier enumerator_list enumerator_definition enumerator
%type <sval> class_or_namespace_name
%type <sval> identifier
%type <sval> id_expression
%type <sval> constant_expression


%type <sval> declaration_seq_opt
%type <sval> TEMPLATE_opt
%type <sval> nested_name_specifier_opt
%type <sval> expression_list_opt
%type <sval> COLONCOLON_opt
%type <sval> new_placement_opt
%type <sval> new_initializer_opt
%type <sval> new_declarator_opt
%type <sval> expression_opt
%type <sval> statement_seq_opt
%type <sval> condition_opt
%type <sval> decl_specifier_seq_opt
%type <sval> init_declarator_list_opt
%type <sval> identifier_opt
%type <sval> enumerator_list_opt
%type <sval> TYPENAME_opt
%type <sval> initializer_opt
%type <sval> cv_qualifier_seq_opt
%type <sval> exception_specification_opt
%type <sval> constant_expression_opt
%type <sval> abstract_declarator_opt
%type <sval> type_specifier_seq_opt
%type <sval> direct_abstract_declarator_opt
%type <sval> parameter_declaration_list_opt
%type <sval> ELLIPSIS_opt
%type <sval> ctor_initializer_opt
%type <sval> COMMA_opt
%type <sval> member_specification_opt
%type <sval> base_clause_opt
%type <sval> member_declarator_list_opt
%type <sval> SEMICOLON_opt
%type <sval> pure_specifier_opt
%type <sval> constant_initializer_opt
%type <sval> access_specifier_opt
%type <sval> VIRTUAL_opt
%type <sval> conversion_declarator_opt
%type <sval> EXPORT_opt
%type <sval> handler_seq_opt
%type <sval> assignment_expression_opt
%type <sval> type_id_list_opt


%error-verbose
//%debug
%%

MOC_block_seq_opt
        : /* empty */
        | MOC_block_seq_opt MOC_uLib_Parameters
        | MOC_block_seq_opt MOC_Property
        ;

MOC_Property:
        MOC_PROPERTY '(' IDENTIFIER ')' '{'     { DEBUG("found property: %s",$3); }
        MOC_prop_content_opt
        '}'                { DEBUG("property ends");  }
        ;

MOC_uLib_Parameters:
        MOC_OBJECT_PARAMETERS '(' IDENTIFIER ')' '{' { DEBUG("found parameters: %s",$3); }
        MOC_prop_content_opt
        '}'                { DEBUG("parameters ends");  }
        ;

MOC_prop_content_opt
        :
        | translation_unit
        ;


MOC_monk_seq_opt
        :                           { $$ = EMPTY;         }
        | MOC_monk_seq_opt MOC_monk { $$ = CONCAT($1,$2); }
        ;

MOC_monk
        : INT IDENTIFIER ';'  { $$ = CONCAT("type:",$1," ","id:",$2," "); }
        | CHAR IDENTIFIER ';' { $$ = CONCAT("type:",$1," ","id:",$2," "); }
        | decl_specifier_seq_opt decl_specifier_seq_opt ';' { $$ = CONCAT("type:",$1," ","id:",$2," "); }
        ;

/*----------------------------------------------------------------------
 * Lexical elements.
 *----------------------------------------------------------------------*/

identifier:
        IDENTIFIER
        ;

literal:
        integer_literal
        | character_literal
        | floating_literal
        | string_literal
        | boolean_literal
        ;

integer_literal:
        INTEGER
        ;

character_literal:
        CHARACTER
        ;

floating_literal:
        FLOATING
        ;

string_literal:
        STRING
        ;

boolean_literal:
        TRUE
        | FALSE
        ;

/*----------------------------------------------------------------------
 * Translation unit.
 *----------------------------------------------------------------------*/

translation_unit:
        declaration_seq_opt { DEBUG("t unit"); }
        ;

/*----------------------------------------------------------------------
 * Expressions.
 *----------------------------------------------------------------------*/

primary_expression:
        literal
        | THIS
        | COLONCOLON identifier
        | COLONCOLON operator_function_id
        | COLONCOLON qualified_id
        | '(' expression ')'
        | id_expression
        ;

id_expression:
        unqualified_id
        | qualified_id
        ;

unqualified_id:
        identifier
        | operator_function_id
        | conversion_function_id
        | '~' class_name
        | template_id
        ;

qualified_id:
        nested_name_specifier TEMPLATE_opt unqualified_id
        ;

nested_name_specifier:
        class_or_namespace_name COLONCOLON nested_name_specifier_opt
        ;

class_or_namespace_name:
        class_name
        | namespace_name
        ;

postfix_expression:
        primary_expression
        | postfix_expression '[' expression ']'
        | postfix_expression '(' expression_list_opt ')'
        | simple_type_specifier '(' expression_list_opt ')'
        | postfix_expression '.' TEMPLATE_opt COLONCOLON_opt id_expression
        | postfix_expression ARROW TEMPLATE_opt COLONCOLON_opt id_expression
        | postfix_expression '.' pseudo_destructor_name
        | postfix_expression ARROW pseudo_destructor_name
        | postfix_expression PLUSPLUS
        | postfix_expression MINUSMINUS
        | DYNAMIC_CAST '<' type_id '>' '(' expression ')'
        | STATIC_CAST '<' type_id '>' '(' expression ')'
        | REINTERPRET_CAST '<' type_id '>' '(' expression ')'
        | CONST_CAST '<' type_id '>' '(' expression ')'
        | TYPEID '(' expression ')'
        | TYPEID '(' type_id ')'
        ;

expression_list:
        assignment_expression
        | expression_list ',' assignment_expression
        ;

pseudo_destructor_name:
        COLONCOLON_opt nested_name_specifier_opt type_name COLONCOLON '~' type_name
        | COLONCOLON_opt nested_name_specifier_opt '~' type_name
        ;

unary_expression:
        postfix_expression
        | PLUSPLUS cast_expression
        | MINUSMINUS cast_expression
        | unary_operator cast_expression
        | SIZEOF unary_expression
        | SIZEOF '(' type_id ')'
        | new_expression
        | delete_expression
        ;

unary_operator:
        '*'
        | '&'
        | '+'
        | '-'
        | '!'
        | '~'
        ;

new_expression:
        COLONCOLON_opt NEW new_placement_opt new_type_id new_initializer_opt
        | COLONCOLON_opt NEW new_placement_opt '(' type_id ')' new_initializer_opt
        ;

new_placement:
        '(' expression_list ')'
        ;

new_type_id:
        type_specifier_seq new_declarator_opt
        ;

new_declarator:
        ptr_operator new_declarator_opt
        | direct_new_declarator
        ;

direct_new_declarator:
        '[' expression ']'
        | direct_new_declarator '[' constant_expression ']'
        ;

new_initializer:
        '(' expression_list_opt ')'
        ;

delete_expression:
        COLONCOLON_opt DELETE cast_expression
        | COLONCOLON_opt DELETE '[' ']' cast_expression
        ;

cast_expression:
        unary_expression
        | '(' type_id ')' cast_expression
        ;

pm_expression:
        cast_expression
        | pm_expression DOTSTAR cast_expression
        | pm_expression ARROWSTAR cast_expression
        ;

multiplicative_expression:
        pm_expression
        | multiplicative_expression '*' pm_expression
        | multiplicative_expression '/' pm_expression
        | multiplicative_expression '%' pm_expression
        ;

additive_expression:
        multiplicative_expression
        | additive_expression '+' multiplicative_expression
        | additive_expression '-' multiplicative_expression
        ;

shift_expression:
        additive_expression
        | shift_expression SL additive_expression
        | shift_expression SR additive_expression
        ;

relational_expression:
        shift_expression
        | relational_expression '<' shift_expression
        | relational_expression '>' shift_expression
        | relational_expression LTEQ shift_expression
        | relational_expression GTEQ shift_expression
        ;

equality_expression:
        relational_expression
        | equality_expression EQ relational_expression
        | equality_expression NOTEQ relational_expression
        ;

and_expression:
        equality_expression
        | and_expression '&' equality_expression
        ;

exclusive_or_expression:
        and_expression
        | exclusive_or_expression '^' and_expression
        ;

inclusive_or_expression:
        exclusive_or_expression
        | inclusive_or_expression '|' exclusive_or_expression
        ;

logical_and_expression:
        inclusive_or_expression
        | logical_and_expression ANDAND inclusive_or_expression
        ;

logical_or_expression:
        logical_and_expression
        | logical_or_expression OROR logical_and_expression
        ;

conditional_expression:
        logical_or_expression
        | logical_or_expression  '?' expression ':' assignment_expression
        ;

assignment_expression:
        conditional_expression
        | logical_or_expression assignment_operator assignment_expression
        | throw_expression
        ;

assignment_operator:
        '='
        | MULEQ
        | DIVEQ
        | MODEQ
        | ADDEQ
        | SUBEQ
        | SREQ
        | SLEQ
        | ANDEQ
        | XOREQ
        | OREQ
        ;

expression:
        assignment_expression
        | expression ',' assignment_expression
        ;

constant_expression:
        conditional_expression
        ;

/*----------------------------------------------------------------------
 * Statements.
 *----------------------------------------------------------------------*/

statement:
        labeled_statement
        | expression_statement
        | compound_statement
        | selection_statement
        | iteration_statement
        | jump_statement
        | declaration_statement
        | try_block
        ;

labeled_statement:
        identifier ':' statement
        | CASE constant_expression ':' statement
        | DEFAULT ':' statement
        ;

expression_statement:
        expression_opt ';'
        ;

compound_statement:
        '{' statement_seq_opt '}'
        ;

statement_seq:
        statement
        | statement_seq statement
        ;

selection_statement:
        IF '(' condition ')' statement
        | IF '(' condition ')' statement ELSE statement
        | SWITCH '(' condition ')' statement
        ;

condition:
        expression
        | type_specifier_seq declarator '=' assignment_expression
        ;

iteration_statement:
        WHILE '(' condition ')' statement
        | DO statement WHILE '(' expression ')' ';'
        | FOR '(' for_init_statement condition_opt ';' expression_opt ')' statement
        ;

for_init_statement:
        expression_statement
        | simple_declaration
        ;

jump_statement:
        BREAK ';'
        | CONTINUE ';'
        | RETURN expression_opt ';'
        | GOTO identifier ';'
        ;

declaration_statement:
        block_declaration
        ;

/*----------------------------------------------------------------------
 * Declarations.
 *----------------------------------------------------------------------*/

declaration_seq:
        declaration
        | declaration_seq declaration
        ;

declaration:
        block_declaration
        | function_definition
        | template_declaration
        | explicit_instantiation
        | explicit_specialization
        | linkage_specification
        | namespace_definition
        ;

block_declaration:
        simple_declaration
        | asm_definition
        | namespace_alias_definition
        | using_declaration
        | using_directive
        ;

simple_declaration:
        decl_specifier_seq_opt init_declarator_list_opt ';' { SIMPLE_DECLARATION($1,$2); }
        ;

decl_specifier:
        storage_class_specifier
        | type_specifier
        | function_specifier
        | FRIEND
        | TYPEDEF
        ;

decl_specifier_seq:
        decl_specifier_seq_opt decl_specifier { $$ = CONCAT($1,$2); }
        ;

storage_class_specifier:
        AUTO
        | REGISTER
        | STATIC
        | EXTERN
        | MUTABLE
        ;

function_specifier:
        INLINE
        | VIRTUAL
        | EXPLICIT
        ;

typedef_name:
        identifier
        ;

type_specifier:
        simple_type_specifier
        | class_specifier
        | enum_specifier
        | elaborated_type_specifier
        | cv_qualifier
        ;

simple_type_specifier:
        COLONCOLON_opt /*nested_name_specifier_opt*/ type_name { $$ = CONCAT($1,$2); } /*<<<<< FIX DISAMBIGUATION <<<<<<*/
        | CHAR
        | WCHAR_T
        | BOOL
        | SHORT
        | INT
        | LONG
        | SIGNED
        | UNSIGNED
        | FLOAT
        | DOUBLE
        | VOID
        ;

type_name:
        class_name
        | enum_name
        | typedef_name
        ;

elaborated_type_specifier:
        class_key COLONCOLON_opt nested_name_specifier_opt identifier { $$ = CONCAT($1,$2,$3,$4); }
        | ENUM COLONCOLON_opt nested_name_specifier_opt identifier    { $$ = CONCAT($1,$2,$3,$4); }
        | TYPENAME COLONCOLON_opt nested_name_specifier identifier    { $$ = CONCAT($1,$2,$3,$4); }
        | TYPENAME COLONCOLON_opt nested_name_specifier identifier '<' template_argument_list '>'   { $$ = CONCAT($1,$2,$3,$4,"<",$6,">"); }
        ;

enum_name:
        identifier
        ;

enum_specifier:
        ENUM identifier_opt '{' enumerator_list_opt '}'    { $$ = CONCAT($1,$2,"{",$4,"}"); }
        ;

enumerator_list:
        enumerator_definition
        | enumerator_list ',' enumerator_definition        { $$ = CONCAT($1,",",$3); }
        ;

enumerator_definition:
        enumerator
        | enumerator '=' constant_expression               { $$ = CONCAT($1,"=",$3); }
        ;

enumerator:
        identifier
        ;

namespace_name:
        original_namespace_name
        | namespace_alias
        ;

original_namespace_name:
        identifier
        ;

namespace_definition:
        named_namespace_definition
        | unnamed_namespace_definition
        ;

named_namespace_definition:
        original_namespace_definition
        | extension_namespace_definition
        ;

original_namespace_definition:
        NAMESPACE identifier '{' namespace_body '}'
        ;

extension_namespace_definition:
        NAMESPACE original_namespace_name '{' namespace_body '}'
        ;

unnamed_namespace_definition:
        NAMESPACE '{' namespace_body '}'
        ;

namespace_body:
        declaration_seq_opt
        ;

namespace_alias:
        identifier
        ;

namespace_alias_definition:
        NAMESPACE identifier '=' qualified_namespace_specifier ';'
        ;

qualified_namespace_specifier:
        COLONCOLON_opt nested_name_specifier_opt namespace_name
        ;

using_declaration:
        USING TYPENAME_opt COLONCOLON_opt nested_name_specifier unqualified_id ';'
        | USING COLONCOLON unqualified_id ';'
        ;

using_directive:
        USING NAMESPACE COLONCOLON_opt nested_name_specifier_opt namespace_name ';'
        ;

asm_definition:
        ASM '(' string_literal ')' ';'
        ;

linkage_specification:
        EXTERN string_literal '{' declaration_seq_opt '}'
        | EXTERN string_literal declaration
        ;

/*----------------------------------------------------------------------
 * Declarators.
 *----------------------------------------------------------------------*/

init_declarator_list:
        init_declarator
        | init_declarator_list ',' init_declarator        { $$ = CONCAT($1,",",$3); }
        ;

init_declarator:
        declarator initializer_opt                        { $$ = CONCAT($1,$2); }
        ;

declarator:
        direct_declarator
        | ptr_operator declarator                         { $$ = CONCAT($1,$2); }
        ;

direct_declarator:
        declarator_id
        | direct_declarator '('parameter_declaration_clause ')' cv_qualifier_seq_opt exception_specification_opt
        | direct_declarator '[' constant_expression_opt ']'      { $$ = CONCAT($1,"[",$3,"]"); }
        | '(' declarator ')'                                     { $$ = CONCAT("(",$2,")"); }
        ;

ptr_operator:
        '*' cv_qualifier_seq_opt                                 { $$ = CONCAT("*",$2); }
        | '&'                                                    { $$ = strdup("&"); }
        | COLONCOLON_opt nested_name_specifier '*' cv_qualifier_seq_opt { $$ = CONCAT($1,$2,"*",$4); }
        ;

cv_qualifier_seq:
        cv_qualifier cv_qualifier_seq_opt
        ;

cv_qualifier:
        CONST
        | VOLATILE
        ;

declarator_id:
        COLONCOLON_opt id_expression                               { $$ = CONCAT($1,$2); }
        | COLONCOLON_opt nested_name_specifier_opt type_name       { $$ = CONCAT($1,$2,$3); }
        ;

type_id:
        type_specifier_seq abstract_declarator_opt                 /*{ $$ = CONCAT($1,$2); }*/
        ;

type_specifier_seq:
        type_specifier type_specifier_seq_opt                      { $$ = CONCAT($1,$2); }
        ;

abstract_declarator:
        ptr_operator abstract_declarator_opt                       /*{ $$ = CONCAT($1,$2); }*/
        | direct_abstract_declarator
        ;

direct_abstract_declarator:
        direct_abstract_declarator_opt '(' parameter_declaration_clause ')' cv_qualifier_seq_opt exception_specification_opt
        | direct_abstract_declarator_opt '[' constant_expression_opt ']'
        | '(' abstract_declarator ')'
        ;

parameter_declaration_clause:
        parameter_declaration_list_opt ELLIPSIS_opt
        | parameter_declaration_list ',' ELLIPSIS
        ;

parameter_declaration_list:
        parameter_declaration
        | parameter_declaration_list ',' parameter_declaration
        ;

parameter_declaration:
        decl_specifier_seq declarator
        | decl_specifier_seq declarator '=' assignment_expression
        | decl_specifier_seq abstract_declarator_opt
        | decl_specifier_seq abstract_declarator_opt '=' assignment_expression
        ;

function_definition:
        decl_specifier_seq_opt declarator ctor_initializer_opt function_body
        | decl_specifier_seq_opt declarator function_try_block
        ;

function_body:
        compound_statement
        ;

initializer:
        '=' initializer_clause               { $$ = strdup($2); }
        | '(' expression_list ')'
        ;

initializer_clause:
        assignment_expression
        | '{' initializer_list COMMA_opt '}'
        | '{' '}'
        ;

initializer_list:
        initializer_clause
        | initializer_list ',' initializer_clause
        ;

/*----------------------------------------------------------------------
 * Classes.
 *----------------------------------------------------------------------*/

class_name:
        identifier
        | template_id
        ;

class_specifier:
        class_head '{' member_specification_opt '}'
        ;

class_head:
        class_key identifier_opt base_clause_opt
        | class_key nested_name_specifier identifier base_clause_opt
        ;

class_key:
        CLASS
        | STRUCT
        | UNION
        ;

member_specification:
        member_declaration member_specification_opt
        | access_specifier ':' member_specification_opt
        ;

member_declaration:
        decl_specifier_seq_opt member_declarator_list_opt ';'
        | function_definition SEMICOLON_opt
        | qualified_id ';'
        | using_declaration
        | template_declaration
        ;

member_declarator_list:
        member_declarator
        | member_declarator_list ',' member_declarator
        ;

member_declarator:
        declarator pure_specifier_opt
        | declarator constant_initializer_opt
        | identifier_opt ':' constant_expression
        ;

pure_specifier:
        '=' '0'
        ;

constant_initializer:
        '=' constant_expression
        ;

/*----------------------------------------------------------------------
 * Derived classes.
 *----------------------------------------------------------------------*/

base_clause:
        ':' base_specifier_list
        ;

base_specifier_list:
        base_specifier
        | base_specifier_list ',' base_specifier
        ;

base_specifier:
        COLONCOLON_opt nested_name_specifier_opt class_name
        | VIRTUAL access_specifier_opt COLONCOLON_opt nested_name_specifier_opt class_name
        | access_specifier VIRTUAL_opt COLONCOLON_opt nested_name_specifier_opt class_name
        ;

access_specifier:
        PRIVATE
        | PROTECTED
        | PUBLIC
        ;

/*----------------------------------------------------------------------
 * Special member functions.
 *----------------------------------------------------------------------*/

conversion_function_id:
        OPERATOR conversion_type_id
        ;

conversion_type_id:
        type_specifier_seq conversion_declarator_opt
        ;

conversion_declarator:
        ptr_operator conversion_declarator_opt
        ;

ctor_initializer:
        ':' mem_initializer_list
        ;

mem_initializer_list:
        mem_initializer
        | mem_initializer ',' mem_initializer_list
        ;

mem_initializer:
        mem_initializer_id '(' expression_list_opt ')'
        ;

mem_initializer_id:
        COLONCOLON_opt nested_name_specifier_opt class_name
        | identifier
        ;

/*----------------------------------------------------------------------
 * Overloading.
 *----------------------------------------------------------------------*/

operator_function_id:
        OPERATOR operator
        ;

operator:
        NEW
        | DELETE
        | NEW '[' ']'
        | DELETE '[' ']'
        | '+'
        | '_'
        | '*'
        | '/'
        | '%'
        | '^'
        | '&'
        | '|'
        | '~'
        | '!'
        | '='
        | '<'
        | '>'
        | ADDEQ
        | SUBEQ
        | MULEQ
        | DIVEQ
        | MODEQ
        | XOREQ
        | ANDEQ
        | OREQ
        | SL
        | SR
        | SREQ
        | SLEQ
        | EQ
        | NOTEQ
        | LTEQ
        | GTEQ
        | ANDAND
        | OROR
        | PLUSPLUS
        | MINUSMINUS
        | ','
        | ARROWSTAR
        | ARROW
        | '(' ')'
        | '[' ']'
        ;

/*----------------------------------------------------------------------
 * Templates.
 *----------------------------------------------------------------------*/

template_declaration:
        EXPORT_opt TEMPLATE '<' template_parameter_list '>' declaration
        ;

template_parameter_list:
        template_parameter
        | template_parameter_list ',' template_parameter
        ;

template_parameter:
        type_parameter
        | parameter_declaration
        ;

type_parameter:
        CLASS identifier_opt
        | CLASS identifier_opt '=' type_id
        | TYPENAME identifier_opt
        | TYPENAME identifier_opt '=' type_id
        | TEMPLATE '<' template_parameter_list '>' CLASS identifier_opt
        | TEMPLATE '<' template_parameter_list '>' CLASS identifier_opt '=' template_name
        ;

template_id:
        template_name '<' template_argument_list '>'
        ;

template_name:
        identifier
        ;

template_argument_list:
        template_argument
        | template_argument_list ',' template_argument
        ;

template_argument:
        assignment_expression
        | type_id
        | template_name
        ;

explicit_instantiation:
        TEMPLATE declaration
        ;

explicit_specialization:
        TEMPLATE '<' '>' declaration
        ;

/*----------------------------------------------------------------------
 * Exception handling.
 *----------------------------------------------------------------------*/

try_block:
        TRY compound_statement handler_seq
        ;

function_try_block:
        TRY ctor_initializer_opt function_body handler_seq
        ;

handler_seq:
        handler handler_seq_opt
        ;

handler:
        CATCH '(' exception_declaration ')' compound_statement
        ;

exception_declaration:
        type_specifier_seq declarator
        | type_specifier_seq abstract_declarator
        | type_specifier_seq
        | ELLIPSIS
        ;

throw_expression:
        THROW assignment_expression_opt
        ;

exception_specification:
        THROW '(' type_id_list_opt ')'
        ;

type_id_list:
        type_id
        | type_id_list ',' type_id
        ;

/*----------------------------------------------------------------------
 * Epsilon (optional) definitions.
 *----------------------------------------------------------------------*/

declaration_seq_opt:
        { $$ = EMPTY; }
        | declaration_seq
        ;

TEMPLATE_opt:
        { $$ = EMPTY; }
        | TEMPLATE
        ;

nested_name_specifier_opt:
        { $$ = EMPTY; }
        | nested_name_specifier
        ;

expression_list_opt:
        { $$ = EMPTY; }
        | expression_list
        ;

COLONCOLON_opt:
        { $$ = EMPTY; }
        | COLONCOLON { $$ = strdup("::"); }
        ;

new_placement_opt:
        { $$ = EMPTY; }
        | new_placement
        ;

new_initializer_opt:
        { $$ = EMPTY; }
        | new_initializer
        ;

new_declarator_opt:
        { $$ = EMPTY; }
        | new_declarator
        ;

expression_opt:
        { $$ = EMPTY; }
        | expression
        ;

statement_seq_opt:
        { $$ = EMPTY; }
        | statement_seq
        ;

condition_opt:
        { $$ = EMPTY; }
        | condition
        ;

decl_specifier_seq_opt:
        { $$ = EMPTY; }
        | decl_specifier_seq
        ;

init_declarator_list_opt:
        { $$ = EMPTY; }
        | init_declarator_list
        ;

identifier_opt:
        { $$ = EMPTY; }
        | identifier
        ;

enumerator_list_opt:
        { $$ = EMPTY; }
        | enumerator_list
        ;

TYPENAME_opt:
        { $$ = EMPTY; }
        | TYPENAME
        ;

initializer_opt:
        { $$ = EMPTY; }
        | initializer
        ;

cv_qualifier_seq_opt:
        { $$ = EMPTY; }
        | cv_qualifier_seq
        ;

exception_specification_opt:
        { $$ = EMPTY; }
        | exception_specification
        ;

constant_expression_opt:
        { $$ = EMPTY; }
        | constant_expression
        ;

abstract_declarator_opt:
        { $$ = EMPTY; }
        | abstract_declarator
        ;

type_specifier_seq_opt:
        { $$ = EMPTY; }
        | type_specifier_seq
        ;

direct_abstract_declarator_opt:
        { $$ = EMPTY; }
        | direct_abstract_declarator
        ;

parameter_declaration_list_opt:
        { $$ = EMPTY; }
        | parameter_declaration_list
        ;

ELLIPSIS_opt:
        { $$ = EMPTY; }
        | ELLIPSIS
        ;

ctor_initializer_opt:
        { $$ = EMPTY; }
        | ctor_initializer
        ;

COMMA_opt:
        { $$ = EMPTY; }
        | ','
        ;

member_specification_opt:
        { $$ = EMPTY; }
        | member_specification
        ;

base_clause_opt:
        { $$ = EMPTY; }
        | base_clause
        ;

member_declarator_list_opt:
        { $$ = EMPTY; }
        | member_declarator_list
        ;

SEMICOLON_opt:
        { $$ = EMPTY; }
        | ';'
        ;

pure_specifier_opt:
        { $$ = EMPTY; }
        | pure_specifier
        ;

constant_initializer_opt:
        { $$ = EMPTY; }
        | constant_initializer
        ;

access_specifier_opt:
        { $$ = EMPTY; }
        | access_specifier
        ;

VIRTUAL_opt:
        { $$ = EMPTY; }
        | VIRTUAL
        ;

conversion_declarator_opt:
        { $$ = EMPTY; }
        | conversion_declarator
        ;

EXPORT_opt:
        { $$ = EMPTY; }
        | EXPORT
        ;

handler_seq_opt:
        { $$ = EMPTY; }
        | handler_seq
        ;

assignment_expression_opt:
        { $$ = EMPTY; }
        | assignment_expression
        ;

type_id_list_opt:
        { $$ = EMPTY; }
        | type_id_list
        ;


%%

int yyerror(char *s) {
  printf("error, %s\n", s);
  return 1;
}

void yyprint (FILE *file,
                     int type,
                     YYSTYPE value)
{
  if (type == IDENTIFIER)
    fprintf (file, "%s", value.sval);
  if (type == COLONCOLON)
    fprintf (file, "%s", value.sval);

}

int main(void) {
/*  yydebug = 1;*/
  yyparse();
}
