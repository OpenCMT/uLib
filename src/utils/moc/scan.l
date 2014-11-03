%option stack
%{
/* preamble */
#include <ctype.h>
#include <stdio.h>
#include "y.tab.h"

#define PRINT(str)  { printf("%s",str); }
#define ENSTATE(st) { yy_push_state(YY_START); BEGIN(st); /*printf("ST[%i]",YY_START);*/ }
#define EXSTATE     { BEGIN(yy_top_state()); yy_pop_state(); /*printf("ST[%i]",YY_START);*/ }

#define SCANTEXT    { fill_sval(); }
#define MATCH(name) { ECHO; SCANTEXT; return name; }

int lineno;
int moc_level = 0;

static int yywrap(void);
static void skip_until_eol(void);
static void skip_comment(void);
static int check_identifier(const char *);
static int fill_sval();
%}

blank                           [\t\f\v\r ]+
anyunch                         <*>.

intsuffix			([uU][lL]?)|([lL][uU]?)
fracconst			([0-9]*\.[0-9]+)|([0-9]+\.)
exppart				[eE][-+]?[0-9]+
floatsuffix			[fFlL]
chartext			([^'])|(\\.)
stringtext			([^"])|(\\.)

digit				[0-9]
hex				[0-9A-Fa-f]
letter				[A-Z_a-z]
simple_escape_sequence		(\\\'|\\\"|\\\?|\\\\|\\a|\\b|\\f|\\n|\\r|\\t|\\v)
octal_escape_sequence		(\\[0-7]|\\[0-7][0-7]|\\[0-7][0-7][0-7])
hexadecimal_escape_sequence	(\\x{hex}+)
escape_sequence			({simple_escape_sequence}|{octal_escape_sequence}|{hexadecimal_escape_sequence})
universal_character_name	(\\u{hex}{hex}{hex}{hex}|\\U{hex}{hex}{hex}{hex}{hex}{hex}{hex}{hex})
non_digit			({letter}|{universal_character_name})
identifier			({non_digit}({non_digit}|{digit})*)

begin_comment        "/*"
end_comment          "*/"
begin_inline_comment "//"
end_inline_comment   "\n"


%s moc
%x cmt
%x inlcmt

%%

"\n"		{ ++lineno; ECHO; }
{blank}         ECHO;

{begin_comment}    { ENSTATE(cmt); ECHO; }
<cmt>{end_comment} { EXSTATE;      ECHO; }

{begin_inline_comment}       { ENSTATE(inlcmt); ECHO; }
<inlcmt>{end_inline_comment} { EXSTATE;         ECHO; }


property               { ECHO; ENSTATE(moc); return MOC_PROPERTY; }
ULIB_OBJECT_PARAMETERS { ECHO; ENSTATE(moc); return MOC_OBJECT_PARAMETERS; }
<moc>{
              "{"        { moc_level++; MATCH('{'); }
              "}"        { if(!--moc_level)EXSTATE; MATCH('}'); }

              "<%"				{ MATCH('{'); }
              "%>"				{ MATCH('}'); }
              "["				{ MATCH('['); }
              "<:"				{ MATCH('['); }
              "]"				{ MATCH(']'); }
              ":>"				{ MATCH(']'); }
              "("				{ MATCH('('); }
              ")"				{ MATCH(')'); }
              ";"				{ MATCH(';'); }
              "::"				{ MATCH(COLONCOLON); }
              ":"				{ MATCH(':'); }
              "..."				{ MATCH(ELLIPSIS); }
              "?"				{ MATCH('?'); }
              "."				{ MATCH('.'); }
              ".*"				{ MATCH(DOTSTAR); }
              "+"				{ MATCH('+'); }
              "-"				{ MATCH('-'); }
              "*"				{ MATCH('*'); }
              "/"				{ MATCH('/'); }
              "%"				{ MATCH('%'); }
              "^"				{ MATCH('^'); }
              "xor"				{ MATCH('^'); }
              "&"				{ MATCH('&'); }
              "bitand"				{ MATCH('&'); }
              "|"				{ MATCH('|'); }
              "bitor"				{ MATCH('|'); }
              "~"				{ MATCH('~'); }
              "compl"				{ MATCH('~'); }
              "!"				{ MATCH('!'); }
              "not"				{ MATCH('!'); }
              "="				{ MATCH('='); }
              "<"				{ MATCH('<'); }
              ">"				{ MATCH('>'); }
              "+="				{ MATCH(ADDEQ); }
              "-="				{ MATCH(SUBEQ); }
              "*="				{ MATCH(MULEQ); }
              "/="				{ MATCH(DIVEQ); }
              "%="				{ MATCH(MODEQ); }
              "^="				{ MATCH(XOREQ); }
              "xor_eq"				{ MATCH(XOREQ); }
              "&="				{ MATCH(ANDEQ); }
              "and_eq"				{ MATCH(ANDEQ); }
              "|="				{ MATCH(OREQ); }
              "or_eq"				{ MATCH(OREQ); }
              "<<"				{ MATCH(SL); }
              ">>"				{ MATCH(SR); }
              "<<="				{ MATCH(SLEQ); }
              ">>="				{ MATCH(SREQ); }
              "=="				{ MATCH(EQ); }
              "!="				{ MATCH(NOTEQ); }
              "not_eq"				{ MATCH(NOTEQ); }
              "<="				{ MATCH(LTEQ); }
              ">="				{ MATCH(GTEQ); }
              "&&"				{ MATCH(ANDAND); }
              "and"				{ MATCH(ANDAND); }
              "||"				{ MATCH(OROR); }
              "or"				{ MATCH(OROR); }
              "++"				{ MATCH(PLUSPLUS); }
              "--"				{ MATCH(MINUSMINUS); }
              ","				{ MATCH(','); }
              "->*"				{ MATCH(ARROWSTAR); }
              "->"				{ MATCH(ARROW); }

              "asm"				{ MATCH(ASM); }
              "auto"				{ MATCH(AUTO); }
              "bool"				{ MATCH(BOOL); }
              "break"				{ MATCH(BREAK); }
              "case"				{ MATCH(CASE); }
              "catch"				{ MATCH(CATCH); }
              "char"				{ MATCH(CHAR); }
              "class"				{ MATCH(CLASS); }
              "const"				{ MATCH(CONST); }
              "const_cast"			{ MATCH(CONST_CAST); }
              "continue"			{ MATCH(CONTINUE); }
              "default"				{ MATCH(DEFAULT); }
              "delete"				{ MATCH(DELETE); }
              "do"				{ MATCH(DO); }
              "double"				{ MATCH(DOUBLE); }
              "dynamic_cast"			{ MATCH(DYNAMIC_CAST); }
              "else"				{ MATCH(ELSE); }
              "enum"				{ MATCH(ENUM); }
              "explicit"			{ MATCH(EXPLICIT); }
              "export"				{ MATCH(EXPORT); }
              "extern"				{ MATCH(EXTERN); }
              "false"				{ MATCH(FALSE); }
              "float"				{ MATCH(FLOAT); }
              "for"				{ MATCH(FOR); }
              "friend"				{ MATCH(FRIEND); }
              "goto"				{ MATCH(GOTO); }
              "if"				{ MATCH(IF); }
              "inline"				{ MATCH(INLINE); }
              "int"                             { MATCH(INT); }
              "long"				{ MATCH(LONG); }
              "mutable"				{ MATCH(MUTABLE); }
              "namespace"			{ MATCH(NAMESPACE); }
              "new"				{ MATCH(NEW); }
              "operator"			{ MATCH(OPERATOR); }
              "private"				{ MATCH(PRIVATE); }
              "protected"			{ MATCH(PROTECTED); }
              "public"				{ MATCH(PUBLIC); }
              "register"			{ MATCH(REGISTER); }
              "reinterpret_cast"		{ MATCH(REINTERPRET_CAST); }
              "return"				{ MATCH(RETURN); }
              "short"				{ MATCH(SHORT); }
              "signed"				{ MATCH(SIGNED); }
              "sizeof"				{ MATCH(SIZEOF); }
              "static"				{ MATCH(STATIC); }
              "static_cast"			{ MATCH(STATIC_CAST); }
              "struct"				{ MATCH(STRUCT); }
              "switch"				{ MATCH(SWITCH); }
              "template"			{ MATCH(TEMPLATE); }
              "this"				{ MATCH(THIS); }
              "throw"				{ MATCH(THROW); }
              "true"				{ MATCH(TRUE); }
              "try"				{ MATCH(TRY); }
              "typedef"				{ MATCH(TYPEDEF); }
              "typeid"				{ MATCH(TYPEID); }
              "typename"			{ MATCH(TYPENAME); }
              "union"				{ MATCH(UNION); }
              "unsigned"			{ MATCH(UNSIGNED); }
              "using"				{ MATCH(USING); }
              "virtual"				{ MATCH(VIRTUAL); }
              "void"				{ MATCH(VOID); }
              "volatile"			{ MATCH(VOLATILE); }
              "wchar_t"				{ MATCH(WCHAR_T); }
              "while"				{ MATCH(WHILE); }
              [a-zA-Z_][a-zA-Z_0-9]*		{ ECHO; return check_identifier(yytext); }

              "0"[xX][0-9a-fA-F]+{intsuffix}?	{ ECHO; return INTEGER; }
              "0"[0-7]+{intsuffix}?		{ ECHO; return INTEGER; }
              [0-9]+{intsuffix}?		{ ECHO; return INTEGER; }

              {fracconst}{exppart}?{floatsuffix}?	{ ECHO; return FLOATING; }
              [0-9]+{exppart}{floatsuffix}?		{ ECHO; return FLOATING; }

              "'"{chartext}*"'"			{ ECHO; return CHARACTER; }
              "L'"{chartext}*"'"		{ ECHO; return CHARACTER; }
              "\""{stringtext}*"\""		{ ECHO; return STRING; }
              "L\""{stringtext}*"\""		{ ECHO; return STRING; }

}

%%

static int yywrap(void)
{
        return 1;
}


static int fill_sval() {
     int len = strlen(yytext);
     if(len) {
       yylval.sval = malloc(len);
       strncpy(yylval.sval, yytext, len);
     }
     else {
       yylval.sval = strdup("");
     }
     return len;
}

static int check_identifier(const char *s)
{
/*
        switch (s[0]) {
        case 'D': return TYPEDEF_NAME;
        case 'N': return NAMESPACE_NAME;
        case 'C': return CLASS_NAME;
        case 'E': return ENUM_NAME;
        case 'T': return TEMPLATE_NAME;
        }
*/

        yylval.sval = malloc(strlen(yytext));
        strncpy(yylval.sval, yytext, strlen(yytext));
        return IDENTIFIER;
}

