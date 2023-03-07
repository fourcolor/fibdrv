#include <linux/string.h>
#define XOR_SWAP(a, b, type) \
    do {                     \
        type *__c = (a);     \
        type *__d = (b);     \
        *__c ^= *__d;        \
        *__d ^= *__c;        \
        *__c ^= *__d;        \
    } while (0)


static void __swap(void *a, void *b, size_t size)
{
    if (a == b)
        return;

    switch (size) {
    case 1:
        XOR_SWAP(a, b, char);
        break;
    case 2:
        XOR_SWAP(a, b, short);
        break;
    case 4:
        XOR_SWAP(a, b, unsigned int);
        break;
    case 8:
        XOR_SWAP(a, b, unsigned long);
        break;
    default:
        /* Do nothing */
        break;
    }
}

static void reverse_str(char *str, size_t n)
{
    for (int i = 0; i < (n >> 1); i++)
        __swap(&str[i], &str[n - i - 1], sizeof(char));
}

static void string_number_add(char *a, char *b, char *out)
{
    size_t size_a, size_b;
    int i, carry = 0;
    int sum;

    /*
     * Make sure the string length of 'a' is always greater than
     * the one of 'b'.
     */
    if (strlen(a) < strlen(b))
        __swap((void *) &a, (void *) &b, sizeof(void *));

    size_a = strlen(a);
    size_b = strlen(b);

    reverse_str(a, size_a);
    reverse_str(b, size_b);

    for (i = 0; i < size_b; i++) {
        sum = (a[i] - '0') + (b[i] - '0') + carry;
        out[i] = '0' + sum % 10;
        carry = sum / 10;
    }

    for (i = size_b; i < size_a; i++) {
        sum = (a[i] - '0') + carry;
        out[i] = '0' + sum % 10;
        carry = sum / 10;
    }

    if (carry)
        out[i++] = '0' + carry;

    out[i] = 0;

    reverse_str(out, i);

    /* Restore the original string */
    reverse_str(a, size_a);
    reverse_str(b, size_b);
}