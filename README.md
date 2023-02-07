# Lib Helium
------------

A small and compact lib to represent a dom structure.
The main element of lib is the He (Html Element) that represents a minimalist Html Element.

With the help of HeAttr a minimalist Dom can be construted and rendered later.

## Example 1:

```c
He build_a_card(char *title, char *text)
{
	return
		heNew("div",
			heClass("card"),
			heNew("div",
				heClass("cardtitle"),
				heText(title),
				NULL
			),
			heNew("div",
				heClass("cardtext"),
				heText(text),
				NULL
			),
			NULL
		);
}
```

Note:

```heClass(char *class)``` is really just a call to ```heAttrNew("class", class)```, just to shorten things a little bit.

Latter the structure can be rendered as HTML to a StringBuffer (from libabd) using:

```c
void render(He page)
{
StringBuffer    st;

        st = StringBufferNew(1024);
        heRender(page, st);
        puts(stringBufferGetBuffer(st));
        stringBufferFree(st);
}
```

If it's a CGI don't forget the cgi header

```c
int main()
{
He page;

        page = build_a_card("A Card", "This is just a text inside a simple card");

        puts("Content-type: text/html\r\n\r\n");
        puts("<!DOCTYPE html PUBLIC '-//W3C//DTD HTML 4.01 Transitional//EN'>");

		render(page);
}
```

Required includes:

```c
#include <stdio.h>
#include <stdlib.h>
#include <helium/He.h>
```
## Resources

LibHelihum has a number o features to deal with common needs of HTML doc construction.
As an standard way to deal with variadic functions, or ways to add children to already existing elements.

### Adding children

heAddChild(He self, He child); This is how children can be added to a already existing Element.

```c
He mkFormFieldSelect(char *label, char *name, char **options, int n_options)
{
He select;

        select = heNew("select", heClass("input"), heAttrNew("name", name), NULL);

        for(int c=0; c<n_options; c++){
                heAddChild(select, heNew("option", heAttrNew("value", options[c]), heText(options[c]), NULL));
        }

        return mkFormLine(label, select);
}
```

### Dealing with variadic args

This example with just encapsulate a list of Elements with a form tag.
```c
He mkForm(char *action, char *method, ...)
{
va_list args;
He      children;

        va_start(args, method);
        children = heListv(args);
        va_end(args);

        return
		heNew("form",
				heAttrNew("action", action),
				heAttrNew("method",method),
                children,
                NULL
        );
}
```

### A more complete Example

In file [examples/form.c](examples/form.c) is possible to find a complete, even though simple, example that uses many characteristics and features of LibHelium.

Designed as a cgi, this piece of software renders a form with a small number of common fields.
The example does not process any information as dealing with CGI protocol is out of escope of the lib.
However QUERY_STRING is displayed in the upper left corner so one can verify the form is working.

### API

Full API can be find in include file [helium/He.h](helium/He.h)

## Build

A Makefile is profided, so to build just use 'make'

	make

LibHelium requires libabd.
if it's not in the system locations (usually /usr/include and /usr/lib), add those lines before build

	export CFLAGS=-I<PATH TO LIBABD INCLUDE>
	export LIBABD=<PATH TO LIBABD>


## About the Name

Why LibHelium instead of something simpler like LibHe ok hlib?
It's just to avoid poluting name space with too short names.
And sounds nive :-)




