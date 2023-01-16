/* =======================================================================================
comparison_funcs_TEST.c

Tests on helper components for comparison methods to ensure they work correctly
========================================================================================*/
#include <stdbool.h>

#include "../libs/EWENIT/EWENIT.c"
#include "../src/components/calc_groups.h"
#include "../src/components/utility_functions.h"
#include "../src/components/idx_ref.h"


/*=======================================================================================
CalcGroup
========================================================================================*/

// Test properties of CalcGroup_addNew
void test_calc_groups_ADDNEW()
{
    /* Adding New */
    CalcGroup cg = CalcGroup_init(4);

    CalcGroup_addNew(&cg, 1, 10);
    CalcGroup_addNew(&cg, 2, 20);
    CalcGroup_addNew(&cg, 3, 5);

    ASSERT_EQUAL_INT(cg.length, 3);
    ASSERT_EQUAL_INT(cg.idx2_min, 5);

    /* ADD TESTS TO CHECK ARRAY ELEMENTS */
    ASSERT_EQUAL_INT((*(cg.groups + 0)).idx1, 1);
    ASSERT_EQUAL_INT((*(cg.groups + 0)).idx2, 10);

    ASSERT_EQUAL_INT((*(cg.groups + 1)).idx1, 2);
    ASSERT_EQUAL_INT((*(cg.groups + 1)).idx2, 20);

    ASSERT_EQUAL_INT((*(cg.groups + 2)).idx1, 3);
    ASSERT_EQUAL_INT((*(cg.groups + 2)).idx2, 5);

    CalcGroup_deconstruct(&cg);
}

// Test CalcGroup_addBest when best element comes second
void test_calc_groups_ADDBEST_UPDATESECOND()
{
    /* Adding Best */
    CalcGroup cg = CalcGroup_init(4);

    // Start with two
    CalcGroup_addNew(&cg, 4, 1); // diff 6 
    CalcGroup_addNew(&cg, 3, 7); // diff 1 - UPDATE THIS 
    // Add best
    // (4, 1), (3, 7) => (4, 1), (5, 8)
    bool is_added = CalcGroup_addBest(&cg, 5, 8);
    ASSERT_TRUE(is_added);
    // Should have not added element
    ASSERT_EQUAL_INT(cg.length, 2);
    // Proper element updated
    ASSERT_EQUAL_INT((*(cg.groups + 1)).idx1, 5);
    ASSERT_EQUAL_INT((*(cg.groups + 1)).idx2, 8);

    ASSERT_EQUAL_INT(cg.offset_difference, 1);
    ASSERT_EQUAL_INT(cg.matches, 1);
    ASSERT_EQUAL_INT(cg.idx2_min, 1);

    CalcGroup_deconstruct(&cg);
}

// Test CalcGroup_addBest when best element comes first
void test_calc_groups_ADDBEST_UPDATEFIRST()
{
    // Check reversed order
    CalcGroup cg = CalcGroup_init(4);

    CalcGroup_addNew(&cg, 3, 7); // diff 1
    CalcGroup_addNew(&cg, 4, 1); // diff 6

    // (3, 7), (4, 1) => (5, 8), (4, 1)
    bool is_added = CalcGroup_addBest(&cg, 5, 8);
    ASSERT_TRUE(is_added);
    ASSERT_EQUAL_INT((*(cg.groups + 0)).idx1, 5);
    ASSERT_EQUAL_INT((*(cg.groups + 0)).idx2, 8);

    CalcGroup_deconstruct(&cg);
}

// Test CalcGroup_addBest when element to be added is invalid
void test_calc_groups_ADDBEST_INVALID()
{
    CalcGroup cg = CalcGroup_init(4);

    CalcGroup_addNew(&cg, 5, 5);
    bool is_added = CalcGroup_addBest(&cg, 6, 0);
    ASSERT_FALSE(is_added);

    ASSERT_EQUAL_INT(cg.length, 1);
    ASSERT_EQUAL_INT(cg.matches, 0);
    ASSERT_EQUAL_INT(cg.offset_difference, 0);
    ASSERT_EQUAL_INT(cg.idx2_min, 5);
    CalcGroup_deconstruct(&cg);
}

