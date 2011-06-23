
/*** Descriptor tags ***/

#define Empty       0
#define OneReader   1
#define OneWriter   2
#define ManyReaders 3
#define ManyWriters 4
#define String      5
#define Forwarded   6
#define Tuple       7

#define TUPLE(x)  (Tuple+((x)<<3))
#define STRING(x) (String+((x)<<3))
#define SIZE(x)   ((x)>>3)

/*** Types ***/

typedef long Val;
typedef unsigned int uint32;
typedef int int32;

/*** Conversion macros ***/

#define intInt(x) ((x)<<1)
#define I(x) ((x)>>1)
#define S(x) ((char*)&OFFSET(x,1))
#define F(x) (*(float*)&OFFSET(x,1))
#define D(x) ((Display *)x)
#define G(x) ((GC)x)
#define W(x) I(x)

#define Zero      0
#define One       2

/*** Macros for tagged values ***/

#define TAG(x)      (((Val)(x))+1)
#define OFFSET(x,i) ((Val*)(x-1))[i]
#define STATUS(x)   OFFSET(x,0)
#define VAL(x)      OFFSET(x,1)

/*** External Values ***/

typedef struct External_ {
  Val value; struct External_ *previous, *next;
} External;

extern External *freeExternals;
extern External liveExternals;

/*** External declarations ***/

extern Val *fromSpace, *fromLimit, *toSpace, *toLimit;
extern Val *Free, *StartQ, *EndQ;

extern int ArgC;
extern char **ArgV;

extern void ComplexInput(Val ch, Val a);
extern void ComplexOutput(Val ch, Val a);

extern void fair (void);
extern void unfair (void);
extern void (*scheduler) (void);

extern Val signalHandler;
extern Val wakeupHandler;
extern int heapSizeInWords;
extern void pictMain0(void);

extern void initGc(void);
extern void Gc(int requiredSizeInWords);

/*** Profiling ***/

typedef struct _CostCentre {
  long idle;
  long def,defAlloc;
  long closures,closureAlloc;
  long runqAlloc;
  long new,chanAlloc,fifoAlloc;
  long ccode, ccodeAlloc;
  long tuple,tupleAlloc;
  long record,recordAlloc;
  long INPUT,INPUTk,INPUTl;
  long INPUTe,INPUT1r,INPUT1w,INPUTmr,INPUTmw;
  long OUTPUT,OUTPUTk,OUTPUTl;
  long OUTPUTe,OUTPUT1r,OUTPUT1w,OUTPUTmr,OUTPUTmw,OUTPUTdef;
  long gc,live,compact,gap;
} CostCentre;

extern CostCentre cc;
extern void printProfile (void);
#include <string.h>
#define COPY(d,s,l) memmove(d,s,l)
