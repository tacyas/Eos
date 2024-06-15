#ifndef STRING_H
#define STRING_H
#include <stdio.h>

/* constant begin */
#define STRING_MAX_LENGTH (8192)
#define STRING_WORD_SEPARATOR  " ,\t" 
#define STRING_COMMENT_LINE_ID '#' 
/* constant end */

/* struct begin */
typedef char*         String;
typedef unsigned long stringParaTypeInteger;
typedef float         stringParaTypeReal;
/* struct end */

#ifdef __cplusplus
extern "C" {
#endif

/* prototype begin */
extern void stringInit(String s, char* message);

/*
	mode&0x01 := 0: quary   1: no quary
	mode&0x02 := 0: message 1: no message
*/
extern String stringGetFromFile(char* s, char* message, FILE* fptIn, FILE* fptOut, long mode);
extern String stringGetFromFileWithSkippingComment(char* s, char* message, FILE* fptIn, FILE* fptOut, long mode);
extern char* __getStringData(char* s, char* message, FILE* fptIn, FILE* fptOut, long mode);

extern String stringGetNthWord(char* s, long nth, char* exception);
extern double stringGetNthRealData(char* s, long nth, char* exception);
extern long   stringGetNthIntegerData(char* s, long nth, char* exception);
extern String stringGetNthWord0(char* s, long nth, char* exception);
extern double stringGetNthRealData0(char* s, long nth, char* exception);
extern long   stringGetNthIntegerData0(char* s, long nth, char* exception);

extern String stringGetWordFromField(char* s, long init, long end);
extern double stringGetRealDataFromField(char* s, long init, long end);
extern long   stringGetIntegerDataFromField(char* s, long init, long end);

extern long stringIsSame(String s1, String s2, long n);

extern String stringDefinedValueGet(String s, String key, String separater);
extern long stringLength(String s);
extern long stringCopy(String dst, String src, long n);
extern String stringDuplicate(String src);

/* prototype end */

#ifdef __cplusplus
};
#endif

#endif /* STRING_H */
