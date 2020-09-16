#include <stdio.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdarg.h>

#include "CuTest.h"
#include "dictionary.h"

/* We need to directly insert the .c file in order to test the */
/* static functions as well */
#include "iniparser.c"

#define GOOD_INI_PATH "ressources/good_ini"
#define BAD_INI_PATH "ressources/bad_ini"


/* Tool function to create and populate a generic non-empty dictionary */
static dictionary * generate_dictionary(unsigned sections, unsigned entries_per_section)
{
    unsigned i, j ;
    dictionary * dic;
    char sec_name[32];
    char key_name[64];
    char key_value[32];

    dic = dictionary_new(sections + sections * entries_per_section);
    if (dic == NULL)
        return NULL;

    /* Insert the sections */
    for (i = 0; i < sections; ++i) {
        sprintf(sec_name, "sec%d", i);
        dictionary_set(dic, sec_name, "");
        for (j = 0; j < entries_per_section; ++j) {
            /* Populate the section with the entries */
            sprintf(key_name, "%s:key%d", sec_name, j);
            sprintf(key_value, "value-%d/%d", i, j);
            dictionary_set(dic, key_name, key_value);
        }
    }

    return dic;
}

void Test_iniparser_strlwc(CuTest *tc)
{
    char out_buffer[128];

    /* NULL ptr as input */
    CuAssertPtrEquals(tc, NULL, strlwc(NULL, NULL, 0));
    CuAssertPtrEquals(tc, NULL, strlwc(NULL, out_buffer, sizeof (out_buffer)));
    CuAssertPtrEquals(tc, NULL, strlwc("", NULL, sizeof (out_buffer)));
    CuAssertPtrEquals(tc, NULL, strlwc("", out_buffer, 0));
    CuAssertPtrEquals(tc, NULL, strlwc(NULL, NULL, 0));

    /* empty string */
    CuAssertStrEquals(tc, "", strlwc("", out_buffer, sizeof (out_buffer)));

    CuAssertStrEquals(tc, "  ", strlwc("  ", out_buffer, sizeof (out_buffer)));
    CuAssertStrEquals(tc, "test", strlwc("test", out_buffer, sizeof (out_buffer)));
    CuAssertStrEquals(tc, "test", strlwc("TEST", out_buffer, sizeof (out_buffer)));
    CuAssertStrEquals(tc, "test", strlwc("TeSt", out_buffer, sizeof (out_buffer)));
    CuAssertStrEquals(tc, "test test",
                      strlwc("TEST TEST", out_buffer, sizeof (out_buffer)));
    CuAssertStrEquals(tc, "very long string !!!!!!!",
                      strlwc("very long string !!!!!!!", out_buffer, sizeof (out_buffer)));
    CuAssertStrEquals(tc, "cutted string", strlwc("cutted string<---here", out_buffer, 14));

    /* test using same buffer as input and output */
    strcpy(out_buffer, "OVERWRITE ME !");
    CuAssertPtrNotNull(tc, strlwc(out_buffer, out_buffer, sizeof(out_buffer)));
    CuAssertStrEquals(tc, "overwrite me !", out_buffer);
}

void Test_iniparser_strstrip(CuTest *tc)
{
    /* First element in the array is the expected stripping result */
    const char *strings_empty[] = {
        "",
        "       ",
        "\n\n\n\n",
        "\t\t\t\t",
        "\n     \t\n\t\n    "
    };
    const char *strings_test[] = {
        "test",
        "test ",
        "test          ",
        " test",
        "   test    ",
        "\ttest\t",
        "\ttest\n"

    };
    const char *test_with_spaces = "I am a test with\tspaces.";
    char stripped[ASCIILINESZ+1];
    char error_msg[1060];
    unsigned i;

    /* NULL ptr as input */
    strstrip(NULL);

    /* empty string */
    for (i = 0 ; i < sizeof (strings_empty) / sizeof (char *) ; ++i) {
        strcpy(stripped, strings_empty[i]);
        strstrip(stripped);
        sprintf(error_msg, "Bad stripping : strstrip(\"%s\") ==> \"%s\"",
            strings_empty[i], stripped);
        CuAssertStrEquals_Msg(tc, error_msg, stripped, strings_empty[0]);
    }

    /* test string */
    for (i = 0 ; i < sizeof (strings_test) / sizeof (char *) ; ++i) {
        strcpy(stripped, strings_test[i]);
        strstrip(stripped);
        sprintf(error_msg, "Bad stripping : strstrip(\"%s\") ==> \"%s\"",
            strings_test[i], stripped);
        CuAssertStrEquals_Msg(tc, error_msg, strings_test[0], stripped);
    }
    strcpy(stripped, ".");
    strstrip(stripped);
    CuAssertStrEquals(tc, ".", stripped);

    /* string containing spaces */
    strcpy(stripped, test_with_spaces);
    strstrip(stripped);
    CuAssertStrEquals(tc, test_with_spaces, stripped);
}