// Test replacing old idx2 element where new element is still lowest idx2
void test_calc_groups_ADDBEST_IDX2REPLACE()
{
    // Updates old idx2_min on same element
    CalcGroup cg = CalcGroup_init(4);

    CalcGroup_addNew(&cg, 1, 4);
    CalcGroup_addNew(&cg, 5, 6);
    // (1, 4), (5, 6) => (2, 5), (5, 6)
    CalcGroup_addBest(&cg, 2, 5);
    ASSERT_EQUAL_INT(cg.idx2_min, 5);
    CalcGroup_deconstruct(&cg);
}

// Test replacing old idx2 element where a previously existing element is now lowest idx2
void test_calc_groups_ADDBEST_IDX2SECONDMIN()
{
    // idx2_min updates to other element
    CalcGroup cg = CalcGroup_init(4);

    CalcGroup_addNew(&cg, 1, 4);
    CalcGroup_addNew(&cg, 5, 6);

    // (1, 4), (5, 6) => (6, 9), (5, 6)
    CalcGroup_addBest(&cg, 6, 9);
    ASSERT_EQUAL_INT(cg.idx2_min, 6);
    CalcGroup_deconstruct(&cg);
}

// Test addFirst where the first available element works
void test_calc_groups_ADDFIRST_UPDATEFIRST()
{
    CalcGroup cg = CalcGroup_init(4);

    bool is_added = CalcGroup_addFirst(&cg, 1, 1);
    // Empty - can't add
    ASSERT_FALSE(is_added);

    CalcGroup_addNew(&cg, 2, 2);
    CalcGroup_addNew(&cg, 1, 1);
    // (2, 2), (1, 1) => (3, 4), (1, 1)
    CalcGroup_addFirst(&cg, 3, 4);
    ASSERT_EQUAL_INT((*(cg.groups + 0)).idx1, 3);
    ASSERT_EQUAL_INT((*(cg.groups + 0)).idx2, 4);

    ASSERT_EQUAL_INT(cg.length, 2);
    ASSERT_EQUAL_INT(cg.matches, 1);
    ASSERT_EQUAL_INT(cg.idx2_min, 1);
    ASSERT_EQUAL_INT(cg.offset_difference, 1);

    CalcGroup_deconstruct(&cg);
}

// Test addFirst where the second available element must be used
void test_calc_groups_ADDFIRST_UPDATESECOND()
{
    CalcGroup cg = CalcGroup_init(4);

    CalcGroup_addNew(&cg, 4, 4);
    CalcGroup_addNew(&cg, 1, 1);
    // (4, 4), (1, 1) => (4, 4), (3, 3)
    CalcGroup_addFirst(&cg, 2, 3);
    ASSERT_EQUAL_INT((*(cg.groups + 1)).idx1, 2);
    ASSERT_EQUAL_INT((*(cg.groups + 1)).idx2, 3);

    ASSERT_EQUAL_INT(cg.length, 2);
    ASSERT_EQUAL_INT(cg.matches, 1);
    ASSERT_EQUAL_INT(cg.idx2_min, 3);
    ASSERT_EQUAL_INT(cg.offset_difference, 1);

    CalcGroup_deconstruct(&cg);
}

void test_calc_groups_ADDFIRST_IDX2REPLACE()
{
    CalcGroup cg = CalcGroup_init(4);

    CalcGroup_addNew(&cg, 1, 1);
    CalcGroup_addNew(&cg, 3, 3);
    // (1, 1), (3, 3) => (2, 2), (3, 3)
    CalcGroup_addFirst(&cg, 2, 2);
    ASSERT_EQUAL_INT(cg.idx2_min, 2);

    CalcGroup_deconstruct(&cg);
}

