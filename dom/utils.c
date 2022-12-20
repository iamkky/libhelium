#include "helium/He.h"

HeAttr heClass(char *class_name)
{
	return heAttrNew("class", class_name);
}

HeAttr heId(char *id_name)
{
	return heAttrNew("id", id_name);
}

He heText(char *text)
{
	return heNew("text", text);
}


