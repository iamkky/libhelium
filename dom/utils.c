#include "stdlib.h"
#include "abd/printf.h"
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

He heTextf(char *fmt, ...)
{
va_list args;
char	buffer[128], *buffer2;
int	size;

	va_start(args, fmt);

	if((size = vsnprintf(buffer, 128, fmt, args)) < 128){
		buffer2 = buffer;
	}else{
		if((buffer2 = malloc(size+1)) == NULL){
			va_end(args);
			return NULL;
		}
		vsnprintf(buffer2, size+1, fmt, args);
	}

	va_end(args);

	return heNew(HELIUM_TEXT_TAG, buffer2);
}

He heList()
{
	return heNew(HELIUM_LIST_TAG);
}

He heListv(va_list args)
{
	return heNewv(HELIUM_LIST_TAG, args);
}


