#ifndef NASM_X86PG_H
#define NASM_X86PG_H

#include "nasm.h"
#include "insnlist.h"
#include "section.h"
#include "seed.h"
#include "tmplt.h"


/* big sequence index
 */
#define SEQ_INDEXES_NUM 6
/* big_sequence_index:
 *     A big index structure used to traverse all the operand combinations.
 *     Every field in this structure has a corresponding create_XXX function.
 *     It is used to generate unit test.
 */
typedef struct big_sequence_index {
    bool start;
    int i;
    int num;
    int indexes[SEQ_INDEXES_NUM];
} big_sequence_index;


/* INDEX SIZE | INDEX POS
 */
typedef uint32_t bseqiflags_t;

#define INDEXPOS_SHIFT         (0)
#define INDEXPOS_BITS          (6)
#define INDEXPOS_MASK          (((1 << INDEXPOS_BITS) - 1) << INDEXPOS_SHIFT)
#define GEN_INDEXPOS(bit)      (bit << INDEXPOS_SHIFT)
                            
#define INDEXSIZE_SHIFT       (6)
#define INDEXSIZE_BITS        (5)
#define INDEXSIZE_MASK        (((1 << INDEXSIZE_BITS) - 1) << INDEXSIZE_SHIFT)
#define GEN_INDEXSIZE(bit)    (bit << INDEXSIZE_SHIFT)

/* bits distribution (counted from 0)
 *  *
 *   3         2         1
 * 210987654321098765432109876543210
 * ...........................111111 index position in bseqi.indexes[]
 * ......................11111...... index size of bseqi.indexes[pos]
 */
#define BSEQIFLAG_VALUE(flags,flag)      ((flags & flag##_MASK) >> flag##_SHIFT)
#define BSEQIFLAG_INDEXPOS(flags)        BSEQIFLAG_VALUE(flags,INDEXPOS)
#define BSEQIFLAG_INDEXSIZE(flags)       BSEQIFLAG_VALUE(flags,INDEXSIZE)

void bseqi_init(big_sequence_index *bseqi);
bseqiflags_t bseqi_flags(opflags_t opndflags);
bool bseqi_inc(big_sequence_index *bseqi, const insn_seed *seed, int opnum);


/* global program generator state
 */
struct X86PGState {
    bool seqMode;
    big_sequence_index bseqi;

    struct section text_sec;
    struct section data_sec;

    struct {
        enum opcode opcode;
        insn *curr_inst;
        bool need_init;
    }; /* current instruction */

    blk_struct *curr_blk;

    int labeli;
    insnlist_entry_t **labelspos;
    bool lock_ctrl;
    bool lock_ecx;
    bool lock_ebx;
    bool lock_edx;

    insnlist_t *instlist;
    insnlist_entry_t *insertpos;
};

extern struct X86PGState X86PGState;

void init_x86pgstate(void);
void reset_x86pgstate(void);

enum position {
    INSERT_AFTER,
    INSERT_BEFORE,
    INSERT_TAIL
};

void stat_insert_insn(insn *inst, enum position pos);

blk_struct *stat_get_curr_blk(void);
void stat_set_curr_blk(blk_struct *blk);
int stat_get_labeli(void);
void stat_inc_labeli(void);
enum opcode stat_get_opcode(void);
void stat_set_opcode(enum opcode opcode);
bool stat_get_need_init(void);
void stat_set_need_init(bool need_init);

void stat_lock_ctrl(void);
void stat_unlock_ctrl(void);
bool stat_ctrl_locked(void);
void stat_lock_edx(void);
void stat_unlock_edx(void);
bool stat_edx_locked(void);
void stat_lock_ebx(void);
void stat_unlock_ebx(void);
bool stat_ebx_locked(void);
void stat_lock_ecx(void);
void stat_unlock_ecx(void);
bool stat_ecx_locked(void);

#endif