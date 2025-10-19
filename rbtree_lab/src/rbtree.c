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
  node_t *nil = (node_t *)calloc(1, sizeof(node_t)); // 공통 NIL 노드 생성
  nil->color = RBTREE_BLACK; //루트는 블랙
  nil->left = nil->right = nil->parent = NULL; //nil은 색만 있음
  p->nil = nil;
  p->root = nil; // 루트는 처음엔 NIL로 설정

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

  node_t *z = (node_t *)calloc(1, sizeof(node_t)); //새로 삽입할 노드의 메모리 확보
  z->key = key; //노드의 값 넣기
  z->color = RBTREE_RED; //새로 넣는 노드는 무조건 빨간색
  z->left = t->nil; //왼쪽을 nil노드로 초기화
  z->right = t->nil; //오른쪽을 nil노드로 초기화
  
  node_t *parent = t->nil; //새 노드의 부모 노드
  node_t *current = t->root; //현재 탐색하고 있는 노드

  while(current != t->nil) { //현재 노드가 nil이면 멈춤
    parent = current; //현재 노드가 nil이 아니면 값이 있다는 것이므로 부모로 설정
    if(key < parent->key) { //만약 값이 현재 부모 값보다 작다면
      current = current->left; //왼쪽으로 이동
    }
    else {
      current = current->right; //아닐 경우 오른쪽으로 이동 
    }
  }

  z->parent = parent; //새 노드의 부모 노드를 설정 

  if(parent == t->nil) { //만약 비어있는 노드여서 노드가 없을 경우 
    t->root = z; //루트를 현재 노드로 설정 
  }
  else if(key < parent->key) { //입력 받은 값이 부모 노드보다 클 경우
    parent->left = z; //부모 노드의 왼쪽에 현재 노드 연결 
  }
  else {
    parent->right = z; //아닐 경우 부모 노드의 오른쪽에 현재 노드 연결
  }

  // 의사코드
  // 우선 key의 color를 red로 설정한다.
  // root와의 비교를 통해 오른쪽으로 갈지 왼쪽으로 갈지 정한다.
  // 방향을 정한 후 노드를 안착시키고 NIL을 설정한다.
  // 그 후 조건을 검사한다.
  // 위배되는 경우가 있을 경우 회전을 통해서 정상적인 트리로 만든다.
  // 트리의 루트를 리턴한다.
  

  return t->root;
}

node_t case3(rbtree *t, const key_t key) {

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

