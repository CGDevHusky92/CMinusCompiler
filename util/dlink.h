/*
 * dlink.h
 *
 *  Created on: Jun 29, 2009
 *      Author: carr
 */

#ifndef DLINK_H_
#define DLINK_H_

#include <util/general.h>

struct DLinkList_struct;

typedef struct DLinkNode_struct {
    struct DLinkNode_struct *next; /**< the next node on a list */
    struct DLinkNode_struct *prev; /**< the previous node on a list */
    Generic atom; /**< the data stored in the node */
    struct DLinkList_struct *up; /**< the list on which the node resides */
} DLinkNode, *DNode; /**< a node on a linked list */

typedef struct DLinkList_struct {
    DLinkNode *head; /**< the first node on a list */
    DLinkNode *tail; /**< the second node on a list */
    Generic atom; /**< user data regarding the list */
} DLinkList, *DList; /**< a linked list */

EXTERN(DLinkNode *, dlinkNodeAlloc, (Generic atom));
/*  Generic atom;	info for this node
 *
 * Returns a new initialized node.
 * `atom' is typically a pointer to the "owner" of the node,
 * eg. another structure containing the node.
 */

EXTERN(DLinkList *, dlinkListAlloc, (Generic atom));
/*  Generic atom;	info for this node
 *
 * Returns a new initialized list.
 */

EXTERN(DLinkNode *, dlinkNodeInit, (DLinkNode *node, Generic atom));
/*  DLinkNode *node;
 *  Generic atom;
 *
 * Initialize the fields of a node in a sensible way.
 * `atom' is typically a pointer to the "owner" of the node,
 * eg. another structure containing the node.
 * `node' is returned, for convenience.
 */

EXTERN(DLinkList *, dlinkListInit, (DLinkList *list, Generic atom));
/*  DLinkList *list;
 *  Generic atom;
 *
 * Initialize the fields of a list in a sensible way.
 * `atom' is typically a pointer to the "owner" of the list,
 * eg. another structure containing the list.
 * `list' is returned, for convenience.
 */

EXTERN(DLinkNode *, dlinkHead, (DLinkList *list));
/*  DLinkList *list;
 *
 * Returns the head of `list'.  Returns NULLNODE if list is empty.
 */

EXTERN(DLinkNode *, dlinkTail, (DLinkList *list));
/*  DLinkList *list;
 *
 * Returns the tail of `list'.  Returns NULLNODE if list is empty.
 */

EXTERN(DLinkList *, dlinkList, (DLinkNode *node));
/*  DLinkNode *node;
 *
 * Returns the list of which `node' is a member.
 */

EXTERN(Generic, dlinkListAtom, (DLinkList *list));
/*  DLinkList *list;
 *
 * Returns the atom associated with `list'.
 */

EXTERN(Generic, dlinkNodeAtom, (DLinkNode *node));
/*  DLinkNode *node;
 *
 * Returns the atom associated with `node'.
 */

EXTERN(DLinkNode *, dlinkNext, (DLinkNode *node));
/*  DLinkNode *node;
 *
 * Returns the next node in the list.  Returns NULLNODE if there is no next node.
 */

EXTERN(DLinkNode *, dlinkPrev, (DLinkNode *node));
/*  DLinkNode *node;
 *
 * Returns the previous node in the list.  Returns NULLNODE if there is no previous node.
 */


EXTERN(void, dlinkPush, (DLinkNode *node, DLinkList *list));
/*  DLinkNode *node;
 *  DLinkList *list;
 *
 * Pushes `node' onto the front of `list'.
 * If `node' is on another list when `dlink_push' is called, well,
 * the other list is trashed.  So don't do that.
 */

EXTERN(void, dlinkAppend, (DLinkList *list, DLinkNode *node));
/*  DLinkList *list;
 *  DLinkNode *node;
 *
 * Appends `node' to the end of `list'.
 * If `node' is on another list when `dlink_append' is called,
 * the other list is trashed.  So don't do that.
 */

EXTERN(void, dlinkInsertAfter, (DLinkNode *afternode, DLinkNode *node));
/*  DLinkNode *afternode;
 *  DLinkNode *node;
 *
 * Insert `node' into the list that `afternode' is on,
 * immediately after `afternode' in the list.
 * Preconditions:
 *  `afternode' should be on a list
 *  `node' should not be on any list
 */


EXTERN(void, dlinkInsertBefore, (DLinkNode *node, DLinkNode *beforenode));
/*  DLinkNode *node;
 *  DLinkNode *beforenode;
 *
 * Insert `node' into the list that `beforenode' is on,
 * immediately before `beforenode' in the list.
 * Preconditions:
 *  `beforenode' should be on a list
 *  `node' should not be on any list
 */

EXTERN(void, dlinkJoin, (DLinkList *res, DLinkList *first, DLinkList *second));
/*  DLinkList *res;
 *  DLinkList *first;
 *  DLinkList *second;
 *
 * Join two lists `first' and `second' end-to-end,
 * placing the result in `res'.
 * Preconditions:
 *  `res' need not be distinct from `first' or `second'
 * Postconditions:
 *  old contents, if any, of `res' are lost (not freed)
 *  `first' and `second' contain trash.  They should be
 *  re-initialized before any reuse.
 */

