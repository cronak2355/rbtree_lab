//rbtree
//1. 모든 노드는 레드이거나 블랙이다.
//2. 루트는 블랙이다.
//3. 모든 리프(NIL)은 블랙이다.
//4. 노드가 레드이면 그 노드의 자식은 모두 블랙이다.
//5. 각 노드로부터 그 노드의 자손인 리프로 가는 경로들은 모두 같은 수의 블랙 노드를 포함한다.





//////////////////////////////////////////////////////
#include "rbtree.h"

#include <stdlib.h>

rbtree *new_rbtree(void) {
  rbtree *p = (rbtree *)calloc(1, sizeof(rbtree));
  // TODO: initialize struct if needed
  // tree = `new_tree()`: RB tree 구조체 생성
  // 여러 개의 tree를 생성할 수 있어야 하며 각각 다른 내용들을 저장할 수 있어야 합니다.
  p->root = (node_t *)calloc(1, sizeof(node_t)); //여러 개의 루트를 만들 수 있게 트리의 루트 값을 할당
  p->root->color = RBTREE_BLACK; //루트는 블랙
  return p;
}

void delete_rbtree(rbtree *t) {
  // TODO: reclaim the tree nodes's memory
  // 알비트리 삭제 
  free(t);
}

node_t *rbtree_insert(rbtree *t, const key_t key) {
  // TODO: implement insert
  // 알비트리 삽입
  // `tree_insert(tree, key)`: key 추가
  // 구현하는 ADT가 multiset이므로 이미 같은 key의 값이 존재해도 하나 더 추가 합니다.
  // 새 노드는 항상 빨강으로 삽입
  // 삽입 후 위 조건이 깨지면 → 색 변경 + 회전으로 복구
  // 루트는 마지막에 반드시 검정으로 바꿔야 함

  // 의사코드
  // 우선 key의 color를 red로 설정한다.
  // root와의 비교를 통해 오른쪽으로 갈지 왼쪽으로 갈지 정한다.
  // 방향을 정한 후 노드를 안착시키고 NIL을 설정한다.
  // 그 후 조건을 검사한다.
  // 위배되는 경우가 있을 경우 회전을 통해서 정상적인 트리로 만든다.
  // 트리의 루트를 리턴한다.
  
  // while(t->root->left != NULL || t->root->right != NULL) {
  //     if(key > t->root) {
  //       t->root->right = key;
  //       t->root->right->color = 'red';

  //     }
  //     else {
  //       t->root->left = key;
  //       t->root->left->color = 'red';
  //     }
  //     t->root = 
  // }
  
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

