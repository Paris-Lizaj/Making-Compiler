#include <stdio.h>

enum State {QS,		EQ1,EQ2,EQ3,EQ4,EQ5,EQ6,EQ7,EQ8,	TQ1,TQ2,TQ3,TQ5,	MQ1,	
			SQ1, SQ2,SQ3,SQ4,SQ5,SQ6,SQ7,SQ8,SQ9,SQ10,SQ11,SQ12,SQ13,	Q1,Q2,Q3,Q4,Q5,Q6,
			GOOD, BAD};
typedef enum State State;

//emfanizei th sumboloseira pou tou deineis
void dbg(char*);

// H synarthsh avoidblanks diabazei thn eisodo xarakthra-xarakthra
// prospernwntas ta kena, tis nees grammes (\n) kai ta tabs (\t)
// mexri na brei kapoion 'kanoniko' xarakthra, opote kai epistrefei.
void avoidblanks();

// H synarthsh avoidchars diabazei thn eisodo xarakthra-xarakthra
// prospernwntas olous tous 'kanonikous' xarakthres mexri na synanthsei
// kapoio keno h nea grammh (\n) h tab (\t), opote kai epistrefei. Me
// ton tropo auto to programma prospernaei agnwstes seires xarakthrwn.
// Xrisimi episis otan h diadikasia anagnorisis mias symboloseiras apotyxei
// kai prepei na oloklirothei h anagnwsi twn xarakthrvn ths
void avoidchars();

void integer();
void op();
void variable();
void comment();
void string();
void SyntaxError();

char ch;
FILE *fp;
FILE *fo;
int correct=0,wrong=0,newline=1;
State currentState=QS;//OUSIASTIKA H EPOMENH KATASTASH