void Test_iniparser_getnsec(CuTest *tc)
{
    int i;
    char sec_name[32];
    dictionary *dic;

    /* NULL test */
    CuAssertIntEquals(tc, -1, iniparser_getnsec(NULL));

    /* Empty dictionary */
    dic = dictionary_new(10);
    CuAssertIntEquals(tc, 0, iniparser_getnsec(dic));
    dictionary_del(dic);

    /* Regular dictionary */
    dic = generate_dictionary(512, 0);
    CuAssertIntEquals(tc, 512, iniparser_getnsec(dic));

    /* Check after removing sections */
    for (i = 1; i < 512; ++i) {
        sprintf(sec_name, "sec%d", i);
        dictionary_unset(dic, sec_name);
        CuAssertIntEquals(tc, 512 - i, iniparser_getnsec(dic));
    }
    dictionary_del(dic);

    /* Mix sections and regular keys */
    dic = generate_dictionary(10, 512);
    CuAssertIntEquals(tc, 10, iniparser_getnsec(dic));
    dictionary_del(dic);
}

void Test_iniparser_getsecname(CuTest *tc)
{
    unsigned i;
    char sec_name[32];
    dictionary *dic;
    /* NULL test */
    CuAssertTrue(tc, iniparser_getsecname(NULL, 0) == NULL);

    /* Empty dictionary */
    dic = dictionary_new(10);
    CuAssertPtrEquals(tc, NULL, iniparser_getsecname(dic, 0));
    dictionary_del(dic);

    /* Sections without entries dictionary */
    dic = generate_dictionary(100, 0);
    for (i = 0; i < 100; ++i) {
        sprintf(sec_name, "sec%d", i);
        CuAssertStrEquals(tc, sec_name, iniparser_getsecname(dic, i));
    }
    dictionary_del(dic);

    /* Generic dictionary */
    dic = generate_dictionary(10, 100);
    for (i = 0; i < 10; ++i) {
        sprintf(sec_name, "sec%d", i);
        CuAssertStrEquals(tc, sec_name, iniparser_getsecname(dic, i));
    }
    dictionary_del(dic);
}

void Test_iniparser_getseckeys(CuTest *tc)
{
    unsigned i;
    char key_name[64];
    dictionary *dic;
    int nkeys;
    const char * keys[10]; /* At most 10 elements per section */
    /* NULL test */
    CuAssertPtrEquals(tc, NULL, iniparser_getseckeys(NULL, NULL, NULL));
    CuAssertPtrEquals(tc, NULL, iniparser_getseckeys(NULL, "dummy", NULL));
    CuAssertPtrEquals(tc, NULL, iniparser_getseckeys(NULL, "dummy", keys));

    /* Empty dictionary */
    dic = dictionary_new(10);
    CuAssertPtrEquals(tc, NULL, iniparser_getseckeys(dic, NULL, keys));
    CuAssertPtrEquals(tc, NULL, iniparser_getseckeys(dic, "dummy", keys));
    dictionary_del(dic);

    /* Generic dictionary */

    dic = generate_dictionary(100, 10);
    CuAssertPtrEquals(tc, NULL, iniparser_getseckeys(dic, NULL, keys));
    CuAssertPtrEquals(tc, NULL, iniparser_getseckeys(dic, "dummy", keys));
    CuAssertPtrEquals(tc, NULL, iniparser_getseckeys(dic, "sec0", NULL));
    nkeys = iniparser_getsecnkeys(dic, "sec42");
    CuAssertIntEquals(tc, nkeys, 10);
    CuAssertPtrEquals(tc, keys, iniparser_getseckeys(dic, "sec42", keys));
    for (i = 0; i < 10; ++i) {
        sprintf(key_name, "sec42:key%d", i);
        CuAssertStrEquals(tc, key_name, keys[i]);
    }

    /* Remove some keys to make the dictionary more real */
    dictionary_unset(dic, "sec42");
    dictionary_unset(dic, "sec99:key9");
    dictionary_unset(dic, "sec0:key0");
    dictionary_unset(dic, "sec0:key1");
    dictionary_unset(dic, "sec0:key2");

    CuAssertPtrEquals(tc, NULL, iniparser_getseckeys(dic, "sec42", keys));
    nkeys = iniparser_getsecnkeys(dic, "Sec99");
    CuAssertIntEquals(tc, nkeys, 9);
    CuAssertPtrEquals(tc, keys, iniparser_getseckeys(dic, "Sec99", keys));
    for (i = 0; i < 9; ++i) {
        sprintf(key_name, "sec99:key%d", i);
        CuAssertStrEquals(tc, key_name, keys[i]);
    }

    nkeys = iniparser_getsecnkeys(dic, "sec0");
    CuAssertIntEquals(tc, nkeys, 7);
    CuAssertPtrEquals(tc, keys, iniparser_getseckeys(dic, "sec0", keys));
    for (i = 0; i < 7; ++i) {
        sprintf(key_name, "sec0:key%d", i + 3);
        CuAssertStrEquals(tc, key_name, keys[i]);
    }

    dictionary_del(dic);
}

