/* Copyright (c) 2010, Torbjörn Lönnemark <tobbez@ryara.net>
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#include <stdio.h>
#include <malloc.h>
#include <string.h>

#include "ucfg.h"

int main(int argc, char **argv)
{
	ucfg_node *cfg, *lvl1, *lvl2;
	int err;

	/* create a root element and set its name */
	cfg = ucfg_new_node();
	ucfg_node_name_set(cfg, "root");

	/* create subsection */
	lvl1 = ucfg_new_node ();
	ucfg_node_sub_append(cfg, lvl1);

	/* set name and value for first element in subsection */
	ucfg_node_name_set(lvl1, "child");
	ucfg_node_value_set(lvl1, "child value");

	/* append another element to the subsection */
	lvl1 = ucfg_new_node ();
	ucfg_node_sub_append(cfg, lvl1);

	/* set name and value for that element */
	ucfg_node_name_set(lvl1, "another child");
	ucfg_node_value_set(lvl1, "another child's value");

	/* append yet another element and name it */
	lvl1 = ucfg_new_node ();
	ucfg_node_sub_append(cfg, lvl1);
	ucfg_node_name_set(lvl1, "child node with list");

	/* and make it a subsection */
	lvl2 = ucfg_new_node ();
	ucfg_node_sub_append(lvl1, lvl2);

	/* add some values without names (i.e. a list) to the subsection */
	ucfg_node_value_set(lvl2, "list item1 has some double-quotes:"
			    "\" and \" such\" ");
	lvl2 = ucfg_new_node ();
	ucfg_node_sub_append(lvl1, lvl2);
	ucfg_node_value_set(lvl2, "list item2");

	/* serialize config onto stdout */
	ucfg_write(cfg, stdout);

	/* serialize config into file 'example.conf' */
	if ((err = ucfg_write_file(cfg, "example.conf")) != UCFG_OK) {
		printf("%s\n", ucfg_strerror(err));
	}

	/* destroy config structure and free its memory */
	ucfg_node_destroy(cfg);

	/* load previously written config file */
	if ((err = ucfg_read_file(&cfg, "example.conf")) == UCFG_OK) {

		/* lookup a value in the config and print it */
		if (ucfg_lookup(cfg, &lvl2, "root:child node with list:") == UCFG_OK)
			printf("%s\n", lvl2->value);

		ucfg_node_destroy(cfg);
	} else {
		printf("%s\n", ucfg_strerror(err));
	}

	return 0;
}
