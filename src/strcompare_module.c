/*========================================================================================
strcompare_module.c
Pythod module definition for strcompare.
Version 2.0.0

Relevant Files
------------------
character_distribution.c
    cdist_score

longest_substring.c
    lss_major
    lss_minor
    longest_substring

fragmented_substring.c
    fss_major
    fss_minor

levenshtein.c
    levenshtein_major
    levenshtein_minor
    levenshtein_distance


========================================================================================*/
#include <Python.h>
#include <string.h>

#include "compare_functions/strcompare.h"

// #include "compare_functions/cdist_score.h"
// #include "compare_functions/fss_score.h"
// #include "compare_functions/lcs_score.h"
// #include "compare_functions/levenshtein_score.h"


/*========================================================================================
Wrap C functions into python object returning functions
========================================================================================*/

// Wrap cdist_score
static PyObject* method_cdist_score(PyObject* self, PyObject *args)
{
    char *str1, *str2;
    double score;

    if (!PyArg_ParseTuple(args, "ss", &str1, &str2))
        return NULL;
    
    score = cdist_score(str1, str2);
    return PyFloat_FromDouble(score);
}

// Wrap lss_major
static PyObject* method_lss_major(PyObject* self, PyObject* args)
{
    char* str1;
    char* str2;
    double score;

    if (!PyArg_ParseTuple(args, "ss", &str1, &str2))
        return NULL;

    score = lss_major(str1, str2);

    if (score < 0)
    {
        PyErr_SetString(PyExc_MemoryError, "Error allocating memory for lss_major.");
        return NULL;
    }

    return PyFloat_FromDouble(score);
}

// Wrap lss_minor
static PyObject* method_lss_minor(PyObject* self, PyObject* args)
{
    char* str1;
    char* str2;
    double score;

    if (!PyArg_ParseTuple(args, "ss", &str1, &str2))
        return NULL;

    score = lss_minor(str1, str2);

    if (score < 0)
    {
        PyErr_SetString(PyExc_MemoryError, "Error allocating memory for lss_minor.");
        return NULL;
    }

    return PyFloat_FromDouble(score);
}

// Wrap return value of longest_substring
static PyObject* method_substring_length(PyObject* self, PyObject* args)
{
    char* str1;
    char* str2;
    int len1;
    int len2;

    int length;

    if (!PyArg_ParseTuple(args, "ss", &str1, &str2))
        return NULL;

    len1 = strlen(str1);
    len2 = strlen(str2);

    if (len2 > len1)
        length = longest_substring(str1, str2, NULL);
    else
        length = longest_substring(str2, str1, NULL);
    
    if (length < 0)
    {
        PyErr_SetString(PyExc_MemoryError, "Error allocating memory for substring_length.");
        return NULL;
    }

    return PyLong_FromLong((long)length);
}

// Wraps longest_substring - makes use of the "substr" argument & return value to 
// use PyUnicode_FromStringAndSize
static PyObject* method_longest_substring(PyObject* self, PyObject* args)
{
    char* str1;
    char* str2;
    char* substr;
    int substrLen;
    PyObject* returnVal;

    if (!PyArg_ParseTuple(args, "ss", &str1, &str2))
        return NULL;

    substrLen = longest_substring(str1, str2, &substr);

    if (substrLen < 0)
    {
        PyErr_SetString(
            PyExc_MemoryError, "Error allocating memory for longest_substring."
        );
        return NULL;
    }

    return PyUnicode_FromStringAndSize(substr, substrLen);
}

// Wraps fss_major
static PyObject* method_fss_major(PyObject* self, PyObject* args)
{
    char* str1;
    char* str2;
    double score;

    if (!PyArg_ParseTuple(args, "ss", &str1, &str2))
        return NULL;

    score = fss_major(str1, str2);

    if (score < 0)
    {
        PyErr_SetString(PyExc_MemoryError, "Error allocating memory for fss_major.");
        return NULL;
    }

    return PyFloat_FromDouble(score);
}

