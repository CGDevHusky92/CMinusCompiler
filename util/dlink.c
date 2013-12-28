/**
 *
 * dlink.c
 *
 * A doubly linked list utility from the Rice University DSystem compiler and
 * parallel programming environment.
 *
 */

/******************************************************************************/
/*        Copyright (c) 1990, 1991, 1992, 1993, 1994 Rice University          */
/*                           All Rights Reserved                              */
/******************************************************************************/

#include <stdlib.h>
#include <util/dlink.h>

#ifndef COREDUMP
#define COREDUMP()      abort()
#endif

#ifdef notdef
#define ASSERT(bool)    {if ( !(bool) ) {COREDUMP();}}
#else
#define ASSERT(bool)	{}
#endif

/**
 * Returns a new initialized node.
 * `atom' is typically a pointer to the "owner" of the node,
 * eg. another structure containing the node.
 *
 * @param atom the data to be stored in the list node
 * @return a new list node
 */
DLinkNode *
dlinkNodeAlloc(Generic atom)
{
        return dlinkNodeInit( (DLinkNode *)malloc(sizeof(DLinkNode)), atom );
}

/**
 *
 * Returns a new initialized list.
 *
 * @param atom the data to be stored in the list node
 * @return a new list containing one node
 */
DLinkList *
dlinkListAlloc(Generic atom)
{
        return dlinkListInit( (DLinkList *)malloc(sizeof(DLinkList)), atom );
}

/**
 *
 * Initialize the fields of a node in a sensible way.
 * `atom' is typically a pointer to the "owner" of the node,
 * eg. another structure containing the node.
 * `node' is returned, for convenience.
 *
 * @param node a linked list node
 * @param atom the data to be stored in the node
 * @return the initialized node
 */
DLinkNode *
dlinkNodeInit(DLinkNode *node, Generic atom)
{
        node->up = NULLLIST;
        node->next = NULLNODE;
        node->prev = NULLNODE;
        node->atom = atom;
        return node;
}

/**
 *
 * Initialize the fields of a list in a sensible way.
 * `atom' is typically a pointer to the "owner" of the list,
 * eg. another structure containing the list.
 * `list' is returned, for convenience.
 *
 * @param list a linked list
 * @param atom a pointer typically to the "owner" of the list
 * @return a linked list
 */
DLinkList *
dlinkListInit(DLinkList *list, Generic atom)
{
        list->head = NULLNODE;
        list->tail = NULLNODE;
	list->atom = atom;

	ASSERT( dlinkGoodList(list) );
        return list;
}

/**
 *
 * Returns the head of `list'.  Returns NULLNODE if list is empty.
 *
 * @param list a linked list
 * @return the head of the list
 */
DLinkNode *
dlinkHead(DLinkList *list)
{
	ASSERT( dlinkGoodList(list) );
        return list->head;
}

/**
 *
 * Returns the tail of `list'.  Returns NULLNODE if list is empty.
 *
 * @param list a linked list
 * @return the tail of the list
 */
DLinkNode *
dlinkTail(DLinkList *list)
{
	ASSERT( dlinkGoodList(list) );
        return list->tail;
}

/**
 *
 * Returns the atom associated with `list'.
 *
 * @param list a linked list
 * @return the data stored in the list node
 */
Generic
dlinkListAtom(DLinkList *list)
{
        return list->atom;
}

/**
 *
 * Returns the atom associated with `node'.
 *
 * @param node a node on a linked list
 * @return the data associated with the list
 */
Generic
dlinkNodeAtom(DLinkNode *node)
{
        return node->atom;
}

/**
 *
 * Returns the next node in the list.  Returns NULLNODE if there is no next node.
 *
 * @param node a node on a linked list
 * @return the next node on the list
 */
DLinkNode *
dlinkNext(DLinkNode *node)
{
	return node->next;
}

/**
 *
 * Returns the previous node in the list.  Returns NULLNODE if there is no previous node.
 *
 * @param node a node on a linked list
 * @return the previous node on the linked list
 */
DLinkNode *
dlinkPrev(DLinkNode *node)
{
	return node->prev;
}

/**
 *
 * Returns the list of which `node' is a member.
 *
 * @param node a linked list node
 * @return the list on which node occurs
 */
DLinkList *
dlinkList(DLinkNode *node)
{
        return node->up;
}

/**
 *
 * Pushes `node' onto the front of `list'.
 * If `node' is on another list when `dlink_push' is called, well,
 * the other list is trashed.  So don't do that.
 *
 * @param node a linked list node
 * @param list a linked list
 */
