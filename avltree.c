#include "avltree.h"
#include <stdlib.h>
#include "fatal.h"

struct avlNode {
    elementType element;
    avlTree left;
    avlTree right;
    int height;
};

avlTree makeEmpty( avlTree t ) {
    if( t != NULL ) {
        makeEmpty( t->left );
        makeEmpty( t->right );
        free( t );
    }
    return NULL;
}

position find( elementType x, avlTree t ) {
    if( t == NULL ) {
        return NULL;
    }
    if( x < t->element ) {
        return find( x, t->left );
    }else if( x > t->element ) {
        return find( x, t->right );
    }else{
        return t;
    }
}

position findMin( avlTree t ) {
    if( t == NULL ) {
        return NULL;
    }else if( t->left == NULL ) {
        return t;
    }else{
        return findMin( t->left );
    }
}

position findMax( avlTree t ) {
    if( t == NULL ) {
        return NULL;
    }else if( t->right == NULL ) {
        return t;
    }else{
        return findMax( t->right );
    }
}

static int height( position p ) {
    if( p == NULL ) {
        return -1;
    }else{
        return p->height;
    }
}

static int max( int lhs, int rhs ) {
    return lhs > rhs ? lhs : rhs;
}

static position singleRotateWithLeft( position k2) {
    position k1;
    k1 = k2->left;
    k2->left = k1->right;
    k1->right = k2;

    k2->height = max( height( k2->left ), height(k2->right ) ) + 1;
    k1->height = max( height( k1->left ), k2->height ) + 1;
    return k1;
}

static position singleRotateWithRight( position k1 ) {
    position k2;
    k2 = k1->right;
    k1->right = k2->left;
    k2->left = k1;
    
    k1->height = max( height( k1->left ), height( k1->right ) ) + 1;
    k2->height = max( height(k2->right), k1->height ) + 1;

    return k2;
}

static position doubleRotateWithLeft( position k3 ) {
    k3->left = singleRotateWithRight(k3->left);
    return singleRotateWithLeft(k3);
}

static position doubleRotateWithRight( position k1 ) {
    k1->right = singleRotateWithLeft(k1->right);
    return singleRotateWithRight(k1);
}

avlTree insert( elementType x, avlTree t ) {
    if( t == NULL ) {
        t = malloc( sizeof( struct avlNode ) );
        if( t == NULL ) {
            fatalError("out of space!!!");
        }else{
            t->element = x;
            t->height = 0;
            t->left = t->right = NULL;
        }
    }else if( x < t->element ) {
        t->left = insert(x, t->left);
        if( height( t->left) - height( t->right) == 2 ) {
            if( x < t->left->element ) {
                t = singleRotateWithLeft( t );
            }else{
                t = doubleRotateWithLeft( t );
            }
        }
    } else if( x > t->element ) {
        t->right = insert( x, t->right );
        if( height(t->right) - height( t->left ) == 2) {
            if( x > t->right->element ) {
                t = singleRotateWithRight( t );
            }else{
                t = doubleRotateWithRight( t );
            }
        }
    }

    t->height = max( height( t->left ), height( t->right) ) + 1;
    return t;
}

avlTree delete( elementType x, avlTree  t) {
    return t;    
}

elementType retrieve( position p ) {
    return p->element;
}


