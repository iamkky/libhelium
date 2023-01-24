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
	return heNew(HELIUM_TEXT_TAG, text);
}

He heList()
{
	return heNew(HELIUM_LIST_TAG);
}

He heListv(va_list args)
{
	return heNewv(HELIUM_LIST_TAG, args);
}


