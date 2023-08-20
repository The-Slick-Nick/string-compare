/*=======================================================================================
IdxRef.h

Framework for tracking the indices (by character) for characters in a given model string

Basic struct consists of three parts:
    1. chr_counts
        A 0-255 indexed array representing the number of instances per character
        in a modeled string. (index corresponds to chr code of a character, i.e. 'A' - 65)
    2. ptr_ref
        A 0-255 indexed arry reprsenting pointer-offsets where a particular character
        is referenced in idx_arr (3.). Value corresponding to character represents
        where to look in idx_arr to find what indices a character appears at in the
        modeled string. Defaults to 0, indicating an invalid reference.
    3. idx_arr
        An array of all indices from modeled string for each character. One contiguous
        block, identified by referencing ptr_ref. Note that space allocated is one
        greater than string, as index 0 is "blocked off" as invalid.

Example:
string 'lava' results in the following (non-represented characters excluded, will be 0)
l a v a
0 1 2 3 
chr_counts              ptr_ref             idx_arr
    IDX         VAL     IDX         VAL     IDX     VAL
     97 ('a')   2        97 ('a')    2      0       N/A
    108 ('l')   1       108 ('l')    1      1       0       (l, FIRST IDX)       
    118 ('v')   1       118 ('v')    4      2       1       (a, FIRST IDX)
                                            3       3       (a, SECOND_IDX)    
                                            4       2       (v, FIRST_IDX)      
========================================================================================*/

#ifndef INCLUDE_GUARD_IDXREF
#define INCLUDE_GUARD_IDXREF
#include <stdbool.h>

/*=======================================================================================
Structure Definition
========================================================================================*/

typedef struct {
    int* chr_counts;        // Array of counts per character
    int* ptr_ref;           // Array of pointer offsets per character to look into idx_arr
    int* idx_arr;           // Array of all indices found for a provided string
    bool active;            // Flag indicating if IdxRef is ready for use.
} IdxRef;


/*=======================================================================================
Public methods
========================================================================================*/

/// @brief Builds an existing IdxRef struct based on a basis string.
/// It is the responsibility of the caller to ensure IdxRef_deconstruct is called
/// for every IdxRef that is built.
/// @param self Pointer to existing, uninitialized IdxRef struct.
/// @param str Basis string to build from.
/// @param chr_counts 256-sized integer array, already initialzied to 0s
/// @param ptr_ref 256-sized integer array, already initialized to 0s
/// @return Boolean flag indicating if build was successful. If false, memory allocation
/// failed and IdxRef did not build successfully.
bool IdxRef_build(IdxRef* self, const char* str, int* chr_counts, int* ptr_ref);

// Retrieve ith index for a given character from idx_ref 

/// @brief Get the index of the desired instance number of the provided character.
/// If not enough instances of provided character exist, return -1.
/// For example, for basis string FOLLOW, calling IdxRef_getIndex()
/// @param self Pointer to initialized IdxRef struct.
/// @param chr Character to look for.
/// @param chr_num Instance number of said character to return an index for.
/// @return Integer index that this instance of this character appears in basis string.
int IdxRef_getIndex(IdxRef* self, unsigned char chr, int chr_num);


/// @brief Get the number of instances that the provided character appears in the basis
/// string.
/// @param self Pointer to initialized IdxRef struct. 
/// @param chr Character whose count to return.
/// @return Integer representing the number of times this character appears in basis
/// string.
int IdxRef_getChrCount(IdxRef* self, unsigned char chr);

/// @brief Decomissions an IdxRef struct. Frees internally allocated memory. Must be 
/// called on any IdxRef that has been provided to IdxRef_build
/// @param self Pointer to IdxRef struct to deconstruct.
void IdxRef_deconstruct(IdxRef* self);


#endif