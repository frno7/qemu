/*
 * Test MFSA, MTSA, MTSAB and MTSAH.
 */

#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include <assert.h>

/* FIXME: Clobber? */

static uint64_t mfsa(void)
{
    uint64_t sa;

    __asm__ __volatile__ (
        "    mfsa  %0\n"
        : "=r" (sa));

    return sa;
}

static void mtsa(uint64_t sa)
{
    __asm__ __volatile__ (
        "    mtsa  %0\n"
        :: "r" (sa));
}

#define MTSAB(rs, imm) \
    __asm__ __volatile__ ( \
        "    mtsab  %0, %1\n" \
        :: "r" (rs), "i" (imm))

#define MTSAH(rs, imm) \
    __asm__ __volatile__ ( \
        "    mtsah  %0, %1\n" \
        :: "r" (rs), "i" (imm))

int main(int argc, char *argv[])
{
    uint64_t t = 0x6665646362613938;
    int i;

    mtsa(t);
    printf("%llx\n", mfsa());

    MTSAB(0, 0); printf("%llx\n", mfsa());
    MTSAB(0, 1); printf("%llx\n", mfsa());
    MTSAB(0, 2); printf("%llx\n", mfsa());
    MTSAB(0, 3); printf("%llx\n", mfsa());
    printf("\n");
    MTSAB(7, 3); printf("%llx\n", mfsa());
    printf("\n");

    for (i = 0; i < 16; i++) {
        MTSAB(i, 0);
        printf("%llx\n", mfsa());
    }
    printf("\n");

    for (i = 0; i < 16; i++) {
        MTSAH(i, 0);
        printf("%llx\n", mfsa());
    }

    return 0;
}
