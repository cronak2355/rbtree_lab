#include "rbtree.h"

#include <stdlib.h>

rbtree *new_rbtree(void) {
  rbtree *p = (rbtree *)calloc(1, sizeof(rbtree));
  // TODO: initialize struct if needed
  //알비트리 생성
  return p;
}

void delete_rbtree(rbtree *t) {
  // TODO: reclaim the tree nodes's memory
  //알비트리 삭제 
  free(t);
}

node_t *rbtree_insert(rbtree *t, const key_t key) {
  // TODO: implement insert
  //알비트리 삽입
  return t->root;
}

node_t *rbtree_find(const rbtree *t, const key_t key) {
  // TODO: implement find
  //알비트리 찾기
  return t->root;
}

node_t *rbtree_min(const rbtree *t) {
  // TODO: implement find
  //가장 작은 알비트리
  return t->root;
}

node_t *rbtree_max(const rbtree *t) {
  // TODO: implement find
  // 가장 큰 알비트리 
  return t->root;
}

int rbtree_erase(rbtree *t, node_t *p) {
  // TODO: implement erase
  //알비트리 지우기
  return 0;
}

int rbtree_to_array(const rbtree *t, key_t *arr, const size_t n) {
  // TODO: implement to_array
  //알비트리 길이
  return 0;
}

