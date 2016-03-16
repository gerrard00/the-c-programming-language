#include <stdio.h>
#include <string.h>
#include "dcl-common.h"

/* undcl: convert word description to declaration*/
int main()
{
	int type;
	char temp[MAXTOKEN];

	while(gettoken() != EOF) {
		strcpy(out, token);
		while((type = gettoken()) != '\n') {
			if (type == PARENS || type == BRACKETS) {
        // If the last token was an asterisk, we have a 
        // pointer to a function. We need to wrap the current
        // output in parens.
        if (previous_tokentype == '*') {
          sprintf(temp,"(%s)%s", out, token);
          strcpy(out, temp);
        } else {
          strcat(out, token);
        }
			} else if (type == '*') {
        sprintf(temp,"*%s", out);
				strcpy(out, temp);
			} else if (type == NAME) {
				sprintf(temp,"%s %s", token, out);
				strcpy(out, temp);
			} else {
				printf("invalid input at %s\n", token);
			}
		}
		printf("%s\n", out);
	}
	return 0;
}