void Test_iniparser_getstring(CuTest *tc)
{
    dictionary *dic;
    /* NULL test */
    CuAssertPtrEquals(tc, NULL, iniparser_getstring(NULL, NULL, NULL));
    CuAssertPtrEquals(tc, NULL, iniparser_getstring(NULL, "dummy", NULL));

    /* Check the def return element */
    dic = dictionary_new(10);
    CuAssertPtrEquals(tc, NULL, iniparser_getstring(dic, "dummy", NULL));
    CuAssertStrEquals(tc, "def", iniparser_getstring(dic, NULL, "def"));
    CuAssertStrEquals(tc, "def", iniparser_getstring(dic, "dummy", "def"));
    dictionary_del(dic);

    /* Generic dictionary */
    dic = generate_dictionary(100, 10);
    CuAssertStrEquals(tc, "value-0/0",
                      iniparser_getstring(dic, "sec0:key0", NULL));
    CuAssertStrEquals(tc, "value-42/5",
                      iniparser_getstring(dic, "sec42:key5", NULL));
    CuAssertStrEquals(tc, "value-99/9",
                      iniparser_getstring(dic, "sec99:key9", NULL));
    dictionary_del(dic);
}

void Test_iniparser_getint(CuTest *tc)
{
    unsigned i;
    char key_name[64];
    dictionary *dic;
    const struct { int num; const char *value; } good_val[] = {
        { 0, "0" },
        { 1, "1" },
        { -1, "-1" },
        { 1000, "1000" },
        { 077, "077" },
        { -01000, "-01000" },
        { 0xFFFF, "0xFFFF" },
        { -0xFFFF, "-0xFFFF" },
        { 0x4242, "0x4242" },
        { 0, NULL} /* must be last */
    };
    const char *bad_val[] = {
        "",
        "notanumber",
        "0x",
        "k2000",
        " ",
        "0xG1"
    };
    /* NULL test */
    CuAssertIntEquals(tc, -42, iniparser_getint(NULL, NULL, -42));
    CuAssertIntEquals(tc, -42, iniparser_getint(NULL, "dummy", -42));

    /* Check the def return element */
    dic = dictionary_new(10);
    CuAssertIntEquals(tc, 42, iniparser_getint(dic, "dummy", 42));
    CuAssertIntEquals(tc, 0xFFFF, iniparser_getint(dic, NULL, 0xFFFF));
    CuAssertIntEquals(tc, -0xFFFF, iniparser_getint(dic, "dummy", -0xFFFF));
    dictionary_del(dic);

    /* Generic dictionary */
    dic = dictionary_new(10);
    for (i = 0; good_val[i].value != NULL; ++i) {
        sprintf(key_name, "int:value%d", i);
        dictionary_set(dic, key_name, good_val[i].value);
    }
    for (i = 0; good_val[i].value != NULL; ++i) {
        sprintf(key_name, "int:value%d", i);
        CuAssertIntEquals(tc, good_val[i].num,
                          iniparser_getint(dic, key_name, 0));
    }
    dictionary_del(dic);

    /* Test bad names */
    dic = dictionary_new(10);
    for (i = 0; i < sizeof (bad_val) / sizeof (char *); ++i) {
        sprintf(key_name, "int:bad%d", i);
        dictionary_set(dic, key_name, bad_val[i]);
    }
    for (i = 0; i < sizeof (bad_val) / sizeof (char *); ++i) {
        sprintf(key_name, "int:bad%d", i);
        CuAssertIntEquals(tc, 0,
                          iniparser_getint(dic, key_name, 0));
    }
    dictionary_del(dic);
}

