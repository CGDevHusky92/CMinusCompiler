/*
 * symtab.c
 *
 *  Created on: Jun 29, 2009
 *      Author: carr
 */
/*
 * The New Rn/ParaScope Symbol Table Utility		December 1990
 * Principal Author: Keith D. Cooper
 *
 * Copyright 1990, Rice University, as part of the Rn/ParaScope Programming
 * Environment Project.
 *
 *
 *	Although this utility was written for users of the Rn/ParaScope
 *	Abstract Syntax Tree data structure, it has general utility.
 *
 *	Implementation Notes:
 *
 *	 (1) Initial values must be remembered to make expansion work!
 *	 (2) InitField() must check for previous use.
 *
 *  Modification History:
 *
 *    May 1991                    John Mellor-Crummey
 *          Added external functions SymQueryIndex, SymDump and SymForAll.
 *          Modified SymInitField to take a cleanup function for a field and
 *          SymKill and SymKillField to use field cleanup functions.
 *          Added internal cleanup function sfree_if_nonzero to handle
 *          deallocation of field names in the symbol table.
 *          Ensured 0 initialization of field values in SymFieldIndex. Added
 *          constant FIRST_SLOT and made handling of initial symbol
 *          slot consistent.
 *
 *    June 1991                   John Mellor-Crummey
 *          Added SymMaxIndex and defined SYM_NAME_FIELD
 *
 *    July 10 1991                John Mellor-Crummey
 *          Added SymDumpEntryByIndex
 *
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#include <util/symtab.h>
#include <util/string_utils.h>

STATIC(void, OverflowIndex, (SymTable ip));
STATIC(void, OverflowVectors, (SymTable ip));
STATIC(int,  SymFieldIndex, (SymTable ip, char* field));
STATIC(int,  SymFieldFind, (SymTable ip, char* field, int* index));
STATIC(void, sfree_if_nonzero, (Generic p));

struct SymTable_internal_structure
{
  int             NumFields;   /**< number of allowable dynamic fields       */
  int             NumSlots;    /**< number of distinct symbols               */
  int             NumIndices;  /**< size of sparse hash index set            */
  int             NameField;
  int             NextSlot;    /**< next available opening                   */

  int*            Index;       /**< Sparse hash index set                    */

  Generic**       FieldVals;   /**< Field values                             */
  char**          FieldNames;  /**< Field names                              */
  SymCleanupFunc* CleanupFns;  /**< cleanup functions for field deallocation */
  Generic*        InitVals;    /**< Field initial values (for realloc)       */
};


/* In this version of the code, the number of fields allowed over the
 * life of a Symbol Table instance is fixed and small.  The defined
 * constant "FS" determines the number of fields.
 *
 * There are two rationales for this decision:
 *  (1)	the number of fields used in any prior version of the Symbol
 *	Table was less than 16.  I believe that this reflects something
 *	fundamental about the clients of the Symbol Table, rather than
 *	reflecting a simple limit of the old implementation.  I don't
 *	expect the Symbol Table to EVER exceed 128 fields.  (ha, ha, ha!)
 *
 *  (2) keeping the number relatively small makes it reasonable to iterate
 *	over all the field slots.  If FS is increased beyond 255 (or, even
 *	more problematic, made to expand automatically on overflow), then
 *	the abstraction needs a chain that links together the active fields
 *	of a Symbol Table instance to make those iterations efficient.
 *	(In particular, look at SymKill() and OverflowVectors().)
 *
 */

#define FS 255
#define FIRST_SLOT (SYM_INVALID_INDEX + 1)

/**
 *
 * Returns a pointer to a symbol table instance
 *
 * @param size the size of the symbol table
 * @return symbol table with 'size' entries
 */
