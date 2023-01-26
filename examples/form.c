/*
	Use example for libhelium

	A basic form creationg code.
	No validation, not data processing.
	Just rendering.

 */


#include <stdio.h>
#include <stdlib.h>
#include <helium/He.h>
#include "cgi.h"

He mkPage(char *title, ...)
{
va_list	args;
He	children;

	va_start(args, title);
	children = heListv(args);
	va_end(args);

	return heNew("html",
		heNew("head",
			heNew("meta", heAttrNew("http-equiv", "content-type"), heAttrNew("content","text/html"), heAttrNew("charset","ISO-8859-1"), NULL),
			heNew("meta", heAttrNew("name", "author"), heAttrNew("content","Rafael Steil"), NULL),
			heNew("title",
				heText(title),
				NULL
			),
			NULL
		),
		heNew("body",
			children,
			NULL
		),
		NULL
	);
}

He mkForm(char *action, char *method, ...)
{
va_list	args;
He	form, children;

	va_start(args, method);
	children = heListv(args);
	va_end(args);

	form = heNew("form", heAttrNew("action", action), heAttrNew("method",method),
		heNew("table",
			heNew("tbody", children, NULL),
			NULL
		),
		NULL
	);

	return form;
}

He mkFormLine(char *label, He field)
{
	if(label){
		return heNew("tr",
			heNew("td", heText(label), NULL),
			heNew("td", field, NULL),
			NULL
		);
	}else{
		return heNew("tr",
			heNew("td", field, NULL),
			NULL
		);
	}
}

He mkFormFieldButton(char *type, ...)
{
va_list	args;
He	children;

	va_start(args, type);
	children = heListv(args);
	va_end(args);

	return mkFormLine(NULL, heNew("button", heAttrNew("type", type), children, NULL));
}


He mkFormFieldText(char *label, char *name, char *size)
{
	return mkFormLine(label, heNew("input", heAttrNew("name", name), heAttrNew("size", size), NULL));
}

He mkFormFieldHidden(char *name, char *size)
{
	return heNew("input", heAttrNew("name", name), heAttrNew("type", "hidden"));
}

He mkFormFieldSelect(char *label, char *name, char **options, int n_options)
{
He select;

	select = heNew("select", heAttrNew("name", name), NULL);

	for(int c=0; c<n_options; c++){
		heAddChild(select, heNew("option", heAttrNew("value", options[c]), heText(options[c]), NULL));
	}
	
	return mkFormLine(label, select);
}

He mkFormFieldRadio(char *label, char *name, char **options, int n_options)
{
He div;

	div = heNew("div", heAttrNew("name", name), NULL);

	for(int c=0; c<n_options; c++){
		heAddChild(div, heNew("input", heAttrNew("type", "radio"), heAttrNew("name", name), NULL));
		heAddChild(div, heText(options[c]));
	}
	
	return mkFormLine(label, div);
}

He cgi_editform_x(int id)
{
char *continents[] = {"Africa","America","Asia","Europe","Oceania"};
char *money_options[] = {"Make money","Spend money","Don't care about money"};
char *query_string;

	query_string = getenv("QUERY_STRING");

	return mkPage("Form Example", 
		heNew("div",
			heText("Last Query String: "),
			heText(query_string),
			NULL
		),
		mkForm("form", "GET",
			mkFormFieldHidden("id", "0"),
			mkFormFieldText("Name:", "name", "20"),
			mkFormFieldText("Age:", "age", "20"),
			mkFormFieldSelect("Continent:", "continent", continents, 5),
			mkFormFieldRadio("Money option:", "money", money_options, 3),
			mkFormFieldButton("submit", heText("Submit"), NULL),
			NULL
		),
		NULL
	);
}

int main(void)
{
StringBuffer	st;
He		page;

	page = cgi_editform_x(0);

	puts("Content-type: text/html\r\n\r\n");
	puts("<!DOCTYPE html PUBLIC '-//W3C//DTD HTML 4.01 Transitional//EN'>");

	st = StringBufferNew(1024);
	heRender(page, st);
	puts(stringBufferGetBuffer(st));
	stringBufferFree(st);
}
