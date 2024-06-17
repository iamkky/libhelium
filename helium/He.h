#ifndef _HLIB_H_
#define _HLIB_H_

#include <stdarg.h>
#include <stdint.h>
#include <abd/AString.c.h>

typedef uint32_t hmagic;

//typedef int HEventHandler_t(AString type, void *component, AString value);

#define HLIB_ELEMENT		0x454c454d
#define HLIB_ATTRIBUTE		0x41545452

#define HELIUM_TEXT_TAG		"_text"
#define HELIUM_LIST_TAG		"_list"

#define HE_GET_CHILDREN(last_named_field) (va_start(args, last_named_field), heListv(args)); va_end(args)

#define HE_CHILDREN_START(field)	va_list args; He children; children = HE_GET_CHILDREN(field);


struct HNode_st;
typedef struct HNode_st *HNode;
typedef struct HNode_st HNode_st;

struct He_st;
typedef struct He_st *He;
typedef struct He_st He_st;

struct Hatt_st;
typedef struct HeAttr_st *HeAttr;
typedef struct HeAttr_st HeAttr_st;

struct HeAttr_st {
	hmagic	magic;
	char	*name;
	char	*value;
	//void	*target;
	//int	(*handler)(AString event_type, void *target, AString value);
	//HEventHandler_t	*handler;
	HeAttr	next;
};

struct He_st {
	hmagic	magic;
	char	*face;
	char	*id;
	char	*cl;
	HeAttr	attribute;
	char	*content;
	He	child;
	He	child_last;
	He	next;
};

// HTML Elements
He	heNew(const char *face, ...);
He	heNewv(const char *face, va_list args);
void	heFree(He self);

void	heAddChild(He self, He child);
void	heAddChildv(He self, va_list args);
void	heAddAttribute(He self, HeAttr attr);

char*	heGetAttr(He self, char *attr_anme);

// Attribute
HeAttr	heAttrNew(char *name, const char *value);
HeAttr	heAttrNewf(char *name, const char *fmt, ...);
//HeAttr	heAttrNewEvent(char *name, int (*handler)(AString event_type, void *targer, AString value), void *target, const char *value);
//HeAttr	heAttrNewEvent(char *name, HEventHandler_t *handler, void *target, const char *value);
void	heAttrFree(HeAttr self);

// Utils (shortcuts)
HeAttr	heClass(char *class_name);
HeAttr	heId(char *id_name);
He	heText(char *text);
He	heTextf(char *fmt, ...);

// utils (support to variadic)
He	heList();
He	heListv(va_list args);

// Renderers
void	heRender(He e, AString sb);
void	heRenderJson(He self, AString sb);

#endif
