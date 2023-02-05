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
			heNew("link", heAttrNew("rel","stylesheet"), heAttrNew("href","/theme_default.css"), NULL),
			heNew("link", heAttrNew("rel","stylesheet"), heAttrNew("href","/form.css"), NULL),
			heNew("meta", heAttrNew("http-equiv", "content-type"), heAttrNew("content","text/html"), heAttrNew("charset","ISO-8859-1"), NULL),
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
He	children;

	va_start(args, method);
	children = heListv(args);
	va_end(args);

	return  heNew("form", heAttrNew("action", action), heAttrNew("method",method),
		heNew("table",
			heNew("tbody", children, NULL),
			NULL
		),
		NULL
	);
}

He mkFormLine(char *label, He field)
{

	if(label){
		return heNew("tr",
			heClass("formline"),
			heNew("td", heText(label), NULL),
			heNew("td", field, NULL),
			NULL	
		);
	}else{
		return heNew("tr",
			heNew("td", heAttrNew("colspan","2"), field, NULL),
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

	return mkFormLine(NULL, heNew("button", heClass("input"), heAttrNew("type", type), children, NULL));
}

He mkFormTitle(He content)
{
	return mkFormLine(NULL, heNew("div", heClass("formtitle"), content, NULL));
}


He mkFormFieldText(char *label, char *name, char *size)
{
	return mkFormLine(label, heNew("input", heClass("input"), heAttrNew("name", name), heAttrNew("size", size), NULL));
}

He mkFormFieldHidden(char *name, char *size)
{
	return heNew("input", heAttrNew("name", name), heAttrNew("type", "hidden"), NULL);
}

He mkFormFieldSelect(char *label, char *name, char **options, int n_options)
{
He select;

	select = heNew("select", heClass("input"), heAttrNew("name", name), NULL);

	for(int c=0; c<n_options; c++){
		heAddChild(select, heNew("option", heAttrNew("value", options[c]), heText(options[c]), NULL));
	}
	
	return mkFormLine(label, select);
}

He mkFormFieldRadio(char *label, char **options, int n_options)
{
He div;

	div = heNew("div", NULL);

	n_options<<=1;

	for(int c=0; c<n_options; c+=2){
		heAddChild(div, heNew("input", heClass("radiobutton"), heAttrNew("type", "radio"), heAttrNew("name", options[c]), NULL));
		heAddChild(div, heText(options[c+1]));
	}
	
	return mkFormLine(label, div);
}

He mkCenterBox(char *name, ...)
{
va_list	args;
He	children;

	va_start(args, name);
	children = heListv(args);
	va_end(args);
  
	return  heNew("div",
			heClass("centerbox"),
			heNew("div",
				heClass("shadowbox"),
				children,
				NULL
			),
			NULL
		);
}

He cgi_editform_example(int id)
{
char *continents[] = {"Africa","America","Asia","Europe","Oceania"};
char *money_options[] = {"makemoney", "Make money", "spendmoney", "Spend money", "dontcare", "Don't care about money"};
char *query_string;

	query_string = getenv("QUERY_STRING");

	return mkPage("Form Example", 
		heNew("div",
			heAttrNew("Style","color: yellow;"),
			heText("Last Query String: "),
			heText(query_string),
			NULL
		),
		mkCenterBox("noname",
			mkForm("form", "GET",
				mkFormTitle(heText("Example Form")),
				mkFormFieldHidden("id", "0"),
				mkFormFieldText("Name:", "name", "20"),
				mkFormFieldText("Age:", "age", "20"),
				mkFormFieldSelect("Continent:", "continent", continents, 5),
				mkFormFieldRadio("Money option:", money_options, 3),
				mkFormFieldButton("submit", heText("Submit"), NULL),
				NULL
			),
			NULL
		),
		NULL
	);
}

int main(void)
{
StringBuffer	st;
He		page;

	page = cgi_editform_example(0);

	puts("Content-type: text/html\r\n\r\n");
	puts("<!DOCTYPE html PUBLIC '-//W3C//DTD HTML 4.01 Transitional//EN'>");

	st = StringBufferNew(1024);
	heRender(page, st);
	puts(stringBufferGetBuffer(st));
	stringBufferFree(st);
}