void Test_iniparser_getlongint(CuTest *tc)
{
    unsigned i;
    char key_name[64];
    dictionary *dic;
    const struct { long int num; const char *value; } good_val[] = {
        { 0, "0" },
        { 1, "1" },
        { -1, "-1" },
        { 1000, "1000" },
        { 077, "077" },
        { -01000, "-01000" },
        { 0x7FFFFFFFFFFFFFFF, "0x7FFFFFFFFFFFFFFF" },
        { -0x7FFFFFFFFFFFFFFF, "-0x7FFFFFFFFFFFFFFF" },
        { 0x4242, "0x4242" },
        { 0, NULL} /* must be last */
    };
    const char *bad_val[] = {
        "",
        "notanumber",
        "0x",
        "k2000",
        " ",
        "0xG1"
    };
    /* NULL test */
    CuAssertLongIntEquals(tc, -42, iniparser_getlongint(NULL, NULL, -42));
    CuAssertLongIntEquals(tc, -42, iniparser_getlongint(NULL, "dummy", -42));

    /* Check the def return element */
    dic = dictionary_new(10);
    CuAssertLongIntEquals(tc, 42, iniparser_getlongint(dic, "dummy", 42));
    CuAssertLongIntEquals(tc, 0x7FFFFFFFFFFFFFFF, iniparser_getlongint(dic, NULL, 0x7FFFFFFFFFFFFFFF));
    CuAssertLongIntEquals(tc, -0x7FFFFFFFFFFFFFFF, iniparser_getlongint(dic, "dummy", -0x7FFFFFFFFFFFFFFF));
    dictionary_del(dic);

    /* Generic dictionary */
    dic = dictionary_new(10);
    for (i = 0; good_val[i].value != NULL; ++i) {
        sprintf(key_name, "longint:value%d", i);
        dictionary_set(dic, key_name, good_val[i].value);
    }
    for (i = 0; good_val[i].value != NULL; ++i) {
        sprintf(key_name, "longint:value%d", i);
        CuAssertLongIntEquals(tc, good_val[i].num,
                          iniparser_getlongint(dic, key_name, 0));
    }
    dictionary_del(dic);

    /* Test bad names */
    dic = dictionary_new(10);
    for (i = 0; i < sizeof (bad_val) / sizeof (char *); ++i) {
        sprintf(key_name, "longint:bad%d", i);
        dictionary_set(dic, key_name, bad_val[i]);
    }
    for (i = 0; i < sizeof (bad_val) / sizeof (char *); ++i) {
        sprintf(key_name, "longint:bad%d", i);
        CuAssertLongIntEquals(tc, 0,
                          iniparser_getlongint(dic, key_name, 0));
    }
    dictionary_del(dic);
}