EXTERN(void, dlinkRemove, (DLinkNode *to_pluck));
/*  DLinkNode *to_pluck;
 *
 * Remove `to_pluck' from the list it is on.
 */

EXTERN(bool, dlinkListEmpty, (DLinkList *list));
/*  DLinkList *list;
 *
 * Returns true iff `list' is an empty list.
 */

EXTERN(DLinkNode *, dlinkPop, (DLinkList *list));
/*  DLinkList *list;
 *
 * Removes the first node from `list', and returns the popped node.
 * Returns NULLNODE if `list' is empty.
 */


EXTERN(void, dlinkListFree, (DLinkList *list));
/*  DLinkList *list;
 *
 * Frees list.
 */

EXTERN(void, dlinkFreeNode, (DLinkNode *node));
/*  DLinkNode *node;
 *
 * Frees node.
 */

EXTERN(void, dlinkFreeNodeAndAtom, (DLinkNode *node));
/*  DLinkNode *node;
 *
 * Frees node and the atom field of the node.  `atom' is treated like
 * a pointer to a block of dynamic storage.
 */


EXTERN(void, dlinkFreeNodes, (DLinkList *list));
/*  DLinkList *list;
 *
 * `dlinkFreeNode' is called for every node in `list'.
 */

EXTERN(void, dlinkFreeNodesAndAtoms, (DLinkList *list));
/*  DLinkList *list;
 *
 * `dlinkFreeNodeAndAtom' is called for every node in `list'.
 */

EXTERN(bool, dlinkInList, (DLinkNode *node, DLinkList *list));
/*  DLinkNode *node;
 *  DLinkList *list;
 *
 * Returns true iff `node' is in `list'.
 */


EXTERN(bool, dlinkGoodList, (DLinkList *list));
/*  DLinkList *list;
 *
 * dlinkGoodList is used to verify the "goodness" of a list.
 * All next and prev links are checked, to determine if the list is
 * fully connected in both directions, and properly terminated.
 * This routine is of interest to those who either
 * doubt the correctness of the list routines in this file,
 * suspect that they may be using these routines incorrectly,
 * or suspect that their lists are being trampled by some other routine.
 * It is, or course, a fairly expensive call.
 */

typedef FUNCTION_POINTER(int, DLinkApplyFunc, (DLinkNode *node));
EXTERN(void, dlinkApply, (DLinkList *list, DLinkApplyFunc func));
/*  DLinkList *list;
 *  dlink_apply_func func;
 *
 * Applies `func' to every node in `list'.  That is, for every node in the
 * list, `func' is called, with the node passed as an argument to `func'.
 */

typedef FUNCTION_POINTER(int, DLinkApply1Func,
 (DLinkNode *node, Generic arg1));
EXTERN(void, dlinkApply1,
 (DLinkList *list, DLinkApply1Func func, Generic arg1));
/*  DLinkList *list;
 *  dlink_apply1_func func;
 *  Generic arg1;
 *
 * Applies `func' to every node in `list', passing `arg1' as the second
 * argument to `func'.
 */

typedef FUNCTION_POINTER(int, DLinkApply2Func,
 (DLinkNode *node, Generic arg1, Generic arg2));
EXTERN(void, dlink_apply_2,
 (DLinkList *list, DLinkApply2Func func, Generic arg1, Generic arg2));
/*  DLinkList *list;
 *  dlink_apply2_func func;
 *  Generic arg1;
 *  Generic arg2;
 *
 * Applies `func' to every node in `list', passing `arg1' as the second
 * argument to `func', and `arg2' as the third.
 */

typedef FUNCTION_POINTER(DLinkNode*, DLinkMatchFunc,
 (DLinkNode *node));
EXTERN(DLinkNode *, dlinkMatch,
 (DLinkList *list, DLinkMatchFunc func));
/*  DLinkList *list;
 *  dlink_match_func func;	match function
 *
 * Apply `func' successively to each node of `list' (see `dlinkApply'),
 * until an application returns a value other than NULLNODE.  This value is
 * then returned, without applying `func' to the remaining nodes in `list'
 */

typedef FUNCTION_POINTER(DLinkNode*, DLinkMatch1Func,
 (DLinkNode *node, Generic arg1));
EXTERN(DLinkNode *, dlink_match_1,
 (DLinkList *list, DLinkMatch1Func func, Generic arg1));
/*  DLinkList *list;
 *  dlink_match1_func func;	match function
 *  Generic arg1;
 *
 * `dlinkMatch1' is `dlinkMatch' as `dlinkApply1' is to `dlinkApply'
 *
 * Apply `func' successively to each node of `list' (see `dlinkApply1'),
 * passing `arg1' as a second argument,
 * until an application returns a value other than NULLNODE.  This value is
 * then returned, without applying `func' to the remaining nodes in `list'
 */

#define NULLNODE (DLinkNode *)0
#define NULLLIST (DLinkList *)0



#endif /* DLINK_H_ */