void
dlinkPush(DLinkNode *node, DLinkList *list)
{
        /* check precondition */
	ASSERT( dlinkGoodList(list) );
        ASSERT( ! dlinkInList(node, list) );

        if ( list->tail == NULLNODE || list->head == NULLNODE )
        {
                /* consistency */
                ASSERT( list->tail == NULLNODE && list->head == NULLNODE );

                /* list was empty before */
                node->prev = NULLNODE;
                node->next = NULLNODE;
                node->up = list;

                list->tail = node;
                list->head = node;
        }
        else
        {
                node->next = list->head;
                node->prev = NULLNODE;
                node->up = list;
                list->head->prev = node;

                /* new node is head of list now */
                list->head = node;
        }
	ASSERT( dlinkGoodList(list) );
}

/**
 *
 * Appends `node' to the end of `list'.
 * If `node' is on another list when `dlink_append' is called,
 * the other list is trashed.  So don't do that.
 *
 * @param list a linked list
 * @param node a linked list node
 */
void
dlinkAppend(DLinkList *list, DLinkNode *node)
{
        /* check precondition */
	ASSERT( dlinkGoodList(list) );
        ASSERT( !dlinkInList(node, list) );

        if ( list->tail == NULLNODE || list->head == NULLNODE )
        {
                /* consistency */
                ASSERT( list->tail == NULLNODE && list->head == NULLNODE );

                /* list was empty before */
                node->next = NULLNODE;
                node->prev = NULLNODE;
                node->up = list;

                list->tail = node;
                list->head = node;
        }
        else
        {
                node->prev = list->tail;
                node->next = NULLNODE;
                node->up = list;
                list->tail->next = node;

                /* new node is tail of list now */
                list->tail = node;
        }
	ASSERT( dlinkGoodList(list) );
}

/**
 *
 * Insert `node' into the list that `afternode' is on,
 * immediately after `afternode' in the list.
 * Preconditions:
 *  `afternode' should be on a list
 *  `node' should not be on any list
 *
 * @param afternode a linked list node
 * @param node a linked list node
 */
void
dlinkInsertAfter(DLinkNode *afternode, DLinkNode *node)
{
        DLinkNode *temp;
        DLinkList *list = dlinkList(afternode);

	ASSERT( dlinkGoodList(list) );
        ASSERT( node != NULLNODE );
        ASSERT( afternode != NULLNODE );
        ASSERT( !dlinkInList(node, list) );

        temp = afternode->next;                 /* fix afternode's links */
        afternode->next = node;

        node->prev = afternode;                 /* fix node's links */
        node->next = temp;
        node->up = list;

        if (temp == NULLNODE)                   /* fix the links of the node following node now */
                list->tail = node;
        else
                node->next->prev = node;
	ASSERT( dlinkGoodList(list) );
}

/**
 *
 * Insert `node' into the list that `beforenode' is on,
 * immediately before `beforenode' in the list.
 * Preconditions:
 *  `beforenode' should be on a list
 *  `node' should not be on any list
 *
 * @param node a linked list node
 * @param beforenode a linked list node
 */
void
dlinkInsertBefore(DLinkNode *node, DLinkNode *beforenode)
{
        DLinkNode *temp;
        DLinkList *list = dlinkList(beforenode);

	ASSERT( dlinkGoodList(list) );
        ASSERT(beforenode != NULLNODE);
        ASSERT(node != NULLNODE);

        ASSERT(!dlinkInList(node, list) );

        temp = beforenode->prev;                /* fix beforenode's links */
        beforenode->prev = node;

        node->next = beforenode;                /* fix node's links */
        node->prev = temp;
        node->up = list;

        if (temp == NULLNODE)                   /* fix the links of the node preceeding node now */
                list->head = node;
        else
                node->prev->next = node;
	ASSERT( dlinkGoodList(list) );
}

/**
 * Join two lists `first' and `second' end-to-end,
 * placing the result in `res'.
 * Preconditions:
 *  `res' need not be distinct from `first' or `second'
 * Postconditions:
 *  old contents, if any, of `res' are lost (not freed)
 *  `first' and `second' contain trash.  They should be
 *  re-initialized before any reuse.
 *
 * @param res a linked list
 * @param first a linked list
 * @param second a linked list
 */