void Test_iniparser_getdouble(CuTest *tc)
{
    dictionary *dic;

    /* NULL test */
    CuAssertDblEquals(tc, -42, iniparser_getdouble(NULL, NULL, -42), 0);
    CuAssertDblEquals(tc, 4.2, iniparser_getdouble(NULL, "dummy", 4.2), 0);

    /* Check the def return element */
    dic = dictionary_new(10);
    CuAssertDblEquals(tc, 3.1415, iniparser_getdouble(dic, "dummy", 3.1415), 0);
    CuAssertDblEquals(tc, 0xFFFFFFFF, iniparser_getdouble(dic, NULL, 0xFFFFFFFF), 0);
    CuAssertDblEquals(tc, -0xFFFFFFFF, iniparser_getdouble(dic, "dummy", -0xFFFFFFFF), 0);

    /* Insert some values */
    dictionary_set(dic, "double", "");
    dictionary_set(dic, "double:good0", "0");
    dictionary_set(dic, "double:good1", "-0");
    dictionary_set(dic, "double:good2", "1.0");
    dictionary_set(dic, "double:good3", "3.1415");
    dictionary_set(dic, "double:good4", "6.6655957");
    dictionary_set(dic, "double:good5", "-123456789.123456789");

    /* Add dummy stuff too */
    dictionary_set(dic, "double:bad0", "foo");

    /* Get back the values */
    CuAssertDblEquals(tc, 0, iniparser_getdouble(dic, "double:good0", 0xFF), 0);
    CuAssertDblEquals(tc, 0, iniparser_getdouble(dic, "double:good1", 0xFF), 0);
    CuAssertDblEquals(tc, 1.0, iniparser_getdouble(dic, "double:good2", 0xFF), 0);
    CuAssertDblEquals(tc, 3.1415, iniparser_getdouble(dic, "double:good3", 0xFF), 0);
    CuAssertDblEquals(tc, 6.6655957, iniparser_getdouble(dic, "double:good4", 0xFF), 0);
    CuAssertDblEquals(tc, -123456789.123456789,
                         iniparser_getdouble(dic, "double:good5", 0xFF), 0);

    CuAssertDblEquals(tc, 0, iniparser_getdouble(dic, "double:bad0", 42.42), 0);

    dictionary_del(dic);
}

void Test_iniparser_getboolean(CuTest *tc)
{
    unsigned i;
    char key_name[64];

    dictionary *dic;
    const char *token_true[] = {
        "1",
        "true",
        "t",
        "TRUE",
        "T",
        "yes",
        "y",
        "YES"
        "Y",
        NULL
    };
    const char *token_false[] = {
        "0",
        "false",
        "f",
        "FALSE",
        "F",
        "no",
        "n",
        "NO",
        "N",
        NULL
    };

    /* NULL test */
    CuAssertIntEquals(tc, 1, iniparser_getboolean(NULL, NULL, 1));
    CuAssertIntEquals(tc, 1, iniparser_getboolean(NULL, "dummy", 1));

    /* Check the def return element */
    dic = dictionary_new(10);
    CuAssertIntEquals(tc, 1, iniparser_getboolean(dic, "dummy", 1));
    CuAssertIntEquals(tc, 0, iniparser_getboolean(dic, NULL, 0));
    CuAssertIntEquals(tc, 1, iniparser_getboolean(dic, "dummy", 1));

    for (i = 0; token_true[i] != NULL; ++i) {
        sprintf(key_name, "bool:true%d", i);
        iniparser_set(dic, key_name, token_true[i]);
    }
    for (i = 0; token_false[i] != NULL; ++i) {
        sprintf(key_name, "bool:false%d", i);
        iniparser_set(dic, key_name, token_false[i]);
    }

    for (i = 0; token_true[i] != NULL; ++i) {
        sprintf(key_name, "bool:true%d", i);
        CuAssertIntEquals(tc, 1, iniparser_getboolean(dic, key_name, 0));
    }
    for (i = 0; token_false[i] != NULL; ++i) {
        sprintf(key_name, "bool:false%d", i);
        CuAssertIntEquals(tc, 0, iniparser_getboolean(dic, key_name, 1));
    }

    /* Test bad boolean */
    iniparser_set(dic, "bool:bad0", "");
    iniparser_set(dic, "bool:bad1", "m'kay");
    iniparser_set(dic, "bool:bad2", "42");
    iniparser_set(dic, "bool:bad3", "_true");
    CuAssertIntEquals(tc, 0xFF, iniparser_getboolean(dic, "bool:bad0", 0xFF));
    CuAssertIntEquals(tc, 0xFF, iniparser_getboolean(dic, "bool:bad1", 0xFF));
    CuAssertIntEquals(tc, 0xFF, iniparser_getboolean(dic, "bool:bad2", 0xFF));
    CuAssertIntEquals(tc, 0xFF, iniparser_getboolean(dic, "bool:bad3", 0xFF));

    dictionary_del(dic);
}

