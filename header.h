#define SEC_INCR_bit 0
#define SEC_INCR 1
#define UPDT_RATE 1

#define PRTWI0 7
#define PRTIM2 6
#define PRTIM0 5
#define PRTIM1 3
#define PRSPI0 2
#define PRUSART0 1
#define PRADC 0

#define WDP3 5
#define WDP2 2
#define WDP1 1
#define WDP0 0

//#define CA22 2
//#define CA21 1
//#define CA20 0

//#define OCIEA 1

typedef struct {
    byte seg;
    byte minu;
    byte hora;
    byte dia;   //Dia da semana
    byte diaDoMes;
    unsigned int diaDoAno;
    byte mes;
    byte ano;   //overflow em 2038
    }   tm;