void
dlinkJoin(DLinkList *res, DLinkList *first, DLinkList *second)
{
        DLinkNode *node;

	ASSERT( dlinkGoodList(first) );
	ASSERT( dlinkGoodList(second) );

        if ( first->head != NULLNODE )
        {
                if ( second->head != NULLNODE )
                {
                        /* want this to be safe even if "res" is actually the same as "first or "second" */
                        DLinkList temp;

                        temp.head = first->head;
                        first->tail->next = second->head;
                        second->head->prev =  first->tail;
                        temp.tail = second->tail;

                        res->head = temp.head;
                        res->tail = temp.tail;
                }
                else
                {
                        res->head = second->head;
                        res->tail = second->tail;
                }
        }
        else
        {
                if ( second->head != NULLNODE )
                {
                        res->head = first->head;
                        res->tail = first->tail;
                }
                else
                {
                        res->head = NULLNODE;
                        res->tail = NULLNODE;
                }
        }

        node = res->head;
        while (node != NULLNODE)
        {
                node->up = res;
                node = node->next;
        }
	ASSERT( dlinkGoodList(res) );
}

/**
 *
 * Remove `to_pluck' from the list it is on.
 *
 * @param to_pluck a linked list node
 */
void
dlinkRemove(DLinkNode *to_pluck)
{
        DLinkList *list = dlinkList(to_pluck);

	ASSERT( dlinkGoodList(list) );
        if ( to_pluck->next == NULLNODE )
        {
                ASSERT( to_pluck == list->tail );
                if ( to_pluck->prev == NULLNODE )
                {
                        /* to_pluck is only node on list */
                        ASSERT( to_pluck == list->head );
                        list->head = NULLNODE;
                        list->tail = NULLNODE;
                }
                else
                {
                        /* to_pluck is at end of list */
                        to_pluck->prev->next = NULLNODE;
                        list->tail = to_pluck->prev;
                        list->tail->next = NULLNODE;
                }
        }
        else
        {
                if ( to_pluck->prev == NULLNODE)
                {
                        /* to_pluck is at head of list */
                        ASSERT( to_pluck == list->head );
                        list->head = to_pluck->next;
                        list->head->prev = NULLNODE;
                }
                else                            /* to_pluck is imbedded in list */
                {
                        to_pluck->prev->next = to_pluck->next;
                        to_pluck->next->prev = to_pluck->prev;
                }
        }

        to_pluck->next = NULLNODE;
        to_pluck->prev = NULLNODE;
        to_pluck->up = NULLLIST;

	ASSERT( dlinkGoodList(list) );
        return;
}

/**
 *
 * Returns true iff `list' is an empty list.
 *
 * @param list a linked list
 * @return true if the list is not empty
 */
bool
dlinkListEmpty(DLinkList *list)
{
        return (bool) (list->head == NULLNODE);
}

/**
 *
 * Removes the first node from `list', and returns the popped node.
 * Returns NULLNODE if `list' is empty.
 *
 * @param list a linked list
 * @return the list with the first node removed
 */
DLinkNode *
dlinkPop(DLinkList *list)
{
        DLinkNode *temp;

	ASSERT( dlinkGoodList(list) );

        /* bad to pop from a null or mangled list */
        if ( list->head == NULLNODE )
        {
                ASSERT( list->tail == NULLNODE );
                return NULLNODE;
        }

        temp = list->head;
        list->head = list->head->next;

        temp->next = NULLNODE;
        temp->up = NULLLIST;

        if ( list->head == NULLNODE )
        {
                ASSERT( list->tail == temp );

                list->tail = NULLNODE;
        }
        else
        {
                list->head->prev = NULLNODE;
        }

	ASSERT( dlinkGoodList(list) );
	return temp;
}

/**
 *
 * Frees node.
 *
 * @param node a linked list node
 */
void
dlinkFreeNode(DLinkNode *node)
{
        free((void*)node );
}

/**
 *
 * Frees node and the atom field of the node.  `atom' is treated like
 * a pointer to a block of dynamic storage.
 *
 * @param node a linked list node
 */
void
dlinkFreeNodeAndAtom(DLinkNode *node)
{
        free((void*)(node->atom) );
        free((void*) node );
}

/**
 *
 * `dlinkFreeNode' is called for every node in `list'.
 *
 * @param list a linked list
 */
void
dlinkFreeNodes(DLinkList *list)
{
        DLinkNode *head;

        while( (head = dlinkPop(list)) != NULLNODE )
        {
                dlinkFreeNode(head);
        }
}

/**
 *
 * `dlinkFreeNodeAndAtom' is called for every node in `list'.
 *
 * @param list a linked list
 */
void
dlinkFreeNodesAndAtoms(DLinkList *list)
{
        DLinkNode *head;

        while( (head = dlinkPop(list)) != NULLNODE )
        {
                dlinkFreeNodeAndAtom(head);
        }
}

/**
 *
 * Frees list.
 *
 * @param list a linked list
 */
void dlinkListFree(DLinkList *list)
{
	free((void*)list );
}

/**
 *  Returns true iff `node' is in `list'.
 * @param node a linked list node
 * @param list a linked list
 * @return true if the node is on the list
 */
