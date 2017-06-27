#include <stdio.h>
#include <string.h>

#include "eval.h"
#include <assert.h>

static void test_str(const char* expr, const char* expect) {
    EvalResult result;
    ExprValue output;
    expr_value_init(&output);

    result = eval_execute(expr, eval_default_hooks(), 0, &output);
    printf("%s %s\n", expr, eval_result_to_string(result));
    assert(result == EVAL_RESULT_OK);
    assert(output.type == EXPR_VALUE_TYPE_STRING && strcmp(output.v.str.str, expect) == 0); 

    expr_value_clear(&output);
}

static void test_number(const char* expr, double expect) {
    EvalResult result;
    ExprValue output;
    expr_value_init(&output);

    result = eval_execute(expr, eval_default_hooks(), 0, &output);
    printf("%s %s\n", expr, eval_result_to_string(result));
    assert(result == EVAL_RESULT_OK);
    assert(output.type == EXPR_VALUE_TYPE_NUMBER && (output.v.val - expect) == 0); 
}

int main()
{
    /*string -> number*/
    test_number("\"1\" < \"2\"", 1);
    test_number("\"1\" <= \"2\"", 1);
    test_number("\"1\" == \"2\"", 0);
    test_number("\"1\" >= \"2\"", 0);
    test_number("\"1\" > \"2\"", 0);
    test_number("\"1\" != \"2\"", 1);
    test_number("\"1\" || \"2\"", 1);
    test_number("\"1\" || \"\"", 1);
    test_number("\"1\" && \"\"", 0);
    test_number("\"1\" && !\"\"", 1);
    test_number("!\"\"", 1);
    test_number("!\"123\"", 0);
    test_number("\"1\" && !\"\"", 1);
    
    /*string -> string*/
    test_str("\"1\"+\"2\"", "12");
    test_str("\"1\"+2", "12");
    test_str("\"1\"*2", "1*2");
    test_str("\"1\"-2", "1-2");
    test_str("\"1\"/2", "1/2");
    test_str("\"1\"&2", "1&2");
    test_str("\"1\"|2", "1|2");
    
    /*number -> number*/
    test_number("2 < 3", 1);
    test_number("2 <= 3", 1);
    test_number("2 == 3", 0);
    test_number("2 >= 3", 0);
    test_number("2 > 3", 0);
    test_number("2 != 3", 1);
    test_number("2 || 3", 1);
    test_number("2 || 0", 1);
    test_number("1 && 0", 0);
    test_number("1 && !0", 1);
    test_number("!0", 1);
    test_number("!123", 0);
    
    test_number("1+2", 3);
    test_number("1+22", 23);
    test_number("2*3", 6);
    test_number("1-2", -1);
    test_number("1/2", 0.5);
    test_number("1&2", 0);
    test_number("1|2", 3);
    test_number("1 + -2", -1);
    test_number("1 + !2", 1);

    /*bracket*/
    test_number("1+(2*3)", 7);
    test_number("1+(2*(3-2))", 3);
    test_number("(2+3)*(8-6)", 10);

    /*fucntions*/
    test_number("number(123)", 123);
    test_number("number(\"123\")", 123);
    test_str("string(123)", "123");
    test_str("string(\"123\")", "123");

    test_number("strlen(123)", 3);
    test_number("strlen(\"123\")", 3);

    test_str("tolower(\"aBc\")", "abc");
    test_str("toupper(\"aBc\")", "ABC");
    test_str("toupper(\"It Is Upper\")", "IT IS UPPER");

    return 0;
}

