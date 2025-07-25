#ifndef _ASM_X86_TMR_H
#define _ASM_X86_TMR_H

#include <linux/types.h>
#include <asm/pgtable_types.h>

#define p4d_tmr(p4d) ((tmr_p4d_t *)(p4d))
#define pud_tmr(pud) ((tmr_pud_t *)(pud))
#define pmd_tmr(pmd) ((tmr_pmd_t *)(pmd))
#define pte_tmr(pte) ((tmr_pte_t *)(pte))

typedef struct {
	pte_t pte[3];
} tmr_pte_t;

typedef struct {
	pmd_t pmd[3];
} tmr_pmd_t;

typedef struct {
	pud_t pud[3];
} tmr_pud_t;

typedef struct {
	p4d_t p4d[3];
} tmr_p4d_t;

typedef struct {
	pgd_t pgd[3];
} tmr_pgd_t;

#endif /* _ASM_X86_TMR_H */