void test_calc_groups_ADDFIRST_IDX2SECONDMIN()
{
    CalcGroup cg = CalcGroup_init(4);

    CalcGroup_addNew(&cg, 1, 1);
    CalcGroup_addNew(&cg, 3, 3);
    // (1, 1), (3, 3) => (4, 4), (3, 3)
    CalcGroup_addFirst(&cg, 4, 4);

    ASSERT_EQUAL_INT(cg.idx2_min, 3);

    CalcGroup_deconstruct(&cg);
}

void test_calc_groups_RESIZE()
{
    CalcGroup cg = CalcGroup_init(1);

    // 5 elements added
    CalcGroup_addNew(&cg, 1, 1);
    CalcGroup_addNew(&cg, 2, 2);
    CalcGroup_addNew(&cg, 3, 3);
    CalcGroup_addNew(&cg, 4, 4);
    CalcGroup_addNew(&cg, 5, 5);

    ASSERT_EQUAL_INT(cg._size, 8);

    CalcGroup_deconstruct(&cg);
}


/*=======================================================================================
choose_fss_basis
========================================================================================*/
// Test choose_fss_starter
void test_choose_fss_basis()
{
    int basis_code;
    // The basis should be the longer string
    basis_code = choose_fss_basis("THIS IS A LONG STRING","SHORT");
    ASSERT_EQUAL_INT(basis_code, 0);
    basis_code = choose_fss_basis("SHORT", "NOW THIS ONE IS LONGER");
    ASSERT_EQUAL_INT(basis_code, 1);

    // Choose alphabetically if they are the same length
    basis_code = choose_fss_basis("ZYXW", "ABCD");
    ASSERT_EQUAL_INT(basis_code, 0);
    basis_code = choose_fss_basis("ABCD", "ZYXW");
    ASSERT_EQUAL_INT(basis_code, 1);

    // Test assessing multiple characters in
    basis_code = choose_fss_basis("AAAZ", "AAAA");
    ASSERT_EQUAL_INT(basis_code, 0);
    basis_code = choose_fss_basis("AAAA", "AAAZ");
    ASSERT_EQUAL_INT(basis_code, 1);

    // Test the old switcharoo
    basis_code = choose_fss_basis("ZAAA", "AZZZ");
    ASSERT_EQUAL_INT(basis_code, 0);
    basis_code = choose_fss_basis("AZZZ", "ZAAA");
    ASSERT_EQUAL_INT(basis_code, 1);

}

/*=======================================================================================
summarize_string
========================================================================================*/
void test_summarize_string()
{
    int char_counts[256] = {0};
    int* idx_ref[256] = {NULL};
    int len;

    len = summarize_string("HELLO", char_counts, idx_ref);

    // Check length
    ASSERT_EQUAL_INT(len, 5);
    // check char_counts
    ASSERT_EQUAL_INT(char_counts['H'], 1);
    ASSERT_EQUAL_INT(char_counts['E'], 1);
    ASSERT_EQUAL_INT(char_counts['L'], 2);
    ASSERT_EQUAL_INT(char_counts['O'], 1);
    // check idx_ref
    ASSERT_EQUAL_INT(*(idx_ref['H'] + 0), 0);
    ASSERT_EQUAL_INT(*(idx_ref['E'] + 0), 1);
    ASSERT_EQUAL_INT(*(idx_ref['L'] + 0), 2);
    ASSERT_EQUAL_INT(*(idx_ref['L'] + 1), 3);
    ASSERT_EQUAL_INT(*(idx_ref['O'] + 0), 4);


}

/*=======================================================================================
IdxRef
========================================================================================*/