// Wraps fss_minor
static PyObject* method_fss_minor(PyObject* self, PyObject* args)
{
    char* str1;
    char* str2;
    double score;

    if (!PyArg_ParseTuple(args, "ss", &str1, &str2))
        return NULL;

    score = fss_minor(str1, str2);

    if (score < 0)
    {
        PyErr_SetString(PyExc_MemoryError, "Error allocating memory for fss_minor.");
        return NULL;
    }

    return PyFloat_FromDouble(score);
}

// Wraps adjusted_fss_major
static PyObject* method_adjusted_fss_major(PyObject* self, PyObject* args)
{
    char* str1;
    char* str2;
    double score;

    if (!PyArg_ParseTuple(args, "ss", &str1, &str2))
        return NULL;

    score = adjusted_fss_major(str1, str2);
    if (score < 0)
    {
        PyErr_SetString(
            PyExc_MemoryError, "Error allocating memory for adjusted_fss_major."
        );
        return NULL;
    }

    return PyFloat_FromDouble(score);
}

// Wraps adjusted_fss_minor
static PyObject* method_adjusted_fss_minor(PyObject* self, PyObject* args)
{
    char* str1;
    char* str2;
    double score;

    if (!PyArg_ParseTuple(args, "ss", &str1, &str2))
        return NULL;

    score = adjusted_fss_minor(str1, str2);
    if (score < 0)
    {
        PyErr_SetString(
            PyExc_MemoryError, "Error allocating memory for adjusted_fss_minor."
        );
        return NULL;
    }

    return PyFloat_FromDouble(score);
}

// Wraps levenshtein_distance
static PyObject* method_levenshtein_distance(PyObject* self, PyObject* args)
{
    char* str1;
    char* str2;
    int len;

    if (!PyArg_ParseTuple(args, "ss", &str1, &str2))
        return NULL;

    len = levenshtein_distance(str1, str2);
    if (len < 0)
    {
        PyErr_SetString(PyExc_MemoryError, "Error allocating memory for levenshtein_distance.");
        return NULL;
    }

    return PyLong_FromLong((long)len);
}

// Wraps levenshtein_major
static PyObject* method_levenshtein_major(PyObject* self, PyObject* args)
{
    char* str1;
    char* str2;
    double score;

    if (!PyArg_ParseTuple(args, "ss", &str1, &str2))
        return NULL;

    score = levenshtein_major(str1, str2);

    if (score < 0)
    {
        PyErr_SetString(PyExc_MemoryError, "Error allocating memory for levnshtein_major.");
        return NULL;
    }

    return PyFloat_FromDouble(score);
}

// Wraps levenshtein_minor
static PyObject* method_levenshtein_minor(PyObject* self, PyObject* args)
{
    char* str1;
    char* str2;
    double score;

    if (!PyArg_ParseTuple(args, "ss", &str1, &str2))
        return NULL;

    score = levenshtein_minor(str1, str2);

    if (score < 0)
    {
        PyErr_SetString(PyExc_MemoryError, "Error allocating memory for levenshtein_minor.");
        return NULL;
    }

    return PyFloat_FromDouble(score);
}

/*========================================================================================
Define python functions
========================================================================================*/

