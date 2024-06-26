/*
	Use example for libhelium

	A basic form creationg code.
	No validation, not data processing.
	Just rendering.

 */


#include <stdio.h>
#include <stdlib.h>
#include <helium/He.h>
#include <abd/new.h>
#include "cgi.h"

He mkPage(char *title, ...)
{
va_list	args;
He	children;

	children = HE_GET_CHILDREN(title);

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

He mkFormLine(char *label, He field)
{

	if(label){
		return heNew("div",
			heNew("div", heText(label), NULL),
			heNew("div", 
				heClass("formline"),
				field,
				NULL),
			NULL	
		);
	}else{
		return heNew("div",
			heClass("formline"),
			heNew("div", field, NULL),
			NULL
		);
	}
}

He mkFormTitle(He content)
{
	return mkFormLine(NULL, heNew("div", heClass("formtitle"), content, NULL));
}

He mkForm(char *action, char *method, char *title, ...)
{
va_list	args;
He	children;

	children = HE_GET_CHILDREN(title);

	return heNew("div", heClass("formclass"),
		heNew("form",
			heAttrNew("action", action),
			heAttrNew("method",method),
			heNew("div",
				heClass("formtitle"),
				heText(title),
				NULL
			),
			heNew("div",
				heClass("formcontent"),
				children,
				NULL
			),
			NULL
		),
		NULL
	);
}

He mkFormFieldButton(char *type, ...)
{
va_list	args;
He	children;

	children = HE_GET_CHILDREN(type);

	return mkFormLine(NULL, heNew("button", heClass("input"), heAttrNew("type", type), children, NULL));
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

	children = HE_GET_CHILDREN(name);
  
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
			mkForm("form", "GET", "Example Form",
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
AString	st;
He		page;

	page = cgi_editform_example(0);

	puts("Content-type: text/html\r\n\r\n");
	puts("<!DOCTYPE html PUBLIC '-//W3C//DTD HTML 4.01 Transitional//EN'>");

	st = CNew(AStrinf, 1024);
	heRender(page, st);
	puts(aStringGetBuffer(st));
	aStringFree(st);

}
