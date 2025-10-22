//rbtree
//1. 모든 노드는 레드이거나 블랙이다.
//2. 루트는 블랙이다.
//3. 모든 리프(NIL)은 블랙이다.
//4. 노드가 레드이면 그 노드의 자식은 모두 블랙이다.
//5. 각 노드로부터 그 노드의 자손인 리프로 가는 경로들은 모두 같은 수의 블랙 노드를 포함한다.



//////////////////////////////////////////////////////
#include "rbtree.h"

#include <stdlib.h>
//////////////////////////////////////////////////////
node_t* get_uncle(rbtree* t, node_t *grandparent, node_t *parent);
node_t* fix_up(node_t *z, rbtree *t);
node_t* case3_LL_Match(node_t *z, rbtree *t);
node_t* case3_RR_Match(node_t *z, rbtree *t);
node_t* case2_LR_MissMatch(node_t *z, rbtree *t);
node_t* case2_RL_MissMatch(node_t *z, rbtree *t);
node_t* case1_Color_Change(node_t *z, rbtree *t);


//////////////////////////////////////////////////////
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

  t->root->color = RBTREE_BLACK; //루트는 블랙
  fix_up(z, t);
  return t->root;
}

node_t* get_uncle(rbtree* t, node_t* grandparent, node_t* parent) {// 삼촌 반환 함수
	if (grandparent == t->nil || parent == t->nil) {
    return t->nil;
  }
  if (grandparent->left == parent) {
    return grandparent->right;
  } 	
	else {
    return grandparent->left;
  }
}

node_t* get_uncle(rbtree* t, node_t* grandparent, node_t* parent) {
	if (grandparent == t->nil || parent == t->nil) {
        	return t->nil;
   	 }
   	 if (grandparent->left == parent) {
        	return grandparent->right;
    	} 	
	else if (grandparent->right == parent) {
        	return grandparent->left;
    	}
}

node_t *fix_up(node_t *z, rbtree *t) {
  node_t *parent = z->parent; //z의 부모를 parent로 지정
  node_t *grandparent = parent->parent; //할아버지 노드 추가

  while(z->parent->color == RBTREE_RED) { //모든 case에서 부모는 red이므로 case발동은 부모가 red라는 것을 전제로 함
      if(get_uncle(t, grandparent, parent) == RBTREE_RED) { //부모가 red이고 삼촌도 red일 경우 
        case1_Color_Change(z, t); //case1
      }
      else if(parent->right == z && grandparent->left == parent && get_uncle(t, grandparent, parent) == RBTREE_BLACK) {
        case2_LR_MissMatch(z, t); //case2 LEFT and RIGHT 
      }
      else if(parent->left == z && grandparent->right == parent && get_uncle(t, grandparent, parent) == RBTREE_BLACK) {
        case2_RL_MissMatch(z, t); //case2 RIGHT and LEFT
      }
      else if(parent->right == z && grandparent->right == parent&& get_uncle(t, grandparent, parent) == RBTREE_BLACK) {
        case3_RR_Match(z, t); //case3 RIGHT and RIGHT
      }
      else if(parent->left == z && grandparent->left  == parent&& get_uncle(t, grandparent, parent) == RBTREE_BLACK) {
        case3_LL_Match(z, t); //case3 LEFT and LEFT
      }
  }
}

node_t* case3_LL_Match(node_t* z, rbtree *t) { //테스트 케이스3 왼쪽 부모의 왼쪽 노드가 빨간일 경우 
    node_t * parent = z->parent;  // z의 부모를 parent로 지정
    node_t * grandparent = z->parent->parent;  // 할아버지 노드 추가
    
    grandparent->left = parent->right; // 부모의 오른쪽을 할아버지의 왼쪽으로 지정
    if (parent->right != t->nil) //부모의 오른쪽이 비어있지 않을 경우
        parent->right->parent = grandparent; // 부모의 오른쪽 노드의 부모를 할아버지로 지정

    parent->right = grandparent;  // 할아버지를 부모의 오른쪽으로
    parent->parent = grandparent->parent;  // 부모의 부모를 증조부모로 연결
    
    
    if (grandparent->parent != t->nil) { // 증조부모가 있다면
        if (grandparent->parent->left == grandparent) {//할아버지의 위치가 증조부의 왼쪽이였다면
            grandparent->parent->left = parent; //부모를 증조부의 왼쪽으로
        }
        else {
          grandparent->parent->right = parent; //아니라면 부모를 증조부의 오른쪽으로
        }      
    }
    grandparent->parent = parent;  // 할아버지의 부모를 parent로

    // 색 변경
    parent->color = RBTREE_BLACK;
    grandparent->color = RBTREE_RED;  

    return parent; // 새로운 서브트리 루트
}