void test_idx_ref()
{
    IdxRef ref;
    int chr_counts[256] = {0};
    int ptr_ref[256] = {0};
    IdxRef_build(&ref, "greetings", chr_counts, ptr_ref);

    // Test chr_counts
    ASSERT_EQUAL_INT(*(ref.chr_counts + 'g'), 2);
    ASSERT_EQUAL_INT(*(ref.chr_counts + 'r'), 1);
    ASSERT_EQUAL_INT(*(ref.chr_counts + 'e'), 2);
    ASSERT_EQUAL_INT(*(ref.chr_counts + 't'), 1);
    ASSERT_EQUAL_INT(*(ref.chr_counts + 'i'), 1);
    ASSERT_EQUAL_INT(*(ref.chr_counts + 'n'), 1);
    ASSERT_EQUAL_INT(*(ref.chr_counts + 's'), 1);

    // Test ptr_ref
    // G R E T I N S
    // 1 3 4 6 7 8 9
    ASSERT_EQUAL_INT(*(ref.ptr_ref + 'g'), 1);
    ASSERT_EQUAL_INT(*(ref.ptr_ref + 'r'), 3);
    ASSERT_EQUAL_INT(*(ref.ptr_ref + 'e'), 4);
    ASSERT_EQUAL_INT(*(ref.ptr_ref + 't'), 6);
    ASSERT_EQUAL_INT(*(ref.ptr_ref + 'i'), 7);
    ASSERT_EQUAL_INT(*(ref.ptr_ref + 'n'), 8);
    ASSERT_EQUAL_INT(*(ref.ptr_ref + 's'), 9);

    // Test idx_arr (index 0 invalid)
    // 0 1 2 3 4 5 6 7 8 9
    // X 0 7 1 2 3 4 5 6 8
    ASSERT_EQUAL_INT(*(ref.idx_arr + 1), 0);
    ASSERT_EQUAL_INT(*(ref.idx_arr + 2), 7);
    ASSERT_EQUAL_INT(*(ref.idx_arr + 3), 1);
    ASSERT_EQUAL_INT(*(ref.idx_arr + 4), 2);
    ASSERT_EQUAL_INT(*(ref.idx_arr + 5), 3);
    ASSERT_EQUAL_INT(*(ref.idx_arr + 6), 4);
    ASSERT_EQUAL_INT(*(ref.idx_arr + 7), 5);
    ASSERT_EQUAL_INT(*(ref.idx_arr + 8), 6);
    ASSERT_EQUAL_INT(*(ref.idx_arr + 9), 8);

    // Test front-facing get functions 
    ASSERT_EQUAL_INT(IdxRef_getChrCount(&ref, 'g'), 2);
    ASSERT_EQUAL_INT(IdxRef_getIndex(&ref, 'e', 1), 3);

    // Now test updating index
    IdxRef_updateIndex(&ref, 'e', 1, -1);
    ASSERT_EQUAL_INT(IdxRef_getIndex(&ref, 'e', 1), -1);


    IdxRef_deconstruct(&ref);
}


/*=======================================================================================
Main method
========================================================================================*/

int main()
{
    EWENIT_START;
    ADD_CASE(test_choose_fss_basis, "fss_basis");
    ADD_CASE(test_summarize_string, "summarize_string");

    ADD_CASE(test_calc_groups_ADDBEST_IDX2REPLACE, "CG addBest IDX2_REPLACE");
    ADD_CASE(test_calc_groups_ADDBEST_IDX2SECONDMIN, "CG addBest IDX2_NEWELEM");
    ADD_CASE(test_calc_groups_ADDBEST_INVALID, "CG addBest Invalid");
    ADD_CASE(test_calc_groups_ADDBEST_UPDATEFIRST, "CG addBest Update First");
    ADD_CASE(test_calc_groups_ADDBEST_UPDATESECOND, "CG addBest Update Second");
    ADD_CASE(test_calc_groups_ADDNEW, "CG Add New");
    ADD_CASE(test_calc_groups_RESIZE, "CG resize");

    ADD_CASE(test_calc_groups_ADDFIRST_IDX2REPLACE, "CG addFirst Replace idx2_min");
    ADD_CASE(test_calc_groups_ADDFIRST_IDX2SECONDMIN, "CG addFirst secondmin idx2_min");
    ADD_CASE(test_calc_groups_ADDFIRST_UPDATESECOND, "CG addFirst updates second");
    ADD_CASE(test_calc_groups_ADDFIRST_UPDATEFIRST, "CG addFirst updates first");

    ADD_CASE(test_idx_ref, "idx ref");

    EWENIT_END_COMPACT;
}