SymTable SymInit(unsigned int size)
{
  register SymTable ip;
  register int power, i;

  if (size < 8)
     size = 8;

  ip = (SymTable) malloc(sizeof(struct SymTable_internal_structure));

  /* compute a size for the sparse index set */
  power = 0;
  i = 31;

  while(i > 1)
  {
    if (size & 1<<i)
    {
      if (i < 20)		/* make the index set 2 to 4 * size */
	 power = (1 << (i+2)) -1;
      else 			/* the set is too large, anyway */
	 power = (1 << i) -1;

      i = 0;			/* exit the little loop */
    }
    i--;
  }

  ip->NumFields = FS;
  ip->FieldVals  = (Generic**)malloc(FS*sizeof(Generic*));
  ip->FieldNames = (char**)malloc(FS*sizeof(char*));
  ip->CleanupFns = (SymCleanupFunc*)malloc(FS*sizeof(void*));
  ip->InitVals   = (Generic*)malloc(FS*sizeof(Generic*));

  bzero((char *)ip->FieldVals, FS*sizeof(Generic*));
  bzero((char *)ip->FieldNames, FS*sizeof(char*));
  bzero((char *)ip->CleanupFns, FS*sizeof(void*));
  bzero((char *)ip->InitVals, FS*sizeof(Generic*));

  ip->NumSlots   = size;
  ip->NextSlot   = FIRST_SLOT;      /* added JMC  14 March 1991 */

  ip->NumIndices = power;
  ip->Index =      (int*) malloc(power*sizeof(int));

  for (i=0; i<power;i++)	/* fill in the index set */
      ip->Index[i] = -1;

  SymInitField(ip,SYM_NAME_FIELD, 0, sfree_if_nonzero);
  ip->NameField = SymFieldIndex(ip, SYM_NAME_FIELD);

#ifdef DEBUG
  fprintf(stderr, "SymInit(%d): sparse index size set to %d.\n", size, power);
  fprintf(stderr, "\tFields: %d, Slots: %d, Next Slot: %d, Name Field: %d.\n",
	  ip->NumFields, ip->NumSlots, ip->NextSlot, ip->NameField);
#endif

  return ip;
}

/**
 *
 * deallocates and cleans up the instance "ip"
 *
 * @param ip a symbol table
 */
void SymKill(SymTable ip)
{
  register int i;

  if (ip->FieldVals != 0)
  {
    for(i=0;i<ip->NumFields;i++) {

       if (ip->FieldVals[i] != 0) {	/* if this field is defined */
         if ((ip->CleanupFns != 0) && (ip->CleanupFns[i] != 0)) {
           int j;
           for(j=FIRST_SLOT;j<ip->NumSlots;j++)
             (*(ip->CleanupFns[i]))(ip->FieldVals[i][j]);
         }
         free((void*)ip->FieldVals[i]);
       }
	   if (ip->FieldNames[i] != (char*) 0) /* free field name */
         sfree((char*)ip->FieldNames[i]);
	}

    free((void*)ip->FieldVals);		/* and the vector, itself */
  }

  if (ip->FieldNames != 0)
     free((void*)ip->FieldNames);

  if (ip->CleanupFns != 0)
     free((void*)ip->CleanupFns);

  if (ip->InitVals != 0)
     free((void*)ip->InitVals);

  if (ip->Index != 0)
     free((void*)ip->Index);

  free((void*)ip);

#ifdef DEBUG
  fprintf(stderr, "SymKill(%d).\n", ip);
#endif
}

/**
 *
 * returns the maximum index used for an entry in the symbol table
 *
 * @param ip a symbol table
 * @return see above
 */
int SymMaxIndex(SymTable ip)
{
	if (ip->NextSlot > 0) return ip->NextSlot - 1;
	else return 0;
}

/**
 *
 * returns an index for "name". If "name" is not in the symbol table,
 * then it is inserted in an empty slot.
 *
 * @param ip a symbol table
 * @param name a key to lookup in 'ip'
 * @return see above
 */
