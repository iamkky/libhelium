#include <stdio.h>
#include <stdlib.h>
#include <helium/He.h>

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

void render(He page)
{
AString    st;

        st = AStringNew(1024);
        heRender(page, st);
        puts(aStringGetBuffer(st));
        aStringFree(st);
}


int main()
{
He page;

        page = build_a_card("A Card", "This is just a text inside a simple card");

        puts("Content-type: text/html\r\n\r\n");
        puts("<!DOCTYPE html PUBLIC '-//W3C//DTD HTML 4.01 Transitional//EN'>");

	render(page);
}