static PyMethodDef strcompare_methods[] = {
    {
        "cdist_score", method_cdist_score, METH_VARARGS,
        "Character Distribution Score. Compares the character distribution between two "
        "input strings, returning a float representing the ratio of matched characters "
        "to the total number of characters between the two strings."
    },
    {
        "lss_major", method_lss_major, METH_VARARGS,
        "Longest Substring Score - Major variant. Assesses the similarity of two input "
        "strings by comparing the length of the longest substring common to both, "
        "returning a float representing the ratio of the longest substring's length to "
        "the length of the longer input string."
    },
    {
        "lss_minor", method_lss_minor, METH_VARARGS,
        "Longest Substring Score - Minor variant. Assesses the similarity of two input strings by "
        "comparing the length of the longest substring common to both, returning a float "
        "representing the ratio of the longest substring's length to the length of the "
        "shorter input string."
    },
    {
        "substring_length", method_substring_length, METH_VARARGS,
        "Substring Length. Identifies and returns the length of the longest substring "
        "common to both input strings. Returns 0 if there are no characters common to "
        "both input strings."
    },
    {
        "longest_substring", method_longest_substring, METH_VARARGS,
        "Longest Substring. Identifies and returns the longest sequence of characters "
        "appearing in the same order in both input strings. Returns an empty string if "
        "there are no matching characters between the two input strings."
    },
    {
        "fss_major", method_fss_major, METH_VARARGS,
        "Fragmented Substring Score - Major variant. Assesses the similarity of two "
        "input strings by identifying the longest sequence of characters that appear "
        "in the same relative order in both input strings, returning a float "
        "representing the ratio of the longest fragmented substring's length to the "
        "length of the longer string."
    },
    {
        "fss_minor", method_fss_minor, METH_VARARGS,
        "Fragmented Substring Score - Minor variant. Assesses the similarity of two "
        "input strings by identifying the longest sequence of characters that appear "
        "in the same relative order in both input strings, returning a float "
        "representing the ratio of the longest fragmented substring's length to the "
        "length of the shorter string."
    },
    {
        "adjusted_fss_major", method_adjusted_fss_major, METH_VARARGS,
        "Adjusted Fragmented Substring Score - Major variant. "
        "Assesses string similarity in the same manner as fss_major, but assesses "
        "a penalty for differing relative distances between matching fragmented "
        "substring characters across the two input strings. For example, "
        "strings ABZZZ and AXXXB would receive a lower adjusted score than its base "
        "fss score, as A & B are one character apart in the first string, but 4 "
        "characters apart in the second. As a major variant, the raw score is scaled "
        "against the longer string and returned as a float."
    },
    {
        "adjusted_fss_minor", method_adjusted_fss_minor, METH_VARARGS,
        "Adjusted Fragmented Substring Score - Minor variant. "
        "Assesses string similarity in the samer manner as fss_minor, but assesses "
        "a penalty for differing relative distances between matching fragmented "
        "substring characters across the two input strings. For example, "
        "strings ABZZZ and AXXXB would receive a lower adjusted score that its base "
        "fss score, as A & B are one character apart in the first string, but 4 "
        "characters apart in the second. As a minor variant, the raw score is scaled "
        "against the shorter string and returned as a float."
    },
    {
        "levenshtein_distance", method_levenshtein_distance, METH_VARARGS,
        "Levenshtein Distance. Returns the levenshtein_distance between two strings. "
        "The levenshtein distance is defined as the minimum number of single character "
        "edits required to turn one string into another. (Edits include insertions, " 
        "deletions, and substitutions.)"
    },
    {
        "levenshtein_major", method_levenshtein_major, METH_VARARGS,
        "Levenshtein Score - Major variant. "
        "Assesses similarity between two strings based on their levenshtein distance, "
        "returning a float representing the ratio of the levenshtein distance to the "
        "length of the longer string."
    },
    {
        "levenshtein_minor", method_levenshtein_minor, METH_VARARGS,
        "Levenshtein Score - Minor variant. "
        "Assesses similarity between two strings based on their levenshtein distance, "
        "returning a float representing the ratio of the levenshtein distance to the "
        "length of the shorter string."
    },
    {NULL, NULL, 0, NULL}
};


/*========================================================================================
Define python module struct
========================================================================================*/

static struct PyModuleDef strcompare_module = {
    PyModuleDef_HEAD_INIT,
    "strcompare",
    "Methods and utilities to assess string similarity",
    -1,
    strcompare_methods
};


/*========================================================================================
Define module initialization function
========================================================================================*/


PyMODINIT_FUNC PyInit_strcompare(void)
{
    return PyModule_Create(&strcompare_module);
}