void Test_iniparser_line(CuTest *tc)
{
    char section [ASCIILINESZ+1] ;
    char key     [ASCIILINESZ+1] ;
    char val     [ASCIILINESZ+1] ;

    /* Test empty line */
    CuAssertIntEquals(tc, LINE_EMPTY, iniparser_line("", section, key, val));
    CuAssertIntEquals(tc, LINE_EMPTY, iniparser_line("    ", section, key, val));
    CuAssertIntEquals(tc, LINE_EMPTY, iniparser_line("\t", section, key, val));

    /* Test valid syntax */
    CuAssertIntEquals(tc, LINE_SECTION, iniparser_line("[s]", section, key, val));
    CuAssertStrEquals(tc, "s", section);

    CuAssertIntEquals(tc, LINE_SECTION, iniparser_line("[ section ]", section, key, val));
    CuAssertStrEquals(tc, "section", section);

    CuAssertIntEquals(tc, LINE_VALUE, iniparser_line("k=1", section, key, val));
    CuAssertStrEquals(tc, "k", key);
    CuAssertStrEquals(tc, "1", val);

    CuAssertIntEquals(tc, LINE_VALUE, iniparser_line("key = 0x42", section, key, val));
    CuAssertStrEquals(tc, "key", key);
    CuAssertStrEquals(tc, "0x42", val);

    CuAssertIntEquals(tc, LINE_VALUE, iniparser_line("key= value with spaces", section, key, val));
    CuAssertStrEquals(tc, "key", key);
    CuAssertStrEquals(tc, "value with spaces", val);

    CuAssertIntEquals(tc, LINE_VALUE, iniparser_line("k =_!<>''", section, key, val));
    CuAssertStrEquals(tc, "k", key);
    CuAssertStrEquals(tc, "_!<>''", val);

    CuAssertIntEquals(tc, LINE_VALUE, iniparser_line("empty_value =", section, key, val));
    CuAssertStrEquals(tc, "empty_value", key);
    CuAssertStrEquals(tc, "", val);

    CuAssertIntEquals(tc, LINE_VALUE, iniparser_line("empty_value =        \t\n", section, key, val));
    CuAssertStrEquals(tc, "empty_value", key);
    CuAssertStrEquals(tc, "", val);

    CuAssertIntEquals(tc, LINE_VALUE, iniparser_line("key =\tval # comment", section, key, val));
    CuAssertStrEquals(tc, "key", key);
    CuAssertStrEquals(tc, "val", val);

    CuAssertIntEquals(tc, LINE_VALUE, iniparser_line("key \n\n = \n val", section, key, val));
    CuAssertStrEquals(tc, "key", key);
    CuAssertStrEquals(tc, "val", val);

    CuAssertIntEquals(tc, LINE_COMMENT, iniparser_line(";comment", section, key, val));
    CuAssertIntEquals(tc, LINE_COMMENT, iniparser_line(" # comment", section, key, val));

    CuAssertIntEquals(tc, LINE_VALUE, iniparser_line("key = \"  do_not_strip  \"", section, key, val));
    CuAssertStrEquals(tc, "key", key);
    CuAssertStrEquals(tc, "  do_not_strip  ", val);

    CuAssertIntEquals(tc, LINE_VALUE, iniparser_line("key = '    '", section, key, val));
    CuAssertStrEquals(tc, "key", key);
    CuAssertStrEquals(tc, "    ", val);

    CuAssertIntEquals(tc, LINE_VALUE, iniparser_line("key = \"\"", section, key, val));
    CuAssertStrEquals(tc, "key", key);
    CuAssertStrEquals(tc, "", val);

    CuAssertIntEquals(tc, LINE_VALUE, iniparser_line("key = ''", section, key, val));
    CuAssertStrEquals(tc, "key", key);
    CuAssertStrEquals(tc, "", val);

    /* Test syntax error */
    CuAssertIntEquals(tc, LINE_ERROR, iniparser_line("empty_value", section, key, val));
    CuAssertIntEquals(tc, LINE_ERROR, iniparser_line("not finished\\", section, key, val));
    CuAssertIntEquals(tc, LINE_ERROR, iniparser_line("0x42 / 0b101010", section, key, val));

}