int SymIndex(SymTable ip, char* name)
{
  register int i, initial, found, count;
  char **Names;


  Names = (char**) ip->FieldVals[ip->NameField];

  initial = hash_string(name, ip->NumIndices);
  i       = initial;
  found   = 0;
  count   = 1;

#ifdef DEBUG
  fprintf(stderr, "SymIndex(%d,%s).\n\tinitial probe: %d", ip, name, i);

#endif

  while(ip->Index[i] != -1 && found == 0)
  {
    if (strcmp(name, Names[ip->Index[i]]) == 0)
       found = 1;

    else		/* 16 is relatively prime to a Mersenne prime! */
    {
      count++;
      i = (i + 16) % ip->NumIndices;

#ifdef DEBUG
  fprintf(stderr, "\tre-probe: %d", i);
  if ((count % 4) == 0)
     fprintf(stderr,"\n");
#endif
      if ((count > 10 &&		/* too many collisions! 	*/
           ip->NextSlot + ip->NextSlot > ip->NumIndices) || /* limit it!*/
          (i == initial))		/* or a full table		*/
      {
	 OverflowIndex(ip);
	 return SymIndex(ip,name); /* real sloppy loop exit - kdc */
      }
    }
  }
  /* two possible cases
   * 	found = 1 		---> we've got a sparse index in i
   *	ip->Index[i] == -1	---> we've got a sparse index in i and
   *				     we must initialize it
   */

#ifdef DEBUG
  fprintf(stderr, "\n\tsuccess: %d.\n", i);
#endif

  if (ip->Index[i] == -1)
  {

    ip->Index[i] = ip->NextSlot++;
    Names[ip->Index[i]] = ssave(name);
    if (ip->NextSlot == ip->NumSlots)
       OverflowVectors(ip);
  }

  return ip->Index[i];
}
/**
 *
 * returns an "index" for "name" if name in table, else SYM_INVALID_INDEX
 *
 * @param ip a symbol table
 * @param name a key to look up in the table
 * @return see above
 */
int SymQueryIndex(SymTable ip, char* name)
{
  char **Names         = (char**) ip->FieldVals[ip->NameField];
  register int initial = hash_string(name, ip->NumIndices);
  register int i       = initial;
  register int count   = 1;

#ifdef DEBUG
  fprintf(stderr, "SymQueryIndex(%d,%s).\n\tinitial probe: %d", ip, name, i);
#endif


  while(ip->Index[i] != -1) {
	/*
	 * 3 exit conditions for loop
	 * (1) name found: index returned
	 * (2) empty slot encountered => name cannot be in table
	 * (3) searched whole table and name not found
	 */

    if (strcmp(name, Names[ip->Index[i]]) == 0)
		return ip->Index[i]; /* found! */
    else {
	  count++;
	  /* 16 is relatively prime to a Mersenne prime! */
      i = (i + 16) % ip->NumIndices;

#ifdef DEBUG
  fprintf(stderr, "\tre-probe: %d", i);
  if ((count % 4) == 0)
     fprintf(stderr,"\n");
#endif
      if (i == initial)	/* searched whole table, name not found */
		return SYM_INVALID_INDEX;
      }
    }
  return SYM_INVALID_INDEX; /* empty slot encountered */
}

static int SymFieldFind(SymTable ip, char* field, int* index)
{
  register int initial, i, found;

#ifdef DEBUG
  int j;
#endif

  initial = hash_string(field, ip->NumFields);
  i       = initial;
  found   = 0;

#ifdef DEBUG
  fprintf(stderr, "SymFieldIndex(%d,%s).\n\tinitial probe: %d", ip, field, i);
  j = 1;
#endif

  while(ip->FieldNames[i] != (char*)0 && found == 0)
  {
    if (strcmp(field, ip->FieldNames[i]) == 0)
       found = 1;
    else
    {
      i = (i + 1) % ip->NumIndices;	/* 1 is always relatively prime */
#ifdef DEBUG
  fprintf(stderr, "\tre-probe: %d", i);
  j++;
  if (j==4)
  {
    fprintf(stderr,"\n");
    j = 0;
  }
#endif
      if (i == initial)
      {
	fprintf(stderr, "SymTable design problem: field hash table overflow\n");
	found = 1;
      }
    }
  }
  *index = i;
  return found;
}

/**
 *
 * Returns if the field exists in the symbol table.
 *
 * @param ip a symbol table
 * @param field a field name
 * @return see above
 */
int SymFieldExists(SymTable ip, char* field)
{
    int i = 0;

    return SymFieldFind(ip, field, &i);
}


