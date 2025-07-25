#include <linux/printk.h>
#include <asm/pgtable_types.h>
#include <asm/tmr.h>

static inline pteval_t vote_pte_val(pteval_t v1, pteval_t v2, pteval_t v3)
{
	if (v1 == v2) {
		if (unlikely(v1 != v3)) {
			pr_warn("TMR Voter: Corrected single bit flip in PTE (v3: %llx)\n",
				v3);
		}
		return v1;
	}
	if (v1 == v3) {
		pr_warn("TMR Voter: Corrected single bit flip in PTE (v2: %llx)\n",
			v2);
		return v1;
	}
	if (v2 == v3) {
		pr_warn("TMR Voter: Corrected single bit flip in PTE (v1: %llx)\n",
			v1);
		return v2;
	}

	pr_err("TMR Voter: Uncorrectable triple fault in PTE! v1=%llx, v2=%llx, v3=%llx\n",
	       v1, v2, v3);
	// In a real implementation, this might trigger a panic.
	// Returning 0 might cause a fault, which is a reasonable failure mode.
	return 0;
}

pte_t vote_pte(tmr_pte_t tmr_pte)
{
	pteval_t val = vote_pte_val(native_pte_val(tmr_pte.pte[0]),
				    native_pte_val(tmr_pte.pte[1]),
				    native_pte_val(tmr_pte.pte[2]));
	return native_make_pte(val);
}

pmd_t vote_pmd(tmr_pmd_t tmr_pmd)
{
	pteval_t val = vote_pte_val(native_pmd_val(tmr_pmd.pmd[0]),
				    native_pmd_val(tmr_pmd.pmd[1]),
				    native_pmd_val(tmr_pmd.pmd[2]));
	return native_make_pmd(val);
}

pud_t vote_pud(tmr_pud_t tmr_pud)
{
	pteval_t val = vote_pte_val(native_pud_val(tmr_pud.pud[0]),
				    native_pud_val(tmr_pud.pud[1]),
				    native_pud_val(tmr_pud.pud[2]));
	return native_make_pud(val);
}

p4d_t vote_p4d(tmr_p4d_t tmr_p4d)
{
	pteval_t val = vote_pte_val(native_p4d_val(tmr_p4d.p4d[0]),
				    native_p4d_val(tmr_p4d.p4d[1]),
				    native_p4d_val(tmr_p4d.p4d[2]));
	return native_make_p4d(val);
}

pgd_t vote_pgd(tmr_pgd_t tmr_pgd)
{
	pteval_t val = vote_pte_val(native_pgd_val(tmr_pgd.pgd[0]),
				    native_pgd_val(tmr_pgd.pgd[1]),
				    native_pgd_val(tmr_pgd.pgd[2]));
	return native_make_pgd(val);
}
