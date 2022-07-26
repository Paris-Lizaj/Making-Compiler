#include <stdio.h>
#include "lib.h"

//##############################################################################
void variable()
{
State prevState;//OUSIASTIKA H TWRINH KATASTASH
while (ch!=EOF){
switch (currentState) {
	case QS : 
		{
		if(ch>='A' && ch<='Z'|| ch>='a'&&ch<='z'||ch=='_'||ch>='Á'&&ch<='Ù'||ch>='á'&&ch<='ù')
	       	currentState=MQ1;
		 // Odhgei se periptwsh poy den anagnwrisei xrakthra ths glwssas
	    else                                  
	        currentState=BAD;
	    prevState=QS;
	    break;
	    }	
	case MQ1 : 
	    {
	    if(ch>='0' && ch<='9'||ch>='A' && ch<='Z'||ch>='a'&&ch<='z'||ch=='_'||ch>='Á'&&ch<='Ù'||ch>='á'&&ch<='ù')                         
	       currentState=MQ1;
	    else if(ch==' '||ch=='\n'||ch=='\t'||ch==EOF) //separator
	        {
	          currentState=GOOD;
	          fprintf(fo,"line:%d token: Variable  \n",newline);
	        }
		else                                   
	          currentState=BAD;
	    prevState=MQ1;
	    break;
	    }
	case GOOD : 
	    {
	     break;
	    }                  
	case BAD :
	    {
	    // SyntaxError();
		 prevState=BAD;
	     avoidchars();   
	     break;
	    }
	}	
	//px diabazei . opote paei EQ8, enter (newline++) paei currentState=BAD,epeidh omws  xwris to parakatw continue diabazei ena char
    //ean meta diabasei 1 einai hdh se katastash BAD opote enw einai swsto to xanei
	if(currentState==BAD && prevState!=BAD)		continue;
	if(currentState==BAD)						SyntaxError();
	if(ch=='\n')								newline++;
	if (currentState==GOOD)						correct++;
    if ((currentState==GOOD)||(currentState==BAD)&&(prevState==BAD))
		 break;          
    				
	ch=fgetc(fp);	
}}
//#####################################################################
void integer()
{
State prevState;//OUSIASTIKA H TWRINH KATASTASH
while (ch!=EOF){
switch (currentState) {
	case QS : 
	{
	    //Odhgei se mhdenikh katastash
	    if(ch=='0')
	        currentState=EQ3;
	        //Odhgei se int h float h e analoga me thn katastash pou 8a metabei meta 
	    else if(ch>='1' && ch<='9')
	        currentState=EQ1;
	        //Odhgei se float h e
	    else if(ch=='.')
	        currentState=EQ8;
	        // Odhgei se periptwsh poy den anagnwrisei xrakthra ths glwssas
	    else                                  
	        currentState=BAD;
	    prevState=QS;
	    break;
    }
    case EQ1 : 
	{
	    if(ch>='0' && ch<='9')                        
	        currentState=EQ1;
	    else if(ch=='.')
	    	currentState=EQ4;
	    else if(ch==' '||ch=='\n'||ch=='\t'||ch==EOF) //separator
	        {
	          currentState=GOOD;
	          fprintf(fo,"line:%d token: Int \n",newline);
	        }
		else                                   //oxi string
	          currentState=BAD;
	    prevState=EQ1;
	    break;
	}
	case EQ2 :
	{   
	    if(ch>='1' && ch<='9')
			currentState=EQ1;
		else if(ch=='.')
			currentState=EQ8;
		else if(ch=='0')
			currentState=EQ3;
		else if(ch=='=')
			  currentState=TQ5;
		else if(ch==' '||ch=='\n'||ch=='\t'||ch==EOF) //separator
	        {
			  currentState=GOOD;
	    	  fprintf(fo,"line:%d token: Operator  \n",newline);
	    	}
	    else
	          currentState=BAD;
		prevState=EQ2; 
		break;           
	}
	case EQ3:
	{
		if(ch=='0')
			currentState=EQ3;
	 	else if(ch=='.')
			currentState=EQ4;
		else if(ch==' '||ch=='\n'||ch=='\t'||ch==EOF) //separator
	        {
	          currentState=GOOD;
	          fprintf(fo,"line:%d token: Int \n",newline);
	        }
		else
	          currentState=BAD;
	    prevState=EQ3;
		break;	
	}
	case EQ4:
		{
		if(ch>='0' && ch<='9')
			currentState=EQ4;
		else if(ch=='E' || ch=='e')
			currentState=EQ5;
		else if(ch==' '||ch=='\n'||ch=='\t'||ch==EOF) //separator
	        {
	          currentState=GOOD;
	          fprintf(fo,"line:%d token: Float \t  \n",newline);
	        } 
	    else
	        currentState=BAD;
		prevState=EQ4;
		break;
		}
	case EQ5:
		{
		if(ch=='+' || ch=='-')
			currentState=EQ6;
		else if(ch>='0' && ch<='9')
			currentState=EQ7;
		else                                   
	        currentState=BAD;
		prevState=EQ5;
		break;
		}
	case EQ6:
		{
		if(ch>='0' && ch<='9')
			currentState=EQ7;
		else 
			currentState=BAD;
		prevState=EQ6;
		break;
		}
	case EQ7:
		{
		if(ch>='0' && ch<='9')
			currentState=EQ7;
		else if(ch==' '|| ch=='\n' || ch=='\t' || ch==EOF) //separator
	        {
	          currentState=GOOD;
	          fprintf(fo,"line:%d token: Float \t  \n",newline);
	        } 
	    else
	          currentState=BAD;
	    prevState=EQ7;
		break;
		}
	case EQ8:{
		if(ch>='0' && ch<='9')
		 	currentState=EQ4;
	 	else
	        currentState=BAD;
		prevState=EQ8;
		break;
		}
	
	case GOOD : 
	    {
	     break;
	    }                  
	case BAD :
	    {
	    // SyntaxError();
		 prevState=BAD;
	     avoidchars();   
	     break;
	    }
	}	
	//px diabazei . opote paei EQ8, enter (newline++) paei currentState=BAD,epeidh omws  xwris to parakatw continue diabazei ena char
    //ean meta diabasei 1 einai hdh se katastash BAD opote enw einai swsto to xanei
	if(currentState==BAD && prevState!=BAD)		continue;
	if(currentState==BAD)						SyntaxError();
	if(ch=='\n')								newline++;
	if (currentState==GOOD)						correct++;
    if ((currentState==GOOD)||(currentState==BAD)&&(prevState==BAD))
		 break;          
    				
	ch=fgetc(fp);	
}};
//#######################################################################
void op()
{
State prevState;//OUSIASTIKA H TWRINH KATASTASH
while (ch!=EOF){
switch (currentState) {
	case QS : 
	{
		//Odhgei se Telesth
	    if(ch=='%')
	    	currentState=TQ3;
	    	//Odhgei se Telesth
	    else if(ch=='/')
	    	currentState=TQ2;
	    	//Odhgei se Telesth
	    else if(ch=='*')
	    	currentState=TQ1;
	    	//Odhgei se Telesth
	    else if(ch=='=')
	    	currentState=TQ5;
	    else                                  
	        currentState=BAD;
	    prevState=QS;
	    break;
	}	
	case TQ1:
	{
		if(ch=='=')
			currentState=TQ5;
		else if(ch=='*')
			currentState=TQ3;
		else if(ch==' '||ch=='\n'||ch=='\t'||ch==EOF) //separator
	        {
	          currentState=GOOD;
	          fprintf(fo,"line:%d token: Operator \n",newline);
	        } 
	    else                                
	          currentState=BAD;                                    
		prevState=TQ1;
		break;
	}	
	case TQ2:
	{
		if(ch=='=')
			currentState=TQ5;
		else if(ch=='/')
			currentState=TQ3;
		else if(ch==' '||ch=='\n'||ch=='\t'||ch==EOF) //separator
	        {
	          currentState=GOOD;
			  fprintf(fo,"line:%d token: Operator \n",newline);
	        } 
	    else  
	          currentState=BAD;
		prevState=TQ2;
		break;
	}
	case TQ3:
	{
		if(ch=='=')
			currentState=TQ5;
		else if(ch==' '||ch=='\n'||ch=='\t'||ch==EOF) //separator
		    {
		      currentState=GOOD;                   
			  fprintf(fo,"line:%d token: Operator  \n",newline);
		    } 
		else                                   //oxi string
		    currentState=BAD;
		prevState=TQ3;
		break;
	}
	case TQ5:
	{
		if(ch==' '|| ch=='\n' || ch=='\t' || ch==EOF) //separator
	    	{
	          currentState=GOOD;
	          fprintf(fo,"line:%d token: Operator \n",newline);
	        } 
	    else 
	        currentState=BAD;                               
	        
		prevState=TQ5;
		break;
	}
	case GOOD : 
	{
	     break;
	}                  
	case BAD :
	{
	    // SyntaxError();
		 prevState=BAD;
	     avoidchars();   
	     break;
	}
	}	
	//px diabazei . opote paei EQ8, enter (newline++) paei currentState=BAD,epeidh omws  xwris to parakatw continue diabazei ena char
    //ean meta diabasei 1 einai hdh se katastash BAD opote enw einai swsto to xanei
	if(currentState==BAD && prevState!=BAD)		continue;
	if(currentState==BAD)						SyntaxError();
	if(ch=='\n')								newline++;
	if (currentState==GOOD)						correct++;
    if ((currentState==GOOD)||(currentState==BAD)&&(prevState==BAD))
		 break;          
    				
	ch=fgetc(fp);	
}};
//########################################################################
void comment()
{
State prevState;//OUSIASTIKA H TWRINH KATASTASH
while (ch!=EOF){
switch (currentState) {
	case QS : 
	{
		//Odygei se sxolia
	    if(ch=='#')
	    	currentState=SQ1;
	    	  //Odhgei se sxoio h se string analoga me thn epomenh katastash pou 8a metabei
	    else if(ch=='\"')
	    	currentState=SQ4;
	}
	case SQ1:
		{
		if(ch=='\n' || ch==EOF)
			currentState=GOOD;
		else 
			currentState=SQ1;  
		prevState=SQ1;
		break;
		}
	//gia na anagnwrhsei ena comment 8a "mpei" prwta sth string k meta 8a er8ei edw
	case SQ5:
		{
		if(ch=='\"')
	        currentState=SQ11;
	    else
	    	currentState=SQ6;
		prevState=SQ5;
		break;
		}	
	case SQ6:
		{
		if(ch=='\"') 
	        currentState=SQ7;
	    else
	    	currentState=SQ6;	
		prevState=SQ6;
		break;
		}
	case SQ7:
		{
		if(ch=='\"') 
	        currentState=SQ8;
	    else
	    	currentState=SQ6;
		prevState=SQ7;
		break;
		}
	case SQ8:
		{
		if(ch=='\"') 
	        currentState=SQ9;
	    else
	    	currentState=SQ6;
		prevState=SQ8;
		break;
		}
	case SQ11:
		{
		if(ch=='\"') 
	        currentState=SQ12;
	    else
	    	currentState=SQ6;
		prevState=SQ11;
		break;
		}
	case SQ12:
		{
		if(ch=='\"') 
	        currentState=SQ13;
	    else
	    	currentState=SQ6;
		prevState=SQ12;
		break;
		}
	case SQ9:
		{
		if(ch=='\"') 
	        currentState=SQ10;
		else if(ch==' '||ch=='\n'||ch=='\t'||ch==EOF) //separator
	      currentState=GOOD;
	    else                                  
	      currentState=BAD;
		prevState=SQ9;
		break;
		}
	case SQ10:
		{
		if(ch=='\"') 
	        currentState=SQ13;
		else if(ch==' '||ch=='\n'||ch=='\t'||ch==EOF) //separator
	      currentState=GOOD;
	    else                                 
	      currentState=BAD;
		prevState=SQ10;
		break;
		}
	case SQ13:
		{
		if(ch==' '||ch=='\n'||ch=='\t'||ch==EOF) //separator
	      currentState=GOOD;
	    else                                  
	      currentState=BAD;
		prevState=SQ13;
		break;
		}
	case GOOD : 
	    {
	     break;
	    }                  
	case BAD :
	    {
	    // SyntaxError();
		 prevState=BAD;
	     avoidchars();   
	     break;
	    }
	}	
	//px diabazei . opote paei EQ8, enter (newline++) paei currentState=BAD,epeidh omws  xwris to parakatw continue diabazei ena char
    //ean meta diabasei 1 einai hdh se katastash BAD opote enw einai swsto to xanei
	if(currentState==BAD && prevState!=BAD)		continue;
	if(currentState==BAD)						SyntaxError();
	if(ch=='\n')								newline++;
	if (currentState==GOOD)						correct++;
    if ((currentState==GOOD)||(currentState==BAD)&&(prevState==BAD))
		 break;          
    				
	ch=fgetc(fp);	
}}
//###########################################################################
void string()
{
State prevState;//OUSIASTIKA H TWRINH KATASTASH
while (ch!=EOF){
switch (currentState) {
	case QS : 
	{
		if(ch=='\"')
	    	currentState=SQ3;
	    else if(ch=='\'') 
	        currentState=Q1;
	    else                                  
		    currentState=BAD;
		prevState=QS;
		break;
	}
	case Q1:
	{
		if(ch=='\\')
	    	currentState=Q2;
	    else if(ch=='\'')
	    	currentState=Q3;
	    else if(ch!='\n')
	    	currentState=Q1;
	    else  
	    	currentState=BAD;
	    prevState=Q1;
		break;
	}
	case Q2:
	{
		if(ch!='\n') 
		    currentState=Q1;
	    else                                  
		    currentState=BAD;
		prevState=Q2;
		break;
	}
	case Q3:
	{
		if(ch==' '||ch=='\n'||ch=='\t'||ch==EOF) //separator
	    {
	      currentState=GOOD;                   
		  fprintf(fo,"line:%d token: String \n",newline);
	    } 
	    else                                   
	    	currentState=BAD;
		prevState=Q3;
		break;
	}
	case Q6:
	{
		if(ch!='\n')
	    	currentState=Q4;
		else
	         currentState=BAD;
	    prevState=Q6;
		break;
	}	
	case Q4:
	{
		if(ch=='\"')
			currentState=Q3;
		else if(ch=='\\')
			currentState=Q5;
		else if(ch!='\n') 
	    	currentState=Q4;
	    else 
	        currentState=BAD;
	    prevState=Q4;
		break;
	}
	case Q5:
	{
		if(ch!='\n')
			currentState=Q4;
		else 
		    currentState=BAD;
		prevState=Q5;
		break;
	}
	case SQ3:
	{
		if(ch=='\"')
			currentState=SQ4;
		else if(ch=='\\')
			currentState=Q6;
		else if(ch!='\n') 
	        currentState=Q4;
	    else                                  
	        {
	          currentState=BAD;
	        }
		prevState=SQ3;
		break;
	}
	case SQ4:
	{
		if(ch=='\"')
			{
			  currentState=SQ5;
			  ch=fgetc(fp);
			  comment();
			  return;
			}
		else if(ch==' '||ch=='\n'||ch=='\t'||ch==EOF) //separator
		    {
		      currentState=GOOD;
			  fprintf(fo,"line:%d token: String  \n",newline);
		    } 
		else                                   
		      currentState=BAD;
		prevState=SQ4;
		break;
	}
	case GOOD : 
	{
	     break;
	}                  
	case BAD :
	{
	    // SyntaxError();
		 prevState=BAD;
	     avoidchars();   
	     break;
	}
	}	
	//px diabazei . opote paei EQ8, enter (newline++) paei currentState=BAD,epeidh omws  xwris to parakatw continue diabazei ena char
    //ean meta diabasei 1 einai hdh se katastash BAD opote enw einai swsto to xanei
	if(currentState==BAD && prevState!=BAD)		continue;
	if(currentState==BAD)						SyntaxError();
	if(ch=='\n')								newline++;
	if (currentState==GOOD)						correct++;
    if ((currentState==GOOD)||(currentState==BAD)&&(prevState==BAD))
		 break;          
    				
	ch=fgetc(fp);	
}}
//########################################################################################################
void SyntaxError()
{
//	printf("%c",(char)prevState);
	wrong++;
	fprintf(fo,"line:%d ERROR! %d\n",newline,wrong);
}

void avoidchars ()
{
    dbg("Found unrecognizable characters! -> Skipping...\n=================================================\n");
    if(ch!=' '&&ch!='\n'&&ch!='\t')    	
        while (ch!=EOF)
        {
            if(ch!=' '&&ch!='\n'&&ch!='\t')
               ch=fgetc(fp);
            else
              break;
        }
}

void avoidblanks()
{
    while (ch!=EOF)
    {
        if((ch!=' ')&&(ch!='\n')&&(ch!='\t'))
            break;
        ch=fgetc(fp);
		if(ch=='\n')	newline++;
    }
}

void dbg(char* prn)
{
    printf("%s", prn);
}

