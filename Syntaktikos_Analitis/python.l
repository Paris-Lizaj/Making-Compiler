%option noyywrap
%x error
%{
#include "python.tab.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
void countlines();
int  lines=1,	correct=0,	wrong=0;
%}

digit 		[0-9]
prefix		[-+]?
exponent 	[eE]{prefix}{digit}+
integer		((0+|[1-9]({digit})*))


letters 	[a-zA-Z_Α-Ωα-ωόίύέήάώ]
var 		{letters}([0-9_a-zA-ZΑ-Ωα-ωόίύέήάώ])*
string1		'(\\.|[^'\n\r])*'
string2		\"(\\.|[^"\n\r])*\"
sh		(#.*[\n\r])	


string_error1	'(\\.|[^'\n\r])*
string_error2	\"(\\.|[^"\n\r])*
int_error	(0+[1-9]+)
float_error1 	{int_error}\.
float_error2 	{integer}?(\.[0-9]*[Ee])
var_error	[0-9]+[a-z]+



%%
"print"			{correct++;ECHO;return PRINT;}
"input" 		{correct++;ECHO;return INPUT;}
"len"			{correct++;ECHO;return LEN;}
"type"			{correct++;ECHO;return TYPE;}
"sep"			{correct++;ECHO;return SEP;}
"end"			{correct++;ECHO;return END;}
[ \t]+          	{ }


"+" 	{correct++;ECHO;return PLUS; }
"-" 	{correct++;ECHO;return MINUS;}
"*" 	{correct++;ECHO;return MULT;}
"/" 	{correct++;ECHO;return DIV;}
"%"	{correct++;ECHO;return MOD;}
"(" 	{correct++;ECHO;return '(';}
")" 	{correct++;ECHO;return ')';}
"**"	{correct++;ECHO;return POWER;}
"//"	{correct++;ECHO;return IDIV;}


"="	{correct++;ECHO;return EQUALS;}
"*="	{correct++;ECHO;return EMULT;}
"+="	{correct++;ECHO;return EADD;}
"-="	{correct++;ECHO;return EMINUS;}
"/="	{correct++;ECHO;return EDIV;}
"%="	{correct++;ECHO;return EMOD;}
"**="	{correct++;ECHO;return EPOWER;}
"//="	{correct++;ECHO;return EIDIV;}


"\n" 	{lines++;ECHO;return NL;}
","	{correct++;ECHO;return COMMA;}

"["     {correct++;ECHO;return '[';}
"]"     {correct++;ECHO;return ']';}

"{"	{correct++;ECHO;return '{';}
"}"	{correct++;ECHO;return '}';}


(({integer}\.({digit})*)|(\.({digit})+))({exponent})?	{correct++; yylval.num = atof(yytext); ECHO;return FLOAT; }
{integer}						{correct++; yylval.num=atof(yytext); ECHO;return INT;}
{string1}|{string2}					{correct++; yylval.name=strdup(yytext);ECHO;return STRING;}
{var}							{correct++; yylval.name=strdup(yytext);ECHO;return VAR;}
(\"\"\"((\"?\"?[^"]+)+\"?\"?)?\"\"\")|{sh}		{countlines();}
<<EOF>> {printf("\n#End of file#\n"); return 0;}


{prefix}{int_error}					{wrong++;ECHO;BEGIN(error);return EINTEGER;}
{float_error1}						{wrong++;ECHO;BEGIN(error);return EEKTHETIKO1;}
{float_error2}						{wrong++;ECHO;BEGIN(error);return EEKTHETIKO2;}
{var_error}						{wrong++;ECHO;BEGIN(error);return EVAR;}		
({string_error1}|{string_error2})			{wrong++;ECHO;BEGIN(error);countlines();return ESTRING;}
<error>[ \t\n]						{ECHO;BEGIN(0);countlines();}
<error>.						{ECHO;BEGIN(0);countlines();}
%%





void countlines()
{
int i;
for ( i = 0; i<yyleng;i++ )
	  if(yytext[i]=='\n')
		lines++;
}