node_t* case3_RR_Match(node_t* z, rbtree *t) { //테스트 케이스3 오른쪽 부모의 오른쪽 노드가 빨간일 경우 
    node_t * parent = z->parent;  // z의 부모를 parent로 지정
    node_t * grandparent = z->parent->parent;  // 할아버지 노드 추가
    
    grandparent->right = parent->left; // 부모의 왼쪽을 할아버지의 오른쪽으로 지정
    if (parent->left != t->nil) //부모의 왼쪽이 비어있지 않을 경우
        parent->left->parent = grandparent; // 부모의 왼쪽 노드의 부모를 할아버지로 지정

    parent->left = grandparent;  // 할아버지를 부모의 왼쪽으로
    parent->parent = grandparent->parent;  // 부모의 부모를 증조부모로 연결
    
    
    if (grandparent->parent != t->nil) { // 증조부모가 있다면
        if (grandparent->parent->left == grandparent) //할아버지의 위치가 증조부의 왼쪽이였다면
            grandparent->parent->left = parent; //부모를 증조부의 왼쪽으로
        else
            grandparent->parent->right = parent; //아니라면 부모를 증조부의 오른쪽으로
    }
    
    grandparent->parent = parent;  // 할아버지의 부모를 parent로

    // 색 변경
    parent->color = RBTREE_BLACK;
    grandparent->color = RBTREE_RED;  // z->parent->parent 대신 grandparent 사용

    return parent; // 새로운 서브트리 루트
}

node_t* case2_LR_MissMatch(node_t* z, rbtree *t) {
    node_t * parent = z->parent;  // z의 부모를 parent로 지정
    node_t * grandparent = z->parent->parent;  // 할아버지 노드 추가
    node_t * temp = z->left; //붙였다 뗄 노드 추가

    grandparent->left = z; //할아버지의 왼쪽을 z로 설정
    z->parent = grandparent; //z의 부모를 할아버지로 설정
    z->left = parent; //z의 왼쪽을 부모로 설정
    parent->right = temp; //z의 왼쪽을 부모로 설정
    parent->parent = z; //부모의 부모를 z로 설정

    case3_LL_Match(z, t); //펴진 트리를 넘겨줌
}

node_t* case2_RL_MissMatch(node_t* z, rbtree *t) {
    node_t *parent = z->parent; //z의 부모를 parent로 지정
    node_t *grandparent = parent->parent; //할아버지 노드 추가
    node_t *temp = z->right; //붙였다 뗄 노드 추가

    grandparent->right = z; //할아버지의 오른쪽을 z로 설정
    z->parent = grandparent; //z의 부모를 할아버지로 설정
    z->right = parent; //z의 오른쪽을 부모로 설정
    parent->left = temp; //z의 왼쪽을 부모로 설정  
    parent->parent = z; //부모의 부모를 z로 설정

    return case3_RR_Match(z, t); //펴진 트리를 넘겨줌
}

node_t* case1_Color_Change(node_t* z, rbtree *t) {
  node_t *parent = z->parent; //z의 부모를 parent로 지정
  node_t *grandparent = parent->parent; //할아버지 노드 추가

  parent->color = RBTREE_BLACK;
  if(grandparent->left == parent) {
    grandparent->right->color = RBTREE_BLACK;
  }
  else {
    grandparent->left->color = RBTREE_BLACK;
  }
  grandparent->color = RBTREE_RED;

  return grandparent;
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

