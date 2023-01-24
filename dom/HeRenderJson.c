#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <abd/strEscapeJson.h>
#include <helium/He.h>

int32_t static inline hashAccInt(int32_t hash, int data)
{
	return (hash + data) & 0xfffffff;
}

int32_t static hashAccString(int32_t hash, const char *data)
{
	while(*data)
		hash = (hash + *data++) & 0x3fffffff;

	return hash;
}

void heRenderJson(He self, StringBuffer sb)
{
HeAttr	a;
He	c;
int32_t	hash;
char	*st;

	if(self==NULL) return;
	if(self->magic!=HLIB_ELEMENT) return;

	if(!strcmp(self->face,HELIUM_TEXT_TAG)){
		if(self->content) {
			stringBufferAddf(sb, "{\"t\":\"%d\", \"v\":\"%s\", \"h\":%d}", 
				hashAccString(0,self->face),
				st=strEscapeJson(self->content),
				hashAccString(0,self->content)
				);
			if(st) free(st);
		}
	}else{
		hash = 0;

		stringBufferAddf(sb, "{\"t\":\"%d\"", hashAccString(0, self->face));

		hash = 0;
		if(self->cl){
			stringBufferAddf(sb, ", \"c\":\"%s\"", self->cl);
			hash = hashAccString(hash, self->cl);
		}
		if(self->id){
			stringBufferAddf(sb, ", \"i\":\"%s\"", self->id);
			hash = hashAccString(hash, self->id);
		}
		a = self->attribute;
		if(a){
			stringBufferAddf(sb, ", \"at\":[");
			while(a!=NULL){
				if(a->ptr){
					stringBufferAddf(sb, "{\"n\":\"%s\", \"c\":\"%d\", \"v\":%ld, \"p\":\"%p\"}",
								a->name, (int)(a->component), (long)a->value, a->ptr);
					// Fixme: hash does not reflect changes in handler function pointer... 
					//        neither component pointer... 
					hash = hashAccInt(hash, (int)(a->component));
					hash = hashAccString(hash, a->name);
					hash = hashAccString(hash, a->value);
				}else{
					stringBufferAddf(sb, "{\"n\":\"%s\", \"v\":\"%s\"}", a->name, a->value);
					hash = hashAccString(hash, a->name);
					hash = hashAccString(hash, a->value);
				}
				if((a = a->next)) stringBufferAddf(sb, ", ");
			}
			stringBufferAddf(sb, " ]");
		}
		c = self->child;
		if(c){
			stringBufferAddf(sb, ", \"ch\":[\n");
			while(c!=NULL){
				heRenderJson(c, sb);
				if((c = c->next)) stringBufferAddf(sb, ",\n ");
			}
			stringBufferAddf(sb, "\n]");
		}
		stringBufferAddf(sb, ", \"h\":%d}", hash);
	}
}