static int SymFieldIndex(SymTable ip, char* field)
{
  int i = 0, found;

  found = SymFieldFind(ip, field, &i);

  /* two possible cases
   * 	found = 1 		---> we've got a sparse index in i
   *	ip->FieldNames[i] == 0	---> we've got a sparse index in i and
   *				     we must initialize it
   */

#ifdef DEBUG
  fprintf(stderr, "\n\tsuccess: %d.\n",i);
#endif
  if (ip->FieldNames[i] == (char*)0)
  {
    ip->FieldNames[i] = ssave(field);
    ip->FieldVals[i]= (Generic*) malloc(sizeof(Generic)*ip->NumSlots);
    bzero((char *)ip->FieldVals[i], sizeof(Generic)*ip->NumSlots); /* JMC -- initially 0 */
    ip->InitVals[i] = 0;
    ip->CleanupFns[i] = (SymCleanupFunc)0;
  }

  return i;
}

/**
 *
 *	   returns the value of "field" for "index"
 *	   where "field" is simply a textual string that names the slot in
 *	   the table.  Any valid C string will do fine here.  Consistency
 *	   is what associates values with names.
 *
 * @param ip a symbol table
 * @param index an index into the symbol table
 * @param field the name of a field in the symbol table
 * @return see above
 */
Generic SymGetFieldByIndex(SymTable ip, int index, char* field)
{
  register int i;

  i = SymFieldIndex(ip, field);

  return ip->FieldVals[i][index];
}

/**
 *
 * 	 - same function as SymGetFieldByIndex(), except that it takes
 *	   a textual name rather than the index.  It calls SymIndex()
 *	   to turn the name into an index.
 *
 * @param ip a symbol table
 * @param name a key to lookup in 'ip'
 * @param field a field in the symbol table
 * @return see above
 */
Generic SymGetField(SymTable ip, char* name, char* field)
{
  int i, index;

  index = SymIndex(ip, name);
  i     = SymFieldIndex(ip, field);

  return ip->FieldVals[i][index];
}

/**
 *
 * 	 - sets the value of the "field" for "index"  (see SymGetField())
 *
 * @param ip a symbol table
 * @param index an index into 'ip'
 * @param field a field name in the symbol table
 * @param val a field value to be stored in table
 */
void SymPutFieldByIndex(SymTable ip, int index, char* field, Generic val)
{
  register int i;

  i = SymFieldIndex(ip, field);

  ip->FieldVals[i][index] = val;
}

/**
 *
 * 	 - same function as SymPutFieldByIndex(), except that it takes
 *	   a textual name rather than an index.  It calls SymIndex()
 *	   to turn the name into an index.
 *
 * @param ip a symbol table
 * @param name a key to be looked up in 'ip'
 * @param field a field name in 'ip'
 * @param val a field valude to be stored in 'ip'
 */
void SymPutField(SymTable ip, char* name, char* field, Generic val)
{
  register int i, index;

  index = SymIndex(ip, name);
  i     = SymFieldIndex(ip, field);

  ip->FieldVals[i][index] = val;
}

/**
 *
 * 	 - allows the client to initialize "field" to "value" for every
 *	   valid "index". "cleanupfn" is a pointer to a function to be called
 *         for each symbol table entry when the field is deallocated. a value
 *         of 0 for "cleanupfn" indicates no cleanup needed.
 *     if 'field' is new, then space in the table is assigned for it
 *
 * @param ip a symbol table
 * @param field a field in the symbol table
 * @param val an initial value for the field
 * @param cleanup a function to be call when the file is deallocated
 */
void SymInitField(SymTable ip, char* field, Generic val, SymCleanupFunc cleanup)
{
  register int i,j;

  i = SymFieldIndex(ip, field);
  ip->InitVals[i] = val;
  ip->CleanupFns[i] = cleanup;

  for (j=FIRST_SLOT;j<ip->NumSlots;j++)
    ip->FieldVals[i][j] = val;

  return;
}

/**
 *
 * 	 - deallocates any storage associated with "field", losing all values
 *	   associated with "field" in any valid "index". the cleanup function
 *         (if any) specified by SymInitField is invoked on each field value.
 *
 * @param ip a symbol table
 * @param field a field in the symbol table
 */