bool
dlinkInList(DLinkNode *node, DLinkList *list)
{
        return (bool) (node->up == list);
}

/**
 *
 * dlinkGoodList is used to verify the "goodness" of a list.
 * All next and prev links are checked, to determine if the list is
 * fully connected in both directions, and properly terminated.
 * This routine is of interest to those who either
 * doubt the correctness of the list routines in this file,
 * suspect that they may be using these routines incorrectly,
 * or suspect that their lists are being trampled by some other routine.
 * It is, or course, a fairly expensive call.
 *
 * @param list a linked list
 * @return true if the list correctly structured
 */
bool
dlinkGoodList(DLinkList *list)
{
        DLinkNode *current = list->head;
        DLinkNode *last;

        if (current == NULLNODE)
        {
                if (list->tail == NULLNODE)
                        return true;
                else
                        COREDUMP();
        }

        if ( current->prev != NULLNODE )
                COREDUMP();

        last = current;
        current = current->next;

        while ( current != NULLNODE )
        {
                if ( current->prev != last )
                        COREDUMP();

                if ( last->up != list )
                        COREDUMP();

                last = current;
                current = current->next;
        }

        if ( last->up != list )
                COREDUMP();

        if ( last != list->tail )
                COREDUMP();

        return true;
}

/**
 *
 * Applies `func' to every node in `list'.  That is, for every node in the
 * list, `func' is called, with the node passed as an argument to `func'.
 *
 * @param list a linked list
 * @param func a function to be applied to every list node
 */
void
dlinkApply(DLinkList *list, DLinkApplyFunc func)
{
        DLinkNode *temp = list->head;

	ASSERT( dlinkGoodList(list) );
        while (temp != NULLNODE)
        {
                func(temp);
                temp = temp->next;
        }
}

/**
 *
 * Applies `func' to every node in `list', passing `arg1' as the second
 * argument to `func'.
 *
 * @param list a linked list
 * @param func a function to be applied to every list node
 * @param arg1 the argument to the function call
 */
void
dlinkApply1(DLinkList *list, DLinkApply1Func func, Generic arg1)
{
        DLinkNode *temp = list->head;

	ASSERT( dlinkGoodList(list) );
        while (temp != NULLNODE)
        {
                func(temp, arg1);
                temp = temp->next;
        }
}

/**
 *
 * Applies `func' to every node in `list', passing `arg1' as the second
 * argument to `func', and `arg2' as the third.
 *
 * @param list a linked list
 * @param func a function to be applied to every list node
 * @param arg1 the second argument to each 'func' call
 * @param arg2 the third argument ot each 'func' call
 */
void
dlinkApply2(DLinkList *list, DLinkApply2Func func, Generic arg1, Generic arg2)
{
        DLinkNode *temp = list->head;

	ASSERT( dlinkGoodList(list) );
        while (temp != NULLNODE)
        {
                func(temp, arg1, arg2);
                temp = temp->next;
        }
}

/**
 *
 * Apply `func' successively to each node of `list' (see `dlinkApply'),
 * until an application returns a value other than NULLNODE.  This value is
 * then returned, without applying `func' to the remaining nodes in `list'
 *
 * @param list a linked list
 * @param func a function to be call on each node
 * @return the first node on which a call to 'func' does not return NULLNODE
 */
DLinkNode *
dlinkMatch(DLinkList *list, DLinkMatchFunc func)
{
        DLinkNode *temp = list->head;
        DLinkNode *ret;

	ASSERT( dlinkGoodList(list) );
        while (temp != NULLNODE)
        {
                ret = func(temp);
                if (ret)
                        return ret;
                temp = temp->next;
        }
        return NULLNODE;
}

/**
 *
 * `dlinkMatch1' is `dlinkMatch' as `dlinkApply1' is to `dlinkApply'
 *
 * Apply `func' successively to each node of `list' (see `dlinkApply1'),
 * passing `arg1' as a second argument,
 * until an application returns a value other than NULLNODE.  This value is
 * then returned, without applying `func' to the remaining nodes in `list'
 *
 * @param list a linked list
 * @param func a function to be called on each list node
 * @param arg1 the argument to the function
 * @return the first node on which a call to 'func' does not return NULLNODE
 */
DLinkNode *
dlinkMatch1(DLinkList *list, DLinkMatch1Func func, Generic arg1)
{
        DLinkNode *temp = list->head;
        DLinkNode *ret;

	ASSERT( dlinkGoodList(list) );
        while (temp != NULLNODE)
        {
                ret = func(temp, arg1);
                if (ret)
                        return ret;
                temp = temp->next;
        }
        return NULLNODE;
}



