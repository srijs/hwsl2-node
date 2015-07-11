#include "core/sl2-inl.h"

void hwsl2_unit(void *h) {
  sl2_unit(h);
};

void hwsl2_append(void *h, char *buf, size_t len) {
  sl2_mul_buf_right(h, (unsigned char *)buf, len);
}

void hwsl2_prepend(void *h, char *buf, size_t len) {
  sl2_mul_buf_left(h, (unsigned char *)buf, len);
}

void hwsl2_concat(void *z, void *l, void *r) {
  sl2_mul(z, l, r);
}

int hwsl2_equals(void *l, void *r) {
  return sl2_eq(l, r);
}

void hwsl2_serialize(void *h, char *buf) {
  sl2_serialize(h, (unsigned char *)buf);
};