void SymKillField(SymTable ip, char* field)
{
  register int i;

  i = SymFieldIndex(ip, field);

  if (ip->FieldVals[i] != 0) {
     if ((ip->CleanupFns != 0) && (ip->CleanupFns[i] != 0)) {
       int j;
       for(j=FIRST_SLOT;j<ip->NumSlots;j++)
         (*(ip->CleanupFns[i]))(ip->FieldVals[i][j]);
       ip->CleanupFns[i] = (SymCleanupFunc)0;
     }
     free((void*)ip->FieldVals[i]);
  }

  ip->FieldVals[i] = 0;

  if (ip->FieldNames[i] != (char*) 0)
     sfree(ip->FieldNames[i]);

  ip->FieldNames[i] = 0;

  return;
}


/* The Index table can overflow for two very different reasons:
 *
 *  (1)	it is full.  This only happens with a reasonably good distribution
 *	from the Hash function.  (Check the collision limit code in
 *	SymIndex().  If we get here with a full table, we should add
 *	a reasonable increment -- after all, the Index table is designed
 *	to be a sparse table.  (See the code in SymInit() that picks the
 *	Index set size as a function of the number of requested slots.)
 *
 *  (2) we're getting bad behavior from the hash function and the table
 *	is moderately full.  (The combination of a table that is over
 *	50% full and an insertion that has more than ten probes triggers
 *	an overflow.)  In this case, we'd like to change the distribution.
 *	Typically, two factors make a difference here: the density of
 *	entries in the Index table and numerical properties involving
 *	the MOD oepration in the hash function.
 *
 * So, after much discussion and some limited experimentation, we chose
 * the following scheme.  The Index set size is enlarged by roughly the
 * number of symbols already entered (ip->NextSlot).
 *
 * I say "roughly", because we first mask off the low order bit to ensure
 * that the increment is even.  This keeps the rehash quotient relatively
 * prime to the size of the Index table.  It also ensures that the MOD
 * operation in the hash function is taken relative to an odd number.
 * This keeps it from being a simple masking off of some high order bits.
 * (We hope that this changes the distribution radically in pathological
 * cases.  Our thinking is that too many collisions should trigger a
 * resize on the Index set.  In turn, that should change the distribution
 * enough to get us out of the collisions.
 *
 * Linda Torczon suggested the rehash limit.  The decisions about
 * incremental size increases for both Index and Vector sets were the
 * result of a lengthy discussion.  We hope that this scheme avoids
 * most pathology and provides reasonable behavior.
 *
 *
 */
static void OverflowIndex(SymTable ip)
{
  register int i, initial, j, size;
  char **Names;

  if (ip->NumIndices < 4096)
     size = ip->NumIndices + 1024;   /* Small table => big increment	    */
  else
  {				     /* Big table => more careful choice    */
    size = ip->NextSlot & 0xFFFFFFFE;/* mask off last bit to make it even.  */
    size += ip->NumIndices;	     /* Add number of entries to index set. */
  }				     /* This moderates growth in case of    */
 				     /* pathology.  Test in SymIndex() cuts */
  if (ip->Index != 0)		     /* out when Index is less than 50% full*/
     free((void*)ip->Index);

  ip->Index = (int*) malloc(sizeof(int**)*size);

  for (i=0;i<size;i++)
      ip->Index[i] = -1;

  Names = (char**) ip->FieldVals[ip->NameField];

  for (i=FIRST_SLOT;i<ip->NextSlot;i++)
  {
    initial = hash_string(Names[i], size);
    j       = initial;

    while(ip->Index[j] != -1)
    {
      j = (j + 16) % size;
      if (j == initial)
      {
	fprintf(stderr, "SymTable: failure in OverflowIndices\n.");
	ip->Index[j] = -1; 	/* get out of here, it can't work anyway! */
      }
    }
    ip->Index[j] = i;
  }

#ifdef DEBUG
  fprintf(stderr, "\n\nOverflowIndex(%d): Old Size: %d, New Size: %d.\n",
	  ip, ip->NumIndices, size);
#endif

  ip->NumIndices = size;
}


