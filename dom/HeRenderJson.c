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

void heRenderJson(He self, AString sb)
{
HeAttr	a;
He	c;
int32_t	hash;
char	*st;

	if(self==NULL) return;
	if(self->magic!=HLIB_ELEMENT) return;

	if(!strcmp(self->face,HELIUM_TEXT_TAG)){
		if(self->content) {
			aStringAddf(sb, "{\"t\":\"%s\", \"v\":\"%s\", \"h\":%d}", 
				//hashAccString(0,self->face),
				self->face,
				st=strEscapeJson(self->content),
				hashAccString(0,self->content)
				);
			if(st) free(st);
		}
	}else{
		hash = 0;

		//aStringAddf(sb, "{\"t\":\"%d\"", hashAccString(0, self->face));
		aStringAddf(sb, "{\"t\":\"%s\"", self->face);

		hash = 0;
		if(self->cl){
			aStringAddf(sb, ", \"c\":\"%s\"", self->cl);
			hash = hashAccString(hash, self->cl);
		}
		if(self->id){
			aStringAddf(sb, ", \"i\":\"%s\"", self->id);
			hash = hashAccString(hash, self->id);
		}
		a = self->attribute;
		if(a){
			aStringAddf(sb, ", \"at\":[");
			while(a!=NULL){
/*
				if(a->handler){
					aStringAddf(sb, "{\"n\":\"%s\", \"c\":\"%d\", \"v\":\"%s\", \"p\":\"%p\"}",
								a->name, (int)(a->target), a->value, a->handler);
					aStringAddf(sb, "{\"n\":\"%s\", \"v\":\"%s\" }", a->name, a->value);
					
					// Fixme: hash does not reflect changes in handler function pointer... 
					//        neither component pointer... 
					hash = hashAccInt(hash, (int)(a->target));
					hash = hashAccString(hash, a->name);
					hash = hashAccString(hash, a->value);
				}else{
*/
					aStringAddf(sb, "{\"n\":\"%s\", \"v\":\"%s\"}", a->name, a->value);
					hash = hashAccString(hash, a->name);
					hash = hashAccString(hash, a->value);
			//	}
				if((a = a->next)) aStringAddf(sb, ", ");
			}
			aStringAddf(sb, " ]");
		}
		c = self->child;
		if(c){
			aStringAddf(sb, ", \"ch\":[\n");
			while(c!=NULL){
				heRenderJson(c, sb);
				if((c = c->next)) aStringAddf(sb, ",\n ");
			}
			aStringAddf(sb, "\n]");
		}
		aStringAddf(sb, ", \"h\":%d}", hash);
	}
}

