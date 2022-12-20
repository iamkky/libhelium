#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <abd/StringBuffer.h>
#include "helium/He.h"

static int isVoid(char *face);

void heRender(He self, StringBuffer sb)
{
HeAttr		attr;
He		child;

	if(self==NULL) return;
	if(self->magic!=HLIB_ELEMENT) return;

	if(!strcmp(self->face,"text")){
		stringBufferAddStr(sb, self->content);
		return;
	}

	stringBufferAddf(sb, "<%s", self->face);

	if(self->id) stringBufferAddf(sb, " id = \"%s\"", self->id);

	if(self->cl) stringBufferAddf(sb, " class = \"%s\"", self->cl);

	for(attr = self->attribute; attr !=NULL; attr = attr->next){
		if(!strcmp(attr->name,"id")) continue;
		if(!strcmp(attr->name,"class")) continue;
		stringBufferAddf(sb, " %s = \"%s\"", attr->name, attr->value);
	}
	stringBufferAddStr(sb, ">\n");

	for(child = self->child; child !=NULL; child = child->next){
		heRender(child, sb);
	}

	if(!isVoid(self->face)) stringBufferAddf(sb, "</%s>\n", self->face);
}

static int isVoid(char *face)
{
static char *void_list[] = {"area", "base", "br", "col", "embed", "hr", "img", "input", "keygen", "link", "meta", "param", "source", "track", "wbr", NULL};
char **word;

	if(face==NULL) return 0;

	for(word = void_list; *word; word++){
		if(!strcmp(face, *word)) return 1;
	}

	return 0;
}


/*

void heRenderJson(He self, StringBuffer sb)
{
HeAttr	a;
He	c;
int32_t	h;
char	*st;

	if(self==NULL) return;
	if(self->magic!=HLIB_ELEMENT) return;

	if(!strcmp(self->face,"text")){
		h = hashAddString(e->type, e->content.text);
		stringBufferAddStr(sb, self->content);
		return;
	}

	case HTELEMENT_PLAINTEXT:
		if(e->content.text) {

			//Fixme: Should be HTML escape and not JSON escape... But works by now.
			stringBufferAppendf(sb, "{\"t\":\"%d\", \"v\":\"%s\", \"h\":%d}", e->type, st=strJsonEscape(e->content.text), h);
			if(st) free(st);
		}
		break;

	default:
		if(e!=NULL && e->postJs!=NULL) {
			errLogf("postJs  unsupported\n");
		}

		stringBufferAppendf(sb, "{\"t\":\"%d\"", e->type);

		h = htElementRenderJsonHashAcc(e->type, 0);
		if(e->clas){
			stringBufferAppendf(sb, ", \"c\":\"%s\"", e->clas);
			h = htElementRenderJsonHashString(h, e->clas);
		}
		if(e->id){
			stringBufferAppendf(sb, ", \"i\":\"%s\"", e->id);
			h = htElementRenderJsonHashString(h, e->id);
		}
		a = e->attr;
		if(a){
			stringBufferAppendf(sb, ", \"at\":[");
			while(a!=NULL){
				if(a->ptr){
					stringBufferAppendf(sb, "{\"n\":\"%s\", \"v\":%ld, \"p\":\"%p\"}",a->name,(long)a->value, a->ptr);
					// Fixme: hash does not reflect changes in handler function pointer... 
					h = htElementRenderJsonHashString(h, a->name);
					h = htElementRenderJsonHashString(h, a->value);
				}else{
					stringBufferAppendf(sb, "{\"n\":\"%s\", \"v\":\"%s\"}", a->name, a->value);
					h = htElementRenderJsonHashString(h, a->name);
					h = htElementRenderJsonHashString(h, a->value);
				}
				if((a = a->next)) stringBufferAppendf(sb, ", ");
			}
			stringBufferAppendf(sb, " ]");
		}
		c = e->content.child;
		if(c){
			stringBufferAppendf(sb, ", \"ch\":[\n");
			while(c!=NULL){
				htElementRenderJson(c, sb);
				if((c = c->next)) stringBufferAppendf(sb, ",\n ");
			}
			stringBufferAppendf(sb, "\n]");
		}
		stringBufferAppendf(sb, ", \"h\":%d}", h);
       }

	return sb;
}
*/