static void OverflowVectors(SymTable ip)
{
  register int   i, j, NewSlots, NewSize, OldSize ;
  Generic Val;
  register Generic *p;


  if (ip->NumSlots < 4096)
     NewSlots = ip->NumSlots + 512;
  else if (ip->NumSlots < 16384)
     NewSlots = ip->NumSlots + 2048;
  else
     NewSlots = (int) (1.33 * (float) ip->NumSlots) ;

  NewSize  = NewSlots * sizeof(Generic);
  OldSize  = ip->NumSlots * sizeof(Generic);

  for (i=0;i<ip->NumFields;i++)
  {
    if (ip->FieldVals[i] != (Generic*) 0)
    {
      p = (Generic*) malloc(NewSize);
      bcopy((const char *)ip->FieldVals[i], (char *)p, OldSize);	/* copy the old values	*/

      Val = ip->InitVals[i];			/* initialize the rest	*/
      for (j=ip->NumSlots;j<NewSlots;j++)
          p[j] = Val;

      free((void*)ip->FieldVals[i]);		/* and replace it	*/
      ip->FieldVals[i] = p;
    }
  }

#ifdef DEBUG
  fprintf(stderr, "\n\nOverflowVectors(%d): Old Slots: %d, New Slots: %d.\n",
	  ip, ip->NumSlots, NewSlots);
#endif

  ip->NumSlots = NewSlots;
}

/**
 *
 * 	 - calls func(ip,index,extra_arg) with the index of each valid symbol in
 *         the table
 *
 * @param ip a symbol table
 * @param funct a function to be called on all entries in the symbol table
 * @param extra_arg an argument to be passed to 'funct'
 */
void SymForAll(SymTable ip, SymIteratorFunc funct, Generic extra_arg)
{
  register int i;

#ifdef DEBUG
  fprintf(stderr, "SymForAll(%d, %x, %x).\n", ip, funct, extra_arg);
#endif

  for (i = FIRST_SLOT; i < ip->NextSlot; i++) funct(ip, i, extra_arg);
}


static void sfree_if_nonzero(Generic p)
{
  if (p) sfree((char*)p);

  return;
}


/**
 *
 *    - for the symbol with index "index", dump the names and values for
 *     all fields to stderr. field values are dumped in decimal and hex
 *
 * @param ip a symbol table
 * @param index a symbol table index
 */
void SymDumpEntryByIndex(SymTable ip, int index)
{
	register int i;

	fprintf(stderr, "Single Entry of Symbol Table (%x)\n", (unsigned int)ip);
	if (index < FIRST_SLOT || index >= ip->NextSlot) {
		fprintf(stderr, "Index %d Invalid", index);
	} else {
		fprintf(stderr, "%-10s %-12s  %-30s  %-10s  %-10s\n",
			"Index", "Name", "Field", "Dec Value", "Hex Value");

		if (ip->FieldVals[ip->NameField][index] != 0) {
			fprintf(stderr, "0x%-8x %-12s\n",
				index,(char*)ip->FieldVals[ip->NameField][index]);
			for(i=0;i<ip->NumFields;i++) {
				if (i != ip->NameField && ip->FieldVals[i] != 0)
					fprintf(stderr, "  %-8s %-12s  %-30s  %-10d  0x%-8x\n",
						"", "", ip->FieldNames[i], (int)ip->FieldVals[i][index],
						(unsigned int)ip->FieldVals[i][index]);
			}
		}
	}
}

/**
 *
 *    - for each symbol, dumps the names and values for all fields
 *     to stderr. field values are dumped in decimal and hex
 *
 * @param ip a symbol table
 */
void SymDump(SymTable ip)
{
	register int i,j;
	fprintf(stderr, "Dump of Symbol Table (%x)\n", (unsigned int)ip);
	fprintf(stderr, "%-10s %-12s  %-30s  %-10s  %-10s\n",
		"Index", "Name", "Field", "Dec Value", "Hex Value");

	for(j=FIRST_SLOT;j<ip->NumSlots;j++)
	{
		if (ip->FieldVals[ip->NameField][j] != 0) {
			fprintf(stderr, "0x%-8x %-12s\n",
				j, (char*)ip->FieldVals[ip->NameField][j]);
			for(i=0;i<ip->NumFields;i++) {
				if (i != ip->NameField && ip->FieldVals[i] != 0)
					fprintf(stderr, "  %-8s %-12s  %-30s  %-10d  0x%-8x\n",
						"", "", ip->FieldNames[i], (int)ip->FieldVals[i][j],
						(unsigned int)ip->FieldVals[i][j]);
			}
		}
	}
}
