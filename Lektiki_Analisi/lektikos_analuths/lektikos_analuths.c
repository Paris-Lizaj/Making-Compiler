/* Onoma arxeiou:	lektikos_analuths.c
   Perigrafh:		Skeletos gia lektiko analyth grammeno se glwssa programmatismou C
   Syggrafeas:		Ergasthrio Metaglwttistwn, Tmhma Mhx.Plhroforikhs TE, TEI Athhnas
   					Lizai Paris		Xatzhs Dimitris		Sfyridaki Angeliki
*/


#include <stdio.h>
#include "lib.c"

// H synarthsh main - Arxiko shmeio ekteleshs tou programmatos.
int main(int argc, char** argv)
{
    fp=fopen("input.txt","r");
    fo=fopen("output.txt","w");

    if (fp==NULL) return 1;
    ch=fgetc(fp);
    if(ch=='\n')
		newline++;
    while(ch!=EOF)
    {
        avoidblanks();
	/* Anagnwrish xarakthra. */
        if(ch == '\'' ||  ch=='\"')
    		string();	//ola ta string kai ta comment me """
        else if(ch=='#' )
        	comment();	//ola ta comment apo #
		else if((ch>='0' && ch<='9') || ch=='.')
        	integer();        //an einai INT h FLOAT h E h Telesths xwris thn periptwsh na 3ekinaei apo +-
        else if(ch=='/'||ch=='='||ch=='%'||ch=='*')
        	op();		//an einai operator xwris ta + += - -=
        else if(ch=='+' || ch=='-')		//e3etazw 3exwrista thn periptwsh na arxizei kati me + -
    	{
    		ch=fgetc(fp);
			if(ch>='1' && ch<='9')	//einai integer opote pas kateu8eian sthn katastash EQ1
			{
			  currentState=EQ1;
			  ch=fgetc(fp);
			  integer();
			}
			else if(ch=='.')	//einai integer opote pas kaateu8eian sthn katastash EQ8
			{
			  currentState=EQ8;
			  ch=fgetc(fp);
			  integer();
			}
			else if(ch=='0')	//einai integer opote pas kateu8eian sthn katastash EQ3
			{  
			  currentState=EQ3;
			  ch=fgetc(fp);
			  integer();
			}
			else if(ch=='=')	//einai operator opote pas kateu8eian sthn katastash TQ5
		  	{
			  currentState=TQ5;
			  ch=fgetc(fp);
			  op();
			}
			else if(ch==' '||ch=='\n'||ch=='\t'||ch==EOF) //separator einai h telikh katastash + 
        	{
		  		currentState=GOOD;
    	  		fprintf(fo,"line:%d token: Operator  \n",newline);
    	  		
    		}
			else
			{                              
	        	currentState=BAD;
				op();
			}	
	    }
		else if(ch>='A' && ch<='Z'||ch>='a'&&ch<='z'||ch=='_'||ch>='Á'&&ch<='Ù'||ch>='á'&&ch<='ù')
       		variable();
        else
            {
	      // O xarakthras den mporese na tairiaksei kapou -> mh apodektos
            fprintf(fo,"+Error! Can't recognize characters!\n");
            avoidchars();
            //sthn periptwsh auth gia na bgei apo thn avoidchars xreiazetai ena leuko xarakthra ekei omws den exw if na anagnwrizei to \n opote to ebala edw
            if(ch=='\n')
				newline++;
            }
        currentState=QS;//OUSIASTIKA H EPOMENH KATASTASH
        ch=fgetc(fp);
    }
    fprintf(fo,"Correct:%d\tWrong:%d",correct,wrong);
    fclose(fp);
    fclose(fo);
    dbg("EOF!\n");
    return 0;
}

