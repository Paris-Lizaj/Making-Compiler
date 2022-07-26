%{
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
extern char *yytext;
FILE *yyin,*yyout;
int flag=0;
extern int yyerror(),yywrap(),yylex();
extern int lines,correct,wrong;
int correct_exp=0,wrong_expr=0;
%}


%error-verbose

%union
{
double num;
char*  name;
}


%token <name> PRINT LEN SEMI INPUT TYPE SEP END	COMMA	/*termatikoi oroi oxi token*/
%token <num>  INT FLOAT 				/*ari8mhtika token*/
%token <name> STRING VAR				/*alphari8mhtika token*/
%token <name> EINTEGER EEKTHETIKO1 EEKTHETIKO2 EVAR ESTRING /*ERRORS*/
%type  <num>  line exp met input len content		/*ari8mhtikoi mh termatikoi oroi*/
%type  <name> print print2 print3 type lista string_con SyntaxError	/*alphari8mhtikoi mh termatikoi oroi*/

%token PLUS MINUS MULT DIV MOD POWER IDIV NL		/*aples ari8mhtikes pra3eis*/
%token EQUALS EMULT EADD EMINUS EDIV EMOD EPOWER EIDIV	/*ari8mhtikes pra3eis pou periexoun =*/
									

%right EQUALS
%right EMULT EADD EMINUS EDIV EMOD EPOWER EIDIV
%left  MINUS PLUS
%left  MULT DIV MOD IDIV
%right POWER 
%left  '(' ')'







%start start
%%
/*arxh*/
start:    /* empty */
        | start line
	;
		
		
/*oles oi pi8anes entoles*/
line:     NL		{}
        | print NL	{correct_exp++;}
	| met NL	{correct_exp++;}
	| error NL 	{wrong_expr++; flag=1;yyerrok;}
	;


content:  INT		{$$=$1;}
	| FLOAT		{$$=$1;}
	| VAR		{}
	| STRING  	{}
	;


/*ari8mhtikes ekfraseis*/
exp:      INT		 {$$=$1;}
	| FLOAT		 {$$=$1;}
	| MINUS exp	 {$$=-$2;}
	| VAR		 {}
	| len		 {}
	| SyntaxError	 {correct_exp--;flag=1;}
        | exp PLUS exp   { $$ = $1 + $3;		}
        | exp MINUS exp  { $$ = $1 - $3;		}
        | exp MULT exp   { $$ = $1 * $3;		}
        | exp DIV exp    { if(!$3) {fprintf(yyout,"division by 0 not allowed\n");flag=1;}else $$ = $1 / $3;		}
	| exp MOD exp    { if(!$3) {fprintf(yyout,"division by 0 not allowed\n");flag=1;}else {int i=$1/$3; i=$1-i*$3; $$=i;}	}
	| '(' exp ')'    { $$ = $2;			}
	| exp POWER exp	 { int i,pow=1;for(i=0;i<$3;i++) {pow*=$1;} $$=pow;}
	| exp IDIV exp	 { if(!$3) {fprintf(yyout,"division by 0 not allowed\n");flag=1;}else $$=(int)($1/ $3);		}
	; 
		
		
/*h printf*/
print:	  PRINT '(' print2 COMMA SEP EQUALS STRING COMMA END EQUALS STRING ')' {}
	| PRINT '(' print2 COMMA END EQUALS STRING ')' {}
	| PRINT '(' print2 COMMA SEP EQUALS STRING ')' {}
	| PRINT '(' print2 ')'			       {}
	| PRINT '(' SyntaxError			       {correct_exp--;flag=1;}
	;	
		
		
				
print2:   print3		{}
	| print2 COMMA print3	{}
	;

print3:   content		{}
	| type			{}
	;
/*h input*/
input:	  INPUT  '(' ')'	{}
	| INPUT  '(' STRING ')'	{}
	| INPUT  '(' SyntaxError	{correct_exp--;flag=1;}
	;
		
		
		
		
/*h len*/
len:	  LEN '(' VAR ')'	{}
	| LEN '(' '[' lista ']' ')'{}
	| LEN  '(' SyntaxError	{correct_exp--;flag=1;}
	
	;
		
		
		
/**h type*/
type:	  TYPE '(' VAR ')'	{}
	| TYPE '(' SyntaxError	{correct_exp--;flag=1;}
	;
	
/*CONCATENATION*/	
string_con:STRING		{}
	|  STRING PLUS string_con {}
	;
	
/*lista*/
lista:	 '[' lista ']'		{}
	|'[' ']'		{}
	| content		{}
	| lista COMMA lista	{}
	;


/*tuple*/
pleiada: '(' pleiada  COMMA content')'	{}
	| content			{}
	| pleiada COMMA content		{}
	;
/*h ekfrash gia ka8e diastash pxa[1][3][i+j]*/
dimension: '['exp ']'		{}
	|  dimension '['exp ']' {}
	;
/*ana8esh timhs*/
met: 	  VAR EQUALS type	{}
	| VAR EQUALS input{}
	| VAR EQUALS VAR dimension  	{}
	| VAR EQUALS '['lista']'{}
	| VAR EQUALS '[' ']'	{}  
	| VAR dimension EQUALS exp	{}
	| VAR EQUALS '('pleiada COMMA pleiada ')'{}
	| VAR EQUALS string_con {}
	| VAR EQUALS exp 	{if (!flag) fprintf(yyout,"%.2f\n",$3);}
	| VAR EMULT exp		{}
	| VAR EADD exp		{}
	| VAR EMINUS exp	{} 
	| VAR EDIV exp		{}
	| VAR EMOD exp	 	{}
	| VAR EPOWER exp	{}
	| VAR EIDIV exp		{}
	| SyntaxError		{wrong_expr++; flag=1;}
	;

SyntaxError:   EINTEGER		{wrong_expr++;fprintf (yyout,"\tline:%d\t integer starts with 0 \n", lines);flag=0;}
	| EEKTHETIKO1		{wrong_expr++;fprintf (yyout,"\tline:%d\t float starts with 0 \n", lines);flag=0;}
	| EEKTHETIKO2		{wrong_expr++;fprintf (yyout,"\tline:%d\t float ends incorrectly \n", lines);flag=0;}
	| EVAR			{wrong_expr++;fprintf (yyout,"\tline:%d\t var starts with digit \n", lines);flag=0;}
	| ESTRING		{wrong_expr++;fprintf (yyout,"\tline:%d\t string does not end \n", lines);flag=0;}
	;
%%
int yyerror (const char*  s)  /* Called by yyparse on error */
{
  fprintf (yyout,"line:%d\t%s \n", lines,s);
  flag=0;
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
	yyparse();
	fprintf(yyout,"\nΣΩΣΤΕΣ ΛΕΞΕΙΣ:%d\nΣΩΣΤΕΣ ΕΚΦΡΑΣΕΙΣ:%d\nΛΑΘΟΣ ΛΕΞΕΙΣ:%d\nΛΑΘΟΣ ΕΚΦΡΑΣΕΙΣ:%d",correct,correct_exp,wrong,wrong_expr);
}
