#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAXTEXT 1024
#define MAXURL 1024
#define MAXTAG 16

char Char;
char Text[MAXTEXT];
char URL[MAXURL];
char Tag[MAXTAG];
SymbolType Symbol;

typedef enum SymbolType {
	plaintext, othertag,
	htmlS, htmlE, headS, headE, bodyS, bodyE, footerS, footerE, titleS, titleE,
	h1S, h1E, h2S, h2E, h3S, h3E, h4S, h4E, pS, pE, aS
}SymbolType;

void getNextChar(){
	int ch = getchar();
	if (ch==EOF)
	{
		Char = '\0';
	}
	else
	{
		Char = ch;
	}
}

void skipSpace(){
	while (Char==" ")
	{
		getNextChar();
	}
}

void getTagName(){
	for (int i = 0; i < MAXTAG; i++)
	{
		Tag[i] = '\0';
	}
	int j = 0;

	while (isalnum(Char))
	{
		if (j<MAXTAG-1)
		{
			Tag[j++] = toupper(Char);
			getNextChar();
		}
	}
}

void getText(){
	int i = 0;

	while (Char != '<'&&Char!='\0')
	{
		if (i<MAXTEXT-1)
		{
			getNextChar();
		}
	}
	Text[i] = '\0';
	printf("%s\n", Text);
}

void getURL(){
	int i = 0;

	while (Char != '"' && Char != '\0')
	{
		if (i < MAXURL - 1)
		{
			getNextChar();
		}
	}
	Text[i] = '\0';
	printf("%s\n", URL);
}


SymbolType startTag(){

	char* tag[] = {"HTML","HEAD","BODY","FOOTER","tITLE","H1","H2","H3","H4","P","A"};

	SymbolType startTags[] = { htmlS, headS, bodyS, footerS, titleS,
					   h1S, h2S, h3S, h4S, pS, aS };

	for (int  i = 0; i < sizeof(tag)/sizeof(tag[0]); i++)
	{
		if (!strcmp(Tag,tag[i]))
		{
			return startTags[i];
		}
	}
	return othertag;
}

SymbolType endTag() {

	char* tag[] = { "HTML","HEAD","BODY","FOOTER","tITLE","H1","H2","H3","H4","P" };

	SymbolType endTags[] = { htmlE, headE, bodyE, footerE, titleE,
					   h1E, h2E, h3E, h4E, pE};

	for (int i = 0; i < sizeof(tag) / sizeof(tag[0]); i++)
	{
		if (!strcmp(Tag, tag[i]))
		{
			return endTags[i];
		}
	}
	return othertag;
}

void skipToChar(char ch) {
	while ((toupper(Char) != toupper(ch)) && (Char != '>'))
	{
		getNextChar();
	}
}

void skipToAlpha() {
	while (((toupper(Char) < 'A') || (toupper(Char) > 'Z')) && (Char != '>'))
	{
		getNextChar();
	}
}

int expect(SymbolType sym) {
	if (accept(sym))
	{
		return 1;
		perror("expect: unxepected symbol");
	}
	return 0;
}

void parseTag() {
	getTagName();



}

int getNextSymbol() {
	skipSpace();
	switch (Char)
	{
	case'<': {
		getNextChar();
		getTagName();
		if (Char=='/')
		{
			getNextChar();
			getTagName();
			Symbol = endTag();
			skipToChar('>');
			getNextChar();
			return 0;
		}
		if (toupper(Char)=='A')
		{
			Symbol = aS;
			skipToAlpha();
			if (Char=='>')
			{
				return 0;
			}
			else
			{
				skipToChar('h');
				if (Char=='>')
				{
					skipToChar('=');
					getNextChar();
					if (Char == '"' || Char == '\'')
					{
						getNextChar();
						getURL();
						skipToChar('>');
						getNextChar();
					}
				}
			}
		}
		else
		{
			getTagName();
			Symbol = startTag();
			skipToChar('>');
			getNextChar();

		}
	}break;
	default:
	{
		getText();
		Symbol = plaintext;
		skipToChar('<');
	}
		break;
	}
}

