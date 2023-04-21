typedef struct _bn {
    unsigned int *number;
    unsigned int size;
    int sign;
} bn;

char *bn_to_string(const bn *src);
bn *bn_alloc(size_t size);
int bn_free(bn *src);
int bn_cpy(bn *dest, bn *src);
int bn_cmp(const bn *a, const bn *b);
void bn_swap(bn *a, bn *b);
void bn_lshift(bn *src, size_t shift);
void bn_rshift(bn *src, size_t shift);
void bn_add(const bn *a, const bn *b, bn *c);
void bn_sub(const bn *a, const bn *b, bn *c);
void bn_mult(const bn *a, const bn *b, bn *c);
void bn_fib_fdoubling(bn *dest, unsigned int n);
void bn_fib(bn *dest, unsigned int n);
int bn_resize(bn *src, size_t size);