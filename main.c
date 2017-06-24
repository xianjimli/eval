#include <stdio.h>

#include "eval.h"


int main(int argc, char* argv[])
{
    if ( argc >= 2 )
    {
        EvalResult result;
        ExprValue output;
        
        expr_value_set_number(&output, 0);
        result = eval_execute(argv[1], eval_default_hooks(), 0, &output);
        
        if ( result == EVAL_RESULT_OK )
        {
            if(output.type == EDATA_TYPE_STRING) {
                printf("string: %s\n", output.v.str.str);
            }else{
                printf("number: %lf\n", output.v.val);
            }
        }
        else
        {
            printf("%s\n", eval_result_to_string(result));
            return 1;
        }
    }
    else
    {
        printf("Usage: eval <expression>\n");
        return 0;
    }
    
    return 0;
}
