#include "ucfg.h"
#include <string.h>
#include <stdio.h>

#define assert_strequals(obj1, obj2, msg) \
	if (strcmp((obj1), (obj2)) != 0) { \
		fprintf(stderr, "Assertion error on line %i: '%s'. Expected '%s', got '%s'\n", __LINE__, msg, obj1, obj2); \
	};

#define assert_equals(obj1, obj2, msg) \
	if ((obj1) != (obj2)) { \
		fprintf(stderr, "Assertion error on line %i: '%s'\n", __LINE__, msg); \
	};

#define assert_not_equals(obj1, obj2, msg) \
	if ((obj1) == (obj2)) { \
		fprintf(stderr, "Assertion error on line %i: '%s'\n", __LINE__, msg); \
	};

void test_string()
{
	char* outstr;
	const char* strcfg = "\
root: {\n\
  child: \"child value\";\n\
  another child: \"another child's value\";\n\
  child node with list: {\n\
    \"list item1 has some double-quotes:\"\" and \"\" such\"\" \";\n\
    \"list item2\";\n\
  }\n\
}\n";
	ucfg_node *cfg, *tmp;
	ucfg_read_string(&cfg, strcfg);

	assert_equals (ucfg_lookup(&tmp, cfg, "root:child node with list:"), UCFG_OK, "Failure when looking up element");
	assert_strequals("list item1 has some double-quotes:\" and \" such\" ", tmp->value, "Couldn't find element in node list");
	ucfg_write_string(cfg, &outstr);
	assert_strequals(strcfg, outstr, "Output is not input");
}

int main()
{
	test_string();
	return 0;
}