void Test_iniparser_load(CuTest *tc)
{
    DIR *dir;
    struct dirent *curr;
    struct stat curr_stat;
    dictionary *dic;
    char ini_path[276];

    /* Dummy tests */
    dic = iniparser_load("/you/shall/not/path");
    CuAssertPtrEquals(tc, NULL, dic);

    /* Test all the good .ini files */
    dir = opendir(GOOD_INI_PATH);
    CuAssertPtrNotNullMsg(tc, "Cannot open good .ini conf directory", dir);
    for (curr = readdir(dir); curr != NULL; curr = readdir(dir)) {
        sprintf(ini_path, "%s/%s", GOOD_INI_PATH, curr->d_name);
        stat(ini_path, &curr_stat);
        if (S_ISREG(curr_stat.st_mode)) {
            dic = iniparser_load(ini_path);
            CuAssertPtrNotNullMsg(tc, ini_path, dic);
            dictionary_del(dic);
        }
    }
    closedir(dir);

    /* Test all the bad .ini files */
    dir = opendir(BAD_INI_PATH);
    CuAssertPtrNotNullMsg(tc, "Cannot open bad .ini conf directory", dir);
    for (curr = readdir(dir); curr != NULL; curr = readdir(dir)) {
        sprintf(ini_path, "%s/%s", BAD_INI_PATH, curr->d_name);
        stat(ini_path, &curr_stat);
        if (S_ISREG(curr_stat.st_mode)) {
            dic = iniparser_load(ini_path);
            CuAssertPtrEquals_Msg(tc, ini_path, NULL, dic);
            dictionary_del(dic);
        }
    }
    closedir(dir);
}

void Test_dictionary_wrapper(CuTest *tc)
{
    dictionary *dic;

    dic = dictionary_new(10);

    CuAssertIntEquals(tc, -1, iniparser_set(dic, NULL, NULL));
    CuAssertIntEquals(tc, -1, iniparser_set(NULL, "section", "value"));

    CuAssertIntEquals(tc, 0, iniparser_set(dic, "section", NULL));
    CuAssertIntEquals(tc, 0, iniparser_set(dic, "section:key", "value"));

    CuAssertStrEquals(tc, "value", iniparser_getstring(dic, "section:key", NULL));
    /* reset the key's value*/
    CuAssertIntEquals(tc, 0, iniparser_set(dic, "section:key", NULL));
    CuAssertStrEquals(tc, NULL, iniparser_getstring(dic, "section:key", "dummy"));
    CuAssertIntEquals(tc, 0, iniparser_set(dic, "section:key", "value"));
    CuAssertStrEquals(tc, "value", iniparser_getstring(dic, "section:key", NULL));

    iniparser_unset(dic, "section:key");
    CuAssertStrEquals(tc, "dummy", iniparser_getstring(dic, "section:key", "dummy"));
    CuAssertStrEquals(tc, NULL, iniparser_getstring(dic, "section", "dummy"));

    CuAssertIntEquals(tc, 0, iniparser_set(dic, "section:key", NULL));
    CuAssertIntEquals(tc, 0, iniparser_set(dic, "section:key1", NULL));
    CuAssertIntEquals(tc, 0, iniparser_set(dic, "section:key2", NULL));

    iniparser_unset(dic, "section");
    CuAssertStrEquals(tc, NULL, iniparser_getstring(dic, "section", NULL));

    iniparser_freedict(dic);
}

static char _last_error[1024];
static int _error_callback(const char *format, ...)
{
    int ret;
    va_list argptr;
    va_start(argptr, format);
    ret = vsprintf(_last_error, format, argptr);
    va_end(argptr);
    return ret;

}

void Test_iniparser_error_callback(CuTest *tc)
{
    dictionary *dic;

    /* Specify our custom error_callback */
    iniparser_set_error_callback(_error_callback);

    /* Trigger an error and check it was written on the right output */
    dic = iniparser_load("/path/to/nowhere.ini");
    CuAssertPtrEquals(tc, NULL, dic);
    CuAssertStrEquals(tc, "iniparser: cannot open /path/to/nowhere.ini\n", _last_error);

    /* Reset erro_callback */
    _last_error[0] = '\0';
    iniparser_set_error_callback(NULL);

    /* Make sure custom callback is no more called */
    dic = iniparser_load("/path/to/nowhere.ini");
    CuAssertPtrEquals(tc, NULL, dic);
    CuAssertStrEquals(tc, "", _last_error);
}
