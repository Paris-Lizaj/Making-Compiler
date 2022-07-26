%option noyywrap
%x error

%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "heading.h"
int  num_lines=1,    num_chars=0,	correct=0,	wrong=0;
void yyerror(int x);
void countlines();
%}


delimiter		[ \t\r\n]+
no_whites		[^ \t\r\n]
prefix			[-+]?
integer			({prefix}(0+|[1-9][0-9]*))
Ek			([Ee]{prefix}[0-9]+)
sh			(#.*[\n\r])	
quotes			(\"\"\")
letters 		[a-zA-Z_Α-Ωα-ωόίύέήάώ]
sym			[-+\*\/%]
string1			'(\\.|[^'\n\r])*
string2			\"(\\.|[^"\n\r])*

int_error1		(0+[1-9]+)
int_error2		[0-9]+[^0-9\. \t\r\n]{no_whites}*
float_error1 		{prefix}{int_error1}\.{no_whites}*
float_error2 		({integer}\.[0-9]*[Ee])|({prefix}\.[0-9]*[Ee])
float_error3 		(({integer}\.[0-9]*)|({prefix}\.[0-9]+))[^0-9Ee \t\r\n]{no_whites}*
var_error		{letters}({letters}+[0-9])*[^a-zA-Z_Α-Ωα-ωόίύέήάώ0-9 \t\r\n]{no_whites}*
op_error1		[^= \t\r\n]{no_whites}*
op_error2		{sym}{op_error1}
comm_error		({quotes}(\"?\"?[^"]+)*{quotes}\"?\"?){no_whites}+



%%
{delimiter}						{countlines(); }
<<EOF>>							{fprintf(yyout,"\ncorrect %d\twrong %d\n",correct,wrong);exit(0); 
/*emfanizoume to plh8os twn swstwn kai lan8asmenwn le3hmatwn pou entophsame kai termatizoume ton kataskeuasth*/}

((({integer}\.[0-9]*)|({prefix}\.[0-9]+))({Ek})?)	{correct++;fprintf(yyout,"\nFLOAT\t\t(%s , %d)\n",yytext,num_lines);return EKTHETIKO; }
{integer}						{correct++;fprintf(yyout,"\nINTEGER\t\t(%s , %d)\n",yytext,num_lines);return INTEGER; }
({quotes}(\"?\"?[^"]+)*{quotes}\"?\"?)|{sh}		{correct++;/*fprintf(yyout,"\nCOMMENT\t\t(%s , %d)\n",yytext,num_lines);*/countlines();return COMMENT;}
{letters}([a-zA-Z_Α-Ωα-ωόίύέήάώ0-9]*)			{correct++;fprintf(yyout,"\nVARIABLE\t(%s , %d)\n",yytext,num_lines);return VAR; }
((((\*{2})|(\/{2})|({sym}))?=?)|=)			{correct++;fprintf(yyout,"\nOPERATOR\t(%s , %d)\n",yytext,num_lines);return OPERATOR;}	  
({string1}')|({string2}\")				{correct++;fprintf(yyout,"\nSTRING\t\t(%s , %d)\n",yytext,num_lines);return STRING;}


{prefix}({int_error1}|{int_error2})			{yyerror(7);BEGIN(error);return EINTEGER;
/*int_error1: 01 -03 00004565 int-error2:5k15k +0e45*/}
({float_error1})|({float_error2})|({float_error3})	{yyerror(8);BEGIN(error);return EEKTHETIKO;
/*fe1: +02. 005. +02.e 002.kl fe2: 2.1e 2.e +2.e -6.54e .1e .e +.6e +.e fe3: 2.123l +2.12gtg 2.. 2.1- 2.-2.j .5l +.2.*/}
{var_error}						{yyerror(9);BEGIN(error);return EVAR;
/*cv6$ c?*/}		
({string1}[\r\n])|({string2}[\r\n])			{yyerror(10);BEGIN(error);countlines();return ESTRING;
/*"string\n 'string\n*/}
(\*\*{op_error1})|(\/\/{op_error1})|{op_error2}		{yyerror(11);BEGIN(error);return EOPERATOR; 
/*+k **l /// %+*/}
{comm_error}						{yyerror(12);BEGIN(error);countlines();return ECOMMENT; 
/*"""com"""sth*/}
<error>{delimiter}					{BEGIN(0);countlines();}
%%

/* H synarthsh metraei ta new lines pou uparxoun sto le3hma pou einai apo8hkeumeno stnn yytext. H yyleng anaferetai sto plh8os twn xarakthrwn pou uparxoun sthn yylex */
void countlines()
{
int i;
char *start=yytext[0];
for ( i = 0; i<yyleng;i++ )
	  if(yytext[i]=='\n')
		num_lines++;
}

/* H synarthsh dexete to katalilo kwdiko apo to to lathos token 
pou exei anagnwristei  kai emfanizei to katallhlo munhma analoga me ton kwdiko. Epishs au3anei ton metrhth la8wn ka8e fora pou entopizei la8os*/
void yyerror(int x)
{
wrong++;
if(x==7)
fprintf(yyout,"\nIllegal  identifier (int) at  line: %d \t %s \n",num_lines,yytext);
else if(x==8)
fprintf(yyout,"\nIllegal  identifier (float) at  line: %d \t %s \n",num_lines,yytext);
else if(x==9)
fprintf(yyout,"\nIllegal  identifier (variable) at  line: %d \t %s \n", num_lines,yytext);
else if(x==10)
fprintf(yyout,"\nIllegal  identifier (string) at  line: %d \t %s \n",num_lines,yytext);
else if(x==11)
fprintf(yyout,"\nIllegal  identifier (operator) at  line: %d \t %s %s\n", num_lines,yytext);
else if(x==12)
fprintf(yyout,"\nIllegal  identifier (comment) at  line: %d \t %s ", num_lines,yytext);
}



int main(int argc, char **argv)
{
	int token;
	/* Otan dinetai arxeio eisodou kai arxeio e3odou*/
	if(argc == 3)
	{	if(!(yyin = fopen(argv[1], "r"))) 
		{
			fprintf(stderr, "Cannot read file: %s\n", argv[1]);
			return 1;
		}
		if(!(yyout= fopen(argv[2], "w"))) 
		{
			fprintf(stderr, "Cannot create file: %s\n", argv[2]);
			return 1;
		}
	}
	/* Otan dinetai mono arxeio eisodou*/
	else if(argc == 2)
	{
		if(!(yyin = fopen(argv[1], "r"))) 
		{
			fprintf(stderr, "Cannot read file: %s\n", argv[1]);
			return 1;
		}
	}
	/* Telos otan den dinetai tipota tote ennoeitai oti diabazoume apo to plhktrologio*/
	while( (token=yylex())>=0){}
}
