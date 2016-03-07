#ifndef APP_STACKVM_H
#define APP_STACKVM_H

#include "../inc/qdio.h"

typedef struct {
    list_t istack;
    map_t  varmap;
    uint16 status;
    uint16 maxsize;
} stackVM_t;

typedef enum {
    EOS = 0x00,     // End of stream
    NOP = 0x01,     // Nothing
    pushi = 0x02,   // val
    pushf = 0x03,   // int(dec), int(from tenth) or int(dec), negate int(index), int(from index)
    swap = 0x04,    // None
    addi = 0x05,    // None
    addf = 0x06,    // None
    ci_f = 0x07,    // None
    cf_i = 0x08,    // None
    subi = 0x09,    // None
    subf = 0x10,    // None
    muli = 0x11,    // None
    mulf = 0x12,    // None
    divi = 0x13,    // None
    divf = 0x14,    // None
    modi = 0x15,    // None ; Also modd does not exist!
    raddi = 0x16,   // None ; 1, 5 -> 1+...+5
    rsubi = 0x17,   // None ; 1, 5 -> 1-...-5
    clrs = 0x18,    // None ; Clears the stack
    flip = 0x19,    // None ; Flips the stack
    setl = 0x20,    // int  ; Inserts a jump point on current spot
    jmpl = 0x21,    // int  ; Jumps to a defined jump point
    jmpz = 0x22,    // int  ; Jumps to an offset from zero
    jmpo = 0x23,    // int  ; Jumps to an offset from current spot
    tryl = 0x24,    // int  ; If error, goto label %1 and error code is pushed on stack as int
    tryd = 0x25,    // None ; Ends the closest try-catch block
    seto = 0x26,    // int, int  ; Inserts a jump point to offset from current spot
    setz = 0x27,    // int, int  ; Inserts a jump point to offset from zero
    pop = 0x28,     // None ; Pops the last item out (destroyed)
    popc = 0x29,    // int  ; Pops a specific amount of items
    cmpt = 0x30,    // None ; Compares the next 2 items' types. 1 means same, 0 means different
    eqlv = 0x31,    // None ; Compares the next 2 items' value. Types must be same otherwise exception
    inb = 0x32,     // None ; Pops one value as port and pushes val as in value
    outb = 0x33,    // None ; Pops two values and invokes outportb in asm
    outw = 0x34,    // None ; (See outb)
    sftl = 0x35,    // None ; << operator in C
    sftr = 0x36,    // None ; >> operator in C
    andb = 0x37,    // None ; & operator in C
    orb = 0x38,     // None ; | operator in C
    xorb = 0x39,    // None ; ^ operator in C
    notb = 0x40,    // None ; ~ or ! operator in C
    _hlt = 0x41,    // None ; asm "hlt"
    _cli = 0x42,    // None ; asm "cli"
    _sti = 0x43,    // None ; asm "sti"
    cmpv = 0x44,    // None ; Compares the next 2 items' value. Types must be same otherwise exception
    ifjl = 0x45,    // int  ; If true (1), Jumps to a defined jump point
    ifjz = 0x46,    // int  ; If true (1), Jumps to an offset from zero
    ifjo = 0x47,    // int  ; If true (1), Jumps to an offset from current spot
    defi = 0x48,    // int  ; Param1 = %1i
    deff = 0x49,    // int  ; Param1 = %1f
    geti = 0x50,    // int  ; Push ivalue linked to Param1 in stack
    getf = 0x51,    // int  ; Push fvalue linked to Param1 in stack
    putf = 0x52,    // None ; prints %1
    puti = 0x53,    // None ; prints itos10(%1)
    putc = 0x54,    // None ; prints (char) %1
    blnk = 0x55,    // None ; Clears screen
    infbf = 0x56,   // None ; A infomation box
    infbi = 0x57,   // None ; A infomation box
    infbc = 0x58,   // None ; A infomation box
    dup = 0x59,     // None ; Duplicates last item in stack
    pushs = 0x60,   // int  ; Reference to a string (Got you stressed out there)
    puts = 0x61,    // None ; prints %1
    infbs = 0x62,   // None ; A infomation box
    cs_i = 0x63,    // None ; Converts a string to ascii value
    ci_s = 0x64,    // None ; Converts int to string 123 -> "123"
    cs_p = 0x65,    // None ; Converts string to its pointer value
    cf_s = 0x66,    // None ; Converts float to string
    ei_s = 0x67,    // None ; Encodes int to string. Essentially the Base64 algorithm
    ci_p = 0x68,    // None ; Casts pointer address to string
    thrwi = 0x69,   // Int  ; Throws an exception
    defs = 0x70,    // Int  ; Param1 = %1s
    gets = 0x71,    // Int  ; Push svalue linked to Param1 in stack
    waiti = 0x72,   // None ; Wait for %1i seconds
    randf = 0x73    // None ; Pushes a value between 0 and 1
} STACKVM_OP;

typedef enum {
    EXEC_SUCCESS = 0,
    ILLEGAL_OPND = 1,
    DIVI_BY_ZERO = 2,
    ILLEGAL_JOFF = 3,
    ILLEGAL_TRYB = 4,
    BAD_CONV_TYP = 5,
    UNDEF_EXCEPT = 6,
    NEG_WAIT_TME = 7
} statusCode;

stackVM_t initEnv(uint16);

void cleanEnv(stackVM_t*);

uint32 invokeOp(stackVM_t*, int[]);

#endif
