/*========================================================================================
strcompare_module.c
Pythod module definition for strcompare.
Version 1.2.1

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

static PyObject* method_cdist_score(PyObject* self, PyObject *args)
{
    char *str1, *str2;
    double score;

    if (!PyArg_ParseTuple(args, "ss", &str1, &str2))
        return NULL;
    
    score = cdist_score(str1, str2);
    return PyFloat_FromDouble(score);
}

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

static PyObject* method_longest_substring(PyObject* self, PyObject* args)
{
    char* str1;
    char* str2;
    int substrLen;
    int substrIdx;
    PyObject* returnVal;

    if (!PyArg_ParseTuple(args, "ss", &str1, &str2))
        return NULL;

    substrLen = longest_substring(str1, str2, &substrIdx);

    if (substrLen < 0)
    {
        PyErr_SetString(PyExc_MemoryError, "Error allocating memory for longest_substring.");
        return NULL;
    }

    if (substrLen > 255)
    {
        char* substr = (char*)malloc((1 + substrLen) * sizeof(char));
        if (substr == NULL)
        {
            PyErr_SetString(PyExc_MemoryError, "Error allocating memory for longest_substring.");
            return NULL;
        }
        build_substring(str1, substrIdx, substrLen, substr);
        returnVal = PyUnicode_FromString(substr);
        free(substr);
        return returnVal;
    }

    char substr[256];
    build_substring(str1, substrIdx, substrLen, substr);
    return PyUnicode_FromString(substr);
}


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

static PyObject* method_fss_minor(PyObject* self, PyObject* args)
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

    return Pyfloat_FromDouble(score);
}

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

    return Pyfloat_FromDouble(score);
}

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

    return Pyfloat_FromDouble(score);
}

/*========================================================================================
Define python functions
========================================================================================*/

static PyMethodDef strcompare_methods[] = {
    {
        "cdist_score", method_cdist_score, METH_VARARGS,
        "Character Distribution Score. Compares the character distribution between two "
        "strings.",
    },
    {
        "fss_score", method_fss_score, METH_VARARGS,
        "Fractured Substring Score. Identifies sequences of characters with the same "
        "relative order bewteen two strings"
    },
    {
        "adjusted_fss_score", method_adjusted_fss_score, METH_VARARGS,
        "Adjusted Fractured Substring Score. Identifies sequences of characters with the "
        "same relative order between two strings, adjusted for differences in distances "
        "between two matching characters in the first and second."
    },
    {
        "naive_fss_score", method_naive_fss_score, METH_VARARGS,
        "Naive Fractured Substring Score. Employes a naive algorithm to identify "
        "sequences of characters with the same relative order between two strings."
    },
    {
        "adjusted_naive_fss_score", method_adjusted_naive_fss_score, METH_VARARGS,
        "Naive Adjusted Fractured Substring Score. Employes a naive algorithm to "
        "identify sequences of characters with the same relative order between two "
        "strings, while also correcting for differences in index offsets between those "
        "characters in the first and second strings."
    },
    {
        "lcs_score", method_lcs_score, METH_VARARGS,
        "Longest Common Substring Score. Assesses similarity between two strings by "
        "identifying the longest substring common to both strings."
    },
    {
        "naive_lcs_score", method_naive_lcs_score, METH_VARARGS,
        "Naive Longest Common Substring Score. Employs a naive algorithm to "
        "assess the similarity of two strings by identifying the longest substring "
        "common to both strings."
    },
    {
        "levenshtein_score", method_levenshtein_score, METH_VARARGS,
        "Levenshtein Score. Assesses the similarity between two strings by calculating "
        "the levenshtein distance between the two and returning the proportion of the "
        "difference between the maximum possible distance and the calculated distance " 
        "to the maximum possible distance."
    },
    {NULL, NULL, 0, NULL}
};


/*========================================================================================
Define python module struct
========================================================================================*/

static struct PyModuleDef strcompare_module = {
    PyModuleDef_HEAD_INIT,
    "strcompare",
    "Methods to assess string similarity",
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
