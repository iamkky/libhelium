#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include "helium/He.h"

static inline char *safe_strdup(const char *str)
{
	return str ? strdup(str) : NULL;
}

static inline void safe_free(void *ptr)
{
	if(ptr) free(ptr);
}

// HTML Elements

He heNew(const char *face, ...)
{
va_list args;
He self;

	va_start(args, face);
	self = heNewv(face, args);
	va_end(args);

	return self;
}

He heNewv(const char *face, va_list args)
{
He	self;
		
	if(face == NULL) return NULL;

	if((self = malloc(sizeof(He_st))) == NULL) {
		//errLogf("Malloc failed in HtElemenetNew\n");
		return NULL;
	}

	self->magic		= HLIB_ELEMENT;
	self->face		= safe_strdup(face);
	self->id		= NULL;
	self->cl		= NULL;
	self->attribute		= NULL;
	self->content		= NULL;
	self->child		= NULL;
	self->child_last	= NULL;
	self->next		= NULL;

	if(!strcmp(face,HELIUM_TEXT_TAG)){
		self->content = safe_strdup(va_arg(args, char *));
	}else{
		heAddChildv(self, args);
	}

	return self;
}

void heFree(He self)
{
He	child, next_child;
HeAttr	attribute, next_attribute;

	if(self==NULL) return;
	if(self->magic!=HLIB_ELEMENT) return;

	safe_free(self->face);
	safe_free(self->id);
	safe_free(self->cl);

	attribute = self->attribute;
	while(attribute != NULL){
		next_attribute = attribute->next;
		heAttrFree(attribute);
		attribute = next_attribute;
	}

	safe_free(self->content);

	child = self->child;
	while(child != NULL){
		next_child = child->next;
		heFree(child);
		child = next_child;
	}


	free(self);
}
	
static He heGetLast(He self)
{
He last = self;

	while(last->next){
		last = last->next;
	}

	return last;
}

void heAddChild(He self, He child)
{
	if(self==NULL) return;
	if(self->magic!=HLIB_ELEMENT) return;

	if(child!=NULL && !strcmp(child->face, HELIUM_LIST_TAG)){
		child = child->child;
	}

	if(self->child == NULL){
		self->child = child;
	}else{
		self->child_last->next = child;
	}
	self->child_last = heGetLast(child);
}

void heAddChildv(He self, va_list args)
{
He	child;
hmagic	*param;

	if(self==NULL) return;
	if(self->magic!=HLIB_ELEMENT) return;

	while((param = va_arg(args, hmagic *))!=NULL){
		if(*param == HLIB_ELEMENT) heAddChild(self, (He) param);
		if(*param == HLIB_ATTRIBUTE) heAddAttribute(self, (HeAttr) param);
	}

}

void heAddAttribute(He self, HeAttr attr)
{
	if(self==NULL) return;
	if(self->magic!=HLIB_ELEMENT) return;

	attr->next = self->attribute;
	self->attribute = attr;

	if(!strcmp(attr->name,"id")){
		if(self->id) free(self->id);
		self->id = safe_strdup(attr->value);
	}

	if(!strcmp(attr->name,"class")){
		if(self->cl) free(self->cl);
		self->cl = safe_strdup(attr->value);
	}
}

char* heGetAttr(He self, char *attr_name)
{
HeAttr		attr;

	if(self==NULL) return NULL;
	if(attr_name==NULL) return NULL;
	if(self->magic!=HLIB_ELEMENT) return NULL;
	if(!strcmp(self->face,HELIUM_TEXT_TAG)) return NULL;

	if(!strcmp(attr_name,"id")) return self->id;
	if(!strcmp(attr_name,"class")) return self->cl;

	for(attr = self->attribute; attr !=NULL; attr = attr->next){
		if(!strcmp(attr->name,attr_name)) return attr->value;
	}

	return NULL;
}

// Attributes

HeAttr heAttrNew(char *name, const char *value)
{
HeAttr	self;
		
	if(name==NULL) return NULL;

	if((self = malloc(sizeof(HeAttr_st))) == NULL) {
		//errLogf("Malloc failed in HtElemenetNew\n");
		return NULL;
	}

	self->magic		= HLIB_ATTRIBUTE;

	self->name		= safe_strdup(name);
	self->value		= safe_strdup(value);

	self->next		= NULL;

	return self;
}

HeAttr heAttrNewf(char *name, const char *fmt, ...)
{
va_list args;
char    buffer[128], *buffer2;
int     size;

	if(name==NULL) return NULL;
	if(fmt==NULL) return NULL;

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

        return heAttrNew(name, buffer2);
}

HeAttr heAttrNewEvent(char *name, void *target, int (*handler)(void *targer, char *value), const char *value)
{
HeAttr	self;

        if((self = heAttrNew(name, value))==NULL) return NULL;
        self->target = target;
        self->handler = handler;
        return self;
}

void heAttrFree(HeAttr self)
{
	if(self==NULL) return;
	if(self->name) free(self->name);
	if(self->value) free(self->value);
	free(self);
}
